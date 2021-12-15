#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtHeaders.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new myLabel(this);
    is_add_roi = false;
    label->setText("Please Load Image");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel{background-color:rgb(200,200,200);}");
    label->setScaledContents(true);
    ui->verticalLayout->addWidget(label);
    QObject::connect(label, &myLabel::sendRectSig, this, &MainWindow::recvRectSig);
    QObject::connect(this, &MainWindow::sendSaveImageSig, label, &myLabel::recvSaveImageSig);
    QObject::connect(this, &MainWindow::sendIsAddROISig, label, &myLabel::recvIsAddROISig);
    QObject::connect(this, &MainWindow::sendRectMapSig, label, &myLabel::recvRectMapSig);
    QObject::connect(ui->roi1, &QPushButton::clicked, this, &MainWindow::AddROI1_clicked);
    QObject::connect(ui->roi2, &QPushButton::clicked, this, &MainWindow::AddROI2_clicked);
    QObject::connect(ui->roi3, &QPushButton::clicked, this, &MainWindow::AddROI3_clicked);
    QObject::connect(ui->roi4, &QPushButton::clicked, this, &MainWindow::AddROI4_clicked);
    QObject::connect(ui->roi5, &QPushButton::clicked, this, &MainWindow::AddROI5_clicked);
    QObject::connect(ui->roi6, &QPushButton::clicked, this, &MainWindow::AddROI6_clicked);
    QObject::connect(ui->roi7, &QPushButton::clicked, this, &MainWindow::AddROI7_clicked);
    QObject::connect(ui->roi8, &QPushButton::clicked, this, &MainWindow::AddROI8_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadImage_clicked()
{
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("选择图片");
    QStringList qstrFilters;
    qstrFilters<<"图片文件(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
    qstrFilters<<"所有文件 (*)";
    fileDlg->setNameFilters(qstrFilters);
    fileDlg->setFileMode(QFileDialog::ExistingFile);
    if(fileDlg->exec() == QDialog::Accepted)
    {
        QStringList lstName = fileDlg->selectedFiles();
        if(lstName.count() > 0)
        {
            ui->lineEdit->setText(lstName.at(0));
            QImage img = QImage(lstName.at(0));
            QPixmap tempPix=QPixmap::fromImage(img);
            label->setPixmap(tempPix);
            label->resize(label->pixmap()->size());
            label->m_loadPixmap = tempPix;
        }
    }
    fileDlg->close();
    delete fileDlg;
    fileDlg = nullptr;
}

void MainWindow::on_SaveImage_clicked()
{
    emit sendSaveImageSig();
}

void MainWindow::recvRectSig(QRect rect)
{
    rect_map[current_roi] = rect;
    emit sendRectMapSig(rect_map);
}

void MainWindow::ROIClickedHelper(QString string)
{
    if (is_add_roi && current_roi == string)
    {
        is_add_roi = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
    else
    {
        is_add_roi = true;
        this->setCursor(QCursor(Qt::CrossCursor));
    }
    current_roi = string;
    emit sendIsAddROISig(is_add_roi);
}

void MainWindow::AddROI1_clicked()
{
    ROIClickedHelper("ROI1");
}

void MainWindow::AddROI2_clicked()
{
    ROIClickedHelper("ROI2");
}

void MainWindow::AddROI3_clicked()
{
    ROIClickedHelper("ROI3");
}

void MainWindow::AddROI4_clicked()
{
    ROIClickedHelper("ROI4");
}


void MainWindow::AddROI5_clicked()
{
    ROIClickedHelper("ROI5");
}


void MainWindow::AddROI6_clicked()
{
    ROIClickedHelper("ROI6");
}

void MainWindow::AddROI7_clicked()
{
    ROIClickedHelper("ROI7");
}

void MainWindow::AddROI8_clicked()
{
    ROIClickedHelper("ROI8");
}















