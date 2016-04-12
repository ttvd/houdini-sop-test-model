#include "OBJ_TestModel.h"

#include <UT/UT_DSOVersion.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>


OBJ_TestModel::OBJ_TestModel(OP_Network* network, const char* name, OP_Operator* op) :
    OBJ_Geometry(network, name, op)
{

}


OBJ_TestModel::~OBJ_TestModel()
{

}


OP_Node*
OBJ_TestModel::myConstructor(OP_Network* network, const char* name, OP_Operator* entry)
{
    return new OBJ_TestModel(network, name, entry);
}


OP_TemplatePair*
OBJ_TestModel::buildTemplatePair(OP_TemplatePair* template_prev)
{
    OP_TemplatePair* geo = new OP_TemplatePair(OBJ_Geometry::getTemplateList(OBJ_PARMS_PLAIN), template_prev);
    return geo;
}


OP_ERROR
OBJ_TestModel::cookMyObj(OP_Context& context)
{
    OP_ERROR errorstatus = OBJ_Geometry::cookMyObj(context);

    SOP_Node* node = getDisplaySopPtr();
    if(!node)
    {
        createNode("testmodel");
    }

    return errorstatus;
}


void
newObjectOperator(OP_OperatorTable* table)
{
    table->addOperator(new OP_Operator("testmodel", "Test Model", OBJ_TestModel::myConstructor,
        OBJ_TestModel::buildTemplatePair(0), 0, 1, 0));
}
