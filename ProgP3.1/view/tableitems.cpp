#include "tableitems.h"
#include <QLabel>

TableItems::TableItems(const User *user, const Warehouse *allItem, QWidget* parent):QTableView(parent),logUser(user),items(allItem)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    createTable();
    setModel(model);
    setView();
}

void TableItems::createTable()
{
    model=new QStandardItemModel(1,5,this);

    name=new QStandardItem("Nome");
    type=new QStandardItem("Tipo");
    price=new QStandardItem("Prezzo");
    quantity=new QStandardItem("Quantita'");
    pos=new QStandardItem("Posizione");

    model->setHorizontalHeaderItem(0,name);
    model->setHorizontalHeaderItem(1,type);
    model->setHorizontalHeaderItem(2,pos);
    model->setHorizontalHeaderItem(3,quantity);
    model->setHorizontalHeaderItem(4,price);
}

void TableItems::clearTable()
{
    model->clear();
    createTable();
}

void TableItems::insertItem(const Item *item, int row)
{
    if(item){
        model->setItem(row,0,new QStandardItem(QString::fromStdString(item->getName())));
        model->setItem(row,1,new QStandardItem(QString::fromStdString(item->getType())));
        model->setItem(row,2,new QStandardItem(QString::fromStdString(item->getPos())));
        model->setItem(row,3,new QStandardItem(QString::number(item->getQuantity())));
        model->setItem(row,4,new QStandardItem(QString::number(item->getPrice())));
    }
}

void TableItems::addItem(const Item *item)
{
    clearTable();
    model->setRowCount(1);
    insertItem(item);
    setModel(model);
    setView();
}

void TableItems::addAllItems(const list<Item *> &listItem)
{
    int i=0;
    clearTable();
    for(list<Item*>::const_iterator it=listItem.begin(); it!=listItem.end(); ++it)
    {
        insertItem((*it),i);
        i++;
    }
    setModel(model);
    setViewSeeAll();
}


void TableItems::setView()
{
    if(logUser->getType()!="Admin")
    {
        setColumnHidden(1,true);
        if(logUser->getType()!="Accountant")
        {
            setColumnHidden(4,true);
        }
    }
}

void TableItems::setViewSeeAll()
{
    setView();
    if(logUser->getType()!="Admin")
    {
        setColumnHidden(2,true);
    }
}
