/****************************************************************************
** Copyright (c) 2016 Golubchikov Mihail <https://github.com/rue-ryuzaki>
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

#ifndef QXLSX_MARKER_P_H
#define QXLSX_MARKER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Xlsx API.  It exists for the convenience
// of the Qt Xlsx.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include "xlsxmarker.h"
#include "xlsxcolor_p.h"

#include <QSharedPointer>

class QXmlStreamReader;
class QXmlStreamWriter;

namespace QXlsx {
class ChartLine
{
public:
    ChartLine() : enable(false) { }

    void setColor(QColor color) {
        enable = true;
        xcolor = XlsxColor(color);
    }
    XlsxColor getColor() const { return xcolor; }
    bool isEnable() { return enable; }

private:
    XlsxColor xcolor;
    bool      enable;
};

class MarkerPrivate
{
    Q_DECLARE_PUBLIC(Marker)

public:
    MarkerPrivate(Marker *p);
    MarkerPrivate(const MarkerPrivate * const mp);
    ~MarkerPrivate();

    ChartLine line;
    Marker *q_ptr;
};

} // namespace QXlsx

#endif // QXLSX_MARKER_P_H
