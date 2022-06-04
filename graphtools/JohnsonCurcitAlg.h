#ifndef JOHNSONCURCITALG_H
#define JOHNSONCURCITALG_H

#include "GraphCommon.h"
namespace GraphAnalysis {
    typedef std::vector<int> Loop;
    class JohnsonCurcitAlg {
        public:
        JohnsonCurcitAlg(const AdjacencyXi& adjacencyMatrix);
        virtual ~JohnsonCurcitAlg();
        void Reset(const AdjacencyXi& adjacencyMatrix);
        std::vector<Loop> GetResult();
        void DisplayConnectionMatrix();
        void DisplayNodeConnectionList();
        void DisplayNodeBuffer();
        private:
        AdjacencyXi adjacency;
        NodeBuffer nodeBuffer;
    };
}
#endif