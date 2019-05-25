/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3


#define TINYOBJLOADER_IMPLEMENTATION

#include "Obj_Loader.hpp"
#include <tiny_obj_loader.h>
#include <Point.hpp>
#include <GL/glew.h>

using namespace std;
using namespace tinyobj;


namespace example
{
	/**
	*	Constructor que carga mallas desde un archivo obj.
	*	@param string Recibe el directorio del archivo a cargar.
	*/
	Obj_Loader::Obj_Loader(const string & obj_file_path, const string& texture_path)
	{
		attrib_t             attributes;
		vector< shape_t    > shapes;
		vector< material_t > materials;

		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, obj_file_path.c_str()) || !error.empty())
		{
		//	return;
		}
		
		// Se comprueba si los datos son válidos:

		if (shapes.size() == 0) { error = string("There're no shapes in ") + obj_file_path; return; }
		if (attributes.vertices.size() == 0) { error = string("There're no vertices in ") + obj_file_path; return; }
		if (attributes.normals.size() == 0) { error = string("There're no normals in ") + obj_file_path; return; }
		if (attributes.colors.size() == 0) { error = string("There're no colors in ") + obj_file_path; return; }
		if (attributes.texcoords.size() == 0) { error = string("There're no textures in ") + obj_file_path; return; }


		for (auto & shape : shapes)
		{
			const vector< index_t > & indices = shape.mesh.indices;
			const GLsizei              indices_count = (GLsizei)indices.size();
			const GLsizei    vertices_count = indices_count;
			vector< unsigned int    > index_positions(vertices_count);
			vector<Mesh::Vertex> vertexs(vertices_count);
			vector< toolkit::Point4f > vertex_components(vertices_count);
			vector< toolkit::Point4f > normal_components(vertices_count);
			//renderer::Mesh::Vertex_Colors color_components(vertices_count);


			size_t index_offset = 0;
			for (size_t face = 0; face < shape.mesh.num_face_vertices.size(); face++) {
				int face_vertices = shape.mesh.num_face_vertices[face];

				// Loop en los vertices de la cara.
				for (size_t vertex = 0; vertex < face_vertices; vertex++) {
		
					tinyobj::index_t idx = shape.mesh.indices[index_offset + vertex];
					index_positions[index_offset + vertex] = idx.vertex_index;

					vertexs[idx.vertex_index].Position =
					{
						attributes.vertices[3 * idx.vertex_index + 0],
						attributes.vertices[3 * idx.vertex_index + 1],
						attributes.vertices[3 * idx.vertex_index + 2]
					};

					vertexs[idx.vertex_index].Normal =
						{
							attributes.normals[3 * idx.normal_index + 0],
							attributes.normals[3 * idx.normal_index + 1],
							attributes.normals[3 * idx.normal_index + 2]
						};
					
					vertexs[idx.vertex_index].TexCoords =
					{
						attributes.texcoords[2 * idx.texcoord_index + 0],
						attributes.texcoords[2 * idx.texcoord_index + 1]
					};
				
					
				}

				index_offset += face_vertices;
			
				
			}

			shared_ptr< Mesh > mesh(new Mesh(vertexs,index_positions,texture_path));
			//mesh->set_Vertex(vertex_components,normal_components,color_components);
			//mesh->set_index(index_positions);

			get_meshes().push_back(*mesh);
		}
	}

}