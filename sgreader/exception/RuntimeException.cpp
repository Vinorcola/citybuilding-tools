#include "RuntimeException.hpp"



RuntimeException::RuntimeException(const QString& message) :
    QException(),
    message(message),
    standardFormatMessage(message.toStdString())
{

}



const QString& RuntimeException::getMessage() const
{
    return message;
}



void RuntimeException::raise() const
{
    throw *this;
}



RuntimeException* RuntimeException::clone() const
{
    return new RuntimeException(*this);
}



const char* RuntimeException::what() const noexcept
{
    return standardFormatMessage.c_str();
}
