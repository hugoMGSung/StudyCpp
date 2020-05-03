#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

struct CharacterInvenInfo {
	int SlotNum;
	int ItemCode;
};

class MCommand {
	int Num;
};

auto func1() { return 1; }

int y = 3;
auto& func2() { return y; }

auto IsMaxLevel(int level) {
	if (level >= 100)
		return true;
	else
		return false;
}

int main(void) {
	// char*
	auto NewName = "Hugo";
	std::cout << NewName << std::endl;

	// int 
	auto Number = 1;
	std::cout << Number << std::endl;

	// pointer
	int UserMode = 4;
	auto pUserMode = &UserMode;
	std::cout << "pUserMode : Value = " << *pUserMode << ", address : "
		<< pUserMode << std::endl;

	// reference
	auto& refUserMode = UserMode;
	refUserMode = 5;
	std::cout << "UserMode : Value = " << UserMode << " | refUserMode : Value = "
		<< refUserMode << std::endl;

	auto pCharInven = new CharacterInvenInfo();
	pCharInven->ItemCode = 10;
	pCharInven->SlotNum = 1;

	std::cout << pCharInven->SlotNum << ", " << pCharInven->ItemCode << std::endl;

	delete pCharInven;

	typedef std::list<MCommand*> LIST_COMMAND;
	LIST_COMMAND m_listCommand;
	LIST_COMMAND::iterator iter = m_listCommand.begin();

	//auto iter = m_listCommand.begin();

	int x = func1(); // x == 1;
	std::cout << "x is " << x << std::endl;

	int& r = func2();
	std::cout << "r is " << r << std::endl;

	int NumberList[5] = { 1,2,3,4,5 };

	// for 
	for (int i = 0; i < 5; i++)
	{
		std::cout << "for " << i << ", ";
	}
	std::cout << std::endl;

	// VC for each // 规过 茫酒具
	/*for each (int i in NumberList)
	{
		std::cout << "for each " << i << ", ";
	}
	std::cout << std::endl;*/

	// range based for
	for (auto& i : NumberList)
	{
		std::cout << "range for " << i << ", ";
	}
	std::cout << std::endl;

	std::unordered_map<int, std::string> NumString; // 规过 茫酒具

	// end of main
	return 0;
}