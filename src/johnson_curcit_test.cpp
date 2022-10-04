/*************************************************************

Copyright(C) 2022 Longhao Qian

This program is free software; you can redistribute it and / or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program;
if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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