#ifndef WORKER_H
#define WORKER_H
#include "user.h"

class Worker: public User
{

public:
    Worker(string user="", string pass="", string n="", string s="", int sk=0);

    virtual Worker* clone()const=0;
    virtual void loadUser(QXmlStreamReader& xmlReader)=0;
    virtual void saveUser(QXmlStreamWriter& xmlWriter)const=0;
    virtual string getType()const=0;

    virtual string getItemAccess()const=0;

    virtual bool changeQuantity()const=0;
    virtual bool changeNameItem()const=0;
    virtual bool changeTypeItem()const=0;
    virtual bool changePosItem()const=0;
    virtual bool changePriceItem()const=0;
    virtual bool deleteItem()const=0;
    virtual bool insertNewItem()const=0;
};
#endif // WORKER_H
