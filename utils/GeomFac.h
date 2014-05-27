#ifndef GEOM_FAC_H
#define GEOM_FAC_H

#include <vector>

#include "CmpVertexDef.h"

std::vector<cmp::VtxDebug> g_GenerateGroundDebugVertexes(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b);

std::vector<unsigned> g_GenerateGroundDebugIndexes(int lx, int ly);

std::vector<cmp::VtxDebug> g_GenerateCarDebugVertexes();
std::vector<unsigned> g_GenerateCarDebugIndexes();

#endif
