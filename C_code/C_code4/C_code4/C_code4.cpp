#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#define N 100

using namespace std;

/////////////////////////////////////////////////////////
//1.编写一个函数reverse_string(char * string)（递归实现） 实现：将参数字符串中的字符反向排列。
void Reverse_string(char* string)
{
	static char arr[N] = { 0 };//记录字符串
	static char* p = arr;
	static char* q = arr;

	if (*string != '\0')
	{
		*q = *string;
		q++;
		
		Reverse_string(string + 1);
		*string = *p;//翻转
		p++;
	}


}

void ReverseString()
{
	char str[N] = { 0 };

	cout << "Please input a string： ";
	gets_s(str);

	Reverse_string(str);

	cout << "The new str is: " << str << endl;
}

///////////////////////////////////////////////////////////////
//2.递归和非递归分别实现strlen
//递归
int _RMyStrlen(const char* str)
{ 
	if (*str == '\0')
		return 0;

	return 1 + _RMyStrlen(str + 1);

}

//非递归
int _NotRMyStrlen(string& str)
{
	int count = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}

	return count;
}

void MyStrlen()
{
	string str;
	cout << "Please input a string: ";
	getline(cin , str);

	const char* ps = str.data();
	int size = _RMyStrlen(ps);
	cout << "The size of " << str << " is: " << size << endl;

	size = _NotRMyStrlen(str);
	cout << "The size of " << str << " is: " << size << endl;
}

///////////////////////////////////////////////////////
//3.递归和非递归分别实现求n的阶乘
long _RFactorial(int n)
{
	if (n == 1)
		return 1;
	else
		return n * _RFactorial(n - 1);
}

//非递归
long _NotRFactorial(int n)
{
	long  res = 1;
	int tmp = n;
	while (tmp)
	{
		res *= tmp;
		tmp--;
	}

	return res;
}
void Factorial()
{
	int  n = 0;
	cout << "Please input a number: ";
	cin >> n;

	long res = _RFactorial(n);
	cout << "The Factorial of " << n << " is: " << res << endl;

	res = _NotRFactorial(n);
	cout << "The Factorial of " << n << " is: " << res << endl;
}

int main()
{
	////1.字符反向排列
	//ReverseString();
	////2.模拟实现strlen
	//MyStrlen();
	////3.n的阶乘
	Factorial();


	system("pause");
	return 0;
}