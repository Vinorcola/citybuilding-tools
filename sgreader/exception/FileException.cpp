#include "FileException.hpp"



FileException::FileException(const QString& message) :
    QException(),
    message(message),
    rawMessage(message.toStdString().c_str())
{

}



const QString& FileException::getMessage() const
{
    return message;
}



void FileException::raise() const
{
    throw *this;
}



FileException* FileException::clone() const
{
    return new FileException(*this);
}



const char* FileException::what() const noexcept
{
    return rawMessage;
}
