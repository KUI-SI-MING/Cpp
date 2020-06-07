##### 1.第一个只出现一次的字符
<font color=black size=3 face="微软雅黑">&emsp;&emsp;在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.
> <font color = black size = 3 face  = "微软雅黑">考虑字符出现的次数，所以统计每个字符出现在字符串中的次数，也就是说实现字符和数字的映射实现，所以采用哈希表进行处理数据，字符是一个长度为8的数据类型，共有256种可能，鉴于题目中说明字符串全部由字母组成，所以创建一个大小为123的数组，将每个字符的ASCⅡ码值作为数组下标对应数组的数字。
```cpp
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int data[123] = { 0 };
        int res = 0;

        for (int i = 0; i < str.size(); i++)
        {
            data[str[i]]++;
        }

        //找到第一次出现一次的元素
        for (int i = 0; i < str.size(); i++)
        {
            if (data[str[i]] == 1)
            {   res = i;
                return res;
            }
        }

        return -1;
    }
};
```
- [第一个只出现一次的字符](https://www.nowcoder.com/practice/1c82e8cf713b4bbeb2a5b31cf5b0417c?tpId=13&tqId=11187&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
- 来源：牛客网(NOWCODER)
##### 2.数组中的逆序对
<font color=black size=3 face="微软雅黑">&emsp;&emsp;在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007
> <font color = black size = 3 face  = "微软雅黑">若是考虑顺序扫描数组，其时间复杂度在数组含有n个元素的情况下时间复杂度为O(n^2^),若是优先考虑比较两个相邻的数字，即将数组进行拆分，划分成子数组的形式，直至子数组只包含一个元素，然后合并相邻子数组，同时进行逆序对的统计，合并子数组时同时完成排序，来避免重复统计。其本质就是归并排序，所以可以基于归并排序完成代码设计。
```cpp
class Solution {
public:
	long long InversePairsCore(vector<int>& data, vector<int>& tmp, int start, int end)
	{
		//子数组只包含一个元素
		if (start == end)
		{
			tmp[start] = data[start];
			return 0;
		}

		int length = (end - start) / 2;//开始划分
		long long left = InversePairsCore(tmp, data, start, start + length);
		long long right = InversePairsCore(tmp, data, start + length + 1, end);

		int i = start + length;
		int j = end;
		int indextmp = end;
		long long count = 0;

		while (i >= start && j >= start + length + 1)
		{
			if (data[i] > data[j])
			{
				tmp[indextmp--] = data[i--];
				count += j - start - length;
			}
			else
			{
				tmp[indextmp--] = data[j--];
			}


		}

		for (; i >= start; i--)
		{
			tmp[indextmp--] = data[i];
		}

		for (; j >= start + length + 1; j--)
		{
			tmp[indextmp--] = data[j];
		}

		return left + right + count;

	}
	int InversePairs(vector<int> data) {
		if (data.size() <= 0)
			return 0;

		vector<int> tmp = data;

		long long cou = InversePairsCore(data, tmp, 0, data.size() - 1);
		return  cou % 1000000007;
	}
};

```
- [数组中的逆序对](https://www.nowcoder.com/practice/96bd6684e04a44eb80e6a68efc0ec6c5?tpId=13&tqId=11188&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)
- 来源：牛客网(NOWCODER)
##### 3.两个链表的第一个公共结点
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入两个链表，找出它们的第一个公共结点。（注意因为传入数据是链表，所以错误测试数据的提示是用其他方式显示的，保证传入数据是正确的）<br>
> <font color = black size = 3 face  = "微软雅黑">假设两条链表的长度分别为m和n。首先考虑暴力法：在某一条链表中顺序遍历链表结点，然后在另外一条链表中顺序遍历结点找到与之相同的结点，即公共结点时间复杂度为O(mn)。<br>
> <font color = black size = 3 face = "微软雅黑">其次两条链表是单向链表，若两者有其公共结点，则其结构一定是Y型结构，故公共结点一定出现在两个链表的尾部，若从链表尾部向前遍历直至最后一个相同的结点即第一个公共结点，但由于链表的结构的特殊性，所以利用栈的“后入先出”特性来进行寻找，时间复杂度为O(m+n).<br>
> <font color = black size = 3 face ="微软雅黑">利用栈的根本出发点就是遍历两条链表的尾部的结点，因此若是在获得链表的长度的前提下，可以得到短的链表与长的链表之间的结点数差，然后让长链表先走几步，在让两个链表开始同时遍历，找到的第一个相同的结点就是公共结点，时间复杂度为O(m+n),但无需额外空间。<br>
```cpp
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
	unsigned int GetListLength(ListNode* head)
	{
		unsigned int len = 0;
		while (head != nullptr)
		{
			++len;
			head = head->next;
		}

		return len;
	}
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		unsigned int len1 = GetListLength(pHead1);//获取长度
		unsigned int len2 = GetListLength(pHead2);

		ListNode* longList = pHead1;
		ListNode* shortList = pHead2;
		int klen = len1 - len2;

		if (len1 < len2)
		{
			longList = pHead2;
			shortList = pHead1;
			klen = len2 - len1;
		}//获取先走的步数

		for (int i = 0; i < klen; i++)
		{//长链表先走klen步
			longList = longList->next;
		}

		while ((longList != nullptr) && (shortList != nullptr) && (longList != shortList))
		{//二者同时走
			longList = longList->next;
			shortList = shortList->next;
		}

		ListNode* commonNode = longList;

		return commonNode;

	}
};
```
- [两个链表的第一个公共结点](https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&tqId=11189&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)
- 来源：牛客网(NOWCODER)
##### 4.数字在排序数组中出现的次数
<font color=black size=3 face="微软雅黑">&emsp;&emsp;统计一个数字在排序数组中出现的次数。
> <font color = black size = 3 face  = "微软雅黑">对于排序的数组而言，利用二分查找法查找数字k第一次出现的位置和最后一次出现的位置，然后求得出现的次数。
```cpp
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int lower = getLower(data,k);
        int upper = getUpper(data,k);

        return upper - lower + 1;
    }

    //获取k第一次出现的下标
    int getLower(vector<int> data,int k){
        int start = 0,end = data.size()-1;
        int mid = (start + end)/2;

        while(start <= end){
            if(data[mid] < k){
                start = mid + 1;
            }else{
                end = mid - 1;
            }
            mid = (start + end)/2;
        }
        return start;
    }
    //获取k最后一次出现的下标
    int getUpper(vector<int> data,int k){
         int start = 0,end = data.size()-1;
        int mid = (start + end)/2;

        while(start <= end){
            if(data[mid] <= k){
                start = mid + 1;
            }else{
                end = mid - 1;
            }
            mid = (start + end)/2;
        }

        return end;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">其递归实现如下：
```cpp
class Solution {
public:
	int GetFirstK(vector<int>&data, int k, int start, int end)
	{
		if (start > end)
			return -1;

		int midIndex = (start + end) / 2;

		if (data[midIndex] == k)
		{
			if ((midIndex > 0 && data[midIndex - 1] != k) || midIndex == 0)
				return midIndex;
			else
				end = midIndex - 1;//midIndex前仍有k
		}
		else if (data[midIndex] > k)
			end = midIndex - 1;
		else
			start = midIndex + 1;

		return GetFirstK(data, k, start, end);

	}

	int GetLastK(vector<int>&data, int k, int start, int end)
	{
		if (start > end)
			return -1;

		int midIndex = (start + end) / 2;

		if (data[midIndex] == k)
		{
			if ((midIndex < (int)data.size() - 1 && data[midIndex + 1] != k) || midIndex == (int)data.size() - 1)
				return midIndex;
			else
				start = midIndex + 1;//midIndex前仍有k
		}
		else if (data[midIndex] > k)
			end = midIndex - 1;
		else
			start = midIndex + 1;

		return GetLastK(data, k, start, end);

	}
	int GetNumberOfK(vector<int> data, int k) {
		int number = 0;

		if (data.size() > 0)
		{
			int first = GetFirstK(data, k, 0, (int)data.size() - 1);
			int last = GetLastK(data, k, 0, (int)data.size() - 1);

			if (first > -1 && last > -1)
				number = last - first + 1;
		}

		return number;
	}
};
```
- [数字在排序数组中出现的次数](https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&tqId=11190&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)
- 来源：牛客网(NOWCODER)
