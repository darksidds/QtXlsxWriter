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

#include "xlsx_xml_helper.hpp"

#include "xlsx_xml_exception.hpp"

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

bool
QXlsx::parse_bool(const QString& value)
{
    if (value == QLatin1String("1") || value == QLatin1String("true"))
        return true;
    if (value == QLatin1String("0") || value == QLatin1String("false"))
        return false;
    throw XlsxParseException();
}

// ELEMENTS ===================================================================

void
QXlsx::write_element(QXmlStreamWriter& writer, const QString& element,
                     const QString& value, bool writeEmpty)
{
    if ((!writeEmpty) && value.isEmpty())
        return;
    writer.writeStartElement(element);
    writer.writeCharacters(value);
    writer.writeEndElement(); // element
}

// ATTRIBUTES =================================================================

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  bool value)
{
    writer.writeAttribute(attribute,
                          value ? QLatin1Literal("1") : QLatin1Literal("0"));
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute, int value)
{
    writer.writeAttribute(attribute, QString::number(value));
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  unsigned int value)
{
    writer.writeAttribute(attribute, QString::number(value));
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  const QString& value)
{
    writer.writeAttribute(attribute, value);
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  bool value, bool defaultValue)
{
    if (value == defaultValue)
        return;
    write_attr(writer, attribute, value);
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute, int value,
                  int defaultValue)
{
    if (value == defaultValue)
        return;
    write_attr(writer, attribute, value);
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  unsigned int value, unsigned int defaultValue)
{
    if (value == defaultValue)
        return;
    write_attr(writer, attribute, value);
}

void
QXlsx::write_attr(QXmlStreamWriter& writer, const QString& attribute,
                  const QString& value, const QString& defaultValue)
{
    if (value == defaultValue)
        return;
    write_attr(writer, attribute, value);
}

bool
QXlsx::read_attr_bool(QXmlStreamReader& reader, const QString& attribute)
{
    if (reader.attributes().hasAttribute(attribute))
        return parse_bool(reader.attributes().value(attribute).toString());

    throw XlsxParseException();
}

int
QXlsx::read_attr_int(QXmlStreamReader& reader, const QString& attribute)
{
    if (reader.attributes().hasAttribute(attribute))
    {
        bool isOk;
        int res = reader.attributes().value(attribute).toInt(&isOk);
        if (isOk)
            return res;
    }
    throw XlsxParseException();
}

unsigned int
QXlsx::read_attr_unsigned(QXmlStreamReader& reader, const QString& attribute)
{
    if (reader.attributes().hasAttribute(attribute))
    {
        bool isOk;
        unsigned int res = reader.attributes().value(attribute).toUInt(&isOk);
        if (isOk)
            return res;
    }
    throw XlsxParseException();
}

QString
QXlsx::read_attr_string(QXmlStreamReader& reader, const QString& attribute)
{
    if (reader.attributes().hasAttribute(attribute))
        return reader.attributes().value(attribute).toString();

    throw XlsxParseException();
}

// Read optional attribute
bool
QXlsx::read_attr_bool(QXmlStreamReader& reader, const QString& attribute,
                      bool defaultValue)
{
    if (reader.attributes().hasAttribute(attribute))
        return parse_bool(reader.attributes().value(attribute).toString());
    else
        return defaultValue;
}

int
QXlsx::read_attr_int(QXmlStreamReader& reader, const QString& attribute,
              int defaultValue)
{
    if (reader.attributes().hasAttribute(attribute))
    {
        bool isOk;
        int res = reader.attributes().value(attribute).toInt(&isOk);
        if (isOk)
            return res;
        else
            throw XlsxParseException();
    }
    return defaultValue;
}

unsigned int
QXlsx::read_attr_unsigned(QXmlStreamReader& reader, const QString& attribute,
                   unsigned int defaultValue)
{
    if (reader.attributes().hasAttribute(attribute))
    {
        bool isOk;
        unsigned int res = reader.attributes().value(attribute).toUInt(&isOk);
        if (isOk)
            return res;
        else
            throw XlsxParseException();
    }
    return defaultValue;
}

QString
QXlsx::read_attr_string(QXmlStreamReader& reader, const QString& attribute,
                 const QString& defaultValue)
{
    if (reader.attributes().hasAttribute(attribute))
        return reader.attributes().value(attribute).toString();
    else
        return defaultValue;
}
