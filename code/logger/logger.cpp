#include <stdio.h>
#include <cstdlib>
#include "log4cpp/Portability.hh"
#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#ifdef LOG4CPP_HAVE_SYSLOG
#include "log4cpp/SyslogAppender.hh"
#endif
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/Configurator.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include "logger.h"



namespace logger {
	using namespace log4cpp;
	using namespace std;
    // 定义变长参数的总长度（单位:bit)
    const int MAX_BUFFER = MAX_LOG_BUF;

	Clog4cppWapper * Clog4cppWapper::m_this = new Clog4cppWapper();
	
	// sample 为Category的类型，与配置文件log4cpp.property结合使用
    log4cpp::Category * Clog4cppWapper::m_st_log =
			&log4cpp::Category::getRoot();
            //&log4cpp::Category::getInstance(std::string("sample"));

    void Clog4cppWapper::log4cpp_callback(int level,
                                     const char* stringFormat, ...)
    {
        if(NULL == stringFormat || NULL == m_st_log)
        {
            return;
        }

        char buffer[MAX_BUFFER]={0};
        va_list ap;

        va_start(ap,stringFormat);
        int n = vsnprintf(buffer,MAX_BUFFER,stringFormat,ap);
        va_end(ap);

        if(n < 0 || n >= MAX_BUFFER)
        {
            m_st_log->error("log4cpp callback is error,buffer len is not enough.cur len [%d]",n);
            return;
        }
	buffer[n]='\0';
        m_this->log4cpp_log((logger::LogLevel)level,buffer);
    }

    Clog4cppWapper::Clog4cppWapper()
    {
        try
        {
		using std::string;
		string local_config="config/log4cpp.property";
		string home_config=string(getenv("HOME"))+"/."+local_config;
		string config(local_config);
		if(::access(local_config.c_str(),F_OK))
			config=home_config;
			// 注意配置文件的路径
            log4cpp::PropertyConfigurator::configure(config.c_str());
        }
		catch (log4cpp::ConfigureFailure & e)
		{
			std::cerr << "configure problem " << e.what() << std::endl;
        }
    }

    Clog4cppWapper::~Clog4cppWapper()
    {
    }

    void Clog4cppWapper::log4cpp_log(LogLevel level,const char* stringFormat, ...)
    {
        if(NULL == stringFormat || NULL == m_st_log)
        {
            return;
        }

        char buffer[MAX_BUFFER]={0};
        va_list ap;

        va_start(ap,stringFormat);
        int n = vsnprintf(buffer,MAX_BUFFER,stringFormat,ap);
        va_end(ap);

        if(n < 0 || n >= MAX_BUFFER)
        {
            m_st_log->error("buffer len is not enough.cur len [%d]",n);
            return;
        }

        switch (level)
        {
        /*case EN_EMERG:
            m_st_log->emerg(buffer);
            break;*/
        case EN_FATAL:
            m_st_log->fatal(buffer);
            break;
        case EN_ALERT:
            m_st_log->alert(buffer);
            break;
        case EN_CRIT:
            m_st_log->crit(buffer);
            break;
        case EN_ERROR:
            m_st_log->error(buffer);
            break;
        case EN_WARN:
            m_st_log->warn(buffer);
            break;
        case EN_NOTICE:
            m_st_log->notice(buffer);
            break;
        case EN_INFO:
            m_st_log->info(buffer);
            break;
        case EN_DEBUG:
            m_st_log->debug(buffer);
            break;
        case EN_NOTSET:
			// 暂不支持
        default:
            break;
        }

        return;
    }
}
