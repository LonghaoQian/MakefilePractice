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

#include "JohnsonCurcitAlg.h"
#include "FindStrongComponents.h"

GraphAnalysis::AdjacencyXi LoadTestCase()
{
    GraphAnalysis::AdjacencyXi connection(9, 9);
    connection(0, 1) = 1;
    connection(0, 7) = 1;

    connection(1, 2) = 1;
    connection(1, 8) = 1;
    connection(1, 6) = 1;

    connection(2, 0) = 1;
    connection(2, 1) = 1;
    connection(2, 3) = 1;
    connection(2, 5) = 1;

    connection(3, 4) = 1;

    connection(4, 1) = 1;

    connection(5, 3) = 1;

    connection(7, 8) = 1;
    connection(8, 7) = 1;
    return connection;
}

int main(void)
{
    auto adjacency = LoadTestCase();
    GraphAnalysis::SccTarjan sccDetection(adjacency, adjacency.rows());
    sccDetection.PrintNodeList();
    // print the result
    auto res = sccDetection.GetResult();
    for (auto it = res.begin(); it != res.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            std::cout << *it2 << " ";
        }
        std::cout << '\n';
    }
    GraphAnalysis::JohnsonCurcitAlg curcitDetection(adjacency, res,
                                                    adjacency.rows());
    auto resCycle = curcitDetection.GetResult();
    std::cout << "cycles are: \n";
    for (auto it = resCycle.begin(); it != resCycle.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            std::cout << *it2 << " ";
        }
        std::cout << '\n';
    }
    return 0;
}