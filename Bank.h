#include "BankAccount.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Bank {
public:
  Bank();
  void menu();
  void openBankAcct();
  void modBnkAcc();
  void closeBnkAccount();
  void detailBnkAccts();
  void sortedDetailBnkAccInfo();
  void print();
  double getAggBalBnkAccts(double amount);

private:
  string bankName;
  string bankAddress;
  string workHours;
  vector<BankAccount *> bankAccts;
  static int numOfBnkAcc;
  double totBalAccts = 0;
};

Bank::Bank() {
  cout << "Enter the name of the bank: ";
  getline(cin, bankName);
  cout << "Enter the address of the bank: ";
  getline(cin, bankAddress);
  cout << "Enter the working hours: ";
  getline(cin, workHours);
  cout << endl;
}

void Bank::menu() {
  char selection = 'y';

  while (selection != 'X') {
    cout << "\nEligible Services for " << bankName << endl;
    cout << "\t\tA -- Number of Bank-Accounts" << endl;
    cout << "\t\tS -- Number of Saving-Accounts" << endl;
    cout << "\t\tH -- Number of Checking-Accounts" << endl;
    cout << "\t\tO -- Open Bank-Account" << endl;
    cout << "\t\tC -- Close Bank-Account" << endl;
    cout << "\t\tM -- Modify Bank-Account" << endl;
    cout << "\t\tD -- Detailed Bank-Accounts" << endl;
    cout << "\t\tB -- Brief Bank-Accounts Info Sorted Based on Aggregated "
            "Balances"
         << endl;
    cout << "\t\tX -- Exit" << endl;

    cout << "Please enter your selection: ";
    cin >> selection;
    selection = toupper(selection);

    if (selection == 'A') {
      cout << "\t| The number of Bank Account(s) is " << bankAccts.size()
           << endl
           << endl;
    } else if (selection == 'S') {
      cout << "\t| The number of Saving-Account(s) is "
           << BankAccount::numOfSavAcc << endl
           << endl;

    } else if (selection == 'H') {
      cout << "\t| The number of Checking-Account(s) is "
           << BankAccount::numOfChkAcc << endl
           << endl;
      
    } else if (selection == 'O') {
      openBankAcct();
      cout << endl;

    } else if (selection == 'C') {
      closeBnkAccount();
      cout << endl;

    } else if (selection == 'M') {
      modBnkAcc();
      cout << endl;

    } else if (selection == 'D') {
      detailBnkAccts();
      print();
      cout << endl;

    } else if (selection == 'B') {
      sortedDetailBnkAccInfo();
      cout << endl;
      
    } else if (selection == 'X') {
      cout << "\t| End of service for bank " << bankName << endl;
    } else {
      cout << "\n\t| Invalid input" << endl << endl;
    }
  }
}

void Bank::openBankAcct() {
  string firstName, lastName, SSN;
  BankAccount *bankAcct = new BankAccount();

  cout << "\n\tEnter the first name of the account holder: ";
  cin >> firstName;
  bankAcct->setFirstName(firstName);

  cout << "\tEnter the last name of the account holder: ";
  cin >> lastName;
  bankAcct->setLastName(lastName);

  cout << "\tEnter the SSN of the account holder: ";
  cin >> SSN;
  bankAcct->setSSN(SSN);

  bankAcct->setBnkAccNum(make_pair("BNK", 10000 + numOfBnkAcc));

  numOfBnkAcc++;
  bankAccts.push_back(bankAcct);

  cout << "\n\t| A new Bank Account " << bankAcct->getBnkAccNum().first
       << bankAcct->getBnkAccNum().second << " was successfully created\n\n";

  bankAcct->bankAccMenu();

  getAggBalBnkAccts(bankAcct->getTotalBalance());
}

int Bank::numOfBnkAcc = 0;

void Bank::modBnkAcc() {
  string str, strNum, bnkAccount;
  BankAccount temp;
  pair<string, int> bnkAccNum;
  bool check = true;

  cout << "\tEnter the bank account number to be modified: ";
  bnkAccNum = temp.getSubAccount();

  for (int i = 0; i < bankAccts.size(); i++) {
    if (bnkAccNum.second == bankAccts.at(i)->getBnkAccNum().second) {
      bankAccts.at(i)->bankAccMenu();
      check = false;
      break;
    }
  }
  if (check) {
    cout << "\n\t| Entered Bank Account Number Not found!\n";
  }
}

double Bank::getAggBalBnkAccts(double amount) {
  totBalAccts += amount;
  return totBalAccts;
}

void Bank::detailBnkAccts() {
  cout << "\n\t| Bank Name: " << bankName;
  cout << "\n\t| Bank Address: " << bankAddress;
  cout << "\n\t| Bank Working Hours: " << workHours;
  cout << "\n\t| Aggregated Balance: $" << totBalAccts;
  cout << "\n\t| Consists of " << numOfBnkAcc << " Bank-Accounts\n";
}

void Bank::print() {
  for (auto bnkA : bankAccts) {
    bnkA->printInfo();
    bnkA->sortedDetailSubAccInfo();
  }
}

void Bank::closeBnkAccount() {
  pair<string, int> bnkAccNum;
  BankAccount temp;
  vector<BankAccount *>::iterator it1;

  it1 = bankAccts.begin();

  cout << "\tEnter the bank account number to be closed: ";
  bnkAccNum = temp.getSubAccount();

  bool found = false;
  if (bnkAccNum.first == "BNK") {
    for (int i = 0; i < bankAccts.size(); i++) {
      if (bankAccts.at(i)->getBnkAccNum().second == bnkAccNum.second) {
        found = true;
        cout << "\n\t| Bank account " << bnkAccNum.first << bnkAccNum.second
             << " was successfully closed.\n";
        bankAccts.erase(it1);
        break;
      } else {
        it1++;
      }
    }
  }
  if (!found) {
    cout << "\n\t| Entered SubAccount Number Not Found!\n";
  }
}

void Bank::sortedDetailBnkAccInfo() {
  sort(bankAccts.begin(), bankAccts.end(), [](BankAccount* a, BankAccount* b){return a->getTotalBalance() < b->getTotalBalance();});
  detailBnkAccts();
  for (int i = 0; i < bankAccts.size(); i++) {
    bankAccts.at(i)->briefBnkAccInfo();
  }
}
