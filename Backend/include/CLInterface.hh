#ifndef CLInterface_H
#define CLInterface_H 

using namespace std;

class CLInterface {
    public:
        CLInterface();

        static CLInterface *GetInstance();

        void runInterface();

    private:

        static CLInterface *fInstance;

        int mainMenu();

        void addAccountPage();
        int adminToolsPage();

        
};

#endif