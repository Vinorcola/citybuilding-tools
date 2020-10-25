#ifndef OUTOFRANGEEXCEPTION_HPP
#define OUTOFRANGEEXCEPTION_HPP

#include "RuntimeException.hpp"

class OutOfRangeException : public RuntimeException
{
    public:
        OutOfRangeException(const QString& message);
};

#endif // OUTOFRANGEEXCEPTION_HPP
