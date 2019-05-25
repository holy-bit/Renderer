/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019

#pragma once


#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "Mesh.hpp"
#include <list>
#include <memory>

using namespace toolkit;
namespace renderer
{

	class Model
	{
		

		//* Transform Struct.
		/** Guarda la escala, rotacion, position y tranformacion*/
		struct Transform
		{
		public:
			Scaling3f     scaling{};/**< Escala. */ 
			Rotation3f    rotation_x{};/**< rotacion en X. */ 
			Rotation3f    rotation_y{};/**< rotacion en Y. */ 
			Translation3f translation{};/**< Posicion. */ 
			Transformation3f transformation{};/**< Transformacion. */ 
		};

	private:
		std::list<Mesh> meshes;/**< Lista de todas las mallas del modelo. */

	public:
		Model* parent = nullptr; /**< Puntero al modelo padre. */ 
		Transform transform; /**< Transform que contiene las distintas transformaciones del modelo */

		Model() = default;

		/**
		*	Devuelve la lista de mallas que posee el modelo.
		*/
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

		/**
		*	Aplica rotacion en el eje Y
		*	@param float angulo al que va a rotar;
		*/
		void rotateY(float angle) { transform.rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle); }

		/**
		*	Aplica rotacion en el eje X
		*	@param float angulo al que va a rotar;
		*/
		void rotateX(float angle) { transform.rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle); }

		void update() {

			transform.transformation = transform.translation * transform.rotation_x * transform.rotation_y * transform.scaling;

			if (parent != nullptr)
				transform.transformation = parent->transform.transformation * transform.transformation;
			
			for (Mesh& mesh : meshes)
			{
				mesh.set_Transform(transform.transformation);
				mesh.update();
			}
		}
		void render(Rasterizer<Color_Buffer_Rgba8888>& rasterizer) { for (Mesh& mesh : meshes) mesh.render(rasterizer); };

		
	};
}


#endif


