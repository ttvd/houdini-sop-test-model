#pragma once

struct SOP_StanfordModelDragon
{
    static constexpr int s_num_vertices = 150000;
    static constexpr int s_num_indices = 300000;

    static float s_vertices[SOP_StanfordModelDragon::s_num_vertices];
    static float s_indices[SOP_StanfordModelDragon::s_num_indices];
};
