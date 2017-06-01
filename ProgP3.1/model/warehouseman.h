#ifndef WAREHOUSEMAN_H
#define WAREHOUSEMAN_H
#include "user.h"

class Warehouseman:public User
{
    static const string itemAccess;
public:
    Warehouseman(string user="", string pass="", string n="", string s="", int sk=0);


    virtual Warehouseman* clone()const;
    virtual void loadUser(QXmlStreamReader& xmlReader);
    virtual void saveUser(QXmlStreamWriter& xmlWriter)const;
    virtual string getType()const;

    virtual string getItemAccess()const;

    virtual bool changeQuantity()const;
    virtual bool changeNameItem()const;
    virtual bool changeTypeItem()const;
    virtual bool changePosItem()const;
    virtual bool changePriceItem()const;
    virtual bool deleteItem()const;
    virtual bool insertNewItem()const;
};

#endif // WAREHOUSEMAN_H

