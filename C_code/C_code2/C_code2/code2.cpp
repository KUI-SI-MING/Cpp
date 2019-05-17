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
int main()
{

	////1.前n项之和
	//Sum();
	////2.验证花括号
	TestCurlyBraces();


	system("pause");
	return 0;
}