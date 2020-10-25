#ifndef FILEEXCEPTION_HPP
#define FILEEXCEPTION_HPP

#include <QtCore/QException>

class FileException : public QException
{
    private:
        QString message;
        const char* rawMessage;

    public:
        FileException(const QString& message);

        const QString& getMessage() const;

        virtual void raise() const override;
        virtual FileException* clone() const override;
        virtual const char* what() const noexcept override;
};

#endif // FILEEXCEPTION_HPP
