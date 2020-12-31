cmake_minimum_required(VERSION 3.14)

project(G2D)

# adds "#define CMAKE_BUILD"
#add_definitions(-DG2D_CMAKE_BUILD)

set(SRC_FILES 

	main.c
	
	G2D/g2d.c

	Game/g_collisions.c
	Game/g_destroy.c
	Game/g_entities.c
	Game/g_init.c
	Game/g_player.c
	Game/g_render.c
    Game/g_scene.c
    Game/g_simulate.c
    Game/g_utils.c

	Render/r_draw_circle.c
	Render/r_draw_line.c
	Render/r_draw_point.c
	Render/r_draw_rect.c
	Render/r_draw_sprite.c
	Render/r_draw_triangle.c
	Render/r_utils.c
	Render/render.c

	Utils/utils.c
	
	Window/Win_32/w_callback.c
	Window/Win_32/w_create.c
	Window/Win_32/w_fps.c
	Window/Win_32/w_input.c
	Window/Win_32/w_input_keyboard.c
	Window/Win_32/w_input_mouse.c
	#Window/w_log.c
	Window/Win_32/w_render.c
	Window/Win_32/w_sprite.c
)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

#FILE(COPY soldier.bmp DESTINATION "${CMAKE_BINARY_DIR}/resources")
#FILE(COPY enemy.bmp DESTINATION "${CMAKE_BINARY_DIR}/resources")
