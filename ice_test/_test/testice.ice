#ifndef _H_TEST_WG_ICE_H_
#define _H_TEST_WG_ICE_H_
module WG
{
	        interface WGTestIce
			        {
					                int ping();
							                int GetTime(out string strTime);
									        };
};
#endif
