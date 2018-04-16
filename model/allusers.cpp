#include "allusers.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QMessageBox>

const string AllUsers::xmlFile="Users.xml";

User *AllUsers::getUser(const string &name, bool check)
{
    User* a=NULL;
    for (list<User*>::const_iterator it=users.begin(); it!=users.end() && a==NULL; ++it)
    {
        if((*it)->getUsername()==name)
        {
            check=true;
            a=(*it);
        }
    }
    if(!check)QMessageBox::warning(0,"Utente non trovato","L'utente non e' esistente nel database");
    return a;
}

const list<User *> AllUsers::getAllUser()
{
    list<User *> app;
    for(list<User*>::const_iterator it=users.begin(); it!=users.end(); ++it)
    {
        app.push_back(*it);
    }
    return app;
}

void AllUsers::loadUsers()
{
    deleteList();
    QFile file(QString::fromStdString(xmlFile));
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNextStartElement();
        while (!xmlReader.atEnd())
        {
            User* app=NULL;
            if(xmlReader.name()=="Officeworker") app=new Officeworker;
            else if(xmlReader.name()=="Warehouseman") app=new Warehouseman;
            else if(xmlReader.name()=="Accountant") app=new Accountant;
            else if(xmlReader.name()=="Processworker") app=new Processworker;
            else if(xmlReader.name()=="Admin")app=new Admin;

            if (app)
            {
                app->loadUser(xmlReader);
                xmlReader.readNextStartElement();
                users.push_back(app);
            }
            xmlReader.readNextStartElement();//lettura prossimo utente
        }
    }else QMessageBox::warning(0,"Caricamento utenti non riuscito","Impossibile leggere gli utenti, il file Users.xml non e' stato trovato");
}

void AllUsers::deleteList()
{
    for (list<User*>::iterator it=users.begin(); it!=users.end(); ++it)
    {
        delete(*it);
        it=users.erase(it);
        --it;
    }
}

bool AllUsers::checkAdmin()
{
    for (list<User*>::iterator it=users.begin(); it!=users.end(); ++it)
    {
        if(dynamic_cast<Admin*>(*it))return true;
    }
    return false;
}

AllUsers::AllUsers()
{
    loadUsers();
}

const User *AllUsers::searchUser(const string &name, bool check) const
{
    User* a=NULL;
    for (list<User*>::const_iterator it=users.begin(); it!=users.end() && a==NULL; ++it)
    {
        if((*it)->getUsername()==name)
        {
            check=true;
            a=(*it);
        }
    }
    if(!check)QMessageBox::warning(0,"Utente non trovato","L'utente non e' esistente nel database");
    return a;
}

User* AllUsers::tryLog(const string &name, const string &password)
{

    if(!checkAdmin())
    {
        removeUser("admin",true);
        users.push_back(new Admin ("admin","admin","admin","admin"));
    }

    User* app=getUser(name, false);
    if (app)
    {
          if (app->getPassword()==password)return app;
          else QMessageBox::warning(0,"Inserimento Password","La password da lei digitata e' errata");
    }
    return 0;
}

void AllUsers::addUser(User *user)
{
    const User* a=searchUser(user->getUsername(),true);
    if(!a){
        users.push_back(user);
        QMessageBox::information(0,"Creazione Utente","La creazione dell'utente e' avvenuta con successo");
    }else QMessageBox::warning(0,"Creazione Utente non riuscita","L'utente da lei creato e' gia' esistente nel database");
}

void AllUsers::removeUser(const string &name, bool check)
{
    bool a=false;
    for (list<User*>::iterator it=users.begin(); it!=users.end() && a==false; ++it)
    {
        if((*it)->getUsername()==name)
        {
            delete(*it);
            it=users.erase(it);
            --it;
            a=true;
            if(!check)QMessageBox::information(0,"Eliminazione riuscita","La rimozione dell'utente e' avvenuta con successo");
        }
    }
    if(!a && !check) QMessageBox::warning(0,"Eliminazione non riuscita","L'utente da lei digitato non e' esistente nel database");
}

void AllUsers::changeUsername(User* user, const string &newUsername)
{
    const User* check=searchUser(newUsername,true);
    if(!check) {
        user->setUsername(newUsername);
        QMessageBox::information(0,"Modifica username riuscita","La modifica dell'username e' avvenuto con successo");
    }else QMessageBox::warning(0,"Modifica username non riuscita","L'username da lei digitato e' gia' esistente");
}

void AllUsers::changePassword(User* user, const string &newPassword)
{
    if(user){
        user->setPassword(newPassword);
        QMessageBox::information(0,"Modifica password riuscita","La modifica della password e' avvenuta con successo");
    }else QMessageBox::warning(0,"Modifica password non riuscita","Utente non trovato");
}

void AllUsers::changeName(User* user, const string &newName)
{
    if(user){
        user->setName(newName);
        QMessageBox::information(0,"Modifica del nome riuscita","La modifica del nome e' avvenuta con successo");
    }
    else QMessageBox::warning(0,"Modifica del nome non riuscita","Utente non trovato");
}

void AllUsers::changeSurname(User *user, const string &newSurname)
{
    if(user){
        user->setSurname(newSurname);
        QMessageBox::information(0,"Modifica del cognome riuscita","La modifica del cognome e' avvenuta con successo");
    }else QMessageBox::warning(0,"Modifica del cognome non riuscita","Utente non trovato");
}

void AllUsers::changeSkill(User *user, const int &newSkill)
{
    if(user){
        user->setSkill(newSkill);
        QMessageBox::information(0,"Modifica skill riuscita","La modifica delle skill e' avvenuta con successo");
    }else QMessageBox::warning(0,"Modifica skill non riuscita","Utente non trovato");
}

void AllUsers::changeType(User *newUserType)
{

    bool a=false;
    for (list<User*>::iterator it=users.begin(); it!=users.end() && a==false; ++it)
    {
        if((*it)->getUsername()==newUserType->getUsername())
        {
            delete *it;
            *it=newUserType;
            a=true;
            QMessageBox::information(0,"Modifica del tipo riuscita","La modifica del tipo e' avvenuta con successo");
        }
    }
    if(!a) QMessageBox::warning(0,"Modifica tipo non riuscita","L'utente non e' esistente nel database");
}

int AllUsers::getSize() const
{
    return users.size();
}

bool AllUsers::checkList() const
{
    return users.size()>0;
}

void AllUsers::saveUsers() const
{
    QFile file(QString::fromStdString(xmlFile));
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Users");
    for(list<User*>::const_iterator it=users.begin(); it!=users.end(); ++it)
    {
        (*it)->saveUser(xmlWriter);
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

AllUsers::~AllUsers()
{
    deleteList();
}
