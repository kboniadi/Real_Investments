#ifndef _DEAL_H_
#define _DEAL_H_

#include <stdio.h>
#include "LIMITS.h"
#include "TOOLS.h"

typedef struct {
	double asking_price;
	double market_price;
	double hoa;
	double monthly_rent;
	double cash_out;

	double purchase_price;
	double down_payment;
	double rehab_cost;
	double mortgage;
	double taxes;
	double insurance;
	double capex;
	double repairs;
	double vacancy;
	double management;
} DEAL;

void init_deal(DEAL *deal);
void calculate_deal(DEAL *deal);
void modify_values(DEAL *deal);
double calculate_30_year(DEAL *deal);

#endif
