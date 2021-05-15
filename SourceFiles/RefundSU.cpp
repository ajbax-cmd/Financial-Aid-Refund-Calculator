#include "RefundSU.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <vector>
#include <stdlib.h>
using namespace std;

void RefundSU::setSize(int s)
{
	size = s;
	creditNumber.resize(size);
	pot.resize(size);
}
void RefundSU::setPell(int p)
{
	Pell = p;
}
void RefundSU::setCost(double c)
{
	cost = c;
}
void RefundSU::setSub(double s)
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
void RefundSU::setUnsub(double u)
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
void RefundSU::setCreditNumber(int index, double input)
{
	creditNumber[index] = input;
}
void RefundSU::setPot(int index, int input)
{
	pot[index] = input;
}

void RefundSU::swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}
void RefundSU::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

double RefundSU::getSum()
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += creditNumber[i];
	}
	return total;
}
//********************************************
// setLoanSplit Function
// Determines if student is at least half
// time for POT 1 and 7
//
//********************************************
void RefundSU::setLoanSplit()
{
	int total = 0;
	for (int i = 0; i < size; i++)
	{
		if (pot[i] == 1 || pot[i] == 7)
		{
			total += creditNumber[i];
		}
	}
	if (total > 5)
	{
		loanSplit = true;
	}
}


//***************************************************************************************
// Sort Function																		*
// First uses a bubble sort to sort in ascending order. Parts of term are then swapped  *
// to occur in the order they are disbursed. Parts of term 0,1,2,4 are disbursed first, *
// Part of term 5 second, Part of term 3 3rd, and part of term 6 last. If all parts of  *
// term are being used, the result will be 0,1,2,4,5,3,6.    						    *
//***************************************************************************************
void RefundSU::sort()
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
}

int RefundSU::getFTPell()
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
int RefundSU::getLast()
{
	int last;
	bool Notfound = true;
	for (int i = THREE - 1; i > -1 && Notfound; i--)
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
void RefundSU::calculateDisb()
{

	double count = 0;


	for (int i = 0; i < size && count < 13; i++)
	{
		if (pot[i] == 0 || pot[i] == 1 || pot[i] == 7)
		{
			disb[0] += creditNumber[i];
			count += creditNumber[i];
		}
		else if (pot[i] == 8)
		{
			disb[1] += creditNumber[i];
			count += creditNumber[i];
		}
		else if (pot[i] == 9)
		{
			disb[2] += creditNumber[i];
			count += creditNumber[i];
		}
	
	}

}

//*****************************************************
// calculatePell Function
// Uses the disb array to assign Pell Grant amounts to
// the PellPot array based on how many credits are in
// each disbursement period. The last disbursement period
// in the disb array to hold credits will have the remainder
// of their total Pell from what was already disbursed. 
// Every other disbursement period based off of the following:
// 
//***************************************************	
void RefundSU::calculatePell()
{
	int FTPell = getFTPell();
	int last = getLast();

	int total = 0;

	for (int i = 0; i < THREE; i++)
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

void RefundSU::calculateLoan()
{

	if (loanSplit)
	{
		SubLoanPot[0] = Sub / 2;
		UnsubLoanPot[0] = Unsub / 2;

		Sub2nd = Sub / 2;
		Unsub2nd = Unsub / 2;
		
	}
	else
	{
		int total = 0;

		for (int i = 0; i < THREE && total < 6; i++)
		{
			total += disb[i];
			if (total > 5)
			{
				SubLoanPot[i] = Sub;
				UnsubLoanPot[i] = Unsub;
				i = 3;
			}
		}
	}
}

void RefundSU::calculateRefund()
{
	double total2nd = Sub2nd + Unsub2nd;
	double total[3];
	for (int i = 0; i < 3; i++)
	{
		total[i] = PellPot[i] + SubLoanPot[i] + UnsubLoanPot[i];
	}

	cost *= -1;


	for (int i = 0; i < 3; i++)
	{
		if (i == 1) // Refund2nd pays out prior to or at same time as 2nd disbursment
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
double RefundSU::getRefundTotal()
{
	double total = 0;
	for (int i = 0; i < THREE; i++)
	{
		total += Refund[i];
	}
	total += Refund2nd;
	return total;
}

