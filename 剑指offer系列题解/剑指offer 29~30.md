##### 1.最小的K个数
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4
> <font color = black size = 3 face  = "微软雅黑">将整个数组进行排序后，前k个数字就是最小的k个数。其时间复杂度就是O(nlogn)。先来个简单暴力时间复杂度为O(n^2^)的解决方法：每遍历数组，找到最小值然后将其保存，然后将这个元素删除掉便于下一次的查找。直到将最小的k个数全部保存即可。
```cpp
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if(input.size() == 0 || input.size() < k)
            return res;
        vector<int> tmp = input;
 
        while (k--)
        {
            int pos = 0;//标记找到的最小元素位置
            int min = tmp[0];
 
            for (int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i] < min)
                {
                    min = tmp[i];
                    pos = i;
                }
            }
 
            res.push_back(min);
            tmp.erase(tmp.begin() + pos);//将这个最小值删除
        }
        return res;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">从前一个题“数组中出现次数超过一半的数字”来考虑，这个题中以数组的第k个数字来调整，使得比第k个数字小的放置到数组的左边，比第k个数字大的放到数组的右边。即可得到最小的k个数。
```cpp

class Solution {
public:
	int RandomInRange(int start, int end)
	{
		int res = 0;
		res = rand() % (end - start + 1) + start;

		return res;
	}

	int Partition(vector<int>& number, int start, int end)
	{/*
		if (number.size() == 0 || start < 0 || end >= number.size())
			throw new std::exception("Invalid Parameters");*/

			//生成一个随机数，来确定一个随机位置
		int index = RandomInRange(start, end);
		//将产生的随机位置上的元素挪到尾
		swap(number[index], number[end]);


		int pos = start - 1;
		for (index = start; index < end; ++index)
		{
			if (number[index] < number[end])
			{
				++pos;
				if (pos != index)
				{
					swap(number[index], number[pos]);
				}
			}
		}

		++pos;
		swap(number[pos], number[end]);

		return pos;
	}
	
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		vector<int> res;
		if (input.size() == 0 || k > input.size() || k <= 0)
			return res;

		int start = 0;
		int end = input.size() - 1;
		int index = Partition(input, start, end);//数组的深拷贝
		//进行排序
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				end = index - 1;
				index = Partition(input, start, end);
			}
			else
			{
				start = index + 1;
				index = Partition(input, start, end);
			}
		}

		for (int i = 0;i < k; ++i)
		{
			res.push_back(input[i]);
		}

		return res;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">在不修改所给数组的前提下再进行修改。先利用一个容量为k的容器用来保存最小的k个数字然后每次从数组中取出元素，若容器中的元素数小于k个，则将取出的数字保存到容器中，直到容器装满，当容器装满后，此时选出容器中的最大值，然后与数组中的待插入的元素进行比较，如果这个值比这个最大值小，用这个数替换最大值，若比最大值还大就抛弃这个整数。<br>
> <font color = black size = 3 face  = "微软雅黑">当容器满了之后，需要①在容器中选出最大值②有可能会删除这个最大值③有可能插入一个新的数字。利用最大堆来作为容器，但是太过繁杂，因此可以用以红黑树为基础的set和multiset来简化操作，总体时间复杂度为O(nlogn)，并且可以处理海量数据。<br>
```cpp
typedef multiset<int, greater<int>> intSet;
typedef multiset<int, greater<int>>::iterator setIterator;

class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		vector<int> res;
		if (k < 1 || input.size() == 0 || k > input.size())
			return res;

		intSet leastNumbers;
		for (auto iter = input.begin(); iter != input.end(); ++iter)
		{
			if (leastNumbers.size() < k)
			{
				leastNumbers.insert(*iter);//容器未满
			}
			else
			{
				setIterator iterGreatest = leastNumbers.begin();

				if (*iter < *(leastNumbers.begin()))
				{
					leastNumbers.erase(iterGreatest);
					leastNumbers.insert(*iter);
				}
			}
		}
		
		for (auto iter = leastNumbers.begin();iter != leastNumbers.end();++iter)
		{
			res.push_back(*iter);
		}
		return res;
	}
};
```
- [最小的K个数](https://www.nowcoder.com/practice/6a296eb82cf844ca8539b57c23e6e9bf?tpId=13&tqId=11182&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
##### 2.连续子数组的最大和
<font color=black size=3 face="微软雅黑">&emsp;&emsp;HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)<br>
> <font color = black size = 3 face  = "微软雅黑">最直观的方法就是枚举出所有的子序列并求出其和，一个长度为n 的数组共存在n(n+1)/2个子数组。在序列中放入负数，然后求其连续子序列的和，需要在每加入一个元素后，就进行最大值的判断。所以从首元素开始进行处理，针对每一个元素与之后的元素相加，每加入一个数字就确定其max，这样的时间复杂度为O(n^2^)
```cpp 
class Solution {
public:
    void CompareSize(int& n1, int& n2)//将n1,n2中的较大值赋给n2
    {
        if(n1 > n2)
        {
            n2 = n1;
        }
    }
    int FindGreatestSumOfSubArray(vector<int> array) {
        int max;
        int sum = 0;
 
        if(!array.empty())
           max = array[0];
         
        for (int i = 0;i < array.size();i++)
        {
            sum = array[i];
            for (int j = i + 1;j < array.size();j++)
            {
                CompareSize(sum, max);//确保max中的值始终是当前计算到的最大的数值
                sum += array[j];
     
            }
             CompareSize(sum, max);//将最后的数字加入sum后还需要进行一次比较
        }
        return max;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">举列子分析数组的规律，从头到尾逐个累加数组中的每个数字，同时需要判断当前和和最大和之间的最大值。当前和为负数或0时需要舍弃其值直接赋予当前元素。否则直接加上当前元素，并且每次都需要判断当前和和最大和的大小，来更新子序列最大和。
```cpp
class Solution {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		if (array.size() == 0)
			return 0;

		int curSum = 0;
		int greatSum = 0x80000000;

		for (int i = 0; i < array.size(); ++i)
		{
			if (curSum <= 0)
			{
				curSum = array[i];
			}
			else
			{
				curSum += array[i];
			}

			greatSum = (curSum > greatSum) ? curSum : greatSum;
		}

		return greatSum;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">再利用动态规划来解决这个问题。利用函数f(i)表示以第i个数字结尾的子数组的最大和，求出Max[f(i)],其中0<=i<=n，可以得到公式:<br>

> `f(i) = array[i]` &emsp;i = 0 or f(i - 1)<=0<br>
> &emsp;&emsp;&emsp;&emsp;`f(i - 1) + array[i]` &emsp; i != 0 & f(i - 1) >0<br>

> <font color = black size = 3 face  = "微软雅黑">公式的含义是：当以第i-1个数字结尾的子数组中的数字和小于0时，如果把这个负数和第i个数字相加，得到的结果比第i个数字本身还要小，此时就需要舍弃这个和，即以第i个数字结尾的子数组的和为当前第i个元素的本身。如果以第i-1个数字结尾的子数组的和大于0，将其与第i个数字相加即可得到以第i个数字结尾的子数组的和。这种递归过程解释成循环就是上述解法，f(i)为curSum,max[f(i)] 为greatSum.
```cpp
class Solution {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		int res = INT_MIN, curSum = 0;

		for (int num : array) 
		{
			curSum = max(curSum + num, num);
			res = max(res, curSum);
		}

		return res;
	}
};
```
