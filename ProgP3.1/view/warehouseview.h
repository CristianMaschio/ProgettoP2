#ifndef WAREHOUSEVIEW_H
#define WAREHOUSEVIEW_H
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <string>
#include "model/allusers.h"
#include "model/warehouse.h"
#include "tableitems.h"
#include "modificaitem.h"

#include <QTableWidget>

using std::string;

class WarehouseView: public QWidget
{
    Q_OBJECT
    User* logUser;
    Item* currentItem=NULL;
    Warehouse* items;

    QGridLayout* grid;
    QVBoxLayout* layoutWarehouse;

    QLabel* lUtenteLoggato;
    QLabel* lUsername;
    QLabel* lNome;
    QLabel* lName;
    QLabel* lCognome;
    QLabel* lSurname;
    QPushButton* cerca;
    QPushButton* findAll;
    QLineEdit* textItem;
    QComboBox* boxItem;

    QPushButton* modifica;
    QPushButton* elimina;
    QSpinBox* quantity;
    QPushButton* addRemove;
    TableItems* tabellaItem;
public:
    WarehouseView(User* users, Warehouse* Items, QWidget* parent=0);
    ModificaItem* modificaOggetto;

    void setLabel(QLabel *l);
    void createLayout();
    void setHide();
    void clear();
    void refresh();
    void createBox();
    void addItemTable(Item* app);
public slots:
    void findAllButton();
    void findItem();
    void boxItemChange(QString);
    void bAddRemove();
    void bDeleteItem();
signals:
    void changeItemStatBar(Item*);
    void sModificationItem();
    void sDeleteItem(const string&);
    void sChangeQuantity(Item*,int);
    void sViewEnable();
};

#endif // WAREHOUSEVIEW_H
