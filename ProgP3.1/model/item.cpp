#include "item.h"
#include <QString>
#include <QMessageBox>

Item::Item(string nome, string tipo, double prezzo, int quant, string posizione): name(nome), type(tipo), price(prezzo), quantity(quant), pos(posizione)
{

}

string Item::getName() const
{
    return name;
}

string Item::getType() const
{
    return type;
}

double Item::getPrice() const
{
    return price;
}

int Item::getQuantity() const
{
    return quantity;
}

std::__cxx11::string Item::getPos() const
{
    return pos;
}

void Item::setType(const string &a)
{
    if(a=="Office" || a=="All" || a=="Process") type=a;
    else QMessageBox::warning(0,"Errore nel settaggio del tipo di Item","L'item puo' essere solamente di questi 3 tipi: 'Office','Process' o 'All'");
}

void Item::setName(const string& a)
{
    name=a;
}

void Item::setPrice(const double& a)
{
    price=a;
}

void Item::setQuantity(const int& a)
{
    quantity=a;
}

void Item::setPos(const std::__cxx11::string &a)
{
    pos=a;
}

void Item::loadItem(QXmlStreamReader &xmlReader, Item *app)
{
    xmlReader.readNextStartElement();
    if(xmlReader.name()=="Name") {
        app->setName(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Type") {
        app->setType(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Price") {
        app->setPrice(xmlReader.readElementText().toDouble());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Quantity") {
        app->setQuantity(xmlReader.readElementText().toInt());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Pos") app->setPos(xmlReader.readElementText().toStdString());
}

void Item::saveItem(QXmlStreamWriter &xmlWriter, const Item *app) const
{
    xmlWriter.writeTextElement("Name", QString::fromStdString(app->getName()) );
    xmlWriter.writeTextElement("Type", QString::fromStdString(app->getType()) );
    xmlWriter.writeTextElement("Price", QString::number(app->getPrice()) );
    xmlWriter.writeTextElement("Quantity", QString::number(app->getQuantity()) );
    xmlWriter.writeTextElement("Pos", QString::fromStdString(app->getPos()) );
}

bool Item::operator ==(const Item &a)
{
    return name==a.getName() && price==a.getPrice() && pos==a.getPos();
}

Item *Item::clone() const
{
    return new Item(*this);
}
