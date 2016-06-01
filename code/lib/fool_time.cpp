#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "fool.h"
namespace
{
    char * StrTok_r(char  * s,const char * tokens,char  ** lasts)
    {
        char *ptemp_a = NULL;

        if (s == 0)
            s = *lasts;
        else
            *lasts = s;
        if (*s == 0)                  // We have reached the end
            return 0;
        int l_org = (int)strlen (s);
        s = strtok_r(s, tokens, &ptemp_a);

        if (s == 0)
            return 0;
        const int l_sub = (int)strlen (s);
        if (s + l_sub < *lasts + l_org)
            *lasts = s + l_sub + 1;
        else
            *lasts = s + l_sub;
        return s;
    }
    bool str_to_time_1(char* p, char* pm,
    struct tm& when, char* buf, char* tmp)
    {
        if((p = StrTok_r(buf, "-",&pm)) == NULL
            || (when.tm_year = atoi(p) - 1900 ) > 138
            || when.tm_year < 0
            || (p = StrTok_r(NULL, "-",&pm)) == NULL
            || (when.tm_mon = atoi(p) - 1) < 0
            || when.tm_mon > 11
            || (p = StrTok_r(NULL, " ",&pm)) == NULL
            || (when.tm_mday = atoi(p)) > 31
            || when.tm_mday < 1
            || (p = StrTok_r(NULL, ":",&pm)) == NULL
            || (when.tm_hour = atoi(p)) > 23
            || when.tm_hour < 0
            || (p = StrTok_r(NULL, ":",&pm)) == NULL
            || (when.tm_min = atoi(p)) > 59
            || when.tm_min < 0
            || (p = StrTok_r(NULL, "\0",&pm)) == NULL
            || (when.tm_sec = atoi(p)) > 59
            || when.tm_sec < 0
            )
            return true;
        else
            return false;

    }

    bool str_to_time_2(char* p, char* pm,
    struct tm& when, char* buf, char* tmp)
    {
        if((p = StrTok_r(buf, "/",&pm)) == NULL
            || (when.tm_year = atoi(p) - 1900 ) > 138
            || when.tm_year < 0
            || (p = StrTok_r(NULL, "/",&pm)) == NULL
            || (when.tm_mon = atoi(p) - 1) < 0
            || when.tm_mon > 11
            || (p = StrTok_r(NULL, " ",&pm)) == NULL
            || (when.tm_mday = atoi(p)) > 31
            || when.tm_mday < 1
            || (p = StrTok_r(NULL, ":",&pm)) == NULL
            || (when.tm_hour = atoi(p)) > 23
            || when.tm_hour < 0
            || (p = StrTok_r(NULL, ":",&pm)) == NULL
            || (when.tm_min = atoi(p)) > 59
            || when.tm_min < 0
            || (p = StrTok_r(NULL, "\0",&pm)) == NULL
            || (when.tm_sec = atoi(p)) > 59
            || when.tm_sec < 0
            )
            return true;
        else
            return false;

    }

    bool str_to_time_3(char* p, char* pm,
    struct tm& when, char* buf, char* tmp)
    {
        if(strncpy(tmp, buf, 4) == NULL
            || (when.tm_year = atoi(tmp) - 1900 ) > 138
            || when.tm_year < 0
            || strncpy(tmp + 4, buf + 4, 2) == NULL
            || (when.tm_mon = atoi(tmp + 4) - 1) < 0
            || when.tm_mon > 11
            || strncpy(tmp + 6, buf + 6, 2) == NULL
            || (when.tm_mday = atoi(tmp + 6)) > 31
            || when.tm_mday < 1
            || strncpy(tmp + 8, buf + 8, 2) == NULL
            || (when.tm_hour = atoi(tmp + 8)) > 23
            || when.tm_hour < 0
            || strncpy(tmp + 10, buf + 10, 2) == NULL
            || (when.tm_min = atoi(tmp + 10)) > 59
            || when.tm_min < 0
            || strncpy(tmp + 12, buf + 12, 2) == NULL
            || (when.tm_sec = atoi(tmp + 12)) > 59
            || when.tm_sec < 0
            )
            return true;
        else
            return false;

    }

    bool str_to_time_4(char* p, char* pm,
    struct tm& when, char* buf, char* tmp, char* firstyear)
    {
        if(strncpy(tmp, buf, 2) == NULL
            || (when.tm_year = atoi(strcat(firstyear,tmp)) - 1900 ) > 138
            || when.tm_year < 0
            || strncpy(tmp + 2, buf + 2, 2) == NULL
            || (when.tm_mon = atoi(tmp + 2) - 1) < 0
            || when.tm_mon > 11
            || strncpy(tmp + 4, buf + 4, 2) == NULL
            || (when.tm_mday = atoi(tmp + 4)) > 31
            || when.tm_mday < 1
            || strncpy(tmp + 6, buf + 6, 2) == NULL
            || (when.tm_hour = atoi(tmp + 6)) > 23
            || when.tm_hour < 0
            || strncpy(tmp + 8, buf + 8, 2) == NULL
            || (when.tm_min = atoi(tmp + 8)) > 59
            || when.tm_min < 0
            || strncpy(tmp + 10, buf + 10, 2) == NULL
            || (when.tm_sec = atoi(tmp + 10)) > 59
            || when.tm_sec < 0
            )
            return true;
        else
            return false;
    }
}
namespace fool
{
    std::string time_to_str(time_t i_time,int i_format)
    {
        tm time_tm;
        tm * lt = &time_tm ;
        time_t add_time =  time(NULL);
        char str[64]={0};
        int maxLength=sizeof(str);

        localtime_r(&i_time, &time_tm);

        switch(i_format)
        {
        case 0:
            {
                snprintf(str, maxLength, "%d%02d%02d%02d%02d%02d",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday, lt->tm_hour,
                    lt->tm_min, lt->tm_sec);
            }
            break;
        case 1:
            {
                snprintf(str, maxLength, "%d-%02d-%02d %02d:%02d:%02d",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday, lt->tm_hour,
                    lt->tm_min, lt->tm_sec);
            }
            break;
        case 2:
            {
                snprintf(str, maxLength, "%d-%02d-%02d 00:00:00",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday);
            }
            break;
        case 5:
            {
                snprintf(str, maxLength, "%d%02d%02d%02d0000",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday, lt->tm_hour);
            }
            break;
        case 6:
            {
                snprintf(str, maxLength, "%d%02d%02d%02d%02d%02d",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday, lt->tm_hour,
                    lt->tm_min, lt->tm_sec);
            }
            break;
        case 7:
            {	//时间：2011-2-11，修改人：王建洪，关联问题单： V100R002C11，ID：1222
                //修改原因：时间格式不符合要求
                snprintf(str, maxLength, "%d%02d%02d",
                    lt->tm_year + 1900,lt->tm_mon + 1, lt->tm_mday);
            }
            break;
        case 8:
            {	//格林威治时间

                struct tm utc_tm;
                struct tm *gmt = gmtime_r(&i_time,&utc_tm);
                snprintf(str, maxLength, "%04d%02d%02d%02d%02d%02d",
                    gmt->tm_year + 1900,gmt->tm_mon + 1,
                    gmt->tm_mday, gmt->tm_hour,
                    gmt->tm_min, gmt->tm_sec);
            }
            break;
        case 9:
            {	//格林威治时间
                struct tm utc_tm;
                struct tm *gmt = gmtime_r(&i_time,&utc_tm);
                snprintf(str, maxLength, "%04d-%02d-%02d %02d:%02d:%02d",
                    gmt->tm_year + 1900,gmt->tm_mon + 1,
                    gmt->tm_mday, gmt->tm_hour,
                    gmt->tm_min, gmt->tm_sec);
            }
            break;
        case 10:
            {
                snprintf(str, maxLength, "%d-%02d-%02d",
                    lt->tm_year + 1900, lt->tm_mon + 1,
                    lt->tm_mday);
            }
            break;
        case 11:
            {
                //格林威治时间
                struct tm utc_tm;
                struct tm *gmt = gmtime_r(&i_time,&utc_tm);
                snprintf(str, maxLength, "%02d:%02d:%02d",
                    gmt->tm_hour, gmt->tm_min, gmt->tm_sec);
            }
            break;


        default:
            break;
        }

        return str;
    }

    

    //format 1:yyyy-mm-dd hh:mi:ss
    //format 2:yyyy/mm/dd hh:mi:ss
    //format 3:yyyymmddhhmiss
    //2008-6-17 王建洪添加，增加对yymmddhhmiss格式的年份支持///////
    //format 4:yymmddhhmiss
    const char* const yearfirst = "20";
    time_t str_to_time(const char * p_time, int n_format)
    {
        //2008-6-17 王建洪添加，增加对yymmddhhmiss格式的年份支持///////
        char firstyear[5] = {0};
        strncpy(firstyear, yearfirst, sizeof(firstyear) - 1);
        //////////////////////////////////////////////////////////////

        struct tm when = {0,0,0,0,0,0,0,0,0};
        const int MAX_TIME_LENGTH = 30;
        char buf[MAX_TIME_LENGTH + 1] = {0};
        char tmp[MAX_TIME_LENGTH + 1] = {0};
        if(p_time == NULL)
            return 0;
        strncpy(buf, p_time, MAX_TIME_LENGTH);
        char *p = NULL;
        char *pm = NULL;
        switch(n_format)
        {
        case 1:
            if (str_to_time_1(p, pm, when, buf, tmp))
                return 0;
            break;
        case 2:
            if (str_to_time_2(p, pm, when, buf, tmp))
                return 0;
            break;
        case 3:
            if (str_to_time_3(p, pm, when, buf, tmp))
                return 0;
            break;
            //2008-6-17 王建洪添加，增加对yymmddhhmiss格式的年份支持///////
        case 4:
            if (str_to_time_4(p, pm, when, buf, tmp, firstyear))
                return 0;
            break;
        default:
            return 0;
        }
        return mktime(&when);
    }
}