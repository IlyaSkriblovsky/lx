#ifndef __LX__EXCEPTION_H
#define __LX__EXCEPTION_H

namespace lx
{

    class Exception
    {
        public:
            Exception(const char *reason);
            ~Exception();

            const char* reason() const;


            static Exception format(const char *reason, ...);

        private:
            char* _reason;
    };

}

#endif
