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
    ui->verticalLayout->addWidget(label);
    QObject::connect(label, &myLabel::sendRectSig, this, &MainWindow::recvRectSig);
    QObject::connect(this, &MainWindow::sendIsAddROISig, label, &myLabel::recvIsAddROISig);
    QObject::connect(ui->roi1, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi2, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi3, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi4, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi5, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi6, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi7, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));
    QObject::connect(ui->roi8, SIGNAL(clicked()), this, SLOT(on_AddROI_clicked()));

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

}

void MainWindow::recvRectSig(QRect rect)
{
    if (rect_list.size() < 8)
    {
        rect_list.push_back(rect);
    }
    else
    {
        rect_list[7] = rect;
    }
    qDebug() << rect_list << endl;

}

void MainWindow::on_AddROI_clicked()
{
    if (is_add_roi)
    {
        is_add_roi = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
    else
    {
        is_add_roi = true;
        this->setCursor(QCursor(Qt::CrossCursor));
    }
    emit sendIsAddROISig(is_add_roi);

}
