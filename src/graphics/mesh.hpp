#include "common.h"

namespace cyx {

	struct Mesh {
		void* data;
		vec3* positions;
		u32*  indices;
		vec2* uvs;
		u32 vertices_count;
		u32 indices_count;
		Mesh() {}
		~Mesh() { delete data; }

		auto alloc_mesh_data() {
			auto position_size = vertices_count * sizeof(positions[0]);
			auto indices_size = indices_count * sizeof(indices[0]);
			auto vertices_size = vertices_count * sizeof(uvs[0]);
			data = new byte[position_size + indices_size + vertices_size];
			// set up pointers (symmetry excuse below)
			positions = (vec3*)((u8*)data);
			indices = (u32*)((u8*)data + position_size);
			uvs = (vec2*)((u8*)data + position_size + indices_size);
		}

	};
}	

