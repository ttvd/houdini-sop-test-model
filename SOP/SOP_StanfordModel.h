#pragma once

#include <SOP/SOP_API.h>
#include <SOP/SOP_Node.h>

class SOP_API SOP_StanfordModel : public SOP_Node
{
    public:

        static OP_Node* myConstructor(OP_Network* network, const char* name, OP_Operator* op);

        static PRM_Template myTemplateList[];

    protected:

        SOP_StanfordModel(OP_Network* network, const char* name, OP_Operator* op);
        virtual ~SOP_StanfordModel();

    protected:

        virtual OP_ERROR cookMySop(OP_Context& context);

    private:

        int getModelType(fpreal t) const;
        int getPrimitiveType(fpreal t) const;
        bool getKeepOriginalCoordinateSystem(fpreal t) const;
        float getUniformScale(fpreal t) const;
        float getCenterX(fpreal t) const;
        float getCenterY(fpreal t) const;
        float getCenterZ(fpreal t) const;
};
