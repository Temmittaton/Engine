#include "GameManager.hpp"
#include "../WorldActor/Camera.hpp"

// Constructor
GameManager::GameManager () {
	currentWorld = new World (glm::vec3 (64), 16, 16, glm::vec3 (0.6, 0.4, 1));
	gameTime = 0.0;
}

// Destructor
GameManager::~GameManager () {
	delete currentWorld;
}

// Methods
void GameManager::Init () {
	Camera* camera = new Camera ();
	camera->values = vec4 (.1, .1, 0, 0);
	currentWorld->mainCamera = camera;

	// Player
	WorldActor* playerPaddle = new WorldActor ();

	playerPaddle->core = Core (vec4 (-0.5, 0, 1, 0), vec4 (.5, 0, 0, 0));
	playerPaddle->model = Model (vec4 (1, 0, 0, 1));

	currentWorld->AddWorldActor (playerPaddle);

	// Ennemy
	WorldActor* ennemyPaddle = new WorldActor ();

	ennemyPaddle->core = Core (vec4 (0.5, -0.1, 1, 0), vec4 (.5, 0, 0, 0));
	ennemyPaddle->model = Model (vec4 (0, 0, 1, 1));

	currentWorld->AddWorldActor (ennemyPaddle);

	// The sun
	WorldActor* sun = new WorldActor ();

	sun->core = Core (vec4 (-64, 128, 256, 0), vec4 (16, 0, 0, 0));
	sun->model = Model (vec4 (1, 1, 0, 1), vec4 (1));

	currentWorld->AddWorldActor (sun);
}

void GameManager::Frame () {
	gameTime += .1;
}
