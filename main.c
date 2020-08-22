#include <stdio.h>
#include "DEAL.h"
#include "TOOLS.h"
#include "LIMITS.h"
#include "operators.h"

/*
we have to eventually calculate holding costs...
we should also calculate IRR
it's Principal not principle
*/

//double Payment(double principle, double interest, int period)
//{
//	double denominator;
//	double numerator;
//
//	numerator = interest * pow((1 + interest), period);
//	denominator = pow((1 + interest), period) - 1;
//
//	return principle * (numerator / denominator);
//}
//
//double rate(double interest, int CompNum, int payNum)
//{
//	double power = (double) CompNum / payNum;
//	double helper = interest / CompNum;
//
//	return pow(1 + helper, power) - 1;
//}
//
//void print(double home,  double down)
//{
//	int i = 1;
//	double amount_count = 0;
//	double principal_count = 0;
//	double interest_count = 0;
//	double balance = home - down;
//	double amount = Payment(balance,
//		rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH * 12);
//
//	printf("%-10s %-10s %-10s %-10s %-10s\n", "Payment", "Amount",\
//		"Interest", "Principal", "Balance");
//	printf("%-10s %-10s %-10s %-10s %-10.2lf\n", "", "", "", "", balance);
//
//	while (round(balance) > 0) {
//		amount_count += amount;
//		principal_count += amount - (balance * rate(INTEREST,
//			COMPOUND_RATE, PAY_RATE));
//
//		interest_count += balance * rate(INTEREST, COMPOUND_RATE,
//			PAY_RATE);
//
//		printf("%-10i %-10.2lf %-10.2lf %-10.2lf %-10.2lf\n",
//			i, amount, balance * rate(INTEREST, COMPOUND_RATE,
//			PAY_RATE), amount - (balance * rate(INTEREST,
//			COMPOUND_RATE, PAY_RATE)), balance - (amount -
//			(balance * rate(INTEREST, COMPOUND_RATE, PAY_RATE))));
//
//		balance -= (amount - (balance * rate(INTEREST, COMPOUND_RATE,
//			PAY_RATE)));
//
//		if (i % 12 == 0) {
//			printf("---------------------------------------------"
//		  "----------\n");
//
//			printf("%-10s %-10.2lf %-10.2lf %-10.2lf %-10.2lf\n",
//				"total", amount_count, interest_count,
//				principal_count, balance);
//
//			printf("-----------------------------------------------"
//				"--------\n");
//		}
//		i++;
//	}
//}

int main()
{
	DEAL deal;

	init_deal(&deal);

	calculate_deal(&deal);

	struct Operator *op = CreateOperator();
	double home = 0;
	double down = 0;

	FloatType left;
	FloatType right;
	FloatType newNum;

	ConvertToFloatType(&left, 123.4523);
	ConvertToFloatType(&right, 554.12);

	op->divi(&left, &right, &newNum);
	printf("%i, %i, %i\n", (int) left.scale, (int) right.scale, (int) newNum.scale);
//	printf("%i, %i, %i\n", (int) left.precision, (int) right.precision, (int) newNum.precision);
	printf("%i, %i, %lld\n", (int) left.scaledNum, (int) right.scaledNum, (long long) newNum.scaledNum);
	printf("%lf, %lf, %lf\n", ConvertToDouble(&left), ConvertToDouble(&right), ConvertToDouble(&newNum));

	printf("%lf\n", ConvertToDouble(&left));
	op->absolute(&left);
	printf("%lf", ConvertToDouble(&left));

	/*
	DEAL deal;
	int rehab_cost;
	int down_payment;
	int monthly_mortgage;
	int max_mortgage;
	int purchase_price;
	int year_one_amortization;
	int year_one_cash_in;
	int max_loan;

	printf("Market Price:");
	scanf("%d", &deal.market_price);

	printf("HOA:");
	scanf("%d", &deal.hoa);

	printf("Monthly Rent:");
	scanf("%d", &deal.monthly_rent);

	printf("Rehab Cost:");
	scanf("%d", &rehab_cost);

	printf("Purchase pricerape:");
	scanf("%d", &purchase_price);


	int fees_without_mortgage = (deal.monthly_rent * MONTHLY_RENTAL_FEES) +
		MINIMUM_CASH_FLOW_MONTHLY + deal.hoa +
		((deal.market_price * YEARLY_PROP_TAXES) / 12) +
		((deal.market_price * YEARLY_HOME_INSURANCE) / 12);

	max_mortgage = deal.monthly_rent - fees_without_mortgage;

	printf("Max mortgage: %d\n", max_mortgage);

	max_loan = principle(max_mortgage, rate(INTEREST, COMPOUND_RATE,
		PAY_RATE), LOAN_LENGTH);
	printf("Max mortgage: %lf\n", max_loan);
	*/

	/*
	down_payment = purchase_price * 0.2;

	printf("Down Payment:%d\n", down_payment);

	monthly_mortgage = payment(deal.market_price - (down_payment +
		(deal.market_price - purchase_price)), rate(INTEREST, COMPOUND_RATE, PAY_RATE),
		LOAN_LENGTH);

	printf("Monthly mortgage without fees:%d\n", monthly_mortgage);

	monthly_mortgage += (deal.market_price * YEARLY_HOME_INSURANCE) / 12;
	monthly_mortgage += (deal.market_price * YEARLY_PROP_TAXES) / 12;
	monthly_mortgage += deal.hoa;

	printf("Monthly mortgage:%d\n", monthly_mortgage);

	monthly_mortgage += (deal.monthly_rent * RENTAL_FEES);

	printf("Monthly mortgage after fees:%d\n", monthly_mortgage);

	max_mortgage = deal.monthly_rent - ((deal.monthly_rent * RENTAL_FEES) +
		MINIMUM_CASH_FLOW_MONTHLY);

	printf("Max mortgage:%d\n", max_mortgage);

	year_one_amortization = calc_year_one_amortization(deal.market_price,
		(down_payment +
			(deal.market_price - purchase_price)));
	printf("Year one Amortization:%d\n", year_one_amortization);

	printf("Year one return:%d\n", year_one_amortization +
		((deal.monthly_rent - monthly_mortgage) * 12));

	year_one_cash_in = rehab_cost + down_payment;
	printf("Year one cash in:%d\n", year_one_cash_in);
	*/

	return 0;
}
