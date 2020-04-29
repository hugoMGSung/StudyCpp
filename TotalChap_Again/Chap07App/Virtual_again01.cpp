#include <stdio.h>
#include <string.h>

class Human {
protected:
	char name[12];
	int age;
public:
	Human(const char* aname, int aage) {
		strcpy(name, aname);
		age = aage;
	}
	void intro() {
		printf("%s�� %d�� �Դϴ�\n", name, age);
	}
};

class Student : public Human {
protected:
	int stunum;
public:
	Student(const char* aname, int aage, int astunum) : Human(aname, aage) {
		stunum = astunum;
	}
	void intro() {
		printf("%d��, %s�Դϴ�\n", stunum, name);
	}
};

int main() {
	Human h("������", 45);
	h.intro();
	Student s("�ֻ��", 26, 25);
	s.intro();
}