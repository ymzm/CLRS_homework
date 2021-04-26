#include <vector>
#include <iostream>
#include <ctime>
#include <climits>
using namespace std;
int retcheck(vector<int>& nums1, vector<int>& nums2, int i, int j, int l1, int l2)
{
        int min1, min2, max1, max2;
        if (j < 0)
        {
            return -1;
        }
        
        if (j > l2)
        {
            return 1;
        }
        
        
        min1 = (i==0) ? INT_MIN : nums1[i-1];
        min2 = (j==0) ? INT_MIN : nums2[j-1];
        max1 = (i==l1) ? INT_MAX : nums1[i];
        max2 = (j==l2) ? INT_MAX : nums2[j];
        
        if (min1 > max2)
        {
            return -1;
        }
        
        if (min2 > max1)
        {
            return 1;
        }
        
        return 0;
    }
    
    double median(vector<int>& nums1, vector<int>& nums2, int i, int j)
    {
        int min1 = (i==0) ? INT_MIN : nums1[i-1];
        int min2 = (j==0) ? INT_MIN : nums2[j-1];
        int max1 = (i==nums1.size()) ? INT_MAX : nums1[i];
        int max2 = (j==nums2.size()) ? INT_MAX : nums2[j];
        
        if ((nums1.size() + nums2.size()) & 1 )
        {
            return min(max1, max2);
        }
        else
        {
            return ((double)(min(max1, max2) + max (min1, min2)))/2;
        }
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < nums2.size())
        {
            // nums1.length() >= nums2.length()
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int l1 = nums1.size();
        int l2 = nums2.size();
        int sum = l1 + l2;
        int mid = sum / 2; // divide sum into mid || mid or mid + 1 
        //int s_m = sum -mid;
        //int flag = sum & 1; // flag = 0 means even, flag = 1 means odd;
        
        int i = l1 / 2;
        int j = mid - i;
        int ret;
        int high = l1; 
        int low = 0;
        
        while ((ret  = retcheck (nums1, nums2, i, j, l1, l2)) != 0)
        {
            if (ret == -1)
            {
                high = i;
                i = (i+low)/2;
                
            }else
            {
                low = i;
                if (i == (i+high)/2)
                {
                    i++;
                }
                else
                {
                    i = (i+high)/2;
                }
                
            }
            
            j = mid - i;
        }
        
        return median (nums1, nums2, i, j);
    }
#define N 1000 
#define STEP1 2
#define STEP2 3
void generate_vector(vector<int> &nums, int cnt, int step)
{
    srand((int)time(0));
    nums.resize(cnt);
    nums[0] = rand()%step;
    for (int i=1; i<cnt; i++)
    {
        nums[i] += nums[i-1] + rand()%step;
    }
}
    int main(void)
    {
        vector<int> nums1 = {}, nums2 = {};
        generate_vector (nums1, N, STEP1);
        generate_vector (nums2, N, STEP2);
        int ret =  findMedianSortedArrays(nums1, nums2);
        cout << ret << endl;
        return 0;
    }
