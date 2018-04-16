#include "admin.h"

const string Admin::itemAccess="All";

Admin::Admin(string user, string pass, string n, string s, int sk):
    User(user,pass,n,s,sk)
{

}

Admin *Admin::clone() const
{
    return new Admin (*this);
}

void Admin::loadUser(QXmlStreamReader &xmlReader)
{
    loadBaseUser(xmlReader);
}

void Admin::saveUser(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeStartElement("Admin");
    saveBaseUser(xmlWriter);
}

string Admin::getType() const
{
    return "Admin";
}

string Admin::getItemAccess() const
{
    return itemAccess;
}

bool Admin::changeQuantity() const
{
    return true;
}

bool Admin::changeNameItem() const
{
    return true;
}

bool Admin::changeTypeItem() const
{
    return true;
}

bool Admin::changePosItem() const
{
    return true;
}

bool Admin::changePriceItem() const
{
    return true;
}

bool Admin::deleteItem() const
{
    return true;
}

bool Admin::insertNewItem() const
{
    return true;
}
