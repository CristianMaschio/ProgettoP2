#ifndef OFFICEWORKER_H
#define OFFICEWORKER_H
#include "worker.h"

class Officeworker: public Worker
{
    static const string itemAccess;
public:
    Officeworker(string user="", string pass="", string n="", string s="", int sk=0);

    virtual Officeworker* clone()const;
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

#endif // OFFICEWORKER_H
