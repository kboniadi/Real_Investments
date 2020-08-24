#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include "LIMITS.h"

double payment(double principle, double interest, int period);
double principle(double payment, double interest, int period);
double rate(double interest, int CompNum, int payNum);
double compund_interest(double principle, double rate, int time);
void print(double home,  double down);
int calc_annual_amortization(double balance, int months_paid);
void print_chart(char **header, char **sidebar, char ***data, int width,
	int height, int column_width);
void print_chart_single(char *header, char **sidebar, char **data, int height,
	int column_width);
void draw_line(int width);
double computeIRR(double cf[], int numOfFlows);
char* itoa(int val, char *out, int size);
char* ftoa(double input, char *out, int size);
char* ftoa_p(double input, char *out, int size);

#endif
