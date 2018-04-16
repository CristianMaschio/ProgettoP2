#ifndef ADMIN_H
#define ADMIN_H
#include "warehouse.h"
#include "user.h"
#include "allusers.h"

class AllUsers;

class Admin: public User
{
    static const string itemAccess;
public:
    Admin(string user="", string pass="", string n="", string s="", int sk=0);

    virtual Admin* clone()const;
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

#endif // ADMIN_H
