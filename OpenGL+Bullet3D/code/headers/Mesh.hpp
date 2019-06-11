/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3


#pragma once

#ifndef MESH_HEADER
#define MESH_HEADER
#include <GL/glew.h> 
#include <SFML/OpenGL.hpp>
#include <Vector>
#include <memory>
#include <Point.hpp>
#include <cmath>
#include "Color_Buffer_Rgba8888.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include <random>

using namespace std;
using namespace toolkit;


extern "C"
{
#include <targa.h>
}

namespace glTools
{
	class Mesh
	{
		typedef Color_Buffer_Rgba8888 Texture;
	public:
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

	public:
		/*  Mesh Data  */
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		unsigned int VAO;
		std::shared_ptr< Texture > texture;

		bool has_texture;
		GLuint texture_id;
		
		//void Draw(Shader shader);
		
	private:
		/*  Render data  */
		unsigned int VBO, EBO;
		/*  Functions    */
		

	public:


		//! Crea la malla 
		/*! <b>Method:  </b>     Mesh */
		/*! <b>FullName:</b>     glTools::Mesh::Mesh */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   vector<Vertex> vertices
		* @param   vector<unsigned int> indices
		* @param   const string & texture_path
		* @return  
		*/
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, const string& texture_path);

		//! Carga todos los datos de la malla a OpenGL.
		/*! <b>Method:  </b>     setupMesh */
		/*! <b>FullName:</b>     glTools::Mesh::setupMesh */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  void
		*/
		void setupMesh();

		//! Dibuja la malla.
		/*! <b>Method:  </b>     Draw */
		/*! <b>FullName:</b>     glTools::Mesh::Draw */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  void
		*/
		void Draw();


		std::shared_ptr< Texture > load_texture(const std::string& texture_path)
		{
			std::shared_ptr< Texture > buffer;

			// Se carga el archivo TGA:

			tga_image loaded_image;

			if (tga_read(&loaded_image, texture_path.c_str()) == TGA_NOERR)
			{
				// Se crea un búfer con el formato de píxel adecuado:

				buffer.reset(new Texture(loaded_image.width, loaded_image.height));

				// Se convierte el búfer de la imagen cargada al formato de píxel adecuado:

				tga_convert_depth(&loaded_image, buffer->bits_per_color());
				tga_swap_red_blue(&loaded_image);

				Texture::Color* loaded_image_pixels = reinterpret_cast<Texture::Color*>(loaded_image.image_data);
				Texture::Color* loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
				Texture::Color* texture_buffer_pixels = buffer->colors();

				while (loaded_image_pixels < loaded_image_pixels_end)
				{
					*texture_buffer_pixels++ = *loaded_image_pixels++;
				}

				tga_free_buffers(&loaded_image);
			}

			return buffer;
		}


	};
}


#endif