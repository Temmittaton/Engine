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
	camera->values = vec4 (1.6, .9, 0, 0);
	camera->core.position = vec4 (0, 1, 0, 0);
	currentWorld->mainCamera = camera;

	// Player
	WorldActor* playerPaddle = new WorldActor ();

	playerPaddle->core = Core (vec4 (-0.5, 1, 1, 0), vec4 (.5, 0, 0, 0));
	playerPaddle->model = Model (vec4 (1, 0, 0, 1));

	currentWorld->AddWorldActor (playerPaddle);

	// Ennemy
	WorldActor* ennemyPaddle = new WorldActor ();

	ennemyPaddle->core = Core (vec4 (0.5, .9, 1, 0), vec4 (.5, 0, 0, 0));
	ennemyPaddle->model = Model (vec4 (0, 0, 1, 1));

	currentWorld->AddWorldActor (ennemyPaddle);

	// Ground
	WorldActor* ground = new WorldActor ();

	ground->core = Core (vec4 (0, -256, 0, 0), vec4 (256, 0, 0, 0));
	ground->model = Model (vec4 (.1, .1, .1, 1));

	currentWorld->AddWorldActor (ground);
}

void GameManager::Frame () {
	gameTime += .1;
}
