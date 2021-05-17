#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include "RefundFS.h"
#include "RefundSU.h"
#include "OriginationFee.h"
#include <windows.h>
#include <conio.h>
using namespace std;

void showMenu();
void FallSpring();
void Summer();
void Origination();
void Info();
void ClearScreen();
void setBackground();
bool validate(string);
bool validatedouble(string);


int main()
{
	setBackground();
	int count = 0;
	string input0;
	int input;
	do
	{
		showMenu();
		do
		{
			if (count > 0)
			{
				cout << "\tPlease enter a number between 1 and 5: ";
			}
			getline(cin, input0);

			while (!validate(input0))
			{
				cout << "\tPlease enter a number: ";
				getline(cin, input0);
			}
			count++;
			input = stoi(input0);
		} while (input < 1 || input > 5);
		count = 0;
		

			ClearScreen();

			if (input == 1)
			{
				FallSpring();
			}
			else if (input == 2)
			{
				Summer();
			}
			else if (input == 3)
			{
				Origination();
			}
			else if (input == 4)
			{
				Info();
			}
		 

	} while (input != 5);

	return 0;

}
void ClearScreen()
{
	#if defined _WIN32
		system("cls");
		
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		
	#elif defined (__APPLE__)
		system("clear");
	#endif
}
void setBackground()
{
#if defined _WIN32
	system("color 47");

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("");
#endif
}
void showMenu()
{
	cout << "\n\t\tFINANCIAL AID REFUND CALCULATOR\n\n"
		<< "\t1) Calculate for Fall/Spring\n"
		<< "\t2) Calculate for Summer\n"
		<< "\t3) Set Origination Fee\n"
		<< "\t4) Information\n"
		<< "\t5) Exit\n\n"
		<< "\tEnter: ";
}
void FallSpring()
{
	//local variables
	string strinput;
	int number;
	int size;
	int count = 0;
	double value;
	char input;
	char repeat;
	int* PellPot;
	double* SubLoanPot;
	double* UnsubLoanPot;
	double* Refund;



	do
	{
		cout << "\n\t\t\t\tFALL/SPRING\n\n";
		RefundFS *calc = nullptr;					// Define a RefundFS pointer
		calc = new RefundFS;						// Dynamicallly allocate a RefundFS object named calc

		cout << "Number of classes: ";
		getline(cin, strinput);
		while (!validate(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		size = stod(strinput);

		if (size <= 0)
		{
			break;
		}
		calc->setSize(size);   // set input for RefundFS member variable size


		for (int i = 0; i < size; i++)
		{
			do
			{
				if (count != 0)
				{
					cout << "Number of credits must be greater than 0. \n"
						 << "Enter the number of credits for class " << i + 1 << ": ";
				}
				else
				{
					cout << "\nNumber of credits for class " << i + 1 << ": ";
				}
				getline(cin, strinput);
				while (!validatedouble(strinput))
				{
					cout << "Please enter a number: ";
					getline(cin, strinput);
					count++;
				}
				count++;
				number = stoi(strinput);
			} while (number <= 0);
			if (count > 1)
			{
				cout << endl;
			}
			count = 0;
			
			calc->setCreditNumber(i, number);		// set input for RefundFS member vector CreditNumber at position i

			do
			{
				if (count < 1)
				{
					cout << "Part of term for class " << i + 1 << "(For Late start, enter 0): ";
				}
				else
				{
					cout << "Parts of term for Fall/Srping range from 0 to 6: ";
				}
				getline(cin, strinput);
				while (!validate(strinput))
				{
					cout << "Please enter a number between 0 and 6: ";
					getline(cin, strinput);
				}
				number = stoi(strinput);
				count++;
			}while (number < 0 || number > 6);
			count = 0;
			
			calc->setPot(i, number);			// set input for RefundFS member vector Pot at position i	
		}

		cout << "\nPell Grant amount: ";
		getline(cin, strinput);
		while (!validate(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		number = stoi(strinput);
		calc->setPell(number);						 // set input for RefundFS member variable Pell

		cout << "\nSubsidized loan amount: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setSub(value);						// set input for RefundFS member variable Sub

		cout << "\nUnsubsidized loan amount: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setUnsub(value);						// set input for RefundFS member variable Unsub

		cout << "\nTuition Cost: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setCost(value);							// set input for RefundFS member variable cost

		cout << "\nLoan disbursment split (Y/N): ";
		cin >> input;									
		calc->setLoanSplit(input);						// boolean value, if (no loans disbursed in fall){true}

		calc->sort();
		calc->calculateDisb();
		calc->calculatePell();
		calc->calculateLoan();
		calc->calculateRefund();

		PellPot = calc->getPellPot();
		SubLoanPot = calc->getSubLoanPot();
		UnsubLoanPot = calc->getUnsubLoanPot();
		Refund = calc->getRefund();
		


		cout << setprecision(2) << fixed;
		cout << "\nDISBURSEMENT DATA\n-------------------------------------------------";
		cout << "\nPell Grant amount for Part of Term 1, 2, 4, and L: " << *PellPot << "\n";
		cout << "Pell Grant amount for Part of term 5: " << *(PellPot + 1) << "\n";
		cout << "Pell Grant amount for Part of term 3: " << *(PellPot + 2) << "\n";
		cout << "Pell Grant amount for part of term 6: " << *(PellPot + 3) << "\n\n";

		cout << "Subsidized loan amount for Part of Term 1, 2, 4, and L: " << *SubLoanPot << "\n";
		cout << "Subsidized loan amount for Part of term 5: " << *(SubLoanPot + 1) << "\n";
		cout << "Subsidized loan amount for Part of term 3: " << *(SubLoanPot + 2) << "\n";
		cout << "Subsidized loan amount for part of term 6: " << *(SubLoanPot + 3) << "\n\n";

		cout << "Subsidized loan amount for 2nd disbursement: " << calc->getSub2nd() << "\n\n";

		cout << "Unsubsidized loan amount for Part of Term 1, 2, 4, and L: " << *UnsubLoanPot << "\n";
		cout << "Unsubsidized loan amount for Part of term 5: " << *(UnsubLoanPot + 1) << "\n";
		cout << "Unsubsidized loan amount for Part of term 3: " << *(UnsubLoanPot + 2) << "\n";
		cout << "Unsubsidized loan amount for part of term 6: " << *(UnsubLoanPot + 3) << "\n\n";

		cout << "Unsubsidized loan amount for 2nd disbursement: " << calc->getUnsub2nd() << "\n\n";

		cout << "REFUND\n-------------------------------------------------";
		cout << "\nRefund Total: " << calc->getRefundTotal() << "\n";
		cout << "\nRefund amount for Part of Term 1, 2, 4, and L: " << *Refund << "\n";
		cout << "Refund amount for Part of term 5: " << *(Refund + 1) << "\n";
		cout << "Refund amount for Part of term 3: " << *(Refund + 2) << "\n";
		cout << "Refund amount for part of term 6: " << *(Refund + 3) << "\n\n";

		cout << "Refund amount for 2nd loan disbursement: " << calc->getRefund2nd() << "\n\n";

		cout << "Run another calculation? (Y/N) ";
		cin >> repeat;
		cin.ignore();

		delete calc; // Delete object from memory
		calc = nullptr;

		ClearScreen();
		

	} while (repeat == 'Y' || repeat == 'y');
	ClearScreen();
	
}
void Summer()
{
	ClearScreen();
	//local variables
	string strinput;
	int number;
	int size;
	int count = 0;
	double value;
	char input;
	char repeat;
	int* PellPot;
	double* SubLoanPot;
	double* UnsubLoanPot;
	double* Refund;



	do
	{
		cout << "\n\t\t\t\tSUMMER\n\n";
		RefundSU *calc = nullptr;	// Define a RefundSU pointer
		calc = new RefundSU;		// Dynamicallly allocate a RefundSU object

		cout << "Number of classes: ";
		getline(cin, strinput);
		while (!validate(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		size = stod(strinput);

		if (size <= 0)
		{
			break;
		}
		calc->setSize(size);   // set input for RefundSU member variable size


		for (int i = 0; i < size; i++)
		{
			do
			{
				if (count != 0)
				{
					cout << "Number of credits must be greater than 0. \n"
						 << "Enter the number of credits for class " << i + 1 << ": ";
				}
				else
				{
					cout << "\nNumber of credits for class " << i + 1 << ": ";
				}
				getline(cin, strinput);
				while (!validatedouble(strinput))
				{
					cout << "Please enter a number: ";
					getline(cin, strinput);
					count++;
				}
				count++;
				number = stoi(strinput);
			} while (number <= 0);
			if (count > 1)
			{
				cout << endl;
			}
			count = 0;
			calc->setCreditNumber(i, number);					// set input for RefundSU member vector CreditNumber at position i

			do
			{
				if (count < 1)
				{
					cout << "Part of term for class " << i + 1 << ": ";
				}
				else
				{
					cout << "Parts of term for Summer are 1, 7, 8, and 9.\n"
						 << "Enter the part of term for class " << i + 1 << ": ";
				}
				getline(cin, strinput);
				while (!validate(strinput))
				{
					cout << "Please enter a number: ";
					getline(cin, strinput);
				}
				number = stoi(strinput);
				count++;
			} while (number != 1 && number != 7 && number != 8 && number != 9);
			count = 0;

			calc->setPot(i, number);				// set input for RefundSU member vector Pot at position i	
		}

		cout << "\nPell Grant amount: ";
		getline(cin, strinput);
		while (!validate(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		number = stoi(strinput);
		calc->setPell(number);					// set input for RefundSU member variable Pell

		cout << "\nSubsidized loan amount: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setSub(value);					// set input for RefundSU member variable Sub
		

		cout << "\nUnsubsidized loan amount: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setUnsub(value);					// set input for RefundSU member variable Unsub
		

		cout << "\nTuition Cost: ";
		getline(cin, strinput);
		while (!validatedouble(strinput))
		{
			cout << "Please enter a number: ";
			getline(cin, strinput);
		}
		value = stod(strinput);
		calc->setCost(value);					// set input for RefundFS member variable cost
		

		
		calc->setLoanSplit();
		calc->sort();
		calc->calculateDisb();
		calc->calculatePell();
		calc->calculateLoan();
		calc->calculateRefund();

		PellPot = calc->getPellPot();
		SubLoanPot = calc->getSubLoanPot();
		UnsubLoanPot = calc->getUnsubLoanPot();
		Refund = calc->getRefund();


		cout << setprecision(2) << fixed;
		cout << "\nDISBURSEMENT DATA\n-------------------------------------------------";
		cout << "\nPell Grant amount for Part of Term 1 and 7: " << *PellPot << "\n";
		cout << "Pell Grant amount for Part of term 8: " << *(PellPot + 1) << "\n";
		cout << "Pell Grant amount for Part of term 9: " << *(PellPot + 2) << "\n\n";
		

		cout << "Subsidized loan amount for Part of Term 1 and 7: " << *SubLoanPot << "\n";
		cout << "Subsidized loan amount for Part of term 8: " << *(SubLoanPot + 1) << "\n";
		cout << "Subsidized loan amount for Part of term 9: " << *(SubLoanPot + 2) << "\n\n";
		

		cout << "Subsidized loan amount for 2nd disbursement: " << calc->getSub2nd() << "\n\n";

		cout << "Unsubsidized loan amount for Part of Term 1 and 7: " << *UnsubLoanPot << "\n";
		cout << "Unsubsidized loan amount for Part of term 8: " << *(UnsubLoanPot + 1) << "\n";
		cout << "Unsubsidized loan amount for Part of term 9: " << *(UnsubLoanPot + 2) << "\n\n";

		cout << "Unsubsidized loan amount for 2nd disbursement: " << calc->getUnsub2nd() << "\n\n";

		cout << "REFUND\n-------------------------------------------------";
		cout << "\nRefund Total: " << calc->getRefundTotal() << "\n";
		cout << "\nRefund amount for Part of Term 1 and 7: " << *Refund << "\n";
		cout << "Refund amount for Part of term 8: " << *(Refund + 1) << "\n";
		cout << "Refund amount for Part of term 9: " << *(Refund + 2) << "\n\n";
		

		cout << "Refund amount for 2nd loan disbursement: " << calc->getRefund2nd() << "\n\n";

		cout << "Run another calculation? (Y/N) ";
		cin >> repeat;
		cin.ignore();

		delete calc; // Delete object from memory
		calc = nullptr;
		
		ClearScreen();

	} while (repeat == 'Y' || repeat == 'y');
	ClearScreen();
	
}
void Origination()
{
	ClearScreen();
	char input;
	string fee0;
	double fee;
	bool valid;

	do
	{
		OriginationFee* rate = nullptr;
		rate = new OriginationFee;
		cout << "\t\t\t\tLOAN ORIGINATION FEE\n\n";

		cout << setprecision(6) << defaultfloat;
		cout << "Origination fee is set to: " << rate->getOrigFee() << "\n\n";
		cout << "Change the origination fee? (Y/N): ";
		cin >> input;
		cin.ignore();

		if (input == 'Y' || input == 'y')
		{
			cout << "\nEnter the origination fee as a percentage: ";
			getline(cin, fee0);
			
			valid = validatedouble(fee0);
			while (!valid)
			{
				cout << "\nPlease enter a number as a percentage (e.g. 1.059): ";
				getline(cin, fee0);
				valid = validatedouble(fee0);
			}
			fee = stod(fee0);

			rate->setOrigFee(fee);
		}
		delete rate;
		rate = nullptr;
		ClearScreen();

	} while (input == 'Y' || input == 'y');
	
}
void Info()
{
	ClearScreen();
	char ch;

	cout << "\t\t\t\t\t\t\tINFORMATION\n\n"
		<< "\tThis calculator is a tool that will assist you in determining when a student will receive their refund.\n"
		<< "\tHowever, it will not tell you whether or not a student will have single or multiple loan disbursements for\n"
		<< "\tthe Fall / Spring semesters as this can depend on factors outside the semester in question such as whether or\n"
		<< "\tnot the student requested a one term only loan or is starting in the Spring semester.For more information\n"
		<< "\ton how to determine the number of loan disbursements for Spring / Fall, refer to department training resources.\n\n"

		<< "\tHOW TO USE\n"
		<< "\t---------------------------\n"
		<< "\t1. Select the correct semester from the main menu.\n"
		<< "\t2. Follow prompts and enter required information.For the Fall / Spring semester, enter \"Y\" for Loan Split if\n"
		<< "\t   there will be more than one loan disbursement and \"N\" if there will only be one.\n"
		<< "\t3. Once a calculation is performed, enter \"Y\" to run another calculation or \"N\" to return to the main menu.\n"
		<< "\t*  If the wrong semester is chosen, you can enter 0 for the number of classes to return to the main menu\n"
		<< "\t   without having to run through an entire calculation.\n\n"

		<< "\tORIGINATION FEE\n"
		<< "\t---------------------------\n"
		<< "\t1. To set the origination fee, select option 3 from the main menu.\n"
		<< "\t2. The current origination fee will be displayed and you will be given\n"
		<< "\t   the option to change it by entering \"Y\" or \"N\" (If it is the first\n"
		<< "\t   time running the program, the origination fee will be set to 0 however,\n"
		<< "\t   once you set the fee, it will remain until you choose to change it).\n"
		<< "\t3. If the loans in banner have memoed and had the origination fee amount\n"
		<< "\t   deducted already, you will either want to use the original award amounts\n"
		<< "\t   when entering the loan amounts into the calculator, or set the origination\n"
		<< "\t   fee to zero to avoid deducting the origination fee % twice.";


	cout << "\n\n\tPress Enter to return to main menu.\n";
	
	ch = cin.get();
	ClearScreen();
	

}
bool validate(string s)
{
	 int size = s.size();
	 char* sarray = &s[0];

	 for (int i = 0; i < size; i++)
	 {
		 *(sarray + i) = s[i];
	 }

	 for (int i = 0; i < size; i++)
	 {
		 if (!isdigit(*(sarray + i)))
		 {
			 return false;
		 }
	 }
	 return true;

}
bool validatedouble(string s)
{
	int count = 0;
	int size = s.size();
	char* sarray = &s[0];

	for (int i = 0; i < size; i++)
	{
		*(sarray + i) = s[i];
	}

	for (int i = 0; i < size; i++)
	{
		if (!isdigit(*(sarray + i)) && *(sarray + i) != '.' )
		{
			return false;
		}
		if (*(sarray + i) == '.')
		{
			count++;
		}
	}
	if (count > 1)
	{
		return false;
	}
	return true;
	
}
