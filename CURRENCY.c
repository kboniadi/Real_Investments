#include "CURRENCY.h"

bool Init_CURRENCY(CURRENCY *currency, const char *value) {
	int digits_after_period = 0;
	char *period_loc = strstr(value, ".");

	if (period_loc == NULL) {
		*currency = atoi(value);

		if (*currency == 0 && strcmp(value, "0")) {

		}
	} else {
		digits_after_period = strlen(value) - ((period_loc + 1) -
			value);

		if (digits_after_period > 2) {
			return false;
		} else {
			*currency = atoi(period_loc + 1);
			if (*currency == 0 && (
				strcmp(period_loc + 1, "") == 0 ||
				strcmp(period_loc + 1, "0") == 0 ||
				strcmp(period_loc + 1, "00") == 0)) {

				return false;
			}
		}

		switch(digits_after_period) {
			case 0:
				if (strcmp(period_loc + 1, "") == 0) {
					*currency = 0;
					return true;
				}
			case 1:
			case 2:

			default:
				return false;
		}

	}
}
