#ifndef _ID_

#define _ID_

#include <glm/glm.hpp>

struct ID {
	glm::vec3 ChunkID;
	unsigned int nID, linearID;

	ID (glm::vec3 _chunkID = glm::vec3(0), unsigned int _ID = 0, unsigned int _linearIndex = 0) {
		ChunkID = _chunkID;
		nID = _ID;
		linearID = _linearIndex;
	}
};

#endif //_ID_