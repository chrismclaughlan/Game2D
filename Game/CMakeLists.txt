set(GAME_SOURCE_FILES
	
	../main.c

	g_collisions.c
	g_destroy.c
	g_entities.c
	g_init.c
	g_player.c
	g_render.c
	g_scene.c
	g_simulate.c
	g_sprite.c
	g_utils.c

	resources/sound.rc
)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DRESOURCES_DIR="resources/")

# Copy all .bmp files to resource dir
file(GLOB ResourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.bmp)
foreach(ResourceFile ${ResourceFiles})
	file(COPY ${ResourceFile} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
endforeach()

set(G2D_EXTERNAL_DEPENDENCIES
	winmm.lib
	Kernel32.lib
)

add_executable(game WIN32 ${GAME_SOURCE_FILES})
target_link_libraries(game PUBLIC G2D_lib ${G2D_EXTERNAL_DEPENDENCIES})