#ifndef ALLUSERS_H
#define ALLUSERS_H
#include "officeworker.h"
#include "accountant.h"
#include "processworker.h"
#include "warehouseman.h"
#include "admin.h"
#include <list>
using std::list;

//"Database Utenti"
class AllUsers
{
    static const string xmlFile;
    list<User*> users;
    void deleteList();
    bool checkAdmin();

public:
    AllUsers();

    void loadUsers();
    User* getUser(const string& name, bool check=false);
    const list<User*> getAllUser();
    const User* searchUser(const string& name, bool check=false) const;
    User *tryLog(const string& name, const string& password);
    void addUser(User *user);
    void removeUser(const string& name, bool check=false);

    void changeUsername(User* user, const string& newUsername);
    void changePassword(User* user, const string& newPassword);
    void changeName(User *user, const string& newName);
    void changeSurname(User* user, const string& newSurname);
    void changeSkill(User *user, const int& newSkill);
    void changeType(User* newUserType);

    int getSize()const;
    bool checkList() const;     //ritrona true se la lista ha almeno un elemento
    void saveUsers() const;



    ~AllUsers();
};

#endif // ALLUSERS_H
