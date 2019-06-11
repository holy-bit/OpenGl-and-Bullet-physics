/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include "Bullet_World_Controller.hpp"

namespace btTools
{

	btTools::Bullet_World_Controller& Bullet_World_Controller::getInstance()
	{
		static Bullet_World_Controller instance;
		return instance;
	}

	Bullet_World_Controller::Bullet_World_Controller() : collisionDispatcher(&collisionConfiguration)
	{
		CreateWorld();
	}

	void Bullet_World_Controller::CreateWorld()
	{
		/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
										   PHYSISCS WORLD INITIALIZATION
		\+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

		// Collision configuration contains default setup for memory, collision setup.
		// Advanced users can create their own configuration.

		// Create and configure the physiscs world:

		world.reset
		(
			new btDiscreteDynamicsWorld
			(
				&collisionDispatcher,
				&overlappingPairCache,
				&constraintSolver,
				&collisionConfiguration
			)
		);

		world->setGravity(btVector3(0, -10, 0));
	}

	void Bullet_World_Controller::update()
	{
		world->stepSimulation(1.f / 60.f);
		checkCollsions();
		for (map<string, shared_ptr< Entity > >::iterator it = entities.begin(); it != entities.end(); ++it)
			it->second->update();


		/*btTransform physics_transform;
		suelo->getMotionState()->getWorldTransform(physics_transform);

		glm::mat4 graphics_transform;

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		*models["suelo"]->transform.transformation(graphics_transform);*/
	}

	void Bullet_World_Controller::checkCollsions()
	{
		btTransform physics_transform;

		entities["platform"]->body->getMotionState()->getWorldTransform(physics_transform);
		btTransform physics_transform2;
		entities["wheel_FR"]->body->getMotionState()->getWorldTransform(physics_transform2);
		btScalar   z = physics_transform.getOrigin().getZ();
		btScalar   z_player = physics_transform2.getOrigin().getZ();
		int   manifold_count = world->getDispatcher()->getNumManifolds();
		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold* manifold = world->getDispatcher()->getManifoldByIndexInternal(i);


			btCollisionObject* object_a = (btCollisionObject*)(manifold->getBody0());
			btCollisionObject* object_b = (btCollisionObject*)(manifold->getBody1());

			int   numContacts = manifold->getNumContacts();

			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& point = manifold->getContactPoint(j);

				if (point.getDistance() < 0.f)
				{
					if ((object_a == entities["wheel_FR"]->body.get() && object_b == entities["platform"]->body.get()) || (object_a == entities["platform"]->body.get() && object_b == entities["wheel_FR"]->body.get()))
					{
						if (z > z_player)
						{
							entities["platform"]->body->setLinearVelocity(btVector3(0, 0, -1));
						}

					}
					if ((object_a == entities["suelo2"]->body.get() && object_b == entities["platform"]->body.get()) || (object_a == entities["platform"]->body.get() && object_b == entities["suelo2"]->body.get()))
					{

						entities["platform"]->body->setLinearVelocity(btVector3(0, 0, 0));
					}
					if ((object_a == entities["chasis"]->body.get() && object_b == entities["key"]->body.get()) || (object_a == entities["key"]->body.get() && object_b == entities["chasis"]->body.get()))
					{
						entities["key"]->body->translate(btVector3(1000, 1000, 1000));
						entities["gate"]->body->translate(btVector3(1000, 1000, 1000));
					}

				}
			}


		}
	}

	void Bullet_World_Controller::CreateEntities(map<string, shared_ptr<Model>>& models, int shape /*= BOX*/)
	{

		btTransform transform;

		for (map<string, shared_ptr< Model > >::iterator it = models.begin(); it != models.end(); ++it)
		{
			glm::vec3 location = it->second->transform.getLocation();
			glm::vec3 scale = it->second->transform.getScale();
			transform.setIdentity();
			transform.setOrigin(vector3(location[0], location[1], location[2]));
			btVector3 btscale(scale[0], scale[1], scale[2]);
			switch (shape)
			{
			case 0:
			{
				entities.insert(make_pair(it->first, make_shared<Entity>(Entity(it->second, world, transform, btscale, it->second->mass))));
				break;
			}
			case 1:
			{
				entities.insert(make_pair(it->first, make_shared<Entity>(Entity(it->second, world, transform, btscale, it->second->mass, new btSphereShape(btScalar(1.))))));
				break;
			}
			default:
				break;
			}

		}
	}

}

