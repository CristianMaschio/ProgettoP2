#include "processworker.h"

const string Processworker::itemAccess="Process";

Processworker::Processworker(string user, string pass, string n, string s, int sk):Worker(user,pass,n,s,sk)
{

}

Processworker *Processworker::clone() const
{
    return new Processworker(*this);
}

void Processworker::loadUser(QXmlStreamReader &xmlReader)
{
    loadBaseUser(xmlReader);
}

void Processworker::saveUser(QXmlStreamWriter &xmlWriter)const
{
    xmlWriter.writeStartElement("Processworker");
    saveBaseUser(xmlWriter);
}

string Processworker::getType() const
{
    return "Processworker";
}

string Processworker::getItemAccess() const
{
    return itemAccess;
}

bool Processworker::changeQuantity() const
{
    return true;
}

bool Processworker::changeNameItem() const
{
    return false;
}

bool Processworker::changeTypeItem() const
{
    return false;
}

bool Processworker::changePosItem() const
{
    return false;
}

bool Processworker::changePriceItem() const
{
    return false;
}

bool Processworker::deleteItem() const
{
    return false;
}

bool Processworker::insertNewItem() const
{
    return false;
}

