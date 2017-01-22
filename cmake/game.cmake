set (GAME_SOURCE
	source/main.cpp
)

set (GAME_LIBS
	glfw
	OpenSimplexNoise
	GLEW
)

set (GAME_INCLUDES 
	source
	thirdparty/glew/include
	thirdparty/glfw/include
	thirdparty/glm
	thirdparty/openSimplexNoise
)

if (WIN32)
	set (GAME_LIBS
		${GAME_LIBS}
		OpenGL32
	)
endif()

add_executable(CPPCraft ${GAME_SOURCE})
target_link_libraries(CPPCraft ${GAME_LIBS})
target_include_directories(CPPCraft PUBLIC ${GAME_INCLUDES})
target_compile_definitions(CPPCraft PUBLIC GLEW_STATIC)