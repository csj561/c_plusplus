#include "timer.hpp"
#include <unistd.h>
int main()
{
	fool::timer t("main timer");
	sleep(1);
}
