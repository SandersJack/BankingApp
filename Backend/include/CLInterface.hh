#ifndef CLInterface_H
#define CLInterface_H 

#include "Account.hh"

using namespace std;

class CLInterface {
    public:
        CLInterface();

        static CLInterface *GetInstance();

        void runInterface();

    private:

        static CLInterface *fInstance;

        int mainMenu();

        int addAccountPage();
        int adminToolsPage();
        int viewAccountPage();
        int loginAccountPage();
        int viewModifyPage();

        int accountPage(Account *loginAccount);
        int productsPage(Account *loginAccount);
        int addProductsPage(Account *loginAccount);
        int closeProductsPage(Account *loginAccount);

        
};

#endif