/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#pragma once

#include "Model.hpp"


namespace glTools
{


	class Postprocessing
	{
		const string vertex_shader_code =

			"#version 330\n"
			""
			""
			"layout (location = 0) in vec2 vertex_coordinates;"
			"layout (location = 1) in vec2 tex_coords;"
			""
			"out vec2 tex_coords2;"
			""
			"void main()"
			"{"
			"	tex_coords2 = vec2 (tex_coords.x,tex_coords.y);"
			"   gl_Position =  vec4(vertex_coordinates.x,vertex_coordinates.y,0.0, 1.0);"
			"}";

		const string fragment_shader_code =

			"#version 330\n"
			""
			"out vec4 FragColor;"
			"in vec2 tex_coords2; "
			"uniform sampler2D sampler2d;"
			""
			"void main()"
			"{"
			"vec3 color = texture(sampler2d, tex_coords2).rgb;"
			"if (tex_coords2.x < 0.5) color = vec3(0.0, color.g, 0.0);"
			"FragColor = vec4(color, 1.0);"
			"}";

	public:
		unsigned int VAO, VBO, FBO, TBO, RBO;
		shared_ptr< Shader_Program > shader_program;

		float vertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.

			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
		};



		void setupPostProcessing()
		{
			shader_program.reset(new Shader_Program);

			shader_program->attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
			shader_program->attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));

			shader_program->link();



			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


			shader_program->use();

			glUniform1i(shader_program->get_uniform_id("sampler2d"),0);

			glGenFramebuffers(1, &FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			glGenTextures(1, &TBO);
			glBindTexture(GL_TEXTURE_2D, TBO);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080 , 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TBO, 0);

			glGenRenderbuffers(1, &RBO);
			glBindRenderbuffer(GL_RENDERBUFFER, RBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080 ); // use a single renderbuffer object for both a depth AND stencil buffer.
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);


		
		}



	};
}