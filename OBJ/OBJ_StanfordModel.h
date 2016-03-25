#pragma once

#include <OBJ/OBJ_Geometry.h>

class OBJ_StanfordModel : public OBJ_Geometry
{
    public:

        OBJ_StanfordModel(OP_Network* network, const char* name, OP_Operator* op);
        virtual ~OBJ_StanfordModel();

    protected:

        virtual OP_ERROR cookMyObj(OP_Context& context);

    public:

        static OP_Node* myConstructor(OP_Network* network, const char* name, OP_Operator* entry);
        static OP_TemplatePair* buildTemplatePair(OP_TemplatePair* template_pair);
};
