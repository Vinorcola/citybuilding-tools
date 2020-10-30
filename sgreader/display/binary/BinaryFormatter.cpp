#include "BinaryFormatter.hpp"

#include <QtCore/QDataStream>



QString BinaryFormatter::format(const QString& name, quint32 value)
{
    QByteArray memoryArray;
    QDataStream writer(&memoryArray, QIODevice::WriteOnly);
    writer << value;

    auto binaryContent(QString::fromLatin1(memoryArray.toHex()));
    binaryContent.insert(4, ' ');

    return binaryContent + " (" + QString::number(value) + ") = " + name;
}



QString BinaryFormatter::format(const QString& name, qint32 value)
{
    QByteArray memoryArray;
    QDataStream writer(&memoryArray, QIODevice::WriteOnly);
    writer << value;

    auto binaryContent(QString::fromLatin1(memoryArray.toHex()));
    binaryContent.insert(4, ' ');

    return binaryContent + " (" + QString::number(value) + ") = " + name;
}



QString BinaryFormatter::format(const QString& name, quint16 value)
{
    QByteArray memoryArray;
    QDataStream writer(&memoryArray, QIODevice::WriteOnly);
    writer << value;

    auto binaryContent(QString::fromLatin1(memoryArray.toHex()));

    return binaryContent + "      (" + QString::number(value) + ") = " + name;
}



QString BinaryFormatter::format(const QString& name, qint16 value)
{
    QByteArray memoryArray;
    QDataStream writer(&memoryArray, QIODevice::WriteOnly);
    writer << value;

    auto binaryContent(QString::fromLatin1(memoryArray.toHex()));

    return binaryContent + "      (" + QString::number(value) + ") = " + name;
}



QString BinaryFormatter::format(const QString& name, char value)
{
    QByteArray memoryArray;
    QDataStream writer(&memoryArray, QIODevice::WriteOnly);
    writer << (qint8) value;

    auto binaryContent(QString::fromLatin1(memoryArray.toHex()));

    return binaryContent + "        (" + QString::number(value) + ") = " + name;
}
