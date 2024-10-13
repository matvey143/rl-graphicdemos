#include "raylib.h"
#include <random>

#define MAX_STARS 30

class StarBall {
public:
	float radius;
	Vector3 position;
	float speed;

	void resetStar(float newX, float newY, float newZ, float newSpeed)
	{
		radius = 1.0;
		position = (Vector3) {newX, newY, newZ};
		speed = newSpeed;
	}

	void moveStar()
	{
		position.z -= speed;
	}
};

int main()
{
	const float maxXY = 15.0;
	const float minXY = -15.0;
	const float maxSpeed = 3.0;
        const float minSpeed = 0.1;
	const float maxZ = 65.0;
	const float minZ = 50.0;
	const float cameraPos = -10.0;

	//Инициализация генератора случайных чисел с запятой
	std::random_device randDevice;
	std::mt19937 rng(randDevice());
	std::uniform_real_distribution<> distrXY(minXY, maxXY);
	std::uniform_real_distribution<> distrSpeed(minSpeed, maxSpeed);
	std::uniform_real_distribution<> distrZ(minZ, maxZ);

	StarBall stars[MAX_STARS];
	for(int i = 0; i < MAX_STARS; i++) {
		stars[i].resetStar(distrXY(rng), distrXY(rng), distrZ(rng), distrSpeed(rng));
	}

	Camera3D camera;
	camera.position = (Vector3) {0.0, 0.0, cameraPos};
	camera.target = (Vector3) {0.0, 0.0, 0.0};
	camera.up = (Vector3) {0.0, 0.1, 0.0};
	camera.fovy = 45.0;
	camera.projection = CAMERA_PERSPECTIVE;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 480, u8"Шарики");
	SetWindowMinSize(320, 240);
	SetTargetFPS(60);
	while(!WindowShouldClose()) {
		for (int i = 0; i < MAX_STARS; i++)
		{
			stars[i].moveStar();
			if (stars[i].position.z <= cameraPos) {
				stars[i].resetStar(distrXY(rng), distrXY(rng), distrZ(rng), distrSpeed(rng));
			}
		}
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);
		{
			for (int i = 0; i < MAX_STARS; i++) {
				DrawSphere(stars[i].position, stars[i].radius, WHITE);
			}
		}
		EndMode3D();
		EndDrawing();
	}
	return 0;
}
