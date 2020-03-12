##### 1.合并两个排序的链表
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则
> <font color = black size = 3 face  = "微软雅黑">首先了解到的要点就是需要合并两个已经排序后的链表，因此就有两种选择：①创建第三条链表，同时对两条原始链表的元素从头开始进行比较然后将得到的元素压入新链表直到某一条链表结束，将剩下的链表接上即可②在两条原始链表的基础上进行元素的处理，即选择长链表作为最终返回值，将短链表中的元素压入长链表，处理好前后之间的关系即可
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
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		ListNode* newlist;

		if (pHead1 == pHead2 || pHead2 == NULL)
		{
			return pHead1;//两条链表相同或者第二条链表为空
		}
		else if (pHead1 == NULL) {
			return pHead2;//第一条链表为空
		}
		else//两条链表都不为空
		{
			if (pHead1->val < pHead2->val)//第一条链表的值小于第二条链表的值
			{
				newlist = pHead1;//插入第一条链表的元素
				newlist->next = Merge(pHead1->next, pHead2);
			}
			else//第一条链表的值大于第二条链表的值
			{
				newlist = pHead2;//插入第二条链表的元素
				newlist->next = Merge(pHead1, pHead2->next);
			}
		}
		return newlist;
	}
};
```
> <font color = black size = 3 face  = "微软雅黑">链接：[合并两个排序的链表](https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=13&tqId=11169&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 2.树的子结构
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
> <font color = black size = 3 face  = "微软雅黑">查找A树中是否存在和B树结构一致的子结构，可分为两方面：①在A树中找到和B树的根节点的值一致的节点C②然后判断A树中以C为根节点的子树是否包含和B树一致的结构
>  <font color = black size = 3 face  = "微软雅黑">第一步在A树中查找和B树根节点一致的节点，实质就是树的遍历，鉴于二叉树的结构特点选用递归的方法进行遍历，当找到相应节点后进行第二步处理
>  <font color = black size = 3 face  = "微软雅黑">第二步判断A树中以C节点为根节点的子树中是否包含和B树具有相同的结构，利用递归，若界节点C的值和B树不一致，则返回false，若一致，则递归判断它们各自的左右节点，直至A树或B树的叶节点
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
    //其次，当找着R后，判断Tree1中以R为跟节点的树和Tree2结构是否相同，以Tree1和Tree2的空节点为限
    bool Tree1hasTree2(TreeNode* p1, TreeNode* p2)
    {
        if (p2 == nullptr)
            return true;
 
        if (p1 == nullptr)
            return false;
 
        if (p1->val != p2->val)
            return false;
 
        return Tree1hasTree2(p1->left, p2->left) && Tree1hasTree2(p1->right, p2->right);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        //首先在Root1中查找Root2的根结点相同的节点R
        bool result = false;
 
        if (pRoot1 != nullptr && pRoot2 != nullptr)
        {
            if(pRoot1->val == pRoot2->val)
                result = Tree1hasTree2(pRoot1, pRoot2);
 
            if (!result)
                result = HasSubtree(pRoot1->left, pRoot2);
            if (!result)
                result = HasSubtree(pRoot1->right, pRoot2);
        }
         
        return result;
    }
};
```
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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if(pRoot1 == NULL || pRoot2 == NULL) return false;
        if(pRoot1->val == pRoot2->val && MyHasSubtree(pRoot1, pRoot2)) {    // 找到与根相同的结点才往下判断
            return true;
        }
        return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);   // 查找A的左右子树是不是含有B树
    }

    bool MyHasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if(pRoot2 == NULL) return true; // B树匹配到叶子结点了，说明B是A的子结构
        if(pRoot1 == NULL) return false;    // B没到叶子结点，A就已经到了叶子结点，说明B还没匹配完
        if(pRoot1->val == pRoot2->val) {
            return MyHasSubtree(pRoot1->left, pRoot2->left) && MyHasSubtree(pRoot1->right, pRoot2->right);
        }
        return false;
    }
};
```
- [树的子结构](https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&tqId=11170&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 3.二叉树的镜像
<font color=black size=3 face="微软雅黑">&emsp;&emsp;操作给定的二叉树，将其变换为源二叉树的镜像
>![在这里插入图片描述](https://img-blog.csdnimg.cn/20200311203458537.png)
> <font color=black size=3 face="微软雅黑">&emsp;首先根据提供的信息观察特点，对比源二叉树和镜像二叉树，可以发现根结点相同；镜像二叉树第二层交换了源二叉树根节点的两个子结点；镜像二叉树第三层即使在上一步的基础上进一步交换每个含叶结点的左右结点。
> <font color=black size=3 face="微软雅黑">&emsp;根据上面的特点可以总结到：先前序遍历二叉树的每个结点，如过遍历到的结点有子结点，就交换它的两个子结点，直至交换完所有的非叶子节点的左右结点后即可得到镜像二叉树
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
    void Mirror(TreeNode *pRoot) {
    // 空节点
        if(pRoot==nullptr)
            return;
 
        // 叶子结点
        if(pRoot->left==nullptr&&pRoot->right==nullptr)
            return;
 
        // 二叉树有多个节点时，交换当前节点的左右节点
        TreeNode* temp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = temp;
         
        // 二叉树的遍历
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
```
##### 4.顺时针打印矩阵
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
><font color=black size=3 face="微软雅黑">1 &emsp;2&emsp; 3&emsp; 4
>5 &emsp;6&emsp; 7&emsp; 8
>9 &emsp;10 &ensp;11&emsp;12
>13&ensp;14&emsp;15&emsp;16

><font color=black size=3 face="微软雅黑">针对这道题，没有特别的数据结构和高级的算法，考虑到的也即是此题中需要用到多次循环以及判断多个边界条件。因此我们首先考虑特殊情况：单行及单列。然后在考虑一般情况：首先计算需要打印几圈，计算出行rows列cols的较小值min，若min为偶数则圈数为：layers = min / 2;min为奇数则圈数为：layers = min / 2 + 1;然后再控制循环一圈一圈的打印数字
```cpp
class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		int cols = matrix[0].size();
		int rows = matrix.size();

		vector<int> res;

		if (cols == 1)//单列
		{
			for (int i = 0; i < rows; i++)
			{
				res.push_back(matrix[i][0]);
			}
			return res;
		}
		if (rows == 1)//单行
		{
			for (int i = 0; i < cols; i++)
			{
				res.push_back(matrix[0][i]);
			}
			return res;
		}

		int start1 = 0;
		int start2 = 0;
		int end1 = rows;
		int end2 = cols;
		int layers = 0;
		int max = rows;
		int min = cols;

		if (cols > rows)
		{
			swap(max, min);
		}
		if (min % 2 == 0)
		{
			layers = min / 2;
		}
		else
		{
			layers = min / 2 + 1;//圈数
		}

		for (int i = start1; i < end1; i++)
		{
			int flag = 0;//顺时针转一圈的每一个组成都是不可缺少的
			//从左到右
			for (int j = start2; j < end2; j++)
			{
				res.push_back(matrix[i][j]);
				flag = 1;
			}
			//从上到下，要想无从上到下的元素必须确保从左到右的元素已经被取过
			if (flag == 1)
			{
				for (int j = i + 1; j < end1; j++)
				{
					res.push_back(matrix[j][end2 - 1]);
					flag = 2;
				}
			}
			//从右到左
			if (flag == 2)
			{
				for (int j = end2 - 1 - 1; j >= i; j--)
				{
					res.push_back(matrix[end1 - 1][j]);
					flag = 3;
				}
			}
			//从下到上
			if (flag == 3)
			{
				for (int j = end1 - 1 - 1; j > i; j--)
				{
					res.push_back(matrix[j][i]);
				}
			}

			start1++;
			start2++;
			end1--;
			end2--;
			layers--;
			if (layers == 0)
			{
				break;
			}
		}
		return res;
	}
};
```	
##### 5.包含min函数的栈
<font color=black size=3 face="微软雅黑">&emsp;&emsp;定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。
注意：保证测试中不会当栈为空的时候，对栈调用pop()或者min()或者top()方法。
><font color=black size=3 face="微软雅黑">题目要求时间复杂度为O(1)，	就需要我们考率很多的设计，	若是用一个变量存储最小值那么当当前最小元素出栈后，无法获得下一个最小的元素，因此需要用一个辅助栈进行数据的保存，当我们每次把最小元素压入辅助栈，就能保证辅助栈的栈顶一直是最小元素，当最小元素从数据栈内弹出后，同时弹出辅助栈的栈顶元素，此时辅助栈的栈顶元素就是下一个最小值

|步骤  | 操作 |数据栈|辅助栈|最小值
|--|--|--|--|--|
| 1 | 压入3 |3 | 3 | 3
| 2 | 压入4 |3，4 | 3，3 | 3
| 3 | 压入2 |3，4，2 | 3，3，2 | 2
| 4 | 压入1 |3，4，2，1 | 3，3，2，1 | 1
| 3 | 弹出 |3，4，2 | 3，3，2 | 2
| 3 | 弹出 |3，4| 3，3| 3
| 3 | 压入0 |3，4，0 | 3，3，0 | 0
```cpp
#include <stack>
class Solution {
public:
    void push(int value) {
        ordin_stack.push(value);
         
        if(min_stack.empty() || value <= min_stack.top())
        {
            min_stack.push(value);
        }
    }
    void pop() {
        if(ordin_stack.top() == min_stack.top())
        {
            ordin_stack.pop();
            min_stack.pop();
        }
        else{
            ordin_stack.pop();
        }
    }
    int top() {
            return ordin_stack.top();
    }
    int min() {
        return min_stack.top();
    }
private:
    std::stack<int> ordin_stack;
     
    std::stack<int> min_stack;
};
```