/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3
#pragma once


#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "Mesh.hpp"
#include <list>
#include <memory>
#include "Camera.hpp"
#include <iostream>
#include "Shader_Program.hpp"
#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"
using namespace toolkit;
using namespace std;
using namespace glm;
namespace glTools
{
	

	class Model
	{


		
		//* Transform Struct.
		/** Guarda la escala, rotacion, position y tranformacion*/
		struct Transform
		{
		private:
			glm::vec3     location{};/**< Posicion. */
			glm::vec3     rotation{};/**< rotacion. */
			glm::vec3     scale{ 1,1,1 };/**< Escala. */

		public:
			glm::vec3 getLocation() const { return location; }
			void setLocation(glm::vec3 val) { location = val; }

			
			glm::vec3 getRotation() const { return rotation; }
			void setRotation(glm::vec3 val) { rotation = val; }

			glm::vec3 getScale() const { return scale; }
			void setScale(glm::vec3 val) { scale = val; }

			glm::mat4     transformation;/**< Transformacion. */
			
			void setTransformValues(vec3 location, vec3 rotation, vec3 scale) { setLocation(location); setRotation(rotation); setScale(scale); }
		};
		
	private:
		shared_ptr< Shader_Program > shader_program; /**< Shader_Program para gestionar los shaders del modelo. */
		std::list<Mesh> meshes;/**< Lista de todas las mallas del modelo. */

	public:
		bool isEntity;
		float mass;
		Model* parent = nullptr; /**< Puntero al modelo padre. */ 
		Transform transform; /**< Transform que contiene las distintas transformaciones del modelo */
		GLint  model_view_matrix_id; /**< id del model_view_matrix del vertex_shader */
		GLint  projection_matrix_id; /**< id del projection_matrix del vertex_shader */
		GLint  normal_matrix_id; /**< id del normal_matrix del vertex_shader */



		//! Crea el modelo estableciendo sus valores de transformacion.
		/*! <b>Method:  </b>     Model */
		/*! <b>FullName:</b>     glTools::Model::Model */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   glm::vec3 location
		* @param   glm::vec3 scale
		* @param   glm::vec3 rotation
		* @param   float mass_p
		* @return  
		*/
		Model(glm::vec3 location = {0,0,0}, glm::vec3 scale = { 1,1,1 }, glm::vec3 rotation = { 0,0,0 }, float mass_p = 0);

	

		//! Aplica rotacion en el eje X.
		/*! <b>Method:  </b>     rotate_around_x */
		/*! <b>FullName:</b>     glTools::Model::rotate_around_x */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float angle angulo al que va a rotar;
		* @return  void
		*/
		void rotate_around_x(float angle);
		
		//! Aplica rotacion en el eje Y
		/*! <b>Method:  </b>     rotate_around_y */
		/*! <b>FullName:</b>     glTools::Model::rotate_around_y */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float angle angulo al que va a rotar;
		* @return  void
		*/
		void rotate_around_y(float angle);

		//! Aplica rotacion en el eje Z
		/*! <b>Method:  </b>     rotate_around_z */
		/*! <b>FullName:</b>     glTools::Model::rotate_around_z */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float angle angulo al que va a rotar;
		* @return  void
		*/
		void rotate_around_z(float angle);
		

		//! Devuelve la lista de mallas del modelo.
		/*! <b>Method:  </b>     get_meshes */
		/*! <b>FullName:</b>     glTools::Model::get_meshes */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  std::list<glTools::Mesh>&
		*/
		std::list<Mesh>& get_meshes();


		/**
		*	Establece un puntero al modelo que va a ser el padre.
		*   @param Model* Puntero al modelo padre.
		*/
		//! Establece un puntero al modelo que va a ser el padre.
		/*! <b>Method:  </b>     setParent */
		/*! <b>FullName:</b>     glTools::Model::setParent */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   Model & parent_parameter Puntero al modelo padre.
		* @return  void
		*/
		void setParent(Model& parent_parameter);

		


		//! Calcula la matriz de transformacion.
		/*! <b>Method:  </b>     GetTransformMatrix */
		/*! <b>FullName:</b>     glTools::Model::GetTransformMatrix */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   const Camera & camera
		* @return  glm::mat4
		*/
		glm::mat4 GetTransformMatrix(const Camera& camera);


		//! Actualiza el modelo
		/*! <b>Method:  </b>     update */
		/*! <b>FullName:</b>     glTools::Model::update */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   const Camera & camera
		* @return  void
		*/
		void update(const Camera& camera);


		//! Dibuja el modelo.
		/*! <b>Method:  </b>     render */
		/*! <b>FullName:</b>     glTools::Model::render */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   const Camera & camera
		* @return  void
		*/
		void render(const Camera& camera);


		//! Asigna los valores al shader.
		/*! <b>Method:  </b>     SetShaderValues */
		/*! <b>FullName:</b>     glTools::Model::SetShaderValues */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   const Camera & camera
		* @return  void
		*/
		void SetShaderValues(const Camera& camera);


		//! Configura el material que se le aplicara al modelo.
		/*! <b>Method:  </b>     configure_material */
		/*! <b>FullName:</b>     glTools::Model::configure_material */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   GLuint program_id
		* @return  void
		*/
		void configure_material(GLuint program_id);


		//! Configura la luz que se le aplicara al modelo.
		/*! <b>Method:  </b>     configure_light */
		/*! <b>FullName:</b>     glTools::Model::configure_light */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   GLuint program_id
		* @return  void
		*/
		void configure_light(GLuint program_id);

		
	};
}


#endif


