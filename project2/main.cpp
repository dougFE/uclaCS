#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	// Force 2 decimal point precision
	cout << fixed << setprecision(2);
	// Collect name, taxable income, occupation, num of kids
	std::string name;
	double income;
	std::string job;
	int kids = 0;
	double tax;
	cout << "Name: ";
	std::getline(std::cin,name);
	cout << "Taxable income: ";
	cin >> income;
	cin.ignore(10000000, '\n');
	cout << "Occupation: ";
	std::getline(std::cin,job);
	cout << "Number of children: ";
	cin >> kids;
	cout << "---" << endl;

		//The first $55000 of taxable income is taxed at 4%.
	if (income <= 55000)
		tax = income * 0.04;
	else
		tax = 55000 * 0.04;

	//The next $70000 of taxable income is taxed at 7 % in general.
	if (income <= 125000 && income > 55000)
		//If the taxpayer's occupation is nurse or teacher (so spelled, entirely in lower case), the income in this bracket is taxed at only 5%.
		if (job == "nurse" || job == "teacher")
			tax += (income - 55000) * 0.05;
		else
			tax += (income - 55000) * 0.07;
	else if (income > 55000)
		if (job == "nurse" || job == "teacher")
			tax += (70000) * 0.05;
		else
			tax += (70000) * 0.07;

	//The amount of taxable income that exceeds $125000 is taxed at 9.3 % .
	if (income > 125000)
		tax += (income - 125000) * 0.093;
	else
	{
		//If the taxable income is under $125000, the tax is reduced by $200 per child; however, the tax is never allowed to go below zero.
		for (int i = 0; i < kids; ++i)
		{
			if (tax >= 200)
				tax = tax - 200;
		}
	}
	

	// Account for missing/incorrect user input
	if (name == "")
		cout << "You must enter a name";
	else if (income < 0)
		cout << "The taxable income must not be negative";
	else if (job == "")
		cout << "You must enter an occupation";
	else if (kids < 0)
		cout << "The number of children must not be negative";
	else // Print result if input was correct
		cout << name << " would pay $" << tax << endl;

}