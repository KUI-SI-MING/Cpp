#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

#define N 15
using namespace::std;

////////////////////////////////////////////////////////
//1.求Sn=a+aa+aaa+aaaa+aaaaa的前5项之和，其中a是一个数字，例如：2+22+222+2222+22222 
void Sum()
{
	int num = 0;//数字
	int count = 0;//项数
	cout << "Please input number of items : ";
	cin >> num >> count;

	int sum = 0;
	int n = num;
	for (int i = 0; i < count; i++)
	{
		sum += n;
		n = n * 10 + 2;
	}

	cout << "The resaults is: " << sum << endl;
}

////////////////////////////////////////////////////////
//2.从标准输入读取C源代码，并验证所有的花括号都正确的成对出现
void TestCurlyBraces()
{
	cout << "Please input CurlyBraces: ";
	string bra;
	getline(cin, bra);

	int leftbraces = 0;//左括号数目
	int rightbraces = 0;//右括号数
	for (int i = 0; i < bra.size(); i++)
	{
		if (bra[i] == '{')
		{
			leftbraces++;
		}
		else
		{
			rightbraces++;
		}
	}
	if (leftbraces != rightbraces)
	{
		cout << "Is not Into pairs" << endl;
	}
	else
	{
		//当左右括号数相同时，考虑括号顺序如：{}{},}}{{
		for (int i = 0; i < leftbraces; i++)
		{
			if (bra[i] != '{')
			{
				cout << "Is not Into pairs" << endl;
				return;
			}
		}
		cout << "Is Into pairs" << endl;
	}

}

////////////////////////////////////////////////////////
//3.写一个函数返回参数二进制中 1 的个数
void Count_One_Bit()
{
	//①取位判断
	unsigned int num = 0;
	int cou = 0;

	cout << "Please inout a number: ";
	cin >> num;

	//存储时超过4294967295的数自动变为4294967295,负数存为无符号数时值属性已变如-1会变为4294967295
	if ( (int)num < 0 || (int)num > 4294967295)
	{
		cout << "Exceeding range!" << endl;
		return;
	}

	for (int i = 0; i < 32; i++)
	{
		if ((num >> i) & 1 == 1)
		{
			cou++;
		}
	}

	cout << "The number if the '1' is: " << cou << endl << endl;
	//②num & (num - 1)计数
	cou = 0;
	unsigned int tmp = num;
	while (tmp)
	{
		cou++;
		tmp &= (tmp - 1);///每运行一次，value二进制低位的1就减少一个直到value=0
	}
	cout << "The number if the '1' is: " << cou << endl;
}

////////////////////////////////////////////////////////
//4.获取一个数二进制序列中所有的偶数位和奇数位，分别输出二进制序列
void Determine_OE()
{
	int num = 0;

	cout << "Please inout a number: ";
	cin >> num;
	vector<int> odd, even;

	if(num < (int)-2147483648 || num > (int)2147483647)
	{
		cout << "Exceeding ranger!" << endl;
		return;
	}

	int pos = 0;
	for (int i = 0; i < 32; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			even.push_back(((num >> i) & 1));
		}
		else
		{
			odd.push_back(((num >> i) & 1));
		}
	}

	cout << "The even bit of elements is: ";
	for (int i = 0; i < even.size(); i++)
	{
		cout << ' ' << even[i];
	} 
	cout << endl << "The odd bit of elements is: ";
	for (int i = 0; i < odd.size(); i++)
	{
		cout << ' ' << odd[i];
	}

	cout << endl;
}

////////////////////////////////////////////////////////
//5.两个int（32位）整数m和n的二进制表达中，有多少个位(bit)不同
void DifferentBit()
{
	int n1 = 0, n2 = 0;
	cout << "please input two number: ";
	cin >> n1 >> n2;

	if (n1 < (int)-2147483648 || n1 >(int)2147483647 || n2 < (int)-2147483648 || n2 >(int)2147483647)
	{
		cout << "Exceeding ranger!" << endl;
		return;
	}

	int cou = 0;
	for (int i = 0; i < 32; i++)
	{
		if (((n1 >> i) & 1) != ((n2 >> i) & 1))
			cou++;
	}

	cout << "The different bit count is: " << cou << endl;
}

////////////////////////////////////////////////////////
//6.跳水比赛
//5位运动员参加了10米台跳水比赛，有人让他们预测比赛结果
//A选手说：B第二，我第三；
//B选手说：我第二，E第四；
//C选手说：我第一，D第二；
//D选手说：C最后，我第三；
//E选手说：我第四，A第一；
//比赛结束后，每位选手都说对了一半，请编程确定比赛的名次
int Forecast(int arr[])//判断预测结果
{
	if ((arr[1] == 2) + (arr[0] == 3) == 1
		&& (arr[1] == 2) + (arr[4] == 4) == 1
		&& (arr[2] == 1) + (arr[3] == 2) == 1
		&& (arr[2] == 5) + (arr[3] == 3) == 1
		&& (arr[4] == 4) + (arr[0] == 1) == 1)
		return 1;
	else
		return 0;
}
int Repetition(int arr[])//判断名次是否重复
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 5; i++)
		for (j = i + 1; j < 5; j++)
		{
			if (arr[i] == arr[j])
				return 0;
		}
	return 1;
}
void MatchRanking()
{
	int arr[5] = { 0 };
	//数组arr[0]~arr[4]分别代表A B C D E  
	//arr[i]的值表示其名次 
	//暴力穷举找到唯一情况
	for (arr[0] = 1; arr[0] <= 5; arr[0]++)
	{
		for (arr[1] = 1; arr[1] <= 5; arr[1]++)
		{
			for (arr[2] = 1; arr[2] <= 5; arr[2]++)
			{
				for (arr[3] = 1; arr[3] <= 5; arr[3]++)
				{
					for (arr[4] = 1; arr[4] <= 5; arr[4]++)
					{
						if (Forecast(arr) == 1)
							if (Repetition(arr) != 0)
							{
								cout << "A:为第 " << arr[0] << "名" << endl;
								cout << "B:为第 " << arr[1] << "名" << endl;
								cout << "C:为第 " << arr[2] << "名" << endl;
								cout << "D:为第 " << arr[3] << "名" << endl;
								cout << "E:为第 " << arr[4] << "名" << endl;
							}
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////
//7.日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个嫌疑犯
//的一个。以下为4个嫌疑犯的供词。
//A说：不是我。
//B说：是C。
//C说：是D。
//D说：C在胡说
//已知3个人说了真话，1个人说的是假话
void FindKiller()
{
	char killer = '0';
	for (killer = 'A'; killer <= 'D'; killer++)
	{
		//三个真命题 一个假命题
		if (((killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D')) == 3)
		{
			cout << "The killer is: " << killer << endl;
		}
	}
}

////////////////////////////////////////////////////////
//8.打印杨辉三角
void PrintYangHuiTriangle()
{
	int i, j, n = 0, box[N][N];
	cout << "Please input rows number: ";
	while (0 >= n || n > N)
		cin >> n;

	//两边的数
	for (i = 0;i < n;i++)
	{
		box[i][0] = box[i][i] = 1;
	}

	for (i = 2; i < n; i++)
	{
		for (j = 1; j < i; j++)
		{
			box[i][j] = box[i - 1][j - 1] + box[i - 1][j];//除两边的数外都等于上两顶数之和
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
			cout << "   ";
		for (j = 0; j <= i; j++)
			printf("%6d", box[i][j]);

		cout << endl;
	}

	cout << endl;

}

////////////////////////////////////////////////////////
//9.用分治法求最大值
int FindMax(const vector<int> a, int left, int right)
{
	int fm = 0;//第一部分最大值
	int sm = 0;//第二部分最大值

	if (left == right)
		return a[left];

	int mid = (left + right) / 2;
	fm = FindMax(a, left, mid);
	sm = FindMax(a, mid + 1, right);

	return fm > sm ? fm : sm;

}
void MaxValue()
{
	int size = 0;
	cout << "Please input arr elements counts: ";
	cin >> size;

	cout << "Please input arr elements: ";
	vector<int> arr;
	for (int i = 0; i < size; i++)
	{
		int data = 0;
		cin >> data;
		arr.push_back(data);
	}

	int max = FindMax(arr, 0, size - 1);
	cout << "The max value is: " << max << endl;
}

////////////////////////////////////////////////////////
//10.逆置比特位
//在32位机器上25这个值包含下列各位：
//00000000000000000000000000011001
//翻转后：（2550136832）
//10011000000000000000000000000000
//程序结果返回：
//2550136832
void ReverseBit()
{
	unsigned int n = 0;
	cout << "Please input a number: ";
	while (n <= 0 || n > 4294967295)
		cin >> n;

	unsigned int res = 0;
	//取出最低位，左移到相对应的位置
	for (int i = 0; i < 32; i++)
	{
		res += ((n >> i) & 1) << (31 - i);
	}

	cout << "The val is: " << res << endl;
}
int main()
{

	////1.前n项之和
	//Sum();
	////2.验证花括号
	//TestCurlyBraces();
	////3.1的个数
	//Count_One_Bit();
	////4.奇偶判断
	//Determine_OE();
	////5.不同比特位
	//DifferentBit();
	////6.跳水比赛
	//MatchRanking();
	////7.杀人凶手
	//FindKiller();
	////8.杨辉三角
	//PrintYangHuiTriangle();
	////9.数组最大值
	//MaxValue();
	////10.逆置比特位
	ReverseBit();



	system("pause");
	return 0;
}