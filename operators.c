//
// Created by kord on 8/20/20.
//
#include <stdio.h>
#include <math.h>
#include "operators.h"

void add(const FloatType * const left, const FloatType * const right, FloatType * const newType)
{
	int lscalar = 0;
	int rscalar = 0;
	if (left->scale > right->scale) {
		newType->scale = left->scale;
		rscalar = left->scale - right->scale;
	} else if (left->scale < right->scale) {
		newType->scale = right->scale;
		lscalar = right->scale - left->scale;
	}
	newType->scaledNum = (left->scaledNum * (pow(10, lscalar))) + (right->scaledNum * (pow(10, rscalar)));
}

void sub(const FloatType * const left, const FloatType * const right, FloatType * const newType)
{
	int lscalar = 0;
	int rscalar = 0;
	if (left->scale > right->scale) {
		newType->scale = left->scale;
		rscalar = left->scale - right->scale;
	} else if (left->scale < right->scale) {
		newType->scale = right->scale;
		lscalar = right->scale - left->scale;
	} else {
		newType->scale = left->scale;
	}

	newType->scaledNum = (left->scaledNum * (pow(10, lscalar))) - (right->scaledNum * (pow(10, rscalar)));
}

void mult(const FloatType * const left, const FloatType * const right, FloatType * const newType)
{
	newType->scale = left->scale + right->scale;
	newType->scaledNum = left->scaledNum * right->scaledNum;
}

void divi(const FloatType * const left, const FloatType * const right, FloatType * const newType)
{
	int lscalar = 0;
	int rscalar = 0;
	if (left->scale > right->scale) {
		newType->scale = right->scale;
		rscalar = left->scale - right->scale;
	} else if (right->scale > left->scale) {
		newType->scale = left->scale;
		lscalar = right->scale - left->scale;
	} else {
		newType->scale = left->scale;
	}
	ConvertToFloatType(newType, (left->scaledNum * (pow(10, lscalar))) / (right->scaledNum * (pow(10, rscalar))));
//	newType->scaledNum = (left->scaledNum * (pow(10, lscalar))) / (right->scaledNum * (pow(10, rscalar)));
}

//double pwr(double left, double exp)
//{
//	return left;
//}
//
bool lessThan(const FloatType * const left, const FloatType * const right)
{
	return left->scale < right->scale && left->scaledNum < right->scaledNum;
}

bool greaterThan(const FloatType * const left, const FloatType * const right)
{
	return left->scale > right->scale && left->scaledNum > right->scaledNum;
}

void absolute(FloatType * const type)
{
	if (type->scaledNum <= 0)
		type->scaledNum = 0 - type->scaledNum;
}

struct Operator* CreateOperator()
{
	struct Operator *ptr = malloc(sizeof(struct Operator));
	if (ptr != NULL) {
		ptr->add = &add;
		ptr->sub  = &sub;
		ptr->mult = &mult;
		ptr->divi = &divi;
//		ptr->pwr = &pwr;
		ptr->lessThan = &lessThan;
		ptr->greaterThan = &greaterThan;
		ptr->absolute = &absolute;
	}
	return ptr;
}

void ConvertToFloatType(FloatType  * const type, double num)
{
	unsigned i = 0;
	char str[20] = {0};
	char *string = NULL;
	char mod[10] = {0};

	sprintf(str, "%lf", num);
	for (i = strlen(str) - 1; i >= 0; i--) {
		if (str[i] != '0')
			break;
	}

	strncpy(mod, str, i + 1);
	string = strchr(mod, '.');

//	type->precision = (int) strlen(mod) - 1;
	type->scale = (int) strlen(string) - 1;
	type->scaledNum = num * (pow(10, type->scale));
}

double ConvertToDouble(const FloatType * const type)
{
	return (double) type->scaledNum / (pow(10, type->scale));
}