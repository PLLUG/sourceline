#include "revisiondelegate.h"
#include <QPainter>
#include <QDebug>

RevisionDelegate::RevisionDelegate(QObject * parent) :
    QAbstractItemDelegate(parent),
    OFFSET(20)
{
}

void RevisionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QColor c;
    if ( option.state &QStyle::State_Selected )
    {
        c = QColor(170, 170, 170, 150);
    }
    else
    {
        c = QColor(130, 130, 130, 150);
    }
    QColor main = QColor(30, 130, 210, 255);
    QColor buble = QColor(15, 65, 106, 255);
    painter->fillRect(option.rect, c);
    QMap<QString, QVariant> data = index.model()->data(index, Qt::DisplayRole).toMap();
    if ( data.contains("pos") )
    {
        painter->setPen(main);
        int pos = data.value("pos").toInt() + 1;

        if ( data.contains("children") )
        {
            for (int i =1; i <= data.value("children").toInt(); ++i)
            {
                QPainterPath path;
                path.moveTo(qreal((pos) * OFFSET), qreal(option.rect.center().y()));
                QRectF r(qreal((pos) * OFFSET), qreal(option.rect.center().y()),
                         qreal( i * OFFSET), qreal(option.rect.bottom() - option.rect.center().y()));
                QPointF c1 = QPointF(r.x(), r.center().y());//r.bottomLeft();
                QPointF c2 = QPointF(r.right(), r.center().y());//r.topRight() + QPointF(0, 2);
                path.cubicTo(c1, c2, r.bottomRight());
                painter->drawPath(path);
            }
        }
        for (int i = 1; i < pos; ++i)
        {
            painter->drawLine(QPoint(i * OFFSET, option.rect.y()), QPoint(i * OFFSET, option.rect.bottom()));
        }
        if ( data.contains("last") )
        {
            bool isHead = data.value("last").toBool();
            if ( isHead )
                painter->drawLine(QPoint(pos * OFFSET, option.rect.y()), QPoint(pos * OFFSET, option.rect.center().y()));
            else
                painter->drawLine(QPoint(pos * OFFSET, option.rect.y()), QPoint(pos * OFFSET, option.rect.bottom()));

            painter->drawEllipse(QPoint(pos * OFFSET, option.rect.center().y()), 5, 5);
            painter->setBrush(buble);
            painter->drawEllipse(QPoint(pos * OFFSET, option.rect.center().y()), 3, 3);
        }
        if ( data.contains("branches") )
        {
            for (int i = 0; i < data.value("branches").toInt(); ++i)
            {
                painter->drawLine(QPoint((pos +1 + i) * OFFSET, option.rect.y()), QPoint((pos + 1 + i)* OFFSET, option.rect.bottom()));
            }
        }
    }
    painter->restore();
}

QSize RevisionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(80, 30);
}
