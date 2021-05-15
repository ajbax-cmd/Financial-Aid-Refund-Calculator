#include "RefundFS.h"
#include "OriginationFee.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <vector>
#include <stdlib.h>
using namespace std;

void RefundFS::setSize(int s)
{
	size = s;
	creditNumber.resize(size);
	pot.resize(size);
}
void RefundFS::setPell(int p)
{
	Pell = p;
}
void RefundFS::setCost(double c)
{
	cost = c;
}
void RefundFS::setSub(double s)
{
	double Ofee;
	fstream File;
	File.open("OriginationFee.txt", ios::in);
	if (File.fail())
	{
		Ofee = 0.00;
	}
	else
	{
		File >> Ofee;
	}
	File.close();

	
	Sub = (1 - (Ofee * .01)) * s;
}
void RefundFS::setUnsub(double u)
{
	double Ofee;
	fstream File;
	File.open("OriginationFee.txt", ios::in);
	if (File.fail())
	{
		Ofee = 0.00;
	}
	else
	{
		File >> Ofee;
	}
	File.close();

	Unsub = (1 - (Ofee * .01)) * u;
}
void RefundFS::setCreditNumber(int index, double input)
{
	creditNumber[index] = input;
}
void RefundFS::setPot(int index, int input)
{
	pot[index] = input;
}
void RefundFS::setLoanSplit(char input)
{
	loanSplit = getSplit(input);
}

void RefundFS::swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}
void RefundFS::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

double RefundFS::getSum()
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += creditNumber[i];
	}
	return total;
}

bool RefundFS::getSplit(char input)
{
	bool output = false;
	if (input == 'Y' || input == 'y')
		output = true;
	else
		output = false;

	return output;
}
//***************************************************************************************
// Sort Function																		*
// First uses a bubble sort to sort in ascending order. Parts of term are then swapped  *
// to occur in the order they are disbursed. Parts of term 0,1,2,4 are disbursed first, *
// Part of term 5 second, Part of term 3 3rd, and part of term 6 last. If all parts of  *
// term are being used, the result will be 0,1,2,4,5,3,6.    						    *
//***************************************************************************************
void RefundFS::sort()
{

	int maxElement;
	int index;

	for (maxElement = size - 1; maxElement > 0; maxElement--)
	{
		for (index = 0; index < maxElement; index++)
		{
			if (pot[index] > pot[index + 1])
			{
				swap(pot[index], pot[index + 1]);
				swap(creditNumber[index], creditNumber[index + 1]);
			}
		}
	}

	for (maxElement = size - 1; maxElement > 0; maxElement--)
	{
		for (index = 0; index < maxElement; index++)
		{
			if (pot[index] == 3 && pot[index + 1] == 4)
			{
				swap(pot[index], pot[index + 1]);
				swap(creditNumber[index], creditNumber[index + 1]);
			}
		}
	}

	for (maxElement = size - 1; maxElement > 0; maxElement--)
	{
		for (index = 0; index < maxElement; index++)
		{
			if (pot[index] == 3 && pot[index + 1] == 5)
			{
				swap(pot[index], pot[index + 1]);
				swap(creditNumber[index], creditNumber[index + 1]);
			}
		}
	}
}

int RefundFS::getFTPell()
{
	int FTPell = 0;
	double sum = getSum();

	if (sum < 6 && sum > 0)
		FTPell = Pell / .25;
	else if (sum < 9)
		FTPell = Pell / .5;
	else if (sum < 12)
		FTPell = Pell / .75;
	else
		FTPell = Pell;

	return FTPell;

}

//*******************************************************************
// getLast function calculates which disbursement period 			*
// 	is the last to have credits registered. This last 			 	*
//  period will have whatever is left of the original Pell award. 	*
//*******************************************************************
int RefundFS::getLast()
{
	int last;
	bool Notfound = true;
	for (int i = FOUR - 1; i > -1 && Notfound; i--)
	{
		if (disb[i] != 0)
		{
			last = i;
			Notfound = false;
		}

	}
	return last;
}
//*******************************************************************
// getDisb function assigns the correct number of credits to each   *
// corresponding disbursement period in the disb[]. There are four  *
// disbursement dates. POT L, 1, 2, and 4 are the 1st (disb[0]).    *
// POT 5 is the 2nd (disb[1]). POT 3 is the 3rd (dib[2]). POT 6 is  *
// the 4th disbursement (disb[3]).									*
//*******************************************************************
void RefundFS::calculateDisb()
{

	double count = 0;


	for (int i = 0; i < size && count < 13; i++)
	{
		if (pot[i] == 0 || pot[i] == 1 || pot[i] == 2 || pot[i] == 4)
		{
			disb[0] += creditNumber[i];
			count += creditNumber[i];
		}
		else if (pot[i] == 5)
		{
			disb[1] += creditNumber[i];
			count += creditNumber[i];
		}
		else if (pot[i] == 3)
		{
			disb[2] += creditNumber[i];
			count += creditNumber[i];
		}
		else if (pot[i] == 6)
		{
			disb[3] += creditNumber[i];
			count += creditNumber[i];
		}
	}

}

//****************************************************************
// calculatePell Function
// Uses the disb array to assign Pell Grant amounts to
// the PellPot array based on how many credits are in
// each disbursement period. The last disbursement period
// in the disb array to hold credits will have the remainder
// of their total Pell from what was already disbursed. 
// Every other disbursement period based off of the following:
// 
//********************************************************************	
void RefundFS::calculatePell()
{
	int FTPell = getFTPell();
	int last = getLast();

	int total = 0;

	for (int i = 0; i < FOUR; i++)
	{
		if (i == last)
		{
			PellPot[i] = Pell - total;
		}
		else
		{
			if (disb[i] < 6 && disb[i] > 0)
			{
				PellPot[i] = FTPell * .25;
			}
			else if (disb[i] < 9 && disb[i] > 5)
			{
				PellPot[i] = FTPell * .5;
			}
			else if (disb[i] < 12 && disb[i] > 8)
			{
				PellPot[i] = FTPell * .75;
			}
			else if (disb[i] >= 12)
			{
				PellPot[i] = FTPell;
			}
			total += PellPot[i];
		}
	}
}

void RefundFS::calculateLoan()
{

	if (loanSplit)
	{
		int total = 0;

		for (int i = 0; i < FOUR && total < 6; i++)
		{
			total += disb[i];
			if (total > 5)
			{
				if (i > 1)
				{
					SubLoanPot[i] = Sub;
					UnsubLoanPot[i] = Unsub;
				}
				else
				{
					SubLoanPot[i] = Sub / 2;
					UnsubLoanPot[i] = Unsub / 2;

					Sub2nd = Sub / 2;
					Unsub2nd = Unsub / 2;
				}
				i = 4;
			}
		}
	}
	else
	{
		int total = 0;

		for (int i = 0; i < FOUR && total < 6; i++)
		{
			total += disb[i];
			if (total > 5)
			{
				SubLoanPot[i] = Sub;
				UnsubLoanPot[i] = Unsub;
				i = 4;
			}
		}
	}
}

void RefundFS::calculateRefund()
{
	double total2nd = Sub2nd + Unsub2nd;
	double total[4];
	for (int i = 0; i < 4; i++)
	{
		total[i] = PellPot[i] + SubLoanPot[i] + UnsubLoanPot[i];
	}

	cost *= -1;

	// Refund2nd pays out prior to 3rd disbursment
	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			Refund2nd = total2nd + cost;
			if (Refund2nd < 0)
			{
				Refund2nd = 0;
			}
			cost += total2nd;
			if (cost > 0)
			{
				cost = 0;
			}

		}
		Refund[i] = total[i] + cost;
		if (Refund[i] < 0)
		{
			Refund[i] = 0;
		}
		cost += total[i];
		if (cost > 0)
		{
			cost = 0;
		}
	}
}
double RefundFS::getRefundTotal()
{
	double total = 0;
	for (int i = 0; i < FOUR; i++)
	{
		total += Refund[i];
	}
	total += Refund2nd;
	return total;
}
