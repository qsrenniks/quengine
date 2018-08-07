#include "stdafx.h"
#include "CppUnitTest.h"
//#include "..\openGLFirst\TileGameObject.h"
#include "..\openGLFirst\Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace openGLUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
      Engine* engine = Engine::Instance();

      Assert::IsTrue(engine != nullptr);

      Engine::Destroy();
		}
	};
}