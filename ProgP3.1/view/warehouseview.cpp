#include "warehouseview.h"
#include <QMessageBox>
#include <typeinfo>
#include <QFont>

void WarehouseView::createBox()
{
    list<Item*> app;
    app=items->getAllItems(logUser->getItemAccess());
    boxItem->clear();
    boxItem->addItem("");
    for(list<Item*>::const_iterator it=app.begin(); it!=app.end(); ++it)
    {
        boxItem->addItem(QString::fromStdString((*it)->getName()));
    }
}

WarehouseView::WarehouseView(User *users, Warehouse *Items, QWidget *parent):
    QWidget(parent), logUser(users), items(Items)
{
    createLayout();
}

void WarehouseView::setLabel(QLabel* l)
{
    //l->setFont(font);
    l->setFixedHeight(15);
}

void WarehouseView::createLayout()
{
    lUtenteLoggato=new QLabel;
    lUtenteLoggato->setText("Utente loggato:");
    setLabel(lUtenteLoggato);
    lUsername=new QLabel;
    setLabel(lUsername);
    lUsername->setText(QString::fromStdString(logUser->getUsername()));

    lNome=new QLabel;
    lNome->setText("Nome:");
    setLabel(lNome);
    lName=new QLabel;
    setLabel(lName);
    lName->setText(QString::fromStdString(logUser->getName()));

    lCognome=new QLabel;
    setLabel(lCognome);
    lCognome->setText("Cognome:");
    lSurname=new QLabel;
    setLabel(lSurname);
    lSurname->setText(QString::fromStdString(logUser->getSurname()));

    textItem=new QLineEdit;
    textItem->setPlaceholderText("Inserisci nome oggetto");
    textItem->setFixedWidth(100);
    textItem->setValidator(new QRegExpValidator(QRegExp(".{1,14}")));
    boxItem=new QComboBox;
    createBox();
    connect(boxItem,SIGNAL(currentIndexChanged(QString)),this,SLOT(boxItemChange(QString)));

    cerca=new QPushButton;
    cerca->setText("Cerca");
    connect(cerca,SIGNAL(clicked(bool)),this,SLOT(findItem()));

    findAll=new QPushButton;
    findAll->setText("Visualizza tutti");
    connect(findAll,SIGNAL(clicked()),this,SLOT(findAllButton()));

    quantity=new QSpinBox;
    quantity->setFixedWidth(45);
    quantity->setMinimum(-100);
    quantity->setMaximum(100);
    addRemove=new QPushButton;
    addRemove->setText("Preleva/Deposita");
    connect(addRemove,SIGNAL(clicked(bool)),this,SLOT(bAddRemove()));

    elimina=new QPushButton;
    elimina->setText("Elimina");
    connect(elimina,SIGNAL(clicked(bool)),this,SLOT(bDeleteItem()));

    modifica=new QPushButton;
    modifica->setText("Modifica");
    connect(modifica,SIGNAL(clicked(bool)),this,SIGNAL(sModificationItem()));//Il segnale arriva nel LogMainView


    tabellaItem=new TableItems(logUser,items);

    grid=new QGridLayout;
    grid->addWidget(lUtenteLoggato,0,0); grid->addWidget(lUsername,0,1);
    grid->addWidget(lNome,1,0); grid->addWidget(lName,1,1);
    grid->addWidget(lCognome,2,0); grid->addWidget(lSurname,2,1);
    grid->addWidget(textItem,3,0); grid->addWidget(boxItem,3,1);
    grid->addWidget(cerca,3,2); grid->addWidget(quantity,3,3);
    grid->addWidget(addRemove,3,4); grid->addWidget(elimina,4,5);
    grid->addWidget(findAll,4,2); grid->addWidget(modifica,3,5);
    grid->addWidget(tabellaItem,6,0,8,6);

    layoutWarehouse=new QVBoxLayout;
    layoutWarehouse->addLayout(grid);
    setHide();


    setLayout(layoutWarehouse);
}

void WarehouseView::setHide()
{
    if (!dynamic_cast<const Admin*>(logUser))
    {
        elimina->hide();
    }
    if (!logUser->changeNameItem() && !logUser->changePosItem() && !logUser->changePriceItem()
            && !logUser->changeTypeItem()) modifica->hide();
}

void WarehouseView::clear()
{
    textItem->clear();
    quantity->clear();
}

void WarehouseView::refresh()
{
    lUsername->setText(QString::fromStdString(logUser->getUsername()));
    lName->setText(QString::fromStdString(logUser->getName()));
    lSurname->setText(QString::fromStdString(logUser->getSurname()));
}

void WarehouseView::findAllButton()
{
    tabellaItem->addAllItems(items->getAllItems(logUser->getItemAccess()));
}

void WarehouseView::findItem()
{
    currentItem=items->getItem(textItem->text().toStdString(),logUser->getItemAccess());
    emit changeItemStatBar(currentItem);
    if(currentItem){
        tabellaItem->addItem(currentItem);
    }
}

void WarehouseView::boxItemChange(QString name)
{
    currentItem=items->getItem(name.toStdString(),logUser->getItemAccess(),true);
    emit changeItemStatBar(currentItem);
    textItem->setText(name);
}

void WarehouseView::bAddRemove()
{
    if(currentItem)
    {
        emit sChangeQuantity(currentItem,quantity->text().toInt());
        tabellaItem->addItem(currentItem);//refresh oggetto
    }else QMessageBox::warning(0,"Modifica della quantita' non riuscita","L'oggetto attualmente selezionato e' inesistente, selezionalo dalla lista o esegui la ricerca per compiere modifiche");
}

void WarehouseView::bDeleteItem()
{
    if(currentItem)
    {
        QString app=QString::fromStdString(currentItem->getName());
        emit sDeleteItem(currentItem->getName());
        //boxItem->setCurrentText(app);

        boxItem->setCurrentIndex(boxItem->findText(app));

        boxItem->removeItem(boxItem->currentIndex());
        currentItem=NULL;
        emit changeItemStatBar(currentItem);
    }else QMessageBox::warning(0,"Eliminazione non riuscita","L'oggetto attualmente selezionato e' inesistente, selezionalo dalla lista o esegui la ricerca per compiere modifiche");

}

