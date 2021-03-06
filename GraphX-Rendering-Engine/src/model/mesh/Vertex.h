#pragma once

#include "GraphX_Vectors.h"
#include "Buffers/VertexBufferLayout.h"

namespace engine
{
	/* A Structure to represent a 2D vertex with all the attributes including color (Keeping this for the testing purposes */
	struct Vertex2DC
	{
		// The Position of the vertex
		gm::Vector2 Position;

		// The color for the vertex
		gm::Vector4 Color;

		// Returns the vertexbufferlayout for this struct
		static VertexBufferLayout GetVertexLayout()
		{
			VertexBufferLayout layout;
			layout.Push<float>(gm::Vector2::Components);	// For positions
			layout.Push<float>(gm::Vector4::Components);	// For colors

			return layout;
		}
	};

	/* A Structure to represent a vertex 2D with all the attributes including texture coordinates */
	struct Vertex2D
	{
		// The Position of the vertex
		gm::Vector2 Position;

		// The texture coordinate for the vertex
		gm::Vector2 TexCoord;

		// Returns the vertexbufferlayout for this struct
		static VertexBufferLayout GetVertexLayout()
		{
			VertexBufferLayout layout;
			layout.Push<float>(gm::Vector2::Components);	// For positions
			layout.Push<float>(gm::Vector2::Components);	// For texture coordinates

			return layout;
		}
	};

	/* A Structure to represent a vertex with all the attributes including color (Only keeping this for the testing purposes) */
	struct Vertex3DC
	{
		// The Position of the vertex
		gm::Vector3 Position;

		// The normal vector of the vertex
		gm::Vector3 Normal;
		
		// The color for the vertex
		gm::Vector4 Color;

		// Returns the vertexbufferlayout for this struct
		static VertexBufferLayout GetVertexLayout()
		{
			VertexBufferLayout layout;
			layout.Push<float>(gm::Vector3::Components);	// For positions
			layout.Push<float>(gm::Vector3::Components);	// For Normals
			layout.Push<float>(gm::Vector4::Components);	// For colors

			return layout;
		}
	};

	/* A Structure to represent a vertex with all the attributes including texture coordinates */
	struct Vertex3D
	{
		// The Position of the vertex
		gm::Vector3 Position;

		// The normal vector of the vertex
		gm::Vector3 Normal;

		// The texture coordinate for the vertex
		gm::Vector2 TexCoord;

		// Returns the vertexbufferlayout for this struct
		static VertexBufferLayout GetVertexLayout()
		{
			VertexBufferLayout layout;
			layout.Push<float>(gm::Vector3::Components);	// For positions
			layout.Push<float>(gm::Vector3::Components);	// For Normals
			layout.Push<float>(gm::Vector2::Components);	// For texture coordinates

			return layout;
		}
	};
}