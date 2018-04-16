#include "logmainview.h"
#include "modificauser.h"
#include <QDebug>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>

LogMainView::LogMainView(User *user, Warehouse *Items,AllUsers* allUsers, QWidget *parent):
    QMainWindow(parent),logUser(user),items(Items), users(allUsers)
{
    setWindowTitle("Gestionale");
    setFixedHeight(500);
    setFixedWidth(600);
    QRect r = geometry();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(r);

    statBar=new QStatusBar;
    setStatusBar(statBar);
    infoStatBar=new QLabel("Tipo utente: "+ QString::fromStdString(logUser->getType()));
    statBar->addWidget(infoStatBar,500);
    itemStatBar=new QLabel("Oggetto selezionato: Nessuno");
    statBar->addWidget(itemStatBar);

    addMenu();
    setViewItems();
}

WarehouseView *LogMainView::getWarehouseView() const
{
    return gestionale;
}

void LogMainView::addMenu()
{
    menu=new QMenuBar;

    settings=new QMenu("Impostazioni");
    logout=new QAction("Disconnetti",0);
    modifyUser=new QAction("Modifica account",0);
    save=new QAction("Salva modifiche",0);
    settings->addAction(logout);
    settings->addAction(modifyUser);
    settings->addAction(save);

    connect(logout,SIGNAL(triggered(bool)),this,SLOT(disconnetti()));
    connect(modifyUser,SIGNAL(triggered(bool)),this,SLOT(impostazioniUtente()));
    connect(save,SIGNAL(triggered(bool)),this,SIGNAL(saveAll()));

    menu->addMenu(settings);


    if(dynamic_cast<Admin*>(logUser)) //Menu Admin
    {
        management=new QMenu("Gestione");
        userManagement=new QAction("Utenti",0);
        itemManagement=new QAction("Items",0);
        management->addAction(userManagement);
        management->addAction(itemManagement);

        menu->addMenu(management);
        //connect
        connect(userManagement,SIGNAL(triggered(bool)),this,SLOT(addViewUsers()));
        connect(itemManagement,SIGNAL(triggered(bool)),this,SLOT(addViewItems()));

        add=new QMenu("Aggiungi");
        addUser=new QAction("Nuovo Utente",0);
        addItem=new QAction("Nuovo Item",0);
        add->addAction(addUser);
        add->addAction(addItem);

        menu->addMenu(add);
        //connect
        connect(addUser,SIGNAL(triggered(bool)),this,SLOT(creaUser()));
        connect(addItem,SIGNAL(triggered(bool)),this,SLOT(creaItem()));
    }

    setMenuBar(menu);

}

void LogMainView::setViewItems()
{
    delete viewUsers;
    viewUsers=0;
    gestionale=new WarehouseView(logUser,items);
    emit aggiornaViewItem(gestionale);
    connect(gestionale,SIGNAL(changeItemStatBar(Item*)),this,SLOT(aggiornaItemStatusBar(Item*)));
    connect(gestionale,SIGNAL(sModificationItem()),this,SLOT(modificationItem()));
    connect(gestionale,SIGNAL(sViewEnable()),this,SLOT(viewEnabled()));
    aggiornaItemStatusBar(modItem);
    setCentralWidget(gestionale);

}

void LogMainView::setViewUsers()
{
    delete gestionale;
    gestionale=0;
    viewUsers= new AllUsersView(logUser,users);
    emit aggiornaViewUsers(viewUsers);
    connect(viewUsers,SIGNAL(sAggiornaModificaUser(ModificaUser*)),this,SIGNAL(aggiornaUserController(ModificaUser*)));
    connect(viewUsers,SIGNAL(sAggiornaModUserStatusBar(User*)),this,SLOT(aggiornaUserStatusBar(User*)));
    connect(viewUsers,SIGNAL(sViewEnable()),this,SLOT(viewEnabled()));
    connect(viewUsers,SIGNAL(sDisconnetti()),this,SLOT(disconnetti()));
    aggiornaUserStatusBar(modUser);
    setCentralWidget(viewUsers);
}
 //NON VA IN LAB
void LogMainView::closeEvent(QCloseEvent *event)
{
    //! Ignore the event by default.. otherwise the window will be closed always.
    event->ignore();

    QMessageBox msgClose;
    msgClose.setWindowTitle("Disconnessione");
    msgClose.setText("Disconnessione dell'utente in corso..");
    msgClose.setInformativeText("Vuoi salvare le possibili modifiche?");
    msgClose.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    msgClose.setButtonText(QMessageBox::Save,"Salva ed esci");
    msgClose.setButtonText(QMessageBox::Discard,"Esci senza salvare");
    msgClose.setButtonText(QMessageBox::Cancel,"Annulla");
    int ret = msgClose.exec();
    bool app=true;
    switch (ret) {
      case QMessageBox::Save:
        {
          emit saveAll();
          qDebug() << "click button: Salva ed esci";
          break;
        }
      case QMessageBox::Discard:
        {
            qDebug() << "click button: Esci senza salvare";
            break;
        }
      case QMessageBox::Cancel:
        {
          qDebug() << "click button: Annulla";
          app=false;
          break;
        }
      default:
          break;
    }
    if (app) event->accept();
}

bool LogMainView::deleteEvent()
{
        QMessageBox msgClose;
        msgClose.setWindowTitle("Disconnessione");
        msgClose.setText("Disconnessione dell'utente in corso..");
        msgClose.setInformativeText("Vuoi salvare le possibili modifiche?");
        msgClose.setStandardButtons(QMessageBox::Save | QMessageBox::Discard| QMessageBox::Cancel);

        msgClose.setButtonText(QMessageBox::Save,"Salva ed esci");
        msgClose.setButtonText(QMessageBox::Discard,"Esci senza salvare");
        msgClose.setButtonText(QMessageBox::Cancel,"Annulla");
        int ret = msgClose.exec();

        bool app;
        switch (ret) {
        case QMessageBox::Save:
        {
            app=true;
            emit saveAll();
            qDebug() << "click button: Salva ed esci";
            break;
        }
        case QMessageBox::Discard:
        {
            app=true;
            emit reloadAll();
            qDebug() << "click button: Esci senza salvare";
            break;
        }
        case QMessageBox::Cancel:
        {
            qDebug() << "click button: Annulla";
            app=false;
            break;
        }
        default:
            app=false;
            break;
        }
        return app;
}

void LogMainView::disconnetti()
{
    if(deleteEvent())
    {
        emit makeLoginAgain();
        this->deleteLater();
    }
}

void LogMainView::impostazioniUtente()
{
    modUserView = new ModificaUser(logUser);
    emit aggiornaUserController(modUserView);
    connect(modUserView,SIGNAL(finished(int)),this,SLOT(aggiornaViewLog()));
    viewEnabled();
    connect(modUserView,SIGNAL(finished(int)),this,SLOT(viewEnabled()));
    modUserView->show();
}

void LogMainView::creaUser()
{
    modUserView=new ModificaUser(logUser,0,true);
    emit aggiornaUserController(modUserView);
    viewEnabled();
    connect(modUserView,SIGNAL(finished(int)),this,SLOT(viewEnabled()));
    connect(modUserView,SIGNAL(v_addUser(User*)),this,SLOT(aggiornaViewUserBox()));//++++++++++++++++++++++++++++++++++++
    modUserView->show();
}

void LogMainView::creaItem()
{
    modItemView=new ModificaItem(logUser,0,true);//view pre creare l'oggetto
    emit aggiornaItemController(modItemView);
    connect(modItemView,SIGNAL(aggiornaBox()),this,SLOT(aggiornaViewBox()));
    viewEnabled();
    connect(modItemView,SIGNAL(finished(int)),this,SLOT(viewEnabled()));
    modItemView->show();
}

void LogMainView::addViewUsers()
{
    if (!viewUsers) setViewUsers();
    else QMessageBox::warning(0,"Menu, gestionale, utenti","Il gestionale degli utenti e' gia' aperto");
}

void LogMainView::addViewItems()
{
    if (!gestionale) setViewItems();
    else QMessageBox::warning(0,"Menu, gestionale, items","Il gestionale degli items e' gia' aperto");
}

void LogMainView::aggiornaViewLog()
{
    if(gestionale)gestionale->refresh();
    else viewUsers->refresh();
}

void LogMainView::aggiornaViewBox()
{
    gestionale->createBox();
}

void LogMainView::aggiornaItemStatusBar(Item *item)
{
    modItem=item;
    if(modItem) itemStatBar->setText("Oggetto selezionato: "+QString::fromStdString(modItem->getName()));
    else itemStatBar->setText("Oggetto selezionato: Nessuno");
}

void LogMainView::aggiornaUserStatusBar(User *user)
{
    modUser=user;
    if(modUser) itemStatBar->setText("Utente selezionato: "+QString::fromStdString(modUser->getUsername()));
    else itemStatBar->setText("User selezionato: Nessuno");
}

void LogMainView::aggiornaViewUserBox()
{
    if(viewUsers)viewUsers->addUsersBox();
}

void LogMainView::modificationItem()
{
    if(modItem) //se l'oggetto esiste allora creo la view per la modifica
    {
        modItemView=new ModificaItem(logUser,modItem);
        connect(modItemView,SIGNAL(sAggiornaName()),this,SLOT(aggiornaViewBox()));
        viewEnabled();
        connect(modItemView,SIGNAL(finished(int)),this,SLOT(viewEnabled()));
        emit aggiornaItemController(modItemView);
        modItemView->show();
    }else QMessageBox::warning(0,"Errore sull'oggetto selezionato","L'oggetto attualmente selezionato e' inesistente, selezionalo dalla lista o esegui la ricerca per compiere modifiche");
}

void LogMainView::viewEnabled()
{
    if(isEnabled())setEnabled(false);
    else setEnabled(true);
}

