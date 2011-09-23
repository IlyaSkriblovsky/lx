#include "String.h"

namespace lx
{


StringRep StringRep::m_emptyRep(L"");


String String::number(int n)
{
    wchar_t buffer[20];

#if defined(_WIN32) && !defined(__WINE__)
    _snwprintf(buffer, 20, L"%d", n);
#else
    #if defined(__WINE__)
        swprintf(buffer, L"%d", n);
    #else
        swprintf(buffer, 20, L"%d", n);
    #endif
#endif

    buffer[19] = L'\0';

    return String(buffer);
}


String String::vformat(int bufsize, const wchar_t *format, va_list args)
{
    wchar_t *buffer = new wchar_t[bufsize];

#ifdef _WIN32
    _vsnwprintf
#else
    vswprintf
#endif
        (buffer, bufsize-1, format, args);

    buffer[bufsize-1] = L'\0';

    String ret(buffer);

    delete[] buffer;

    return ret;
}

String String::format(int bufsize, const wchar_t *format, ...)
{
    va_list ap;
    va_start(ap, format);
    String ret = vformat(bufsize, format, ap);
    va_end(ap);

    return ret;
}


}
