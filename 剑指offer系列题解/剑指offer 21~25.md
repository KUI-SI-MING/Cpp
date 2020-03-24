@[toc]
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
> <font color = black size = 3 face  = "微软雅黑">无论是广度优先遍历一个有向图还是一棵树，都需要用到队列。首先把起始结点（根结点）放入队列中；然后每一次从队列的头部取出一个结点，遍历这个结点之后，把它能到达的结点都依次放入队列。重复这个过程，直到队列中的结点全部被遍历完。<br>
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
##### 4.二叉树中和为某一值的路径
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)
> <font color = black size = 3 face  = "微软雅黑">针对这种问题具体分析，画出一个二叉树查看其规律。题目有两个要求：一是对路径的定义为从树的根结点到叶节点，即路径总是以根结点为起始点，因此需要首先遍历根结点，因此选择树的前序遍历来访问结点。<br>
> <font color = black size = 3 face  = "微软雅黑">此题中二叉树的结构中无指向父结点的指针，因此需要我们保存经过的路径上的结点，每访问一个结点时，我们就把当前的结点添加到路径中去，若到达某个叶结点时当前值并不等于目标值，此时需要删除路径中的结点，即每一次当从子结点返回到父结点时，都需要考虑在路径上删除子结点。<br>
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
  void The_Path(TreeNode* root, int expectNumber, vector<vector<int> >& path, int& currentNumber,
      vector<int>& tmp)
  {
      currentNumber += root->val;
      tmp.push_back(root->val);//根结点入

      bool is_leaf = root->left == nullptr && root->right == nullptr;//是否是叶子结点
      if (currentNumber == expectNumber && is_leaf)//满足要求两个要求即可退出
      {
          path.push_back(tmp);
      }

      if (root->left != nullptr)
      {
          The_Path(root->left, expectNumber, path, currentNumber, tmp);
      }
      if (root->right != nullptr)
      {
          The_Path(root->right, expectNumber, path, currentNumber, tmp);
      }

      currentNumber -= root->val;//从子结点返回到父结点，路径上删除此结点
      tmp.pop_back();
  }

  vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
      vector<vector<int> > res;
      vector<int> path;
      if (root == nullptr)
          return res;

      int currentNumber = 0;
      The_Path(root, expectNumber, res, currentNumber, path);
         
  }
};
```
> <font color = black size = 3 face  = "微软雅黑">上面解法中的递归调用的本质就是一个压栈和入栈的过程，所以可以利用一个辅助栈模拟这个过程，首先从根结点开始遍历，优先将每个结点的左结点压入栈中，直到到达最左边的叶节点，与此同时将`expectNumber`减去但当前结点的值，所以最后的判别标准就是`expectNumber`是否为0；然后获取到最左边的结点，进行条件判断，若满足条件则将路径保存；其次需要考虑的就是上步的从子结点返回到父结点这一步了，出栈后，判断此时栈顶元素的右结点是否遍历过。
```cpp
class Solution {
public:
    vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
        stack<TreeNode*> s;
        vector<int> v;
        vector<vector<int> > res;
 
        while (root || !s.empty())
        {
            while (root)
            {
                s.push(root);
                v.push_back(root->val);
                expectNumber -= root->val;
                //能左就左，否则向右
                root = root->left ? root->left : root->right;
            }
 
            root = s.top();
            if (expectNumber == 0 && root->left == NULL && root->right == NULL)
                res.push_back(v);
 
            s.pop();
            v.pop_back();
            expectNumber += root->val;
            //右子数没遍历就遍历，如果遍历就强迫出栈
            if (!s.empty() && s.top()->left == root)
                root = s.top()->right;
            else
                root = NULL;//强迫出栈
        }
        return res;
    }
};
```
- [二叉树中和为某一值的路径](https://www.nowcoder.com/practice/b736e784e3e34731af99065031301bca)
##### 5.复杂链表的复制
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
> <font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;首先明确复杂链表的组成中，除了有指向下一个结点的指针，还有指向任意结点的指针。<br>
> <font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;要想完不成这个复杂链表的复制，需要考虑两个因素：一是原始链表的每一个结点用next指针链接起来；二是每个结点的随机指针random。当我们完成第一步得到一个新的链表后，考虑第二步时，随机指针指向的元素可能在当前结点的前面，也可能在后面，所以需要从原始链表的头结点开始找，记录下从头结点到当前结点的随机指针指向的结点所走过的步数count，然后在新链表中也是沿着头结点开始走count步即可。这样对于一个含有n个结点的链表，定位每个结点的random都需要从头结点开始经过O(n)在，这种方法的时间复杂度就是O(n^2^)。<br>
>  <font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;针对上述方法的第二步进行优化，采用空间换取时间的做法。第一步复制原始链表的每个结点S创建D，然后将创建出来的结点用next指针连接起来，同时将<S,D>的配对信息保存到一个哈希表中，第二步复制每个结点的random,通过哈希表查找这种对应关系的时间就是O(1)，，对于n个结点的链表来说，所用的时间复杂度就是O(n)。<br>
>  <font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;那么在没有辅助空间的情况下实现O(n)的时间效率。第一步仍然是根据原始结点S创建对应的D，同时将创建好的D连接在S的后面；第二步设置复制出来的random，即若原始链表中的S1的random指向S3，那么复制出来的D1的random同样指向D3；第三步就是将这个长链表拆分成两个链表：将奇数位置的结点用next链接起来就是原始链表；将偶数位置的结点用next链接起来就是复制出来的链表。<br>

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200324173727714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2t1aXNpOTU=,size_16,color_FFFFFF,t_70)
```cpp
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (!pHead) 
			return NULL;
		
		RandomListNode* currNode;
		currNode = pHead;
		
		//创建新结点并放到其后
		while (currNode) 
		{
			RandomListNode *node = new RandomListNode(currNode->label);
			node->next = currNode->next;
			currNode->next = node;
			currNode = node->next;
		}

		//确定新插入节点的random
		currNode = pHead;
		while (currNode) 
		{
			RandomListNode *node = currNode->next;
			if (currNode->random) {
				node->random = currNode->random->next;
			}
			currNode = node->next;
		}

		//分拆长链表
		RandomListNode *pCloneHead = pHead->next;//复制链表
		RandomListNode *tmp;
		currNode = pHead;
		
		while (currNode->next) 
		{//一个一个的接
			tmp = currNode->next;
			currNode->next = tmp->next;
			currNode = tmp;
		}

		return pCloneHead;
	}
};
```
- [复杂链表的复制](https://www.nowcoder.com/practice/f836b2c43afc4b35ad6adc41ec941dba)