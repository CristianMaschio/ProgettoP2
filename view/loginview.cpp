#include "loginview.h"
#include <QMessageBox>
#include <QRegExpValidator>

LoginView::LoginView()
{
    setWindowTitle("Login");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    createLayout();
}

void LoginView::createLayout()
{
    labelUserName=new QLabel;
    labelUserName->setText("Username:");
    labelPassword=new QLabel;
    labelPassword->setText("Password:");

    lineUserName=new QLineEdit;
    lineUserName->setPlaceholderText("insert username..");
    lineUserName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,14}")));
    linePassword=new QLineEdit;
    linePassword->setPlaceholderText("insert password..");
    linePassword->setEchoMode(QLineEdit::Password);
    linePassword->setValidator(new QRegExpValidator(QRegExp(".{1,14}")));

    buttonLogin=new QPushButton;
    buttonLogin->setText("Login");

    gridLogin=new QGridLayout;
    gridLogin->addWidget(labelUserName,1,1);
    gridLogin->addWidget(labelPassword,2,1);
    gridLogin->addWidget(lineUserName,1,2);
    gridLogin->addWidget(linePassword,2,2);
    gridLogin->addWidget(buttonLogin,3,2);

    layoutLogin=new QVBoxLayout;
    layoutLogin->addLayout(gridLogin);
    setLayout(layoutLogin);

    connect(buttonLogin,SIGNAL(clicked()),this,SLOT(log()));
}

void LoginView::clean()
{
    linePassword->clear();
    lineUserName->clear();
    lineUserName->setFocus();
}

void LoginView::log()
{
    emit tryLog(lineUserName->text().toStdString(),linePassword->text().toStdString());
}
