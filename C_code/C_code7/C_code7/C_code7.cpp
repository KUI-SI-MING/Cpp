#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;
#define N 100
#define BLUE 'B'
#define WHITE 'W'
#define RED 'R'
#define swap(x, y){ char temp;\
	temp = color[x];\
	color[x] = color[y]; \
	color[y] = temp; }

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

////////////////////////////////////////////////////////////////////////
//	有一根绳子，上面有红、白、蓝三种颜色的旗子。绳子上旗子的颜色并没有顺序，现在要对旗子进行分类，按照蓝色、
//白色、红色的顺序排列。只能在绳子上进行移动，并且一次只能调换两面旗子，怎样移动才能使旗子移动的次数最少？
void Three_Color_Flag()
{
	char color[] = { 'R', 'W', 'B', 'W', 'W', 'B', 'R', 'B', 'W', 'R', '\0' };
	int w = 0;
	int b = 0;
	int r = strlen(color) - 1;

	for (int i = 0; i < strlen(color) - 1; i++)
	{
		cout << color[i] << ' ';
	}
	cout << endl;

	while (w <= r)
	{
		if (color[w] == WHITE)
		{
			w++;
		}
		else
		{
			if (color[w] == BLUE)
			{
				swap(b, w);
				b++;
				w++;
			}
			else
			{
				while (w < r && color[r] == RED)
				{
					r--;
				}
				swap(r, w);
				r--;
			}
		}
	}

	for (int i = 0; i < strlen(color) - 1; i++)
	{
		cout << color[i] << ' ';
	}
	cout << endl;
}

///////////////////////////////////////////////////////////
//5.定义一个表示三维空间点坐标的结构类型，通过函数求空间上任意两点之间的距离
struct Point
{
	float x = 0;
	float y = 0;
	float z = 0;
};

float Dist(const struct Point p1, const struct Point p2)
{
	float s1, s2, s3;
	float res = 0;

	s1 = fabs(p1.x - p2.x);
	s2 = fabs(p1.y - p2.y);
	s3 = fabs(p1.z - p2.z);

	res = sqrt(s1*s1 + s2*s2 + s3*s3);
	return res;
}
void Space_Distance()
{
	struct Point p1, p2;
	
	cout << "Enter Point1: ";
	cin >> p1.x >> p1.y >> p1.z;
	cout << endl;
	cout << "Enter Point2: ";
	cin >> p2.x >> p2.y >> p2.z;
	cout << endl;

	cout << "The distence is: " << Dist(p1, p2) << endl;
}

//////////////////////////////////////////////////
//6.求某一范围内完数的个数。
//如果一个数等于它的因子之和，则称该数为“完数”（或“完全数”)。例如，6的因子为1、2、3，而 6 = 1 + 2 + 3，
//因此6是“完数”。
void Finished()
{
	int n = 0;
	cout << "Please input Ceiling number: ";
	cin >> n;

	for (int i = 2; i <= n; i++)
	{
		int sum = 0;
		for (int j = 1; j < i; j++)
		{
			if (i%j == 0)
			{
				sum += j;
			}
		}

		if (sum == i)
			cout << sum << ' ';
	}

	cout << endl;
}
int main()
{
	////1.输出等腰三角形
	//Trangle();
	////2.约瑟夫环
	//Joseph();
	////3.整数逆序输出
	//Integer_Inverse_Order();
	////4.三色旗问题
	//Three_Color_Flag();
	////5.空间两点之间的距离
	//Space_Distance();
	////6.完数
	Finished();

	system("pause");
	return 0;
}