##### 1.整数中1出现的次数（从1到n整数中1出现的次数）
<font color=black size=3 face="微软雅黑">&emsp;&emsp;求出1`~`13的整数中1出现的次数,并算出100`~`1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。
> <font color = black size = 3 face  = "微软雅黑">题中要求的是范围内整数中1出现的次数，就针对每个整数进行%10取余，/10减位，数出1个数，输入数字n，n有O(logn)位，整体的时间复杂度就是O(nlogn)。
```cpp
class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int count = 0;
        int tmp = 0;
 
        for (int i = 1; i <= n; i++)
        {
            tmp = i;
            while (tmp != 0)
            {
                if (tmp % 10 == 1)
                    count++;
 
                tmp /= 10;
            }
        }
 
        return count;
    }
};
```
> <font color = black size = 3 face  = "微软雅黑">&emsp;当输入的n非常大的时候，从数字规律入手来提高时间效率。假定范围为1~21345,将其分为两部分：1到1345；1346到21345.<br>
> <font color = black size = 3 face  = "微软雅黑">&emsp;先考虑1346到21345中1的出现次数，又可以分为两种情况：1出现在最高位的情况，从1346到21345的数字中，1出现在10000~19999这10000个数字的万位中，一共出现了10000（10^4^）个<br>
> <font color = black size = 3 face  = "微软雅黑">&emsp;不是所有的5位数在万位出现的次数都是10000个，如输入12345,1在10000到112345中出现的次数为2346次，即除去最高位数字之后，剩下的数字再加上1。<br>
> <font color = black size = 3 face  = "微软雅黑">&emsp;然后就是当1出现在除最高位之外的其他四位数中的情况，如1346到21345的最高位是2，可以将1346到21345再分为两段，1346到11345和11346到21345，每一段剩下的4位数中，选择其中一位是1，其余三位可以在0到9这10个数字中任意选择，因此根据排列组合员原则，总共出现的次数就是2`*`10^3^=2000次<br>
> <font color = black size = 3 face  = "微软雅黑">&emsp;从1到1345中的1出现的次数就可以用递归求解，之前将21345的最高位去掉变为1345即使为了便于采用递归的思路<br>
```cpp
class Solution {
public:
	int PowerBase10(unsigned int n)
	{
		int res = 1;
		for (unsigned int i = 0;i <n;++i)
		{
			res *= 10;
		}

		return res;
	}

	int NumberOf1(const char* str)
	{
		if (!str || *str < '0' || *str > '9' || *str == '\0')
			return 0; 

		int first = *str - '0';
		unsigned int length = static_cast<unsigned int>(strlen(str));

		if (length == 1 && first == 0)
		{
			return 0;
		}

		if (length == 1 && first > 0)
		{
			return 1;
		}

		//若str为"21345"
		//numFirstDigit是数字10000~19999的第一个位中的数目
		int numFirstDigit = 0;
		if (first > 1)
			numFirstDigit = PowerBase10(length - 1);
		else if (first == 1)
			numFirstDigit = atoi(str + 1) +1;

		//numOtherDigits是1346~21345除了第一位之外的数位中的数目
		int numOtherDigits = first * (length - 1)*PowerBase10(length - 2);
		//numRecursive是1~1345中的数目
		int numRecursive = NumberOf1(str + 1); 

		return numFirstDigit + numOtherDigits + numRecursive;
	}

	int NumberOf1Between1AndN_Solution(int n)
	{
		if (n <= 0)
			return 0;

		char strN[50];
		sprintf(strN, "%d",n);
		return NumberOf1(strN);
	}
};
```
- [整数中1出现的次数（从1到n整数中1出现的次数）](https://www.nowcoder.com/practice/bd7f978302044eee894445e244c7eee6?tpId=13&tqId=11184&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)
##### 2.把数组排成最小的数
<font color=black size=3 face="微软雅黑">&emsp;&emsp;输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323
> <font color = black size = 3 face  = "微软雅黑">要求求出所有的数字中的最小的一个，先求出这个数组中的数组中的所有的数字的全排列，然后将每个排列拼起来，最后求拼起来的数字的最小值。n个数字一共有n!个排列，比较繁杂。<br>
>  <font color = black size = 3 face  = "微软雅黑">还可以根据某个排序规则对数组进行排序，在排序规则中，比较的不仅仅是数字m和n的大小，还需要比较两个数字的组合中那个应该排在前面。数字m和n可以组成mn和nm，若mn`<`nm,则打印出mn，否则打印出nm，若nm==mn则n等于m,这种“<"，“>”，“=”,并非常规意义上的数值大小的关系，而是自定义的对比关系。由于给定数字大小为定，为了解决大数问题，可以使用将数字转换成字符串按照字符串的比较规则进行比较。<br>
```cpp
class Solution {
public:
    static bool Compare(int d1, int d2)
    {
        string str1;
        string str2;
 
        str1 += to_string(d1) + to_string(d2);
        str2 += to_string(d2) + to_string(d1);
 
        return str1 < str2;
    }
    string PrintMinNumber(vector<int> numbers) {
        string res;
        if (numbers.size() < 0)
            return res;
 
        sort(numbers.begin(), numbers.end(), Compare);
        for (int i = 0; i < numbers.size(); i++)
        {
            res += to_string(numbers[i]);  
        }
 
        return res;
    }
};
```
##### 3.丑数
<font color=black size=3 face="微软雅黑">&emsp;&emsp;把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
> <font color = black size = 3 face  = "微软雅黑">丑数：整数的因子只有2,3,5.那么就可以通过两种方式来求得值。①逐个判断每个整数是不是丑数，即若整数能被2整除，则将其连续除2，若能被3整除，则将其连续除以3，若能被5整除，则连续除以5，若最后得到是1，则就是丑数。这样的计算方法很繁杂，很多不是丑数的整数任然要进行求余和除法操作，时间效率低下。
```cpp
class Solution {
public:
  bool IsUgly(int number)
  {
      while (number % 2 == 0)
          number /= 2;

      while (number % 3 == 0)
          number /= 3;

      while (number % 5 == 0)
          number /= 5;

      return (number == 1) ? true : false;
  }

  int GetUglyNumber_Solution(int index) {

      if (index <= 0)
          return 0;

      int count = 0;
      int res = 0;

      while (count < index)
      {
          res++;

          if (IsUgly(res))
              count++;
      }

      return res;
  }
};
```
> <font color = black size = 3 face  = "微软雅黑">若是利用已知的丑数对剩下的丑数进行推断，则可以利用空间换取时间的办法来提高时间效率。根据丑数的定义，丑数是另一个丑数乘以2,3,5的结果（除过1），所以创建辅助数组来保存排好序的数组。<br>
> <font color = black size = 3 face  = "微软雅黑">需要做的就是确保数组中的丑数是排好序的，首相就是将1~7这7个丑数存入数组，然后创建三个辅助变量使之指向2,3,5。然后进入循环，找到这三个辅助变量的分别乘以2,3,5之后的最小值，并找到最小的值对应的元素的位置加1，来计算其他位置上的丑数，这样得到的丑数就是有序的。
```cpp
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
 
        // 特殊输入
        if(index<7) return index;
 
        // 辅助容器
        vector<int> res(index);
        for(int i = 0;i<6;i++)
            res[i] = i+1;
 
        // 辅助变量
        int t2=3;
        int t3=2;
        int t5=1;
 
        // 按序计算丑数
        for(int i =6;i<index;i++)
        {
            res[i] = min(res[t2]*2,min(res[t3]*3,res[t5]*5));
 
            if(res[i] == res[t2] * 2 ) t2++;
            if(res[i] == res[t3] * 3 ) t3++;
            if(res[i] == res[t5] * 5 ) t5++;
        }
        return res[index-1];
    }
};
```
- [丑数](https://www.nowcoder.com/practice/6aa9e04fc3794f68acf8778237ba065b?tpId=13&tqId=11186&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)