/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3

#pragma once


#ifndef OBJ_LOADER_HEADER
#define OBJ_LOADER_HEADER

#include "Model.hpp"

namespace glTools
{
	class Obj_Loader : public Model
	{
		std::string error;

	public:

		//!Constructor que carga mallas desde un archivo obj.
		/*! <b>Method:  </b>     Obj_Loader */
		/*! <b>FullName:</b>     glTools::Obj_Loader::Obj_Loader */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   const std::string & obj_file_path Recibe el directorio del archivo a cargar.
		* @param   const string & texture_path
		* @param   glm::vec3 location
		* @param   glm::vec3 scale
		* @param   glm::vec3 rotation
		* @param   float mass
		* @return  
		*/
		Obj_Loader(const std::string & obj_file_path, const string& texture_path, glm::vec3 location = { 0,0,0 }, glm::vec3 scale = { 1,1,1 }, glm::vec3 rotation = { 0,0,0 }, float mass = 0);


		//! Comprueba que la carga es correcta.
		/*! <b>Method:  </b>     is_ok */
		/*! <b>FullName:</b>     glTools::Obj_Loader::is_ok */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  bool
		*/
		bool is_ok()
		{
			error.empty();
		}


		//! Devuelve el error que se ha producido.
		/*! <b>Method:  </b>     get_error */
		/*! <b>FullName:</b>     glTools::Obj_Loader::get_error */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  const std::string
		*/
		const std::string get_error() const
		{
			return error;
		}
	};
}


#endif