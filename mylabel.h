#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

#include "QtHeaders.h"


class myLabel:public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent);
    ~myLabel();
    QPixmap m_loadPixmap;
    QPixmap m_capturePixmap;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public slots:
    void recvIsAddROISig(bool is_add_roi);

private:
    bool m_isDown;
    bool is_add_roi;
    QPoint m_start;
    QPoint m_stop;
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QList<QRect> rect_list;

Q_SIGNALS:
    void sendRectSig(QRect rect);


};

#endif // MYLABEL_H
