/**
 * @file String.h
 *
 * @brief Simple implementation of general purpose String class
 * with copy-on-write behavior.
 *
 * @author Ilya Skriblovsky
 * @date 2009
 *
 * This file defines LightCore::String class that implements wide character
 * string with set of common operations and copy-on-write behavior.
 *
 * If you define \c STRING_DEBUG when compiling, it will enable many debug
 * prints.
 *
 */

#ifndef __STRING_H
#define __STRING_H

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef STRING_DEBUG
    #include <stdio.h>
#endif

#include <assert.h>

namespace lx
{

/// Internal representation of string contents
/**
 * Every String object contains pointer to StringRep instance. Several String
 * objects may share one StringRep. StringRep contains reference counter and
 * will be deleted automagically when no Strings are referencing it.
 *
 * String class should always be sure that its StringRep isn't shared before
 * changing its contents.
 */
class StringRep
{
    private:
        friend class String;

        /// Static instance containing empty string.
        /**
         * Used for uninitialized String objects
         */
        static StringRep m_emptyRep;

        int m_len; ///< Length of the string
        /// Array of characters. Always contains terminating NULL.
        wchar_t *m_chars;
        /// Reference counter
        mutable int m_refcount;

        /// Points to multi-byte UTF-8 representation of string
        /**
         * String is converted to UTF-8 by utf8() method and this pointer
         * remains valid until any modification of the string.
         *
         * If utf8() method was not called, or any modification was done after
         * call to utf8(), m_utf8 will be NULL.
         */
        mutable char* m_utf8;


        /// Constructor for internal usage
        /**
         * Constructs StringRep that will use existing wchar_t array
         *
         * Created StringRep will own the passed array and will delete it when
         * destroyed itself.
         *
         * \c wstring must be allocated with new wchar_t[]. Never call this
         * function with constant or static string.
         */
        static StringRep* fromExistingString(wchar_t *wstring)
        {
            assert(wstring != NULL);

#ifdef STRING_DEBUG
            printf("StringRep::fromExistingString(%ls) of len %d\n", wstring, wcslen(wstring));
#endif

            StringRep *rep = new StringRep;
            rep->m_refcount = 1;
            rep->m_utf8 = 0;
            rep->m_chars = wstring;
            rep->m_len = wcslen(wstring);

            return rep;
        }

        /// Default constructor
        /**
         * For internal usage only
         *
         * Creates StringRep with no character array. Array should be created
         * manually
         */
        StringRep()
        {
            m_len = 0;
            m_chars = 0;
            m_utf8 = 0;
        }

    public:
        /// Destructor
        /**
         * Destructor is called automatically when reference counter becames
         * zero.
         *
         * Frees m_chars and m_utf8 arrays.
         */
        ~StringRep()
        {
#ifdef STRING_DEBUG
            printf("StringRep::~StringRep()\n");
#endif
            if (m_chars)
                delete[] m_chars;

            if (m_utf8)
                delete[] m_utf8;
        }

        /// Increase reference counter
        /**
         * Use this function every time when you store pointer to StringRep
         * somewhere to be sure that it will not be deleted.
         */
        void incRef() const
        {
#ifdef STRING_DEBUG
            printf("incRef\n");
#endif
            m_refcount++;
        }

        /// Decrease reference counter
        /**
         * Use this function every time when you release a pointer to StringRep
         *
         * If reference counter becames zero after this function, destructor
         * will be called automatically.
         */
        void decRef() const
        {
#ifdef STRING_DEBUG
            printf("decRef\n");
#endif
            m_refcount--;
            if (m_refcount == 0)
            {
#ifdef STRING_DEBUG
                printf("Deleting StringRep of len %d\n", m_len);
#endif
                delete this;
            }
        }

        /// Obtain reference counter value
        /**
         * This method can be used to check if this StringRep instance is
         * shared. If refcount() == 1, this instance is not shared.
         */
        int refcount() const
        { return m_refcount; }

        /// Returns reference to StringRep that stores empty string
        static StringRep* emptyRep()
        { return &m_emptyRep; }

        /// Get length of contained string
        int len() const
        { return m_len; }

        /// Obtain the pointer to string characters
        const wchar_t* const_wchars() const
        { return m_chars; }

        /// Obtain the pointer to string characters
        /**
         * @note This function will reset the UTF-8 representation that
         * previously returned by utf8()
         */
        wchar_t* wchars()
        {
            if (m_utf8)
            {
                delete[] m_utf8;
                m_utf8 = 0;
            }
            return m_chars;
        }


        /// Copy constructor
        /**
         * Allocates new string and copy contents of \c other into it
         */
        explicit StringRep(const StringRep& other)
            : m_utf8(0)
        {
            m_len = other.m_len;
#ifdef STRING_DEBUG
            printf("StringRep(StringRep&) of len %d\n", m_len);
#endif
            m_chars = new wchar_t[m_len + 1];
            memcpy(m_chars, other.m_chars, (m_len + 1) * sizeof(wchar_t));
            m_refcount = 1;
        }

        /// Copy constructor
        /** @copydetails StringRep(const StringRep&) */
        explicit StringRep(const StringRep* other)
            : m_utf8(0)
        {
            m_len = other->m_len;
#ifdef STRING_DEBUG
            printf("StringRep(StringRep*) of len %d\n", m_len);
#endif
            m_chars = new wchar_t[m_len + 1];
            memcpy(m_chars, other->m_chars, (m_len + 1) * sizeof(wchar_t));
            m_refcount = 1;
        }

        StringRep(const wchar_t *wstring)
            : m_utf8(0)
        {
            assert(wstring != 0);

            m_len = wcslen(wstring);
#ifdef STRING_DEBUG
            printf("StringRep(wchar_t) of len %d\n", m_len);
#endif
            m_chars = new wchar_t[m_len+1];
            wcscpy(m_chars, wstring);
            m_refcount = 1;
        }

        StringRep(const wchar_t *wstring, int maxlen)
            : m_utf8(0)
        {
            assert(wstring != 0);

#ifdef STRING_DEBUG
            printf("StringRep(wchar_t, maxlen=%d)\n", maxlen);
#endif

            int strlen = wcslen(wstring);
#ifdef STRING_DEBUG
            printf("strlen = %d\n", strlen);
#endif

            if (strlen > maxlen)
                m_len = maxlen;
            else
                m_len = strlen;

            m_chars = new wchar_t[m_len+1];
            wcsncpy(m_chars, wstring, m_len);
            m_chars[m_len] = L'\0';

            m_refcount = 1;
        }


        StringRep(const char *string)
            : m_utf8(0)
        {
            assert(string != 0);

#ifdef _WIN32
            m_len = MultiByteToWideChar(CP_UTF8, 0, string, -1, 0, 0) - 1;
#ifdef STRING_DEBUG
            printf("StringRep(char) of len %d\n", m_len);
#endif
            m_chars = new wchar_t[m_len + 1];
            MultiByteToWideChar(CP_UTF8, 0, string, -1, m_chars, m_len + 1);
#else
            m_len = mbstowcs(0, string, 0);
#ifdef STRING_DEBUG
            printf("StringRep(char) of len %d\n", m_len);
#endif
            m_chars = new wchar_t[m_len + 1];
            mbstowcs(m_chars, string, m_len + 1);
#endif

            m_refcount = 1;
        }

        const char* utf8() const
        {
            if (m_utf8)
                return m_utf8;

#ifdef _WIN32

            int utf8len = WideCharToMultiByte(CP_UTF8, 0, m_chars, -1, 0, 0, 0, 0);
            m_utf8 = new char[utf8len];
            WideCharToMultiByte(CP_UTF8, 0, m_chars, -1, m_utf8, utf8len, 0, 0);
            m_utf8[utf8len-1] = '\0';

#else

            int utf8len = wcstombs(0, m_chars, 0);
            m_utf8 = new char[utf8len + 1];
            wcstombs(m_utf8, m_chars, utf8len);
            m_utf8[utf8len] = '\0';

#endif

            return m_utf8;
        }
};

class String
{
    private:
        StringRep *rep;

        String(StringRep *rep)
        {
            this->rep = rep;
        }

    public:
        class CharRef
        {
            private:
                friend class String;

                String *string;
                int pos;

                CharRef(String *string, int pos)
                    : string(string), pos(pos)
                {
                }

            public:
                CharRef& operator = (const wchar_t c)
                {
                    string->wchars()[pos] = c;
					return *this;
                }

                operator wchar_t ()
                {
                    return string->const_wchars()[pos];
                }
        };


        ~String()
        { rep->decRef(); }

        String()
        { rep = StringRep::emptyRep(); rep->incRef(); }

        String(const wchar_t *wstring)
        { assert(wstring != 0); rep = new StringRep(wstring); }

        String(const char *string)
        { assert(string != 0); rep = new StringRep(string); }

        String(const String &other)
        { rep = other.rep; rep->incRef(); }

        String(const String *other)
        { rep = other->rep; rep->incRef(); }

        String& operator = (const String &other)
        {
            if (rep != other.rep)
            {
                rep->decRef();
                rep = other.rep;
                rep->incRef();
            }
            return *this;
        }

        int length() const
        {
            return rep->len();
        }

        bool empty() const
        {
            return length() == 0;
        }

        void makeOwn()
        {
            if (rep->refcount() != 1)
            {
                StringRep *newRep = new StringRep(rep);
                rep->decRef();
                rep = newRep;
            }
        }

        const wchar_t* const_wchars() const
        { return rep->const_wchars(); }

        const wchar_t* wchars() const
        { return rep->const_wchars(); }

        wchar_t* wchars()
        { makeOwn(); return rep->wchars(); }


        wchar_t operator [] (int pos) const
        {
            assert(pos >= 0 && pos < rep->len());

            return wchars()[pos];
        }

        CharRef operator [] (int pos) 
        {
            assert(pos >= 0 && pos < rep->len());

            return CharRef(this, pos);
        }

        wchar_t at(int pos) const
        {
            assert(pos >= 0 && pos < rep->len());

            return wchars()[pos];
        }



        //\\//\\//\\// UTF-8 functions //\\//\\//\\//

        const char* utf8() const
        {
            return rep->utf8();
        }



        //\\//\\//\\// Search functions //\\//\\//\\//

        int indexOf(wchar_t ch) const
        {
            const wchar_t *begin = rep->wchars();
            const wchar_t *ptr = wcschr(begin, ch);
            if (ptr == 0)
                return -1;

            return ptr - begin;
        }


        int lastIndexOf(wchar_t ch) const
        {
            const wchar_t *begin = rep->wchars();
            const wchar_t *ptr = wcsrchr(begin, ch);
            if (ptr == 0)
                return -1;

            return ptr - begin;
        }



        //\\//\\//\\// Substring functions //\\//\\//\\//

        String substring(int beginning, int length) const
        {
            assert(beginning >= 0 && beginning < rep->len());
            assert(length > 0);

            StringRep* rep = new StringRep(&(this->rep->wchars()[beginning]), length);
            return String(rep);
        }



        //\\//\\//\\// Formatting functions //\\//\\//\\//

        static String number(int n);

        static String vformat(int bufsize, const wchar_t *format, va_list args);

        static String format(int bufsize, const wchar_t *format, ...);
        

        //\\//\\//\\// Concatenating functions //\\//\\//\\//

        String operator + (const String& other) const
        {
            int newlen = length() + other.length();
            wchar_t *newString = new wchar_t[newlen + 1];
            wcscpy(newString, wchars());
            wcscat(newString, other.wchars());

            return String(StringRep::fromExistingString(newString));
        }

        //\\//\\//\\// Concatenating functions //\\//\\//\\//

        bool operator == (const String& other) const
        {
            if (rep == other.rep)
                return true;

            return wcscmp(rep->const_wchars(), other.rep->const_wchars()) == 0;
        }
};


}

#endif
