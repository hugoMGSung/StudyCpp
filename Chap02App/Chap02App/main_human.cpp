#include <stdio.h>

class Human {
public:
	char name[12];
	int age;

	void intro() {
		printf("�̸� %s, ���� %d\n", name, age);
	}
};

int main() {
	/*Human h = { "�����", 45 };
	h.intro();*/

	Human arFriend[10] = {
		{"������", 49},
		{"������", 45},
		{"�ڻ�", 30}
	};

	for (int i = 0; i < 10; i++)
	{
		Human* pFriend;
		pFriend = &arFriend[i];
		pFriend->intro();
	}
	

	return 0;
}