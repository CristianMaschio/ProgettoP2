#include "allusersview.h"

void AllUsersView::addUsersBox()
{
    list<User*> app;
    app=users->getAllUser();
    boxUsers->clear();
    boxUsers->addItem("");
    for(list<User*>::const_iterator it=app.begin(); it!=app.end(); ++it)
    {
        boxUsers->addItem(QString::fromStdString((*it)->getUsername()));
    }
}


AllUsersView::AllUsersView(User *LogUser, AllUsers *allUsers, QWidget *parent):QWidget(parent),logUser(LogUser),users(allUsers)
{
    createLayout();
    connect(this,SIGNAL(destroyed(QObject*)),this,SLOT(closeEvent()));
}

void AllUsersView::setLabel(QLabel *l)
{
    l->setFixedHeight(15);
}

void AllUsersView::createLayout()
{
    lUtenteLoggato=new QLabel;
    lUtenteLoggato->setText("Utente loggato:");
    setLabel(lUtenteLoggato);
    lUsername=new QLabel;
    setLabel(lUsername);
    lUsername->setText(QString::fromStdString(logUser->getUsername()));

    lNome=new QLabel;
    lNome->setText("Nome:");
    setLabel(lNome);
    lName=new QLabel;
    setLabel(lName);
    lName->setText(QString::fromStdString(logUser->getName()));

    lCognome=new QLabel;
    setLabel(lCognome);
    lCognome->setText("Cognome:");
    lSurname=new QLabel;
    setLabel(lSurname);
    lSurname->setText(QString::fromStdString(logUser->getSurname()));

    textUser=new QLineEdit;
    textUser->setPlaceholderText("Inserisci Utente");
    textUser->setFixedWidth(100);
    textUser->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,14}")));

    boxUsers=new QComboBox;
    addUsersBox();
    connect(boxUsers,SIGNAL(currentIndexChanged(QString)),this,SLOT(boxUserChange(QString)));

    find=new QPushButton("Cerca/Seleziona");
    connect(find,SIGNAL(clicked(bool)),this,SLOT(buttonFind()));
    seeAll=new QPushButton("Visualizza tutti");
    connect(seeAll,SIGNAL(clicked(bool)),this,SLOT(buttonSeeAll()));
    modifica=new QPushButton("Modifica");
    connect(modifica,SIGNAL(clicked(bool)),this,SLOT(buttonModifica()));
    elimina=new QPushButton("Elimina");
    connect(elimina,SIGNAL(clicked(bool)),this,SLOT(buttonElimina()));

    tabellaUtenti=new TableUsers(users);

    grid=new QGridLayout;
    grid->addWidget(lUtenteLoggato,0,0); grid->addWidget(lUsername,0,1);
    grid->addWidget(lNome,1,0); grid->addWidget(lName,1,1);
    grid->addWidget(lCognome,2,0); grid->addWidget(lSurname,2,1);
    grid->addWidget(textUser,3,0); grid->addWidget(boxUsers,3,1);
    grid->addWidget(find,3,2); grid->addWidget(modifica,3,3);
    grid->addWidget(elimina,3,4);
    grid->addWidget(seeAll,4,2);
    grid->addWidget(tabellaUtenti,6,0,8,5);

    layoutAllUsers=new QVBoxLayout;
    layoutAllUsers->addLayout(grid);

    setLayout(layoutAllUsers);
}

void AllUsersView::buttonFind()
{
    modUser=users->getUser(textUser->text().toStdString());
    if (modUser){
        tabellaUtenti->addUser(modUser);
    }else tabellaUtenti->clearTable();
}

void AllUsersView::buttonSeeAll()
{
    tabellaUtenti->addAllUsers(users->getAllUser());
}

void AllUsersView::buttonModifica()
{
    if(modUser){
        modUserView=new ModificaUser(logUser,modUser);
        emit sAggiornaModificaUser(modUserView);
        emit sViewEnable();
        connect(modUserView,SIGNAL(finished(int)),this,SIGNAL(sViewEnable()));
        connect(modUserView,SIGNAL(finished(int)),this,SLOT(aggiornaView()));
        connect(modUserView,SIGNAL(v_changeUsername(User*,string)),this,SLOT(aggiornaViewChangeName()));
        modUserView->show();
    }else QMessageBox::warning(0,"Modifica non possibile","Non e' stato selezionato alcun utente da modificare");
}

void AllUsersView::buttonElimina()
{
    if(modUser) {
        if(modUser==logUser){
            emit sDeleteUser(modUser->getUsername());
            emit sDisconnetti();
        }else{
            emit sDeleteUser(modUser->getUsername());
            addUsersBox();
            aggiornaView();
        }
    }
    else QMessageBox::warning(0,"Eliminazione non riuscita","Non e' stato selezionato alcun utente da eliminare");
}

void AllUsersView::boxUserChange(QString name)
{
    modUser=users->getUser(name.toStdString(),true);
    emit sAggiornaModUserStatusBar(modUser);
    textUser->setText(name);
}

void AllUsersView::aggiornaView()
{
    emit sAggiornaModUserStatusBar(modUser);
    addUsersBox();
}

void AllUsersView::aggiornaViewChangeName()
{
    addUsersBox();
}

void AllUsersView::closeEvent()
{
    modUserView->close();
}

