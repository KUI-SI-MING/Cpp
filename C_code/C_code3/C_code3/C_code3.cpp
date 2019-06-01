#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;
#define N 3

////////////////////////////////////////////////////
//1,求两个数的平均值
int Plus(int d1, int d2)
{
	while (d2 != 0)
	{
		int orbit = d1 ^ d2;
		d2 = d1 & d2;
		d1 = orbit;
		d2 <<= 1;//进位
	}

	return d1;
}

void AverageValue()
{
	int n1 = 0;
	int n2 = 0;

	cout << "Please input 2 numbers: ";
	cin >> n1 >> n2;

	int ave;
	//①（n1 + n2） / 2
	//右移除 2
	ave = (n1 + n2) >> 1;//本质上和（n1 + n2） / 2并未有区别
	cout << "The average of " << n1 << " and " << n2 << " is " << ave << endl;
	
	//②考虑n1和n2过大溢出问题
	ave = n1 - (n1 - n2) / 2;
	cout << "The average of " << n1 << " and " << n2 << " is " << ave << endl;
	 
	//③利用位运算符进行计算
	//n1即为两数之和
	ave = Plus(((n1 ^ n2) >> 1) , n1 & n2);//(比特位：1 + 0或0 + 1的平均值， 1 + 1的平均值)
	cout << "The average of " << n1 << " and " << n2 << " is " << ave << endl;
}

////////////////////////////////////////////////////
//2.一组数据中只有一个数字出现了一次。其他所有数字都是成对出现的。 
//请找出这个数字
void FindNumsAppearOnce()
{
	int size;
	cout << "Please input the size if the array: ";
	cin >> size;

	vector<int> arr;
	for (int i = 0; i < size; i++)
	{
		int d = 0;
		cout << "Please input the elements if the array: ";
		cin >> d;

		arr.push_back(d);
	}

	int res = arr[0];
	for (int i = 1; i < size; i++)
	{
		res ^= arr[i];
	}
	cout << "The number is: " << res << endl;
}


////////////////////////////////////////////////////
//3.有一个字符数组的内容为:"student a am i",请你将数组的内容改为"i am a student". 
//要求：
//不能使用库函数。只能开辟有限个空间（空间个数和字符串的长度无关）
void RotatingArray()
{
	string str;

	cout << "Please input Character array: ";
	getline(cin, str);

	int start = 0;
	int end = str.size() - 1;

	//整体前后逆置
	while (start < end)
	{
		swap(str[start], str[end]);
		start++;
		end--;
	}

	int wordsize = 0;
	//将每个单词逆置
	for (int i = 0; i <= str.size(); i++)
	{
		if (str[i] != ' ' && str[i] != '\0')//考虑最后一个单词
		{
			wordsize++;
			continue;
		}

		if (wordsize == 1)
		{
			wordsize = 0;
			continue;
		}

		start = i - wordsize;
		end = i - 1;
		while (start < end)
		{
			swap(str[start], str[end]);
			start++;
			end--;
		}
		wordsize = 0;
	}

	cout << "The new Character array is: " << str << endl;

}

////////////////////////////////////////////////////
//4.输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半
//部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变
void reOrderArray()
{
	int size;
	cout << "Please input the size if the array: ";
	cin >> size;

	vector<int> array;
	for (int i = 0; i < size; i++)
	{
		int d = 0;
		cout << "Please input the elements if the array: ";
		cin >> d;

		array.push_back(d);
	}

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

	cout << "The new array is: ";
	for (int i = 0; i < size; i++)
	{
		cout << ' ' << array[i] << ' ';
	}
	cout << endl;

}

////////////////////////////////////////////////////
//5.杨氏矩阵
//在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按
//照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否
//含有该整数
bool _Find(int target, vector<vector<int> >& array)
{
	int rows = array.size();
	int cols = array[0].size();

	if (array.size() > 0)
	{
		int i = 0;
		int j = cols - 1;
		while ((i < rows) && (j >= 0))
		{
			if (array[i][j] == target)
			{
				return true;
			}
			else if (array[i][j] < target)
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

void Find()
{
	vector<vector<int> > array(N, vector<int> (N));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int da = 0;
			cout << "Please input array's elements: ";
			cin >> da;
			array[i][j] = da;
		}
	}

	int target = 0;
	cout << "Please input your find number: ";
	cin >> target;
	cout << endl;

	if (_Find(target, array))
	{
		cout << "Find success!" << endl;
	}
	else
	{
		cout << "Find failed!" << endl;
	}
}

////////////////////////////////////////////////////
//6.实现一个函数，可以左旋字符串中的k个字符。 
//ABCD左旋一个字符得到BCDA
//ABCD左旋两个字符得到CDAB
void LeftRotatingString()
{
	cout << "Please input a String: ";
	string str;
	cin >> str;

	int k = 0;
	cout << "Please input roating number: ";
	cin >> k;

	char tmp = 0;
	while (k--)
	{
		tmp = str[0];
		for (int i = 0; i < str.size() - 1; i++)
		{
			str[i] = str[i + 1];
		}
		str[str.size() - 1] = tmp;
	}

	cout << "The roating string is: " << str << endl;
}

////////////////////////////////////////////////////
//7.判断一个字符串是否为另外一个字符串旋转之后的字符串。 
//例如：给定s1 ＝ AABCD和s2 = BCDAA，返回1，给定s1 = abcd和s2 = ACBD，返回0.
//AABCD左旋一个字符得到ABCDA
//AABCD左旋两个字符得到BCDAA
//AABCD右旋一个字符得到DAABC

void Roating(string& str, int rn)
{
	char tmp = 0;
	while (rn--)
	{
		tmp = str[0];
		for (int i = 0; i < str.size() - 1; i++)
		{
			str[i] = str[i + 1];
		}
		str[str.size() - 1] = tmp;
	}
}

void WhitherRotating()
{
	string str1, str2;
	cout << "Please input a String1: ";
	cin >> str1;

	cout << "Please input a String2: ";
	cin >> str2;

	if (str1 == str2)
	{
		cout << "str1 is equals str2" << endl;
		return;
	}

	for (int i = 1; i < str1.size(); i++)
	{
		Roating(str1, 1);//从0开始左旋 0， 1， 2， ...进行判断，每次在原来的基础上旋转一个
		if (str1 == str2)//右旋一个 == 左旋n - 1个，n为长度
		{
			cout << "After Roating, str1 is equals str2" << endl;
			return;
		}
	}

	cout << "After Roating, str1 is not equals str2" << endl;
}

////////////////////////////////////////////////////////////////
//8.递归和非递归分别实现求第n个斐波那契数
int NotRFibonacci(int n)
{

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
int RFibonacci(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1 || n == 2)
		return 1;

	return RFibonacci(n - 1) + RFibonacci(n - 2);
}

void Fibonacci()
{
	cout << "Please inout a number: ";
	int n;
	cin >> n;

	int res = 0;

	//迭代
	res = NotRFibonacci(n);
	cout << "The Fibonacci of the " << n << "is: " << res << endl;

	//递归
	res = RFibonacci(n);
	cout << "The Fibonacci of the " << n << "is: " << res << endl;
}
int main()
{
	////1.平均值
	//AverageValue();
	////2.数组中只出现一次的数字
	//FindNumsAppearOnce();
	/////3.数组旋转
	//RotatingArray();
	////4.调整数组顺序使奇数位于偶数前面
	//reOrderArray();
	////5.杨氏矩阵
	//Find();
	////6.左旋字符串
	//LeftRotatingString();
	////7.判断字符串异同
	//WhitherRotating();
	////8.斐波那契
	Fibonacci();


	system("pause");
	return 0;
}

