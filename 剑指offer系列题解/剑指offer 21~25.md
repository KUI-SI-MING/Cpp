##### 1.栈的压入、弹出序列
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
> <font color = black size = 3 face  = "微软雅黑">利用辅助栈进行处理会使问题变得易处理，观察出栈和入栈的序列可以得到规律：首先如果下一个弹出的数字是栈顶数字，那么就直接弹出，如果下一个弹出的数字不在栈顶，就个压栈序列中还没有入栈的数字入栈，直到把下一个需要弹出的数字压入栈顶为止，然后辅助栈出栈，出栈序列数字后移一个，直到将所有元素压入辅助栈；然后在利用辅助栈栈顶和出栈序列数字之间的对比进行判断
```cpp
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        std::stack<int> st;
         
        int index = 0;
        int outdex = 0;
         
        while(index < pushV.size())//元素是否全部入栈
        {
            if(st.empty() || st.top() != popV[outdex])
            {
                st.push(pushV[index]);
                ++index;
            }
            else{//元素相同就出栈
                st.pop();
                ++outdex;
            }
        }
        while(!st.empty())
        {
            if(st.top() != popV[outdex++])
            {
                return false;
            }
            st.pop();
        }
        return true;
    }
};
```
- [栈的压入、弹出序列](https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&tqId=11174&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 2.从上往下打印二叉树
<font color=black size=3 face="微软雅黑">&emsp;&emsp;从上往下打印出二叉树的每个节点，同层节点从左至右打印。
> <font color = black size = 3 face  = "微软雅黑">这道题也就是二叉树的层序遍历，使用具体例子分析，可以得到解决它的方法。每次打印一个结点时，若该结点有子结点则将其放到有个队列的末尾，然后从队列的头部取出最先进入队列的结点，重复之前操作，直至队列为空。<br>
> <font color = black size = 3 face  = "微软雅黑">无论是广度优先遍历一个有向图还是一棵树，都需要用到队列。首先把起始结点（根结点）放入队列中；然后每一次从队列的头部取出一个结点，遍历这个结点之后，把它能到达的结点都依次放入队列。重复这个过程，直到队列中的结点全部被遍历完。
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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        queue<TreeNode*> queuenode;
        vector<int> res;
        if (root == nullptr)
            return res;
 
        queuenode.push(root);
        while (queuenode.size())
        {
            res.push_back(queuenode.front()->val);
            if (queuenode.front()->left)
            {
                queuenode.push(queuenode.front()->left);
            }
            if (queuenode.front()->right)
            {
                queuenode.push(queuenode.front()->right);
            }
 
            queuenode.pop();
        }
 
        return res;
    }
};
```
- [从上往下打印二叉树](https://www.nowcoder.com/profile/3257191/codeBookDetail?submissionId=51548223)
##### 3.二叉搜索树的后序遍历序列
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
> <font color = black size = 3 face  = "微软雅黑">举个例子：如[5,7,6,9,11,10,8]返回true，首先明确后序遍历数组的结构特点：后序遍历的结构是`LRV`即最后一个数字是根结点，对于二叉搜索树来说，数组剩下的元素可以分为两部分：第一部分是左子树，比根结点的值小；第二部分是右子树，比根结点的值大。针对这种特点，利用递归确定与数组每一部分对应的子树的结构
```cpp
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        //判断sequence是是否为空
        if (sequence.size() == 0)
        {
            return false;
        }
 
        vector<int> aleft;
        vector<int> aright;
 
        int root = sequence[sequence.size() - 1];
         
        //二叉搜索树的左子树的节点小于根节点
        int pos = 0;
        for (; pos < sequence.size() - 1; pos++)
        {
            if (sequence[pos] > root)
                break;
            aleft.push_back(sequence[pos]);
        }
 
        int i = pos;
        for (; i < sequence.size() - 1; i++)
        {
            if (sequence[i] < root)
                return false;
            aright.push_back(sequence[i]);
        }
 
        //判断左子树
        bool left = true;
        if (pos > 0)
            left = VerifySquenceOfBST(aleft);
 
        bool right = true;
        if (pos < sequence.size() - 1)
            right = VerifySquenceOfBST(aright);
 
 
        return (left && right);
    }
};
```
- [二叉搜索树的后序遍历序列](https://www.nowcoder.com/practice/a861533d45854474ac791d90e447bafd?tpId=13&tqId=11176&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)