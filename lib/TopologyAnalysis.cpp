#include "TopologyAnalysis.h"
TopologyAnalysis::TopologyAnalysis(const Eigen::MatrixXd& connectionMatrix) : 
    loopFound(false), 
    connection(connectionMatrix)
{
    std::cout<<"topology analysis is instanciated.. \n";
    std::cout<<connection<<'\n';
}
TopologyAnalysis::~TopologyAnalysis()
{
    std::cout<<"topology analysis is destoryed.. \n";
}