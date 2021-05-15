/*
 * ustc CLRS - Lab1 
 * howif 2021/5/15
 */

#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
#define N 20000

vector<int> res1(N);
vector<int> res2;
void generate_points (void){
    srand((int)time(0));
    for (int i=1; i<N; i++)
    {
        res1[i] = rand() % N;
    }
    res2 = res1;
    return;
}

int partition(vector<int> &A, int p, int r){
    int x = A[r];
    int i = p-1;
    for (int j = p; j<r; j++){
        if (A[j] <= x){
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}

void quick_sort(vector<int> &A, int p, int r){
    if (p<r){
        int q = partition(A, p, r);
        quick_sort(A,p,q-1);
        quick_sort(A,q+1,r);
    }
}

int random_partition(vector<int> &A, int p, int r){
    int i = (rand() % (r - p  + 1)) + p;
    swap(A[r], A[i]);
    return partition(A, p, r);
}

void random_quick_sort(vector<int> &A, int p, int r){
    if (p<r){
        int q = random_partition(A, p, r);
        random_quick_sort(A,p,q-1);
        random_quick_sort(A,q+1,r);
    }
}


/*
 * howif@howif-VirtualBox:~$ ./a.out 
 * 20000
 * random input normal quick sort Running Time : 0.004118
 * random input randomized quick sort  Running Time : 0.003972
 * randomized input normal quick sort Running Time : 1.69859
 * randomized input randomized quick sort Running Time : 0.002524
 */

int main(void)
{
    clock_t start,ends;
    clock_t s = clock();
    generate_points();
    cout << N << endl;
    // random input
    start = clock();
    quick_sort(res1, 1, N-1);
    ends = clock();
    cout <<"random input normal quick sort Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    //for (int i=1; i<N; i++){
    //    printf ("%d ", res2[i]);
    //}
    start = clock();
    random_quick_sort(res2, 1, N-1);
    ends = clock();
    cout <<"random input randomized quick sort Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    //for (int i=1; i<N; i++){
    //    printf ("%d ", res2[i]);
    //}
    // sorted input
    start = clock();
    quick_sort(res1, 1, N-1);
    ends = clock();
    cout <<"randomized input normal quick sort Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    start = clock();
    random_quick_sort(res2, 1, N-1);
    ends = clock();
    cout <<"randomized input randomized quick sort Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    clock_t e = clock();
    cout <<"program running time in total : "<<(double)(e - s)/ CLOCKS_PER_SEC << endl;
    return 0;
}
