using namespace std;
#include "CppUnitTest.h"
#include "../DijkstraAlgorithm/DijkstraPathfinder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DijkstraAlgorithmTests
{
	TEST_CLASS(DijkstraAlgorithmTests)
	{
	public:
		
		TEST_METHOD(TestTravelCostParsing)
		{
			List<String> validStrings = { "N/A", "99999", "+1"};
			List<String> invalidStrings = { "-1", "asf3", "-asnoiu"};

			for (size_t i = 0; i < invalidStrings.Count(); i++)
			{
				try
				{
					auto result = DijkstraPathfinder::ParseTravelCost(invalidStrings[i]);
					Assert::Fail();
				}
				catch (exception e)
				{

				}
			}

			Assert::AreEqual(-1l, DijkstraPathfinder::ParseTravelCost(validStrings[0]));
			Assert::AreEqual(99999l, DijkstraPathfinder::ParseTravelCost(validStrings[1]));
			Assert::AreEqual(1l, DijkstraPathfinder::ParseTravelCost(validStrings[2]));
		}
		TEST_METHOD(TestNodeCountParsing)
		{
			List<String> lines = 
			{ 
				"City1;City2;N/A;10",
				"City1;City2;10;10",
				"City3;City2;3;N/A",
				"City1;City2;N/A;10",
				"City3;City2;N/A;15",
				"City1;City3;2;10",
				"City2;City2;N/A;10",
				"City3;City2;0;5"
			};

			DijkstraPathfinder pathfinder(lines);

			Assert::AreEqual((size_t)3, pathfinder.GetNodeCount());

		}

		TEST_METHOD(TestPathfindingResult)
		{
			List<String> lines =
			{
				"A;F;5;5", 
				"A;H;4;4", 
				"F;E;5;5", 
				"E;H;15;15",
				"E;D;15;15",
				"D;H;5;5",
				"D;C;8;8",
				"C;B;5;5",
				"B;H;7;7",

				"notConnected;A;N/A;5"
			};
			//A 0
			//F 1
			//H 2
			//E 3
			//D 4
			//C 5
			//B 6
			//notConnected 7

			DijkstraPathfinder pathfinder(lines);

			Assert::AreEqual((long)0, pathfinder.FindPath(0,0)); //A->A
			Assert::AreEqual((long)5, pathfinder.FindPath(0,1)); //A->F
			Assert::AreEqual((long)4, pathfinder.FindPath(0,2)); //A->H
			Assert::AreEqual((long)10, pathfinder.FindPath(0,3)); //A->E
			Assert::AreEqual((long)9, pathfinder.FindPath(0,4)); //A->D
			Assert::AreEqual((long)16, pathfinder.FindPath(0,5)); //A->C
			Assert::AreEqual((long)11, pathfinder.FindPath(0,6)); //A->B

			Assert::AreEqual((long)5, pathfinder.FindPath(1, 0)); //F->A
			Assert::AreEqual((long)0, pathfinder.FindPath(1, 1)); //F->F
			Assert::AreEqual((long)9, pathfinder.FindPath(1, 2)); //F->H
			Assert::AreEqual((long)5, pathfinder.FindPath(1, 3)); //F->E
			Assert::AreEqual((long)14, pathfinder.FindPath(1, 4)); //F->D
			Assert::AreEqual((long)21, pathfinder.FindPath(1, 5)); //F->C
			Assert::AreEqual((long)16, pathfinder.FindPath(1, 6)); //F->B

			Assert::AreEqual((long)4, pathfinder.FindPath(2, 0)); //H->A
			Assert::AreEqual((long)9, pathfinder.FindPath(2, 1)); //H->F
			Assert::AreEqual((long)0, pathfinder.FindPath(2, 2)); //H->H
			Assert::AreEqual((long)14, pathfinder.FindPath(2, 3)); //H->E
			Assert::AreEqual((long)5, pathfinder.FindPath(2, 4)); //H->D
			Assert::AreEqual((long)12, pathfinder.FindPath(2, 5)); //H->C
			Assert::AreEqual((long)7, pathfinder.FindPath(2, 6)); //H->B

			Assert::AreEqual((long)10, pathfinder.FindPath(3, 0)); //E->A
			Assert::AreEqual((long)5, pathfinder.FindPath(3, 1)); //E->F
			Assert::AreEqual((long)14, pathfinder.FindPath(3, 2)); //E->H
			Assert::AreEqual((long)0, pathfinder.FindPath(3, 3)); //E->E
			Assert::AreEqual((long)15, pathfinder.FindPath(3, 4)); //E->D
			Assert::AreEqual((long)23, pathfinder.FindPath(3, 5)); //E->C
			Assert::AreEqual((long)21, pathfinder.FindPath(3, 6)); //E->B

			Assert::AreEqual((long)9, pathfinder.FindPath(4, 0)); //D->A
			Assert::AreEqual((long)14, pathfinder.FindPath(4, 1)); //D->F
			Assert::AreEqual((long)5, pathfinder.FindPath(4, 2)); //D->H
			Assert::AreEqual((long)15, pathfinder.FindPath(4, 3)); //D->E
			Assert::AreEqual((long)0, pathfinder.FindPath(4, 4)); //D->D
			Assert::AreEqual((long)8, pathfinder.FindPath(4, 5)); //D->C
			Assert::AreEqual((long)12, pathfinder.FindPath(4, 6)); //D->B

			Assert::AreEqual((long)16, pathfinder.FindPath(5, 0)); //C->A
			Assert::AreEqual((long)21, pathfinder.FindPath(5, 1)); //C->F
			Assert::AreEqual((long)12, pathfinder.FindPath(5, 2)); //C->H
			Assert::AreEqual((long)23, pathfinder.FindPath(5, 3)); //C->E
			Assert::AreEqual((long)8, pathfinder.FindPath(5, 4)); //C->D
			Assert::AreEqual((long)0, pathfinder.FindPath(5, 5)); //C->C
			Assert::AreEqual((long)5, pathfinder.FindPath(5, 6)); //C->B

			Assert::AreEqual((long)11, pathfinder.FindPath(6, 0)); //B->A
			Assert::AreEqual((long)16, pathfinder.FindPath(6, 1)); //B->F
			Assert::AreEqual((long)7, pathfinder.FindPath(6, 2)); //B->H
			Assert::AreEqual((long)21, pathfinder.FindPath(6, 3)); //B->E
			Assert::AreEqual((long)12, pathfinder.FindPath(6, 4)); //B->D
			Assert::AreEqual((long)5, pathfinder.FindPath(6, 5)); //B->C
			Assert::AreEqual((long)0, pathfinder.FindPath(6, 6)); //B->B

			Assert::AreEqual((long)-1, pathfinder.FindPath(7, 0)); //path doesn't exist
		}
	};
}
