#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;
int displayTitle();
int carRental(bool member);
bool membership();
void signUp();
bool logIn();
void carReturn();
int main()
{
	int page = 0;
	bool i = false; // membersip yes or no
	while (page != 4) // allow people to return to main menu
	{
		system("cls");
		page = displayTitle();
		system("cls");
		if (page == 1) // rent car
		{
			page = carRental(i);

		}
		else if (page == 2) // return car
		{
			carReturn();
			cout << "Thank you for renting! Have a nice day!" << endl;
			break;
		}
		else if (page == 3) // apply membership
		{
			i = membership();
		}
		else cout << "Thank you for visiting! Have a nice day." << endl;
	}

	system("pause");
	return 0;
}

int displayTitle()
{
	int choice;
	cout << "welcome!" << endl;
	cout << "1. Rent a car" << endl;
	cout << "2. Return a car" << endl;
	cout << "3. Membership" << endl;
	cout << "4. Exit" << endl << endl;
	cout << "Please select page (1-4): ";
	cin >> choice;
	if (choice == 1) return 1;
	else if (choice == 2) return 2;
	else if (choice == 3) return 3;
	else return 4;
}

int carRental(bool member)
{
	const int SIZE = 4, pSize = 4; // change value according to number of model
	ifstream carList;
	ofstream rental; // to save customer who rents
	string model[SIZE], rentModel, name;
	int quantity, memberRent = 0;
	double price[pSize], deposit, deposit_display;
	carList.open("Project2.txt");
	if (!carList) cout << "Error! Unable to open file" << endl;
	else
	{
		// display available car
		cout << "Available rental cars." << endl;
		cout << left << setw(15) << "Model" << setw(15) << "Quantity" << "Price($)" << endl;
		while (!carList.eof())
		{
			if (carList.fail())
			{
				cout << "Error!" << endl;
				break;
			}
			for (int i = 0; i < SIZE; i++)
			{
				carList >> model[i] >> quantity >> price[i];
				cout << setw(15) << model[i] << setw(15) << quantity << price[i] << endl;
			}
		}
		carList.close();
		// applying rental
		rental.open("Rental.txt", ios::app);
		if (!rental) cout << "Error" << endl;
		else
		{
			cout << "Please enter model name to rent: ";
			cin >> rentModel;
			for (int i = 0; i < SIZE; i++)
			{
				if (model[i] == rentModel)
				{
					system("cls");
					if (member == true) // applying member discount (taken for membership())
					{
						price[i] = price[i] / 100.0 * 90;
						cout << "Member's 10% discount applied." << endl;
						memberRent = 1;
					}
					cout << "\nModel : " << model[i] << endl;

					cout << "Rental Price is $" << price[i] << endl;
					deposit_display = price[i] / 100.0 * 60;
					break;
				}
			}
			// paying deposit
			cout << "Minimum deposit amount is $" << deposit_display << endl;
			cout << "Please enter amount to deposit to complete the rental process : ";
			cin >> deposit;
			while (deposit < deposit_display)
			{
				//Sleep(1000);
				cout << "\nProcessing..." << endl;
				Sleep(1000);
				cout << "\nTransaction Disapprove" << endl;
				cout << "Please try again : " << endl;
				cin >> deposit;
			}
			cout << "\nProcessing..." << endl;
			Sleep(1000);
			cout << "\nTrasaction Approve!" << endl;
			Sleep(1000);
			cout << "Please enter name: ";
			cin >> name;
			system("cls");
			cout << "Thank you." << endl;
			cout << "Enjoy your trip!" << endl;
			rental << name << "\t" << deposit << "\t" << rentModel << "\t" << memberRent << endl;
			rental.close();
		}
	}
	return 4;

}

// membership functions
bool membership()
{
	int page;
	bool member = false;
	cout << "Welcome to the Membership store" << endl;
	cout << "Members get a 10% discount on all rentals." << endl;
	cout << "\n1. Sign Up" << endl;
	cout << "2. Log In" << endl;
	cout << "Enter any other to return to menu." << endl;
	cout << "Signing up, or already have an account : ";
	cin >> page;
	if (page == 1)
	{
		signUp();
		member = true;
	}
	else if (page == 2)
	{
		member = logIn();
	}
		cout << "\n Returning to main menu..." << endl;
		Sleep(1000);
	
	return member;
}

void signUp()
{
	ofstream outFile;
	string name, password;
	int payment;
	cout << "\nMembership fee is $50/month" << endl;
	cout << "Please enter username: ";
	cin >> name;
	cout << "please enter password: ";
	cin >> password;
	cout << "Please make payment of $50 : ";
	cin >> payment;
	while (payment != 50)
	{
		cout << "\nProcessing..." << endl;
		Sleep(1000);
		cout << "\nTransaction Disapprove" << endl;
		cout << "Please try again : " << endl;
		cin >> payment;
	}
	cout << "\nProcessing..." << endl;
	Sleep(1000);
	cout << "\nTrasaction Approve!" << endl;
	Sleep(1000);
	outFile.open("membership.txt", ios::app); // allow data to be save into text file
	if (!outFile) cout << "Error" << endl;
	else
	{
		outFile << name << "\t" << password << endl;
		system("cls");
		cout << "member's account created" << endl;
		Sleep(1000);
	}
	outFile.close();
}

bool logIn() // determine if user is a member or not
{
	ifstream inFile;
	string name, username, password, checkPass;
	bool member;
	cout << "\nEnter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;
	
	while (username != name || password != checkPass)
	{
		inFile.open("membership.txt");
		if (!inFile) cout << "Error! Unable to open file" << endl;
		while (!inFile.eof()) // read txt file for user name
		{
			if (inFile.fail())
			{
				cout << "Error fail" << endl;
				break;
			}
			inFile >> name >> checkPass;
			
			if (name == username && checkPass == password) break;
		}
		inFile.close();
		cout << "\nLogging in..." << endl;
		Sleep(1000);
		if (username != name || checkPass != password)
		{
			system("cls");
			cout << "Invalid username/password. Please try again" << endl;
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;
		}
	}
	cout << "Welcome back " << username << "!" << endl;
	member = true;
	
	return member;
}

// returning the car
void carReturn()
{
	ifstream carList, rental;
	string name, checkName, model, checkModel;
	int deposit, member, balance, quantity, price, payment;

	rental.open("Rental.txt");
	carList.open("Project2.txt");
	if (!rental || !carList) cout << "Error" << endl;
	else
	{
		cout << "Please enter rental's name: ";
		cin >> name;
		while (!rental.eof())
		{
			if (rental.fail())
			{
				cout << "Error" << endl;
				break;
			}
			rental >> checkName >> deposit >> model >> member;
			if (checkName == name) break;
		}
		rental.close();
		while (!carList.eof())
		{
			if (carList.fail())
			{
				cout << "Error" << endl;
				break;
			}
			carList >> checkModel >> quantity >> price;
			if (checkModel == model) break;
		}
		if (member == 1) // make sure that the correct amount is paid
		{
			price = price / 100 * 90;
		}
		balance = price - deposit;
		cout << "Rental's name: " << name << endl;
		cout << "Model rented: " << model << endl;
		cout << "Rent amount: " << price << endl;
		cout << "Deposit amount: " << deposit << endl;
		cout << "Balance : " << balance << endl;
		cout << "\n Please pay remaining balances : ";
		cin >> payment;

		while (payment != balance)
		{
			cout << "\nProcessing..." << endl;
			Sleep(1000);
			cout << "\nTransaction Disapprove" << endl;
			cout << "Please try again : " << endl;
			cin >> payment;
		}
		cout << "\nProcessing..." << endl;
		Sleep(1000);
		cout << "\nTrasaction Approve!" << endl;
		Sleep(1000);
		system("cls");
	}
}