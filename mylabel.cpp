#include "mylabel.h"

myLabel::myLabel(QWidget *parent):QLabel(parent),
    m_start(QPoint(-1, -1)), m_stop(QPoint(-1, -1))
{
    this->is_add_roi = false;
}

myLabel::~myLabel()
{

}

void myLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton && is_add_roi){
        m_isDown = true;
        m_start = e->pos();
        m_stop = e->pos();
    }
}

void myLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isDown && is_add_roi){
        m_stop = e->pos();
    }
    update();
}

void myLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton && is_add_roi){
        m_isDown = false;
        QRect selectedRect = getRect(m_start, m_stop);
        emit sendRectSig(selectedRect);
    }
}

void myLabel::paintEvent(QPaintEvent * event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));
    if(!m_isDown){
        return;
    }
    painter.drawRect(QRect(m_start, m_stop));


}

void myLabel::recvIsAddROISig(bool is_add_roi)
{
    this->is_add_roi = is_add_roi;
}

QRect myLabel::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }
    return selectedRect;
}
