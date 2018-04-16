#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H
#include <QObject>
#include "view/modificauser.h"
#include "model/allusers.h"
#include "view/allusersview.h"

class UsersController: public QObject
{
    Q_OBJECT

    AllUsers* users;
    User* logUser=NULL;
    ModificaUser* modUserView=NULL; //puntatore classe view
    AllUsersView* viewUsers=NULL;

    bool isAdmin();
public:
    UsersController(AllUsers* allUsers, QObject* parent=0);

    void aggiornaModificaUser(ModificaUser* mUser);
    void aggiornaLogUser(User* LogUser);
    void aggiornaViewUsers(AllUsersView* aggViewUsers);

public slots:
    void addUser(User*);
    void removeUser(const string&);
    void changeUsername(User*, const string&);
    void changePassword(User*, const string&);
    void changeName(User*, const string&);
    void changeSurname(User*, const string&);
    void changeSkill(User*, const int);
    void changeType(User*);
};

#endif // USERSCONTROLLER_H
