#include <stdio.h>

namespace A {
	double value;
}

namespace B {
	int value;
}

int main()
{
	using namespace A;
	using namespace B;

	value = 3;				// 모호하다는 에러 발생
}