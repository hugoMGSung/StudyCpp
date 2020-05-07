#include <vector>
#include <algorithm>
#include <functional>
#include <cstdarg>
#include <thread>
#include <iostream>
using namespace std;

template<typename Func>
void Test(Func func, int n) {
	func(n);
}

//function<void()> func5() {
//	string str("lambda");
//	return [=] { std::cout << "Hello " << str << endl; };
//}

void func6() {
	return;
}

class Foo {
public:
	int i;
	Foo() : i(0) { ; }
	void amaze() {
		[=]{ i = 8; }();
	}
};

//void PrintNum(int args, ...) {
//	va_list ap;
//
//	va_start(ap, args);
//	for (int i = 0; i < args; i++)
//	{
//		int n = va_arg(ap, int);
//		cout << "args : " << args << ":" << n << endl;
// 	}
//	va_end(ap);
//}

int main() {
	/*PrintNum(1, 1);
	PrintNum(2, 2);
	PrintNum(3, 3, 3);
	PrintNum(4, 4, 4, 4);*/

	auto Sum = [](auto a, auto b) { return a + b; };
	cout << Sum(3, 4) << endl;
	cout << Sum(3.14, 2.77) << endl;

	cout << "-----------------------" << endl;
	cout << endl;
	Foo foo;
	foo.amaze();
	cout << foo.i << endl;

	int num1 = 0;

	auto func = [=](int n) { 
		//num1 = 100;
		// num1 = 100;
		cout << "Hello World! " << num1 << ", " << n << endl; 
	};

	cout << num1 << endl;
	func(10);
	func(20);

	Test(func, 30);

	// ¸®ÅÏ°ª
	auto func1 = [] { return 3.141592f; };
	auto func2 = [](float f) { return f; };
	auto func3 = []() -> float { return 3.141592f; };

	float f1 = func1(); cout << f1 << endl;
	float f2 = func2(3.141592f); cout << f2 << endl;
	float f3 = func3(); cout << f3 << endl;

	vector<int> v1;
	v1.push_back(10);
	v1.emplace_back(20);
	v1.emplace_back(30);
	v1.emplace_back(40);
	v1.emplace_back(50);

	for_each(v1.begin(), v1.end(), [](int n) { cout << n << endl; });

	int x = 100;
	int y = 200;
	[x, y]() mutable { cout << x << y << endl; x = 400; y = 500; }();

	cout << x << y << endl;

	thread Thread1([]() {
		for (int i = 0; i < 5; i++)
		{
			cout << "Hello Thread " << endl;
		}
		});

	Thread1.join();

	return 0;
}