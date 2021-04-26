#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
#define POINT_CNT 100
#define SCALE 10000
#define SIZE_SCALE 100000000
#define N (SIZE_SCALE / POINT_CNT)

typedef struct point {
    struct point *next;
    struct point *prev;
    int x;
    int y;
    bool x_flag; // true means positive, false means nagetive; doesn't matter in this funciton
    bool y_flag;
    int distance;
}point;

static point res[POINT_CNT];

void generate_points (void){
    srand((int)time(0));
    //vector <point> res;
    //res.resize(POINT_CNT);
    for (int i=0; i<POINT_CNT; i++)
    {
        res[i].x = rand() % SCALE;
        res[i].y = rand() & SCALE;
        res[i].distance = res[i].x * res[i].x + res[i].y * res[i].y;
        if ((res[i].distance == 0) || (res[i].distance > SIZE_SCALE))
        {
            i--;
            continue;
        }
        res[i].x_flag = rand() % 2;
        res[i].y_flag = rand() % 2;
        res[i].next = NULL;
        res[i].prev = NULL;
    }
    //return res;
}
vector <point *> bucket(POINT_CNT);
vector <point *> tail(POINT_CNT);
void bucket_sort(void){
    clock_t start = clock();

    for (int i=0; i<POINT_CNT; i++)
    {
        bucket[i] = NULL;
        tail[i] = NULL;
    }
    
    // insert  to bucket
    for (int i=0; i<POINT_CNT; i++)
    {
        int bucket_number = (res[i].distance-1)/N;
        if (bucket[bucket_number] != NULL)
        {
            res[i].next = bucket[bucket_number];
            bucket[bucket_number]->prev = &res[i];
            
        }
        bucket[bucket_number] = &res[i];
    }
    
    // sort bucket[i] with insertion sort
    for (int i=0; i<POINT_CNT; i++)
    {
        if (bucket[i] == NULL)
        {
            continue;
        }
        
        point *head = bucket[i];
        tail[i] = head;
        point *head_save = head;
        point *tmp  = head->next;
        point *tmp2  = tmp;
        head->next = NULL;
        while (tmp != NULL)
        {
            point *prev = NULL;
            tmp2 = tmp->next;
            while (head && (head->distance < tmp->distance))
            {
                prev = head;
                head = head->next;
            }

            if (head == NULL)
            {
                prev->next = tmp;
                tmp->prev = prev;
                tmp->next = NULL;
                head = head_save;
                tail[i] = tmp;
            }
            else{
                if (head->prev == NULL)
                {
                    tmp->next = head;
                    tmp->prev = NULL;
                    head->prev = tmp;
                    head_save = tmp;
                    head = head_save;
                }
                else
                {
                    head->prev->next = tmp;
                    tmp->prev = head->prev;
                    tmp->next = head;
                    head->prev = tmp;
                    head = head_save;
                }
            }
            bucket[i] = head_save;
            tmp = tmp2;
        }
    }
    
    point *tmp_tail = NULL;
    point *ret_head = NULL;

    for (int i=0; i<POINT_CNT; i++)
    {
        
        if (bucket[i] != NULL)
        {
            if (ret_head == NULL)
            {
                ret_head = bucket[i];
            }
            else{
                bucket[i]->prev = tmp_tail;
            
                tmp_tail->next = bucket[i];
            }
            tmp_tail = tail[i];
        }
    }

    clock_t ends = clock();
    cout << "point cnt: " << POINT_CNT << endl;
    cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    cout << "test end" << endl;
#if 1  
    point *tmp = ret_head;
    int i=0;
    while (tmp)
    {
            cout << i << "  "<< tmp->distance << " " << tmp->x << " " << tmp->y << endl;
            i++;
            tmp = tmp->next;
    }
#endif
}

int main(void)
{
    generate_points();

    bucket_sort();
    
    return 0;
}
