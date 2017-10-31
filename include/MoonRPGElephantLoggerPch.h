#pragma once

/*Windows*/
#define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <fstream>
#include <mutex>
#include <atomic>
#include <string>


#ifdef _DEBUG
#   pragma comment(lib, "MoonRPGHelper_d.lib")
#else
#   pragma comment(lib, "MoonRPGHelper.lib")
#endif
