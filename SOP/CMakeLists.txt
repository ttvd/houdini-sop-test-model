project(SOP_StanfordModel)

set(HOUDINI_SOPSTANFORDMODEL_INCLUDE
    SOP_StanfordModel.h
    SOP_StanfordModelBunny.h
    SOP_StanfordModelDragon.h
    SOP_StanfordModelBuddha.h
)

set(HOUDINI_SOPSTANFORDMODEL_SOURCE
    SOP_StanfordModel.C
    SOP_StanfordModelBunny.C
    SOP_StanfordModelDragon.C
    SOP_StanfordModelBuddha.C
)

set(HOUDINI_SOPSTANFORDMODEL_LIBS
    HoudiniUT
    HoudiniGEO
    HoudiniPRM
    HoudiniOP2
    boost_system
)

add_definitions(
    -DUT_DSO_TAGINFO=\"3262197cbf1f501f2caa0ca8572890fb3e4b9bfcc021d8a873a8c3063d69ee812b972985db32267a5946addc2f8f31780eadf501ffc2e85149062ee263fe81be4baf508aff924994a3268d0847f848e6ab4e98a984ed956599\")

add_library(SOP_StanfordModel SHARED ${HOUDINI_SOPSTANFORDMODEL_INCLUDE} ${HOUDINI_SOPSTANFORDMODEL_SOURCE})
target_link_libraries(SOP_StanfordModel ${HOUDINI_SOPSTANFORDMODEL_LIBS})
