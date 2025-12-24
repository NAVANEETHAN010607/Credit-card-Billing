#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Account
{
protected:
    string holderName;
    string cardNumber;

public:
    Account(string name = "", string card = "")
    {
        holderName = name;
        cardNumber = card;
    }

    void displayAccount()
    {
        cout << "Card Holder : " << holderName << endl;
        cout << "Card Number : " << cardNumber << endl;
    }
};

class Charge
{
public:
    double amount;

    Charge(double amt = 0)
    {
        amount = amt;
    }

    double operator+(Charge c)
    {
        return amount + c.amount;
    }
};

class CreditCard : public Account
{
private:
    vector<Charge> charges;
    double interestRate;

public:
    CreditCard(string name, string card, double rate)
        : Account(name, card)
    {
        interestRate = rate;
    }

    void addCharge(double amt)
    {
        charges.push_back(Charge(amt));
    }

    double calculateTotal()
    {
        double total = 0;
        int i;

        for (i = 0; i < charges.size(); i++)
            total += charges[i].amount;

        total += (total * interestRate / 100);
        return total;
    }

    void generateBill(string month)
    {
        string filename = "Bill_" + month + ".txt";
        ofstream file(filename.c_str());

        if (!file)
        {
            cout << "File error!" << endl;
            return;
        }

        file << "===== CREDIT CARD BILL =====\n";
        file << "Month : " << month << endl;
        file << "Card Holder : " << holderName << endl;
        file << "Card Number : " << cardNumber << endl;

        file << "\nCharges:\n";
        file << fixed << setprecision(2);

        double total = 0;
        int i;

        for (i = 0; i < charges.size(); i++)
        {
            file << "Charge " << i + 1 << ": Rs. "
                 << charges[i].amount << endl;
            total += charges[i].amount;
        }

        double interest = total * interestRate / 100;

        file << "\nSubtotal : Rs. " << total << endl;
        file << "Interest (" << interestRate << "%): Rs. " << interest << endl;
        file << "Total Bill : Rs. " << total + interest << endl;
        file << "============================\n";

        file.close();
        cout << "\nBill generated successfully!\n";
    }

    void displayBill()
    {
        displayAccount();
        cout << "Interest Rate : " << interestRate << "%\n";
        cout << "Total Amount Due : Rs. "
             << fixed << setprecision(2)
             << calculateTotal() << endl;
    }
};

int main()
{
    string name, card, month;
    double rate, charge;
    int choice;

    cout << "Enter Card Holder Name: ";
    getline(cin, name);

    cout << "Enter Card Number: ";
    getline(cin, card);

    cout << "Enter Interest Rate (%): ";
    cin >> rate;

    CreditCard cc(name, card, rate);

    do
    {
        cout << "\n1. Add Charge";
        cout << "\n2. Display Bill";
        cout << "\n3. Generate Monthly Bill File";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter charge amount: Rs. ";
            cin >> charge;
            cc.addCharge(charge);
            break;

        case 2:
            cc.displayBill();
            break;

        case 3:
            cout << "Enter Month (e.g., March2025): ";
            cin >> month;
            cc.generateBill(month);
            break;
        }
    } while (choice != 4);

    return 0;
}

