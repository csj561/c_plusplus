#ifndef _REDIS_H_
#define _REDIS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <list>

#include <hiredis/hiredis.h>
typedef std::list<std::string> listStr;
class Redis
{
public:

    Redis(){}

    ~Redis()
  {
  this->_connect = NULL;
    this->_reply = NULL;	    	    
  }

  bool connect(std::string host, int port)
  {
      this->_connect = redisConnect(host.c_str(), port);
    if(this->_connect != NULL && this->_connect->err)
    {
        printf("connect error: %s\n", this->_connect->errstr);
      return 0;
    }
    return 1;
  }

    std::string get(std::string key)
  {
    this->_reply = (redisReply*)redisCommand(this->_connect, "GET %s", key.c_str());
    std::string str = this->_reply->str;
    freeReplyObject(this->_reply);
    return str;
  }

  void set(std::string key, std::string value)
  {
  redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
  }

  bool cmd(const char *_cmd,listStr & _list)
  {
  	_list.clear();
  	if(_cmd)
  		this->_reply = (redisReply*)redisCommand(this->_connect, _cmd);
    if(this->_reply)
    {
		parse_reply(this->_reply,_list);
    	freeReplyObject(this->_reply);
		this->_reply=NULL;
    }
    true;;
  }
  bool cmd(int _argc,const char**_argv,listStr & _list)
  {
  	_list.clear();
	size_t *_argv_len=new size_t[_argc+1];
	for(int i=0;i<_argc;i++)
		_argv_len[i]=strlen(_argv[i]);
  	this->_reply = (redisReply*)redisCommandArgv(this->_connect,_argc+1,_argv,_argv_len);
	delete []_argv_len;
	do
	{
		if(this->_reply)
	    {
	    	if(REDIS_REPLY_ERROR == _reply->type)
				break;
			parse_reply(this->_reply,_list);
	    	freeReplyObject(this->_reply);
			this->_reply=NULL;
			return true;
	    }
	}while(0);
	std::cout<<"ERR::"<<_connect->err<<std::endl;
    false;;
  }

  const char *get_err()
  {
  	return _connect->errstr;
  }

private:

  redisContext* _connect;
  redisReply* _reply;
  bool parse_reply(const redisReply * reply,listStr & _list)
  {
  	switch(reply->type) 
	{
    case REDIS_REPLY_INTEGER:
		do{
			char buf[32];
			snprintf(buf,sizeof(buf),"%lld",reply->integer);
			_list.push_back(buf);
		}while(0);
        break;
    case REDIS_REPLY_ARRAY:
        if (reply->element != NULL) {
            for (int j = 0; j < reply->elements; j++)
                if (reply->element[j] != NULL)
                {
                	parse_reply(reply->element[j],_list);
                }
        }
        break;
	case REDIS_REPLY_STRING:
		if(reply->str)
			_list.push_back(std::string(reply->str,reply->len));
		break;
	default:
        break;
	return true;
  	}   
  }
};

#endif  //_REDIS_H_

