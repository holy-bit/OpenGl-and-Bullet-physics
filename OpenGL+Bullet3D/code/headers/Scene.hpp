/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 25/05/2019
	//Videojuegos-Esne: 4.3

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include <SFML/Window.hpp>
#include "Camera.hpp"
#include "Obj_Loader.hpp"
#include <string>
#include "Skybox.hpp"
#include "Bullet_World_Controller.hpp"
#include "Postprocessing.hpp"
#include "Vehicle.hpp"
using namespace btTools;
using namespace std;
    namespace glTools
    {

        class Scene
        {
        private:


			Postprocessing postpro; /**< Postproceso que se aplica a la ventana */
			Camera camera; /**< Camara de la escena*/
			Skybox skybox; /**< Skybox de la escena */

		public:
			map<string, shared_ptr<Model>> models; /**< Lista de los modelos en la escena */
			shared_ptr<Vehicle> vehicle;/**< Vehiculo que controla el juegador */

            float  angle;/**< angulo de giro que se incrementa en el tiempo */

			int    width; /**< Ancho de la ventana */
			int    height; /**< Altura de la ventana */

			float  angle_around_x;
			float  angle_around_y;
			float  angle_delta_x;
			float  angle_delta_y;

			bool   pointer_pressed;
			int    last_pointer_x;
			int    last_pointer_y;
			glm::vec3 front{0,0,1};
			glm::vec3 direction;


        public:

            Scene(int width, int height);

			
            //! Actualizacion de la escena.
            /*! <b>Method:  </b>     update */
            /*! <b>FullName:</b>     glTools::Scene::update */
            /*! <b>Access:  </b>     public  */
            /**
            * @return  void
            */
            void   update ();

			
            //! Dibujado de la escena.
            /*! <b>Method:  </b>     render */
            /*! <b>FullName:</b>     glTools::Scene::render */
            /*! <b>Access:  </b>     public  */
            /**
            * @return  void
            */
            void   render ();

			
            //! Redimendimensionar la escena respecto al tamaño de la ventana.
            /*! <b>Method:  </b>     resize */
            /*! <b>FullName:</b>     glTools::Scene::resize */
            /*! <b>Access:  </b>     public  */
            /**
            * @param   int width
            * @param   int height
            * @return  void
            */
            void   resize (int width, int height);


			//! Evento al pulsar una tecla
			/*! <b>Method:  </b>     on_key */
			/*! <b>FullName:</b>     glTools::Scene::on_key */
			/*! <b>Access:  </b>     public  */
			/**
			* @return  void
			*/
			void on_key();

			//! Al arrastrar el raton haciendo click.
			/*! <b>Method:  </b>     on_drag */
			/*! <b>FullName:</b>     glTools::Scene::on_drag */
			/*! <b>Access:  </b>     public  */
			/**
			* @param   int pointer_x
			* @param   int pointer_y
			* @return  void
			*/
			void on_drag(int pointer_x, int pointer_y);

			//! Evento al hacer click con el raton.
			/*! <b>Method:  </b>      on_click */
			/*! <b>FullName:</b>    glTools::Scene::on_click */
			/*! <b>Access:  </b>     public  */
			/**
			* @param   int pointer_x
			* @param   int pointer_y
			* @param   bool down
			* @return  void
			*/
			void on_click(int pointer_x, int pointer_y, bool down);



			//! Evento al dejar de pulsar una tecla.
			/*! <b>Method:  </b>     on_key_realeased */
			/*! <b>FullName:</b>     glTools::Scene::on_key_realeased */
			/*! <b>Access:  </b>     public  */
			/**
			* @return  void
			*/
			void on_key_realeased();


        private:
	
			//! Carga de los modelos y creacion de colisiones.
			/*! <b>Method:  </b>     LoadModels */
			/*! <b>FullName:</b>     glTools::Scene::LoadModels */
			/*! <b>Access:  </b>     private  */
			/**
			* @return  void
			*/
			void LoadModels();


			//! Creacion del vehiculo y configuracion de sus contraints.
			/*! <b>Method:  </b>     CreateVehicle */
			/*! <b>FullName:</b>     glTools::Scene::CreateVehicle */
			/*! <b>Access:  </b>     private  */
			/**
			* @return  void
			*/
			void CreateVehicle();

        };

    }

#endif
