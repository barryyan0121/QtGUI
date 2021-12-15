#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QtHeaders.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadImage_clicked();
    void on_SaveImage_clicked();
    void recvRectSig(QRect rect);

    void on_AddROI_clicked();

private:
    Ui::MainWindow *ui;
    myLabel *label;
    bool is_add_roi;
    QList<QRect> rect_list;

Q_SIGNALS:
    void sendIsAddROISig(bool is_add_roi);
};
#endif // MAINWINDOW_H
