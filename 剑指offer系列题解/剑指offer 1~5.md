##### 1.二维数组中的查找
<font color=black size=3 face="微软雅黑">&emsp;&emsp;在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数
> <font color=black size=3 face="微软雅黑">通过对具体例子的研究，可以想到首先选取右上角的数字，如果该数字等于查找的数字则退出，若是小于查找的数字则除去此行，若大于查找的数字则除去此列，这样缩小查找的范围，直到找到该数字或者范围为空时停止
```cpp
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int rows = array.size();
        int cols = array[0].size();
        
        if(array.size() > 0 )
        {
            int i = 0;
            int j = cols - 1;
            while((i  < rows) && (j >= 0))
            {
                if(array[i][j] == target)
                {
                    return true;
                }
                else if(array[i][j] < target)
                {
                    i++;
                }
                else
                {
                    j--;
                }
            }
        }
        return false;
    }
};
```
- <font color=black size=3 face="微软雅黑">[二维数组中的查找](https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 2.替换空格
<font color=black size=3 face="微软雅黑">&emsp;&emsp;请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy
> <font color=black size=3 face="微软雅黑">最简单的莫过于重新申请一块内存然后将源字符串中的数据拷贝过来，在拷贝过程中遇到空格就替换，还有就是若希望在原来的字符串上做替换，对于做到时间复杂度为O(n)的算法需要做到：设定两个指针，P1和P2，P1指向源字符串的末尾，P2指向扩张后的字符串的末尾，然后向前移动P1并将指向的字符赋给P2指向的空间，当P1指向空格时P1向前移动一格，在P2前插入"%20",然后P2向前移动三格，那么当P1等于P2时即可完成目标
```cpp
class Solution {
public:
	void replaceSpace(char *str,int length) {
        if(str == nullptr && length <= 0)
            return;
        
        int space_count = 0;
        for(int i = 0;i < length;i++)
        {
            if(*(str + i) == ' ')
            {
                space_count += 1;
            }
        }
        
        int i = 0;
        int string_size = 0;
        while(*(str + i) != '\0')
        {
            string_size++;
            i++;
        }
        int Modi_string_size = string_size + 2 * space_count;
        if(Modi_string_size > length)
            return;
            
        char* p1 = str + string_size;
        char* p2 = str + Modi_string_size;
        while(p1 != p2)
        {
            if(*p1 == ' ')
            {
                *(p2--) = '0';
                *(p2--) = '2';
                *(p2--) = '%';
            }
            else
            {
                *(p2--) = *(p1);
            }
            --p1;
        }
	}
};
```
- <font color=black size=3 face="微软雅黑">[替换空格](https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&tqId=11155&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
##### 3.从尾到头打印链表
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个链表，按链表值从尾到头的顺序返回一个ArrayList
> <font color=black size=3 face="微软雅黑">当不改变链表的时候，采用递归是一个比较好的方法，每访问到一个结点的时候，先递归找到它的下一个节点，再输出自己或者存入数组中
```cpp
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ArrayList;
        PrintListFromTailToHead(head,ArrayList);
        return  ArrayList;
    }
    
    void  PrintListFromTailToHead(ListNode* head,vector<int> &ArrayList)
    {
        if(head != NULL)
        {
            if(head->next != NULL)
            {
                PrintListFromTailToHead(head->next,ArrayList);
            }
            ArrayList.push_back(head->val);
        }
    }
};
```
- <font color=black size=3 face="微软雅黑">[从尾到头打印链表](https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&tqId=11156&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 4.重建二叉树
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回
> <font color=black size=3 face="微软雅黑">二叉树是一种递归结构，利用前序第一个元素确定根结点，然后利用中序中根结点的位置确定左右子树的元素，再利用递归的方法确定左右子树
```cpp
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;尿素
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        //前序的第一个节点是根节点，在中序中找到根节点所在的位置
        //假定中序中根节点的位置是 i，那么
        //前序中 0~i:根节点左子树前序；i+1~size根节点右子树前序
        //中序 0~i：根节点左子树中序；i+1~size根节点右子树中序
        int size = vin.size();
        if(0 == size)
        {
            return NULL;
        }
        
        vector<int> pre_left, pre_right, vin_left, vin_right;
        int index = pre[0];
        int i = 0;
        while(i < size)
        {
            if(pre[0] == vin[i])
            {
                index = i;
                break;
            }
            i++;
        }
        
        for(i = 0; i < index; i++)
        {
            pre_left.push_back(pre[i + 1]);
            vin_left.push_back(vin[i]);
        }
        for(i = 0; i < size - index - 1; i++)
        {
            pre_right.push_back(pre[index + i + 1]);
            vin_right.push_back(vin[index + i + 1]);
        }
        
        TreeNode* node = new TreeNode(pre[0]);
        node->left = reConstructBinaryTree(pre_left, vin_left);
        node->right = reConstructBinaryTree(pre_right, vin_right);
        
        return node;
    }
};
```
- <font color=black size=3 face="微软雅黑">[重建二叉树](https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=11157&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 5.用两个栈实现队列
<font color=black size=3 face="微软雅黑">&emsp;&emsp;用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型
> <font color=black size=3 face="微软雅黑">栈：先入后出，队列：先入先出，还是通过具体例子思考后可以知道设定了两个栈，S1和S2，先将元素压入S1，当S2为空时将S1中的元素压入S2中，那么S2中栈顶始终是最先进入队列的元素，那么将其弹出就可以做到先入先出了
```cpp
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int res = stack2.top();
        stack2.pop();
        return res;
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};
```
- <font color=black size=3 face="微软雅黑">[用两个栈实现队列](https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&tqId=11158&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
