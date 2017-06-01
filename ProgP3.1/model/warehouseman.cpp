#include "warehouseman.h"

const string Warehouseman::itemAccess="All";

Warehouseman::Warehouseman(string user, string pass, string n, string s, int sk):
    User(user,pass,n,s,sk)
{

}

Warehouseman* Warehouseman::clone() const
{
    return new Warehouseman(*this);
}

void Warehouseman::loadUser(QXmlStreamReader &xmlReader)
{
    loadBaseUser(xmlReader);
}

void Warehouseman::saveUser(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeStartElement("Warehouseman");
    saveBaseUser(xmlWriter);
}

string Warehouseman::getType() const
{
    return("Warehouseman");
}

string Warehouseman::getItemAccess() const
{
    return itemAccess;
}

bool Warehouseman::changeQuantity() const
{
    return true;
}

bool Warehouseman::changeNameItem() const
{
    return false;
}

bool Warehouseman::changeTypeItem() const
{
    return false;
}

bool Warehouseman::changePosItem() const
{
    return true;
}

bool Warehouseman::changePriceItem() const
{
    return false;
}

bool Warehouseman::deleteItem() const
{
    return false;
}

bool Warehouseman::insertNewItem() const
{
    return false;
}

