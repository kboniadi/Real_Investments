#include <stdio.h>
#include "DEAL.h"
#include "TOOLS.h"
#include "LIMITS.h"
#include "operators.h"

/*
we have to eventually calculate holding costs...
we should also calculate IRR
it's Principal not principle
how much can I refi?
*/

int main()
{
	DEAL deal;

	init_deal(&deal);

	calculate_deal(&deal);

	modify_values(&deal);

	return 0;
}
