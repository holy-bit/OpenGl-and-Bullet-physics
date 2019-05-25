 /////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
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
namespace example
{
	

	class Model
	{
		const string vertex_shader_code =

			"#version 330\n"
			""
			"struct Light"
			"{"
			"    vec4 position;"
			"    vec3 color;"
			"};"
			"uniform Light light;"
			"uniform float ambient_intensity;"
			"uniform float diffuse_intensity;"
			""
			"uniform mat4 model_view_matrix;"
			"uniform mat4 projection_matrix;"
			"uniform mat4     normal_matrix;"
			"uniform vec3 material_color;"
			""
			"layout (location = 0) in vec3 vertex_coordinates;"
			"layout (location = 1) in vec3 vertex_normal;"
			"layout (location = 2) in vec2 tex_coords;"
			""
			"out vec3 front_color;"
			"out vec2 tex_coords2;"
			""
			"void main()"
			"{"
			"    vec4  normal = normal_matrix * vec4(vertex_normal, 1.0); "
			"    vec4  position = model_view_matrix * vec4(vertex_coordinates, 1.0);"
			""
			"    vec4  light_direction = light.position - position;"
			"    float light_intensity = diffuse_intensity * max (dot (normalize (normal.xyz), normalize (light_direction.xyz)), 0.0);"
			""
			"    front_color = ambient_intensity * material_color + diffuse_intensity * light_intensity * light.color * material_color;"
			"	tex_coords2 = vec2 (tex_coords.x,tex_coords.y);"
			"   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
			"}";

		const string fragment_shader_code =

			"#version 330\n"
			""
			"in vec2 tex_coords2; "
			"in  vec3    front_color;"
			"uniform sampler2D sampler2d;"
			""
			"void main()"
			"{"
			"    gl_FragColor = texture2D(sampler2d, tex_coords2) * vec4(front_color, 1);"
			"}";

		struct Piece
		{
			std::shared_ptr< Mesh > mesh;
			//std::shared_ptr< Material > material;
		};
		typedef std::list< Piece > Piece_List;
		Piece_List pieces;
		//* Transform Struct.
		/** Guarda la escala, rotacion, position y tranformacion*/
		struct Transform
		{
		public:
			glm::vec3     location{};/**< Posicion. */

			glm::vec3 Location() const { return location; }
			void Location(glm::vec3 val) { location = val; }

			glm::vec3     rotation{};/**< rotacion. */
			glm::vec3 Rotation() const { return rotation; }
			void Rotation(glm::vec3 val) { rotation = val; }

			glm::vec3     scale{1,1,1};/**< Escala. */

			glm::vec3 Scale() const { return scale; }
			void Scale(glm::vec3 val) { scale = val; }

			glm::mat4     transformation;/**< Transformacion. */
			
		};
		
	private:
		shared_ptr< Shader_Program > shader_program;
		std::list<Mesh> meshes;/**< Lista de todas las mallas del modelo. */

	public:
		Model* parent = nullptr; /**< Puntero al modelo padre. */ 
		Transform transform; /**< Transform que contiene las distintas transformaciones del modelo */
		GLint  model_view_matrix_id;
		GLint  projection_matrix_id;
		GLint  normal_matrix_id;
		Model()
		{
			// Se compilan y se activan los shaders:
			

			/*GLuint program_id = compile_shaders();

			glUseProgram(program_id);

			model_view_matrix_id = glGetUniformLocation(program_id, "model_view_matrix");
			projection_matrix_id = glGetUniformLocation(program_id, "projection_matrix");
			normal_matrix_id = glGetUniformLocation(program_id, "normal_matrix");

			configure_material(program_id);
			configure_light(program_id);*/

			// Se compilan y se activan los shaders:

			shader_program.reset(new Shader_Program);

			shader_program->attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
			shader_program->attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));

			shader_program->link();

			model_view_matrix_id = shader_program->get_uniform_id("model_view_matrix");
			projection_matrix_id = shader_program->get_uniform_id("projection_matrix");
			normal_matrix_id	 = shader_program->get_uniform_id("normal_matrix"    );

			shader_program->use();

			configure_material(*shader_program);
			configure_light(*shader_program);
		}

		/**
		*	Devuelve la lista de mallas que posee el modelo.
		*/
		const Piece_List& get_pieces() const
		{
			return pieces;
		}
		void add( const std::shared_ptr< Mesh >& mesh)
		{
			pieces.push_back({ mesh });
		}
		/**
		*	Aplica rotacion en el eje X
		*	@param float angulo al que va a rotar;
		*/
		void rotate_around_x(float angle)
		{
			transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(1.f, 0.f, 0.f));
		}
		/**
		*	Aplica rotacion en el eje Y
		*	@param float angulo al que va a rotar;
		*/
		void rotate_around_y(float angle)
		{
			transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(0.f, 1.f, 0.f));
		}
		/**
		*	Aplica rotacion en el eje Z
		*	@param float angulo al que va a rotar;
		*/
		void rotate_around_z(float angle)
		{
			transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(0.f, 0.f, 1.f));
		}
		
		std::list<Mesh>& get_meshes() { return meshes; }


		/**
		*	Establece un puntero al modelo que va a ser el padre.
		*   @param Model* Puntero al modelo padre.
		*/
		void setParent(Model* parent_parameteer) { parent = parent_parameteer; }

		/**
		*	Retorna puntero de este modelo.
		*/
		Model* getModel() { return this; }

		void GetTransformMatrix(const Camera& camera)
		{
			transform.transformation = camera.get_model_view();
			transform.transformation = glm::translate(transform.transformation, transform.location);
			rotate_around_x(transform.rotation.x);
			rotate_around_y(transform.rotation.y);
			rotate_around_z(transform.rotation.z);
			transform.transformation = glm::scale(transform.transformation, transform.scale);

			if (parent != nullptr)
				transform.transformation = parent->transform.transformation * transform.transformation;
		}

		void update(const Camera& camera) {
			
			
			/*for (Mesh& mesh : meshes)
			{
				mesh.set_Transform(transform.transformation);
				mesh.update();
			}*/
		}
		void render(const Camera& camera) {
			
			shader_program->use();
			GetTransformMatrix(camera);
			SetShaderValues(camera);
			for (Mesh& mesh : meshes) mesh.Draw();
			//shader_program.disable();
		};

		void SetShaderValues(const Camera& camera)
		{
			glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(transform.transformation));
			glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

			glm::mat4 normal_matrix = glm::transpose(glm::inverse(transform.transformation));
			glUniformMatrix4fv(normal_matrix_id, 1, GL_FALSE, glm::value_ptr(normal_matrix));
			
		}


		GLuint compile_shaders()
		{
			GLint succeeded = GL_FALSE;

			// Se crean objetos para los shaders:

			GLuint   vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

			// Se carga el código de los shaders:

			const char* vertex_shaders_code[] = { vertex_shader_code.c_str() };
			const char* fragment_shaders_code[] = { fragment_shader_code.c_str() };
			const GLint    vertex_shaders_size[] = { vertex_shader_code.size() };
			const GLint  fragment_shaders_size[] = { fragment_shader_code.size() };

			glShaderSource(vertex_shader_id, 1, vertex_shaders_code, vertex_shaders_size);
			glShaderSource(fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

			// Se compilan los shaders:

			glCompileShader(vertex_shader_id);
			glCompileShader(fragment_shader_id);

			// Se comprueba que si la compilación ha tenido éxito:

			glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
			if (!succeeded) show_compilation_error(vertex_shader_id);

			glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
			if (!succeeded) show_compilation_error(fragment_shader_id);

			// Se crea un objeto para un programa:

			GLuint program_id = glCreateProgram();

			// Se cargan los shaders compilados en el programa:

			glAttachShader(program_id, vertex_shader_id);
			glAttachShader(program_id, fragment_shader_id);

			// Se linkan los shaders:

			glLinkProgram(program_id);

			// Se comprueba si el linkage ha tenido éxito:

			glGetProgramiv(program_id, GL_LINK_STATUS, &succeeded);
			if (!succeeded) show_linkage_error(program_id);

			// Se liberan los shaders compilados una vez se han linkado:

			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);

			return (program_id);
		}

		void show_compilation_error(GLuint shader_id)
		{
			string info_log;
			GLint  info_log_length;

			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

			info_log.resize(info_log_length);

			glGetShaderInfoLog(shader_id, info_log_length, NULL, &info_log.front());

			cerr << info_log.c_str() << endl;

			/*#ifdef _MSC_VER
				OutputDebugStringA (info_log.c_str ());
			#endif*/

			assert(false);
		}

		void show_linkage_error(GLuint program_id)
		{
			string info_log;
			GLint  info_log_length;

			glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

			info_log.resize(info_log_length);

			glGetProgramInfoLog(program_id, info_log_length, NULL, &info_log.front());

			cerr << info_log.c_str() << endl;

			/* #ifdef _MSC_VER
				 OutputDebugStringA (info_log.c_str ());
			 #endif*/

			assert(false);
		}
		void configure_material(GLuint program_id)
		{
			GLint material_color = glGetUniformLocation(program_id, "material_color");

			glUniform3f(material_color, 1.f, 1.f, 1.f);
		}

		void configure_light(GLuint program_id)
		{
			GLint light_position = glGetUniformLocation(program_id, "light.position");
			GLint light_color = glGetUniformLocation(program_id, "light.color");
			GLint ambient_intensity = glGetUniformLocation(program_id, "ambient_intensity");
			GLint diffuse_intensity = glGetUniformLocation(program_id, "diffuse_intensity");

			glUniform4f(light_position, 10.f, 10.f, 10.f, 1.f);
			glUniform3f(light_color, 1.f, 1.f, 1.f);
			glUniform1f(ambient_intensity, 0.2f);
			glUniform1f(diffuse_intensity, 0.8f);
		}

		
	};
}


#endif


