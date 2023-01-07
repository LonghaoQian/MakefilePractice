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

#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <Eigen/Core>
using namespace Eigen;
namespace RungeKuttaFamily {
    enum class SolverType {
        DORMANDPRINCE = 0,
        RUNGKUTTA_45,
        EXPLICIT_EULER
    };
    using InitButcherTableFunc = void (*)(void);
    class ButcherTableau {
    public:
        ButcherTableau(void) {}
        ButcherTableau(SolverType type,
                        uint32_t numOfK_,
                        size_t tableRows,
                        size_t tableCols) {
            solver = type;
            numOfK = numOfK_;
            table.resize(tableRows, tableCols);
            table.setZero();
            updateCoefficient1.resize(numOfK);
            updateCoefficient1.setZero();
        }
        ~ButcherTableau(void) = default;
        MatrixXd table; // coefficient matrix
        VectorXd updateCoefficient1; // update coefficient
        VectorXd updateCoefficient2;
        uint32_t numOfK{0}; // number of intermediate steps
        SolverType solver{SolverType::EXPLICIT_EULER};
    };
    ButcherTableau &LoadButcherTableau(SolverType solver);
    class RegistButcherTableau {
    public:
        RegistButcherTableau(InitButcherTableFunc ptr) {
            // register all butcher tableau
            if (ptr == nullptr) {
                return;
            }
            (*ptr)();
        }
    };
}

#define REG_BUTCHER_TABLEAU(name, initFuncPtr) \
    static RegistButcherTableau g_resiger_##name##_Tableau(initFuncPtr);

#endif