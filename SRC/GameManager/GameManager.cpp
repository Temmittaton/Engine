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
	currentWorld->mainCamera = camera;

	WorldActor* playerPaddle = new WorldActor ();

	playerPaddle->core = Core ();
	playerPaddle->model = Model ();

	currentWorld->AddWorldActor (playerPaddle, vec3 (0, 0, 0));


	WorldActor* ennemyPaddle = new WorldActor ();

	ennemyPaddle->core = Core ();
	ennemyPaddle->model = Model ();

	currentWorld->AddWorldActor (ennemyPaddle, vec3 (0, 0, 0));
}

void GameManager::Frame () {
	gameTime += .1;
}
