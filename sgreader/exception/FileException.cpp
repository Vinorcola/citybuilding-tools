#include "FileException.hpp"



FileException::FileException(const QString& message) :
    RuntimeException(message)
{

}
