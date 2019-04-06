#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_ARRAY_SIZE 1000 
int arr[MAX_ARRAY_SIZE];
int new_arr[MAX_ARRAY_SIZE];

#define MAX_THREAD_NUM 8

int thread_num;

// return ms
long get_current_time(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

struct node {
    int l;
    int r;
};

void merge(int l, int mid, int r) {
    int iter_1 = l;
    int iter_2 = mid + 1;
    memcpy(new_arr, arr+l, sizeof(int) * (r-l+1));
    int iter = 0;
    while (iter_1 <= mid && iter_2 <= r) {
        if (arr[iter_1] < arr[iter_2]) {
            new_arr[iter++] = arr[iter_1++];
        } else {
            new_arr[iter++] = arr[iter_2++];
        }
    }
    if (iter_1 <= mid) {
        while (iter_1 <= mid) {
            new_arr[iter++] = arr[iter_1++];
        }
    } else {
        while (iter_2 <= r) {
            new_arr[iter++] = arr[iter_2++];
        }
    }
    memcpy(arr+l, new_arr, sizeof(int) * (r-l+1));
}

void *merge_sort(void *args) {
    struct node *n = (struct node *) args;
    int l = n->l;
    int r = n->r;
    if (l >= r) {
        return NULL;
    }
    int mid = (l + r) / 2 + 1;
    struct node *n1 = (struct node *) malloc(sizeof(struct node *));
    struct node *n2 = (struct node *) malloc(sizeof(struct node *));
    n1->l = l;
    n1->r = mid - 1;
    n2->l = mid;
    n2->r = r;
    merge_sort(n1);
    merge_sort(n2);
    merge(l, (l+r)/2, r);
    free(n1);
    free(n2);
    return 0;
}