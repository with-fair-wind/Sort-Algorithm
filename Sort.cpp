#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

void printInteger(int num); //打印整数32位

//创建对数器
void CreateArrDuiShuQi(int testTimes, int maxSize, int maxValue, bool succeed, void (*pt1)(int *arr, int size), void (*pt2)(int *arr, int size));

bool findNumInSortedArr(int *arr, int num, int size);       //有序数组中找到一个数  二分法O(logN)
int mostLeftNoMoreNumIndex(int *arr, int num, int size);    //有序数组中找到一个>=某个数最左边的位置或者<=某个数最右边的位置    二分直到分不下去
int oneMinIndex(int *arr, int size);    //无序且任何相邻两元素均不相等，找到任意一个局部最小的位置  先判断两端，然后必可以二分，然后再二分...

int Extract1OddNum(int *arr, int size);             //一个数组中，只有一种数出现了奇数次，其余数均出现偶数次，找出这个出现了奇数次的数
pair<int, int> Extract2OddNum(int *arr, int size);  //一个数组中，只有两种数出现了奇数次，其余数均出现偶数次，找出这两个出现了奇数次的数

void swap(int arr[], int i, int j);         //基于位运算^的交换
void swap_right(int *arr, int i, int j);    //正常交换
void show(int arr[], int size);             //打印数组元素

//提取数组最大值
int ExtractMax(int *arr, int L, int R);
int Math_max(int leftMax, int rightMax); 

//对数器验证排序算法(数组大小随机生成，数组元素随机生成)
int GetRandomArrSize(int MaxSize) { return rand() % (MaxSize + 1); }
int *GenerateRandomArr(int MaxSize, int MaxValue);
int *copyArr(int *arr, int size);
bool isEqual(int *arr1, int *arr2, int size);
bool isSorted(int *arr, int size);

void SelectionSort(int arr[], int size);    //选择排序
void BubbleSort(int arr[], int size);       //冒泡排序
void InsertSort(int arr[], int size);       //插入排序

//归并排序
void ProcessSort(int *arr, int L, int R);   
void merge_sort(int *arr, int L, int mid, int R);
//基于归并排序的小和问题
int SmallAdd(int *arr, int L, int R);
int merge_smalladd(int *arr, int L, int mid, int R);
//基于归并排序的逆对数问题
int InverseLogarithm(int *arr, int L, int R);
int merge_inverselogarithm(int *arr, int L, int mid, int R);

//荷兰国旗问题1.0(快速排序)
void DutchFlag_first(int *arr, int L, int R);
int classify2(int *arr, int L, int R);
//荷兰国旗问题2.0(快速排序)
void DutchFlag_second(int *arr, int L, int R);
void classify3(int *arr, int L, int R, int *index);

//堆排序
void heapinsert(int *arr, int index);               //index位置数据能否上移
void heapify(int *arr, int index, int heapsize);    //index位置数据能否下移
void heapSort(int *arr, int heapsize);
//基于堆排序的几乎顺序的数组最大移动范围不超过k的排序
void sortedArrDistanceLessK(int *arr, int size, int k);

//桶排序
void raidoSort(int *arr, int size);
int maxbits(int *arr, int size);                        //获取数组中最大值元素的十进制位数
void raidoSort(int *arr, int L, int R, int digit);      //桶排序
int getdigit(int arr_num, int digit);                   //取出一个数第digit位上的数字(十进制)   0 -> 个位 ; 1 -> 十位 ; ......

int main(int argc, char * argv[])
{   
    srand((int)time(0));
    int testTimes = 5;
    int MaxSize = 10;
    int MaxValue = 100;
    bool succeed = true;

    cout << "------------------------------------" << endl;
    cout << "比较选择排序与冒泡排序: " << endl;
    CreateArrDuiShuQi(testTimes, MaxSize, MaxValue, succeed, SelectionSort, BubbleSort);
    
    cout << "------------------------------------" << endl;
    cout << "比较冒泡排序与插入排序: " << endl;
    CreateArrDuiShuQi(testTimes, MaxSize, MaxValue, succeed, InsertSort, BubbleSort);

    cout << "------------------------------------" << endl;
    cout << "After printInteger: ";
    printInteger(1);

    //取相反数
    int num1 = 5;
    int num2 = ~num1 + 1;
    int num3 = INT_MIN;
    cout << num2 << endl;
    printInteger(num3);
    printInteger(~num3 + 1);     //系统最小相反数还是本身
 
    //左移右移
    printInteger(num2);
    printInteger(num2 >> 1); //右移补符号位 左移补0

    cout << "------------------------------------" << endl;

    int arr[] = {1, 1, 2, 2, 2, 2, 5, 5, 5, 6, 6};
    int length = sizeof(arr) / sizeof(arr[0]);
    cout << "Extract1OddNum" << " *** result: " << Extract1OddNum(arr, length) << endl;

    int brr[] = {1, 1, 3, 3, 2, 2, 2, 5, 5, 7, 7, 7, 7, 6};
    length = sizeof(brr) / sizeof(brr[0]);
    pair<int, int> p1 = Extract2OddNum(brr, length);
    cout << "Extract2OddNum" << " *** result: " << p1.first << "; " << p1.second << endl;

    int frr[] = {2, 1, 4, 2, 1, 5, 6, 4, 2, 3, 4};
    cout << "ExtractMax *** result: " << ExtractMax(frr, 0, 11) << endl;

    cout << "------------------------------------" << endl;

    int crr[] = {1, 3, 2, 6, 3, 2};
    ProcessSort(crr, 0, 5);
    cout << "ProcessSort *** result: ";
    show(crr, 6);
    
    int drr[] = {1, 3, 2, 4, 3, 5};
    cout << "SmallAdd *** result: " << SmallAdd(drr, 0, 5) << endl;
    cout << "After SmallAdd arr: ";
    show(drr, 6);

    int err[] = {3, 2, 4, 3, 5, 1};
    cout << "InverseLogarithm *** result: " << InverseLogarithm(err, 0, 5) << endl;
    cout << "After InverseLogarithm arr: ";
    show(err, 6);

    cout << "------------------------------------" << endl;

    int grr[] = {2, 1, 4, 3, 6, 4, 5, 7, 5};
    DutchFlag_first(grr, 0, 8);
    cout << "DutchFlag_first *** result: ";
    show(grr, 9);

    int krr[] = {2, 1, 4, 3, 6, 4, 5, 7, 5};
    DutchFlag_second(krr, 0, 8);
    cout << "DutchFlag_second *** result: ";
    show(krr, 9);
    
    cout << "------------------------------------" << endl;

    int irr[] = {2, 1, 5, 6, 8, 3, 4, 2, 3, 1};
    heapSort(irr, 10);
    cout << "heapSort *** result: ";
    show(irr, 10);

    int hrr[] = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9};
    sortedArrDistanceLessK(hrr, 10, 2);
    cout << "sortedArrDistanceLessK *** result: ";
    show(hrr, 10);

    cout << "------------------------------------" << endl;

    int jrr[] = {3, 1, 2, 5, 1, 1, 3, 7, 4, 9, 3};
    raidoSort(jrr, 11);
    cout << "raidoSort *** result: ";
    show(jrr, 11);

    return 0;
}

void CreateArrDuiShuQi(int testTimes, int maxSize, int maxValue, bool succeed, void (*pt1)(int *arr, int size), void (*pt2)(int *arr, int size))
{
    for (int i = 0; i < testTimes; ++i)
    {
        //生成两个相同的随机数组
        int arr_size = GetRandomArrSize(maxSize);
        int *arr1 = GenerateRandomArr(arr_size, maxValue);
        int *arr2 = copyArr(arr1, arr_size);
        int *tmp = copyArr(arr1, arr_size);

        //对插入排序、冒泡排序、选择排序进行验证
        pt1(arr1, arr_size);
        show(arr1, arr_size);
        pt2(arr2, arr_size);
        show(arr2, arr_size);
        if(!isEqual(arr1, arr2, arr_size))
        {
            succeed = false;
            delete[] arr1;
            delete[] arr2;
            break;
        }

        /*
        if (!isSorted(arr1, arr_size))
        {
            cout << "方式1排序错了！" << endl;
            for (int j = 0; j < arr_size; j++)
            {
                cout << tmp[j] << " ";
            }
            cout << endl;
        }

        if (!isSorted(arr2, arr_size))
        {
            cout << "方式2排序错了！" << endl;
            for (int j = 0; j < arr_size; j++)
            {
                cout << tmp[j] << " ";
            }
            cout << endl;
        }
        */

        delete[] arr1;
        delete[] arr2;
        delete[] tmp;
    }
    cout << (succeed ? "Nice" : "Wrong") << endl;
}

//提取一个不等于0的数最右侧的1
// int rightone = eor & (~eor + 1);

//有序数组中找到一个数
//二分法O(logN)
bool findNumInSortedArr(int *arr, int num, int size)
{
    if(arr == nullptr || size == 0)
        return false;
    int L = 0;
    int R = size - 1;
    while (L <= R)
    {
        int mid = (L + R) / 2;
        if (num == arr[mid])
            return true;
        else if (arr[mid] < num)
            L = mid + 1;
        else
            R = mid - 1;
    }
    return false;
}

//有序数组中找到一个>=某个数最左边的位置或者<=某个数最右边的位置
//二分法，直到分不下去
int mostLeftNoMoreNumIndex(int *arr, int num, int size)
{
    if (arr == nullptr || size == 0)
        return -1;
    int L = 0;
    int R = size - 1;
    int ans = -1;
    while (L <= R)
    {
        //ans 更新
        int mid = (L + R) / 2;
        if(arr[mid] >= num)
        {
            R = mid - 1;
            ans = mid;
        }
        else
            L = mid + 1;
    }
    return ans;
}

//无序且任何相邻两元素均不相等，找到任意一个局部最小的位置
//先判断两端，然后必可以二分，然后再二分...
int oneMinIndex(int *arr, int size)
{
    if(arr == nullptr || size == 0)
        return -1;
    if (size == 1)
        return 0;

    if (arr[0] < arr[1])
        return 0;
    if (arr[size - 1] < arr[size - 2])
        return size - 1;
    
    int L = 0;
    int R = size - 1;
    //L到R上肯定有局部最小
    while (L < R - 1)
    {
        int mid = (L + R) / 2;
        if (arr[mid] < arr[mid] - 1 && arr[mid] < arr[mid + 1])
            return mid;
        else
        {
            if(arr[mid - 1] < arr[mid])
                R = mid - 1;
            else
                L = mid + 1;
        }
    }
    return arr[L] < arr[R] ? L : R;
}

void printInteger(int num)  //打印整数32位
{
    for (int  i = 31; i >= 0; i--)
    {
        cout << (((num & (1 << i)) == 0) ? "0" : "1");
    }
    cout << endl;
}

//数组范围求和(经常操作的话)    //或者列表，最后直接在表里取值
class RangeSum
{
private:
    int *preSum;

public:
    RangeSum();
    void arrPreSum(int *arr, int size);
    int rangeSum(int L, int R);
    ~RangeSum();
};

RangeSum::~RangeSum()
{
    if (preSum != nullptr)
        delete[] preSum;
}

void RangeSum::arrPreSum(int *arr, int size)
{
    preSum = new int[size];
    preSum[0] = arr[0];
    for (int i = 1; i < size; i++)
    {
        preSum[i] = preSum[i - 1] + arr[i];
    }
}

int RangeSum::rangeSum(int L, int R)
{
        return L == 0 ? preSum[R] : preSum[R] - preSum[L - 1];
}

//一个数组中，只有一种数出现了奇数次，其余数均出现偶数次，找出这个出现了奇数次的数
int Extract1OddNum(int * arr, int size)
{
    int eor = 0;
    for (int i = 0; i < size; i++)
    {
        eor ^= arr[i];
    }
    return eor;
}

//一个数组中，只有两种数出现了奇数次，其余数均出现偶数次，找出这两个出现了奇数次的数
pair<int, int> Extract2OddNum(int* arr, int size)
{
    int eor1 = 0;
    for (int i = 0; i < size; i++)
    {
        eor1 ^= arr[i];
    }
    int rightone = eor1 & (~eor1 + 1);
    int eor2 = 0;
    for (int i = 0; i < size; i++)
    {
        if((rightone & arr[i]) == 0)
        {
            eor2 ^= arr[i];
        }
    }
    eor1 ^= eor2;
    pair<int, int> p1;
    p1.first = eor1;
    p1.second = eor2;
    return p1;
}

//提取数组最大值O(N)
int ExtractMax(int * arr, int L, int R)
{
    if(L == R)
        return arr[L];
    int mid = L + ((R - L) >> 1);
    int leftMax = ExtractMax(arr, L, mid);
    int rightMax = ExtractMax(arr, mid + 1, R);
    return Math_max(leftMax, rightMax);
}

int Math_max(int leftMax, int rightMax)
{
    return leftMax > rightMax ? leftMax : rightMax;
}

//获得MaxSize大小数组，每个元素在[-MaxValue, MaxValue]上等概率
int * GenerateRandomArr(int MaxSize, int MaxValue)
{       
    int *arr = new int[MaxSize];     
    for (int i = 0; i < MaxSize; i++)
    {
        arr[i] = (rand() % (MaxValue + 1)) - (rand() % (MaxValue + 1));
    }
    return arr;
}

//拷贝数组
int * copyArr(int * arr, int size)
{
    int *brr = new int[size];
    for (int i = 0; i < size; ++i)
    {
        brr[i] = arr[i];
    }
    return brr;
}

//判断两个数组是否完全一致
bool isEqual(int *arr1, int* arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;
}

bool isSorted(int *arr, int size)
{
    if (size < 2)
        return true;
    int maxValue = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (maxValue > arr[i])
            return false;
        maxValue = max(maxValue, arr[i]);
    }
    return true;
}

//位运算^交换
void swap(int arr[], int i, int j )
{   
    if(i != j)
    {
        arr[i] = arr[i] ^ arr[j];
        arr[j] = arr[i] ^ arr[j];
        arr[i] = arr[i] ^ arr[j];   //必须内存是分开的两块才能交换，否则就像数组一样，i==j的话指向同一个地址，arr[i]^arr[j] = 0，所以会出事
    }    
}

//正常交换
void swap_right(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//显示数组元素
void show(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

////////////////////////////////////////////
//排序算法
////////////////////////////////////////////

//选择排序O(N^2)
void SelectionSort(int arr[], int size)
{    
    if(arr == nullptr || size < 2)
        return;
    for (int i = 0; i < size; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j)
        {
            minIndex = arr[minIndex] < arr[j] ? minIndex : j;
        }
        swap(arr, i, minIndex);
    }
}

//冒泡排序O(N^2)
void BubbleSort(int arr[], int size)
{    
    if(arr == nullptr || size < 2)
        return;
    for (int len = size; len > 0; len--)
    {
        for (int i = 0; i < len - 1; i++)
        {
            if(arr[i] > arr[i+1])
                swap(arr, i, i + 1);
        }
    }
}

//插入排序O(N^2)    数据好的时候可能只有O(N)
void InsertSort(int arr[], int size)
{
    if(arr == nullptr || size < 2)
        return;
    for (int i = 1; i < size; i++)
    {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
        {
            swap(arr, j, j + 1);
        }
    }
}

//归并排序O(NlogN)  额外空间复杂度O(N)
void ProcessSort(int *arr, int L, int R)
{    
    if(L == R)
        return;
    int mid = L + ((R - L) >> 1);
    ProcessSort(arr, L, mid);
    ProcessSort(arr, mid + 1, R);       //先递归即从底向上操作，分到无法再分了，再开始归并
    merge_sort(arr, L, mid, R);
}

void merge_sort(int *arr, int L, int mid, int R)
{
    int p1 = L;
    int p2 = mid + 1;
    int *help = new int[R - L + 1];
    int i = 0;
    while (p1 <= mid && p2 <= R)
    {
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid)
    {
        help[i++] = arr[p1++];
    }
    while (p2 <= R)
    {
        help[i++] = arr[p2++];
    }
    for (i = 0; i < R - L + 1; i++)
    {
        arr[L + i] = help[i];
    }
    delete[] help;
}

//小和问题(或者逆序对也是类似的思路)
int SmallAdd(int *arr, int L, int R)
{
    if(L == R)
        return 0;
    int mid = L + ((R - L) >> 1);
    return SmallAdd(arr, L, mid) + SmallAdd(arr, mid + 1, R) + merge_smalladd(arr, L, mid, R);      //先递归到无法再分了，分到分无可分，再计数加排序
}

int merge_smalladd(int * arr, int L, int mid, int R)
{
    int p1 = L;
    int p2 = mid + 1;
    int *help = new int[R - L + 1];
    int i = 0;
    int res = 0;
    while (p1 <= mid && p2 <= R)
    {
        res += (arr[p1] < arr[p2] ? (R - p2 + 1) * arr[p1] : 0);
        help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid)
    {
        help[i++] = arr[p1++];
    }
    while (p2 <= R)
    {
        help[i++] = arr[p2++];
    }
    for (i = 0; i < R - L + 1; i++)
    {
        arr[L + i] = help[i];
    }
    delete[] help;
    return res;
}

//逆对数有几对
int InverseLogarithm(int *arr, int L, int R)
{
    if(L == R)
        return 0;
    int mid = L + ((R - L) >> 1);
    return InverseLogarithm(arr, L, mid) +
           InverseLogarithm(arr, mid + 1, R) +
           merge_inverselogarithm(arr, L, mid, R);
}

int merge_inverselogarithm(int *arr, int L, int mid, int R)
{
    int p1 = L;
    int p2 = mid + 1;
    int res = 0;
    int *help = new int[R - L + 1];
    int i = 0;

    while (p1 <= mid && p2 <= R)
    {
        res += arr[p1] > arr[p2] ? (R - p2 + 1) : 0;
        //大和的话如下计算
        // res += arr[p1] > arr[p2] ? (R - mid + 1) * arr[p1] : 0;
        help[i++] = arr[p1] > arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid)
    {
        help[i++] = arr[p1++];
    }
    while (p2 <= R)
    {
        help[i++] = arr[p2++];
    }
    for (i = 0; i < R - L + 1; i++)
    {
        arr[L + i] = help[i];
    }

    delete[] help;
    return res;
}

//荷兰国旗问题1.0(快速排序)
void DutchFlag_first(int *arr, int L, int R)
{
    if(L < R)   //???
    {
        int index = classify2(arr, L, R);
        DutchFlag_first(arr, L, index - 1);
        DutchFlag_first(arr, index + 1, R);
    }
}

int classify2(int * arr, int L, int R)
{
    int lowerBoundary = L - 1;
    int comp_num = arr[R];
    int i = L;
    while(i < R)
    {
        if(arr[i] <= comp_num)
        {
            if(lowerBoundary + 1 == i)
            {
                lowerBoundary++;
                i++;
            }
            else
                swap(arr, ++lowerBoundary, i++);
        }
        else
            i++;
    }
    swap(arr, lowerBoundary + 1, R);
    return lowerBoundary + 1;
}

//荷兰国旗问题2.0(快速排序) O(logN)
void DutchFlag_second(int *arr, int L, int R)
{
    if(L < R)   //???
    {
        int random = L + rand() % (R - L + 1);
        if(random != R)
            swap(arr, L + rand() % (R - L + 1), R);
        int *index = new int[2];
        classify3(arr, L, R, index);
        DutchFlag_second(arr, L, index[0] - 1);
        DutchFlag_second(arr, index[1] + 1, R);
        delete[] index;
    }
}

void classify3(int * arr, int L, int R, int * index)
{
    int lowerboundary = L - 1;
    int moreboundary = R + 1;
    int i = L;
    int comp_num = arr[R];
    while(i != moreboundary)
    {
        if(arr[i] < comp_num)
        {
            if(lowerboundary + 1 == i)
            {
                lowerboundary++;
                i++;
            }
            else
                swap(arr, ++lowerboundary, i++);
        }
        else if(arr[i] == comp_num)
            i++;
        else
        {
            if(moreboundary + -1 == i)
                moreboundary--;
            else
                swap(arr, --moreboundary, i);
        }       
    }
    index[0] = lowerboundary + 1;
    index[1] = moreboundary - 1;
}

//数组下标满足完全二叉树，对应下标的数据形成堆结构(每棵子树的最大值都在顶部就是大根堆)
//index位置数据能否上移
void heapinsert(int *arr, int index)
{
    while (arr[index] > arr[(index - 1) / 2])
    {
        swap(arr, index, (index - 1) / 2);
        index = (index - 1) >> 1;
    }
}

//index位置数据能否下移
void heapify(int *arr, int index, int heapsize)
{
    int left = index * 2 + 1;
    while(left < heapsize)
    {
        int largest = left + 1 < heapsize && arr[left + 1] > arr[left] ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if(largest == index)
            break;
        swap(arr, largest, index);
        index = largest;
        left = index * 2 + 1;
    }
}

//堆排序(O(NlogN))、O(1)
void heapSort(int *arr, int heapsize)
{
    if(arr == nullptr || heapsize < 2)
        return;
    for (int i = 0; i < heapsize; i++)      //O(N)
        heapinsert(arr, i);                 //O(logN)

    // for (int i = heapsize - 1; i > 0; i--)      
    //     heapify(arr, i, heapsize);          //O(N)

    swap_right(arr, 0, --heapsize);
    while (heapsize > 0)                    //O(N)
    {
        heapify(arr, 0, heapsize);          //O(logN)
        swap(arr, 0, --heapsize);
    }
}

//几乎顺序的数组排序，每个元素最大移动范围为k
void sortedArrDistanceLessK(int *arr, int size, int k)
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int index = 0;
    for (; index <= k; index++)
    {
        minHeap.push(arr[index]);
    }
    int i = 0;
    for (; index < size; i++, index++)
    {
        minHeap.push(arr[index]);
        arr[i] = minHeap.top();
        minHeap.pop();
    }
    while (i < size)        //or while (!minHeap.empty())
    {
        arr[i++] = minHeap.top();
        minHeap.pop();
    }
}

//桶排序
void raidoSort(int * arr, int size)
{
    if(arr == nullptr || size < 2)
        return;
    raidoSort(arr, 0, size - 1, maxbits(arr, size));
}

//数组中最大值有多少十进制位
int maxbits(int*arr, int size)
{
    int max = ExtractMax(arr, 0, size - 1);
    int res = 0;
    while(max != 0)
    {
        res++;
        max /= 10;
    }
    return res;
}

void raidoSort(int *arr, int L, int R, int digit)
{
    int radio = 10;
    int *help = new int[R - L + 1];
    int i = 0;
    int j = 0;
    for (int d = 0; d < digit; d++)        //d从0开始
    {
        int *count = new int[radio];
        for (; i < radio; i++)
            count[i] = 0;
        for (i = L; i <= R; i++)
        {
            j = getdigit(arr[i], d); //取出个arr中所有数对应第d位上的数字记为j      0对应个位
            count[j]++;
        }
        for (j = 1; j < radio; j++)
        {
            count[j] += count[j - 1];
        }
        for (i = R; i >= L; i--)
        {
            j = getdigit(arr[i], d);
            help[--count[j]] = arr[i];
        }
        for (i = L, j = 0; i <= R; i++, j++)
        {
            arr[i] = help[j];
        }
    }
}

//取出一个数第digit位上的数字(十进制)   0 -> 个位 ; 1 -> 十位 ; ......
int getdigit(int arr_num, int digit)
{
    return ((arr_num / (int)pow(10, digit)) % 10);
}
