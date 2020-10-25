#ifndef FILEEXCEPTION_HPP
#define FILEEXCEPTION_HPP

#include "RuntimeException.hpp"

class FileException : public RuntimeException
{
    public:
        FileException(const QString& message);
};

#endif // FILEEXCEPTION_HPP
