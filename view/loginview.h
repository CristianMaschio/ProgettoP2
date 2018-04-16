#ifndef LOGINVIEW_H
#define LOGINVIEW_H
#include <string>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
using std::string;

class LoginView: public QDialog
{
    Q_OBJECT
    QGridLayout* gridLogin;
    QVBoxLayout* layoutLogin;
    QLabel* labelUserName;
    QLabel* labelPassword;
    QLineEdit* lineUserName;
    QLineEdit* linePassword;
    QPushButton* buttonLogin;
public:
    LoginView();
    void createLayout();
    void clean();

public slots:
    void log();
signals:
    void tryLog(const string&, const string&);
};

#endif // LOGINVIEW_H
