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