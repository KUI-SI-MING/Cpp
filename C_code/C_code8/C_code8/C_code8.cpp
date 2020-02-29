#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////
//1.判断三角形的类型
int main()
{
	float l = 0, w = 0, h = 0;
	float aver = 0, area = 0.0;

	cout << "Please enter the three sides of the triangle: ";
	cin >> l >> w >> h;

	if (l + w > h && l + h >= w && h + w > l)
	{
		aver = (l + w + h) / 2;
		area = (float)sqrt(aver*(aver - l)*(aver - w) * (aver - h));
		cout << "The Area of triangle is: " << area << endl;

		if (l == w && l == h)
			cout << "Is Equilateral triangle" << endl;
		else if (l == w || l == h || w == h)
			cout << "Is Isosceles triangle" << endl;
		else if ((l * l + w * w == h * h) || (l * l + h * h == w * w)
			|| (w * w + h * h == l * l))
			cout << "Is Right triangle" << endl;
		else
			cout << "Is Normal triangle" << endl;
	}
	else
	{
		cout << "Data Error!" << endl;
	}

	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//2.矩阵转置
int main()
{
	int rows = 0, cols = 0;
	cout << "please input the number of rows: ";
	cin >> rows;
	cout << "please input the number of cols: ";
	cin >> cols;
	cout << "please input the element: ";

	vector<vector<int>> Array(rows);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)\
		{
			int in = 0;
			cin >> in;
			Array[i].push_back(in);
		}
	}
	vector<vector<int>> New_Array(cols, vector<int>(rows));

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			New_Array[j][i] = Array[i][j];
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
			cout << New_Array[i][j] << ' ';

		cout << endl;
	}

	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//3.求自然底数e
int main()
{
	float e = 1.0;
	float tmp = 1.0;
	int i = 1;

	while (1 / tmp > 1e-10)
	{
		e += 1 / tmp;
		i++;
		tmp *= i;
	}

	cout << "The value if e is: " << e << endl;
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//4.回文素数
bool IsPrime(int number)
{
	bool isPrime = true;
	int k = (int)sqrt((double)number);

	for (int i = 2; i <= k; i++)
	{
		if (number % i == 0)
		{
			isPrime = false;
			break;
		}
	}

	return isPrime;
}

int main()
{
	int num = 1;

	cout << "The number of prime texts in 1 ~ 1000 is: ";

	for (num = 10; num < 1000; num++)
	{
		if (IsPrime(num))
		{
			if (num / 100 == 0)//判断是否是三位数
			{
				if (num / 10 == num % 10)
				{
					cout << "  " << num;
				}
				if (num % 5 == 0)
					cout << endl;
			}
			else
			{
				if (num / 100 == num % 10)
					cout << "  " << num;
				if (num % 5 == 0)
					cout << endl;
			}
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//5.圆周率π
int main()
{
	float s = 1;
	float pi = 0;
	float i = 1.0;
	float n = 1.0;

	while (fabs(i) >= 1e-6)
	{
		pi += i;
		n += 2;
		s = -s;
		i = s / n;
	}

	pi = 4 * pi;
	cout << "The value of the π is: " << pi << endl;

	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//6.完全数
int main()
{
	int sum = 0;
	int num = 0;

	cout << "Please input a number: ";
	cin >> num;

	cout << "The perfect number is: ";
	for (int i = 2; i <= num; i++)
	{
		sum = 0;
		for (int j = 1; j < i; ++j)
		{
			if (i % j == 0)
				sum += j;
		}
		//for (int j = 1; j <= (i / 2); ++j)
		//{
		//	if (i % j == 0)
		//		sum += j;
		//}

		if (sum == i)
			cout << ' ' << i;
	}

	cout << endl;
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//7.亲密数
int main()
{
	cout << "There are following friendly--numbers pair smaller than 3000: ";

	for (int i = 1; i < 3000; ++i)//该范围内的亲密数
	{
		int val1 = 0;
		for (int j = 1; j <= i / 2; ++j)
		{
			if (i % j == 0)
				val1 += j;
		}//某一数的因子之和

		int val2 = 0;
		for (int j = 1; j <= val1 / 2; ++j)
		{
			if (val1 % j == 0)
				val2 += j;
		}//上步计算出的和的因子之和

		if (val2 == i && i < val1)
			cout << ' ' << i << "--" << val1;
	}

	cout << endl;
	system("pause");
	return 0;
}


///////////////////////////////////////////////////////////
//8.自守数
int main()
{
	long mul = 0;
	long k, a, b;
	cout << "It exists following automorphic nmbers small than 100000: ";

	for (long number = 0; number < 100000; ++number)
	{
		for (mul = number, k = 1; (mul /= 10) > 0; k *= 10);//由number的位数确定截取数字进行乘法时的系数k

		a = k * 10;//截取部分积时的系数
		mul = 0;//积的最后n位
		b = 10;//截取乘数相应位时的系数

		while (k > 0)
		{
			mul = (mul + (number % (k * 10))*(number%b - number % (b / 10))) % a;
			//(部分积 + 截取被乘数的后N位*截取乘数的第M位)，%a再截取部分积
			k /= 10;//k为截取被乘数时的系数
			b *= 10;
		}

		if (number == mul)
			cout << ' ' << mul;
	}

	cout << endl;
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//9.回文数
int main()
{
	vector<int> en(16);
	int count = 0;
	long unsigned old_mul = 0;
	long unsigned new_mul = 0;

	cout << "No.     number     it's square(palindrome)" << endl;

	for (int i = 1; i < 256; ++i)
	{
		int val = 1;//位权值
		old_mul = i * i;
		new_mul = 0;

		int pos = 0;
		for (pos = 0; old_mul != 0; ++pos)//从低到高分解old_mul的每一位到数组中
		{
			en[pos] = old_mul % 10;
			old_mul /= 10;
		}

		for (; pos > 0; --pos)
		{
			new_mul += en[pos - 1] * val;
			val *= 10;
		}

		if (new_mul == i * i)
			printf("%2d%10d%10d\n", ++count, i, new_mul);
	}

	cout << endl;
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////
//10.勾股数
int main()
{
	cout << "  a     b    c       a     b    c       a     b    c       a     b    c" << endl;

	int count = 0;

	for (int a = 1; a <= 100; ++a)
	{
		for (int b = a + 1; b <= 100; ++b)
		{
			int c = (int)sqrt(a*a + b * b);
			if (c*c == a * a + b * b && a + b > c && a + c > b&& b + c > a && c <= 100)
			{
				printf("%4d %4d %4d     ", a, b, c);
				count++;
				if (count % 4 == 0)
				{
					cout << endl;
				}
			}
		}
	}

	system("pause");
	return 0;
}


