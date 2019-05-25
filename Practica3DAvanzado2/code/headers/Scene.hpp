
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <GL/glew.h>            // Debe incluirse antes que gl.h
    #include "Cube.hpp"
#include <SFML/Window.hpp>
#include "Camera.hpp"
#include "Obj_Loader.hpp"
    #include <string>
#include "Skybox.hpp"

    namespace example
    {

        class Scene
        {
        private:

			

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;


			Camera camera;
			Skybox skybox;
            GLint  model_view_matrix_id;
            GLint  projection_matrix_id;
			GLint  normal_matrix_id;
			vector<Model> models; /**< Lista de los modelos en la view */
            //Cube   cube;
            float  angle;

			int    width;
			int    height; 

			float  angle_around_x;
			float  angle_around_y;
			float  angle_delta_x;
			float  angle_delta_y;

			bool   pointer_pressed;
			int    last_pointer_x;
			int    last_pointer_y;
			

        public:

            Scene(int width, int height);

            void   update ();
            void   render ();
            void   resize (int width, int height);

        private:

           
		public:
			glm::vec3 direction;
			void on_key(int key_code)
			{
				glm::vec3 cameraFront = { camera.get_target()[0],camera.get_target()[1],camera.get_target()[2] };
				float cameraSpeed = 0.05f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = cameraSpeed * cameraFront;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = -(glm::normalize(glm::cross(cameraFront, {0,1,0})) * cameraSpeed);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = -(cameraSpeed * cameraFront);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = glm::normalize(glm::cross(cameraFront, { 0,1,0 })) * cameraSpeed;
			}

			void on_drag(int pointer_x, int pointer_y)
			{
				
				if (pointer_pressed)
				{
					angle_delta_x = 0.01f * float(last_pointer_x - pointer_x) / float(width);
					angle_delta_y = 0.01f * float(last_pointer_y - pointer_y) / float(height);
				}
			}

			void on_click(int pointer_x, int pointer_y, bool down)
			{

				if ((pointer_pressed = down) == true)
				{
					last_pointer_x = pointer_x;
					last_pointer_y = pointer_y;
				}
				else
				{
					angle_delta_x = angle_delta_y = 0.0;
				}
			}

        };

    }

#endif
