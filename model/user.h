#ifndef USER_H
#define USER_H
#include <string>
#include "item.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <list>
#include <QMessageBox>

using std::string;

class User
{
    string username;
    string password;
    string name;
    string surname;
    int skill;

public:
    User(string user="", string pass="", string n="", string s="", int sk=0);

    string getUsername()const;
    string getPassword()const;
    string getName()const;
    string getSurname()const;
    int getSkill() const;

    void setUsername(const string& );
    void setPassword(const string& );
    void setName(const string& );
    void setSurname(const string& );
    void setSkill(const int& );

    virtual User* clone()const=0;
    void loadBaseUser(QXmlStreamReader& xmlReader);
    void saveBaseUser(QXmlStreamWriter& xmlWriter)const;
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


    virtual ~User(){}
};

#endif // USER_H
