/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
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

namespace example
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

		/*struct Texture {
			unsigned int id;
			string type;
		};*/

	public:
		/*  Mesh Data  */
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		unsigned int VAO;
		std::shared_ptr< Texture > texture;
		/*  Functions  */
		bool has_texture;
		GLuint texture_id;
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, const string& texture_path);
		//void Draw(Shader shader);
		void Draw();
	private:
		/*  Render data  */
		unsigned int VBO, EBO;
		/*  Functions    */
		void setupMesh();

		
		

	private:
	
		

		Transformation3f  transform; /**< transform del modelo al que perteneces */

		

	public:
		//Mesh() = default;
	 
		/**
		*	Inicializa y redimensiona los vectores de los distintos tipos de procesado de los vertices y la direccion de la luz.
			@param Vertex_Buffer vector con las posiciones de los vertices de la malla.
			@param Vertex_Buffer normales de los vertices de la malla.
			@param Vertex_Colors colores de los vertices de la malla.
		*/
		//void set_Vertex(Vertex_Buffer& vertex_P, Vertex_Buffer& normalsP, Vertex_Colors colorsP);

		/**
		*	Guarda los indices de de los vertices.
			@param Index_Buffer indices de los Vertex_Buffer de vertices y normales.
		*/
		//void set_index(Index_Buffer& index){ index_positions = index; }

		/**
		*	Guarda el transform que recibe.
			@param Transformation3f tranformacion de todas las matrices de position,rotacion y escala.
		*/
		void set_Transform(Transformation3f& transformP) { transform = transformP; };

		void update();
		
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