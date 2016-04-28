/****************************************************************************
** Copyright (c) 2013-2014 Debao Zhang <hello@debao.me>
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

#ifndef QXLSX_CHART_H
#define QXLSX_CHART_H

#include "xlsxabstractooxmlfile.h"

#include <QSharedPointer>

class QXmlStreamReader;
class QXmlStreamWriter;

QT_BEGIN_NAMESPACE_XLSX

class AbstractSheet;
class Worksheet;
class ChartPrivate;
class CellRange;
class DrawingAnchor;

class Marker
{
public:
    enum MarkerType {
        MT_Automatic,
        MT_None,
        MT_Square,
        MT_Diamond,
        MT_Triangle,
        MT_X,
        MT_Star,
        MT_Short_dash,
        MT_Long_dash,
        MT_Circle,
        MT_Plus
    };
    Marker(MarkerType type = MT_Automatic, unsigned size = 20) : type(type), size(size) { }

    void setMarkerType(MarkerType type) { this->type = type; }
    void setMarkerSize(unsigned size)   { this->size = size; }
    MarkerType markerType() const { return type; }
    QString    getType() {
        QString res = QString("none");
        switch (type) {
        case MT_Automatic:
            res = QString("automatic");
            break;
        case MT_None:
            res = QString("none");
            break;
        case MT_Square:
            res = QString("square");
            break;
        case MT_Diamond:
            res = QString("diamond");
            break;
        case MT_Triangle:
            res = QString("triangle");
            break;
        case MT_X:
            res = QString("x");
            break;
        case MT_Star:
            res = QString("star");
            break;
        case MT_Short_dash:
            res = QString("short_dash");
            break;
        case MT_Long_dash:
            res = QString("long_dash");
            break;
        case MT_Circle:
            res = QString("circle");
            break;
        case MT_Plus:
            res = QString("plus");
            break;
        default:
            res = QString("none");
            break;
        }
        return res;
    }

    unsigned   markerSize() const { return size; }

private:
    MarkerType type;
    unsigned size;
    /* border
    fill
    pattern
    gradient*/
};

class Q_XLSX_EXPORT Chart : public AbstractOOXmlFile
{
    Q_DECLARE_PRIVATE(Chart)

public:
    enum ChartType {
        CT_Area = 1, //Zero is internally used for unknown types
        CT_Area3D,
        CT_Line,
        CT_Line3D,
        CT_Stock,
        CT_Radar,
        CT_Scatter,
        CT_Pie,
        CT_Pie3D,
        CT_Doughnut,
        CT_Bar,
        CT_Bar3D,
        CT_OfPie,
        CT_Surface,
        CT_Surface3D,
        CT_Bubble
    };

    ~Chart();

    void addSeries(const CellRange &range, AbstractSheet *sheet=0);
    void setChartType(ChartType type);
    void setChartStyle(int id);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    friend class AbstractSheet;
    friend class Worksheet;
    friend class Chartsheet;
    friend class DrawingAnchor;

    Chart(AbstractSheet *parent, CreateFlag flag);
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_CHART_H

