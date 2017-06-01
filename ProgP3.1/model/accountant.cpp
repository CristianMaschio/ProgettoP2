#include "accountant.h"

const string Accountant::itemAccess="All";

Accountant::Accountant(string user, string pass, string n, string s, int sk):User(user,pass,n,s,sk)
{

}

Accountant *Accountant::clone() const
{
    return new Accountant(*this);
}

void Accountant::loadUser(QXmlStreamReader &xmlReader)
{
    loadBaseUser(xmlReader);
}

void Accountant::saveUser(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeStartElement("Accountant");
    saveBaseUser(xmlWriter);
}

string Accountant::getType() const
{
    return "Accountant";
}

string Accountant::getItemAccess() const
{
    return itemAccess;
}

bool Accountant::changeQuantity() const
{
    return true;
}

bool Accountant::changeNameItem() const
{
    return false;
}

bool Accountant::changeTypeItem() const
{
    return false;
}

bool Accountant::changePosItem() const
{
    return false;
}

bool Accountant::changePriceItem() const
{
    return true;
}

bool Accountant::deleteItem() const
{
    return false;
}

bool Accountant::insertNewItem() const
{
    return true;
}
