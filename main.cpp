#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginForm login;
    if (login.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    return 0;
}
