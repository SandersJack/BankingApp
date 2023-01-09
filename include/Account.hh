#include <iostream>


class Account {

public:
    Account();
    static Account *GetInstance();
    std::string GetAccountName(){ return Accountname;};

private:
    std::string Accountname;
    static Account *fInstance;
};