/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include <cassert>
#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Scene.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


using namespace sf;



int main ()
{

	// Se crea la ventana de SFML, que es donde se creará el contexto de OpenGL:

	Window window(VideoMode(1920, 1080), "OpenGL Examples: Simple Cube", Style::Default, ContextSettings(32));

	// Una vez se ha creado el contexto de OpenGL ya se puede inicializar Glew:

	GLenum glew_initialization = glewInit();

	assert(glew_initialization == GLEW_OK);

	// Glew se inicializa antes de crear view porque view ya usa extensiones de OpenGL:

	Scene scene(1920, 1080);

	window.setVerticalSyncEnabled(true);

	bool running = true;


    do
    {
        Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
				{
					running = false;
					break;
				}

				case Event::Resized:
				{
					Vector2u window_size = window.getSize();
					scene.resize(window_size.x, window_size.y);
					break;
				}

				case Event::KeyPressed:
				{
					scene.on_key();
					break;
				}

				case Event::KeyReleased:
				{
					scene.on_key_realeased();
					break;
				}

				case Event::MouseButtonPressed:
				{
					scene.on_click(event.mouseButton.x, event.mouseButton.y, true);
					break;
				}

				case Event::MouseButtonReleased:
				{
					scene.on_click(event.mouseButton.x, event.mouseButton.y, false);
					break;
				}

				case Event::MouseMoved:
				{
					scene.on_drag(event.mouseMove.x, event.mouseMove.y);
					break;
				}

			}
		}

        glClear (GL_COLOR_BUFFER_BIT);

        scene.update ();
        scene.render ();

        window.display ();
    }
    while (running);
    return (EXIT_SUCCESS);
}
