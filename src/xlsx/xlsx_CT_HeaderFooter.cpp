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
#include "xlsx_CT_HeaderFooter.hpp"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "xlsx_xml_helper.hpp"

bool
QXlsx::CT_HeaderFooter::isEqual(const CT_HeaderFooter& other) const
{
    return (alignWithMargins == other.alignWithMargins)
           && (differentFirst == other.differentFirst)
           && (differentOddEven == other.differentOddEven)
           && (scaleWithDoc == other.scaleWithDoc)
           && (firstHeader == other.firstHeader)
           && (firstFooter == other.firstFooter)
           && (oddHeader == other.oddHeader) && (oddFooter == other.oddFooter)
           && (evenHeader == other.evenHeader)
           && (evenFooter == other.evenFooter);
}

bool
QXlsx::read(QXmlStreamReader& reader, CT_HeaderFooter* pHeaderFooter)
{
    if (reader.name() != QLatin1String("headerFooter"))
        return false;

    CT_HeaderFooter headerFooter;

    headerFooter.differentOddEven
        = read_attr_bool(reader,
                         QLatin1String("differentOddEven"),
                         headerFooter.differentOddEven);
    headerFooter.differentFirst = read_attr_bool(
        reader, QLatin1String("differentFirst"), headerFooter.differentFirst);
    headerFooter.scaleWithDoc = read_attr_bool(
        reader, QLatin1String("scaleWithDoc"), headerFooter.scaleWithDoc);
    headerFooter.alignWithMargins
        = read_attr_bool(reader,
                         QLatin1String("alignWithMargins"),
                         headerFooter.alignWithMargins);

    while (!reader.atEnd()
           && !(reader.name() == QLatin1String("headerFooter")
                && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();
        if (reader.tokenType() != QXmlStreamReader::StartElement)
            continue;
        if (reader.name() == QLatin1String("firstHeader"))
            headerFooter.firstHeader = reader.readElementText();
        else if (reader.name() == QLatin1String("firstFooter"))
            headerFooter.firstFooter = reader.readElementText();
        else if (reader.name() == QLatin1String("oddHeader"))
            headerFooter.oddHeader = reader.readElementText();
        else if (reader.name() == QLatin1String("oddFooter"))
            headerFooter.oddFooter = reader.readElementText();
        else if (reader.name() == QLatin1String("evenHeader"))
            headerFooter.evenHeader = reader.readElementText();
        else if (reader.tokenType() == QXmlStreamReader::StartElement
                 && reader.name() == QLatin1String("evenFooter"))
            headerFooter.evenFooter = reader.readElementText();
    }

    if (pHeaderFooter)
        *pHeaderFooter = headerFooter;
    return true;
}

void
QXlsx::write(QXmlStreamWriter& writer, const CT_HeaderFooter& headerFooter)
{
    CT_HeaderFooter defaultValues;
    // Check if no necessary to write
    if (headerFooter.isEqual(defaultValues))
        return;

    writer.writeStartElement(QLatin1Literal("headerFooter"));

    write_attr(writer,
               QLatin1Literal("alignWithMargins"),
               headerFooter.alignWithMargins,
               defaultValues.alignWithMargins);
    write_attr(writer,
               QLatin1Literal("differentFirst"),
               headerFooter.differentFirst,
               defaultValues.differentFirst);
    write_attr(writer,
               QLatin1Literal("differentOddEven"),
               headerFooter.differentOddEven,
               defaultValues.differentOddEven);
    write_attr(writer,
               QLatin1Literal("scaleWithDoc"),
               headerFooter.scaleWithDoc,
               defaultValues.scaleWithDoc);

    if (headerFooter.differentFirst)
    {
        write_element(
            writer, QLatin1Literal("firstHeader"), headerFooter.firstHeader);
        write_element(
            writer, QLatin1Literal("firstFooter"), headerFooter.firstFooter);
    }
    write_element(writer, QLatin1Literal("oddHeader"), headerFooter.oddHeader);
    write_element(writer, QLatin1Literal("oddFooter"), headerFooter.oddFooter);

    if (headerFooter.differentOddEven)
    {
        write_element(
            writer, QLatin1Literal("evenHeader"), headerFooter.evenHeader);
        write_element(
            writer, QLatin1Literal("evenFooter"), headerFooter.evenFooter);
    }
    writer.writeEndElement(); // headerFooter
}
