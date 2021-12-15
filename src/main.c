//
//  Projet Innovation - Perceptron multicouche
//  Copyright © 2021 Nicolas Demol.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "functions.h"
#include "shuffle.h"
#include "mnist.h"

double init_rand() { return ((double)rand()) / ((double)RAND_MAX); }

int maximum(int n, double *input)
{
    double *t;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (input[i] > *t)
        {
            index = i;
            t = &input[i];
        }
    }
    return index;
}

int main()
{

    load_mnist();

    //-------------------------
    //  Assign values Layers  |
    //-------------------------
    double lr = 0.01;
    int epochs = 10;
    int predict = 0;
    int numSets = 60000;
    int numInputs = 784;
    int numHidden = 100;
    int numOutputs = 10;

    //----------------------
    //  Assign values I/O  |
    //----------------------
    double **inputs = malloc(sizeof *inputs * numSets);
    double **cost = malloc(sizeof *cost * numSets);

    // Assign I/O to mnist data (dynamic allocation memory)
    for (int i = 0; i < numSets; i++)
    {
        inputs[i] = malloc(sizeof *inputs[i] * numInputs);
        cost[i] = malloc(sizeof *cost[i] * numOutputs);

        for (int j = 0; j < numInputs; j++)
        {
            inputs[i][j] = train_image[i][j];
        }

        for (int j = 0; j < numOutputs; j++)
        {
            if (train_label[i] == j)
            {
                cost[i][j] = 1.0f;
            }
        }
    }

    //----------------------------
    //  Init nodes/weights/bias  |
    //----------------------------

    // Declare arrays for nodes/weights/bias
    double *hiddenLayer = malloc(sizeof *hiddenLayer * numHidden);
    double *outputLayer = malloc(sizeof *outputLayer * numOutputs);
    double *hiddenLayerBias = malloc(sizeof *hiddenLayerBias * numHidden);
    double *outputLayerBias = malloc(sizeof *outputLayerBias * numOutputs);

    double **hiddenWeights = malloc(sizeof *hiddenWeights * numHidden);
    for (int i = 0; i < numHidden; i++)
        hiddenWeights[i] = malloc(sizeof *hiddenWeights[i] * numInputs);

    double **outputWeights = malloc(sizeof *outputWeights * numOutputs);
    for (int i = 0; i < numOutputs; i++)
        outputWeights[i] = malloc(sizeof *outputWeights[i] * numHidden);

    // Fill weights/bias with random values
    for (int i = 0; i < numInputs; i++)
    {
        for (int j = 0; j < numHidden; j++)
            hiddenWeights[j][i] = init_rand();
    }
    for (int i = 0; i < numHidden; i++)
    {
        hiddenLayerBias[i] = init_rand();
        for (int j = 0; j < numOutputs; j++)
            outputWeights[j][i] = init_rand();
    }
    for (int i = 0; i < numOutputs; i++)
        outputLayerBias[i] = init_rand();

    // Create training sets
    int setOrder[numSets];
    for (int i = 0; i < numSets; i++)
        setOrder[i] = i;

    // Loop Neural Network : N = Epochs
    int epoch;
    for (epoch = 0; epoch < epochs; epoch++)
    {
        printf("\n");
        shuffle(setOrder, numSets);
        predict = 0;

        //-------------------
        //  Trainning sets  |
        //-------------------
        for (int e = 0; e < numSets; e++)
        {
            int x = setOrder[e];

            //------------------------
            //  Forward Propagation  |
            //------------------------
            // Feed HiddenLayer Nodes
            for (int i = 0; i < numHidden; i++)
            {
                double activation = hiddenLayerBias[i];
                for (int j = 0; j < numInputs; j++)
                    activation += inputs[x][j] * hiddenWeights[i][j];
                hiddenLayer[i] = activation;
            }

            // Apply Activation Function
            softmax(numHidden, hiddenLayer, hiddenLayer);

            // for (int i = 0; i < numHidden; i++)
            //     printf("%f ", hiddenLayer[i]);

            // Feed OutputLayer Nodes
            for (int i = 0; i < numOutputs; i++)
            {
                double activation = outputLayerBias[i];
                for (int j = 0; j < numHidden; j++)
                    activation += hiddenLayer[j] * outputWeights[i][j];
                outputLayer[i] = activation;
            }

            // Apply Activation Function
            relu(numOutputs, outputLayer, outputLayer);

            int m = maximum(numOutputs, outputLayer);

            if (m == train_label[x])
                predict += 1;

            double accuracy = 100 * ((double)predict / (double)e);

            printf("\r");
            printf("|  EPOCH  %d  |  GUESS  %d  |  REAL  %d  |  ACCURACY  %f %%  | ->  ", epoch + 1, m, train_label[x], accuracy);
            for (int i = 0; i < numOutputs; i++)
                printf("%f ", outputLayer[i]);

            //-------------------------
            //  Backward Propagation  |
            //-------------------------

            // Get delta from cost function
            double deltaOutput[numOutputs];
            double gradOutput[numOutputs];
            double errorOutput[numOutputs];

            d_relu(numOutputs, outputLayer, gradOutput);
            errorCost(numOutputs, cost[x], outputLayer, errorOutput);
            mat_mul(numOutputs, errorOutput, gradOutput, deltaOutput);

            // Get delta from deltaOutput function
            double deltaHidden[numHidden];
            double gradHidden[numHidden];
            double errorHidden[numHidden];

            d_softmax(numHidden, hiddenLayer, gradHidden);
            errorCalc(numHidden, numOutputs, deltaOutput, outputWeights, errorHidden);
            mat_mul(numHidden, errorHidden, gradHidden, deltaHidden);

            // Change weights/bias with deltas
            for (int i = 0; i < numOutputs; i++)
            {
                outputLayerBias[i] += deltaOutput[i] * lr;
                for (int j = 0; j < numHidden; j++)
                {
                    outputWeights[i][j] += hiddenLayer[j] * deltaOutput[i] * lr;
                }
            }

            for (int i = 0; i < numHidden; i++)
            {
                hiddenLayerBias[i] += deltaHidden[i] * lr;
                for (int j = 0; j < numInputs; j++)
                {
                    hiddenWeights[i][j] += inputs[e][j] * deltaHidden[i] * lr;
                }
            }
        }
    }

    return 0;
}
