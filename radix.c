#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define MAX 1000

struct node {
    int value;
    struct node *next;
};

void bucket(int k, int size);

struct node *keys[10] = {NULL};
struct node *values[MAX];

void bucket(int k, int size)
{
    int digit;
    //bucketting
    for (int i=0; i<size; i++)
    {
        digit = (values[i]->value / (int)pow(10, k-1)) % 10;
        struct node *tmp = keys[digit];
        while (tmp && tmp->next) tmp = tmp->next;
        if (tmp)
            tmp->next = values[i];
        else
            keys[digit] = values[i];
        values[i]->next = NULL;
    }

    int arr[size], l=0;
    //unpacking into array and destroying the buckets
    for (int i=0; i<10; i++)
    {
        struct node *tmp=keys[i], *nul; 
        while (tmp)
        {
            assert(l < size);
            arr[l++] = tmp->value;
            nul = tmp;
            tmp = tmp->next;
            nul->next = NULL;
        }

        keys[i] = NULL;
    }
    //updating the initial list with the new array values
    for (int i=0; i<size; i++)
    {
        values[i]->value = arr[i];
    }

    for (int i=0; i<size; i++)
        printf("%d\t", values[i]->value);
    printf("\n");

}



int main ()
{
    //struct node *keys[10] = {NULL};
    printf("Enter the number of values\n");
    int n;
    scanf("%d", &n);
    //struct node *values[n];
    int d = 0;


    printf("Enter the %d values\n", n);
    for (int i =0; i<n; i++)
    {
        values[i] = (struct node *)malloc(sizeof(struct node));
        scanf("%d", &(values[i]->value));
        values[i]->next = NULL;
        d = (int)(log10(values[i]->value) + 1) > d ? (int)(log10(values[i]->value) + 1) : d;
    }

    for (int i=0; i<d; i++)
    {
        bucket(i+1, n);
    }

    for (int i=0; i<n; i++)
        free(values[i]);

    return 0;
}
