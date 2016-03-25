#pragma once

struct SOP_StanfordModelBuddha
{
    static constexpr int s_num_vertices = 49990 * 3;
    static constexpr int s_num_indices = 100000 * 3;

    static float s_vertices[SOP_StanfordModelBuddha::s_num_vertices];
    static float s_indices[SOP_StanfordModelBuddha::s_num_indices];
};
