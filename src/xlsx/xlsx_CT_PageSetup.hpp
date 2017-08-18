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
#ifndef QXLSX_CT_PAGE_SETUP_HPP
#define QXLSX_CT_PAGE_SETUP_HPP

#include "xlsxglobal.h"

#include <QString>

class QXmlStreamReader;
class QXmlStreamWriter;

QT_BEGIN_NAMESPACE_XLSX

typedef QString ST_PositiveUniversalMeasure;

enum class ST_Orientation {
    default_,
    portrait,
    landscape
};

ST_Orientation parse(const QString& str);
QString join(ST_Orientation orientation);

// Worksheet page setup
struct CT_PageSetup
{
};

// Chartseet page setup
struct CT_CsPageSetup
{
    // defaults are from the XMLSchema
    unsigned int paperSize{1};
    ST_PositiveUniversalMeasure paperHeight;
    ST_PositiveUniversalMeasure paperWidth;
    unsigned int firstPageNumber{1};
    ST_Orientation orientation{ST_Orientation::default_};
    bool usePrinterDefaults{true};
    bool blackAndWhite{false};
    bool draft{false};
    bool useFirstPageNumber{false};
    unsigned int horizontalDpi{600};
    unsigned int verticalDpi{600};
    unsigned int copies{1};
    QString id;
    bool isEqual(const CT_CsPageSetup& other) const;
};


// Returns true when reading is OK and data was filled
// Returns false when current element is not HeaderFooter (nothing is readed)
// throw exception on error in stream
bool read(QXmlStreamReader& reader, CT_CsPageSetup* pCsPageSetup);

void write(QXmlStreamWriter& writer, const CT_CsPageSetup& pageSetup);


QT_END_NAMESPACE_XLSX

#endif // QXLSX_CT_PAGE_SETUP_HPP
