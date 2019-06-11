
#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER



#include "Entity.hpp"

using namespace std;
using namespace glTools;
namespace btTools
{

	class Component
	{
	public:
		static int id_index;
		int id;
		//Entity* parent;
		//Entity entity;
		Component(shared_ptr<Entity> parent_entity)
		{ 
			//id = id_index;
			//id_index++;
			//parent = parent_entity;
			//parent_entity->addComponent(make_shared<Component>(this));
		}
	};


}

#endif