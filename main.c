#include <stdio.h>
#include <math.h>
#include "DEAL.h"

#define INTEREST		.03110
#define COMPOUND_RATE	12
#define PAY_RATE		12
#define LOAN_LENGTH		30 * 12

double Payment(double principle, double interest, int period)
{
	double denominator;
	double numerator;

	numerator = interest * pow((1 + interest), period);
	denominator = pow((1 + interest), period) - 1;

	return principle * (numerator / denominator);
}

double rate(double interest, int CompNum, int payNum)
{
	double power = (double) CompNum / payNum;
	double helper = interest / CompNum;

	return pow(1 + helper, power) - 1;
}

void print(double home,  double down)
{
	int i = 1;
	double amount_count = 0;
	double principal_count = 0;
	double interest_count = 0;
	double balance = home - down;
	double amount = Payment(balance,
		rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH);

	printf("%-10s %-10s %-10s %-10s %-10s\n", "Payment", "Amount",\
		"Interest", "Principal", "Balance");
	printf("%-10s %-10s %-10s %-10s %-10.2lf\n", "", "", "", "", balance);

	while (round(balance) > 0) {
		amount_count += amount;
		principal_count += amount - (balance * rate(INTEREST,
			COMPOUND_RATE, PAY_RATE));

		interest_count += balance * rate(INTEREST, COMPOUND_RATE,
			PAY_RATE);

		printf("%-10i %-10.2lf %-10.2lf %-10.2lf %-10.2lf\n",
			i, amount, balance * rate(INTEREST, COMPOUND_RATE,
			PAY_RATE), amount - (balance * rate(INTEREST,
			COMPOUND_RATE, PAY_RATE)), balance - (amount -
			(balance * rate(INTEREST, COMPOUND_RATE, PAY_RATE))));

		balance -= (amount - (balance * rate(INTEREST, COMPOUND_RATE,
			PAY_RATE)));

		if (i % 12 == 0) {
			printf("---------------------------------------------\
				----------\n");

			printf("%-10s %-10.2lf %-10.2lf %-10.2lf %-10.2lf\n",
				"total", amount_count, interest_count,
				principal_count, balance);

			printf("-----------------------------------------------\
				--------\n");
		}
		i++;
	}
}


int main()
{
	double home = 0;
	double down = 0;

	DEAL deal;

	printf("Asking Price:");
	scanf("%d", &deal.asking_price);

	printf("Market Price:");
	scanf("%d", &deal.market_price);

	printf("HOA:");
	scanf("%d", &deal.hoa);

	printf("Monthly Rent:");
	scanf("%d", &deal.monthly_rent);

	printf("Enter your home price: ");
	scanf("%lf", &home);
	printf("Enter down payment: ");
	scanf("%lf", &down);

	print(home, down);
	return 0;
}
