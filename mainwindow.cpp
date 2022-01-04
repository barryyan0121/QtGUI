#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtHeaders.h"
#include "loginform.h"

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
    connectSlotHelper();
    groupROIHelper();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// override event functions

void MainWindow::closeEvent( QCloseEvent * event )
{
    switch(QMessageBox::information(this, tr("Exit Warning"), tr("Do you really want to exit?"), tr("Yes"), tr("No"), 0, 1))
    {
        case 0:
            event->accept();
            break;
        default:
            event->ignore();
            break;
    }
}

// Customized SLOT functions

void MainWindow::recvRectSig(QRect rect)
{
    rect_map[current_roi] = rect;
    qDebug() << rect_map << endl;
    emit sendRectMapSig(rect_map);
}

void MainWindow::recvMouseMoveSig(QMouseEvent *e)
{

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
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setBaseSize(QSize(1200, 500));
    msgBox.exec();
}

bool MainWindow::checkSaveImageHelper()
{
    if (label->pixmap() == nullptr)
    {
        QMessageBox::warning(this,tr("Error"),tr("Failed to Save File"));
        return false;
    }
    return true;
}

void MainWindow::connectSlotHelper()
{
    QObject::connect(label, &myLabel::sendRectSig, this, &MainWindow::recvRectSig);
    QObject::connect(label, &myLabel::sendMouseMoveSig, this, &MainWindow::recvMouseMoveSig);
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

void MainWindow::groupROIHelper()
{
    QActionGroup *roi_alignment = new QActionGroup(this);
    roi_alignment->addAction(ui->actionROI1);
    roi_alignment->addAction(ui->actionROI2);
    roi_alignment->addAction(ui->actionROI3);
    roi_alignment->addAction(ui->actionROI4);
    roi_alignment->addAction(ui->actionROI5);
    roi_alignment->addAction(ui->actionROI6);
    roi_alignment->addAction(ui->actionROI7);
    roi_alignment->addAction(ui->actionROI8);
}

QImage MainWindow::savePainterHelper()
{
    QPainter painter;
    QImage img = label->m_loadPixmap.toImage();
    painter.begin(&img);
    painter.setPen(QPen(Qt::red, 2));
    for (QRect rect: rect_map.values())
    {
        QRect newRect = QRect(rect.x() * img.width() / label->width(),
                              rect.y() * img.height() / label->height(),
                              rect.width() * img.width() / label->width(),
                              rect.height() * img.height() / label->height());
        painter.drawRect(newRect);
    }
    painter.end();
    return img;
}

// System SLOT Function

void MainWindow::on_LoadImage_clicked()
{
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("Open File");
    QStringList qstrFilters;
    qstrFilters<<"Picture File (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
    qstrFilters<<"All Files (*)";
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
    if (checkSaveImageHelper())
    {
        QImage img = savePainterHelper();
        QString filename = ui->lineEdit->text();
        filename = filename.split(".jpg").at(0) + "_annotated.jpg";
        img.save(filename);
        QMessageBox::warning(this,tr("Information"), tr("Successfully Saved File to Disk"));
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    on_LoadImage_clicked();
}

void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this, tr("Save File"), "C:/", tr("Picture File (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)"));
    if(fileName == "")
    {
        return;
    }
    if (checkSaveImageHelper())
    {
        QImage img = savePainterHelper();
        img.save(fileName);
        QMessageBox::warning(this,tr("Information"), tr("Successfully Saved File to Disk"));
    }
}

void MainWindow::on_actionSave_Picture_triggered()
{
    on_SaveFile_clicked();
}

void MainWindow::on_actionROI1_triggered()
{
    ui->roi1->click();
    ui->actionROI1->setChecked(true);
}

void MainWindow::on_actionROI2_triggered()
{
    ui->roi2->click();
}

void MainWindow::on_actionROI3_triggered()
{
    ui->roi3->click();
}

void MainWindow::on_actionROI4_triggered()
{
    ui->roi4->click();
}

void MainWindow::on_actionROI5_triggered()
{
    ui->roi5->click();
}

void MainWindow::on_actionROI6_triggered()
{
    ui->roi6->click();
}

void MainWindow::on_actionROI7_triggered()
{
    ui->roi7->click();
}

void MainWindow::on_actionROI8_triggered()
{
    ui->roi8->click();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionClear_Current_triggered()
{
    ui->ClearCurrentROI->click();
}

void MainWindow::on_actionClear_All_triggered()
{
    ui->ClearAllROI->click();
}

void MainWindow::on_actionQuit_Login_triggered()
{
    this->hide();
    LoginForm login;
    if (login.exec() == QDialog::Accepted)
    {
        this->show();
    }
}
