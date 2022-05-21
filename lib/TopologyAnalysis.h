#ifndef TOPOLOGYANALYSIS
#define TOPOLOGYANALYSIS
#include <iostream>
#include <Eigen/Core>

class TopologyAnalysis {
   public:
   TopologyAnalysis(const Eigen::MatrixXd& connectionMatrix);
   void UpdateLoopDetection();
   virtual ~TopologyAnalysis();
   private:
   Eigen::MatrixXd connection;
   bool loopFound{false};
};

#endif