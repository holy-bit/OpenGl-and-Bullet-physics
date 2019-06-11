/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <iostream>
#include "Model.hpp"
#include <btBulletDynamicsCommon.h>


using namespace std;
using namespace glTools;
namespace btTools 
{

	class Entity
	{
	public:

		btTransform physics_transform; /**< Transform al que se le aplica las fisicas de bullet. */

		shared_ptr<Model> model; /**< Modelo grafico de la entidad. */

		shared_ptr< btRigidBody > body; /**< Cuerpo fisico de la entidad. */
		shared_ptr< btDefaultMotionState > state; /**< Motion state de la entidad. */
		shared_ptr< btCollisionShape     > collisionShape; /**< La forma de la colision del cuerpo. */

		shared_ptr< btDiscreteDynamicsWorld> worldP;

	public:

		//! Constructor de la entidad, crea la colision el cuerpo y el motion state.
		/*! <b>Method:  </b>     Entity */
		/*! <b>FullName:</b>     btTools::Entity::Entity */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   shared_ptr<Model> model_P
		* @param   shared_ptr< btDiscreteDynamicsWorld> world
		* @param   btTransform & startTransform
		* @param   btVector3 size_P
		* @param   float mass
		* @param   btCollisionShape * shape_P
		* @return  this
		*/
		Entity(shared_ptr<Model> model_P, shared_ptr< btDiscreteDynamicsWorld> world, btTransform& startTransform, btVector3 size_P = { 1,1,1 }, float mass = 0, btCollisionShape* shape_P = nullptr);
		

		//! Actualiza la entidad.
		/*! <b>Method:  </b>     update */
		/*! <b>FullName:</b>     btTools::Entity::update */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  void
		*/
		void update();


		//! Destruye el cuerpo fisico de la entidad.
		/*! <b>Method:  </b>     destroy */
		/*! <b>FullName:</b>     btTools::Entity::destroy */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  void
		*/
		void destroy();

	};
}

#endif