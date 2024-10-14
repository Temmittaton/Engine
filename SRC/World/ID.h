#ifndef _ID_

#define _ID_

#include <glm/glm.hpp>

struct ID {
	glm::vec3 ChunkID;
	unsigned int nID;

	ID (glm::vec3 _chunkID, unsigned int _ID) {
		ChunkID = _chunkID;
		nID = _ID;
	}
};

#endif //_ID_