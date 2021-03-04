#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#define SIDE 100
#define FSX 2
#define FSY 3
#define SPEED 0.2
#define MAXLIM 0.2

class Laborator3 : public SimpleScene
{
	GLint move1, move2;

public:
	Laborator3();
	~Laborator3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	float translateX, translateY;
	float scaleX, scaleY;
	float angularStep;
	GLfloat c_x = 0, c_y = 0;
	GLfloat d_x = 0, d_y = 0;
	GLfloat e_x = 0, e_y = 0;
	std::vector<float> x = { 400, 450, 500, 550, 600, 650 };
	std::vector<float> y = { -200, -400, -600, -800, -1000, -1200 };
	float alfa = 0;
	float alfa_sgt = 0;
	float raza = 100;
	float putere = 0;
	float s = 150, arc_y = 0;
	float v = 100;
	float speed_s = 2.0f;
	float dim_putere = 5.0f;
	float speed_s_squere = 2.0f;
	float fac_scl = 0.9;
	int viata = 3;
	float nr = 1.0f;
	bool press = false;
	bool press_s = false;
	float collision = false;
	std::vector<float> x_s = { 1300, 2800, 1500, 2600, 1700, 2200, 1400 };
	std::vector<float> y_s = { 100, 300, 500, 700, 200, 400, 600 };


};
