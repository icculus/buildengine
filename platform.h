#ifndef _INCLUDE_PLATFORM_H_
#define _INCLUDE_PLATFORM_H_

#if (defined PLATFORM_WIN32)
#include "win32_compat.h"
#elif (defined PLATFORM_UNIX)
#include "unix_compat.h"
#elif (defined PLATFORM_DOS)
#include "doscmpat.h"
#else
#error Define your platform!
#endif

#endif

// end of platform.h ...


