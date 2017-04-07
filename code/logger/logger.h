#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <cstdio>

namespace log4cpp
{
	class Category;
}

namespace logger{
	
	/// 日志等级枚举
	typedef enum {
		//EN_EMERG  = 0,
		EN_FATAL  = 0,
		EN_ALERT  = 100,
		EN_CRIT   = 200,
		EN_ERROR  = 300,
		EN_WARN   = 400,
		EN_NOTICE = 500,
		EN_INFO   = 600,
		EN_DEBUG  = 700,
		EN_NOTSET = 800
	} LogLevel;
	
    class Clog4cppWapper
    {
	    /// @brief	构造函数
        /// @detail 
        /// @param[in]
        /// @param[out]
        /// @return: 
        ///
        Clog4cppWapper();
		
		/// @brief	析构函数
        /// @detail 
        ///	@param[in]
        /// @param[out]
        /// @return:
        ///
        ~Clog4cppWapper();

    public:

		/// @brief	日志回调函数
        /// @detail 
        /// @param[in]  level 日志等级
        ///	@param[in]	stringFormat 日志内容
        /// @param[out]	
        /// @return: void
        ///
        static void log4cpp_callback(int level,const char* stringFormat, ...);

	private:
		/// @brief	日志记录（打印）
        /// @detail 
        /// @param[in]  level 日志等级
        ///	@param[in]	stringFormat 日志内容
        /// @param[out]	
        /// @return: void
        ///
        void log4cpp_log(LogLevel level,const char* stringFormat, ...);
		
    private:
		/// log4cpp 日志类别静态变量
        static log4cpp::Category * m_st_log;
		
		/// 供回调使用
		static Clog4cppWapper * m_this;
    };
}

enum logger_level{
		//EN_EMERG  = 0,
		EN_FATAL  = 0,
		EN_ALERT  = 100,
		EN_CRIT   = 200,
		EN_ERROR  = 300,
		EN_WARN   = 400,
		EN_NOTICE = 500,
		EN_INFO   = 600,
		EN_DEBUG  = 700,
		EN_NOTSET = 800
};
/*
#ifdef __main__
void (*p_logger)(int level,const char *fmt,...) =
        logger::Clog4cppWapper::log4cpp_callback;
#else
extern void (*p_logger)(int level,const char *fmt,...);
#endif
*/
static void (*p_logger)(int level,const char *fmt,...) =
        logger::Clog4cppWapper::log4cpp_callback;
#ifndef KB
#define KB 1024
#endif
#ifndef MAX_LOG_BUF
#define MAX_LOG_BUF (5*KB)
#endif
#ifndef LOGGER
#define LOGGER(l,f,...) do {\
    if(p_logger){\
    char __logger_tmp_buf[MAX_LOG_BUF];\
    snprintf(__logger_tmp_buf,MAX_LOG_BUF-1,"[%s:%d] %s",__FILE__,__LINE__,(f));\
    (*p_logger)((l),__logger_tmp_buf,##__VA_ARGS__);\
    }\
}\
    while(0)
#endif // LOGGER
#define LOG_FATAL(x,...) LOGGER(EN_FATAL,x,##__VA_ARGS__)
#define LOG_ERR(x,...) LOGGER(EN_ERROR,x,##__VA_ARGS__)
#define LOG_WARN(x,...) LOGGER(EN_WARN,x,##__VA_ARGS__)
#define LOG_NOT(x,...) LOGGER(EN_NOTICE,x,##__VA_ARGS__)
#define LOG_INFO(x,...) LOGGER(EN_INFO,x,##__VA_ARGS__)
#endif // _LOGGER_H_
