#ifndef CLASS_OSERROR
#define CLASS_OSERROR
#define BUF_LEN 256
#include <typeinfo>

class OSError : public std::exception {
private:
    char msg_error[BUF_LEN];
public:
    explicit OSError(const char* fmt,...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~OSError() noexcept {}
};


#endif
