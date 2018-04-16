#ifndef LOGMAINVIEW_H
#define LOGMAINVIEW_H
#include <QMainWindow>
#include "model/allusers.h"
#include "warehouseview.h"
#include "allusersview.h"
#include <QStatusBar>
#include <QMenuBar>
#include "modificauser.h"
#include "modificaitem.h"

class LogMainView: public QMainWindow
{
    Q_OBJECT
    User* logUser;
    Item* modItem=NULL;
    User* modUser=NULL;
    Warehouse* items;
    AllUsers* users;

    QStatusBar* statBar;
    QLabel* infoStatBar;
    QLabel* itemStatBar;

    QMenuBar* menu;
    QMenu* settings;
    QAction* logout;
    QAction* modifyUser;
    QAction* save;
    QMenu* management;
    QAction* userManagement;
    QAction* itemManagement;
    QMenu* add;
    QAction* addUser;
    QAction* addItem;


    WarehouseView* gestionale=NULL;
    AllUsersView* viewUsers=NULL;
    ModificaUser* modUserView;
    ModificaItem* modItemView;
public:
    LogMainView(User* user,Warehouse* Items,AllUsers* allUsers, QWidget* parent=0);
    WarehouseView* getWarehouseView()const;

    void addMenu();
    void setHide();
    void setViewItems();
    void setViewUsers();
    virtual void closeEvent ( QCloseEvent * event );

    bool deleteEvent();

public slots:
    void disconnetti();
    void impostazioniUtente();
    void creaUser();
    void creaItem();
    void addViewUsers();
    void addViewItems();

    void aggiornaViewLog();
    void aggiornaViewBox();
    void aggiornaItemStatusBar(Item*);
    void aggiornaUserStatusBar(User*);
    void aggiornaViewUserBox();

    void modificationItem();
    void viewEnabled();

signals:
    void aggiornaUserController(ModificaUser*);
    void aggiornaItemController(ModificaItem*);
    void aggiornaViewItem(WarehouseView*);
    void aggiornaViewUsers(AllUsersView*);
    void saveAll();
    void reloadAll();
    void makeLoginAgain();
};

#endif // LOGMAINVIEW_H
