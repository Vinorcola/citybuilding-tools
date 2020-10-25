#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include <QtCore/QException>

class RuntimeException : public QException
{
    private:
        const QString message;
        const std::string standardFormatMessage;

    public:
        RuntimeException(const QString& message);

        const QString& getMessage() const;

        virtual void raise() const override;
        virtual RuntimeException* clone() const override;
        virtual const char* what() const noexcept override;
};

#endif // RUNTIMEEXCEPTION_HPP
