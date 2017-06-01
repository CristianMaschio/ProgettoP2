#include "tableusers.h"

TableUsers::TableUsers(const AllUsers* allUser,QWidget *parent):QTableView(parent),users(allUser)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    createTable();
    setModel(model);
}

void TableUsers::createTable()
{
    model=new QStandardItemModel(1,4,this);

    username=new QStandardItem("Username");
    name=new QStandardItem("Nome");
    surname=new QStandardItem("Cognome");
    skill=new QStandardItem("Abilita'");
    type=new QStandardItem("Tipo");

    model->setHorizontalHeaderItem(0,username);
    model->setHorizontalHeaderItem(1,name);
    model->setHorizontalHeaderItem(2,surname);
    model->setHorizontalHeaderItem(3,skill);
    model->setHorizontalHeaderItem(4,type);
}

void TableUsers::clearTable()
{
    model->clear();
    createTable();
}

void TableUsers::insertUser(const User *user, int row)
{
    if(user){
        model->setItem(row,0,new QStandardItem(QString::fromStdString(user->getUsername())));
        model->setItem(row,1,new QStandardItem(QString::fromStdString(user->getName())));
        model->setItem(row,2,new QStandardItem(QString::fromStdString(user->getSurname())));
        model->setItem(row,3,new QStandardItem(QString::number(user->getSkill())));
        model->setItem(row,4,new QStandardItem(QString::fromStdString(user->getType())));
    }
}

void TableUsers::addUser(const User *user)
{
    clearTable();
    model->setRowCount(1);
    insertUser(user);
    setModel(model);
}

void TableUsers::addAllUsers(const list<User *> &listUsers)
{
    int i=0;
    clearTable();
    for(list<User*>::const_iterator it=listUsers.begin(); it!=listUsers.end(); ++it)
    {
        insertUser((*it),i);
        i++;
    }
    setModel(model);
}

