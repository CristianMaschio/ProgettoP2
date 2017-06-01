#ifndef ALLUSERSVIEW_H
#define ALLUSERSVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <string>
#include "model/allusers.h"
#include "modificauser.h"
#include "tableusers.h"

class AllUsersView: public QWidget
{
    Q_OBJECT
    User* logUser;
    AllUsers* users;
    User* modUser=NULL;

    QGridLayout* grid;
    QVBoxLayout* layoutAllUsers;

    QLabel* lUtenteLoggato;
    QLabel* lUsername;
    QLabel* lNome;
    QLabel* lName;
    QLabel* lCognome;
    QLabel* lSurname;

    QLineEdit* textUser;
    QComboBox* boxUsers;
    QPushButton* find;
    QPushButton* seeAll;
    QPushButton* modifica;
    QPushButton* elimina;

    TableUsers* tabellaUtenti;

    ModificaUser* modUserView;

public:
    AllUsersView(User* LogUser,AllUsers* allUsers, QWidget* parent=0);

    void setLabel(QLabel* l);
    void createLayout();
    void addUsersBox();

public slots:
    void buttonFind();
    void buttonSeeAll();
    void buttonModifica();
    void buttonElimina();
    void boxUserChange(QString);
    void aggiornaView();
    void aggiornaViewChangeName();
    void closeEvent();
signals:
    void sAggiornaModificaUser(ModificaUser*);
    void sAggiornaModUserStatusBar(User*);
    void sDeleteUser(const string&);
    void sViewEnable();
    void sDisconnetti();
};

#endif // ALLUSERSVIEW_H
