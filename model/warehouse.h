#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "item.h"
#include <list>
#include "allusers.h"
#include <QTableWidget>

using std::list;

//"Database Item"
class Warehouse
{
private:
    static const string xmlFile;
    list <Item*> items;
    User* logUser=NULL;

    bool checkType(const string& typeItem, const string& type2) const;
    void deleteList();

public:
    Warehouse();
    void setLogUser(User* LogUser);

    void loadItems();
    const list<Item*> getAllItems(const string& type) const;
    const Item *searchItem(const string& name, const string &type, bool check=false) const;
    Item* getItem(const string& name, const string &type, bool check=false);

    bool insertNewItem(const Item& item);
    void deleteItem(const string& name);

    void changeQuantity(Item *app, int& quantity);

    void changeName(Item* item, const string& newName);
    void changeType(Item* item, const string& type);
    void changePos(Item* item, const string& pos);
    void changePrice(Item* item, double& price);

    void saveItems() const;
    ~Warehouse();
};

#endif // WAREHOUSE_H
