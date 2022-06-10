#include "FindStrongComponents.h"

/*
cout << "\nSCCs in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.SCC();
 
    cout << "\nSCCs in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.SCC();
 
    cout << "\nSCCs in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.SCC();
 
    cout << "\nSCCs in fourth graph \n";
    Graph g4(11);
    g4.addEdge(0,1);g4.addEdge(0,3);
    g4.addEdge(1,2);g4.addEdge(1,4);
    g4.addEdge(2,0);g4.addEdge(2,6);
    g4.addEdge(3,2);
    g4.addEdge(4,5);g4.addEdge(4,6);
    g4.addEdge(5,6);g4.addEdge(5,7);g4.addEdge(5,8);g4.addEdge(5,9);
    g4.addEdge(6,4);
    g4.addEdge(7,9);
    g4.addEdge(8,9);
    g4.addEdge(9,8);
    g4.SCC();
 
    cout << "\nSCCs in fifth graph \n";
    Graph g5(5);
    g5.addEdge(0,1);
    g5.addEdge(1,2);
    g5.addEdge(2,3);
    g5.addEdge(2,4);
    g5.addEdge(3,0);
    g5.addEdge(4,2);
    g5.SCC();

    SCCs in first graph
4
3
1 2 0

SCCs in second graph
3
2
1
0

SCCs in third graph
5
3
4
6
2 1 0

SCCs in fourth graph
8 9
7
5 4 6
3 2 1 0
10

SCCs in fifth graph
4 3 2 1 0 
*/

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
    Eigen::MatrixXd m(2, 2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    auto connection = LoadTestCase();
    auto res1 = GraphAnalysis::GetNodeFromAdjMatrix(connection);
    GraphAnalysis::SccTarjan sccDetection(connection, connection.rows());
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