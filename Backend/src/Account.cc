#include "Account.hh"
#include "CurrentAccountdb.hh"
#include "SavingsAccountdb.hh"

Account::Account(): fAccountID(0), fAccountName(""), fEmail(""), fDOB(0), fPassword(""), fQuestion("")
{
}

Account::Account(int accountID, string accountName, string email, int dob, string pass, string ques): 
    fAccountID(accountID), fAccountName(accountName), fEmail(email), fDOB(dob),
    fPassword(pass), fQuestion(ques)
{
}


int Account::securityCheck(){
    
    int c1 = (std::rand() % (fPassword.length()));
    int c2 = (std::rand() % (fPassword.length()));
    int c3 = (std::rand() % (fPassword.length()));

    char in1, in2, in3;

    cout << "Please enter the character " << c1+1 << " of your Password" << endl;
    cin >> in1;
    if(in1 != fPassword[c1]){
        cout << "Incorrect 1 attempt remaining " << fPassword[c1] << endl;
        cin >> in1;
        if(in1 != fPassword[c1]){
            cout << "Incorrect 0 attmpts remaining" << endl;
            return 50;
        }
    }
    cout << "Please enter the character " << c2+1 << " of your Password" << endl;
    cin >> in2;
    if(in2 != fPassword[c2]){
        cout << "Incorrect 1 attempt remaining" << endl;
        cin >> in2;
        if(in2 != fPassword[c2]){
            cout << "Incorrect 0 attmpts remaining" << endl;
            return 50;
        }
    }
    cout << "Please enter the character " << c3+1 << " of your Password" << endl;
    cin >> in3;
    if(in3 != fPassword[c3]){
        cout << "Incorrect 1 attempt remaining" << endl;
        cin >> in3;
        if(in3 != fPassword[c3]){
            cout << "Incorrect 0 attmpts remaining" << endl;
            return 50;
        }
    }

    return 0;
}

vector<int> Account::printAccounts(){
    // See if there is a current account
    vector<int> accounts;
    cout << "*********************************************************************" << endl;
    cout << "**       Type       **      Value           **     IntrestRate     **" << endl;
    cout << "*********************************************************************" << endl;
    int resCA = CurrentAccountdb::GetInstance()->printEntry(fAccountID);
    if(resCA){
        accounts.push_back(0);
    }
    cout << "*********************************************************************" << endl;
    int resSA = SavingsAccountdb::GetInstance()->printEntry(fAccountID);
    if(resSA){
        accounts.push_back(1);
    }
    cout << "*********************************************************************" << endl; 
    return accounts;
}