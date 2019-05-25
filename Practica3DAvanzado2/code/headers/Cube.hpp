
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by �ngel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBE_HEADER
#define CUBE_HEADER
#include <vector>
    //#include <SFML/OpenGL.hpp>
#include <Point.hpp>

    namespace example
    {

        class Cube
        {
        private:

            // �ndices para indexar el array vbo_ids:

            enum
            {
                COORDINATES_VBO,
                COLORS_VBO,
                INDICES_IBO,
                VBO_COUNT
            };

            // Arrays de datos del cubo base:

            static const GLfloat coordinates[];
            static const GLfloat colors[];
            static const GLubyte indices[];

        private:

            GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
            GLuint vao_id;                  // Id del VAO del cubo

        public:

            Cube();
           ~Cube();

            void render ();

        };

    }

#endif
