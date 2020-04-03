##### 1.二叉搜索树与双向链表
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
> <font color = black size = 3 face  = "微软雅黑">二叉树的每个结点都有两个指向子结点的指针，双向链表中的每个结点都存在两个指针，分别指向前一个结点和后一个结点，两者结构类似。转换之后的链表是排序的链表，因此中序遍历二叉搜索树中的结点实现由小到大取出元素的目的。利用递归将左子树，右子树转换成双向链表后再和根结点链接即可得到之后的双向链表。
```cpp
/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right; 
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/
class Solution {
public:
    void ConvertNode(TreeNode* Node, TreeNode** LastNodeInList)
    {
        if (Node == nullptr)
            return;
 
 		//中序遍历
        TreeNode* CurrentNode = Node;
        if (CurrentNode->left != nullptr)
            ConvertNode(CurrentNode->left, LastNodeInList);
 
        CurrentNode->left = *LastNodeInList;
        if (*LastNodeInList != nullptr)
            (*LastNodeInList)->right = CurrentNode;
 
        *LastNodeInList = CurrentNode;
        if (CurrentNode->right != nullptr)
            ConvertNode(CurrentNode->right, LastNodeInList);
 
    }
 
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode* LastNodeInList = nullptr;
        ConvertNode(pRootOfTree, &LastNodeInList);
 
 		//LastNodeInList指向的是双向链表的尾结点，需要返回头结点
        TreeNode* HeadofList = LastNodeInList;
        while (HeadofList != nullptr && HeadofList->left != nullptr)
            HeadofList = HeadofList->left;
 
        return HeadofList;
    }
};
```
- [二叉搜索树与双向链表](https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&tqId=11179&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 2.字符串的排列
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba
输入描述
> <font color = black size = 3 face  = "微软雅黑">输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母<br>

> <font color = black size = 3 face  = "微软雅黑">将复杂问题分解成小问题进行思考，我们将一个字符串看成两个部分，第一个部分是它的第一个字符，第二部分就是后面的所有字符。因此求整个字符串的排列，可以分为两步：①首先求所有可能出现在第一个位置的字符，即将第一个字符和后面的所有字符进行交换；固定好第一个字符后，将后面的所有字符	也分为两部分：后面字符的第一个字符以及这个字符之后之后的所有字符，然后将第一个字符和后面的字符逐一交换。<br>
```cpp
class Solution {
public:
    void Permuta(string &str, int begin, vector<string>& res)
    {
        if (str[begin] == '\0')
        {
            // 如果result中不存在str，才添加；避免aa和aa重复添加的情况
            if(find(res.begin(), res.end(), str) == res.end())
                res.push_back(str);
        }
        else
        {
            for (int i = begin; str[i] != '\0'; i++)
            {
                swap(str[i], str[begin]);
                Permuta(str, begin + 1, res);
                swap(str[i], str[begin]);// 复位，用以恢复之前字符串顺序，达到第一位依次跟其他位交换的目的
            }
        }
    }
 
    vector<string> Permutation(string str) {
        vector<string> res;
        if(str.size() == 0)
            return res;
 
        Permuta(str,0, res);
        // 此时得到的result中排列并不是字典顺序，可以单独再排下序
        sort(res.begin(), res.end());
        return res;
    }
};
```
- [字符串的排列](https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=13&tqId=11180&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 3.数组中出现次数超过一半的数字
<font color=black size=3 face="微软雅黑">&emsp;&emsp;数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组的一半，因此输出2。如果不存在则输出0
输入描述
> <font color = black size = 3 face  = "微软雅黑">这个题中，考虑数组要是排序的局可以快速解决这个问题，但是题目中并未给定排好的数组，所以需要自己来排序，时间复杂度为O(nlogn)。除此之外，先用遍历的方法做一下。时间复杂度是O(n^2^)
```cpp
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int i = 0, j = 0;
        int len = numbers.size();
        int count = 0;
         
        for(i = 0; i < len; i++)
        {
            count = 0;
            for(j = 0; j < len; j++)
            {
            	//找到相同的就+1
                if(numbers[i] == numbers[j])
                {
                    count += 1;
                }
            }
            //判断是否满足条件
            if(count > (len >> 1))
            {
                return numbers[i];
            }
        }
        return 0;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">接下来考虑时间复杂度为O(n)的方法。基于partition函数的O(n)算法。数组中的某一个数字出现的次数超过数组长度的一半，那么将数组排序后，位于数组中间的数字一定是那个出现次数超过数组长度的元素。这个元素即统计学上的中位数，即长度为nz的数组中第n/2大的数字，可以采用O(n)的算法来完成.<br>
> <font color = black size = 3 face  = "微软雅黑">从快排算法开始思考，在随机快速排序算法中，先在数组中随机选一个数字，然后调整数组中数字的顺序，使得比选中的数字小的都排在它的左边，比选中的数字大的数字都放到该数字的右边。完成后如果这个数字的下标刚好是n/2则就是中位数，若下标大于n/2，那么中位数就在它的左边，否则就在右边,即为一个递归过程。<br>
```cpp

class Solution {
public:
	int RandomInRange(int start, int end)
	{
		int res = 0;
		res = rand() % (end - start + 1) + start;

		return res;
	}

	int Partition(vector<int> number, int start, int end)
	{/*
		if (number.size() == 0 || start < 0 || end >= number.size())
			throw new std::exception("Invalid Parameters");*/

		//生成一个随机数，来确定一个随机位置
		int index = RandomInRange(start, end);
		//将产生的随机位置上的元素挪到尾
		swap(number[index], number[end]);


		int pos = start - 1;
		for (index = start;index < end; ++index)
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

	bool CheckMoreThanHalf(vector<int>& numers, int val)
	{
		int times = 0;
		for (int i = 0; i < numers.size(); ++i)
		{
			if (numers[i] == val)
				times++;
		}

		bool isMoreThanHalf = true;
		if (times * 2 <= numers.size())
		{
			isMoreThanHalf = false;
		}

		return isMoreThanHalf;
	}


	int MoreThanHalfNum_Solution(vector<int> numbers) {
		if (numbers.size() == 0)
			return 0;

		int middle = numbers.size() >> 1;
		int start = 0;
		int end = numbers.size() - 1;
		int index = Partition(numbers, start, end);

		while (index != middle)
		{
			if (index > middle)
			{
				end = index - 1;
				index = Partition(numbers, start, end);
			}
			else
			{
				start = index + 1;
				index = Partition(numbers, start, end);
			}
		}

		int res = numbers[middle];
		if (!CheckMoreThanHalf(numbers, res))
			res = 0;

		return res;
	}
};	
```
> <font color = black size = 3 face  = "微软雅黑">也可以考虑用数组特点找出O(n)的算法。数组中有一个数字出现的次数差超过数组长度的一半，也就是说这个数字出现的次数比其他所有数字出现次数的和还要大。因此在遍历数组的时候设置两个值，一个是数组中的一个数字，一个是次数。当我们遍历到下一个数字的时候，如果下一个数字和之前保存的数字相同，则次数加1，如果下一个数字和之前保存的数字不同，则次数减1，如果次数为0，则保存下一个数字，并将次数设置为1。因为要找的数字出现的次数比其他所有的数字出现的次数之和都要多，因此要找的数字就是最后一次把次数设为1时对应的数字。
```cpp

class Solution {
public:

	bool CheckMoreThanHalf(vector<int>& numers, int val)
	{
		int times = 0;
		for (int i = 0; i < numers.size(); ++i)
		{
			if (numers[i] == val)
				times++;
		}

		bool isMoreThanHalf = true;
		if (times * 2 <= numers.size())
		{
			isMoreThanHalf = false;
		}

		return isMoreThanHalf;
	}
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		if (numbers.size() == 0)
			return 0;

		int res = numbers[0];
		int times = 1;

		for (int i = 0; i < numbers.size(); ++i)
		{
			if (times == 0)
			{
				res = numbers[i];
				times = 1;
			}
			else if (numbers[i] == res)
			{
				times++;
			}
			else
				times--;
		}

		if (!CheckMoreThanHalf(numbers, res))
			res = 0;

		return res;
	}
};
```
- [数组中出现次数超过一半的数字](https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=13&tqId=11181&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)