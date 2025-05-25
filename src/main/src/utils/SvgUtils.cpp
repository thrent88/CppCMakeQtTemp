//
// Created by Thrent on 2025/5/25.
//

#include "utils/SvgUtils.h"

namespace utils {
    void SetAttrRecur(QDomElement &elem, QString strtagname, QString strattr, QString strattrval) {
        // if it has the tagname then overwritte desired attribute
        if (elem.tagName().compare(strtagname) == 0) {
            elem.setAttribute(strattr, strattrval);
        }
        // loop all children
        for (int i = 0; i < elem.childNodes().count(); i++) {
            if (!elem.childNodes().at(i).isElement()) {
                continue;
            }
            QDomElement t = elem.childNodes().at(i).toElement();
            SetAttrRecur(t, strtagname, strattr, strattrval);
        }
    }

    QIcon SvgUtils::setSvgColor(QString path, QString color, QSize size) {
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray baData = file.readAll();

        QDomDocument doc;
        doc.setContent(baData);
        QDomElement elem = doc.documentElement(); // const 和 值传递
        SetAttrRecur(elem, "path", "fill", color);

        QSvgRenderer svgRenderer(doc.toByteArray());
        // create pixmap target (could be a QImage)
        // QPixmap pix(svgRenderer.defaultSize());
        QPixmap pix(svgRenderer.defaultSize().scaled(size.width(), size.height(), Qt::KeepAspectRatio));
        // fix: 修改 svg 颜色后略有模糊
        pix.fill(Qt::transparent);
        // create painter to act over pixmap
        QPainter pixPainter(&pix);
        // use renderer to render over painter which paints on pixmap
        svgRenderer.render(&pixPainter);
        QIcon myicon(pix);
        return myicon;
    }
} // utils
