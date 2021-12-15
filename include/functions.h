#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void errorCalc(int n, int p, double *arrDelta, double **arrWeights, double *output);

void errorCost(int n, double *cost, double *input, double *output);

void mat_mul(int n, double *a, double *b, double *result);

void softmax(int n, double *input, double *output);

void d_softmax(int layer_size, double *layer_input, double *layer_output);

void sigmoid(int n, double *input, double *output);

void d_sigmoid(int layer_size, double *layer_input, double *layer_output);

void relu(int n, double *input, double *output);

void d_relu(int layer_size, double *layer_input, double *layer_output);

#endif