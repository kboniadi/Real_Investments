#include <stdio.h>
#include <math.h>
#include "DEAL.h"

/*

1. Amortization rate calculations

*/

int main()
{
	DEAL deal;

	printf("Asking Price:");
	scanf("%d", &deal.asking_price);

	printf("Market Price:");
	scanf("%d", &deal.market_price);

	printf("HOA:");
	scanf("%d", &deal.hoa);

	printf("Monthly Rent:");
	scanf("%d", &deal.monthly_rent);

	return 0;
}
