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

////////////////////////////////////////////////////////////////////
//6.一只兔子躲进了 10 个环形分布的洞的某一个，狼在第一个洞没有找到兔子，就隔一个洞，到第三个洞去找，
//也没有找到，就隔两个洞，到第六个洞去找，以后每次多隔一个洞 去找兔子……这样下去，结果一直找不到兔子，
//请问：兔子可能躲在哪个洞中
void Chasing_Rabbits()
{
	bool pos[10] = { 0 };
	int hunter = 0;
	//判断狼要去的洞的下标pos(i+1) = pos[i] + 1 + i
	for (int i = 0; i < 100; i++)
	{
		pos[hunter] = true;
		hunter++;
		hunter += i;
		hunter = hunter % 10;
	}

	for (int i = 0; i < 10; i++)
	{
		if (!pos[i])
		{
			cout << "The Rabbit is in " << i + 1 << " Room" << endl;
		}
	}
}

/////////////////////////////////////////////////////////////
//7.张、王、李三家各有三个小孩。一天，三家的九个孩子在一起比赛短跑，规定不分年龄大小，跑第一得 9 分，跑第二得 8 分，
//依次类推。比赛结果显示各家的总分相同，且这些孩子没有同时到达终点的，也没有一家的两个或三个孩子获得相连的名次。
//已知获第一名的是李家的孩子，获第二名的是王家的孩子。获得最后一名的是谁家的孩子？
int score[4][4];
void The_Slowest_Clr()
{
	int resu = 0;

	score[1][1] = 7;//张家孩子名次最高：7
	score[2][1] = 8;//王家孩子名次最高：8
	score[3][1] = 9;//李家孩子名次最高：9

	//确定每家孩子的名次
	for (int i = 4; i < 6; i++)
	{
		for (int j = 4; j < 7; j++)
		{
			for (int k = 4; i != j && k < 7; k++)
			{
				if (k != i && k != j && 15 - i - score[1][1] != 15 - j - score[2][1]
					&& 15 - i - score[1][1] != 15 - k - score[3][1]
					&& 15 - j - score[2][1] != 15 - k - score[3][1])
				{
					score[1][2] = i; score[1][3] = 15 - i - 7;
					score[2][2] = j; score[2][3] = 15 - j - 8;
					score[3][2] = k; score[3][3] = 15 - k - 9;
				}

			}
		}
	}
	
	//找到最后一名
	for (int i = 1; i <= 3; i++, cout << endl)
	{
		for (int j = 1; j <= 3; j++)
		{
			cout << score[i][j];
			if (score[i][j] == 1)
			{
				resu = i;
			}
		}
	}

	if (resu == 1)
	{
		cout << "Is Mr.zhang" << endl;
	}
	else if (resu == 2)
	{
		cout << "Is Mr.wang" << endl;
	}
	else
	{
		cout << "Is Mr.li" << endl;
	}
}

///////////////////////////////////////////////////////////
//8.要求使用二维数组将一个 3×4 的矩阵中所有元素的最大值及其下标获取，通过该程序，掌握二维数组的引用知识
void Max_Val_Pos()
{
	vector<vector<int> > matrix(3);
	int da = 0;

	cout << "Please input " << 12 << " number: ";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scanf_s("%d", &da);
			matrix[i].push_back(da);
		}
	}

	int max = matrix[0][0];
	int pos_i = 0;
	int pos_j = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (matrix[i][j] > max)
			{
				swap(matrix[i][j], max);
				pos_i = i;
				pos_j = j;
			}
		}
	}

	cout << "The max value is: " << max << " and the pos is: [" << pos_i << ' ' << pos_j << "] " << endl;
}
////////////////////////////////////////////////////////////
//8.在实际生活中经常会遇到一个问题：写英语作文时，常常要求满足一定的字数。在以往，要么我们一个一个地数；
//要么我们估算一行的单词数，然后用行数进行估算
void Word_Count()
{
	cout << "Please input a string: ";
	char ch;
	int word = 0;
	int count = 0;

	while ((ch = getchar()) != '\n')
	{
		if (ch == ' ')
		{
			word = 0;
		}
		else if (word == 0)
		{
			word = 1;
			count++;
		}
	}
	cout << "There is " << count << " words" << endl;
}

/////////////////////////////////////////////////////////////////////////
//10.设计一个加密和解密算法。在对一个指定的字符串加密之后，利用解密函数能够对密文解密，显示明文信息。
//加密的方式是将字符串中每个字符加上它在字符串中的位置和一个偏移值 5。以字符串“mrsoft”为例，
//第一个字符“m”在字符串中的位置为 0，那么它对应的密文是“'m'+0+5"，即 r
void String_Encryption_Decrypt()
{
	int flag = 1;
	string Plaintext;//明文
	string Ciphertext;//密文

	while (1)
	{

		cout << "[ Entry 1 : Encryption ] [ Entry 2 : Decrypt ] [ Entry 3 : Quit ]" << endl;
		cout << "Please input Command: ";
		cin >> flag;

		if (flag == 1)
		{
			Plaintext.clear();//清除数据
			Ciphertext.clear();

			cout << "Please input a Plaintext: ";
			getline(cin, Plaintext);//读入flag后，接着执行的回车换行符还在输入流中，所以getline碰到它后就结束了
			getline(cin, Plaintext);//解决方法

			for (int i = 0; i < Plaintext.size(); i++)
			{
				Ciphertext += Plaintext[i] + i + 5;
			}
			cout << "After Encryption, The Ciphertext is: " << Ciphertext << endl;
		}
		else if (flag == 2)
		{
			for (int i = 0; i < Plaintext.size(); i++)
			{
				Plaintext[i] = Ciphertext[i] - i - 5;
			}
			cout << "After Decrypt, The Plaintext is: " << Plaintext << endl;
		}
		else if (flag == 3)
		{
			break;
		}
		else
		{
			cout << "Input Error!" << endl;
		}
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
	//Matrix_Translocation();
	////6.狼追兔子问题
	//Chasing_Rabbits();
	////7.谁家孩子跑得最慢
	//The_Slowest_Clr();
	////8.矩阵最大值及其下标
	//Max_Val_Pos();
	////9.统计单词个数，单词个数算法
	//Word_Count();
	////10.字符串加密和解密算法
	String_Encryption_Decrypt();



	system("pause");
	return 0;
}

