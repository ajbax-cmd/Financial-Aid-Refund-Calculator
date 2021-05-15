#ifndef REFUNDSU_H
#define REFUNDSU_H
#include <vector>
using namespace std;

class RefundSU
{
private:
	int const THREE = 3;				// Number of disbursement periods
	int size;							// Number of classes student is taking
	int Pell;							// Pell Grant total
	int FTPell;							// Pell Grant amount if student was FT
	int PellPot[3] = { 0 };				// Array holding Pell Grant amounts for each POT disbursement
	double SubLoanPot[3] = { 0 };		// Array holding Sub loan amounts for each POT disbursement
	double UnsubLoanPot[3] = { 0 };		// Array holding Unsub loan amounts for each POT disbursement
	double disb[3] = { 0 }; 			// Array to conatain the number of credits for each disbursement period
	double Refund[3] = { 0 };			// Array to contain refund amounts for each disbursement period
	double Refund2nd = 0;				// Refund amount from 2nd disbursement of loans that have split disbursements
	double cost;						// Cost of tuition
	double Sub;							// Total amount of subsidized loan student is receiving
	double Sub2nd = 0;					// Variable to hold 2nd half of sub loans that have two disbursements
	double Unsub;						// Total amount of unsubsidized loan student is receiving
	double Unsub2nd = 0;				// Variable to hold 2nd half of unsub loans that have two disbursements
	bool loanSplit = false;				// Boolean indicates if loans have two disbursements or not
	vector <double> creditNumber;		// 2 parallel vectors contianing values for number of credits and part of term for each class
	vector <int> pot;					// 2 parallel vectors contianing values for number of credits and part of term for each class

public:
	void setSize(int);
	void setPell(int);
	void setCost(double);
	void setSub(double);
	void setUnsub(double);
	void setCreditNumber(int, double);
	void setPot(int, int);
	void setLoanSplit();

	vector<double> getCreditNumber()
	{
		return creditNumber;
	}
	vector<int> getPot()
	{
		return pot;
	}
	int getTHREE() const
	{
		return THREE;
	}
	int getSize() const
	{
		return size;
	}
	int getPell() const
	{
		return Pell;
	}
	int* getPellPot()
	{
		return &PellPot[0];
	}
	double* getSubLoanPot()
	{
		return &SubLoanPot[0];
	}
	double* getUnsubLoanPot()
	{
		return &UnsubLoanPot[0];
	}
	double* getDisb()
	{
		return &disb[0];
	}
	double* getRefund()
	{
		return &Refund[0];
	}
	double getRefund2nd() const
	{
		return Refund2nd;
	}
	double getCost() const
	{
		return cost;
	}
	double getSub() const
	{
		return Sub;
	}
	double getSub2nd() const
	{
		return Sub2nd;
	}
	double getUnsub() const
	{
		return Unsub;
	}
	double getUnsub2nd() const
	{
		return Unsub2nd;
	}
	
	double getRefundTotal();
	void calculatePell();
	void calculateLoan();
	int getFTPell();
	void sort();
	void swap(int& a, int& b);
	void swap(double& a, double& b);
	int getLast();
	void calculateDisb();
	void calculateRefund();
	double getSum();


};
#endif
