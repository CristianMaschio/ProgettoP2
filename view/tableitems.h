#ifndef TABLEITEMS_H
#define TABLEITEMS_H
#include <QTableView>
#include "model/allusers.h"
#include "model/warehouse.h"
#include <list>
#include <QStandardItemModel>
#include <QStandardItem>

class TableItems: public QTableView
{
    const User* logUser;
    const Warehouse* items;

    QStandardItemModel* model;
    QStandardItem* name;
    QStandardItem* type;
    QStandardItem* price;
    QStandardItem* quantity;
    QStandardItem* pos;

public:
    TableItems(const User* user, const Warehouse* allItem, QWidget *parent=0);

    void createTable();
    void setViewTable();

    void clearTable();
    void insertItem(const Item* item, int row=0);
    void addItem(const Item* item);
    void addAllItems(const list<Item*>& listItem);

    void setView();
    void setViewSeeAll();
};

#endif // TABLEITEMS_H
