#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;
#define MAXSIZE 15

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

////////////////////////////////////////////////////////////////////////////
//2.自然底数 e=2.718281828…，e 的计算公式如下：e = 1 + 1 / 1!+ 1 / 2!+ 1 / 3!+ …要求当最后一项的值小于
//10^10 时结束
void Evaluation()
{
	float e = 1.0;
	float n = 1.0;
	int i = 1;

	//循环控制条件
	while (1 / n > 1e-10)
	{
		e += 1 / n;
		i++;
		n = i * n;
	}

	cout << "\n" << "The value of e is: " << e << endl;
}

////////////////////////////////////////////////////////
//3.任意的整数，当从左向右读与从右向左读是相同的，且为素数时，称为回文素数。求 1000 以内的所有回文素数
int IsPrime(int n)
{
	int j = 0;
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
		return 1;

	for (j = 2; j < n; j++)
	{
		if (n % j == 0)
			return 0;
		else if (n != j + 1)
			continue;
		else
			return 1;
	}
}

void PalindromePrimes()
{
	int i = 0;
	for (i = 10; i < 1000; i++)
	{
		//首先判断是否为素数
		if (IsPrime(i) == 1)
		{
			//判断是几位数
			if (i / 100 == 0)
			{
				if (i / 10 == i % 10)
					cout << ' ' << i;
			}
			else
			{
				if (i / 100 == i % 10)
					cout << ' ' << i;
			}
			if (i % 5 == 0)
				cout << endl;
		}
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////
//4,假设一对兔子的成熟期是一个月，即一个月可长成成兔，那么，如果每对成兔每个月都生一对小兔，一对新生的小兔从第二个月
//起就开始生兔子，试问从一对兔子开始繁殖，以后每个月会有多少对兔子
void Rabbit_Num()
{
	int month = 0;
	cout << "Please input Month: ";
	cin >> month;

	int r1 = 1;
	int r2 = 1;
	int r3 = 0;
	if (month == 1 || month == 2)
	{
		cout << "There is 1 Rabbits" << endl;
		return;
	}
	else
	{
		for (int i = 3; i <= month; i++)
		{
			r3 = r1 + r2;
			r1 = r2;
			r2 = r3;
		}
		cout << "There is " << r3 << " Rabbits" << endl;
	}

}

//////////////////////////////////////////////////////////////////
//5.设有一矩阵为 m×n 阶（即 m 行 n 列），第 i 行 j 列的元素是 a(i,j)，需要将该矩阵转置为 n×m 阶的矩阵，
//使其中元素满足 b(j,i)=a(i,j)
void Matrix_Translocation()
{
	int rows = 0;
	int cols = 0;
	vector<vector<int>> matrix;
	int new_matrix[MAXSIZE][MAXSIZE] = { 0 };

	cout << "Please input the number of the rows: ";
	cin >> rows;
	cout << endl << "Please input the number of the cols: ";
	cin >> cols;
	cout << endl;

	matrix.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << "Please input the element: ";
			int da = 0;
			cin >> da;
			matrix[i].push_back(da);
		}
	}

	cout << "The source matrx: " << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("\t%d", matrix[i][j]);
		}
		cout << endl;
	}
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_matrix[j][i] = matrix[i][j];
		}
	}
	
	cout << "The new mawtrx: " << endl;
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			printf("\t%d", new_matrix[i][j]);
		}
		cout << endl;
	}

}

int main()
{

	////1.判断三角形的类型
	//TypesOfJudgment();
	////2.求自然底数e
	//Evaluation();
	////3.回文素数
	//PalindromePrimes();
	////4.兔子生兔子问题
	//Rabbit_Num();
	////5.矩阵转置
	Matrix_Translocation();



	system("pause");
	return 0;
}