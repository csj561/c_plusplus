#ifndef __FOOL_INTERNAL_HPP
#define __FOOL_INTERNAL_HPP 1
namespace fool
{
	template<typename T>
	void Pri(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<*iter<<"\n";
	}

	template<typename T>
	void PriM(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<iter->first<<" <> "<<iter->second<<"\n";
	}
	template<typename InputIter,typename UnaryPre>
	InputIter find_if_not(InputIter iter1,InputIter iter2,UnaryPre pre)
	{
		while(iter1 != iter2)
		{
			if(!pre(*iter1))
				return iter1;
			iter1++;
		}
		return iter1;
	}
	template<typename InputIter1,typename InputIter2>
	int count_blk(InputIter1 iter1_beg,InputIter1 iter1_end,
				InputIter2 iter2_beg,InputIter2 iter2_end)
	{
		int count=0;
		int iter2_len=0;
		InputIter1 cur=iter1_beg;
		InputIter2 t = iter2_beg;
		
		while(t++!=iter2_end)
			iter2_len++;
		while(iter1_end!=(cur=std::search(cur,iter1_end,iter2_beg,iter2_end)))
		{
			count++;
			for(int i=0; i<iter2_len;i++)
				cur++;
		}
		return count;
	}
	template<typename KEY,typename VALUE,typename CONTAINER=std::vector<KEY> >
	class PreTree
	{
		struct leaf
		{
			VALUE val;
			KEY key;
			leaf *parent;
			std::set<leaf> leafs;
			bool is_have_val;
			leaf():parent(NULL),is_have_val(false){}
			bool operator==(const KEY& _key) const
			{
				return key==_key;
			}
			bool operator<(const leaf &lr) const
			{
				return key<lr.key;
			}
		};
		leaf root;// root不能有其它字段，只能有叶子结点
	public:
		bool add(CONTAINER const &key,const VALUE &val,bool _force=false)
		{
			typename CONTAINER::const_iterator iter;
			leaf* cur=&root;
			for(iter=key.begin();
				iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
				{
					leaf tmp;
					tmp.key=*iter;
					if(key.end()==iter+1)
					{
						tmp.val=val;
						tmp.is_have_val = true;
						tmp.parent=cur;
					}
					cur = (leaf*)&(*cur->leafs.insert(tmp).first);
				}
				else
				{
					if(key.end()==iter+1)
					{
						if(!liter->is_have_val || (liter->is_have_val&& _force))
						{
							leaf *pleaf=(leaf *)&(*liter);// 风险，set的迭代器默认为const类型，怕破坏掉元素内部排序
							pleaf->val=val;
							pleaf->is_have_val=true;
							return true;
						}
						return false;
					}
					cur=(leaf*)&(*liter);
				}
			}
			return true;
		}
		
		bool match(const CONTAINER &key,VALUE &val,CONTAINER *pre=NULL) const 
		{
			typename CONTAINER::const_iterator iter;
			const VALUE *ret=NULL;
			const leaf* cur=&root;
			iter=key.begin();
			if(pre)
				pre->clear();
			for(;iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
					break;
				else
				{
					if(liter->is_have_val)
						ret=&liter->val;
					cur=(const leaf*)&(*liter);
				}
			}
			if(ret)
			{
				val=*ret;
				if(pre)
					pre->assign(key.begin(),iter);
			}
			
			return ret;
		}
		bool del(const CONTAINER &key)
		{
			typename CONTAINER::const_iterator iter;
			leaf *ret=NULL;
			const leaf* cur=&root;
			iter=key.begin();
			for(;iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
					break;
				else
				{
					if(liter->is_have_val&&key.end()==iter+1)
						ret=(leaf *)&(*liter);
					cur=(const leaf*)&(*liter);
				}
			}
			if(ret)
			{
				ret->is_have_val=false;
				while(ret->parent
					&&ret->leafs.empty()
					&&!ret->is_have_val)
				{
					leaf* parent = ret->parent;
					parent->leafs.erase(*ret);
					ret=parent;
				}
				return true;
			}
			return false;
		}
	};
	
	template<typename VALUE>
	class PreTree<std::string,VALUE>
	{
		typedef std::basic_string<char> CONTAINER;
		typedef std::string key_type;
		PreTree< char,VALUE,CONTAINER > data;
		public:
		bool add(const key_type &key,const VALUE &val)
		{return data.add(key,val);}
		bool match(const CONTAINER &key,VALUE &val,CONTAINER *pre=NULL)
		{return data.match(key,val,pre);}
		bool del(const key_type & key)
		{return data.del(key);}
	};
	class thread_guard
	{
		pthread_mutex_t &mutex;
		public:
			thread_guard(pthread_mutex_t &_m):mutex(_m){pthread_mutex_lock(&mutex);}
			~thread_guard(){pthread_mutex_unlock(&mutex);}
	};
	template<typename T,size_t N=UINT_MAX>
	class security_list
	{
		pthread_mutex_t mutex;
		std::list<T> data;
		
		public:
			security_list(){pthread_mutex_init(&mutex,NULL);}
			~security_list(){pthread_mutex_destroy(&mutex);}
			bool push(const T& e)
			{
				try
				{
					thread_guard mt_guard(mutex);
					if(data.size()>=N)
						throw N;
					data.push_back(e);
					return true;
				}
				catch(...)
				{
					return false;
				}
			}
			bool pop(T&e)
			{
				thread_guard mt_guard(mutex);
				if(data.empty())
					return false;
				e=data.front();
				data.pop_front();
				return true;
			}
			int size() const
			{return data.size();}
	};
	class timer
	{
		std::string name;
		clock_t _start_time;
		public:
			timer();
			timer(const char *);
			virtual ~timer();
	};
}
#endif
