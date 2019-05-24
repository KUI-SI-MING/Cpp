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
int main()
{
	////1.平均值
	AverageValue();

	system("pause");
	return 0;
}