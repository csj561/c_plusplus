#define __main__ 1
#include <logger.h>
int main()
{
	LOGGER(EN_ERROR,"this is error logger");
	LOGGER(EN_DEBUG,"this is DEBUG logger");
	return 0;
}
