#include "mylabel.h"

myLayout::myLayout(QWidget *parent)
{

}

myLayout::~myLayout()
{

}

myLabel::myLabel(QWidget *parent):QLabel(parent),
    m_start(QPoint(-1, -1)), m_stop(QPoint(-1, -1))
{
    this->is_add_roi = false;
    setMouseTracking(true);
}

myLabel::~myLabel()
{

}

void myLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton && is_add_roi)
    {
        m_isDown = true;
        m_start = e->pos();
        m_stop = e->pos();
    }
    update();
}

void myLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isDown && is_add_roi)
    {
        m_stop = e->pos();
    }
    update();
    emit sendMouseMoveSig(e);
}

void myLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton && is_add_roi)
    {
        m_isDown = false;
        current_rect = getRect(m_start, m_stop);
    }
}

void myLabel::paintEvent(QPaintEvent * event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));
    painter.drawRect(QRect(m_start, m_stop));
    for (QRect rect: rect_map.values())
    {
        painter.drawRect(rect);
    }
}

cv::Mat myLabel::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cv::cvtColor(tmp, result, cv::COLOR_BGR2RGB);
     return result;
}

void myLabel::recvIsAddROISig(bool is_add_roi)
{
    this->is_add_roi = is_add_roi;
}

void myLabel::recvSaveRectSig()
{
    emit sendRectSig(this->current_rect);
    m_start = QPoint(-1, -1);
    m_stop = QPoint(-1, -1);
    update();
}

void myLabel::recvRectMapSig(QMap<QString, QRect> rect_map)
{
    this->rect_map = rect_map;
    update();
    QMessageBox::warning(this,tr("Information"), tr("Successfully Saved ROI"));
}

void myLabel::recvResetROISig()
{
    m_start = QPoint(-1, -1);
    m_stop = QPoint(-1, -1);
    update();
}

QRect myLabel::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);

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
