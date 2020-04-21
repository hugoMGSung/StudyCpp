#include <stdio.h>

class Human {
public:
	char name[12];
	int age;

	void intro() {
		printf("이름 %s, 나이 %d\n", name, age);
	}
};

int main() {
	/*Human h = { "성명건", 45 };
	h.intro();*/

	Human arFriend[10] = {
		{"문동욱", 49},
		{"김유진", 45},
		{"박상막", 30}
	};

	for (int i = 0; i < 10; i++)
	{
		Human* pFriend;
		pFriend = &arFriend[i];
		pFriend->intro();
	}
	

	return 0;
}