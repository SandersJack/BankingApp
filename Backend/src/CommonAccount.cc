#include "CommonAccount.hh"
#include "Vdb.hh"

CommonAccount::CommonAccount(): fAccountID(0), fValue(0.), fIntrestRate(0.)
{
}

int CommonAccount::transferTo(CommonAccount *to_account, double value){
    if(value > fValue){
        cout << "[WARNING] This will make the acount go into negative!! Is this ok [Y/N]?";
        string res;
        cin >> res;
        if(res == "N"){
            return 99;
        } 
    }
    fValue -= value;
    to_account->_toValue(value);
    Vdb().updateEntry(to_account);
    CommonAccount *this_account = this; 
    Vdb().updateEntry(this_account);
    cout << "Successfully transfered" << endl;
    return 0;
}