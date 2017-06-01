#include "officeworker.h"

const string Officeworker::itemAccess="Office";

Officeworker::Officeworker(string user, string pass, string n, string s, int sk):Worker(user,pass,n,s,sk)
{

}

Officeworker *Officeworker::clone() const
{
    return new Officeworker(*this);
}

void Officeworker::loadUser(QXmlStreamReader &xmlReader)
{
    loadBaseUser(xmlReader);
}

void Officeworker::saveUser(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeStartElement("Officeworker");
    saveBaseUser(xmlWriter);
}

string Officeworker::getType() const
{
    return "Officeworker";
}

string Officeworker::getItemAccess() const
{
    return itemAccess;
}

bool Officeworker::changeQuantity() const
{
    return true;
}

bool Officeworker::changeNameItem() const
{
    return false;
}

bool Officeworker::changeTypeItem() const
{
    return false;
}

bool Officeworker::changePosItem() const
{
    return false;
}

bool Officeworker::changePriceItem() const
{
    return false;
}

bool Officeworker::deleteItem() const
{
    return false;
}

bool Officeworker::insertNewItem() const
{
    return false;
}
