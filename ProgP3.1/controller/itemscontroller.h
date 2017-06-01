#ifndef ITEMSCONTROLLER_H
#define ITEMSCONTROLLER_H
#include <QObject>
#include "model/warehouse.h"
#include "model/allusers.h"
#include "view/modificaitem.h"
#include "view/warehouseview.h"

class ItemsController: public QObject
{
    Q_OBJECT
    Warehouse* items;

    ModificaItem* modItemView;
    WarehouseView* itemsView;
public:
    ItemsController(Warehouse* Items,QObject* parent=0);
    void aggiornaPuntatoreView(ModificaItem* puntModItemView);
    void aggiornaItemsView(WarehouseView* itemView);

public slots:
    void changeName(Item*,string);
    void changePos(Item*,string);
    void changePrice(Item*,double);
    void changeType(Item*,string);
    void changeQuantity(Item*,int);

    void addItem(const Item&);
    void deleteItem(const string&);
};

#endif // ITEMSCONTROLLER_H
