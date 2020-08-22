#include "TOOLS.h"

double payment(double principle, double interest, int period)
{
	double denominator;
	double numerator;

	numerator = interest * pow((1 + interest), period);
	denominator = pow((1 + interest), period) - 1;

	return principle * (numerator / denominator);
}

double principle(double payment, double interest, int period)
{
	double denominator;
	double numerator;
	double principle;

	numerator = interest * pow((1 + interest), period);
	denominator = pow((1 + interest), period) - 1;

	return payment * (denominator / numerator);
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
	double amount = payment(balance,
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
			for (int i = 0; i < 55; i++)
				printf("-");
			printf("\n");

			printf("%-10s %-10.2lf %-10.2lf %-10.2lf %-10.2lf\n",
				"total", amount_count, interest_count,
				principal_count, balance);

			for (int i = 0; i < 55; i++)
				printf("-");
			printf("\n");
		}
		i++;
	}
}

int calc_year_one_amortization(double home,  double down)
{
	int i = 1;
	double amount_count = 0;
	double principal_count = 0;
	double interest_count = 0;
	double balance = home - down;
	double amount = payment(balance,
		rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH);

	for (int i = 0; i < 12; i++) {
		principal_count += amount - (balance * rate(INTEREST,
			COMPOUND_RATE, PAY_RATE));
	}
	return principal_count;
}

void print_chart(char **header, char **sidebar, char ***data, int width,
	int height, int column_width) {

	char printf_spacer[10]; //i don't know 10 seems like a good number
	int height_index = 0;

	strcpy(printf_spacer, "");
	strcat(printf_spacer, "%-");
	strcat(printf_spacer, itoa(column_width));
	strcat(printf_spacer, "s");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	printf("|");
	printf(printf_spacer, "");
	printf("|");

	for (int i = 0; i < width; i++) {
		printf(printf_spacer, header[i]);
		printf("|");
	}
	printf("\n");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	while (height_index < height) {
		printf("|");

		printf(printf_spacer, sidebar[height_index]);
		printf("|");

		for (int i = 0; i < width; i++) {
			printf(printf_spacer, data[height_index][i]);
			printf("|");
		}

		printf("\n");

		height_index++;
	}


	draw_line(((width + 1) * (column_width + 1)) + 1);
}

void print_chart_single(char *header, char **sidebar, char **data, int height,
	int column_width) {

	int width = 1;
	char printf_spacer[10]; //i don't know 10 seems like a good number
	int height_index = 0;

	strcpy(printf_spacer, "");
	strcat(printf_spacer, "%-");
	strcat(printf_spacer, itoa(column_width));
	strcat(printf_spacer, "s");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	printf("|");
	printf(printf_spacer, "");
	printf("|");

	printf(printf_spacer, header);
	printf("|");
	printf("\n");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	while (height_index < height) {
		printf("|");

		printf(printf_spacer, sidebar[height_index]);
		printf("|");

		printf(printf_spacer, data[height_index]);
		printf("|");

		printf("\n");

		height_index++;
	}


	draw_line(((width + 1) * (column_width + 1)) + 1);
}

void draw_line(int width) {
	for (int i = 0; i < width; i++)
		printf("-");
	printf("\n");
}

char* itoa(int val) {

	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= 10)

		buf[i] = "0123456789abcdef"[val % 10];

	return &buf[i+1];

}

char* ftoa(double input, char *out, int size) {
	//for now two decimal places. Should be changed later
	//for the love of god put in some commas
	snprintf(out, size, "%.2lf", input);
	return out;
}
