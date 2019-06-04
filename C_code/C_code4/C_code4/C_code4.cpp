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

int main()
{
	////1.字符反向排列
	ReverseString();
	system("pause");
	return 0;
}