#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

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

	cout << "The even of elements is: ";
	for (int i = 0; i < even.size(); i++)
	{
		cout << ' ' << even[i];
	} 
	cout << endl << "The odd of elements is: ";
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
void MatchRanking()
{

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
	MatchRanking();


	system("pause");
	return 0;
}