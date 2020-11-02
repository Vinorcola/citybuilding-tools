#ifndef EXPORTEXCEPTION_HPP
#define EXPORTEXCEPTION_HPP

#include "RuntimeException.hpp"

class ExportException : public RuntimeException
{
    public:
        ExportException(const QString& message);
};

#endif // EXPORTEXCEPTION_HPP
