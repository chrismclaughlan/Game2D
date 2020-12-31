set(G2D_SOURCE_FILES
	
	g2d.c

	Render/r_draw_circle.c
	Render/r_draw_line.c
	Render/r_draw_point.c
	Render/r_draw_rect.c
	Render/r_draw_sprite.c
	Render/r_draw_triangle.c
	Render/r_utils.c

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

add_library(G2D_lib STATIC ${G2D_SOURCE_FILES})

target_include_directories(G2D_lib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/headers 
	${CMAKE_CURRENT_SOURCE_DIR}/Render/headers
	${CMAKE_CURRENT_SOURCE_DIR}/Utils/headers
	${CMAKE_CURRENT_SOURCE_DIR}/Win_32/headers
)