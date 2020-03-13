//智能指针

///////////////////////////////////////////////////////////
//1.原理：RAII（Resource Acquisition Is Initialization）
template<class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~SmartPtr()
	{
		if (_ptr)
			delete _ptr;
	}

private:
	T* _ptr;
};

void MerageSort(int* a, int n)
{
	int * tmp = (int*)malloc(sizeof(int)*n);
	
	//tmp指针委托给了sp对象
	SmartPtr<int> sp(tmp);

	//处理其他逻辑
	......
}
int main()
{
	try {
		int a[5] = { 4,5,6,7,2 };
		MerageSort(a,5);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

/////////////////////////////////////////////////////////
//2.1智能指针：std::auto_ptr
#include <memory> //C++智能指针都定义在memory中

class Date 
{
public:
	Date() { cout << "Date()" << endl; }
	~Date() { cout << "~Date()" << endl; }

	int _year;
	int _month;
	int _day;
};

int main()
{
	auto_ptr<Date> ap(new Date);
	auto_ptr<Date> copy(ap);

	//使用auto_ptr后，当对象拷贝或赋值后，原有的对象悬空
	//auto_ptr是C+++98中规定的，缺陷很大，因此不建议使用

	ap->_year = 2018;//运行后，报错“引发了异常: 写入访问权限冲突。ap._Myptr 是 nullptr。”
	
	system("pause");
	return 0;
}

//2.2 auto_ptr模拟实现
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}

	//拷贝操作：将ap中资源转移到当前对象，并让ap与其所管理资源断开联系
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap.ptr)
	{
		ap._ptr = nullptr;
	}

	//赋值操作
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		//检查自己给自己赋值
		if (this != &ap)
		{
			//释放当前对象中资源
			if (_ptr)
			{
				delete _ptr;

				//将ap中资源转入当前对象中
				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}

			return *this;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};

int main()
{
	auto_ptr<Date> ap(new Date);

	//拷贝后，ap对象赋空
	auto_ptr<Date> copy(ap);
	ap->_year = 2018;//报错“引发了异常: 写入访问权限冲突。ap._Myptr 是 nullptr。”

	system("pause");
	return 0;
}

//3.1 智能指针：std::unique_ptr
int main()
{
	unique_ptr<Date> ap(new Date);

	//简单粗暴：为了防止出错，就防拷贝
	unique_ptr<Date> copy(ap);//报错是已删除的函数
}

//3.2 unique_ptr模拟实现
template<class T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~UniquePtr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	//C++98防拷贝方式：只声明不实现+声明为私有
	UniquePtr(Uniqueptr<T> const &);
	UniquePtr & operator=(UniquePtr<T> const &);

	//C++11防拷贝方式：delete
	UniquePtr(Uniqueptr<T> const &) = delete;
	UniquePtr & operator=(UniquePtr<T> const &) = delete;

private:
	T* _ptr;
};

//4.1 智能指针： std::shared_ptr
int main()
{
	//shared_ptr通过引用计数来支持指针对象的拷贝
	shared_ptr<Date> sp(new Date);
	shared_ptr<Date> copy(sp);

	cout << "ref count: " << sp.use_count() << endl;//ref count: 2
	cout << "ref count: " << copy.use_count() << endl;//ref count: 2

	system("pause");
	return 0;
}

//4.2 shared_ptr模拟实现
template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		:_ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{
		//如果是一个空指针对象则引用计数赋0
		if (_ptr == nullptr)
			_pRefCount = 0;
	}

	~SharedPtr()
	{
		Release();
	}

	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		//如果是一个空指针对象则不加引用计数，否则加引用计数
		if (_ptr)
			AddRefCount();
	}

	//sp1 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//释放管理的旧资源
			Release();

			//共享管理新对象的资源，并增加引用计数
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			if (_ptr)
				AddRefCount();
		}

		return *this;
	}

	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }

	int UseCount()
	{
		return *_pRefCount;
	}

	T* Get()
	{
		return _ptr;
	}

	int AddRefCount()
	{
		//加锁或使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();

		return *_pRefCount;
	}

	int SubRefCount()
	{
		//加锁或使用减1的原子操作
		_pMutex->lock();
		--(*_pRefCount);
		_pMutex->unlock();

		return *_pRefCount;
	}

private:
	void Release()
	{
		//引用计数减1，若为0，则释放资源
		if (_ptr && SubRefCount() == 0)
		{
			delete _ptr;
			delete _pRefCount;
		}
	}
private:
	int* _pRefCount;//引用计数
	T* _ptr;//指向管理资源的指针
	mutex* _pMutex;//互斥锁
};


int main()
{
	SharedPtr<int> sp1(new int(10));
	SharedPtr<int> sp2(sp1);
	*sp2 = 20;

	cout << sp1.UseCount() << endl;//2
	cout << sp2.UseCount() << endl;//2

	SharedPtr<int> sp3(new int(10));
	sp2 = sp3;
	cout << sp1.UseCount() << endl;//1
	cout << sp2.UseCount() << endl;//2
	cout << sp3.UseCount() << endl;//2

	sp1 = sp3;
	cout << sp1.UseCount() << endl;//2
	cout << sp2.UseCount() << endl;//3
	cout << sp3.UseCount() << endl;//3

	system("pause");
	return 0;
}

//4.3 std::shared_ptr的线程安全问题
void SharePtrFunc(SharedPtr<Date>& sp, size_t n)
{
	cout << sp.Get() << endl;

	//演示引用计数线程安全问题，就把AddRefCount和SubRefCount中的锁去掉
	//演示可能不出现线程安全问题，因为线程安全问题是偶现性问题，main函数的n改大一些概率就变大了，就
	//容易出现了
	for (size_t i = 0; i < n; ++i)
	{
		//智能指针拷贝会++计数，智能指针析构会--计数，这里是线程安全的
		SharedPtr<Date> copy(sp);

		//里智能指针访问管理的资源，不是线程安全的。所以我们看看这些值两个线程++了2n次，但是最
		//终看到的结果，并一定是加了2n
		copy->_year++;
		copy->_month++;
		copy->_day++;
	}
}

int main()
{
	SharedPtr<Date> p(new Date);
	cout << p.Get() << endl;

	const size_t n = 100;
	thread t1(SharePtrFunc, p, n);
	thread t2(SharePtrFunc, p, n);

	t1.join();
	t2.join();

	cout << p->_year << endl;
	cout << p->_month << endl;
	cout << p->_day << endl;

	system("pause");
	return 0;
}

//4.4 std::shared_ptr循环引用
struct ListNode
{
	int _data;
	SharedPtr<ListNode> _prev;
	SharedPtr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

int main()
{
	SharedPtr<ListNode> node1(new ListNode);
	SharedPtr<ListNode> node2(new ListNode);

	cout << node1.UseCount() << endl;//1
	cout << node2.UseCount() << endl;//1

	node1->_next = node2;
	node2->_prev = node1;

	cout << node1.UseCount() << endl;//2
	cout << node2.UseCount() << endl;//2

	system("pause");
	return 0;
}

//1. node1和node2两个智能指针对象指向两个节点，引用计数变成1，我们不需要手动delete。
//2. node1的_next指向node2，node2的_prev指向node1，引用计数变成2。
//3. node1和node2析构，引用计数减到1，但是_next还指向下一个节点。但是_prev还指向上一个节点。
//4. 也就是说_next析构了，node2就释放了。
//5. 也就是说_prev析构了，node1就释放了。
//6. 但是_next属于node的成员，node1释放了，_next才会析构，而node1由_prev管理，_prev属于node2成员，所以这就叫循环引用，谁也不会释放。

// 解决方案：在引用计数的场景下，把节点中的_prev和_next改成weak_ptr就可以了
// 原理就是，node1->_next = node2;和node2->_prev = node1;此时weak_ptr的_next和_prev不会增加node1和node2的引用计数。
struct ListNode
{
	int _data;
	weak_ptr<ListNode> _prev;
	weak_ptr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

int main()
{
	shared_ptr<ListNode> node1(new ListNode);
	shared_ptr<ListNode> node2(new ListNode);

	cout << node1.use_count() << endl;//1
	cout << node2.use_count() << endl;//1

	node1->_next = node2;
	node2->_prev = node1;

	cout << node1.use_count() << endl;//1
	cout << node2.use_count() << endl;//1

	system("pause");
	return 0;
}