#ifndef _GAMEMANAGER_

#define _GAMEMANAGER_

#include "../World/World.h"

class GameManager {
public :
	// Public variables
	double gameTime;
	World* currentWorld;

	// Constructor
	GameManager ();

	// Destructor
	~GameManager ();

	// Methods
	void Init ();
	void Frame ();
};

#endif //_GAMEMANAGER_