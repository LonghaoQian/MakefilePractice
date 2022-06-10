
#include "JohnsonCurcitAlg.h"
#include "FindStrongComponents.h"

GraphAnalysis::AdjacencyXi LoadTestCase()
{
    GraphAnalysis::AdjacencyXi connection(11, 11);
    connection(0, 1) = 1;
    connection(0, 3) = 1;
    connection(1, 2) = 1;
    connection(1, 4) = 1;
    connection(2, 0) = 1;
    connection(2, 6) = 1;
    connection(3, 2) = 1;
    connection(4, 5) = 1;
    connection(4, 6) = 1;
    connection(5, 6) = 1;
    connection(5, 7) = 1;
    connection(5, 8) = 1;
    connection(5, 9) = 1;
    connection(6, 4) = 1;
    connection(7, 9) = 1;
    connection(8, 9) = 1;
    connection(9, 8) = 1;
    return connection;
}

int main(void) {
    auto adjacency = LoadTestCase();
    auto res1 = GraphAnalysis::GetNodeFromAdjMatrix(adjacency);
    GraphAnalysis::SccTarjan sccDetection(adjacency, adjacency.rows());
    sccDetection.PrintNodeList();
    // print the result
    auto res = sccDetection.GetResult();
    for (auto it = res.begin(); it != res.end(); it++) {
      for (auto it2 = it->begin(); it2 != it->end(); it2++) {
          std::cout<<*it2<<" ";
      }
      std::cout<<'\n';
    }
	return 0;
}