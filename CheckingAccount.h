#include <iostream>
using namespace std;

class CheckingAccount
{
public:
  void print(); // printing
  void chkModify();
  void setAccStatus();
  bool checkAccStatus();
  void deposit(double amount);
  void deposit()
  {
    double amount;
    cout << "\tEnter the amount to deposit: ";
    cin >> amount;
    deposit(amount);
  }
  void withdraw();
  void setTotalChkBalance(double amount) { *totalChkBalance += amount; }
  double getTotalChkBalance() const { return *totalChkBalance; }
  void setMaxCap()
  {
    cout << "\tEnter the desired maximum capacity: ";
    cin >> *maxCap;
  }
  double getMaxCap() { return *maxCap; }
  void lockAcc() { *isLocked = true; }
  void unlockAcc() { *isLocked = false; }
  bool showAccStatus() { return *isLocked; }
  void setChkAccNum(pair<string, int> chkAccNum)
  {
    this->chkAccNum->first = chkAccNum.first;
    this->chkAccNum->second = chkAccNum.second;
  }
  pair<string, int> getChkAccNum() { return *chkAccNum; }
  bool operator>(CheckingAccount c)
  {
    return *totalChkBalance > c.getTotalChkBalance();
  }

private:
  double *totalChkBalance = new double(0);
  double *maxCap = new double;
  bool *isLocked = new bool(false);
  pair<string, int> *chkAccNum = new pair<string, int>;
};

void CheckingAccount::chkModify()
{
  char selection;
  while (true)
  {
    cout << "\n\nEligible services for sub-Account " << chkAccNum->first
         << chkAccNum->second;
    cout << "\n\tD -- Deposit";
    cout << "\n\tW -- Withdraw";
    cout << "\n\tC -- Max Capacity";
    cout << "\n\tL -- Lock sub-Account";
    cout << "\n\tU -- Unlock sub-Account";
    cout << "\n\tX -- Exit";
    cout << "\nPlease enter your selection: ";

    cin >> selection;
    selection = toupper(selection);

    switch (selection)
    {
    case 'D':
      deposit();
      break;
    case 'W':
      withdraw();
      break;
    case 'C':
      setMaxCap();
      break;
    case 'L':
      lockAcc();
      cout << "\n\t| The sub-account " << this->chkAccNum->first
           << this->chkAccNum->second << " is locked now!\n\n";
      break;
    case 'U':
      unlockAcc();
      cout << "\t| The sub-account " << this->chkAccNum->first
           << this->chkAccNum->second << " is unlocked now!\n";
      break;
    case 'X':
      cout << "\t| End of service for sub-account " << chkAccNum->first
           << chkAccNum->second << endl;
      return;
    default:
      cout << "\n\t| Invalid input" << endl
           << endl;
    }
  }
}

void CheckingAccount::setAccStatus()
{
  char accStatus;

  cout << "\tDefine initial state: (L - Locked, Otherwise - Unlocked: ";
  cin >> accStatus;
  if (toupper(accStatus) == 'L')
  {
    lockAcc();
  }
  else
  {
    unlockAcc();
  }
}

bool CheckingAccount::checkAccStatus()
{
  if (*isLocked)
  {
    cout << "\t| The sub-account is currently locked!"
         << "\n\t| Transaction was unsuccessful.\n";
    return true;
  }
  else
  {
    return false;
  }
}

void CheckingAccount::deposit(double amount)
{
  if (!checkAccStatus())
  {
    if (amount >= 0)
    {
      if (getTotalChkBalance() + amount < *maxCap)
      {
        *totalChkBalance += amount;
        cout << "\t| Deposit was successful.";
        cout << "\n\t| The current balance is $" << *totalChkBalance << endl
             << endl;
      }
      else
      {
        cout << "\n\t| Denied!\n"
             << "\t| " << chkAccNum->first << chkAccNum->second
             << " max capacity: $" << *maxCap
             << "\n\t| Max capacity exceeded!\n\n";
      }
    }
    else
    {
      cout << "\t| Error!\n\t| Enter amount greater than 0.\n";
    }
  }
}

void CheckingAccount::withdraw()
{
  double amount;
  cout << "Current balance: $" << getTotalChkBalance() << endl;
  cout << "Enter the amount to withdraw: ";
  cin >> amount;

  if (!checkAccStatus())
  {
    if (amount > 0)
    {
      if (*totalChkBalance >= amount)
      {
        *totalChkBalance -= amount;
        cout << "\t| Withdraw was successful.";
        cout << "\n\t| The current balance is $" << getTotalChkBalance() << endl
             << endl;
      }
      else
      {
        cout << "\t| Insufficient funds!\n\t|Current balance $"
             << *totalChkBalance << endl
             << endl;
      }
    }
    else
    {
      cout << "\t| Error!\n\t| Enter amount greater than 0.\n";
    }
  }
}

void CheckingAccount::print()
{
  cout << "\n\t| Sub-Account number: " << getChkAccNum().first
       << getChkAccNum().second << "\n\t| Balance: $" << getTotalChkBalance()
       << endl
       << endl
       << "\n\t| The maximum capacity is: $" << getMaxCap();
  if (showAccStatus())
  {
    cout << "\n\t| The sub-account is locked.\n";
  }
  else
  {
    cout << "\n\t| The sub-account is not locked.\n";
  }
}