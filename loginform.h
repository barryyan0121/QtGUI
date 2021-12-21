#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>

#include "QtHeaders.h"

class LoginForm : public QDialog
{
    Q_OBJECT
public:
    explicit LoginForm(QDialog *parent = nullptr);

signals:

public slots:
    void login();

private:
    QLabel *userNameLabel;
    QLabel *pwdLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *loginButton;
    QPushButton *exitButton;

};

#endif // LOGINFORM_H
