// customitemdelegate.cpp
#include "customitemdelegate.h"
#include <QPainter>
#include <QColor>

CustomItemDelegate::CustomItemDelegate(QObject *parent): QStyledItemDelegate(parent) {}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString busSequence = index.data(Qt::DisplayRole).toString();
    QString busServiceNo = index.data(Qt::UserRole).toString();
    QString busStopName = index.data(Qt::UserRole+1).toString();
    QString busStopCode = index.data(Qt::UserRole+2).toString();
    QString busDistance = index.data(Qt::UserRole+3).toString();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QPen borderPen(QColor("#00BFFF"), 5);
    painter->setPen(borderPen);

    painter->fillRect(option.rect, "#87CEFA");
    painter->drawRect(option.rect);

    QColor textColor = option.palette.color(QPalette::Text);
    painter->setPen(textColor);

    QFont busSequenceFont = option.font;
    QFont busServiceNoFont = option.font;
    QFont busStopNameFont = option.font;
    QFont busStopCodeFont = option.font;
    QFont busDistanceFont = option.font;

    busSequenceFont.setFamily("Roboto");
    busServiceNoFont.setFamily("Roboto");
    busStopNameFont.setFamily("Roboto");
    busStopCodeFont.setFamily("Roboto");
    busDistanceFont.setFamily("Roboto");

    busSequenceFont.setPointSize(12);
    busServiceNoFont.setPointSize(12);
    busStopNameFont.setPointSize(12);
    busStopCodeFont.setPointSize(12);
    busDistanceFont.setPointSize(12);

    QRect busSequenceRect = option.rect.adjusted(10, 30, 0, 0);
    QRect busServiceNoRect = option.rect.adjusted(10, 100, 0, 0);
    QRect busStopNameRect = option.rect.adjusted(0, 30, -30, 0);
    QRect busStopCodeRect = option.rect.adjusted(0, 100, -30, 0);
    QRect busDistanceRect = option.rect.adjusted(0, 120, -30, 0);

    painter->drawText(busSequenceRect, Qt::AlignLeft | Qt::TextWordWrap, busSequence);
    painter->drawText(busServiceNoRect, Qt::AlignLeft | Qt::TextWordWrap, busServiceNo);
    painter->drawText(busStopNameRect, Qt::AlignRight | Qt::TextWordWrap, busStopName);
    painter->drawText(busStopCodeRect, Qt::AlignRight | Qt::TextWordWrap, busStopCode);
    painter->drawText(busDistanceRect, Qt::AlignRight | Qt::TextWordWrap, busDistance);

    painter->restore();
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(size.height() + 150);
    return size;
}
