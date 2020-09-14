#include "DEAL.h"

void init_deal(DEAL *deal) {
	double max_debt;

	printf("Asking Price:");
	scanf("%lf", &deal->asking_price);

	printf("Market Price:");
	scanf("%lf", &deal->market_price);

	printf("HOA fee:");
	scanf("%lf", &deal->hoa);

	printf("Monthly Rent:");
	scanf("%lf", &deal->monthly_rent);

	deal->purchase_price = 0;
	deal->down_payment = 0;
	deal->rehab_cost = 0;
	deal->mortgage = 0;

	//filling some default values in
	deal->capex = MONTHLY_CAPEX * deal->monthly_rent;
	deal->vacancy = MONTHLY_VACANCY * deal->monthly_rent;
	deal->management = MONTHLY_MANAGEMENT * deal->monthly_rent;
	deal->repairs = MONTHLY_REPAIRS * deal->monthly_rent;
	deal->taxes = (deal->market_price * YEARLY_PROP_TAXES) / 12.0;
	deal->insurance = (deal->market_price * YEARLY_HOME_INSURANCE) / 12.0;
	deal->cash_out = 0;

	deal->mortgage = deal->monthly_rent - (deal->capex + deal->vacancy +
		deal->management + deal->repairs + deal->taxes +
		deal->insurance + deal->hoa + MINIMUM_CASH_FLOW_MONTHLY);

	max_debt = principle(deal->mortgage, rate(INTEREST, COMPOUND_RATE,
		PAY_RATE), LOAN_LENGTH);

		/*
	deal->purchase_price = max_debt / .80;

	deal->down_payment = DEFAULT_DOWN_PAYMENT * deal->purchase_price;

	interest rate
	*/
	deal->purchase_price = deal->market_price * 0.90;

	deal->down_payment = DEFAULT_DOWN_PAYMENT * deal->purchase_price;

	//deal->down_payment = deal->purchase_price - max_debt;

	deal->rehab_cost = (deal->market_price - deal->purchase_price) / 2.0;
}

void modify_values(DEAL *deal) {
	int input;

	while (1) {
		printf("\nWhich would you like to modify? :");
		scanf("%d", &input);

		printf("\nPlease input new value:");
		switch(input) {
		case 1:
			scanf("%lf", &deal->asking_price);
			break;
		case 2:
			scanf("%lf", &deal->market_price);
			break;
		case 3:
			scanf("%lf", &deal->purchase_price);
			break;
		case 4:
			scanf("%lf", &deal->down_payment);
			break;
		case 5:
			scanf("%lf", &deal->rehab_cost);
			break;
		case 6:
			scanf("%lf", &deal->taxes);
			break;
		case 7:
			scanf("%lf", &deal->insurance);
			break;
		case 8:
			scanf("%lf", &deal->hoa);
			break;
		case 9:
			scanf("%lf", &deal->capex);
			break;
		case 10:
			scanf("%lf", &deal->repairs);
			break;
		case 11:
			scanf("%lf", &deal->vacancy);
			break;
		case 12:
			scanf("%lf", &deal->management);
			break;
		case 13:
			scanf("%lf", &deal->monthly_rent);
			break;
		case 14:
			scanf("%lf", &deal->cash_out);
			break;
		default:
			printf("Unrecognized value. Exiting.\n");
			return;
		}

		printf("\n");
		calculate_deal(deal);
	}
}

void calculate_deal(DEAL *deal) {
	double noi;
	double cap_rate;
	double cash_flow;
	double coc;
	double roi;
	double irr;
	double max_cash_out;

	deal->taxes = (deal->market_price * YEARLY_PROP_TAXES) / 12.0;
	deal->insurance = (deal->market_price * YEARLY_HOME_INSURANCE) / 12.0;

	deal->mortgage = payment(deal->purchase_price - deal->down_payment +
		deal->cash_out, rate(INTEREST, COMPOUND_RATE, PAY_RATE),
		LOAN_LENGTH);

	noi = (deal->monthly_rent - (deal->capex + deal->vacancy +
		deal->management + deal->repairs + deal->taxes +
		deal->insurance + deal->hoa)) * 12.0;

	cap_rate = (noi / deal->purchase_price) * 100;

	cash_flow = noi - (deal->mortgage * 12);

	coc = (cash_flow / (deal->rehab_cost + deal->down_payment)) * 100;

	double year_one_amortization = calc_annual_amortization(
		deal->purchase_price - deal->down_payment + deal->cash_out, 0);

	roi = ((cash_flow + year_one_amortization + deal->cash_out) /
		(deal->rehab_cost + deal->down_payment)) * 100;

	irr = calculate_30_year(deal) * 100;

	max_cash_out = ((deal->market_price - deal->purchase_price +
		deal->down_payment) - (deal->market_price *
		DEFAULT_DOWN_PAYMENT)) * MAX_CASH_OUT;

	char *sidebar[] = {
	"1. Asking Price",
	"2. Market Price",
	"3. Purchase Price",
	"4. Down Payment",
	"5. Rehab Cost",
	"6. Taxes (Monthly)",
	"7. Insurance (Monthly)",
	"8. HOA (Monthly)",
	"9. CapEX (Monthly)",
	"10. Repairs (Monthly)",
	"11. Vacancy (Monthly)",
	"12. Management (Monthly)",
	"13. Rent (Monthly)",
	"14. Cash Out",
	"Max Cash Out",
	"Mortgage (Monthly)",
	"NOI (Monthly)",
	"Cash Flow (Monthly)",
	"Cap Rate",
	"Cash on Cash Return",
	"Expected ROI",
	"IRR"};

	char *data[] = {
		ftoa(deal->asking_price, (char[50]){}, 50),
		ftoa(deal->market_price, (char[50]){}, 50),
		ftoa(deal->purchase_price, (char[50]){}, 50),
		ftoa(deal->down_payment, (char[50]){}, 50),
		ftoa(deal->rehab_cost, (char[50]){}, 50),
		ftoa(deal->taxes, (char[50]){}, 50),
		ftoa(deal->insurance, (char[50]){}, 50),
		ftoa(deal->hoa, (char[50]){}, 50),
		ftoa(deal->capex, (char[50]){}, 50),
		ftoa(deal->repairs, (char[50]){}, 50),
		ftoa(deal->vacancy, (char[50]){}, 50),
		ftoa(deal->management, (char[50]){}, 50),
		ftoa(deal->monthly_rent, (char[50]){}, 50),
		ftoa(deal->cash_out, (char[50]){}, 50),
		ftoa(max_cash_out, (char[50]){}, 50),
		ftoa(deal->mortgage, (char[50]){}, 50),
		ftoa(noi / 12.0, (char[50]){}, 50),
		ftoa(cash_flow / 12.0, (char[50]){}, 50),
		ftoa_p(cap_rate, (char[50]){}, 50),
		ftoa_p(coc, (char[50]){}, 50),
		ftoa_p(roi, (char[50]){}, 50),
		ftoa_p(irr, (char[50]){}, 50),
	};

	print_chart_single("Deal Info", sidebar, data, 22, 25);
}

double calculate_30_year(DEAL *deal) {

	int years = 10;

	char ***data = (char***) malloc(years * sizeof(char**));

	for (int i = 0; i < years; i++) {
		data[i] = (char**) malloc(18 * sizeof(char*));
		for (int k = 0; k < 18; k++) {
			data[i][k] = (char*) malloc(50 * sizeof(char));
		}
	}

	double balance = deal->purchase_price - deal->down_payment +
		deal->cash_out;
	double amortization;
	double taxes;
	double insurance;
	double hoa;
	double capex;
	double repairs;
	double vacancy;
	double management;
	double monthly_rent;
	double market_price;
	double noi;
	double cash_flow;
	double coc;
	double cap_rate;
	double roi;
	double cashout_refi;
	double orig_cash_flow;
	double max_debt;

	noi = (deal->monthly_rent - (deal->capex + deal->vacancy +
		deal->management + deal->repairs + deal->taxes +
		deal->insurance + deal->hoa)) * 12.0;

	orig_cash_flow = noi - (deal->mortgage * 12);

	double cf[years + 1], irr = 0.00;

	cf[0] = -(deal->rehab_cost + deal->down_payment);

	for (int i = 0; i < years; i++) {
		amortization = calc_annual_amortization(balance, i * 12);
		balance -= amortization;

		taxes = compund_interest(deal->taxes, YEARLY_FEE_INCREASE, i);
		insurance = compund_interest(deal->insurance,
			YEARLY_FEE_INCREASE, i);

		hoa = compund_interest(deal->hoa, YEARLY_FEE_INCREASE, i);
		capex = compund_interest(deal->capex, YEARLY_FEE_INCREASE, i);
		repairs = compund_interest(deal->repairs, YEARLY_FEE_INCREASE,
			i);

		vacancy = compund_interest(deal->vacancy, YEARLY_FEE_INCREASE,
			i);

		management = compund_interest(deal->management,
			YEARLY_FEE_INCREASE, i);

		monthly_rent = compund_interest(deal->monthly_rent,
			YEARLY_INCREASE_RENT, i);

		market_price = compund_interest(deal->market_price,
			YEARLY_PROP_APP, i);

		noi = (monthly_rent - (capex + vacancy + management + repairs +
			taxes + insurance + hoa)) * 12.0;

		cap_rate = (noi / deal->purchase_price) * 100;

		cash_flow = noi - (deal->mortgage * 12);

		coc = (cash_flow / (deal->rehab_cost + deal->down_payment)) *
			100;

		roi = cash_flow + amortization;

		if (i <= 0) {
			roi += deal->cash_out;
		}

		cf[i + 1] = roi;

		roi /= deal->rehab_cost + deal->down_payment;
		roi *= 100;

		max_debt = principle((noi - orig_cash_flow) / 12.0,
			rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH);

		cashout_refi = max_debt - balance;

		ftoa(deal->mortgage, data[i][0], 50);
		ftoa(taxes, data[i][1], 50);
		ftoa(insurance, data[i][2], 50);
		ftoa(hoa, data[i][3], 50);
		ftoa(capex,data[i][4], 50);
		ftoa(repairs, data[i][5], 50);
		ftoa(vacancy, data[i][6], 50);
		ftoa(management, data[i][7], 50);
		ftoa(monthly_rent, data[i][8], 50);
		ftoa(market_price, data[i][9], 50);
		ftoa(balance, data[i][10], 50);
		ftoa(amortization, data[i][11], 50);
		ftoa(cashout_refi, data[i][12], 50);
		ftoa(noi / 12.0, data[i][13], 50);
		ftoa(cash_flow / 12.0, data[i][14], 50);
		ftoa_p(cap_rate, data[i][15], 50);
		ftoa_p(coc, data[i][16], 50);
		ftoa_p(roi, data[i][17], 50);
	}

	int numOfFlows;
	numOfFlows = years + 1;
	irr = computeIRR(cf, numOfFlows);

	char **header = (char**) malloc(years * sizeof(char*));

	for (int i = 0; i < years; i++) {
		header[i] = (char*) malloc(50 * sizeof(char));
		strcpy(header[i], "");
		strcat(header[i], "Year ");
		strcat(header[i], itoa(i + 1, (char[50]){}, 50));
	}

	char *sidebar[] = {
	"Mortgage (Monthly)",
	"Taxes (Monthly)",
	"Insurance (Monthly)",
	"HOA (Monthly)",
	"CapEX (Monthly)",
	"Repairs (Monthly)",
	"Vacancy (Monthly)",
	"Management (Monthly)",
	"Rent (Monthly)",
	"Market Value",
	"Loan Balance",
	"Amortization",
	"Cash Out Refi",
	"NOI (Monthly)",
	"Cash Flow (Monthly)",
	"Cap Rate",
	"Cash on Cash Return",
	"Expected ROI"};

	for (int i = 0; i < years; i += 5) {
		print_chart(header + i, sidebar, data + i, 5, 18, 21);
		printf("\n");
	}

	for (int i = 0; i < years; i++) {
		free(header[i]);
	}
	free(header);

	for (int i = 0; i < years; i++) {
		for (int k = 0; k < 18; k++) {
			free(data[i][k]);
		}
		free(data[i]);
	}
	free(data);

	return irr;
}
