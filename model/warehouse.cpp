#include "warehouse.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>

const string Warehouse::xmlFile="Items.xml";

void Warehouse::loadItems()
{
    deleteList();
    QFile file(QString::fromStdString(xmlFile));
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNext();
        while (!xmlReader.atEnd())
        {
            Item* app=NULL;
            if (xmlReader.name()=="Item"){
                app=new Item;
                app->loadItem(xmlReader,app);
                xmlReader.readNextStartElement();
                items.push_back(app);
            }
            xmlReader.readNextStartElement();//lettura prossimo utente
        }
    }else QMessageBox::warning(0,"Errore lettura oggetti","Impossibile leggere gli oggetti, non è stato trovato il file Items.xml");
}

bool Warehouse::checkType(const string &typeItem, const string &type2) const
{
    return(type2=="All"||type2==typeItem||"All"==typeItem);
}

void Warehouse::deleteList()
{
    for (list<Item *>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        delete(*it);
        it=items.erase(it);
        --it;
    }
}

Warehouse::Warehouse()
{
    loadItems();
}

void Warehouse::setLogUser(User *LogUser)
{
    logUser=LogUser;
}

const list<Item *> Warehouse::getAllItems(const string &type) const
{
    list<Item *> app;
    for(list<Item *>::const_iterator it=items.begin(); it!=items.end(); ++it)
    {
        if(checkType((*it)->getType(),type))
        {
           app.push_back(*it);
        }
    }
    return app;
}

const Item *Warehouse::searchItem(const string &name, const string &type, bool check) const
{
    Item* a=NULL;
    for(list<Item *>::const_iterator it=items.begin(); it!=items.end(); ++it)
    {
        if((*it)->getName()==name && checkType((*it)->getType(),type))
        {
            a=(*it);
            check=true;
        }
    }

    if(!check) QMessageBox::warning(0,"Item non trovato","L'item da lei digitato non e' stato trovato nel database");
    return a;
}

Item *Warehouse::getItem(const string &name, const string &type, bool check)
{
    Item* a=NULL;
    for(list<Item *>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        if((*it)->getName()==name && checkType((*it)->getType(),type))
        {
            a=(*it);
            check=true;
        }
    }
    if(!check) QMessageBox::warning(0,"Item non trovato","L'item da lei digitato non e' stato trovato nel database");
    return a;
}

bool Warehouse::insertNewItem(const Item &item)
{
    bool check=false;
    if (dynamic_cast<Admin*>(logUser))
    {
        Item* i=item.clone();
        const Item* a=searchItem(item.getName(),"All",true);
        if(a)//item esistente
        {
            QMessageBox::warning(0,"Errore di inserimento","L'item con quel nome e' gia' esistente nel database");
            delete i;
        }else {
            items.push_back(i); //item non esistente -> lo inserisco
            check=true;
            QMessageBox::information(0,"Inserimento item","L'inserimento dell'item e' avvenuto con successo");
        }
    }else{
    QMessageBox::warning(0,"Inserimento item non riuscito","L'oggetto puo' essere inserito solo dall'admin.");
    }
    return check;
}

void Warehouse::deleteItem(const string &name)
{
    if (dynamic_cast<Admin*>(logUser))
    {
        bool check=false;
        for(list<Item *>::iterator it=items.begin(); it!=items.end() && !check; ++it)
        {
            if((*it)->getName()==name)
            {
                delete (*it);
                it=items.erase(it);
                --it;
                check=true;
                QMessageBox::information(0,"Eliminazione riuscita","L'eliminazione e' avvenuta con successo");
            }
        }
        if(!check)QMessageBox::warning(0,"Eliminazione non riuscita","L'item con quel nome non esiste nel database");
    }else{
        QMessageBox::warning(0,"Eliminazione non riuscita","L'oggetto puo' essere eliminato solo dall'admin.");
    }
}

void Warehouse::changeQuantity(Item* app, int &quantity)
{
    if(logUser->changeQuantity())
    {
        if(app)
        {
            if( (app->getQuantity()+quantity)>=0 )
            {
                app->setQuantity(app->getQuantity()+quantity);
                if(quantity>=0) QMessageBox::information(0,"Modifica della quantita' riuscita","L'oggetto selezionato e' stato aumentato di: "+QString::number(quantity)+" unita'");
                else QMessageBox::information(0,"Modifica della quantita' riuscita","L'oggetto selezionato e' stato diminuito di: "+QString::number(quantity)+" unita'");

            }else{
                QMessageBox::warning(0,"Modifica alla quantita' non risucita","La riserva in magazzino e' minore della quantita' da prelevare");
            }
        }
    }else QMessageBox::warning(0,"Modifica alla quantita' non riuscita","L'utente corrente non e' abilitato a modificarla");
}

void Warehouse::changeName(Item *item, const string &newName)
{
    if(logUser->changeNameItem())
    {
        const Item* a=searchItem(newName, "All",true);
        if (a)QMessageBox::warning(0,"Impossibile modificare il nome","Il nome da lei digitato e' gia' esistente");
        else {
            if(item) item->setName(newName); //inserimento avvenuto con successo
            QMessageBox::information(0,"Modifica nome","La modifica al nome e' avvenuta con successo");
        }
    }else QMessageBox::warning(0,"Modifica al nome non riuscito","L'utente corrente non e' abilitato a modificare il nome");
}

void Warehouse::changeType(Item* item, const string &type)
{
    if(logUser->changeTypeItem())
    {
        if(item)
        {
            item->setType(type);
            QMessageBox::information(0,"Modifica","La modifica e' avvenuta con successo");
        }else QMessageBox::warning(0,"Modifica del tipo non riuscita","Item non trovato");
    }else QMessageBox::warning(0,"Modifica al tipo non riuscita","L'utente corrente non e' abilitato a modificare il tipo");
}

void Warehouse::changePos(Item* item,const string &pos)
{
    if(logUser->changePosItem())
    {
        if(item)
        {
            item->setPos(pos);
            QMessageBox::information(0,"Modifica","La modifica e' avvenuta con successo");
        }else QMessageBox::warning(0,"Modifica della posizione non riuscita","Item non trovato");
    }else QMessageBox::warning(0,"Modifica al tipo non riuscita","L'utente corrente non e' abilitato a modificare il tipo");

}

void Warehouse::changePrice(Item* item, double &price)
{
    if(logUser->changePriceItem())
    {
        if(item)
        {
            item->setPrice(price);
            QMessageBox::information(0,"Modifica","La modifica e' avvenuta con successo");
        }else QMessageBox::warning(0,"Modifica del prezzo non riuscito","Item non trovato");
    }else QMessageBox::warning(0,"Modifica al tipo non riuscita","L'utente corrente non e' abilitato a modificare il tipo");

}

void Warehouse::saveItems() const
{
    QFile file(QString::fromStdString(xmlFile));
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Items");
    for(list<Item *>::const_iterator it=items.begin(); it!=items.end(); ++it)
    {
        xmlWriter.writeStartElement("Item");
        (*it)->saveItem(xmlWriter,(*it));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

Warehouse::~Warehouse()
{
    deleteList();
}
