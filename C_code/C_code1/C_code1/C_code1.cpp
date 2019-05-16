#include <iostream>
#include <assert.h>
#include <vector>
#define N 5
using namespace::std;

////////////////////////////////////////////////////////
//1.打印素数
void PrintPrime()
{
	int n1 = 0;
	int n2 = 0;

	cout << "Please input two numbers: ";
	cin >> n1 >> n2;

	int flag = 0;
	//①判断n是否是素数，看n能否被从2到n-1中的整数整除
	//当n很大时，效率低下
	for (int i = n1; i <= n2; i++)
	{
		bool IsNoPrime = false;
		int data = i;
		for (int j = 2; j < data; j++)
		{
			if ((data % j) == 0)
			{
				IsNoPrime = true;
				break;
			}
		}
		if (!IsNoPrime)
		{
			cout << data << ' ';
			if (flag++ == 10)
			{
				cout << endl;
				flag = 0;
			}
		}
	}
	cout << endl << endl;
	//②有规律如下：当n能被2~n-1中的任意整数整除，则其因子中必定有一个小于等于√n，必定
	//有一个大于大于等于√n，那么便可缩小计算范围
	flag = 0;
	for (int i = n1; i <= n2; i++)
	{
		bool IsNoPrime = false;
		int data = i;
		int k = (int)sqrt((double)data);//sqrt的参数类型是double

		for (int j = 2; j <= k; j++)
		{
			if ((data % j) == 0)
			{
				IsNoPrime = true;
				break;
			}
		}
		if (!IsNoPrime)
		{
			cout << data << ' ';
			if (flag++ == 10)
			{
				cout << endl;
				flag = 0;
			}
		}
	}
	cout << endl;
}

////////////////////////////////////////////////////////
//2.打印乘法口诀表
void PrintMultiplicationFormulatable()
{
	//右上
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (j < i)
				cout << "       ";
			else
			{
				printf("%d*%d=%2d ", i, j, i * j);
			}
		}
		cout << endl;
	}
	cout << endl << endl;

	//左上
	for (int i = 1; i <= 9; i++)
	{
		for (int j = i; j <= 9; j++)
		{
			printf("%d*%d=%2d ", i, j, i * j);
		}
		cout << endl;
	}
	cout << endl << endl;

	//右下
	for (int i = 1; i <= 9; i++)
	{

		for (int j = 1; j <= 9 - i; j++)
		{
			cout << "       ";
		}

		for (int j = 1; j <= i; j++)
		{
			printf("%d*%d=%2d ", i, j, i * j);
		}
		cout << endl;
	}
	cout << endl << endl;

	//左下
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%d*%d=%2d ", i, j, i * j);
		}
		cout << endl;
	}
	cout << endl << endl;

}

////////////////////////////////////////////////////////
//3.判断闰年
void IsLeapYear()
{
	int year = 0;
	cout << "Please input year:";
	cin >> year;
	assert(year > 0);

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		cout << "Is Leap Year!" << endl;
	}
	else
	{
		cout << "Is Not Leap Year!" << endl;
	}
}

////////////////////////////////////////////////////////
//4.两数交换
void Swap()
{
	int n1 = 0;
	int n2 = 0;

	cout << "Please input two numbers: ";
	cin >> n1 >> n2;

	cout << "n1: " << n1 << " " << "n2: " << n2 << endl;

	//中间变量法
	int tmp = n1;
	n1 = n2;
	n2 = tmp;
	cout << "n1: " << n1 << " " << "n2: " << n2 << endl;

	//加减法--当数字过大时存在局限性
	n1 += n2;
	n2 = n1 - n2;
	n1 = n1 - n2;
	cout << "n1: " << n1 << " " << "n2: " << n2 << endl;

	//异或法
	n1 = n1 ^ n2;
	n2 = n2 ^ n1;
	n1 = n1 ^ n2;
	cout << "n1: " << n1 << " " << "n2: " << n2 << endl;

	//位运算法--当数字过大时存在局限性(2字节存储范围：-32767-32767)
	n1 <<= 16;
	n1 += n2;
	n2 = n1 >> 16;
	n1 = n1 & 0xffff;
	cout << "n1: " << n1 << " " << "n2: " << n2 << endl;
}

////////////////////////////////////////////////////////
//5.最大公约数GCD
void FindGCD()
{
	unsigned int n1 = 0;
	unsigned int n2 = 0;

	cout << "Please input two numbers: ";
	cin >> n1 >> n2;

	////穷举法--效率低下
	//vector<int> num;
	//for (int i = 1;i < 4294967296; i++)//32位下unsigned int 范围0~4294967296
	//{
	//	if ((n1 % i == 0) && (n2 % i == 0))
	//	{
	//		num.push_back(i);
	//	}
	//}
	//cout << num[num.size() - 1] << endl;

	//按照从大（两个整数中较小的数）到小（到最小的整数1）的顺序求出第一个能同时整除
	//两个整数的自然数
	unsigned int max = n1;
	unsigned int min = n2;
	if (n1 < n2)
	{
		max = n2;
		min = n1;
	}

	for (int i = min; i > 0; i--)
	{
		if ((n1 % i == 0) && (n2 % i == 0))
		{
			cout << "The GCD Is: " << i << endl;
			break;
		}
	}

}

////////////////////////////////////////////////////////
//6.数组内容交换
//根据上一题既可以进行处理
//交换函数
void SwapNum(int* pa, int* pb)
{
	*pa ^= *pb;
	*pb ^= *pa;
	*pa ^= *pb;
}

void SwapElements()
{
	vector<int> arr1, arr2;

	cout << "Please Input Arr1 Elements:";
	int num = 0;
	while (cin >> num)
	{
		arr1.push_back(num);
		if (arr1.size() > N - 1)
			break;

		cout << "Please Input Arr1 Elements:";
	}
	cout << endl << endl;

	cout << "Please Input Arr2 Elements:";
	while (cin >> num)
	{
		arr2.push_back(num);
		if (arr2.size() > N - 1)
			break;

		cout << "Please Input Arr2 Elements:";
	}
	cout << endl << endl;

	cout << "The Arr1 Is: ";
	for (int i = 0; i < arr1.size(); i++)
	{
		cout << arr1[i] << ' ';
	}
	cout << endl << endl;
	cout << "The Arr2 Is:";
	for (int i = 0; i < arr2.size(); i++)
	{
		cout << arr2[i] << ' ';
	}
	cout << endl << endl;

	for (int i = 0; i < arr1.size(); i++)
	{
		SwapNum(&arr1[i], &arr2[i]);
	}
	cout << endl << endl;

	cout << "The Arr1 Is: ";
	for (int i = 0; i < arr1.size(); i++)
	{
		cout << arr1[i] << ' ';
	}
	cout << endl << endl;
	cout << "The Arr2 Is: ";
	for (int i = 0; i < arr2.size(); i++)
	{
		cout << arr2[i] << ' ';
	}
	cout << endl << endl;
}

////////////////////////////////////////////////////////
//7.计算1/1-1/2+1/3-1/4+1/5 …… + 1/99 - 1/100 的值
void SumofFraction()
{
	double sum = 0.0;
	for (int i = 1; i <= 100; i++)
	{
		sum += pow(-1, i + 1) / i;
	}

	cout << "The Sum of '1/1-1/2+1/3-1/4+1/5 …… + 1/99 - 1/100' Is: " << sum << endl;
}


////////////////////////////////////////////////////////
//8.1~100 的所有整数中出现多少次数字9
void NineNumber()
{

	int cou = 0;
	int i = 0;
	for (i = 1; i <= 100; i++)
	{
		int tmp = 1;
		int nu = i;
		while (nu > 0)
		{
			tmp = nu % 10;
			if ((tmp / 9) == 1)
				cou++;
			nu = nu / 10;
		}
	}
	cout << "The number of 9 is: " << cou<< endl;//90
}

int main()
{
	////1.打印素数
	//PrintPrime();
	////2.打印乘法口诀表
	//PrintMultiplicationFormulatable();
	////3.判断闰年
	//IsLeapYear();
	////4.两数交换
	//Swap();
	////5.最大公约数GCD
	//FindGCD();
	////6.数组内容交换
	//SwapElements();
	////7.分数求和
	//SumofFraction();
	////8.数九问题
	NineNumber();


	system("pause");
	return 0;
}





