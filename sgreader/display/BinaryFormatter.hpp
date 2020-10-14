#ifndef BINARYFORMATTER_HPP
#define BINARYFORMATTER_HPP

#include <QtCore/QString>

class BinaryFormatter
{
    public:
        static QString format(const QString& name, quint32 value);
        static QString format(const QString& name, qint32 value);
        static QString format(const QString& name, quint16 value);
        static QString format(const QString& name, qint16 value);
        static QString format(const QString& name, char value);
};

#endif // BINARYFORMATTER_HPP
