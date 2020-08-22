//
// Created by kord on 8/20/20.
//
#ifndef OPERATORS_H
#define OPERATORS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	int64_t scaledNum;
//	int precision;
	int scale;
} FloatType;

void ConvertToFloatType(FloatType  * const type, double num);
double ConvertToDouble(const FloatType * const type);

struct Operator{
	void (*add)(const FloatType * const left, const FloatType * const right, FloatType * const newType);
	void (*sub)(const FloatType * const left, const FloatType * const right, FloatType * const newType);
	void (*mult)(const FloatType * const left, const FloatType * const right, FloatType * const newType);
	void (*divi)(const FloatType * const left, const FloatType * const right, FloatType * const newType);
//	FloatType* (*pwr)(double left, double exp);
	bool (*lessThan)(const FloatType * const left, const FloatType * const right);
	bool (*greaterThan)(const FloatType * const left, const FloatType * const right);
	void (*absolute)(FloatType * const type);
};

struct Operator* CreateOperator();

#endif //OPERATORS_H
