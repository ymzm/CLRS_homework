#include <vector>
#include <iostream>
#include <ctime>

using namespace std;
#define PARENT(i) (i/2)
#define LEFT(i)    (i<<1)
#define RIGHT(i)   (1+i<<1)

// assume LEFT(i) and RIGHT(i) is MAX-HEAP
void max_heapify(vector <int> &A, int index)
{
    int l = LEFT(index), r = RIGHT(index), largest;
    if ((l<=A[0]) && (A[l] > A[index])){
        largest = l;
    }
    else{
        largest = index;
    }

    if ((r<=A[0]) && (A[r] > A[largest])){
        largest = r;
    }

    if (largest != index){
        swap(A[index], A[largest]);
	    max_heapify(A, largest);
    }

    return;
}

/*
 * Presudo HEAP-DELETE(A,i)
 * Input: A max-heap A and integers i.
 * Output: The heap A with the element a position i deleted.
 * A[i] ↔ A[heap-size[A]]
 * heap-size[A] ← heap-size[A] − 1
 * key ← A[i]
 * if key <= A[PARENT (i)] then
 *     MAX-HEAPIFY (A,i)
 * else
 *     while i > 1 and A[P ARENT (i)] < key do
 *         A[i] ↔ A[PARENT (i)]
 *         i ← PARENT (i)
 *     end while
 * end
 */
void heap_delete(vector<int> &A, int index){
    int key = A[index];
    if (index == A[0])
    {
        A[0]--;
	    return;
    }

    swap(A[index], A[A[0]]);
    A[0]--;

    if ((index == 1) || (key <= A[PARENT(index)])){
        max_heapify(A, index);
    }else{
        while ((index > 1) && (A[PARENT(index)] < key)){
            swap(A[index], A[PARENT(index)]);
            index = PARENT(index);
        }
    }
}

/*
 * A[0] is size of heap
 */
vector<int> generate_max_heap(int size)
{
    vector<int> res;
    res.resize(size+1);
    res[0] = size;
    srand((int)time(0));
    res[1] = rand() % 20;
    for (int i=2; i<=size; i++)
    {
        res[i] = res[PARENT(i)] + rand() % 20;
    }

    return res;
}
#define HEAPS_CNT 10000
#define HEAP_SIZE 320
void test(void){
    vector<vector<int>> heaps;
    for (int i=0; i<HEAPS_CNT; i++){
        heaps.push_back(generate_max_heap(HEAP_SIZE));
    }
    srand((int)time(0));
    clock_t start = clock();
    for (int i=0; i<HEAPS_CNT; i++){
        heap_delete(heaps[i], rand()%HEAP_SIZE);
    }

    clock_t ends = clock();
    cout << "heap size: " << HEAP_SIZE << " heaps cnt: " << HEAPS_CNT << endl;
    cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    cout << "test end" << endl;
    return;
}

int main(void)
{
    cout << "test begin" << endl;
    test();
    return 0;
}
