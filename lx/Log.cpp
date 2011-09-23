#include "Log.h"

#include <cstdio>

using namespace lx;


void Log::log(const char *msg)
{
    printf("LX >>> %s\n", msg);
}
