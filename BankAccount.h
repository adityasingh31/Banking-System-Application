#include "CheckingAccount.h"
#include "SavingAccount.h"
#include <algorithm>
#include <iostream>
#include <vector>
// defining classes
class BankAccount
{
public:
  void bankAccMenu();
  void setBnkAccNum(pair<string, int> accNum)
  {
    this->accNum->first = accNum.first;
    this->accNum->second = accNum.second;
  }
  pair<string, int> getBnkAccNum() { return *accNum; }
  void printInfo();
  void openSavAcc();
  void openChkAcc();
  void modSubAcc();
  void closeSubAccount();
  void briefBnkAccInfo();
  void detailSubBnkAccInfo();
  void setFirstName(string firstName) { this->firstName = firstName; }
  void setLastName(string lastName) { this->lastName = lastName; }
  void setSSN(string SSN) { this->SSN = SSN; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  string getSSN() { return SSN; }
  double getTotalBalance();
  pair<string, int> getSubAccount();
  void sortedDetailSubAccInfo();
  static int numOfSavAcc;
  static int numOfChkAcc;

  bool operator<(BankAccount ba)
  {
    return getTotalBalance() < ba.getTotalBalance();
  }

private:
  string firstName;
  string lastName;
  string SSN;
  vector<SavingAccount *> savAcctsVec;
  vector<CheckingAccount *> chkAcctsVec;
  pair<string, int> *accNum = new pair<string, int>;
  void sortSavings();
  void sortCheckings();
  void sortAll();
};

void BankAccount::bankAccMenu()
{
  char selection = 'y';

  while (selection != 'X')
  {
    cout << "\nEligible Services for Bank-Account " << accNum->first
         << accNum->second << endl;
    cout << "\t\tS -- Open Saving Sub-Account" << endl;
    cout << "\t\tC -- Open Checking Sub-Account" << endl;
    cout << "\t\tM -- Modify a Sub-Account" << endl;
    cout << "\t\tE -- Close a Sub-Account" << endl;
    cout << "\t\tD -- Detailed Bank Account Info Sorted Based on Balances of "
            "Sub-Accounts"
         << endl;
    cout << "\t\tB -- Brief Bank Account Info" << endl;
    cout << "\t\tX -- Exit" << endl;

    cout << "Please enter your selection: ";
    cin >> selection;
    selection = toupper(selection);

    if (selection == 'S')
    {
      openSavAcc();
      cout << endl;
    }
    else if (selection == 'C')
    {
      openChkAcc();
      cout << endl;
    }
    else if (selection == 'M')
    {
      modSubAcc();
      cout << endl;
    }
    else if (selection == 'E')
    {
      closeSubAccount();
      cout << endl;
    }
    else if (selection == 'D')
    {
      sortedDetailSubAccInfo();

      cout << endl;
    }
    else if (selection == 'B')
    {
      briefBnkAccInfo();
      cout << endl;
    }
    else if (selection == 'X')
    {
      cout << "\n\t| End of service for bank-account " << accNum->first
           << accNum->second << endl;
    }
    else
    {
      cout << "\t| Invalid input" << endl
           << endl;
    }
  }
}

void BankAccount::openSavAcc()
{
  SavingAccount *savAcct = new SavingAccount();
  double amount;
  pair<string, int> savAccNum;

  savAccNum.first = "SAV";
  savAccNum.second = 1000 + numOfSavAcc;
  savAcct->setSavAccNum(savAccNum);

  numOfSavAcc++;

  if (savAcctsVec.size() == 0)
  {
    cout << "\t$100 bonus for first saving account.";
    savAcct->setSavBalance(100);
  }

  cout << "\n\tEnter the initial balance: ";
  cin >> amount;
  savAcct->initialdeposit(amount);

  savAcctsVec.push_back(savAcct);
  cout << "\t| A new Saving Sub-Account " << savAccNum.first << savAccNum.second
       << " was successfully created\n";
}

void BankAccount::openChkAcc()
{
  CheckingAccount *chkAcct = new CheckingAccount();
  pair<string, int> chkAccNum;
  double amount;

  chkAccNum.first = "CHK";
  chkAccNum.second = 6000 + numOfChkAcc;
  chkAcct->setChkAccNum(chkAccNum);

  cout << "\tEnter the initial balance: ";
  cin >> amount;
  chkAcct->setTotalChkBalance(amount);
  chkAcct->setMaxCap();
  chkAcct->setAccStatus();

  numOfChkAcc++;

  chkAcctsVec.push_back(chkAcct);

  cout << "\t| A new Checking Sub-Account " << chkAccNum.first
       << chkAccNum.second << " was successfully created.\n";
}

int BankAccount::numOfSavAcc = 0;
int BankAccount::numOfChkAcc = 0;

pair<string, int> BankAccount::getSubAccount()
{
  string subAccount;
  string str;
  string strNum;
  pair<string, int> subAccNum;

  cin >> subAccount;
  for (int i = 0; i < subAccount.size(); i++)
  {
    if (i < 3)
    {
      str += subAccount.at(i);
    }
    else
    {
      strNum += subAccount.at(i);
    }
  }

  subAccNum.first = str;
  subAccNum.second = stoi(strNum);
  return subAccNum;
}

void BankAccount::modSubAcc()
{
  pair<string, int> subAccNum;

  cout << "\tEnter the sub-account number to modify: ";
  subAccNum = getSubAccount();

  bool found = false;
  if (subAccNum.first == "SAV")
  {
    for (auto sa : savAcctsVec)
    {
      if (sa->getSavAccNum().second == subAccNum.second)
      {
        found = true;
        sa->savModify();
      }
    }
  }
  else
  {
    for (auto ca : chkAcctsVec)
    {
      if (ca->getChkAccNum().second == subAccNum.second)
      {
        found = true;
        ca->chkModify();
      }
    }
  }
  if (!found)
  {
    cout << "\n\t| Entered SubAccount Number Not Found!\n";
  }
}

void BankAccount::closeSubAccount()
{
  pair<string, int> subAccNum;
  vector<SavingAccount *>::iterator it1;
  vector<CheckingAccount *>::iterator it2;

  it1 = savAcctsVec.begin();
  it2 = chkAcctsVec.begin();

  cout << "\tEnter the sub-account number to be closed: ";
  subAccNum = getSubAccount();

  bool found = false;
  if (subAccNum.first == "SAV")
  {
    for (int i = 0; i < savAcctsVec.size(); i++)
    {
      if (savAcctsVec.at(i)->getSavAccNum().second == subAccNum.second)
      {
        found = true;
        cout << "\t| Sub-account " << subAccNum.first << subAccNum.second
             << " was successfully closed.\n";
        savAcctsVec.erase(it1);
        break;
      }
      else
      {
        it1++;
      }
    }
  }
  else
  {
    for (int i = 0; i < chkAcctsVec.size(); i++)
    {
      if (chkAcctsVec.at(i)->getChkAccNum().second == subAccNum.second)
      {
        found = true;
        cout << "\n\t| Sub-account " << subAccNum.first << subAccNum.second
             << " was successfully closed.\n";
        chkAcctsVec.erase(it2);
        break;
      }
      else
      {
        it2++;
      }
    }
    if (!found)
    {
      cout << "\n\t| Entered SubAccount Number Not Found!\n";
    }
  }
}

double BankAccount::getTotalBalance()
{
  double totBal = 0.0;
  for (int i = 0; i < chkAcctsVec.size(); i++)
  {
    totBal += chkAcctsVec.at(i)->getTotalChkBalance();
  }
  for (int i = 0; i < savAcctsVec.size(); i++)
  {
    totBal += savAcctsVec.at(i)->getTotalSavBalance();
  }
  return totBal;
}

void BankAccount::briefBnkAccInfo()
{
  cout << "\t| Aggregated balance of the bank Account: " << accNum->first
       << accNum->second << " with " << savAcctsVec.size() + chkAcctsVec.size()
       << " Sub-Accounts is $" << getTotalBalance() << endl;
}

void BankAccount::sortSavings()
{
  sort(savAcctsVec.begin(), savAcctsVec.end(), [](SavingAccount *a, SavingAccount *b)
       { return a->getTotalSavBalance() > b->getTotalSavBalance(); });
}
void BankAccount::sortCheckings()
{
  sort(chkAcctsVec.begin(), chkAcctsVec.end(), [](CheckingAccount *a, CheckingAccount *b)
       { return a->getTotalChkBalance() > b->getTotalChkBalance(); });
}

void BankAccount::sortAll()
{
  int si = 0;
  int ci = 0;
  while (si < savAcctsVec.size() && ci < chkAcctsVec.size())
  {
    if (savAcctsVec.at(si)->getTotalSavBalance() >
        chkAcctsVec.at(ci)->getTotalChkBalance())
    {
      savAcctsVec.at(si++)->print();
    }
    else
    {
      chkAcctsVec.at(ci++)->print();
    }
  }

  while (si < savAcctsVec.size())
  {
    savAcctsVec.at(si++)->print();
  }

  while (ci < chkAcctsVec.size())
  {
    chkAcctsVec.at(ci++)->print();
  }
}

void BankAccount::sortedDetailSubAccInfo()
{
  sortSavings();
  sortCheckings();
  sortAll();
}

void BankAccount::printInfo()
{
  cout << "\n\n\t| Bank Account Number: " << getBnkAccNum().first
       << getBnkAccNum().second;
  cout << "\n\t| Account Holder Full Name: " << getFirstName() << " "
       << getLastName();
  cout << "\n\t| Account Holder SSN: " << getSSN();
  cout << "\n\t| Aggregated Balance: $" << getTotalBalance();
  cout << "\n\t| Consists of " << savAcctsVec.size() + chkAcctsVec.size()
       << " Sub-Accounts" << endl;
  cout << "\n";
}
