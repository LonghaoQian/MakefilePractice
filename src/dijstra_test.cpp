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

#include "Dijkstra.h"

std::pair<GraphAnalysis::AdjacencyXi, GraphAnalysis::PathCostXd> LoadTestCase()
{
    GraphAnalysis::AdjacencyXi connection(7, 7);
    connection(0, 1) = 1;
    connection(0, 3) = 1;

    connection(1, 4) = 1;

    connection(2, 0) = 1;
    connection(2, 3) = 1;

    connection(3, 4) = 1;

    connection(5, 4) = 1;

    connection(6, 0) = 1;
    connection(6, 2) = 1;
    connection(6, 5) = 1;

    GraphAnalysis::PathCostXd pathCost(7, 7);
    pathCost(0, 1) = 6.0;
    pathCost(0, 3) = 1.0;

    pathCost(1, 4) = 1.0;

    pathCost(2, 0) = 2.0;
    pathCost(2, 3) = 3.0;

    pathCost(3, 4) = 4.0;

    pathCost(5, 4) = 2.0;

    pathCost(6, 0) = 3.0;
    pathCost(6, 2) = 2.0;
    pathCost(6, 5) = 6.0;
    return {connection, pathCost};
}

int main(void)
{
    auto adjacency = LoadTestCase();
    GraphAnalysis::Dijkstra dijkstra(adjacency.first, adjacency.second, 7);
    dijkstra.PrintConnectionMatrix();
    dijkstra.PrintPathCostMatrix();
    dijkstra.PrintNodeConnectionList();
    auto res = dijkstra.GetResult(2, 4);
    if (res.valid) {
        std::cout << "the optimum path is: \n";
        for (auto t : res.path) {
            std::cout << t << '\n';
        }
        std::cout << "the path cost is: " << res.cost << '\n';
    } else {
        std::cout << "no route from the source to the destination.\n";
    }
    return 0;
}