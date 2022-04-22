#include "pch.h"
#include "CppUnitTest.h"
#include "../3.2/3.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 2;
			Student* s = new Student[N];
			s[0].lastname = "Protsak";
			s[0].cours = 1;
			s[0].spec = "it";
			s[0].physic = 5;
			s[0].math = 5;
			s[0].informatic = 5;
			s[1].lastname = "Prozzz";
			s[1].cours = "2";
			s[1].spec = "it";
			s[1].physic = 3;
			s[1].math = 3;
			s[1].informatic = 3;

			Assert::IsTrue(BinSearch(s, N, "Prozzz", "2", 3) == 1);
		}
	};
}
