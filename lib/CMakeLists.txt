set(G2D_SOURCE_FILES
	
	G2D/g2d.c

	G2D/Render/r_draw_circle.c
	G2D/Render/r_draw_line.c
	G2D/Render/r_draw_point.c
	G2D/Render/r_draw_rect.c
	G2D/Render/r_draw_sprite.c
	G2D/Render/r_draw_triangle.c
	G2D/Render/r_utils.c

	G2D/Utils/u_other.c
	G2D/Utils/u_vector.c

	G2D/Window/Win32/w_win32_callback.c
	G2D/Window/Win32/w_win32_create.c
	G2D/Window/Win32/w_win32_destroy.c
	G2D/Window/Win32/w_win32_fps.c
	G2D/Window/Win32/w_win32_input.c
	G2D/Window/Win32/w_win32_input_keyboard.c
	G2D/Window/Win32/w_win32_input_mouse.c
	G2D/Window/Win32/w_win32_render.c
	G2D/Window/Win32/w_win32_sound.c
	G2D/Window/Win32/w_win32_sprite.c
	G2D/Window/Win32/w_win32_utils.c
	#G2D/Window/w_log.c
)

add_library(G2D_lib STATIC ${G2D_SOURCE_FILES})

target_include_directories(G2D_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/g2d.h)
#${CMAKE_CURRENT_SOURCE_DIR}/headers 
#${CMAKE_CURRENT_SOURCE_DIR}/Render/headers
#${CMAKE_CURRENT_SOURCE_DIR}/Utils/headers
#${CMAKE_CURRENT_SOURCE_DIR}/Win32/headers
#)