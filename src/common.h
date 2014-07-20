#ifndef _COMMON_H_
#define _COMMON_H_

#if defined _WIN32
	#define iexp __declspec(dllexport) 
#else
# 	define iexp
#endif

#endif