/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#include "Model.hpp"

namespace glTools
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

	Model::Model(glm::vec3 location, glm::vec3 scale, glm::vec3 rotation, float mass_p)
	{
		isEntity = false;
		transform.setTransformValues(location, rotation, scale);
		
		mass = mass_p;

		// Se compilan y se activan los shaders:
		shader_program.reset(new Shader_Program);

		shader_program->attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
		shader_program->attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));

		shader_program->link();

		model_view_matrix_id = shader_program->get_uniform_id("model_view_matrix");
		projection_matrix_id = shader_program->get_uniform_id("projection_matrix");
		normal_matrix_id     = shader_program->get_uniform_id("normal_matrix");

		shader_program->use();

		configure_material(*shader_program);
		configure_light   (*shader_program);
	}


	void Model::rotate_around_x(float angle)
	{
		transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(1.f, 0.f, 0.f));
	}

	void Model::rotate_around_y(float angle)
	{
		transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(0.f, 1.f, 0.f));
	}

	void Model::rotate_around_z(float angle)
	{
		transform.transformation = glm::rotate(transform.transformation, angle, glm::vec3(0.f, 0.f, 1.f));
	}

	std::list<glTools::Mesh>& Model::get_meshes()
	{
		return meshes;
	}

	void Model::setParent(Model& parent_parameter)
	{
		parent = &parent_parameter;
	}

	glm::mat4 Model::GetTransformMatrix(const Camera& camera)
	{
		if (parent == nullptr)
			 transform.transformation = camera.get_model_view();
		else transform.transformation = glm::mat4();

		transform.transformation = glm::translate(transform.transformation, transform.getLocation());
		rotate_around_x(transform.getRotation().x);
		rotate_around_y(transform.getRotation().y);
		rotate_around_z(transform.getRotation().z);
		transform.transformation = glm::scale(transform.transformation, transform.getScale());

		if (parent != nullptr)
			transform.transformation = parent->GetTransformMatrix(camera) * transform.transformation;

		return transform.transformation;
	}

	void Model::render(const Camera& camera)
	{

		shader_program->use();
		if (!isEntity)
			GetTransformMatrix(camera);
		else transform.transformation = glm::scale(transform.transformation, transform.getScale());
		SetShaderValues(camera);
		for (Mesh& mesh : meshes) mesh.Draw();
		shader_program->disable();
	}

	void Model::SetShaderValues(const Camera & camera)
	{
		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(camera.get_model_view() * transform.transformation));
		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

		glm::mat4 normal_matrix = glm::transpose(glm::inverse(transform.transformation));
		glUniformMatrix4fv(normal_matrix_id, 1, GL_FALSE, glm::value_ptr(normal_matrix));
	}

	void Model::configure_material(GLuint program_id)
	{
		GLint material_color = glGetUniformLocation(program_id, "material_color");

		glUniform3f(material_color, 1.f, 1.f, 1.f);
	}

	void Model::configure_light(GLuint program_id)
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

}