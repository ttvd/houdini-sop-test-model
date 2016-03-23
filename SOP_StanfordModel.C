#include "SOP_StanfordModel.h"

#include <UT/UT_DSOVersion.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <GEO/GEO_Detail.h>
#include <GEO/GEO_PrimPoly.h>
#include <GU/GU_Detail.h>


static PRM_Name s_name_translate_coordinate_system("sfm_translate_coordinate_system", "Translate to Houdini Coordinate System");
static PRM_Name s_name_model_type("sfm_model_type", "Model Type");
static PRM_Name s_name_model_types[] =
{
    PRM_Name("bunny", "Bunny"),
    PRM_Name("dragon", "Dragon"),
    PRM_Name("buddha", "Buddha"),
    PRM_Name(0),
};
static PRM_Name s_name_primitive_type("sfm_primitive_type", "Primitive Type");
static PRM_Name s_name_primitive_types[] =
{
    PRM_Name("poly", "Polygon"),
    PRM_Name("points", "Points"),
    PRM_Name(0),
};


static PRM_Default s_default_translate_coordinate_system(true);
static PRM_Range s_default_uscale_range(PRM_RANGE_UI, 0, PRM_RANGE_UI, 10);

static PRM_ChoiceList s_choicelist_model_type(PRM_CHOICELIST_SINGLE, s_name_model_types);
static PRM_ChoiceList s_choicelist_primitive_type(PRM_CHOICELIST_SINGLE, s_name_primitive_types);


PRM_Template
SOP_StanfordModel::myTemplateList[] = {
    PRM_Template(PRM_ORD, 1, &s_name_model_type, 0, &s_choicelist_model_type),
    PRM_Template(PRM_ORD, 1, &s_name_primitive_type, 0, &s_choicelist_primitive_type),
    PRM_Template(PRM_TOGGLE, 1, &s_name_translate_coordinate_system, &s_default_translate_coordinate_system),
    PRM_Template(PRM_XYZ, 3, &PRMcenterName),
    PRM_Template(PRM_FLT, 1, &PRMuscaleName, PRMoneDefaults, 0, &s_default_uscale_range),
    PRM_Template()
};


OP_Node*
SOP_StanfordModel::myConstructor(OP_Network* network, const char* name, OP_Operator* op)
{
    return new SOP_StanfordModel(network, name, op);
}


SOP_StanfordModel::SOP_StanfordModel(OP_Network* network, const char* name, OP_Operator* op) :
    SOP_Node(network, name, op)
{

}


SOP_StanfordModel::~SOP_StanfordModel()
{

}


OP_ERROR
SOP_StanfordModel::cookMySop(OP_Context& context)
{
    return error();
}


void
newSopOperator(OP_OperatorTable* table)
{
    table->addOperator(new OP_Operator("stanfordmodel", "Stanford Model", SOP_StanfordModel::myConstructor,
        SOP_StanfordModel::myTemplateList, 0, 0, 0, OP_FLAG_GENERATOR));
}
