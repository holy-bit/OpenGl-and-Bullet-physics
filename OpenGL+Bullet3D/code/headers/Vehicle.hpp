/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#pragma once

#include "Entity.hpp"

using namespace std;
using namespace glTools;
namespace btTools
{
	class Vehicle
	{
	public:
		shared_ptr<Entity> chasis; /**< Entidad que se utiliza como chasis. */
		vector<shared_ptr<Entity>> wheels; /**< Entidades que sirven como ruedas. */
		vector<shared_ptr<btHinge2Constraint>> hinges; /**< Uniones de las ruedas. */
		shared_ptr<btHingeConstraint> catapult_hinge; /**< Union de la palanca de la catapulta. */


		//! Crea el vehiculo cogiendo la primera entidad como chasis y el vector como las ruedas del vehiculo.
		/*! <b>Method:  </b>     Vehicle */
		/*! <b>FullName:</b>     btTools::Vehicle::Vehicle */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   shared_ptr<Entity> & parent
		* @param   vector<shared_ptr<Entity>> & wheels_P
		* @param   shared_ptr< btDiscreteDynamicsWorld > world
		* @return  
		*/
		Vehicle(shared_ptr<Entity>& parent, vector<shared_ptr<Entity>>& wheels_P, shared_ptr< btDiscreteDynamicsWorld > world);


		//! Asigna un puntero a la union de la palanca de la catapulta.
		/*! <b>Method:  </b>     setCatapultHinge */
		/*! <b>FullName:</b>     btTools::Vehicle::setCatapultHinge */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   shared_ptr<btHingeConstraint> hinge
		* @return  void
		*/
		void setCatapultHinge(shared_ptr<btHingeConstraint> hinge);
	};


}
