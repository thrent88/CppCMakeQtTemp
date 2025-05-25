//
// Created by Thrent on 2025/5/25.
//

#ifndef SVGUTILS_H
#define SVGUTILS_H

#include <QFile>
#include <QByteArray>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QSvgRenderer>
#include <QDomElement>
#include <QSize>

namespace utils {

class SvgUtils {
public:
    /**
     * 修改SVG颜色和尺寸
     * @param path
     * @param color
     * @param size
     * @return
     */
    static QIcon setSvgColor(QString path, QString color, QSize size);
};

} // utils

#endif //SVGUTILS_H
