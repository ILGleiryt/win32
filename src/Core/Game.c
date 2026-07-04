#include <stdio.h>
#include "Game.h"
#include <stdbool.h>
#include "utility/Timer.h"

void game_update_viewport(Game* game);

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float uAspect;\n"
"void main()\n"
"{\n"
"   vec2 pos = vec2(aPos.x * uAspect, aPos.y);\n"
"   gl_Position = vec4(pos.x, pos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

static int frameCounter = 0; // stores frame count
static double lastTime = 0.0;

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
	timer_init();
	game->input.hwnd = game->window.hwnd;
	input_init(&game->input);
	game_update_viewport(game);
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

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float verticies[] = {
        -0.5f, -0.5f, 0.f,
         0.5f, -0.5f, 0.f,
         0.0f, 0.5f, 0.f,
        };

        unsigned int VBO, VAO;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

		int aspectLoc = glGetUniformLocation(shaderProgram, "uAspect");
		game_update_viewport(game);

	while (game->running)
	{
		if (!window_process_system_msg(&game->window))
		{
			game->running = false;
			break;
		}
		timer_update();

		game_update_viewport(game);
		float aspect = (float)game->window.window_width / game->window.window_height;// use ascpect ratio for correctly appearance
		{ // fps counter
			frameCounter++;
			double currentTime = timer_get_totaltime();
			if (currentTime - lastTime >= 1.0)
			{
				printf("FPS: %d\n", frameCounter);
				frameCounter = 0;
				lastTime = currentTime;
			}
		} // fpc counter

		double dt = timer_get_delta();

		//printf("Delta: %f ms\n", dt * 1000.0); // print elapsed miliseconds from render frame, currently 16.6-18 on my system with vsync
		
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

		static int diag_counter = 0;
		if (++diag_counter % 60 == 0) {
			RECT clientRect;
			GetClientRect(game->window.hwnd, &clientRect);
			printf("FULLSCREEN DIAG: w=%d, h=%d, aspect=%.2f\n",
				clientRect.right - clientRect.left,
				clientRect.bottom - clientRect.top,
				(float)(clientRect.right - clientRect.left) / (clientRect.bottom - clientRect.top));
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_update(dt); //
		glUseProgram(shaderProgram);
		glUniform1f(aspectLoc, aspect);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		render(&game->opengl);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

// this function maybe would be change to callback version
static void game_update_viewport(Game* game)
{
	RECT clientRect;
	GetClientRect(game->window.hwnd, &clientRect);
	game->window.window_width = clientRect.right - clientRect.left;
	game->window.window_height = clientRect.bottom - clientRect.top;
	glViewport(0, 0, game->window.window_width, game->window.window_height);
}