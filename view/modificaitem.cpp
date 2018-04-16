#include "modificaitem.h"

void ModificaItem::createLayout()
{
    lName=new QLabel("Nome:");
    textName=new QLineEdit;
    textName->setValidator(new QRegExpValidator(QRegExp(".{1,14}")));
    textName->setPlaceholderText("Inserire nome");

    lPos=new QLabel("Posizione:");
    textPos=new QLineEdit;
    textPos->setValidator(new QRegExpValidator(QRegExp("[A-Z][0-9]{1,3}")));
    textPos->setPlaceholderText("Inserire pos. es: A123");
    //textPos->setAccessibleDescription("accetta:[A-Z][0-9] massima lunghezza 4");

    lPrice=new QLabel("Prezzo:");
    textPrice=new QLineEdit;
    textPrice->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,4}[.][0-9]{1,2}")));
    textPrice->setPlaceholderText("Inserire prezzo es: 1.29");

    lType=new QLabel("Tipo:");
    textType=new QComboBox;
    textType->addItem("All");
    textType->addItem("Office");
    textType->addItem("Process");

    grid=new QGridLayout;
    grid->addWidget(lName,0,0); grid->addWidget(textName,0,1);
    grid->addWidget(lPos,1,0); grid->addWidget(textPos,1,1);
    grid->addWidget(lPrice,2,0); grid->addWidget(textPrice,2,1);
    grid->addWidget(lType,3,0); grid->addWidget(textType,3,1);

    if(changeOrAdd && logUser->insertNewItem())createLayoutAdd();
    else if(item) createLayoutChange();

    setView();

    boxLayout=new QVBoxLayout;
    boxLayout->addLayout(grid);
    setLayout(boxLayout);
    setModal(true);
}

void ModificaItem::createLayoutChange()
{
    setWindowTitle(("Modifica Item: "+QString::fromStdString(item->getName())));

    textName->setText(QString::fromStdString(item->getName()));
    textPos->setText(QString::fromStdString(item->getPos()));
    textPrice->setText(QString::number(item->getPrice()));
    //textType->setCurrentText(QString::fromStdString(item->getType()));

    textType->setCurrentIndex(textType->findText(QString::fromStdString(item->getType())));

    changePos=new QPushButton("Cambia Posizione");
    changePrice=new QPushButton("Cambia Prezzo");
    changeType=new QPushButton("Cambia Tipo");
    changeName=new QPushButton("Cambia Nome");
    grid->addWidget(changeName,0,2);
    grid->addWidget(changePos,1,2);
    grid->addWidget(changePrice,2,2);
    grid->addWidget(changeType,3,2);
    //connect
    connect(changeName,SIGNAL(clicked(bool)),this,SLOT(bChangeName()));
    connect(changePos,SIGNAL(clicked(bool)),this,SLOT(bChangePos()));
    connect(changePrice,SIGNAL(clicked(bool)),this,SLOT(bChangePrice()));
    connect(changeType,SIGNAL(clicked(bool)),this,SLOT(bChangeType()));
}

void ModificaItem::createLayoutAdd()
{
    setWindowTitle("Aggiungi Item");
    lQuantity=new QLabel("Quantita':");
    textQuantity=new QLineEdit;
    textQuantity->setPlaceholderText("Inserisci la quantita'', max 100.000");
    textQuantity->setValidator(new QIntValidator(0,100000));
    addItem=new QPushButton("Crea item");
    grid->addWidget(lQuantity,4,0);
    grid->addWidget(textQuantity,4,1);
    grid->addWidget(addItem,5,1);
    //connect
    connect(addItem,SIGNAL(clicked(bool)),this,SLOT(bAddItem()));
}

void ModificaItem::setView()
{
    if(!logUser->changeTypeItem())
    {
        lType->hide();
        textType->hide();
        changeType->hide();
    }
    if(!logUser->changePosItem())
    {
        lPos->hide();
        textPos->hide();
        changePos->hide();
    }
    if(!logUser->changePriceItem())
    {
        lPrice->hide();
        textPrice->hide();
        changePrice->hide();
    }
    if(!logUser->changeNameItem())
    {
        lName->hide();
        textName->hide();
        changeName->hide();
    }
}

ModificaItem::ModificaItem(User *user, Item *oggetto, bool TforAdd):logUser(user), item(oggetto),changeOrAdd(TforAdd)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    createLayout();
}

bool ModificaItem::checkPrice()
{
    if(textPrice->text().toDouble()>0)return true;
    QMessageBox::warning(0,"Errore inserimento del prezzo","Il prezzo deve essere >0");
    textPrice->clear();
    return false;
}

bool ModificaItem::checkQuantity()
{
    if(textQuantity->text().toInt()>0)return true;
    QMessageBox::warning(0,"Errore inserimento della quantita'","La quantita' deve essere >0");
    textQuantity->clear();
    return false;
}

bool ModificaItem::checkPos()
{
    if(textPos->text()!="")return true;
    QMessageBox::warning(0,"Errore inserimento della posizione","La posizione non puo' essere vuota e deve iniziare con una lettera maiuscola seguita da numeri");
    textPos->clear();
    return false;
}

bool ModificaItem::checkName()
{
    if(textName->text()!="")return true;
    QMessageBox::warning(0,"Errore inserimento del nome","Il nome non puo' essere vuoto");
    textName->clear();
    return false;
}

void ModificaItem::bChangeName()
{
    emit sChangeName(item,textName->text().toStdString());//c'e' gia' una verifica nel database se il nome non sia gia' esistente
    emit sAggiornaName();
}

void ModificaItem::bChangePos()
{
    emit sChangePos(item,textPos->text().toStdString());
}

void ModificaItem::bChangePrice()
{
    if(checkPrice()){
        emit sChangePrice(item,textPrice->text().toDouble());
    }
}

void ModificaItem::bChangeType()
{
    emit sChangeType(item,textType->currentText().toStdString());
}

void ModificaItem::bAddItem()
{
    if(checkName()&&checkPrice()&&checkQuantity()&&checkPos())
    {
        emit sAddItem(Item(textName->text().toStdString(),textType->currentText().toStdString(),
                        textPrice->text().toDouble(),textQuantity->text().toInt(),textPos->text().toStdString()));
        emit aggiornaBox();
    }
}

