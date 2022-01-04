#include "loginform.h"

LoginForm::LoginForm(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Login UI"));

    userNameLabel = new QLabel(this);
    userNameLabel->move(50,83);
    userNameLabel->setText("Username:");

    userNameLineEdit = new QLineEdit(this);
    userNameLineEdit->move(130,80);
    userNameLineEdit->setPlaceholderText(tr("Enter Username"));

    pwdLabel = new QLabel(this);
    pwdLabel->move(50,133);
    pwdLabel->setText("Password:");

    pwdLineEdit = new QLineEdit(this);
    pwdLineEdit->move(130,130);
    pwdLineEdit->setPlaceholderText("Enter Password");
    pwdLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton(this);
    loginButton->move(85,200);
    loginButton->setText("Login");

    exitButton = new QPushButton(this);
    exitButton->move(175,200);
    exitButton->setText("Exit");

    connect(loginButton, &QPushButton::clicked, this, &LoginForm::login);
    connect(exitButton, &QPushButton::clicked, this, &LoginForm::close);
}

void LoginForm::login()
{

    if(userNameLineEdit->text().trimmed() == tr("") && pwdLineEdit->text() == tr(""))
    {
       this->accept();
       QMessageBox::information(this, tr("Login"), "Login Success!");
    }
    else
    {
       QMessageBox::warning(this, tr("Warning"), tr("Invalid Username/Password!"), QMessageBox::Yes);
       userNameLineEdit->clear();
       pwdLineEdit->clear();
       userNameLineEdit->setFocus();
    }
}
