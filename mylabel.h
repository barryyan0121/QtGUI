#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

#include "QtHeaders.h"

class myLayout:public QWidget
{
public:
    myLayout(QWidget *parent);
    ~myLayout();
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

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
    void recvSaveRectSig();
    void recvRectMapSig(QMap<QString, QRect> rect_map);
    void recvResetROISig();

private:
    bool m_isDown;
    bool is_add_roi;
    QPoint m_start;
    QPoint m_stop;
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QRect current_rect;
    QMap<QString, QRect> rect_map;

Q_SIGNALS:
    void sendRectSig(QRect rect);


};

#endif // MYLABEL_H
