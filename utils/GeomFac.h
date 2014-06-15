#ifndef GEOM_FAC_H
#define GEOM_FAC_H

#include <vector>
#include "ResShaderDebug.h"
#include "ResShaderTank.h"

std::vector<res::ResShaderDebug::Vertex> g_GenerateGroundDebugVertexes(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b);

std::vector<res::ResShaderDebug::Vertex> g_GenerateCarDebugVertexes();

std::vector<res::ResShaderTank::Vertex> g_GenerateCubeVertexes(
        FLOATING lx, FLOATING ly, FLOATING lz);

#endif
