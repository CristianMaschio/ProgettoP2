#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

using std::string;

class Item
{
    string name;
    string type; //All, Office, Process
    double price;
    int quantity;
    string pos;

public:
    Item(string nome="", string tipo="", double prezzo=0, int quant=0, string posizione="");

    string getName() const;
    string getType() const;
    double getPrice() const;
    int getQuantity() const;
    string getPos() const;

    void setType(const string &a);
    void setName(const string &a);
    void setPrice(const double &a);
    void setQuantity(const int &a);
    void setPos(const string& a);

    void loadItem(QXmlStreamReader& xmlReader, Item* app);
    void saveItem(QXmlStreamWriter& xmlWriter, const Item* app)const;

    bool operator ==(const Item&);
    Item* clone() const;
};

#endif // ITEM_H
