
#include "maincontroller.h"

MainController::MainController(QObject *parent):
    QObject(parent)
{
}


void MainController::startLogin()
{
    loginView->show();//manda in esecuzione LoginWiew
}

void MainController::closeLogin()
{
    loginView->hide();
}



void MainController::startLogMainView()
{
    logUserView=new LogMainView(logUser,items,users);
    connect(logUserView,SIGNAL(makeLoginAgain()),this,SLOT(makeLogin()));
    connect(logUserView,SIGNAL(aggiornaUserController(ModificaUser*)),this,SLOT(aggiornaUserController(ModificaUser*)));
    connect(logUserView,SIGNAL(saveAll()),this,SLOT(saveAllChanges()));
    connect(logUserView,SIGNAL(reloadAll()),this,SLOT(loadAll()));
    connect(logUserView,SIGNAL(aggiornaItemController(ModificaItem*)),this,SLOT(aggiornaItemController(ModificaItem*)));
    connect(logUserView,SIGNAL(aggiornaViewItem(WarehouseView*)),this,SLOT(aggiornaItemView(WarehouseView*)));
    connect(logUserView,SIGNAL(aggiornaViewUsers(AllUsersView*)),this,SLOT(aggiornaUserView(AllUsersView*)));
    controllerItems->aggiornaItemsView( logUserView->getWarehouseView());//va fatto manualmente perche' non e' possibile farlo tramite connect durante la creazione visto che i connect si creano dopo che l'oggetto e' creato
    logUserView->show();
}

void MainController::closeLogMainView()
{
    logUserView->close();
    delete logUserView;
}

void MainController::exe()
{
    users=new AllUsers();
    items=new Warehouse();
    loginView=new LoginView;
    connect(loginView,SIGNAL(tryLog(const string&,const string&)),this,SLOT(tryLogin(const string&,const string&)));

    controllerItems=new ItemsController(items,this);

    controllerUsers=new UsersController(users,this);

    startLogin();
}

MainController::~MainController()
{
    if(users)delete users;
    if(items)delete items;
    if(loginView)loginView->close();
}


void MainController::tryLogin(const string &name, const string &password)
{
    User* app;
    app=users->tryLog(name,password);
    if (app)
    {//log riuscito, passo al controller LogUser
        logUser=app;
        controllerUsers->aggiornaLogUser(logUser);
        items->setLogUser(logUser);
        startLogMainView();
        closeLogin();
    }else{
        loginView->clean();
    }
}

void MainController::aggiornaUserController(ModificaUser *modUser)
{
    controllerUsers->aggiornaModificaUser(modUser);
}

void MainController::aggiornaUserView(AllUsersView *aggViewUsers)
{
    controllerUsers->aggiornaViewUsers(aggViewUsers);
}

void MainController::aggiornaItemController(ModificaItem *modItem)
{
    controllerItems->aggiornaPuntatoreView(modItem);
}

void MainController::aggiornaItemView(WarehouseView *viewItem)
{
    controllerItems->aggiornaItemsView(viewItem);
}

void MainController::saveAllChanges()
{
    users->saveUsers();
    items->saveItems();
    QMessageBox::information(0,"Salvataggio","Salvataggio avvenuto con successo");
}

void MainController::loadAll()
{
    users->loadUsers();
    items->loadItems();
}

void MainController::makeLogin()
{
    loginView->clean();
    loginView->show();
}


