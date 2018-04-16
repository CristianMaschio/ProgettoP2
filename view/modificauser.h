#ifndef MODIFICAUSER_H
#define MODIFICAUSER_H
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "model/allusers.h"
#include "model/warehouse.h"


class ModificaUser: public QDialog
{
    Q_OBJECT
    User* logUser;
    User* modUser;
    bool changeOrAdd; //falso per modificare l'utente, vero per aggiungerlo

    QLabel* lUsername;
    QLineEdit* username;
    QPushButton* changeUsername;

    QLabel* lNewPassword;
    QLineEdit* newPassword;
    QLineEdit* confirmNewPassword;
    QPushButton* changePassword;

    QLabel* lName;
    QLineEdit* name;
    QPushButton* changeName;

    QLabel* lSurname;
    QLineEdit* surname;
    QPushButton* changeSurname;

    QLabel* lSkill;
    QLineEdit* skill;
    QPushButton* changeSkill;

    QGridLayout* gridLayout;
    QVBoxLayout* boxLayout;

    QLabel* selectType;
    QComboBox* typeUser;
    QPushButton* changeType;

    QPushButton* createUser;

public:
    ModificaUser(User *LogUser, User* ModUser=NULL, bool fChangeOrVAdd=false);

    void createLayoutStandard();
    void createLayoutChange();
    void createLayoutAdd();
    void setViewChange();
    void setViewAdd();

public slots:
    void bChangeUsername();
    void bChangePassword();
    void bChangeName();
    void bChangeSurname();
    void bChangeSkill();
    void bAddUser();
    void bChangeType();
signals:
    void v_changeUsername(User*, const string&);
    void v_changePassword(User*, const string&);
    void v_changeName(User*, const string&);
    void v_changeSurname(User*, const string&);
    void v_changeSkill(User*, const int);
    void v_addUser(User*);
    void v_changeType(User*);
};

#endif // MODIFICAUSER_H
