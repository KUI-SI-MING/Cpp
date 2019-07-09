#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

/////////////////////////////////////////////////////////////////
//1.据输入的三角形的三条边判断三角形的类型，并输出其面积和类型
void TypesOfJudgment()
{
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	float sum = 0;
	float area = 0;

	cout << "Please input Three sides: ";
	cin >> x1 >> x2 >> x3;

	//判断是否构成三角形
	if ((x1 + x2) > x3 && (x2 + x3) > x1 && (x1 + x3) > x2)
	{
		sum = (x1 + x2 + x3) / 2;
		area = (float)sqrt(sum * (sum - x1) * (sum - x2) * (sum - x3));
		cout << "The area of Triangle is: " << area << endl;
		if (x1 == x2 && x1 == x3)
		{
			cout << "Equilateral triangle!" << endl;
		}
		else if (x1 == x2 || x1 == x3 || x2 == x3)
		{
			cout << "Isosceles triangle!" << endl;
		}
		else if(x1 * x1 + x2 * x2 == x3 * x3 || x3 * x3 + x2 * x2 == x1 * x1 || x1 * x1 + x3 * x3 == x2 * x2)
		{
			cout << "Right triangle!" << endl;
		}
		else
		{
			cout << "Common triangle!" << endl;
		}
	}
	else
	{
		cout << "Is not a triangle!" << endl;
	}
}
int main()
{

	////1.判断三角形的类型
	TypesOfJudgment();

	system("pause");
	return 0;
}