
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Scene.hpp"
#include <iostream>
#include <cassert>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example
{

    using namespace std;

    

    Scene::Scene(int width, int height)
    :
        angle(0),
		width(width),
		height(height),
		skybox("../../assets/sources/sky-cube-map-")
    {
        // Se establece la configuración básica:
		models.push_back(Obj_Loader("..//..//assets//sources//cube_UV2.obj", "..//..//assets//sources//rocks.tga"));
		models.push_back(Obj_Loader("..//..//assets//sources//key.obj", "..//..//assets//sources//uv-checker-1.tga"));


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
        glClearColor (0.f, 0.f, 0.f, 1.f);

		models[1].setParent(&models[0]);
		

        resize (width, height);
    }

    void Scene::update ()
	{
		angle += 0.5f;
		models[0].transform.Rotation(glm::vec3(angle, angle, 0));
		models[1].transform.Rotation(glm::vec3(3*angle, 0, 0));
		models[0].transform.Location(glm::vec3(0, 0, -20));
		models[1].transform.Location(glm::vec3(5, 0, 0));
		models[1].transform.Scale(glm::vec3(0.2, 0.2, 0.2));
		for (Model& model : models) model.update(camera);
		angle_around_x += angle_delta_x;
		angle_around_y += angle_delta_y;

		if (angle_around_x < -0.5)
		{
			angle_around_x = -0.5;
		}
		else
			if (angle_around_x > +0.5)
			{
				angle_around_x = +0.5;
			}

		glm::mat4 camera_rotation;

		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(0.f, -1.f, 0.f));
		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(-1.f, 0.f, 0.f));

		glm::vec3 front;
		front.z = cos(glm::radians(angle_around_y)) * cos(glm::radians(angle_around_x));
		front.y = sin(glm::radians(angle_around_x));
		front.x = sin(glm::radians(angle_around_y)) * cos(glm::radians(angle_around_y));
		front = glm::normalize(front);

		camera.set_target(front.x, front.y, -front.z);
		camera.rotate(camera_rotation);
		camera.move(direction);
		
		
    }

    void Scene::render ()
    {
		glClearColor(0.5f, .5f, .5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.render(camera);
		for (Model& model : models) model.render(camera);

    }

    void Scene::resize (int new_width, int new_height)
    {
		width = new_width;
		height = new_height;

		camera.set_ratio(float(width) / height);

		glViewport(0, 0, width, height);
    }


}
