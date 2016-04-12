project(SOP_TestModel)

set(HOUDINI_SOP_TEST_MODEL_INCLUDE
    SOP_TestModel.h
    SOP_TestModelBunny.h
    SOP_TestModelDragon.h
    SOP_TestModelBuddha.h
)

set(HOUDINI_SOP_TEST_MODEL_SOURCE
    SOP_TestModel.C
    SOP_TestModelBunny.C
    SOP_TestModelDragon.C
    SOP_TestModelBuddha.C
)

if(APPLE)
	set(HOUDINI_SOP_TEST_MODEL_LIBS
		HoudiniUT
		HoudiniGEO
		HoudiniPRM
		HoudiniOP2
		boost_system
	)
elseif(WIN32)
	set(HOUDINI_SOP_TEST_MODEL_LIBS
    	${HOUDINI_SOP_TEST_MODEL_LINK_DIRECTORIES}/*.a
		${HOUDINI_SOP_TEST_MODEL_LINK_DIRECTORIES}/*.lib
	)
else()
	message(ERROR "Unsupported platform.")
endif()

add_definitions(
    -DUT_DSO_TAGINFO=\"3262197cbf1f501f2caa0ca8572890fb3e4b9bfcc021d8a873a8c3063d69ee812b972985db32267a5946addc2f8f31780eadf501ffc2e85149062ee263fe81be4baf508aff924994a3268d0847f848e6ab4e98a984ed956599\")

add_library(SOP_TestModel SHARED ${HOUDINI_SOP_TEST_MODEL_INCLUDE} ${HOUDINI_SOP_TEST_MODEL_SOURCE})
target_link_libraries(SOP_TestModel ${HOUDINI_SOP_TEST_MODEL_LIBS})
