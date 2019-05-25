/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3

#pragma once


#ifndef OBJ_LOADER_HEADER
#define OBJ_LOADER_HEADER

#include "Model.hpp"

namespace example
{
	class Obj_Loader : public Model
	{
		std::string error;

	public:

		Obj_Loader(const std::string & obj_file_path, const string& texture_path);

		bool is_ok()
		{
			error.empty();
		}

		const std::string get_error() const
		{
			return error;
		}
	};
}


#endif