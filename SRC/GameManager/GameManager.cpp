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
	camera->values = vec4 (2, 2, 0, 0);
	currentWorld->mainCamera = camera;

	WorldActor* playerPaddle = new WorldActor ();

	playerPaddle->core = Core ();
	playerPaddle->model = Model (vec4 (1, 0, .5, 1));

	currentWorld->AddWorldActor (playerPaddle, vec3 (0, 0, 1.5));


	WorldActor* ennemyPaddle = new WorldActor ();

	ennemyPaddle->core = Core ();
	ennemyPaddle->model = Model (vec4 (1, 0, 0, 1));

	currentWorld->AddWorldActor (ennemyPaddle, vec3 (0, .1, 2));
}

void GameManager::Frame () {
	gameTime += .1;
}
