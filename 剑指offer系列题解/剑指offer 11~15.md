##### 1.二进制中1的个数
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示
> <font color = black size = 3 face  = "微软雅黑">接触到这道题的第一想法就是判断参数二进制数的最右边的一位是不是1，然后将整数右移一位就，这样进行循环判断直到整个整数为0为止，所以有如下代码
```cpp
class Solution {
public:
	int  NumberOf1(int n) {
		int count = 0;
		while (n)
		{
			if (n & 1)
			{
				count++;
			}
			n = n >> 1;
		}
		return count;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">但是这样当n为负数时会出现一些问题,对于n来说为了保持始终是负数，其最高位必须是1，这样经过不断的右移，n的每一位会变成1，从而造成死循环，所以必须换种思路。这次我们不移动n,我们移动1,将n与1做与运算，判断最低位是否为1，然后将1左移一位变为2，再和n相与，判断次低位是否为1，这样反复左移1，在和n进行与操作进而判断n中1的个数,这样循环次数等于二进制的位数，如下
```cpp
class Solution {
public:
	int  NumberOf1(int n) {
		int count = 0;
        unsigned int flag = 1;
		while (flag)
		{
			if (n & flag)
			{
				count++;
			}
			flag = flag << 1;
		}
		return count;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">为了提高效率，根据数学规律，我们知道把一个整数减1，再和原整数做运算，会把该整数最右边的一个1变成0，这样二进制数中有多少个1就进行多少次操作，如下
```cpp
class Solution {
public:
	int  NumberOf1(int n) {
		int cou = 0;

		int tmp = n;
		while (tmp)
		{
            tmp &= (tmp - 1);
			cou++;
		}

		return cou;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[https://www.nowcoder.com/practice/8ee967e43c2c4ec193b040ea7fbb10b8?tpId=13&tqId=11164&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking](https://www.nowcoder.com/practice/8ee967e43c2c4ec193b040ea7fbb10b8?tpId=13&tqId=11164&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
来源：牛客网
##### 2.数值的整数次方
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示
> <font color = black size = 3 face  = "微软雅黑">首先库函数了解一下
```cpp
class Solution {
public:
    //调用库函数
    double Power(double base, int exponent) {
		double res = 0.0;
		res = pow(base, exponent);

		return res;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">关于exponent的正负无法得知，先将其按照正数次幂进行计算，然后判断幂的正负进行相应的处理，实际中在数学上0的0次方是无意义的，为了解决这种错误需要对0进行特殊处理，处理的方法有返回值，异常和全局代码，使用全局变量的一个解法
```cpp
bool g_Invalidinput = false;
class Solution {
public:
	bool equal(double base, double num)
	{
		if ((base - num > -0.0000001) && (base - num < 0.0000001))
			return true;
		else
			return false;
	}

	double PowerAbs(double base, unsigned int ex)
	{
		double res = 1.0;
		for (int i = 1; i <= ex; ++i)
		{
			res *= base;
		}

		return res;
	}
	double Power(double base, int exponent) {
		g_Invalidinput = false;

		if (equal(base, 0.0) && exponent < 0)
		{
			g_Invalidinput = true;
			return 0.0;
		}

		unsigned int absExp = abs(exponent);

		double res = PowerAbs(base, absExp);
		if (exponent < 0)
			return 1.0 / res;
		

		return res;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">另有大佬写的更加精简的写法（膜拜）
```cpp
class Solution {
public:
    //模拟库函数
	double Power(double base, int exponent) {
        
		double res = 1;

		for (int i = 0; i < abs(exponent); i++)
		{
			res *= base;
		}
		//当exponent>=0时
		if (exponent >= 0)
			return res;
		//当exponent<0时
		else
			return 1 / res;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[https://www.nowcoder.com/practice/1a834e5e3e1a4b7ba251417554e07c00?tpId=13&tqId=11165&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking](https://www.nowcoder.com/practice/1a834e5e3e1a4b7ba251417554e07c00?tpId=13&tqId=11165&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
来源：牛客网
##### 3.调整数组顺序使奇数位于偶数前面
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变
> <font color = black size = 3 face  = "微软雅黑">我想到的是从后向前遍历，这样遇到奇数就往前拿，相当于和其之前的第一个偶数进行交换
```cpp
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		int length = array.size() - 1;
		int end = length;

		while (end >= 0)
		{
			if (array[end] % 2 == 1)
			{
				for (int i = end - 1; i >= 0; i--)
				{
					int tmp = 0;
                    //若采用交换则会打乱相对位置，所以采取平移的方式
					if (array[i] % 2 == 0)
					{
						tmp = array[i];
						for (int j = i; j < end; j++)
						{
							array[j] = array[j + 1];
						}
						array[end] = tmp;
						break;
					}
				}
			}
			end--;
		}
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">还可以两边加击，设立两个指针，一个指向头向后遍历，一个指向尾向前遍历，然后分别遇到偶奇数就交换,但是这样有个问题就是不能保持相对位置了
```cpp
class Solution {
public:
	void reOrderArray(vector<int> &array) {
        if(array.size() <= 1)
            return;
		int left = 0;
		int right = array.size() - 1;

		while (left < right)
		{
			while (left < right && (array[left] & 0x1) == 1)
				left++;

			while (left < right && (array[right] & 0x1) == 0)
				right--;

			if(left < right)
				swap(array[left], array[right]);
		}
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">为了更进一步的扩展，这类问题可以总结为两部分：一判断元素位于数组的哪一部分，二是拆分数组
```cpp

bool IsEven(int n)
{
	return (n & 1) == 0;
}

class Solution {
public:
	void Reorder(vector<int> &array, bool (*func)(int))
	{
		if (array.size() <= 1)
			return;

		int left = 0;
		int right = array.size() - 1;

		while (left < right)
		{
			while (left < right && !func(array[left]))
				left++;

			while (left < right && func(array[right]))
				right--;

			if (left < right)
				swap(array[left], array[right]);
		}
	
	}
	void reOrderArray(vector<int> &array) {
		
		Reorder(array, IsEven);
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11166&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking](https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11166&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
来源：牛客网
##### 4.链表中倒数第k个结点
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个链表，输出该链表中倒数第k个结点
> <font color = black size = 3 face  = "微软雅黑">快慢指针法，快指针先走k-1步，然后慢指针从头开始走，快指针同时向后走，当快指针到达尾时，慢指针即结果，快慢指针之间始终相差k-i步，当然需要注意是否为空链表，链表的节点数小于k,	以及k的值为0这三个问题
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
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		if (pListHead == nullptr || k == 0)
			return nullptr;

		ListNode* fast = pListHead;
		ListNode* slow = pListHead;

		for (unsigned int i = 0; i < k - 1; ++i)
		{
			if (fast->next != nullptr)
				fast = fast->next;
			else
				return nullptr;
		}

		while (fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[https://www.nowcoder.com/practice/529d3ae5a407492994ad2a246518148a?tpId=13&tqId=11167&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking](https://www.nowcoder.com/practice/529d3ae5a407492994ad2a246518148a?tpId=13&tqId=11167&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
> 来源：牛客网
##### 5.反转链表
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个链表，反转链表后，输出新链表的表头
> <font color = black size = 3 face  = "微软雅黑">首先考虑递归，用于了解实现过程
> ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190910164713559.png)
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
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == nullptr || pHead->next == nullptr)
            return pHead;
        
        ListNode* rh = ReverseList(pHead->next);
        pHead->next->next = pHead;//自身的下一个元素指向自身
        pHead->next = nullptr;//自身的next指向空
        
        return rh;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">设立三个指针，分别指向当前节点，当前节点的前驱和后继，然后改变三者的指向关系即可
```cpp
class Solution {
public:
	ListNode* ReverseList(ListNode* pHead) {
		ListNode* pReverseHode = nullptr;//反转后的头结点
		ListNode* pCurNode = pHead;//当前节点
		ListNode* pPrev = nullptr;//当前节点的前驱

		while (pCurNode != nullptr)
		{
			ListNode* pnext = pCurNode->next;//保存当前节点的下一节点

			if (pnext == nullptr)
				pReverseHode = pCurNode;

			pCurNode->next = pPrev;
			pPrev = pCurNode;
			pCurNode = pnext;
		}
		return pReverseHode;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=13&tqId=11168&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking](https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=13&tqId=11168&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
> 来源：牛客网
