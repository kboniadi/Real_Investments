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

double compund_interest(double principle, double rate, int time)
{
	return principle * pow(1 + rate, time);
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

int calc_annual_amortization(double balance, int months_paid)
{
	int i = 1;
	double amount_count = 0;
	double principal_count = 0;
	double interest_count = 0;
	double amount = payment(balance,
		rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH -
		months_paid);

	for (int i = 0; i < 12; i++) {
		principal_count += amount - (balance * rate(INTEREST,
			COMPOUND_RATE, PAY_RATE));

		balance -= (amount - (balance * rate(INTEREST, COMPOUND_RATE,
			PAY_RATE)));
	}
	return principal_count;
}

void print_chart(char **header, char **sidebar, char ***data, int width,
	int height, int column_width) {

	char text_spacer[10]; //i don't know 10 seems like a good number
	char data_spacer[10]; //i don't know 10 seems like a good number
	int height_index = 0;

	strcpy(data_spacer, "");
	strcat(data_spacer, "%");
	strcat(data_spacer, itoa(column_width, (char[50]){}, 50));
	strcat(data_spacer, "s");

	strcpy(text_spacer, "");
	strcat(text_spacer, "%-");
	strcat(text_spacer, itoa(column_width, (char[50]){}, 50));
	strcat(text_spacer, "s");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	printf("|");
	printf(text_spacer, "");
	printf("|");

	for (int i = 0; i < width; i++) {
		printf(text_spacer, header[i]);
		printf("|");
	}
	printf("\n");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	while (height_index < height) {
		printf("|");

		printf(text_spacer, sidebar[height_index]);
		printf("|");

		for (int i = 0; i < width; i++) {
			printf(data_spacer, data[i][height_index]);
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
	char text_spacer[10]; //i don't know 10 seems like a good number
	char data_spacer[10]; //i don't know 10 seems like a good number
	int height_index = 0;

	strcpy(data_spacer, "");
	strcat(data_spacer, "%");
	strcat(data_spacer, itoa(column_width, (char[50]){}, 50));
	strcat(data_spacer, "s");

	strcpy(text_spacer, "");
	strcat(text_spacer, "%-");
	strcat(text_spacer, itoa(column_width, (char[50]){}, 50));
	strcat(text_spacer, "s");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	printf("|");
	printf(text_spacer, "");
	printf("|");

	printf(text_spacer, header);
	printf("|");
	printf("\n");

	draw_line(((width + 1) * (column_width + 1)) + 1);

	while (height_index < height) {
		printf("|");

		printf(text_spacer, sidebar[height_index]);
		printf("|");

		printf(data_spacer, data[height_index]);
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

char* itoa(int val, char *out, int size) {
	snprintf(out, size, "%d", val);
	return out;
}

char* ftoa(double input, char *out, int size) {
	//for now two decimal places. Should be changed later

	setlocale(LC_NUMERIC, "");
	snprintf(out, size, "%'.2lf", input);
	return out;
}

char* ftoa_p(double input, char *out, int size) {
	//for now two decimal places. Should be changed later
	snprintf(out, size, "%.2lf%%", input);
	return out;
}

#define LOW_RATE -0.5
#define HIGH_RATE 0.5
#define MAX_ITERATION 1000
#define PRECISION_REQ 0.00000001
double computeIRR(double cf[], int numOfFlows)
{
    int i = 0, j = 0;
    double m = 0.0;
    double old = 0.00;
    double new = 0.00;
    double oldguessRate = LOW_RATE;
    double newguessRate = LOW_RATE;
    double guessRate = LOW_RATE;
    double lowGuessRate = LOW_RATE;
    double highGuessRate = HIGH_RATE;
    double npv = 0.0;
    double denom = 0.0;
    for (i=0; i<MAX_ITERATION; i++)
    {
        npv = 0.00;
        for (j=0; j<numOfFlows; j++)
        {
            denom = pow((1 + guessRate),j);
            npv = npv + (cf[j]/denom);
        }

        /* Stop checking once the required precision is achieved */
        if ((npv > 0) && (npv < PRECISION_REQ))
            break;
        if (old == 0)
            old = npv;
	    else
                old = new;
            new = npv;
            if (i > 0)
            {
                if (old < new)
                {
                    if (old < 0 && new < 0)
                        highGuessRate = newguessRate;
                    else
                        lowGuessRate = newguessRate;
                }
                else
                {
                    if (old > 0 && new > 0)
                        lowGuessRate = newguessRate;
                    else
                        highGuessRate = newguessRate;
                    }
            }
            oldguessRate = guessRate;
            guessRate = (lowGuessRate + highGuessRate) / 2;
            newguessRate = guessRate;
        }
        return guessRate;
    }
