#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;
#define N 100

////////////////////////////////////////////////////////////
//1.键盘输入任意整数 n，通过程序运行输出对应高度为 n 的等腰三角形
void Trangle()
{
	int h = 0;
	cout << "Please input the highth of the trangle: ";
	cin >> h;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j <= h - i; j++)
			putchar(' ');

		for (int j = 0; j <= 2 * i; j++)
		{
			putchar('*');
		}

		cout << endl;
	}
}

////////////////////////////////////////////////////
//2.编号为 1，2，3，…，n 的 n 个人围坐一圈，任选一个正整数 m 作为报数上限值，
//从第一个人开始按顺时针方向报数，报数到 m 时停止，报数为 m 的人出列。
//从出列人的顺时针方向的下一个人开始又从 1 重新报数，如此下去，直到所有人都全部出列为止
void _joseph(int a[], int n, int m)
{
	int k = 0;
	int j = 0;

	for (int i = 0; i < n; i++)
	{
		j = 1;
		while (j < m)
		{
			while (a[k] == 0)
				k = (k + 1) % n;
			j++;
			k = (k + 1) % n;
		}

		while (a[k] == 0)
			k = (k + 1) % n;
		cout << a[k] << ' ';
		a[k] = 0;
	}
}

void Joseph()
{
	int da[N] = { 0 };
	int num = 0;
	int count = 0;
	cout << "Please input num & count: ";
	cin >> num >> count;

	for (int i = 0; i < num; i++)
	{
		da[i] = i + 1;
	}

	cout << endl << "The output is " << endl;
	_joseph(da, num, count);
	cout << endl;

}

/////////////////////////////////////////////////////////////////
//3.从键盘输入的整数存放到一个数组中，通过程序的运行按照数组中的逆序输出该整数，利用递归的方法解决问题
void convert(char s[], int n)
{
	int i = 0;
	if ((i = n / 10) != 0)
		convert(s + 1, i);

	*s = n % 10 + '0';
}

void Integer_Inverse_Order()
{
	int num = 0;
	char str[10] = { 0 };
	cout << "Please input a number: ";
	cin >> num;

	convert(str, num);
	cout << "The result is: " << str << endl;
}
int main()
{
	////1.输出等腰三角形
	//Trangle();
	////2.约瑟夫环
	//Joseph();
	////3.整数逆序输出
	Integer_Inverse_Order();

	system("pause");
	return 0;
}