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