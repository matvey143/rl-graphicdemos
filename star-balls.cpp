#include "raylib.h"
#include <random>

constexpr float maxXY = 15.0;
constexpr float minXY = -15.0;
constexpr float maxSpeed = 3.0;
constexpr float minSpeed = 0.1;
constexpr float maxZ = 65.0;
constexpr float minZ = 50.0;

//Initializing RNG.
std::random_device randDevice;
std::mt19937 rng(randDevice());
std::uniform_real_distribution<float> distrXY(minXY, maxXY);
std::uniform_int_distribution<unsigned char> distrColor(0, 255);
std::uniform_real_distribution<float> distrSpeed(minSpeed, maxSpeed);
std::uniform_real_distribution<float> distrZ(minZ, maxZ);

#define MAX_STARS 30

class StarBall {
public:
	static constexpr float radius = 1.0;
	Vector3 position;
	float speed;
	Color color;

	StarBall()
	{
		position = (Vector3) {distrXY(rng), distrXY(rng), distrZ(rng)};
		speed = distrSpeed(rng);
		color = (Color) {distrColor(rng), distrColor(rng), distrColor(rng), 0xFF};
	}

	void moveStar()
	{
		position.z -= speed;
	}
};

int main()
{
	const float cameraPos = -10.0;
	bool noColor = false;

	StarBall stars[MAX_STARS];

	Camera3D camera;
	camera.position = (Vector3) {0.0, 0.0, cameraPos};
	camera.target = (Vector3) {0.0, 0.0, 0.0};
	camera.up = (Vector3) {0.0, 0.1, 0.0};
	camera.fovy = 45.0;
	camera.projection = CAMERA_PERSPECTIVE;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 480, u8"3d Balls. Press spacebar to change color mode.");
	SetWindowMinSize(320, 240);
	SetTargetFPS(60);
	while(!WindowShouldClose()) {
		if (IsKeyReleased(KEY_SPACE)) noColor = !noColor;
		for (int i = 0; i < MAX_STARS; i++)
		{
			stars[i].moveStar();
			if (stars[i].position.z <= cameraPos) {
				stars[i] = StarBall();
			}
		}
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);
		{
			if (noColor) {
				for (int i = 0; i < MAX_STARS; i++) {
					DrawSphere(stars[i].position, stars[i].radius, WHITE);
				}
			}
			else {
				for (int i = 0; i < MAX_STARS; i++) {
					DrawSphere(stars[i].position, stars[i].radius, stars[i].color);
				}
			}
		}
		EndMode3D();
		EndDrawing();
	}
	return 0;
}
