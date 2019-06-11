/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include "Vehicle.hpp"

namespace btTools
{

	Vehicle::Vehicle(shared_ptr<Entity>& parent, vector<shared_ptr<Entity>>& wheels_P, shared_ptr< btDiscreteDynamicsWorld > world)
	{
		parent->body->setActivationState(DISABLE_DEACTIVATION);
		chasis = parent;
		wheels = wheels_P;

		btVector3 anchor;
		btVector3 parentAxis(0.f, 1.f, 0.f);
		btVector3 childAxis(1.f, 0.f, 0.f);
		for (shared_ptr<Entity> wheel : wheels)
		{
			wheel->body->setActivationState(DISABLE_DEACTIVATION);
			wheel->body->setFriction(1);
			wheel->body->setAngularFactor(btVector3(1, 0.3, 0.3));
			anchor = wheel->body->getWorldTransform().getOrigin();
			shared_ptr<btHinge2Constraint> hinge(new btHinge2Constraint(*chasis->body, *wheel->body, anchor, parentAxis, childAxis));
			hinge->setLowerLimit(-SIMD_HALF_PI * 0.5f);
			hinge->setUpperLimit(SIMD_HALF_PI * 0.5f);
			hinge->enableMotor(3, true);
			hinge->setMaxMotorForce(3, 1000);
			hinge->setTargetVelocity(3, 0);
			world->addConstraint(hinge.get(), true);
			hinges.push_back(hinge);
		}
	}

	void Vehicle::setCatapultHinge(shared_ptr<btHingeConstraint> hinge)
	{
		catapult_hinge = hinge;
	}

}