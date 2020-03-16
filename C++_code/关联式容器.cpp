//STL树形结构的关联式容器

/////////////////////////////////////////////////////////////////////
//1. 键值对的定义
template<class T1, class T2>
class pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair()
		:first(T1())
		, second(T2())
	{}

	pair(const T1& a, const T2& b)
		：first(a)
		, second(b)
	{}

};

/////////////////////////////////////////////////////////////////////
//2. 关联式容器：map

//2.1 map的构造
int main()
{
	map<string, string> m1;

	map<string, string> m2{ {"apple","苹果"},
							{"banan", "香蕉"},
							{"orange", "橘子"},
							{"peach", "桃子" },
							{"waterme", "水蜜桃"} };

	cout << m2["apple"] << endl;
	cout << m2["waterme"] << endl;
	map<string, string> m3(m2);

	system("pause");
	return 0;
}

//2.2 map的容量与元素访问
//operator[]与at()函数，都是通过key找到与key对应的value然后返回其引用，不同的是：当key不存在时，
//operator[]用默认value与key构造键值对然后插入，返回该默认value，at()函数直接抛异常

 /*
 operator[]的原理是：
 用<key, T()>构造一个键值对，然后调用insert()函数将该键值对插入到map中
 如果key已经存在，插入失败，insert函数返回该key所在位置的迭代器
 如果key不存在，插入成功，insert函数返回新插入元素所在位置的迭代器
 operator[]函数最后将insert返回值键值对中的value返回
 */
int main()
{
	map<string, string> m;

	//将<"apple", ""> 插入map中，插入成功，返回value的引用，将“苹果”赋值给该引用结果
	m["apple"] = "苹果";
	// 将<"apple", "">插入map中，插入失败，将<"apple", "苹果">中的"苹果"返回

	cout << m["apple"] << endl;//苹果
	cout << m.size() << endl;//1

	system("pause");
	return 0;
}

//2.3  map中元素的修改
int main()
{
	map<string, string> m;

	//①键值对<"peach","桃子">插入map中，用pair构造键值对
	m.insert(pair<string, string>("peach", "桃子"));

	//②键值对<"banan", "香蕉">插入map中，用make_pair构造键值对
	m.insert(make_pair("banan", "香蕉"));

	//③用operator[]向map中插入元素
	m["apple"] = "苹果";

	//④key不存在时抛异常
	//m.at("waterme") = "水蜜桃"
	m.insert(m.find("waterme"), make_pair("waterme", "水蜜桃"));
	cout << m.size() << endl;//4

	// 用迭代器去遍历map中的元素，可以得到一个按照key排序的序列
	for (auto& e : m)
	{
		cout << e.first << "--->" << e.second << endl;
		cout << endl;
	}

	//map中的键值对key是唯一的，若key存在则将插入失败
	auto ret = m.insert(make_pair("peach", "桃子"));
	if (ret.second)
	{
		cout << "<peach, 桃色>不在map中, 已经插入" << endl;
	}
	else
	{
		cout << "键值为peach的元素已经存在：" << ret.first->first << "--->" <<
			ret.first->second << " 插入失败" << endl;
	}

	//删除key为"apple"的元素
	m.erase("apple");
	for (auto& e : m)
		cout << e.first << "--->" << e.second << endl;

	if (1 == m.count("apple"))
		cout << "apple还在" << endl;
	else
		cout << "apple被吃了" << endl;

	system("pause");
	return 0;
}

//1. map中的的元素是键值对
//2. map中的key是唯一的，并且不能修改
//3. 默认按照小于的方式对key进行比较
//4. map中的元素如果用迭代器去遍历，可以得到一个有序的序列
//5. map的底层为平衡搜索树(红黑树)，查找效率比较高O(log_2 N)
//6. 支持[]操作符，operator[]中实际进行插入查找。

/////////////////////////////////////////////////////////////////////
//3. 关联式容器：multimap
int main()
{
	multimap<string, string> m;

	m.insert(make_pair("李逵", "黑旋风"));
	m.insert(make_pair("林冲", "豹子头"));
	m.insert(make_pair("鲁达", "花和尚"));

	//插入key相同的元素
	m.insert(make_pair("李逵", "铁牛"));
	cout << m.size() << endl;//4

	for (auto& e : m)
		cout << "<" << e.first << "," << e.second << ">" << endl;

	//key为李逵的元素有多少个
	cout << m.count("李逵") << endl;//2

	multimap<int, int> m1;
	for (int i = 0; i < 10; ++i)
		m1.insert(pair<int, int>(i, i));

	auto it = m1.lower_bound(5);
	cout << it->first << "--->" << it->second << endl;//5--->5

	// 返回m中大于5的元素
	it = m1.upper_bound(5);
	cout << it->first << "--->" << it->second << endl;//6--->6


	system("pause");
	return 0;
}

/////////////////////////////////////////////////////////////////////
//4 关联式容器：set
int main()
{
	//用数组中的元素构建set
	int array[] = { 1,3,6,5,3,4,5,7,8,9,4,3,7,0 };
	set<int> s(array, array + sizeof(array) / sizeof(array[0]));
	cout << s.size() << endl;//9

	//正向打印set中的元素，可以看到set可以去重
	for (auto& e : s)
	{
		cout << e << ' ';// 0 1 3 4 5 6 7 8 9
	}
	cout << endl;

	//使用迭代器逆向打印set中的元素
	for (auto it = s.rbegin(); it != s.rend(); ++it)
	{
		cout << *it << ' ';//9 8 7 6 5 4 3 1 0
	}
	cout << endl;

	//set中值为3的元素出现的次数（时间复杂度O(logN)）
	cout << s.count(3) << endl;//1

	system("pause");
	return 0;
}

/////////////////////////////////////////////////////////////////////
//5 关联式容器：multiset
int main()
{
	int array[] = { 2,1,3,4,6,5,4,7,8,9,0,7,6,5 };

	//multiset在底层存储的是<int, int>的键值对
	multiset<int> s(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : s)
	{
		cout << e << ' ';// 0 1 2 3 4 4 5 5 6 6 7 7 8 9
	}
	cout << endl;

	s.insert(5);
	cout << s.count(5) << endl;//3
	for (auto& e : s)
	{
		cout << e << ' ';// 0 1 2 3 4 4 5 5 5 6 6 7 7 8 9
	}
	cout << endl;

	s.erase(5);
	for (auto& e : s)
	{
		cout << e << ' ';// 0 1 2 3 4 4 6 6 7 7 8 9
	}
	cout << endl;


	system("pause");
	return 0;
}