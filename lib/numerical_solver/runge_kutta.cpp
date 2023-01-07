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

#include "runge_kutta.h"
#include <map>

namespace RungeKuttaFamily {
    std::map<uint32_t, ButcherTableau> g_ButcherTableauContainer;
    ButcherTableau &LoadButcherTableau(SolverType solver)
    {
        auto idx = static_cast<uint32_t>(solver);
        if (g_ButcherTableauContainer.find(idx) == g_ButcherTableauContainer.end()) {
            return g_ButcherTableauContainer[static_cast<uint32_t>(SolverType::EXPLICIT_EULER)]; // default is euler
        }
        return g_ButcherTableauContainer[idx];
    }
    constexpr uint32_t EXPLICIT_EULER_NUM_K = 1;
    constexpr size_t EXPLICIT_EULER_TABLE_ROWS = 2;
    constexpr size_t EXPLICIT_EULER_TABLE_COLS = 2;
    static void InitbutchertableauExplicitEuler(void)
    {
        auto idx = static_cast<uint32_t>(SolverType::EXPLICIT_EULER);
        g_ButcherTableauContainer.emplace(idx, ButcherTableau(
            SolverType::EXPLICIT_EULER, EXPLICIT_EULER_NUM_K, EXPLICIT_EULER_TABLE_ROWS, EXPLICIT_EULER_TABLE_COLS));
        g_ButcherTableauContainer[idx].table(1, 1) = 1.0;
        g_ButcherTableauContainer[idx].updateCoefficient1(0) = g_ButcherTableauContainer[idx].table(1, 1);
    }
    // resgister butcher tableau
    REG_BUTCHER_TABLEAU(EXPLICIT_EULER, InitbutchertableauExplicitEuler)
    constexpr uint32_t RUNGKUTTA_45_NUM_K = 4;
    constexpr size_t RUNGKUTTA_45_TABLE_ROWS = 5;
    constexpr size_t RUNGKUTTA_45_TABLE_COLS = 5;
    static void InitbutchertableauRK_45(void)
    {
        auto idx = static_cast<uint32_t>(SolverType::RUNGKUTTA_45);
        g_ButcherTableauContainer.emplace(idx, ButcherTableau(
            SolverType::RUNGKUTTA_45, RUNGKUTTA_45_NUM_K, RUNGKUTTA_45_TABLE_ROWS, RUNGKUTTA_45_TABLE_COLS));
        g_ButcherTableauContainer[idx].table(1, 0) = 0.5;
        g_ButcherTableauContainer[idx].table(2, 0) = 0.5;
        g_ButcherTableauContainer[idx].table(3, 0) = 1.0;

        g_ButcherTableauContainer[idx].table(1, 1) = 0.5;
        g_ButcherTableauContainer[idx].table(2, 1) = 0.0;
        g_ButcherTableauContainer[idx].table(3, 1) = 0.0;
        g_ButcherTableauContainer[idx].table(4, 1) = 1.0 / 6.0;

        g_ButcherTableauContainer[idx].table(2, 2) = 0.5;
        g_ButcherTableauContainer[idx].table(3, 2) = 0.0;
        g_ButcherTableauContainer[idx].table(4, 2) = 1.0/3.0;

        g_ButcherTableauContainer[idx].table(3, 3) = 1.0;
        g_ButcherTableauContainer[idx].table(4, 3) = 1.0 / 3.0;

        g_ButcherTableauContainer[idx].table(4, 4) = 1.0 / 6.0;

        for (size_t i = 0; i < g_ButcherTableauContainer[idx].numOfK; i++) {
            g_ButcherTableauContainer[idx].updateCoefficient1(i) =
                g_ButcherTableauContainer[idx].table(g_ButcherTableauContainer[idx].numOfK,
                    i + 1);
        }
    }
    // resgister butcher tableau
    REG_BUTCHER_TABLEAU(RUNGKUTTA_45, InitbutchertableauRK_45)
    constexpr uint32_t DORMANDPRINCE_NUM_K = 7;
    constexpr size_t DORMANDPRINCE_TABLE_ROWS = 9;
    constexpr size_t DORMANDPRINCE_TABLE_COLS = 8;
    // reference: http://depa.fquim.unam.mx/amyd/archivero/DormandPrince_19856.pdf
    static void InitbutchertableauDORMANDPRINCE(void)
    {
        auto idx = static_cast<uint32_t>(SolverType::DORMANDPRINCE);
        g_ButcherTableauContainer.emplace(idx, ButcherTableau(
            SolverType::DORMANDPRINCE, DORMANDPRINCE_NUM_K, DORMANDPRINCE_TABLE_ROWS, DORMANDPRINCE_TABLE_COLS));
        double t21 = 1.0 / 5.0;
        double t22 = 1.0 / 5.0;
        double t31 = 3.0 / 10.0;
        double t32 = 3.0 / 40.0;
        double t33 = 9.0 / 40.0;
        double t41 = 4.0 / 5.0;
        double t42 = 44.0 / 45.0;
        double t43 = -56.0 / 15.0;
        double t44 = 32.0 / 9.0;
        double t51 = 8.0 / 9.0;
        double t52 = 19372.0 / 6561.0;
        double t53 = -25360.0 / 2187.0;
        double t54 = 64448.0 / 6561.0;
        double t55 = -212.0 / 729.0;
        double t61 = 1.0;
        double t62 = 9017.0 / 3168.0;
        double t63 = -355.0 / 33.0;
        double t64 = 46732.0 / 5247.0;
        double t65 = 49.0 / 176.0;
        double t66 = -5103.0 / 18656.0;
        double t71 = 1.0;
        double t72 = 35.0 / 384.0;
        double t73 = 0.0;
        double t74 = 500.0 / 1113.0;
        double t75 = 125.0 / 192.0;
        double t76 = -2187.0 / 6784.0;
        double t77 = 11.0 / 84.0;

        double t82 = 35.0 / 384.0;
        double t83 = 0.0;
        double t84 = 500.0 / 1113.0;
        double t85 = 125.0 / 192.0;
        double t86 = -2187.0 / 6784.0;
        double t87 = 11.0 / 84.0;
        double t88 = 0.0;
        double t92 = 5179.0 / 57600.0;
        double t93 = 0.0;
        double t94 = 7571.0 / 16695.0;
        double t95 = 393.0 / 640.0;
        double t96 = -92097.0 / 339200.0;
        double t97 = 187.0 / 2100.0;
        double t98 = 1.0 / 40.0;

        g_ButcherTableauContainer[idx].table(1, 0) = t21;
        g_ButcherTableauContainer[idx].table(1, 1) = t22;

        g_ButcherTableauContainer[idx].table(2, 0) = t31;
        g_ButcherTableauContainer[idx].table(2, 1) = t32;
        g_ButcherTableauContainer[idx].table(2, 2) = t33;

        g_ButcherTableauContainer[idx].table(3, 0) = t41;
        g_ButcherTableauContainer[idx].table(3, 1) = t42;
        g_ButcherTableauContainer[idx].table(3, 2) = t43;
        g_ButcherTableauContainer[idx].table(3, 3) = t44;

        g_ButcherTableauContainer[idx].table(4, 0) = t51;
        g_ButcherTableauContainer[idx].table(4, 1) = t52;
        g_ButcherTableauContainer[idx].table(4, 2) = t53;
        g_ButcherTableauContainer[idx].table(4, 3) = t54;
        g_ButcherTableauContainer[idx].table(4, 4) = t55;

        g_ButcherTableauContainer[idx].table(5, 0) = t61;
        g_ButcherTableauContainer[idx].table(5, 1) = t62;
        g_ButcherTableauContainer[idx].table(5, 2) = t63;
        g_ButcherTableauContainer[idx].table(5, 3) = t64;
        g_ButcherTableauContainer[idx].table(5, 4) = t65;
        g_ButcherTableauContainer[idx].table(5, 5) = t66;

        g_ButcherTableauContainer[idx].table(6, 0) = t71;
        g_ButcherTableauContainer[idx].table(6, 1) = t72;
        g_ButcherTableauContainer[idx].table(6, 2) = t73;
        g_ButcherTableauContainer[idx].table(6, 3) = t74;
        g_ButcherTableauContainer[idx].table(6, 4) = t75;
        g_ButcherTableauContainer[idx].table(6, 5) = t76;
        g_ButcherTableauContainer[idx].table(6, 6) = t77;

        g_ButcherTableauContainer[idx].table(7, 1) = t82;
        g_ButcherTableauContainer[idx].table(7, 2) = t83;
        g_ButcherTableauContainer[idx].table(7, 3) = t84;
        g_ButcherTableauContainer[idx].table(7, 4) = t85;
        g_ButcherTableauContainer[idx].table(7, 5) = t86;
        g_ButcherTableauContainer[idx].table(7, 6) = t87;
        g_ButcherTableauContainer[idx].table(7, 7) = t88;

        g_ButcherTableauContainer[idx].table(8, 1) = t92;
        g_ButcherTableauContainer[idx].table(8, 2) = t93;
        g_ButcherTableauContainer[idx].table(8, 3) = t94;
        g_ButcherTableauContainer[idx].table(8, 4) = t95;
        g_ButcherTableauContainer[idx].table(8, 5) = t96;
        g_ButcherTableauContainer[idx].table(8, 6) = t97;
        g_ButcherTableauContainer[idx].table(8, 7) = t98;

        g_ButcherTableauContainer[idx]
            .updateCoefficient1
            .resize(g_ButcherTableauContainer[idx].numOfK);
        g_ButcherTableauContainer[idx]
            .updateCoefficient2
            .resize(g_ButcherTableauContainer[idx].numOfK);
        for (size_t i = 0; i < g_ButcherTableauContainer[idx].numOfK; i++) {
            g_ButcherTableauContainer[idx]
                .updateCoefficient1(i) =
            g_ButcherTableauContainer[idx]
                .table(g_ButcherTableauContainer[idx].numOfK, i + 1);
            g_ButcherTableauContainer[idx]
                .updateCoefficient2(i) =
            g_ButcherTableauContainer[idx]
                .table(g_ButcherTableauContainer[idx].numOfK + 1, i + 1);
        }
    }
    // resgister butcher tableau
    REG_BUTCHER_TABLEAU(DORMANDPRINCE, InitbutchertableauDORMANDPRINCE)
}