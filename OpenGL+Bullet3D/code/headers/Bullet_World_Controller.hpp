/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#ifndef BULLET_WORLD_CONTROLLER_HEADER
#define BULLET_WORLD_CONTROLLER_HEADER



#include "Entity.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>


using namespace std;
namespace btTools
{
	typedef btVector3 vector3;

	/**
	 * Enumeracion para marcar la forma de la colision.
	 */
	enum Shape
	{
		BOX = 0, /**< Colision con forma de cubo. */
		SPHERE = 1 /**< Colision con forma de esfera. */
	};

	class Bullet_World_Controller
	{
	public:

		map<string, shared_ptr<Entity>> entities; /**< Entidades del mundo. */
		shared_ptr< btDiscreteDynamicsWorld > world; /**< Puntero al mundo dinamico. */

	private:

		// Collision configuration contains default setup for memory, collision setup.
		btDefaultCollisionConfiguration collisionConfiguration;

		// Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

		btCollisionDispatcher collisionDispatcher;

		// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

		btDbvtBroadphase overlappingPairCache;

		// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

		btSequentialImpulseConstraintSolver constraintSolver;

		//! Constructor de la clase llama a la funcion CreateWorld().
		/*! <b>Method:  </b>     Bullet_World_Controller */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::Bullet_World_Controller */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  
		*/
		Bullet_World_Controller();

	public:

		//! Devuelve una referencia al singleton de controlador del mundo
		/*! <b>Method:  </b>     getInstance */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::getInstance */
		/*! <b>Access:  </b>     public static  */
		/**
		* @return  btTools::Bullet_World_Controller&
		*/
		static Bullet_World_Controller& getInstance();

		//! Actualiza el mundo y a sus entidades.
		/*! <b>Method:  </b>     update */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::update */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  void
		*/
		void update();

		//! Crea las entidades para darle a los modelos colisiones y añadirlos al mundo.
		/*! <b>Method:  </b>     CreateEntities */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::CreateEntities */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   map<string
		* @param   shared_ptr<Model>> & models
		* @param   int shape
		* @return  void
		*/
		void CreateEntities(map<string, shared_ptr<Model>>& models, int shape = BOX);

	private:

		//! Crea el mundo dinamico.
		/*! <b>Method:  </b>     CreateWorld */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::CreateWorld */
		/*! <b>Access:  </b>     private  */
		/**
		* @return  void
		*/
		void CreateWorld();

		//!Comprueba las colisiones que se generan en el mundo.
		/*! <b>Method:  </b>     checkCollsions */
		/*! <b>FullName:</b>     btTools::Bullet_World_Controller::checkCollsions */
		/*! <b>Access:  </b>     private  */
		/**
		* @return  Comprueba las colisiones que se generan en el mundo
		*/
		void checkCollsions();
	};
}

#endif