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
#include "xlsx_CT_PageSetup.hpp"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "xlsx_xml_exception.hpp"
#include "xlsx_xml_helper.hpp"

QXlsx::ST_Orientation
QXlsx::parse(const QString& str)
{
    if (str == QLatin1Literal("landscape"))
        return ST_Orientation::landscape;
    if (str == QLatin1Literal("portrait"))
        return ST_Orientation::portrait;
    if (str == QLatin1Literal("default"))
        return ST_Orientation::default_;
    throw XlsxParseException();
}

QString
QXlsx::join(ST_Orientation orientation)
{
    switch (orientation)
    {
    case ST_Orientation::portrait:
        return QLatin1Literal("portrait");
    case ST_Orientation::landscape:
        return QLatin1Literal("landscape");
    default:
        return QLatin1Literal("default");
    }
}

bool
QXlsx::CT_CsPageSetup::isEqual(const CT_CsPageSetup& other) const
{
    return (paperSize == other.paperSize) && (paperHeight == other.paperHeight)
           && (paperWidth == other.paperWidth)
           && (firstPageNumber == other.firstPageNumber)
           && (orientation == other.orientation)
           && (usePrinterDefaults == other.usePrinterDefaults)
           && (blackAndWhite == other.blackAndWhite) && (draft == other.draft)
           && (useFirstPageNumber == other.useFirstPageNumber)
           && (horizontalDpi == other.horizontalDpi)
           && (verticalDpi == other.verticalDpi) && (copies == other.copies)
           && (id == other.id);
}

bool
QXlsx::read(QXmlStreamReader& reader, CT_CsPageSetup* pPageSetup)
{
    if (reader.name() != QLatin1String("headerFooter"))
        return false;

    CT_CsPageSetup pageSetup;

    pageSetup.paperSize
        = read_attr_unsigned(reader, "paperSize", pageSetup.paperSize);
    pageSetup.paperHeight
        = read_attr_string(reader, "paperHeight", pageSetup.paperHeight);
    pageSetup.paperWidth
        = read_attr_string(reader, "paperWidth", pageSetup.paperWidth);
    pageSetup.firstPageNumber = read_attr_unsigned(
        reader, "firstPageNumber", pageSetup.firstPageNumber);
    pageSetup.orientation = parse(
        read_attr_string(reader, "orientation", join(pageSetup.orientation)));

    // NOTE: if usePrinterDefaults attribute is "false" Microsoft Office 2010
    // doesn't
    // read the whole element "pageSetup", that's why we do NOT parse
    // this attribute and always write "true"
    pageSetup.usePrinterDefaults = true;
    //    = read_attr_bool(reader, "usePrinterDefaults",
    //    pageSetup.usePrinterDefaults);

    pageSetup.blackAndWhite
        = read_attr_bool(reader, "blackAndWhite", pageSetup.blackAndWhite);
    pageSetup.draft = read_attr_bool(reader, "draft", pageSetup.draft);
    pageSetup.useFirstPageNumber = read_attr_bool(
        reader, "useFirstPageNumber", pageSetup.useFirstPageNumber);
    pageSetup.horizontalDpi
        = read_attr_unsigned(reader, "horizontalDpi", pageSetup.horizontalDpi);
    pageSetup.verticalDpi
        = read_attr_unsigned(reader, "verticalDpi", pageSetup.verticalDpi);
    pageSetup.copies = read_attr_unsigned(reader, "copies", pageSetup.copies);
    pageSetup.id     = read_attr_string(reader, "r:id", pageSetup.id);

    if (pPageSetup)
        *pPageSetup = pageSetup;
    return true;
}

void
QXlsx::write(QXmlStreamWriter& writer, const CT_CsPageSetup& pageSetup)
{
    CT_CsPageSetup defaultValues;
    if (pageSetup.isEqual(defaultValues))
        return;
    writer.writeStartElement(QStringLiteral("pageSetup"));

    write_attr(writer,
               QLatin1Literal("paperSize"),
               pageSetup.paperSize,
               defaultValues.paperSize);
    write_attr(writer,
               QLatin1Literal("paperWidth"),
               pageSetup.paperWidth,
               defaultValues.paperWidth);
    write_attr(writer,
               QLatin1Literal("paperHeight"),
               pageSetup.paperHeight,
               defaultValues.paperHeight);
    write_attr(writer,
               QLatin1Literal("firstpageNumber"),
               pageSetup.firstPageNumber,
               defaultValues.firstPageNumber);
    write_attr(writer,
               QLatin1Literal("orientation"),
               join(pageSetup.orientation),
               join(defaultValues.orientation));
    write_attr(writer,
               QLatin1Literal("usePrinterDefaults"),
               pageSetup.usePrinterDefaults,
               defaultValues.usePrinterDefaults);
    write_attr(writer,
               QLatin1Literal("usePrinterDefaults"),
               pageSetup.usePrinterDefaults); // Write anyway
    write_attr(writer,
               QLatin1Literal("blackAndWhite"),
               pageSetup.blackAndWhite,
               defaultValues.blackAndWhite);
    write_attr(
        writer, QLatin1Literal("draft"), pageSetup.draft, defaultValues.draft);
    write_attr(writer,
               QLatin1Literal("useFirstPageNumber"),
               pageSetup.useFirstPageNumber,
               defaultValues.useFirstPageNumber);
    write_attr(writer,
               QLatin1Literal("horizontalDpi"),
               pageSetup.horizontalDpi,
               defaultValues.horizontalDpi);
    write_attr(writer,
               QLatin1Literal("verticalDpi"),
               pageSetup.verticalDpi,
               defaultValues.verticalDpi);
    write_attr(writer, QLatin1Literal("r:id"), pageSetup.id, defaultValues.id);

    writer.writeEndElement(); // pageSetup
}
