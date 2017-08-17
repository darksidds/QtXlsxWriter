/****************************************************************************
** Copyright (c) 2017 Roman Bulygin <rbulygin@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef QXLSX_XML_HELPER_HPP
#define QXLSX_XML_HELPER_HPP

#include "xlsxglobal.h"

class QXmlStreamReader;
class QXmlStreamWriter;
class QString;

QT_BEGIN_NAMESPACE_XLSX

// Number of helper function to read and write data form xml

// Throw exception on error
bool parse_bool(const QString& value);

// ELEMENTS

// writeEmpty = true requiers to write element even it has no value
void write_element(QXmlStreamWriter& writer, const QString& element,
                   const QString& value, bool writeEmpty = false);

// ATTRIBUTES

// write attribute
void write_attr(QXmlStreamWriter& writer, const QString& attribute, bool value);
void write_attr(QXmlStreamWriter& writer, const QString& attribute, int value);
void write_attr(QXmlStreamWriter& writer, const QString& attribute,
                unsigned int value);
void write_attr(QXmlStreamWriter& writer, const QString& attribute,
                const QString& value);

// write optional attribute
void write_attr(QXmlStreamWriter& writer, const QString& attribute, bool value,
                bool defaultValue);
void write_attr(QXmlStreamWriter& writer, const QString& attribute, int value,
                int defaultValue);
void write_attr(QXmlStreamWriter& writer, const QString& attribute,
                unsigned int value, unsigned int defaultValue);
void write_attr(QXmlStreamWriter& writer, const QString& attribute,
                const QString& value, const QString& defaultValue);

// Read necessary attribute
// throw exception if not found
bool read_attr_bool(QXmlStreamReader& reader, const QString& attribute);
int read_attr_int(QXmlStreamReader& reader, const QString& attribute);
unsigned int read_attr_unsigned(QXmlStreamReader& reader,
                                const QString& attribute);
QString read_attr_string(QXmlStreamReader& reader, const QString& attribute);

// Read optional attribute
bool read_attr_bool(QXmlStreamReader& reader, const QString& attribute,
                    bool defaultValue);
int read_attr_int(QXmlStreamReader& reader, const QString& attribute,
                  int defaultValue);
unsigned int read_attr_unsigned(QXmlStreamReader& reader,
                                const QString& attribute,
                                unsigned int defaultValue);
QString read_attr_string(QXmlStreamReader& reader, const QString& attribute,
                         const QString& defaultValue);

QT_END_NAMESPACE_XLSX

#endif // QXLSX_XML_HELPER_HPP
