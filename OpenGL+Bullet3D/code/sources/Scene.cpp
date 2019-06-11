/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include "Scene.hpp"
#include <iostream>
#include <cassert>
#include "Entity.hpp"
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

using namespace btTools;
namespace glTools
{

  

    

    Scene::Scene(int width, int height)
    :
        angle(0),
		width(width),
		height(height),
		skybox("../../assets/sources/sky-cube-map-")
	{
		LoadModels(); //Cargamos los modelos y Entidades.

		CreateVehicle(); //Creamos el vehiculo

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
        glClearColor (0.f, 0.f, 0.f, 1.f);
		postpro.setupPostProcessing();

        resize (width, height);

    }

    void Scene::update ()
	{
		Bullet_World_Controller::getInstance().update();
		angle += 0.5f;

		models["parent"]->transform.setRotation(glm::vec3(3*angle, 0, 0));
		
		
		angle_around_x += angle_delta_x;
		angle_around_y += angle_delta_y;

		if (angle_around_x < -1)
		{
			angle_around_x = -1;
		}
		else
			if (angle_around_x > +1)
			{
				angle_around_x = +1;
			}

		glm::mat4 camera_rotation;

		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(0.f, -1.f, 0.f));
		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(-1.f, 0.f, 0.f));


		camera.set_target(0,0,-1);
		camera.rotate(camera_rotation);
		camera.move(direction);
		
		
    }

    void Scene::render ()
    {
		glBindFramebuffer(GL_FRAMEBUFFER, postpro.FBO);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.5f, .5f, .5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.render(camera);
		for (map<string, shared_ptr< Model > >::iterator it = models.begin(); it != models.end(); ++it) it->second->render(camera);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		
		glClear(GL_COLOR_BUFFER_BIT);

		postpro.shader_program->use();
		glBindVertexArray(postpro.VAO);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, postpro.TBO);	// use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		

    }

    void Scene::resize (int new_width, int new_height)
    {
		width = new_width;
		height = new_height;

		camera.set_ratio(float(width) / height);

		glViewport(0, 0, width, height);
    }


	void Scene::LoadModels()
	{
		map<string, shared_ptr<Model>> models_sphere; /**< mapa temporal de los modelos para que tendran una colision esferica*/

		models.insert(make_pair("suelo", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//rocks.tga", glm::vec3(0, -5, -20), glm::vec3(9, 1, 9), glm::vec3(0, 0, 0), 0))));

		models.insert(make_pair("suelo2", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//rocks.tga", glm::vec3(0, -5, -70), glm::vec3(10, 1, 15), glm::vec3(0, 0, 0), 0))));
		models.insert(make_pair("suelo3", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//rocks.tga", glm::vec3(0, -5, -110), glm::vec3(10, 1, 10), glm::vec3(0, 0, 0), 0))));
		models.insert(make_pair("gate", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wall.tga", glm::vec3(0, 0, -80), glm::vec3(10, 10, 1), glm::vec3(0, 0, 0), 1))));
		models.insert(make_pair("key", make_shared<Model>(Obj_Loader("..//..//assets//sources//key.obj", "..//..//assets//sources//key.tga", glm::vec3(0, -3, -65), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));
		models.insert(make_pair("wall", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wall.tga", glm::vec3(0, -3, -110), glm::vec3(1, 3, 1), glm::vec3(0, 0, 0), 1))));
		models.insert(make_pair("chasis", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wood.tga", glm::vec3(0, 5, -13.5), glm::vec3(3, 0.5, 3), glm::vec3(0, 0, 0), 100))));
		models_sphere.insert(make_pair("wheel_FL", make_shared<Model>(Obj_Loader("..//..//assets//sources//sphere.obj", "..//..//assets//sources//wood.tga", glm::vec3(-2, 3, -15), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));
		models_sphere.insert(make_pair("wheel_BL", make_shared<Model>(Obj_Loader("..//..//assets//sources//sphere.obj", "..//..//assets//sources//wood.tga", glm::vec3(-2, 3, -12), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));
		models_sphere.insert(make_pair("wheel_FR", make_shared<Model>(Obj_Loader("..//..//assets//sources//sphere.obj", "..//..//assets//sources//wood.tga", glm::vec3(2, 3, -15), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));
		models_sphere.insert(make_pair("wheel_BR", make_shared<Model>(Obj_Loader("..//..//assets//sources//sphere.obj", "..//..//assets//sources//wood.tga", glm::vec3(2, 3, -12), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));
		models.insert(make_pair("platform", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//rocks.tga", glm::vec3(0, -5, -32), glm::vec3(5, 1, 5), glm::vec3(0, 0, 0), 1))));
		models.insert(make_pair("catapult", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wood.tga", glm::vec3(0, 6, -12.5), glm::vec3(1, 0.5, 3), glm::vec3(0, 0, 0), 1))));
		models_sphere.insert(make_pair("ball", make_shared<Model>(Obj_Loader("..//..//assets//sources//sphere.obj", "..//..//assets//sources//ball.tga", glm::vec3(0, -10, -20), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1))));

		Bullet_World_Controller::getInstance().CreateEntities(models);
		Bullet_World_Controller::getInstance().CreateEntities(models_sphere, Shape::SPHERE);

		Bullet_World_Controller::getInstance().entities["gate"]->body->setLinearFactor(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["gate"]->body->setAngularFactor(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["gate"]->body->setGravity(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["key"]->body->setLinearFactor(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["key"]->body->setAngularFactor(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["key"]->body->setGravity(btVector3(0, 0, 0));
		Bullet_World_Controller::getInstance().entities["key"]->model->transform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
		shared_ptr< btRigidBody > platform = Bullet_World_Controller::getInstance().entities["platform"]->body;

		platform->setActivationState(DISABLE_DEACTIVATION);
		platform->setLinearFactor(btVector3(0, 0, 0));
		platform->setAngularFactor(btVector3(0, 0, 0));
		platform->setGravity(btVector3(0, 0, 0));

		models.insert(models_sphere.begin(), models_sphere.end()); //juntamos los el mapa de modelos con el de los modelos esfericos.

		models.insert(make_pair("parent", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wall.tga", glm::vec3(3, 6, -20.5)))));
		models.insert(make_pair("particula", make_shared<Model>(Obj_Loader("..//..//assets//sources//cube.obj", "..//..//assets//sources//wall.tga", glm::vec3(0, 1, -3)))));
		models["particula"]->setParent(*models["parent"]);
	}

	void Scene::CreateVehicle()
	{
		vector<shared_ptr<Entity>> wheels;
		wheels.push_back(Bullet_World_Controller::getInstance().entities["wheel_FL"]);
		wheels.push_back(Bullet_World_Controller::getInstance().entities["wheel_BL"]);
		wheels.push_back(Bullet_World_Controller::getInstance().entities["wheel_FR"]);
		wheels.push_back(Bullet_World_Controller::getInstance().entities["wheel_BR"]);

		vehicle = make_shared<Vehicle>(Vehicle(Bullet_World_Controller::getInstance().entities["chasis"], wheels,Bullet_World_Controller::getInstance().world));

		shared_ptr< btRigidBody > chasis = vehicle->chasis->body;

		btVector3 anchor;
		btVector3 parentAxis(-1.f, 0.f, 0.f);
		btVector3 childAxis(-1.f, 0.f, 0.f);
		anchor = chasis->getWorldTransform().getOrigin();
		shared_ptr<btHingeConstraint>hinge = make_shared<btHingeConstraint>(btHingeConstraint(*chasis, *Bullet_World_Controller::getInstance().entities["catapult"]->body, btVector3(0, 0.5, 1), btVector3(0, -0.5, -2.f), parentAxis, childAxis));

		vehicle->setCatapultHinge(hinge);

		hinge->setLimit(-1.2f, 0.0f);
		Bullet_World_Controller::getInstance().world->addConstraint(hinge.get(), true);
	}

	void Scene::on_key()
	{
		glm::vec3 cameraFront = { camera.get_target()[0],camera.get_target()[1],camera.get_target()[2] };
		float cameraSpeed = 0.05f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = cameraSpeed * cameraFront;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = -(glm::normalize(glm::cross(cameraFront, { 0,1,0 })) * cameraSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = -(cameraSpeed * cameraFront);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = glm::normalize(glm::cross(cameraFront, { 0,1,0 })) * cameraSpeed;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			vehicle->hinges[0]->setTargetVelocity(3, 1);
			vehicle->hinges[1]->setTargetVelocity(3, 1);
			vehicle->hinges[2]->setTargetVelocity(3, 1);
			vehicle->hinges[3]->setTargetVelocity(3, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			vehicle->hinges[0]->setTargetVelocity(3, -1);
			vehicle->hinges[1]->setTargetVelocity(3, -1);
			vehicle->hinges[2]->setTargetVelocity(3, -1);
			vehicle->hinges[3]->setTargetVelocity(3, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			vehicle->hinges[0]->setTargetVelocity(3, -1);
			vehicle->hinges[1]->setTargetVelocity(3, -1);
			vehicle->hinges[2]->setTargetVelocity(3,  1);
			vehicle->hinges[3]->setTargetVelocity(3,  1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			vehicle->hinges[0]->setTargetVelocity(3,  1);
			vehicle->hinges[1]->setTargetVelocity(3,  1);
			vehicle->hinges[2]->setTargetVelocity(3, -1);
			vehicle->hinges[3]->setTargetVelocity(3, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			btTransform position = Bullet_World_Controller::getInstance().entities["chasis"]->body->getWorldTransform();
			Bullet_World_Controller::getInstance().entities["ball"]->body->clearForces();
			Bullet_World_Controller::getInstance().entities["ball"]->body->setLinearVelocity(btVector3(0, 0, 0));
			Bullet_World_Controller::getInstance().entities["ball"]->body->setAngularVelocity(btVector3(0, 0, 0));
			Bullet_World_Controller::getInstance().entities["ball"]->body->setWorldTransform(Bullet_World_Controller::getInstance().entities["chasis"]->body->getWorldTransform());
			Bullet_World_Controller::getInstance().entities["ball"]->body->translate(btVector3(0, 4, 3.f));

			vehicle->catapult_hinge->enableMotor(true);
			vehicle->catapult_hinge->setMaxMotorImpulse(10);
		}
	}

	void Scene::on_drag(int pointer_x, int pointer_y)
	{

		if (pointer_pressed)
		{
			angle_delta_x = 0.01f * float(last_pointer_x - pointer_x) / float(width);
			angle_delta_y = 0.01f * float(last_pointer_y - pointer_y) / float(height);
		}
	}

	void Scene::on_click(int pointer_x, int pointer_y, bool down)
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

	void Scene::on_key_realeased()
	{
		vehicle->hinges[0]->setTargetVelocity(3, 0);
		vehicle->hinges[1]->setTargetVelocity(3, 0);
		vehicle->hinges[2]->setTargetVelocity(3, 0);
		vehicle->hinges[3]->setTargetVelocity(3, 0);
		direction = { 0,0,0 };
		vehicle->catapult_hinge->enableMotor(false);
	}

}
