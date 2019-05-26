#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

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
int main()
{
	////1.平均值
	//AverageValue();
	////2.数组中只出现一次的数字
	//FindNumsAppearOnce();
	/////3.数组旋转
	RotatingArray();

	system("pause");
	return 0;
}