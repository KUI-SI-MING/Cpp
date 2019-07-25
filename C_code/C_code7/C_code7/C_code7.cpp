#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

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
int main()
{
	////1.输出等腰三角形
	Trangle();
	system("pause");
	return 0;
}