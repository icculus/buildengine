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

#if (!defined __EXPORT__)
#define __EXPORT__
#endif

#if ((defined PLATFORM_SUPPORTS_SDL) && (!defined PLATFORM_TIMER_HZ))
#define PLATFORM_TIMER_HZ 100
#endif

#if (!defined PLATFORM_TIMER_HZ)
#error You need to define PLATFORM_TIMER_HZ for your platform.
#endif

#if (defined __WATCOMC__)
#define snprintf _snprintf
#endif

#endif  /* !defined _INCLUDE_PLATFORM_H_ */

/* end of platform.h ... */


