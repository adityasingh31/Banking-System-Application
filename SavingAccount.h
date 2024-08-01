#include <iostream>
using namespace std;

class SavingAccount {
public:
  void print();
  void savModify();
  void deposit(double amount);
  void deposit() {
    double amount;
    cout << "\tEnter the amount to deposit: ";
    cin >> amount;
    deposit(amount);
  }
  void withdraw();
  double getTotalSavBalance() const { return *totalSavBalance; }
  void setSavAccNum(pair<string, int> savAccNum) {
    this->savAccNum->first = savAccNum.first;
    this->savAccNum->second = savAccNum.second;
  }
  pair<string, int> getSavAccNum() { return *savAccNum; }
  void setSavBalance(double amount) { *totalSavBalance = amount; }
  void initialdeposit(double amount) { *totalSavBalance += amount; }
  bool operator>(SavingAccount s) {
    return *totalSavBalance > s.getTotalSavBalance();
  }

private:
  double *totalSavBalance = new double(0);
  pair<string, int> *savAccNum = new pair<string, int>;
};

void SavingAccount::savModify() {
  char selection;
  while (true) {
    cout << "\n\nEligible services for sub-Account " << savAccNum->first
         << savAccNum->second;
    cout << "\n\tD -- Deposit";
    cout << "\n\tW -- Withdraw";
    cout << "\n\tX -- Exit";
    cout << "\nPlease enter your selection: ";

    cin >> selection;
    selection = toupper(selection);

    switch (selection) {
    case 'D':
      deposit();
      break;
    case 'W':
      withdraw();
      break;
    case 'X':
      cout << "\t| End of service for sub-account " << savAccNum->first
           << savAccNum->second << endl;
      return;
    default:
      cout << "\t| Invalid input" << endl << endl;
    }
  }
}

void SavingAccount::withdraw() {
  double amount;
  cout << "\tCurrent balance: $" << getTotalSavBalance() << endl;
  cout << "\tEnter the amount to withdraw: ";
  cin >> amount;

  if (amount >= 0) {
    if (*totalSavBalance >= amount) {
      *totalSavBalance -= amount;
      cout << "\t| Withdraw was successful.";
      cout << "\n\t| The current balance is $" << getTotalSavBalance() << endl
           << endl;
    } else {
      cout << "\n\t| Insufficient funds!\n\t| Current balance: $"
           << *totalSavBalance << endl
           << endl;
    }

  } else {
    cout << "\t| Error!\n\t| Enter amount greater than 0.\n";
  }
}

void SavingAccount::deposit(double amount) {
  if (amount > 0) {
    *totalSavBalance += amount;
    cout << "\t| Deposit was successful.";
    cout << "\n\t| The current balance is $" << *totalSavBalance << endl << endl;
  }
}
void SavingAccount::print() {
  cout << "\n\t| Sub-Account number: " << getSavAccNum().first
       << getSavAccNum().second;
  cout << "\n\t| Balance: $" << getTotalSavBalance() << endl;
  cout << endl;
}