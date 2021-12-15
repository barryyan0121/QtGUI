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

    void AddROI1_clicked();
    void AddROI2_clicked();
    void AddROI3_clicked();
    void AddROI4_clicked();
    void AddROI5_clicked();
    void AddROI6_clicked();
    void AddROI7_clicked();
    void AddROI8_clicked();

private:
    Ui::MainWindow *ui;
    myLabel *label;
    bool is_add_roi;
    QMap<QString, QRect> rect_map;
    QString current_roi;

    void ROIClickedHelper(QString string);


Q_SIGNALS:
    void sendIsAddROISig(bool is_add_roi);
    void sendRectMapSig(QMap<QString, QRect> rect_map);
    void sendSaveImageSig();
};
#endif // MAINWINDOW_H
