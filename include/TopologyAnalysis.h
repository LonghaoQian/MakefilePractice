#ifndef TOPOLOGYANALYSIS
#define TOPOLOGYANALYSIS
#include <iostream>

class TopologyAnalysis {
   public:
   TopologyAnalysis();
   virtual ~TopologyAnalysis();
   private:
   bool loopFound{false};
};

#endif