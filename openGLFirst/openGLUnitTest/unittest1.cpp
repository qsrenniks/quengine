#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\openGLFirst\TileGameObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace openGLUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
      TileGameObject* copy = new TileGameObject();

      Assert::IsTrue(copy != nullptr);

		}

	};
}