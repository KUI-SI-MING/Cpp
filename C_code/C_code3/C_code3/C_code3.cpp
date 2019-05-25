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

int main()
{
	////1.平均值
	//AverageValue();
	////2.数组中只出现一次的数字
	FindNumsAppearOnce();

	system("pause");
	return 0;
}