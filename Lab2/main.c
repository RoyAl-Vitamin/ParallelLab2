#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <emmintrin.h>
#include <malloc.h>

float *x, *y;
int count;
int IN;

void* sqrt_my(void *x_void_ptr)
{

    int i;
    int *x_ptr = (int *)x_void_ptr;
    printf("i = %d\n", *x_ptr * count);
    for (i = *x_ptr * count; i < (*x_ptr + 1) * count; i++)
    {
        y[i] = sqrt(x[i]);
//        y[i] = x[i] * x[i];
        //printf("x[%d] == %f; y[%d] = %f\n", i, x[i], i, y[i]);
    }
    return NULL;
}

int main(int argc, char** argv)
{
    int i=0;

    if (argc != 2)
        return 1;

    IN = atoi(argv[1]);

    srand((unsigned int)time(NULL));
    count = 10;
    x = (float*) malloc(count * IN * sizeof(float));
    y = (float*) malloc(count * IN * sizeof(float));
    int * temp = (int*) malloc(IN * sizeof(int));
    for (i = 0; i < IN * count; i++)
    {
        x[i] = rand() % 1000;
//        printf("x[%d] = %f\n", i, x[i]);
//        printf("y[%d] = %f\n", i, y[i]);
    }
    pthread_t* arr_thread;
    //posix_memalign((void**)&arr_thread, 1,  IN * sizeof(pthread_t));

    arr_thread = (pthread_t*) malloc(IN * sizeof(pthread_t));

    for (i = 0 ; i < IN; i++)
    {
        temp[i] = i;
        if(pthread_create(&(arr_thread[i]), NULL, sqrt_my, &(temp[i]))) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (i = 0 ; i < IN; i++)
    {
        if(pthread_join(arr_thread[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }
//    for (i = 0 ; i < count * IN ; i++)
//    {
//        printf("y[%d] = %f\n", i, y[i]);
//    }

    return 0;

}