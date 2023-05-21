/*************************************************************

MIT License

Copyright (c) 2023 Dr. Longhao Qian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*************************************************************/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <unordered_map>
#include "GraphCommon.h"
namespace GraphAnalysis
{
using Path = std::vector<NodeIndex>;
struct DijkstraRes {
    Path path;
    double cost;
    bool valid;
};
class Dijkstra
{
   public:
    Dijkstra(const AdjacencyXi &adjacencyMatrix, const PathCostXd &pathCost,
             unsigned int numOfNodes);
    virtual ~Dijkstra();
    DijkstraRes GetResult(NodeIndex source, NodeIndex destination);
    void PrintConnectionMatrix();
    void PrintNodeConnectionList();
    void PrintPathCostMatrix();
    void Reset(const AdjacencyXi &adjacencyMatrix, const PathCostXd &pathCost,
               unsigned int numOfNodes);
    double GetDist(NodeIndex index);
    bool GreaterCost(double a, double b);

   private:
    bool CheckAdjacencyMatrix();
    bool BfsTraverseTree(NodeIndex source, NodeIndex destination);
    void RecordResult(NodeIndex destination);
    NodeIndex numberOfNodes{0u};
    AdjacencyXi adjacency;
    PathCostXd pathCost;
    std::vector<Node> nodeList;
    std::unordered_map<NodeIndex, double> dist;
    std::vector<NodeIndex> parent;
    std::vector<bool> visited;
    Path path;
};
}  // namespace GraphAnalysis
#endif