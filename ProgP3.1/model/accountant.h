#ifndef ACCOUNTANT_H
#define ACCOUNTANT_H
#include "user.h"

class Accountant: public User
{
    static const string itemAccess;
public:
    Accountant(string user="", string pass="", string n="", string s="", int sk=0);

    virtual Accountant* clone()const;
    virtual void loadUser(QXmlStreamReader& xmlReader);
    virtual void saveUser(QXmlStreamWriter& xmlWriter) const;
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

#endif // ACCOUNTANT_H
