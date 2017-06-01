#include "itemscontroller.h"

ItemsController::ItemsController(Warehouse *Items, QObject *parent):QObject(parent),items(Items)
{

}

void ItemsController::aggiornaPuntatoreView(ModificaItem *puntModItemView)
{
    modItemView=puntModItemView;
    //connect..
    connect(modItemView,SIGNAL(sChangeName(Item*,string)),this,SLOT(changeName(Item*,string)));
    connect(modItemView,SIGNAL(sChangePos(Item*,string)),this,SLOT(changePos(Item*,string)));
    connect(modItemView,SIGNAL(sChangePrice(Item*,double)),this,SLOT(changePrice(Item*,double)));
    connect(modItemView,SIGNAL(sChangeType(Item*,string)),this,SLOT(changeType(Item*,string)));

    connect(modItemView,SIGNAL(sAddItem(Item)),this,SLOT(addItem(Item)));
}

void ItemsController::aggiornaItemsView(WarehouseView *itemView)
{
    itemsView=itemView;
    connect(itemsView,SIGNAL(sChangeQuantity(Item*,int)),this,SLOT(changeQuantity(Item*,int)));
    connect(itemsView,SIGNAL(sDeleteItem(string)),this,SLOT(deleteItem(string)));
}

void ItemsController::changeName(Item *item, string newName)
{
    items->changeName(item,newName);
}

void ItemsController::changePos(Item *item, string newPos)
{
    items->changePos(item,newPos);
}

void ItemsController::changePrice(Item *item, double newPrice)
{
    items->changePrice(item,newPrice);
}

void ItemsController::changeType(Item *item, string newType)
{
    items->changeType(item,newType);
}

void ItemsController::changeQuantity(Item *item, int quantity)
{
    items->changeQuantity(item,quantity);
}

void ItemsController::addItem(const Item &item)
{
    if(items->insertNewItem(item)) modItemView->close();
}

void ItemsController::deleteItem(const std::__cxx11::string &name)
{
    items->deleteItem(name);
}
