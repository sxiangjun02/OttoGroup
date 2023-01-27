#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>

using namespace std;
int displayTitle();
int carRental(bool member);
bool membership();
void signUp();
bool logIn();
int main()
{
	int page = 0;
	bool i; // membersip yes or no
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
			/* request user to pay off remaining rental fee
			can try to request user the mileage on the car.
			Then charge the user fixed rate on extra mileage.
			But if want to do this, then the txt file must update to include limited or unlimited mileage.
			Just suggesting. */
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
	ifstream inFile;
	string model[SIZE], rentModel;
	int quantity;
	double price[pSize], deposit, deposit_display;
	inFile.open("Project2.txt");
	if (!inFile) cout << "Error! Unable to open file" << endl;
	else
	{
		// display available car
		cout << "Available rental cars." << endl;
		cout << left << setw(15) << "Model" << setw(15) << "Quantity" << "Price($)" << endl;
		while (!inFile.eof())
		{
			if (inFile.fail())
			{
				cout << "Error!" << endl;
				break;
			}
			for (int i = 0; i < SIZE; i++)
			{
				inFile >> model[i] >> quantity >> price[i];
				cout << setw(15) << model[i] << setw(15) << quantity << price[i] << endl;
			}
		}
		inFile.close();
		// applying rental
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
		system("cls");
		cout << "Enjoy your trip!" << endl;
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
	string name;
	int payment;
	cout << "\nMembership fee is $50/month" << endl;
	cout << "Please enter username: ";
	cin >> name;
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
		outFile << name << endl;
		system("cls");
		cout << "member's account created" << endl;
		Sleep(1000);
		cout << "\nReturning to main menu." << endl;
	}
	outFile.close();
}

bool logIn() // determine if user is a member or not
{
	ifstream inFile;
	string name, username;
	bool member;
	cout << "Enter username: ";
	cin >> username;
	
	while (username != name)
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
			inFile >> name;
			
			if (username == name) break;
		}
		inFile.close();
		cout << "\nLogging in..." << endl;
		Sleep(1000);
		if (username != name)
		{
			cout << "Invalid username. Please try again: ";
			cin >> username;
		}

	}
	cout << "Welcome back " << username << "!" << endl;
	member = true;
	
	return member;
}