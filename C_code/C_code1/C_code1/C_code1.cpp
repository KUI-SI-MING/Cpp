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

	unsigned int max = n1;
	unsigned int min = n2;
	if (n1 < n2)
	{
		max = n2;
		min = n1;
	}
	//穷举法--效率低下
	vector<int> num;
	for (int i = 1;i <= min; i++)//32位下unsigned int 范围0~4294967296
	{
		if ((n1 % i == 0) && (n2 % i == 0))
		{
			num.push_back(i);
		}
	}
	cout << "The GCD Is: " << num[num.size() - 1] << endl;

	//按照从大（两个整数中较小的数）到小（到最小的整数1）的顺序求出第一个能同时整除
	//两个整数的自然数
	for (int i = min; i > 0; i--)
	{
		if ((n1 % i == 0) && (n2 % i == 0))
		{
			cout << "The GCD Is: " << i << endl;
			break;
		}
	}

	//辗转相除法
	int m = max * min;
	int c = max % min;
	while (c != 0)
	{
		max = min;
		min = c;
		c = max % min;
	}
	cout << "The GCD is: " << min << endl;
	cout << "The MCM is： " << m / min << endl;

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
	cout << "The number of 9 is: " << cou << endl;//90
}

////////////////////////////////////////////////////////
//9.打印菱形
void PrintRhombic()
{
	//①分为上下两部分
	int line = 0;//行数 == 列数
	cout << "Please input a Odd: ";
	cin >> line;

	int spacenumber = line / 2;//空格数
	int starnumber = 1;//星号数
	for (int i = 0; i < line; i++)
	{
		//上半部分
		if (i <= line / 2)
		{
			for (int j = 0; j < spacenumber; j++)
			{
				cout << ' ';
			}
			for (int j = 0; j < starnumber; j++)
			{
				cout << '*';
			}
			cout << endl;
			if (i == line / 2)
			{
				continue;
			}
			spacenumber--;
			starnumber += 2;
		}
		else//下半部分
		{
			spacenumber++;
			starnumber -= 2;
			for (int j = 0; j < spacenumber; j++)
			{
				cout << ' ';
			}
			for (int j = 0; j < starnumber; j++)
			{
				cout << '*';
			}
			cout << endl;
		}
	}

	//②按照行列来考虑，判断某一行某一列的元素line==colnmn
	//对于上半部分(包括中间一行)，当前行与当前列满足如下关系输出星号i,j从1开始
	//j>=(column+1)/2-(i + 1)     (column+1)/2-(i + 1)为第i行最左边的星号
	//j<=(column+1)/2+(i + 1)    (column+1)/2+(i + 1)为第i行最右边的星号
	//对于下半部分，当前行与当前列满足如下关系输出星号
	//j>=(column+1)/2-(line-i)     (column+1)/2-(line-i)为第i行最左边的星号
	//j<=(column+1)/2+(line-i)    (column+1)/2+(line-i)为第i行最右边的星号
	int colnmn = line;//列==行
	for (int i = 1; i <= line; i++)
	{
		//上半部分
		if (i <= (line / 2 + 1))
		{
			for (int j = 1; j <= colnmn; j++)
			{
				if (((colnmn + 1) / 2) - (i - 1) <= j && j <= ((colnmn + 1) / 2) + (i - 1))
				{
					cout << '*';
				}
				else
				{
					cout << ' ';
				}
			}
			cout << endl;
		}
		else//下半部分
		{
			for (int j = 1; j <= colnmn; j++)
			{
				if (((colnmn + 1) / 2) - (line - i) <= j && j <= ((colnmn + 1) / 2) + (line - i))
				{
					cout << '*';
				}
				else
				{
					cout << ' ';
				}
			}
			cout << endl;
		}
	}
}

////////////////////////////////////////////////////////
//10.求出100～999之间的所有“水仙花数”并输出
void FindNarcissisticnumber()
{
	int bit = 0;
	int top = 0;
	int hundred = 0;

	cout << "Result Is: ";
	for (int i = 153; i < 1000; i++)
	{
		int sum = 0;
		int n = i;
		bit = n % 10;
		n = n / 10;
		top = n % 10;
		hundred = n / 10;

		sum = pow(bit, 3) + pow(top, 3) + pow(hundred, 3);
		if (sum == i)
		{
			cout << i << ' ';
		}
	}

	cout << endl;
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
	//NineNumber();
	////9.打印菱形
	//PrintRhombic();
	////10.水仙花数
	FindNarcissisticnumber();


	system("pause");
	return 0;
}





