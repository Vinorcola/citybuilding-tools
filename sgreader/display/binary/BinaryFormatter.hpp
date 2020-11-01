#ifndef BINARYFORMATTER_HPP
#define BINARYFORMATTER_HPP

#include <QtCore/QString>

/**
 * @brief A helper for formatting binary data for a display purpose.
 */
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
