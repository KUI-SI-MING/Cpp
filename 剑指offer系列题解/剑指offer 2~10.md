##### 1.旋转数组的最小数字
<font color=black size=3 face="微软雅黑">&emsp;&emsp;把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0
> <font color=black size=3 face="微软雅黑">旋转之后的数组可分为两个增序的子数组，而且前一部分的子数组的元素是大于等于后一部分的数组元素的，这样整个数组中最先元素就是前后两部分的分界线，所以就取了个巧找到后一个元素小于前一个元素时就返回那个后一个元素，这样时间复杂度最差是O(n)，最好是O(1)，当然了要注意一些特殊情况
```cpp
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() == 0)
            return 0;
        else if(rotateArray.size() == 1)
            return rotateArray[0];
        
        for(int i = 1;i < rotateArray.size();i++)
        {
            if(rotateArray[i] < rotateArray[i -1])
                return rotateArray[i];
        }
        return rotateArray[0];
    }
};
```
- <font color=black size=3 face="微软雅黑">[旋转数组的最小数字](https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=11159&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 2.斐波那契数列
<font color=black size=3 face="微软雅黑">&emsp;&emsp;大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39
> <font color=black size=3 face="微软雅黑">实现斐波那契数列的方法很多，若是采用递归方法则会提示占用资源过大其实不能运行，所以采用了迭代的方法来计算
```cpp
class Solution {
public:
	int Fibonacci(int n) {
		if (n == 0)
			return 0;
		if (n == 1 || n == 2)
			return 1;


		int n1 = 0;
		int n2 = 1;
		int res = 0;
		for (int i = 2; i <= n; i++)
		{
			res = n1 + n2;
			n1 = n2;
			n2 = res;
		}

		return res;
}
};
```
- <font color=black size=3 face="微软雅黑">[斐波那契数列](https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=11160&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 3.跳台阶
<font color=black size=3 face="微软雅黑">&emsp;&emsp;一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）
> <font color=black size=3 face="微软雅黑">分析具体情况可以看到 1级台阶：1种，2级台阶：2种,3级台阶：3种，4级台阶：5种......可以推断出是类似斐波那契数的一种排列
```cpp
class Solution {
public:
    int jumpFloor(int number) {
        if (1 == number)
			return 1;
		if (2 == number)
			return 2;
		
		int n1 = 1;
		int n2 = 2;
		int res = 0;
		for (int i = 3; i <= number; i++)
		{
			res = n1 + n2;
			n1 = n2;
			n2 = res;
		}

		return res;
    }
};
```
- <font color=black size=3 face="微软雅黑">[跳台阶](https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=13&tqId=11161&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)
##### 4.变态跳台阶
<font color=black size=3 face="微软雅黑">&emsp;&emsp;一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法
> <font color=black size=3 face="微软雅黑">同样的经过画图分析有；1级：1种， 2级：2种， 3级：4种， 4级8种......可以看到 n级台阶的跳法是n - 1级台阶的2倍
```cpp
class Solution {
public:
	int jumpFloorII(int number) {
        //通过具体实例1:1  2：2  3：4  4:8即n级台阶是n-1级台阶的2倍
		if (0 == number)
		{
			return 0;
		}
		else if (1 == number)
		{
			return 1;
		}

		int res = 2 * jumpFloorII(number - 1);
		return res;
	}
};
```
- <font color=black size=3 face="微软雅黑">[变态跳台阶](https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=11162&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
##### 5.矩形覆盖
<font color=black size=3 face="微软雅黑">&emsp;&emsp;我们可以用`2*1`的小矩形横着或者竖着去覆盖更大的矩形。请问用n个`2*1`的小矩形无重叠地覆盖一个`2*n`的大矩形，总共有多少种方法
<font color=black size=3 face="微软雅黑">&emsp;&emsp;分析后得到：n=1:1种， n=2:2种， n=3：3种，n=4:5种...即又是斐波那契数列的算法
```cpp
class Solution {
public:
	int rectCover(int number) {
        //观察规律：n:1--1  2--2  3--3 4--5
        //递归消耗太大
		if (1 == number)
			return 1;
		else if (2 == number)
			return 2;

		int res = 0;
		int n1 = 1;
		int n2 = 2;

		for (int i = 2; i < number; i++)
		{
			res = n1 + n2;
			n1 = n2;
			n2 = res;
		}

		return res;
	}
};
```
- [矩形覆盖](https://www.nowcoder.com/practice/72a5a919508a4251859fb2cfb987a0e6?tpId=13&tqId=11163&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)


