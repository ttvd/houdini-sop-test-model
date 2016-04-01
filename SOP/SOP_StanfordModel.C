#include "SOP_StanfordModel.h"
#include "SOP_StanfordModelBunny.h"
#include "SOP_StanfordModelDragon.h"
#include "SOP_StanfordModelBuddha.h"

#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <GEO/GEO_Detail.h>
#include <GEO/GEO_PrimPoly.h>
#include <GU/GU_Detail.h>


static PRM_Name s_name_keep_original_coordinate_system("sfm_keep_original_coordinate_system", "Keep Original Coordinate System");
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


static PRM_Default s_default_keep_original_coordinate_system(false);
static PRM_Range s_default_uscale_range(PRM_RANGE_UI, 0, PRM_RANGE_UI, 10);


static PRM_ChoiceList s_choicelist_model_type(PRM_CHOICELIST_SINGLE, s_name_model_types);
static PRM_ChoiceList s_choicelist_primitive_type(PRM_CHOICELIST_SINGLE, s_name_primitive_types);


PRM_Template
SOP_StanfordModel::myTemplateList[] = {
    PRM_Template(PRM_ORD, 1, &s_name_model_type, 0, &s_choicelist_model_type),
    PRM_Template(PRM_ORD, 1, &s_name_primitive_type, 0, &s_choicelist_primitive_type),
    PRM_Template(PRM_TOGGLE, 1, &s_name_keep_original_coordinate_system, &s_default_keep_original_coordinate_system),
    PRM_Template(PRM_XYZ, 3, &PRMcenterName),
    PRM_Template(PRM_FLT, 1, &PRMuscaleName, PRMoneDefaults, 0, &s_default_uscale_range),
    PRM_Template()
};


int
SOP_StanfordModel::getModelType(fpreal t) const
{
    return evalInt("sfm_model_type", 0, t);
}


int
SOP_StanfordModel::getPrimitiveType(fpreal t) const
{
    return evalInt("sfm_primitive_type", 0, t);
}


bool
SOP_StanfordModel::getKeepOriginalCoordinateSystem(fpreal t) const
{
    return evalInt("sfm_keep_original_coordinate_system", 0, t);
}


float
SOP_StanfordModel::getUniformScale(fpreal t) const
{
    return evalFloat("scale", 0, t);
}


float
SOP_StanfordModel::getCenterX(fpreal t) const
{
    return evalFloat("t", 0, t);
}


float
SOP_StanfordModel::getCenterY(fpreal t) const
{
    return evalFloat("t", 1, t);
}


float
SOP_StanfordModel::getCenterZ(fpreal t) const
{
    return evalFloat("t", 2, t);
}


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
    if(error() >= UT_ERROR_ABORT)
    {
        return error();
    }

    gdp->clearAndDestroy();

    UT_AutoInterrupt boss("Building Stanford Model");
    if(boss.wasInterrupted())
    {
        return error();
    }

    fpreal t = context.getTime();

    int mode_type = getModelType(t);
    int primitive_type = getPrimitiveType(t);
    bool keep_original_coordinate_system = getKeepOriginalCoordinateSystem(t);
    float uniform_scale = getUniformScale(t);
    UT_Vector3 model_center(getCenterX(t), getCenterY(t), getCenterZ(t));

    int num_vertices = 0;
    int num_indices = 0;

    const float* data_vertices = nullptr;
    const float* data_indices = nullptr;

    switch(mode_type)
    {
        default:
        case 0:
        {
            num_vertices = SOP_StanfordModelBunny::s_num_vertices;
            num_indices = SOP_StanfordModelBunny::s_num_indices;

            data_vertices = &SOP_StanfordModelBunny::s_vertices[0];
            data_indices = &SOP_StanfordModelBunny::s_indices[0];

            break;
        }

        case 1:
        {
            num_vertices = SOP_StanfordModelDragon::s_num_vertices;
            num_indices = SOP_StanfordModelDragon::s_num_indices;

            data_vertices = &SOP_StanfordModelDragon::s_vertices[0];
            data_indices = &SOP_StanfordModelDragon::s_indices[0];

            break;
        }

        case 2:
        {
            num_vertices = SOP_StanfordModelBuddha::s_num_vertices;
            num_indices = SOP_StanfordModelBuddha::s_num_indices;

            data_vertices = &SOP_StanfordModelBuddha::s_vertices[0];
            data_indices = &SOP_StanfordModelBuddha::s_indices[0];

            break;
        }
    }

    UT_Map<UT_Vector3, GA_Offset> unique_points;

    for(int idx = 0; idx < num_indices; idx += 3)
    {
        GEO_PrimPoly* prim_poly = nullptr;

        if(!primitive_type)
        {
            prim_poly = dynamic_cast<GEO_PrimPoly*>(gdp->appendPrimitive(GEO_PRIMPOLY));
            prim_poly->setSize(0);
        }

        for(int vtx_idx = 0; vtx_idx < 3; ++vtx_idx)
        {
            int idx_value = *(data_indices + idx + vtx_idx);
            const float* vtx = data_vertices + 3 * idx_value;

            UT_Vector3 point_data(*(vtx + 0), *(vtx + 1), *(vtx + 2));
            point_data -= model_center;
            point_data *= uniform_scale;

            if(keep_original_coordinate_system)
            {
                point_data = UT_Vector3(point_data.x(), point_data.z(), point_data.y());
            }

            GA_Offset point_offset = 0;

            if(unique_points.contains(point_data))
            {
                point_offset = unique_points[point_data];
            }
            else
            {
                point_offset = gdp->appendPointOffset();
                gdp->setPos3(point_offset, point_data);
                unique_points[point_data] = point_offset;
            }

            if(prim_poly)
            {
                prim_poly->appendVertex(point_offset);
            }
        }

        if(prim_poly)
        {
            prim_poly->close();
        }
    }

    return error();
}


void
newSopOperator(OP_OperatorTable* table)
{
    table->addOperator(new OP_Operator("stanfordmodel", "Stanford Model", SOP_StanfordModel::myConstructor,
        SOP_StanfordModel::myTemplateList, 0, 0, 0, OP_FLAG_GENERATOR));
}
