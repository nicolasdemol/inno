#include "functions.h"

#define max(x, y) (x > y ? x : y)

void mat_mul(int n, double *a, double *b, double *result)
{
    // matrix a of size n (array)
    // matrix b of size n
    // matrix result of size n (array)
    // result = a * b
    int i;
    for (i = 0; i < n; i++)
    {
        result[i] = 0.0;
        result[i] = (a[i] * b[i]);
    }
}

void identity(int n, double *input, double *output)
{
    int i;
    for (i = 0; i < n; i++)
        output[i] = input[i]; // Identity function
}

void sigmoid(int n, double *input, double *output)
{
    int i;
    for (i = 0; i < n; i++)
        output[i] = 1.0 / (1.0 + exp(-input[i])); // Sigmoid function
}

void d_sigmoid(int layer_size, double *layer_input, double *layer_output)
{
    int i;
    for (i = 0; i < layer_size; i++)
        layer_output[i] = layer_input[i] * (1.0 - layer_input[i]);
}

void relu(int n, double *input, double *output)
{
    int i;
    for (i = 0; i < n; i++)
        output[i] = max(0.0, input[i]); // ReLU function
}

void d_relu(int layer_size, double *layer_input, double *layer_output)
{
    int i;
    for (i = 0; i < layer_size; i++)
    {
        if (layer_input[i] > 0)
            layer_output[i] = 1;
        else if (layer_input[i] < 0)
            layer_output[i] = 0;
        else                       // derivative does not exist
            layer_output[i] = 0.5; // giving arbitrary value
    }
}

void tan_h(int n, double *input, double *output)
{
    int i;
    for (i = 0; i < n; i++)
        output[i] = tanh(input[i]); // tanh function
}

void softmax(int n, double *input, double *output)
{
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++)
        sum += exp(input[i]);

    for (i = 0; i < n; i++)
        output[i] = exp(input[i]) / sum; // Softmax function
}

void d_softmax(int layer_size, double *layer_input, double *layer_output)
{
    int i;
    for (i = 0; i < layer_size; i++)
        layer_output[i] = layer_input[i] * (1.0 - layer_input[i]);
}

void errorCost(int n, double *cost, double *input, double *output)
{
    int i;
    for (i = 0; i < n; i++)
        output[i] = cost[i] - input[i];
}

void errorCalc(int n, int p, double *arrDelta, double **arrWeights, double *output)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        output[i] = 0.0f;
        for (j = 0; j < p; j++)
        {
            output[i] += arrDelta[i] * arrWeights[j][i];
        }
    }
}
