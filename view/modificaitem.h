#ifndef MODIFICAITEM_H
#define MODIFICAITEM_H
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "model/allusers.h"
#include "model/warehouse.h"

class ModificaItem: public QDialog
{
    Q_OBJECT

    User* logUser;
    Item* item;
    bool changeOrAdd;   //falso per modificare, true per creare

    QLabel* lPos;
    QLineEdit* textPos;
    QPushButton* changePos;
    QLabel* lPrice;
    QLineEdit* textPrice;
    QPushButton* changePrice;
    QLabel* lName;
    QLineEdit* textName;
    QPushButton* changeName;
    QLabel* lType;
    QComboBox* textType;
    QPushButton* changeType;

    QLabel* lQuantity;
    QLineEdit* textQuantity;
    QPushButton* addItem;

    QGridLayout* grid;
    QVBoxLayout* boxLayout;

    void createLayout();

    void createLayoutChange();
    void createLayoutAdd();
    void setView();
public:
    ModificaItem(User* user, Item* oggetto=0, bool TforAdd=false);

    bool checkPrice();
    bool checkQuantity();
    bool checkPos();
    bool checkName();

public slots:
    void bChangeName();
    void bChangePos();
    void bChangePrice();
    void bChangeType();
    void bAddItem();

signals:
    void sChangeName(Item*,string);
    void sAggiornaName();
    void sChangePos(Item*,string);
    void sChangePrice(Item*,double);
    void sChangeType(Item*,string);
    void sAddItem(const Item&);

    void aggiornaBox();
};

#endif // MODIFICAITEM_H
