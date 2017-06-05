#include "userscontroller.h"
#include <QMessageBox>

bool UsersController::isAdmin()
{
    return dynamic_cast<Admin*>(logUser);
}

UsersController::UsersController(AllUsers *allUsers, QObject* parent):QObject(parent),users(allUsers)
{

}

void UsersController::aggiornaModificaUser(ModificaUser *mUser)
{
    modUserView=mUser;
    connect(modUserView,SIGNAL(v_changeUsername(User*,string)),this,SLOT(changeUsername(User*,string)));
    connect(modUserView,SIGNAL(v_changePassword(User*,string)),this,SLOT(changePassword(User*,string)));
    connect(modUserView,SIGNAL(v_changeName(User*,string)),this,SLOT(changeName(User*,string)));
    connect(modUserView,SIGNAL(v_changeSurname(User*,string)),this,SLOT(changeSurname(User*,string)));
    connect(modUserView,SIGNAL(v_changeSkill(User*,int)),this,SLOT(changeSkill(User*,int)));
    connect(modUserView,SIGNAL(v_addUser(User*)),this,SLOT(addUser(User*)));
    connect(modUserView,SIGNAL(v_changeType(User*)),this,SLOT(changeType(User*)));
}

void UsersController::aggiornaLogUser(User *LogUser)
{
    logUser=LogUser;
}

void UsersController::aggiornaViewUsers(AllUsersView *aggViewUsers)
{
    viewUsers=aggViewUsers;
    connect(viewUsers,SIGNAL(sDeleteUser(string)),this,SLOT(removeUser(string)));
}

void UsersController::addUser(User *newUser)
{
    if(isAdmin()){
        if(!users->searchUser(newUser->getUsername(),true))modUserView->close();
        users->addUser(newUser);
    }else{
        QMessageBox::warning(0,"Errore creazione utente","L'Utente attualmente loggato non autorizzato a creare utenti");
    }
}

void UsersController::removeUser(const string & username)
{
    users->removeUser(username);
}

void UsersController::changeUsername(User *modUser, const string & newUsername)
{
    if(logUser==modUser)users->changeUsername(logUser,newUsername);
    else{
        if(dynamic_cast<Admin*>(logUser)){
            users->changeUsername(modUser,newUsername);
        }else{
            QMessageBox::warning(0,"Errore cambio username","Utente non autorizzato a cambiare l'username");
        }
    }
}

void UsersController::changePassword(User *modUser, const string &newPassword)
{
    if(logUser==modUser)logUser->setPassword(newPassword);
    else{
        if(dynamic_cast<Admin*>(logUser)){
            users->changePassword(modUser,newPassword);
        }else{
            QMessageBox::warning(0,"Errore cambio password","Utente non autorizzato a cambiare la password");
        }
    }
}

void UsersController::changeName(User *modUser, const string &newName)
{
    if(isAdmin()){
        users->changeName(modUser,newName);
    }else{
        QMessageBox::warning(0,"Errore cambio nome","Utente non autorizzato a cambiare il nome");
    }
}

void UsersController::changeSurname(User *modUser, const string &newSurname)
{
    if(isAdmin()){
        users->changeSurname(modUser,newSurname);
    }else{
        QMessageBox::warning(0,"Errore cambio cognome","Utente non autorizzato a cambiare il cognome");
    }
}

void UsersController::changeSkill(User *modUser, const int skill)
{
    if(isAdmin()){
        users->changeSkill(modUser,skill);
    }else{
        QMessageBox::warning(0,"Errore cambio skill","Utente non autorizzato a cambiare la skill");
    }
}

void UsersController::changeType(User * newUserType)
{
    if(isAdmin()){
        users->changeType(newUserType);
    }else{
        QMessageBox::warning(0,"Errore cambio tipo","Utente non autorizzato a cambiare il tipo");
    }
}
