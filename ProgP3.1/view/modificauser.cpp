#include "modificauser.h"
#include <QRegExp>

ModificaUser::ModificaUser(User *LogUser, User *ModUser, bool fChangeOrVAdd):logUser(LogUser),changeOrAdd(fChangeOrVAdd)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    if(ModUser==NULL)modUser=LogUser;
    else modUser=ModUser;

    createLayoutStandard();
    if(changeOrAdd)
    {
        setWindowTitle("Aggiungi Utente");
        createLayoutAdd();
    }else {
        setWindowTitle("Modifica Utente: "+ QString::fromStdString(modUser->getUsername()));
        createLayoutChange();
    }
    setModal(true);
}

void ModificaUser::createLayoutStandard()
{
    lUsername=new QLabel("Username:");
    username=new QLineEdit;
    username->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,14}")));
    username->setPlaceholderText("Inserisci username");

    lNewPassword=new QLabel("Password:");
    newPassword=new QLineEdit;
    newPassword->setEchoMode(QLineEdit::Password);
    newPassword->setValidator(new QRegExpValidator(QRegExp(".{1,14}")));
    newPassword->setPlaceholderText("Inserisci nuova password");
    confirmNewPassword=new QLineEdit;
    confirmNewPassword->setEchoMode(QLineEdit::Password);
    confirmNewPassword->setValidator(new QRegExpValidator(QRegExp(".{1,14}")));
    confirmNewPassword->setPlaceholderText("Conferma password");

    lName=new QLabel("Nome:");
    name=new QLineEdit;
    name->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,14}")));
    name->setPlaceholderText("Inserisci nome");

    lSurname=new QLabel("Cognome:");
    surname=new QLineEdit;
    surname->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,14}")));
    surname->setPlaceholderText("Inserischi cognome");

    lSkill=new QLabel("Abilita':");
    skill=new QLineEdit;
    skill->setValidator(new QIntValidator(0,100));
    skill->setPlaceholderText("Inserisci valore abilita'");

    selectType=new QLabel("Seleziona il tipo:");
    typeUser=new QComboBox;
    typeUser->addItem("Processworker");
    typeUser->addItem("Officeworker");
    typeUser->addItem("Warehouseman");
    typeUser->addItem("Accountant");
    typeUser->addItem("Admin");

    gridLayout= new QGridLayout;
    gridLayout->addWidget(lUsername,0,0); gridLayout->addWidget(username,0,1);
    gridLayout->addWidget(lNewPassword,1,0); gridLayout->addWidget(newPassword,1,1);
    gridLayout->addWidget(confirmNewPassword,2,1);
    gridLayout->addWidget(lName,3,0); gridLayout->addWidget(name,3,1);
    gridLayout->addWidget(lSurname,4,0); gridLayout->addWidget(surname,4,1);
    gridLayout->addWidget(lSkill,5,0); gridLayout->addWidget(skill,5,1);
    gridLayout->addWidget(selectType,6,0);
    gridLayout->addWidget(typeUser,6,1);
}

void ModificaUser::createLayoutChange()
{
    if(modUser){
        username->setText(QString::fromStdString(modUser->getUsername()));
        name->setText(QString::fromStdString(modUser->getName()));
        surname->setText(QString::fromStdString(modUser->getSurname()));
        skill->setText(QString::number(modUser->getSkill()));
        //typeUser->setCurrentText(QString::fromStdString(modUser->getType()));

        typeUser->setCurrentIndex(typeUser->findText(QString::fromStdString(modUser->getType())));
    }

    changeUsername=new QPushButton("Cambia Username");
    changePassword=new QPushButton("Cambia password");
    changeName=new QPushButton("Cambia Nome");
    changeSurname=new QPushButton("Cambia Cognome");
    changeSkill=new QPushButton("Cambia Abilita'");
    changeType=new QPushButton("Cambia tipo");

    gridLayout->addWidget(changeUsername,0,2);
    gridLayout->addWidget(changePassword,1,2);
    gridLayout->addWidget(changeName,3,2);
    gridLayout->addWidget(changeSurname,4,2);
    gridLayout->addWidget(changeSkill,5,2);
    gridLayout->addWidget(changeType,6,2);

    connect(changeUsername,SIGNAL(clicked(bool)),this,SLOT(bChangeUsername()));
    connect(changePassword,SIGNAL(clicked(bool)),this,SLOT(bChangePassword()));
    connect(changeName,SIGNAL(clicked(bool)),this,SLOT(bChangeName()));
    connect(changeSurname,SIGNAL(clicked(bool)),this,SLOT(bChangeSurname()));
    connect(changeSkill,SIGNAL(clicked(bool)),this,SLOT(bChangeSkill()));
    connect(changeType,SIGNAL(clicked(bool)),this,SLOT(bChangeType()));

    setViewChange();

}

void ModificaUser::createLayoutAdd()
{
    createUser=new QPushButton("Crea Utente");

    gridLayout->addWidget(createUser,7,1);

    connect(createUser,SIGNAL(clicked(bool)),this,SLOT(bAddUser()));

    setViewAdd();
    setLayout(boxLayout);
}


void ModificaUser::setViewChange()
{
    boxLayout=new QVBoxLayout;
    boxLayout->addLayout(gridLayout);
    if(!dynamic_cast<const Admin*>(logUser))
    {
        lSkill->hide();
        skill->hide();
        changeSkill->hide();

        lSurname->hide();
        surname->hide();
        changeSurname->hide();

        lName->hide();
        name->hide();
        changeName->hide();

        typeUser->hide();
        changeType->hide();
        selectType->hide();
    }else if(logUser==modUser){
        typeUser->hide();
        changeType->hide();
        selectType->hide();
    }
    setLayout(boxLayout);
}

void ModificaUser::setViewAdd()
{
    if(dynamic_cast<const Admin*>(logUser))
    {
        boxLayout=new QVBoxLayout;
        boxLayout->addLayout(gridLayout);

        setLayout(boxLayout);
    }else this->close();
}

void ModificaUser::bChangeUsername()
{
    emit v_changeUsername(modUser,username->text().toStdString());
}

void ModificaUser::bChangePassword()
{
    if (newPassword->text()==confirmNewPassword->text())
    {
        emit v_changePassword(modUser,newPassword->text().toStdString());
    }else QMessageBox::warning(0,"Errore inserimento Passoword", "La nuova password non coincide con la password di conferma");
}

void ModificaUser::bChangeName()
{
    emit v_changeName(modUser,name->text().toStdString());
}

void ModificaUser::bChangeSurname()
{
    emit v_changeSurname(modUser,surname->text().toStdString());
}

void ModificaUser::bChangeSkill()
{
    if(skill->text().toInt()>=0 && skill->text().toInt()<=100)emit v_changeSkill(modUser,skill->text().toInt());
    else QMessageBox::warning(0,"Modifica non riuscita","La skill deve essere compresa tra 0 e 100");
}

void ModificaUser::bAddUser()
{
    if(username->text()=="") QMessageBox::warning(0,"Username vuoto","Inserire un username valido");
    else if(newPassword->text()!=confirmNewPassword->text() || newPassword->text()==""){
        QMessageBox::warning(0,"Errore inserimento password","La password di conferma non coincide con la password da lei inserita o e' vuota");
        newPassword->clear();
        confirmNewPassword->clear();
    }else if(name->text()==""||surname->text()==""){
        QMessageBox::warning(0,"Errore inserimento nome o cognome","Il nome e il cognome non possono essere vuoti");
    }else{
        User* newUser;
        if(typeUser->currentText()=="Admin") newUser=new Admin;
        else if(typeUser->currentText()=="Accountant") newUser=new Accountant;
        else if(typeUser->currentText()=="Warehouseman") newUser=new Warehouseman;
        else if(typeUser->currentText()=="Officeworker") newUser=new Officeworker;
        else newUser=new Processworker;
        newUser->setUsername(username->text().toStdString());
        newUser->setPassword(newPassword->text().toStdString());
        newUser->setName(name->text().toStdString());
        newUser->setSurname(surname->text().toStdString());
        newUser->setSkill(skill->text().toInt());
        emit v_addUser(newUser);
    }
}

void ModificaUser::bChangeType()
{
    User* newUser;
    if(typeUser->currentText()=="Admin") newUser=new Admin;
    else if(typeUser->currentText()=="Accountant") newUser=new Accountant;
    else if(typeUser->currentText()=="Warehouseman") newUser=new Warehouseman;
    else if(typeUser->currentText()=="Officeworker") newUser=new Officeworker;
    else newUser=new Processworker;
    newUser->setUsername(modUser->getUsername());
    newUser->setPassword(modUser->getPassword());
    newUser->setName(modUser->getName());
    newUser->setSurname(modUser->getSurname());
    newUser->setSkill(modUser->getSkill());
    modUser=newUser;
    emit v_changeType(newUser);
   // this->close();
}
