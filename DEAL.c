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

	deal->mortgage = deal->monthly_rent - (deal->capex + deal->vacancy +
		deal->management + deal->repairs + deal->taxes +
		deal->insurance + deal->hoa + MINIMUM_CASH_FLOW_MONTHLY);

	max_debt = principle(deal->mortgage, rate(INTEREST, COMPOUND_RATE,
		PAY_RATE), LOAN_LENGTH);

	deal->purchase_price = max_debt / .80;

	deal->down_payment = DEFAULT_DOWN_PAYMENT * deal->purchase_price;

	deal->rehab_cost = (deal->market_price - deal->purchase_price) / 2.0;
}

void calculate_deal(DEAL *deal) {
	double noi;
	double cap_rate;
	double cash_flow;
	double coc;
	double roi;

	deal->taxes = (deal->market_price * YEARLY_PROP_TAXES) / 12.0;
	deal->insurance = (deal->market_price * YEARLY_HOME_INSURANCE) / 12.0;

	deal->mortgage = payment(deal->purchase_price - deal->down_payment,
		rate(INTEREST, COMPOUND_RATE, PAY_RATE), LOAN_LENGTH);

	noi = (deal->monthly_rent - (deal->capex + deal->vacancy +
		deal->management + deal->repairs + deal->taxes +
		deal->insurance + deal->hoa)) * 12.0;

	cap_rate = noi / (deal->rehab_cost + deal->down_payment);

	cash_flow = noi - (deal->mortgage * 12);

	coc = cash_flow / (deal->rehab_cost + deal->down_payment);

	double year_one_amortization = calc_year_one_amortization(
		deal->purchase_price - deal->down_payment);

	printf("%lf\n", year_one_amortization);

	roi = (cash_flow + year_one_amortization + (deal->market_price *
		YEARLY_PROP_APP) + (deal->market_price -
		deal->purchase_price)) / (deal->rehab_cost +
		deal->down_payment);

	char *sidebar[] = {
	"Asking Price",
	"Market Price",
	"Purchase Price",
	"Down Payment",
	"Rehab Cost",
	"Mortgage (Monthly)",
	"Taxes (Monthly)",
	"Insurance (Monthly)",
	"HOA Monthly)",
	"CapEX (Monthly)",
	"Repairs (Monthly)",
	"Vacancy (Monthly)",
	"Management (Monthly)",
	"Rent (Monthly)",
	"NOI (Yearly)",
	"Cap Rate",
	"Cash Flow (Yearly)",
	"Cash on Cash Return",
	"Expected ROI"};

	char *data[] = {
		ftoa(deal->asking_price, (char[50]){}, 50),
		ftoa(deal->market_price, (char[50]){}, 50),
		ftoa(deal->purchase_price, (char[50]){}, 50),
		ftoa(deal->down_payment, (char[50]){}, 50),
		ftoa(deal->rehab_cost, (char[50]){}, 50),
		ftoa(deal->mortgage, (char[50]){}, 50),
		ftoa(deal->taxes, (char[50]){}, 50),
		ftoa(deal->insurance, (char[50]){}, 50),
		ftoa(deal->hoa, (char[50]){}, 50),
		ftoa(deal->capex, (char[50]){}, 50),
		ftoa(deal->repairs, (char[50]){}, 50),
		ftoa(deal->vacancy, (char[50]){}, 50),
		ftoa(deal->management, (char[50]){}, 50),
		ftoa(deal->monthly_rent, (char[50]){}, 50),
		ftoa(noi, (char[50]){}, 50),
		ftoa(cap_rate, (char[50]){}, 50),
		ftoa(cash_flow, (char[50]){}, 50),
		ftoa(coc, (char[50]){}, 50),
		ftoa(roi, (char[50]){}, 50),
	};

	print_chart_single("Deal Info", sidebar, data, 19, 25);
}
