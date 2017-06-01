#include "user.h"
#include <QMessageBox>

User::User(string user, string pass, string n, string s, int sk)
{
    setUsername(user); setPassword(pass); setName(n); setSurname(s);
    setSkill(sk);
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

string User::getName() const
{
    return name;
}

string User::getSurname() const
{
    return surname;
}

int User::getSkill() const
{
    return skill;
}

void User::setUsername(const string& user)
{
    username=user;
}

void User::setPassword(const string& pass)
{
    password=pass;
}

void User::setName(const string& n)
{
    name=n;
}

void User::setSurname(const string& s)
{
    surname=s;
}

void User::setSkill(const int& s)
{
    skill=s;
}

void User::loadBaseUser(QXmlStreamReader &xmlReader)
{
    xmlReader.readNextStartElement();
    if(xmlReader.name()=="NomeUtente") {
        setUsername(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Password") {
        setPassword(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Name") {
        setName(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Surname") {
        setSurname(xmlReader.readElementText().toStdString());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="Skill") setSkill(xmlReader.readElementText().toInt());
}

void User::saveBaseUser(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeTextElement("NomeUtente",QString::fromStdString(getUsername()));
    xmlWriter.writeTextElement("Password",QString::fromStdString(getPassword()));
    xmlWriter.writeTextElement("Name",QString::fromStdString(getName()));
    xmlWriter.writeTextElement("Surname",QString::fromStdString(getSurname()));
    xmlWriter.writeTextElement("Skill",QString::number(getSkill()));

}
