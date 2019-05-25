/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3

#include "Mesh.hpp"

  
namespace example
{

	Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, const string& texture_path)
	:
		has_texture(false)
	{
		if (texture_path != "")
		{
			texture = load_texture(texture_path);

			has_texture = texture.get() != 0;


		}
		this->vertices = vertices;
		this->indices = indices;

		setupMesh();
	}
	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));


		glBindVertexArray(0);


		if (has_texture)
		{
			// Se habilitan las texturas, se genera un id para un búfer de textura,
			// se selecciona el búfer de textura creado y se configuran algunos de
			// sus parámetros:

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			// Se suben los colores de la textura a la memoria de vídeo:

			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				texture->get_width(),
				texture->get_height(),
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				texture->colors()
			);
		}
	}

	void Mesh::Draw()
	{
		
			
		// draw mesh
		
		if (has_texture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture_id);
		}
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glDisable(GL_BLEND);
	}

}