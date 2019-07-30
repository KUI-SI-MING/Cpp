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
//1.���������������� n��ͨ���������������Ӧ�߶�Ϊ n �ĵ���������
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
//2.���Ϊ 1��2��3������n �� n ����Χ��һȦ����ѡһ�������� m ��Ϊ��������ֵ��
//�ӵ�һ���˿�ʼ��˳ʱ�뷽������������ m ʱֹͣ������Ϊ m ���˳��С�
//�ӳ����˵�˳ʱ�뷽�����һ���˿�ʼ�ִ� 1 ���±����������ȥ��ֱ�������˶�ȫ������Ϊֹ
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
//3.�Ӽ��������������ŵ�һ�������У�ͨ����������а��������е�������������������õݹ�ķ����������
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
//	��һ�����ӣ������к졢�ס���������ɫ�����ӡ����������ӵ���ɫ��û��˳������Ҫ�����ӽ��з��࣬������ɫ��
//��ɫ����ɫ��˳�����С�ֻ���������Ͻ����ƶ�������һ��ֻ�ܵ����������ӣ������ƶ�����ʹ�����ƶ��Ĵ������٣�
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
//5.����һ����ʾ��ά�ռ������Ľṹ���ͣ�ͨ��������ռ�����������֮��ľ���
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

int main()
{
	////1.�������������
	//Trangle();
	////2.Լɪ��
	//Joseph();
	////3.�����������
	//Integer_Inverse_Order();
	////4.��ɫ������
	//Three_Color_Flag();
	////5.�ռ�����֮��ľ���
	Space_Distance();

	system("pause");
	return 0;
}