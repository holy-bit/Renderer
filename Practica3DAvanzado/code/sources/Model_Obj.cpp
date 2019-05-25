

#include "Model_Obj.hpp"

#include <tiny_obj_loader.h>
#include <vector>
#include <Point.hpp>

using namespace tinyobj;
using namespace std;

namespace renderer
{
	Model_Obj::Model_Obj(const std::string & obj_file_path)
	{
		attrib_t             attributes;
		vector< shape_t    > shapes;
		vector< material_t > materials;

		// Se intenta cargar el archivo OBJ:

		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, obj_file_path.c_str()) || !error.empty())
		{
			return;
		}

		// Se comprueba si los datos son válidos:

		if (shapes.size() == 0) { error = string("There're no shapes in ") + obj_file_path; return; }
		if (attributes.vertices.size() == 0) { error = string("There're no vertices in ") + obj_file_path; return; }
		if (attributes.normals.size() == 0) { error = string("There're no normals in ") + obj_file_path; return; }


		// Se crean las mallas que forman el modelo:

		for (auto & shape : shapes)
		{
			const vector< index_t > & indices = shape.mesh.indices;
			const size_t              indices_count = indices.size();

			if (indices_count > 0)
			{
				// Se fusionan los índices de coordenadas y de normales y se ordenan secuencialmente los vértices:

				const size_t   vertices_count = indices_count;

				vector< float > vertex_components(vertices_count * 3);
				vector< float > normal_components(vertices_count * 3);

				for (size_t src = 0, dst = 0; src < indices_count; ++src, dst += 3)
				{
					int vertex_src = indices[src].vertex_index * 3;
					int normal_src = indices[src].normal_index * 3;

					float x = attributes.vertices[vertex_src + 0];
					float y = attributes.vertices[vertex_src + 1];
					float z = attributes.vertices[vertex_src + 2];

					//vertex_components[src] = toolkit::Point4f({ x, y, z, 1 });

					normal_components[dst + 0] = attributes.normals[normal_src + 0];
					normal_components[dst + 1] = attributes.normals[normal_src + 1];
					normal_components[dst + 2] = attributes.normals[normal_src + 2];
				}

				// Se crean los buffers de atributos de vértices:
				/*vector < toolkit::Point4f > v
				shared_ptr< Vertex_Buffer_Object > vbo_coordinates
				(
					new Vertex_Buffer_Object(vertex_components.data(), vertex_components.size() * sizeof(float))
				);

				shared_ptr< Vertex_Buffer_Object > vbo_normals
				(
					new Vertex_Buffer_Object(normal_components.data(), normal_components.size() * sizeof(float))
				);
				*/
				// Se crea una mesh a partir de la shape de tinyobj:

				//shared_ptr< Mesh > mesh(new Mesh);

				/*shared_ptr< Vertex_Array_Object > vao
				(
					new Vertex_Array_Object
					(
						{
							{ vbo_coordinates, Mesh::Vertex_Attribute::COORDINATES, 3, GL_FLOAT },
							{ vbo_normals,     Mesh::Vertex_Attribute::NORMALS,     3, GL_FLOAT }
						}
					)
				);*/

				/*mesh->set_vao(vao);
				mesh->set_vertices_count(indices_count);

				// Se añade la nueva mesh al modelo:

				add(mesh, Material::default_material());*/
			}
		}
	}
	
}