#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#define N 100
#define M 100
#define YEAR 2011

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

///////////////////////////////////////////////////////////
//4.递归方式实现打印一个整数的每一位
void _RDecomposition_Integer(int n)
{
	if (n > 9)
		_RDecomposition_Integer(n / 10);
		
	cout << ' ' << n % 10;

}

void Decomposition_Integer()
{
	int n = 0;
	cout << "Please input a number: ";
	cin >> n;

	cout << "The elements of the number is: ";
	_RDecomposition_Integer(n);
	cout << endl;
}

///////////////////////////////////////////////////////////////
//5.用可变参数，实现函数，求函数参数的平均值
int CalculateAverage(int n, ...)
{
	va_list arg;
	int i = 0;
	int sum = 0;
	__crt_va_start (arg, n);
	for (i = 0; i < n; i++)
	{
		sum += __crt_va_arg(arg, int);
	}
	__crt_va_end(arg);
	return sum / n;
}

void VariableParameters()
{
	int n1 = 0, n2 = 0, n3 = 0;
	cout << "Please input three number: ";
	cin >> n1 >> n2 >> n3;

	int ave1 = CalculateAverage(2, n1, n2);
	int ave2 = CalculateAverage(3, n1, n2, n3);
	cout << "The average of " << n1 << ' ' << n2 << " is: " << ave1 << endl;
	cout << "The average of " << n1 << ' ' << n2 << ' ' << n3 <<  " is: " << ave2 << endl;

}

//////////////////////////////////////////////////////////////////
//6..使用可变参数，实现函数，求函数参数的最大值
int MaxValue(int n, ...)
{
	va_list arg;
	int i = 0;
	int max = 0;
	__crt_va_start(arg, n);
	for (i = 0; i < n; i++)
	{
		int tmp = __crt_va_arg(arg, int);

		if (max < tmp)
			max = tmp;
	}
	__crt_va_end(arg);
	return max;
}
void VariableParameters_Max()
{

	int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0;
	cout << "Please input five number: ";
	cin >> n1 >> n2 >> n3 >> n4 >> n5;

	int max1 = MaxValue(3, n1, n2, n3);
	cout << "The Max of " << n1 << ' ' << n2 << ' ' << n3 <<  " is: " << max1 << endl;

	int max2 = MaxValue(5,n1, n2, n3, n4, n5);
	cout << "The Max of " << n1 << ' ' << n2 << ' ' << n3  << ' ' << n4 \
		<< ' ' << n5 << " is: " << max2 << endl;

}

///////////////////////////////////////////////////////////////
//7.喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给20元，可以喝多少汽水?
void Dynamic_planning()
{
	int money = 0;
	cout << "Please input a number: ";
	cin >> money;

	int sum = money;//总瓶数
	int empty = money;//空瓶数
	while (empty >= 2)
	{
		sum += empty / 2;
		empty = empty / 2 + empty % 2;//当空瓶是奇数瓶时，换过后剩余一个瓶子下次换
	}

	cout << "There is " << sum << " bottles!" << endl;
}

////////////////////////////////////////////////////////////
//8.猴子吃桃问题：猴子第一天摘下若干个桃子，当即吃了一半，还不过瘾，又多吃了一个。第二天
//早上又将第一天剩下的桃子吃掉一半，有多吃了一个。以后每天早上都吃了前一天剩下的一半零一个
//到第 10 天早上想再吃时，发现只剩下一个桃子了。编写程序求猴子第一天摘了多少个桃子
void EatPeach()
{
	int day = 0;
	cout << "Please input days: ";
	cin >> day;

	int i = day - 1;
	int current = 1;
	int front = 0;
	while (i > 0)
	{
		front = (current + 1) * 2;
		current = front;
		i--;
	}

	cout << "The paches number is: " << front << endl;
}

//////////////////////////////////////////////////////
//9.中国古代数学家张丘建在他的《算经》中提出了一个著名的“百钱买百鸡问题”，鸡翁一，
//值钱五，鸡母一，值钱三，鸡雏三，值钱一，百钱买百鸡，问翁、母、雏各几何？
void MoneyChicken()
{
	int cock = 0;
	int hen = 0;
	int chick = 0;
	
	cout << "When spend " << M << " to buy " << N << " chicks:" << endl;
	//穷举法
	for (cock = 0; cock <= 20; cock++)//公鸡：0~20
	{
		for (hen = 0; hen <= 33; hen++)//母鸡：0~33
		{
			for (chick = 3; chick <= 99; chick++)//小鸡：3~99
			{
				if (5 * cock + hen * 3 + chick / 3 == M)//钱数
				{
					if(cock + hen + chick == N)//鸡数
						if (chick % 3 == 0)//判断小鸡数是否为3的倍数
						{
							cout << "Cockerel: " << cock << " Hen: " << hen\
								<< " Chick: " << chick << endl;
						}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////
//10.如果一个渔夫从 2011 年 1 月 1 日开始每三天打一次渔，两天晒一次网，编程实现当输入 
//2011 1 月 1 日以后的任意一天，输出该渔夫是在打渔还是在晒网
bool IsLeap(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	return false;
}
int Days(int year, int month, int day)
{

	int sum = 0;
	int co[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };    
	int le[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };  

	//计算输入月份之前的天数
	if (IsLeap(year))
	{
		for (int i = 0; i < month; i++)
		{
			sum += le[i];
		}
	}
	else
	{
		for (int i = 0; i < month; i++)
		{
			sum += co[i];
		}
	}

	//计算年的天数
	for (int i = YEAR; i < year; i++)
	{
		if (IsLeap(year))
		{
			sum += 366;
		}
		else
		{
			sum += 355;
		}
	}

	//计算输入月的天数
	sum += day;

	return sum;
}

void FishermanProblem()
{
	int year = 0;
	int month = 0;
	int day = 0;
	cout << "Please input year & month & day: ";
	cin >> year >> month >> day;

	int d = 0;
	d = Days(year, month, day);//确定天数
	if ((d % 5) < 4 && (d % 5) > 0)
	{
		cout << "He is Fishing" << endl;
	}
	else
	{
		cout << "He is Sunneting" << endl;
	}
}

int main()
{
	////1.字符反向排列
	//ReverseString();
	////2.模拟实现strlen
	//MyStrlen();
	////3.n的阶乘
	//Factorial();
	////4.分解整数
	//Decomposition_Integer();
	////5.可变参数求平均值
	//VariableParameters();
	////6.可变参数求最大值
	//VariableParameters_Max();
	////7.喝汽水问题
	//Dynamic_planning();
	////8.猴子吃桃
	//EatPeach();
	////9.百钱买白鸡
	//MoneyChicken();
	////10.渔夫打鱼晒网
	FishermanProblem();

	system("pause");
	return 0;
}