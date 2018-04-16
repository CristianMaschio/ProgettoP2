#ifndef TABLEUSERS_H
#define TABLEUSERS_H
#include <QTableView>
#include "model/allusers.h"
#include <list>
#include <QStandardItemModel>
#include <QStandardItem>

class TableUsers: public QTableView
{
    QStandardItemModel* model;
    QStandardItem* username;
    QStandardItem* name;
    QStandardItem* surname;
    QStandardItem* skill;
    QStandardItem* type;

    const AllUsers* users;
public:
    TableUsers(const AllUsers* allUser, QWidget* parent=0);

    void createTable();

    void clearTable();

    void insertUser(const User* user, int row=0);
    void addUser(const User* user);
    void addAllUsers(const list<User*>& listUsers);
};

#endif // TABLEUSERS_H
