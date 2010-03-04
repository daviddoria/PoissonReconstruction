#ifndef __MEMORY_USAGE__
#define __MEMORY_USAGE__

#ifdef WIN32
  #include "MemoryUsageWin32.h"
#else
  #ifdef __APPLE 
    #include "MemoryUsageApple.h"
  #else 
    #include "MemoryUsageUnix.h"
  #endif
#endif

#endif

