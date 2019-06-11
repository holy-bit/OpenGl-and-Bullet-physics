/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include "Entity.hpp"

namespace btTools
{

	Entity::Entity(shared_ptr<Model> model_P, shared_ptr< btDiscreteDynamicsWorld> world, btTransform& startTransform, btVector3 size_P, float mass, btCollisionShape* shape_P)
	{
		worldP = world;

		bool isDynamic = mass != 0 ? true : false;

		if (!shape_P)
			 collisionShape.reset(new btBoxShape(size_P));
		else collisionShape.reset(shape_P);


		btVector3 localInertia(0, 0, 0);

		if (isDynamic)
			collisionShape->calculateLocalInertia(mass, localInertia);

		state.reset(new btDefaultMotionState(startTransform));

		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), collisionShape.get(), localInertia);
		body.reset(new btRigidBody(info));
		body->setRestitution(0.2);

		world->addRigidBody(body.get()); // Se añade el body al mundo dinamico.

		if (isDynamic)
			body->setActivationState(DISABLE_DEACTIVATION); //Si es un cuerpo dinamico desahbilitamos que se pueda dormir.

		model = model_P;
		model->isEntity = true;
	}

	void Entity::update()
	{
		// Aplicamos las transformaciones fisicas al modelo grafico:
		body->getMotionState()->getWorldTransform(physics_transform);
		physics_transform.getOpenGLMatrix(glm::value_ptr(model->transform.transformation));
	}

	void Entity::destroy()
	{
		worldP->removeRigidBody(body.get());
	}

}