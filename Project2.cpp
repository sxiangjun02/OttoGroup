#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sstream>


using namespace std;
const int Maxcar = 100;
int carnum = 0;
string carname[Maxcar];
int carsavail[Maxcar];
double carprice[Maxcar];

void Save()
{
	ofstream RentalCars("Project2.txt");
	carnum = 0;
	for (int i = 0; i < carnum; i++)
	{
		RentalCars << carname[i] << " " << carsavail[i] << " " << carprice[i] << endl;
	}
	RentalCars.close();
}
void Load()
{
	ifstream RentalCars("Project2.txt");
	carnum = 0;
	while (RentalCars >> carname[carnum] >> carsavail[carnum] >> carprice[carnum])
	{
		carnum++;
	}
	RentalCars.close();
}
void PrintCar()
{
	for (int i = 0; i < carnum; i++)
		cout << carname[i] << " " << " " << carsavail[i] << " " << carprice[i] << endl;
}

void DisplayTitle() {
	int choice;
	cout << "welcome!" << endl;
	cout << "would you like to rent a car press 1 for Yes and 2 for No?" << endl;
	cout << "1.Yes" << endl;
	cout << "2.No" << endl;
	cin >> choice;
	system("cls");
	if (choice == 1)
	{
		cout << "the cars available for rent are: " << endl;
		Load();
		PrintCar();
		system("pause");
		exit(0);
	}
	else if (choice == 2)
	{
		exit(0);
	}
	else
	{
		cout << "Invalid number entered, please enter again" << endl;
		cin >> choice;
		while (choice < 1 || choice > 2) 
		{
			cout << "Invalid number entered, please enter again" << endl;
			cin >> choice;
		}
	}

}



int main()
{
    DisplayTitle();

}