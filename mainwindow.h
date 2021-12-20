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

    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:

    // customized slot function
    void recvRectSig(QRect rect);
    void recvMouseMoveSig(QMouseEvent *e);
    void AddROI1_clicked();
    void AddROI2_clicked();
    void AddROI3_clicked();
    void AddROI4_clicked();
    void AddROI5_clicked();
    void AddROI6_clicked();
    void AddROI7_clicked();
    void AddROI8_clicked();

    // system slot function
    void on_LoadImage_clicked();
    void on_SaveImage_clicked();
    void on_ClearCurrentROI_clicked();
    void on_ClearAllROI_clicked();
    void on_lineEdit_returnPressed();
    void on_SaveFile_clicked();
    void on_actionOpen_File_triggered();
    void on_actionSave_As_triggered();
    void on_actionSave_Picture_triggered();
    void on_actionROI1_triggered();
    void on_actionROI2_triggered();
    void on_actionROI3_triggered();
    void on_actionROI4_triggered();
    void on_actionROI5_triggered();
    void on_actionROI6_triggered();
    void on_actionROI7_triggered();
    void on_actionROI8_triggered();

    void on_actionQuit_triggered();

    void on_actionClear_Current_triggered();

    void on_actionClear_All_triggered();

private:
    Ui::MainWindow *ui;
    myLabel *label;
    bool is_add_roi;
    QMap<QString, QRect> rect_map;
    QString current_roi;

    void ROIClickedHelper(QString string);
    void loadImageHelper(QImage img);
    void failToLoadImageHelper();
    bool checkSaveImageHelper();
    void connectSlotHelper();
    void groupROIHelper();

Q_SIGNALS:
    void sendIsAddROISig(bool is_add_roi);
    void sendRectMapSig(QMap<QString, QRect> rect_map);
    void sendSaveRectSig();
    void sendResetROISig();
};
#endif // MAINWINDOW_H
