#pragma once

#include <iostream>

#ifdef DEBUG
#define DebugLog(x) std::cerr << x << std::endl;
#else
#define DebugLog(x)
#endif

#ifdef DEBUG
#define CondDebugLog(b, x)           \
    if (b) {                         \
        std::cout << x << std::endl; \
    }
#else
#define CondDebugLog(b, x)
#endif
