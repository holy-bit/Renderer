/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019



#pragma once

#ifndef MESH_HEADER
#define MESH_HEADER
#include <Vector>
#include <memory>
#include <Point.hpp>
#include <cmath>
#include "Rasterizer.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include <random>

using namespace std;
using namespace toolkit;

namespace renderer
{
	class Mesh
	{
	
	public:
		
		typedef Color_Buffer_Rgba8888 Color_Buffer;
		typedef Color_Buffer::Color   Color;
		typedef Point4f               Vertex;
		typedef vector< Vertex >      Vertex_Buffer;
		typedef vector< int    >      Index_Buffer;
		typedef vector< Color  >      Vertex_Colors;
		typedef Point4i				  VertexI; 
		typedef vector <VertexI>	  Vertex_BufferI;

	private:
		Vertex_Buffer     vertexs; /**< Vertices del modelo */ 
		Vertex_Buffer     normals; /**< Normales del modelo */ 
		vector< int >     index_positions; /**< Indices de los vertices y  normales */ 
		Vertex_Colors     original_colors; /**< Colores de los vertices */ 

		Vertex_Colors     light_colors; /**< Colores de los vertices con iluminacion */ 

		Vertex_Buffer     transformed_vertices; /**< Vertices con transformacion aplicada */ 
		Vertex_Buffer     transformed_normals; /**< Normales con transformacion aplicada */
		Vertex_BufferI    clipped_vertices; /**< vertices recortados (Se pasan al restericer) */
		
		Vertex_BufferI    display_vertices;	/**< vertices a mostrar */

		Transformation3f  transform; /**< transform del modelo al que perteneces */

		Point3f			  light_vector;
		

	public:
		Mesh() = default;
	 
		/**
		*	Inicializa y redimensiona los vectores de los distintos tipos de procesado de los vertices y la direccion de la luz.
			@param Vertex_Buffer vector con las posiciones de los vertices de la malla.
			@param Vertex_Buffer normales de los vertices de la malla.
			@param Vertex_Colors colores de los vertices de la malla.
		*/
		void set_Vertex(Vertex_Buffer& vertex_P, Vertex_Buffer& normalsP, Vertex_Colors colorsP);

		/**
		*	Guarda los indices de de los vertices.
			@param Index_Buffer indices de los Vertex_Buffer de vertices y normales.
		*/
		void set_index(Index_Buffer& index){ index_positions = index; }

		/**
		*	Guarda el transform que recibe.
			@param Transformation3f tranformacion de todas las matrices de position,rotacion y escala.
		*/
		void set_Transform(Transformation3f& transformP) { transform = transformP; };

		void update();
		
		void render(Rasterizer<Color_Buffer_Rgba8888>& rasterizer);
		

	private:
		bool is_frontface(const Vertex * const projected_vertices, const int * const indices);


	};
}


#endif