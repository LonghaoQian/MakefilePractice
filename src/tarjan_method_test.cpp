#include "FindStrongComponents.h"

int main(void) {
    Eigen::MatrixXd m(2, 2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    GraphAnalysis::AdjacencyXi connection(6, 6);
    connection.setZero();
    connection(0,1) = 1;
    connection(0,2) = 1;
    connection(2,3) = 1;
    connection(2,5) = 1;
    connection(3,4) = 1;
    connection(4,2) = 1;
    connection(5,4) = 1;
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