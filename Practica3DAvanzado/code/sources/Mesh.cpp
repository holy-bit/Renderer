/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019

#include "Mesh.hpp"
namespace renderer
{
	void Mesh::set_Vertex(vector< toolkit::Point4f >& vertex_P, vector< toolkit::Point4f >& normalsP, Vertex_Colors colorsP)
	{
		vertexs = vertex_P;
		normals = normalsP;
		original_colors = colorsP;
		original_colors.resize(vertexs.size());
		display_vertices.resize(vertexs.size());
		transformed_vertices.resize(vertexs.size());
		transformed_normals.resize(vertexs.size());
		light_colors.resize(vertexs.size());
		clipped_vertices.resize(vertexs.size());
		light_vector[0] = 0.f;
		light_vector[1] = 0.5f;
		light_vector[2] = 1;

	}

	void Mesh::update()
	{
		

		// Se crean las matrices de transformación:

		
		Projection3f  projection(5, 15, 20, float(1920) / float(1080));

		//translation.set(0, -move, -10);
	

		// Creación de la matriz de transformación unificada:
		
		Transformation3f transformation = projection * transform;

		// Se transforman todos los vértices usando la matriz de transformación resultante:



		for (size_t index = 0, number_of_vertices = vertexs.size(); index < number_of_vertices; index++)
		{
			// Se multiplican todos los vértices originales con la matriz de transformación y
			// se guarda el resultado en otro vertex buffer:

			Vertex & vertex = transformed_vertices[index] = Matrix44f(transformation) * Matrix41f(vertexs[index]);

			//se aplica la tranformacion a las normales, que se normalizan se multiplica por la direccion de la luz 
			//y esa intensidad producto de esto se multiplica por cada componente de color del vertice.

			Vertex normal = Matrix44f(transform) * Matrix41f(normals[index]);
			float module = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
			transformed_normals[index] = Vertex
			({
				normal[0] / module,
				normal[1] / module,
				normal[2] / module,
				0.f
				});
			float Intensity_vertex = (transformed_normals[index][0] * light_vector[0] + transformed_normals[index][1] * light_vector[1] + transformed_normals[index][2] * light_vector[2]) + 0.1;

			Intensity_vertex = max(min(Intensity_vertex,1.f),0.f);

 			light_colors[index].set(original_colors[index].data.component.r *Intensity_vertex, original_colors[index].data.component.g *Intensity_vertex, original_colors[index].data.component.b *Intensity_vertex);

			// La matriz de proyección en perspectiva hace que el último componente del vector
			// transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

			float divisor = 1.f / vertex[3];

			vertex[0] *= divisor;
			vertex[1] *= divisor;
			vertex[2] *= divisor;
			vertex[3] = 1.f;
		}
	}

	void Mesh::render(Rasterizer<Color_Buffer_Rgba8888> &rasterizer)
	{
		// Se convierten las coordenadas transformadas y proyectadas a coordenadas
		// de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
		// La coordenada Z se escala a un valor suficientemente grande dentro del
		// rango de int (que es lo que espera fill_convex_polygon_z_buffer).

		Scaling3f        scaling = Scaling3f(float(1920 / 2), float(1080 / 2), 100000000.f);
		Translation3f    translation = Translation3f(float(1920 / 2), float(1080 / 2), 0.f);
		Transformation3f transformation = translation * scaling;

		for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
		{
			display_vertices[index] = Point4i(Matrix44f(transformation) * Matrix41f(transformed_vertices[index]));
		}


		for (int * indices = index_positions.data(), *end = indices + index_positions.size(); indices < end; indices += 3)
		{
			if (is_frontface(transformed_vertices.data(), indices))
			{
				 //Se establece el color del polígono a partir del color de su primer vértice:

				rasterizer.set_color(light_colors[*indices]);

				// Se rellena el polígono:
				rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
			}
		}

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		rasterizer.get_color_buffer().gl_draw_pixels(0, 0);

	}

	bool Mesh::is_frontface(const Vertex * const projected_vertices, const int * const indices)
	{
		const Vertex & v0 = projected_vertices[indices[0]];
		const Vertex & v1 = projected_vertices[indices[1]];
		const Vertex & v2 = projected_vertices[indices[2]];

		// Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
		// Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
	}
}