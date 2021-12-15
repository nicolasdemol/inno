#include "shuffle.h"

/* Arrange the N elements of ARRAY in random order. */
void shuffle(int *arr, size_t size)
{
    if (size > 1)
    {
        size_t i;
        for (i = 0; i < size - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
}
