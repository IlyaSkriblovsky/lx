#include "Exception.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>


namespace lx
{


Exception::Exception(const char *reason)
{
    _reason = strdup(reason);
    printf("LX EXCEPTION >>> %s\n", _reason);
}

Exception::~Exception()
{
    free(_reason);
}

const char* Exception::reason() const
{
    return _reason;
}


Exception Exception::format(const char *reason, ...)
{
    va_list args;
    va_start(args, reason);

    char buffer[255];
    vsnprintf(buffer, sizeof(buffer), reason, args);

    va_end(args);

    return Exception(buffer);
}



}
