#include <iostream>
using namespace std;

int main()
{
	int i = 1234;
	double d = 56.789;
	const char* str = "String";
	bool b = true;

	// bool�� ��� ���
	cout << b << endl;
	cout << boolalpha << b << endl;

	// ���� ���� ��� �� ��ҹ���
	cout << hex << i << endl;
	cout << showbase << i << endl;
	cout << uppercase << i << endl;

	// + ��� ��ȣ ǥ��
	cout << dec << showpos << i << endl;
}