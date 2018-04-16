#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include "model/warehouse.h"
#include "model/allusers.h"
#include "view/loginview.h"
#include "view/logmainview.h"
#include <QObject>
#include "itemscontroller.h"
#include "userscontroller.h"
#include "itemscontroller.h"

class MainController: public QObject
{
    Q_OBJECT
    Warehouse* items;
    AllUsers* users;
    User* logUser;                          //Utente loggato

    LoginView* loginView;
    LogMainView* logUserView;
    ItemsController* controllerItems;
    UsersController* controllerUsers;

public:
    MainController(QObject *parent=0);

    void startLogin();
    void closeLogin();

    void startLogMainView();
    void closeLogMainView();

    void exe();
    ~MainController();
public slots:
    void tryLogin(const string&, const string&);
    void aggiornaUserController(ModificaUser*);
    void aggiornaUserView(AllUsersView*);
    void aggiornaItemController(ModificaItem*);
    void aggiornaItemView(WarehouseView*);
    void saveAllChanges();
    void loadAll();
    void makeLogin();
};

#endif // MAINCONTROLLER_H
