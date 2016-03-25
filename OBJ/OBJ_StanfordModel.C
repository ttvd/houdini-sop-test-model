#include "OBJ_StanfordModel.h"

#include <UT/UT_DSOVersion.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>


OBJ_StanfordModel::OBJ_StanfordModel(OP_Network* network, const char* name, OP_Operator* op) :
    OBJ_Geometry(network, name, op)
{

}


OBJ_StanfordModel::~OBJ_StanfordModel()
{

}


OP_Node*
OBJ_StanfordModel::myConstructor(OP_Network* network, const char* name, OP_Operator* entry)
{
    return new OBJ_StanfordModel(network, name, entry);
}


OP_TemplatePair*
OBJ_StanfordModel::buildTemplatePair(OP_TemplatePair* template_prev)
{
    OP_TemplatePair* geo = new OP_TemplatePair(OBJ_Geometry::getTemplateList(OBJ_PARMS_PLAIN), template_prev);
    return geo;
}


OP_ERROR
OBJ_StanfordModel::cookMyObj(OP_Context& context)
{
    OP_ERROR errorstatus = OBJ_Geometry::cookMyObj(context);

    SOP_Node* node = getDisplaySopPtr();
    if(!node)
    {
        createNode("stanfordmodel");
    }

    return errorstatus;
}


void
newObjectOperator(OP_OperatorTable* table)
{
    table->addOperator(new OP_Operator("stanfordmodel", "Stanford Model", OBJ_StanfordModel::myConstructor,
        OBJ_StanfordModel::buildTemplatePair(0), 0, 1, 0));
}
