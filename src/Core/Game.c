#include <stdio.h>
#include "Game.h"
#include <stdbool.h>

bool game_init(Game* game,  const wchar_t* wnd_title, const int wnd_width, const int wnd_height)
{
	if (!game) return false;

	game->running = false;

	if (!window_init(&game->window, wnd_title, wnd_width, wnd_height))
	{
		printf("Failed to initialize Window!\n");
		return false;
	}
	if (!gl_init(&game->opengl, window_get_handle(&game->window)))
	{
		printf("Failed to initialize OpenGL!\n");
		game->running = false;
		return false;
	}
	game->input.hwnd = game->window.hwnd;
	input_init(&game->input);
	glViewport(0, 0, wnd_width, wnd_height);
	game->running = true;
	
	return true;
}

void game_shutdown(Game* game)
{
	if (!game) return;
	
	game->running = false;
	gl_exit(&game->opengl);
	window_shutdown(&game->window);
}

void game_gameloop(Game* game)
{
	if (!game || !game->running) return;

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	
	if (!gl_make_current(&game->opengl))
	{
		printf("MakeCurrent failed!\n");
		return;
	}
		
	while (game->running)
	{
		if (!window_process_system_msg(&game->window))
		{
			game->running = false;
			break;
		}

		input_update(&game->input);

		if (input_is_key_pressed(&game->input, 'E')) {
			window_resize(&game->window, 512, 360);
		}
		if (input_is_key_pressed(&game->input, 'R')) {
			window_set_fullscreen(&game->window, true, true);
		}
		if (is_mouse_keydown(&game->input, VK_LBUTTON))
		{
			printf("left mouse clicked\n");
		}
		if (is_mouse_keydown(&game->input, VK_RBUTTON))
		{
			printf("right mouse clicked\n");
		}

		render_update(1.f);
		render(&game->opengl);
	}
}