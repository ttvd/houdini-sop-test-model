#pragma once

struct SOP_StanfordModelBunny
{
    static constexpr int s_num_vertices = 34835 * 3;
    static constexpr int s_num_indices = 69666 * 3;

    static float s_vertices[SOP_StanfordModelBunny::s_num_vertices];
    static float s_indices[SOP_StanfordModelBunny::s_num_indices];
};
