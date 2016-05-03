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

#include "xlsxmarker_p.h"

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

QT_BEGIN_NAMESPACE_XLSX

MarkerPrivate::MarkerPrivate(Marker *p) :
    q_ptr(p)
{

}

MarkerPrivate::MarkerPrivate(const MarkerPrivate * const mp) :
    line(mp->line)
{

}

MarkerPrivate::~MarkerPrivate()
{
    
}

/*!
 * \class Marker
 * \inmodule QtXlsx
 * \brief Main class for the markers.
 */

/*!
  \enum Marker::MarkerType

  \value MT_Auto
  \value MT_Circle,
  \value MT_Dash,
  \value MT_Diamond,
  \value MT_Dot,
  \value MT_None,
  \value MT_Plus,
  \value MT_Square,
  \value MT_Star,
  \value MT_Triangle,
  \value MT_X
*/

/*!
 * \internal
 */
Marker::Marker(MarkerType type, unsigned size)
    : d_ptr(new MarkerPrivate(this)), symbol(type), size(size)
{
    
}

/*!
 * Destroys the marker.
 */
Marker::~Marker()
{
    
}

QString Marker::getType() {
    switch (symbol) {
        case MT_Auto:
            return QLatin1String("auto");
        case MT_Circle:
            return QLatin1String("circle");
        case MT_Dash:
            return QLatin1String("dash");
        case MT_Diamond:
            return QLatin1String("diamond");
        case MT_Dot:
            return QLatin1String("dot");
        case MT_None:
            return QLatin1String("none");
        case MT_Plus:
            return QLatin1String("plus");
        case MT_Square:
            return QLatin1String("square");
        case MT_Star:
            return QLatin1String("star");
        case MT_Triangle:
            return QLatin1String("triangle");
        case MT_X:
            return QLatin1String("x");
        default:
            return QLatin1String("auto");
    }
}

void Marker::setLineColor(const QColor& color) {
    Q_D(Marker);
    d->line.setColor(color);
}

void Marker::writeLineColorToXml(QXmlStreamWriter &writer)
{
    Q_D(Marker);
    if (d->line.isEnable()) {
        writer.writeStartElement(QStringLiteral("c:spPr"));
        writer.writeStartElement(QStringLiteral("a:ln"));
        writer.writeStartElement(QStringLiteral("a:solidFill"));
        writer.writeStartElement(QStringLiteral("a:srgbClr"));
        writer.writeAttribute(QStringLiteral("val"),
                              XlsxColor::toARGBString(d->line.getColor().rgbColor())); // write color
        writer.writeEndElement();//a:srgbClr
        writer.writeEndElement();//a:solidFill
        writer.writeEndElement();//a:ln
        writer.writeEndElement();//c:spPr
    }
}

QT_END_NAMESPACE_XLSX
