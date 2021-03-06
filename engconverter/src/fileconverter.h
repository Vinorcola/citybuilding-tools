/*
 * Citybuilding tools: a set of utilities to work with the game files
 * Copyright (c) 2017  Bianca van Schaik <bvschaik@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include "logger.h"

#include <QFile>

class FileConverter
{
public:
    
    bool convertEngToXml(QFile &inputFile, QFile &outputFile, const QString &encoding, Logger &logger);
    
    bool convertXmlToEng(QFile &inputFile, QFile &outputFile, const QString &encoding, Logger &logger);

private:
    enum FileType {
        TYPE_MESSAGE,
        TYPE_TEXT,
        TYPE_UNKNOWN
    };

    FileType determineEngFileType(QFile &file, Logger &logger);
    FileType determineXmlFileType(QFile &file, Logger &logger);
};

#endif // FILECONVERTER_H
