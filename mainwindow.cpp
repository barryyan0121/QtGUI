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
    QObject::connect(this, &MainWindow::sendSaveRectSig, label, &myLabel::recvSaveRectSig);
    QObject::connect(this, &MainWindow::sendIsAddROISig, label, &myLabel::recvIsAddROISig);
    QObject::connect(this, &MainWindow::sendRectMapSig, label, &myLabel::recvRectMapSig);
    QObject::connect(this, &MainWindow::sendResetROISig, label, &myLabel::recvResetROISig);
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

// System SLOT Function

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
            loadImageHelper(img);
        }
    }
    fileDlg->close();
    delete fileDlg;
    fileDlg = nullptr;
}

void MainWindow::on_SaveImage_clicked()
{
    emit sendSaveRectSig();
}

void MainWindow::on_ClearCurrentROI_clicked()
{
    rect_map.remove(current_roi);
    emit sendRectMapSig(rect_map);
    emit sendResetROISig();
}

void MainWindow::on_ClearAllROI_clicked()
{
    rect_map.clear();
    emit sendRectMapSig(rect_map);
    emit sendResetROISig();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString filename = ui->lineEdit->text();
    QImage img = QImage(filename);
    loadImageHelper(img);
}

void MainWindow::on_SaveFile_clicked()
{
    QImage img = label->pixmap()->toImage();
    QString filename = ui->lineEdit->text();
    filename = filename.split(".jpg").at(0) + "_annotated.jpg";
    img.save(filename);
}

// Helper functions

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
    emit sendResetROISig();
}

void MainWindow::loadImageHelper(QImage img)
{
    if (img.isNull())
    {
        failToLoadImageHelper();
        return;
    }
    QPixmap tempPix = QPixmap::fromImage(img);
    label->setPixmap(tempPix);
    label->resize(label->pixmap()->size());
    label->m_loadPixmap = tempPix;

}

void MainWindow::failToLoadImageHelper()
{
    QMessageBox msgBox;
    msgBox.setText("Failed to load image!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setBaseSize(QSize(1200, 500));
    msgBox.exec();
}

// Customized SLOT functions

void MainWindow::recvRectSig(QRect rect)
{
    rect_map[current_roi] = rect;
    emit sendRectMapSig(rect_map);
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




