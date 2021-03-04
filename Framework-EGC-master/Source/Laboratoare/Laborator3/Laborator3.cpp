#include "Laborator3.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//centrele la care cnstruiesc obiectele
	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 centru1 = glm::vec3(0, 0, 0);
	glm::vec3 centru2 = glm::vec3(c_x, c_y, 0);
	glm::vec3 centru3 = glm::vec3(d_x, d_y, 0);
	glm::vec3 centru4 = glm::vec3(e_x, e_y, 0);

	//adaug obiectele in lista
	Mesh* balon = Object2D::CreateBalon("balon", centru1, 30, glm::vec3(1, 1, 0));
	AddMeshToList(balon);	

	Mesh* balon2= Object2D::CreateBalon("balon2", centru1, 30, glm::vec3(1 , 0 , 0));
	AddMeshToList(balon2);


	Mesh* shuriken = Object2D::CreateShuriken("shuriken", centru2, 30, glm::vec3(0, 0, 1));
	AddMeshToList(shuriken);

	Mesh* sageata = Object2D::CreateSageata("sageata", centru3, 30, glm::vec3(1, 0, 1));
	AddMeshToList(sageata);
	
	Mesh* sageata2 = Object2D::CreateSageata("sageata2", glm::vec3(0,0, 0), 30, glm::vec3(1, 0, 1));
	AddMeshToList(sageata2);

	Mesh* arc = Object2D::CreateArc("arc", centru4, raza, glm::vec3(1, 0, 1));
	AddMeshToList(arc);

	Mesh* putere_arc = Object2D::CreateSquare("putere_arc", glm::vec3(0, 0, 0), dim_putere, glm::vec3(0, 1, 0), true);
	AddMeshToList(putere_arc);

	Mesh* scorebar = Object2D::CreateSquare("scorebar", glm::vec3(0, 0, 0), 25, glm::vec3(1, 0, 0), true);
	AddMeshToList(scorebar);
	
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{	
	//coordonate scena
	glm::ivec2 resol = window->GetResolution();

	//coordonate varf sageata
	float sx = (putere + 120) * cos(alfa_sgt) + 70;
	float sy = (putere + 120) * sin(alfa_sgt) + 350 + arc_y;

	//coliziunea sageata cu balonul
	for (int i = 0; i < 6; i++) {
		float dx = x[i] - sx;
		float dy = y[i] - sy;
		float distance = sqrt(dx * dx + dy * dy);
		if (distance <= 40) {
			y[i] = 0;
			collision = true;
			if (i % 2 == 0) {
				viata--;
			}
			else {
				viata++;
			}
		}
	}

	//coliziunea sageata cu shurikane
	for (int i = 0; i < 7; i++) {
		float dx = sx - x_s[i];
		float dy = sy - y_s[i];
		float distance = sqrt(dx * dx + dy * dy);
		if (distance <= 35) {
			x_s[i] = resol.x;
			y_s[i] = rand() % resol.y;
			viata++;
		}
	}

	//coliziunea arc cu shurikane
	for (int i = 0; i < 7; i++) {
		float dx = 20 - x_s[i];
		float dy = 350 + arc_y - y_s[i];
		float distance = sqrt(dx * dx + dy * dy);
		if (distance <= raza) {
			x_s[i] = resol.x;
			y_s[i] = rand() % resol.y;
			viata--;
		}
	}
	
	//viteza sageata
	if (press_s == true && speed_s <= 30) {
			speed_s += 0.5;
	}

	//putere = pozitia pe ox
	if (press == true && press_s == false) {
		putere += deltaTimeSeconds*v*speed_s;
	}

	float move_y = putere * tan(alfa_sgt);
	
	//cazul in sageata iese din scena si vreau sa o aduc inapoi
	if (putere > resol.x || move_y > resol.y || move_y < -resol.y) {
		putere = 0;
		press = false;
	}

	//cat timp mai am vieti continui jocul
	if (viata > 0) {
		{
			//desenez fiecare obiect in parte la fiecare moment de timp
			for (int i = 0; i < 6; i++) {
				modelMatrix = glm::mat3(1);
				y[i] = y[i] + deltaTimeSeconds * resol.y * SPEED / 2;
				modelMatrix *= Transform2D::Translate(x[i], y[i]);
				modelMatrix *= Transform2D::Scale(1, 1.5);

				if (y[i] > resol.y)
				{
					y[i] = 0;
					x[i] = rand() % (resol.x / 2) + 600;

				}

				if (i % 2 == 0) {
					RenderMesh2D(meshes["balon"], shaders["VertexColor"], modelMatrix);
				}
				else {
					RenderMesh2D(meshes["balon2"], shaders["VertexColor"], modelMatrix);

				}
			}

		}

		{
			alfa += deltaTimeSeconds;
			for (int i = 0; i < 7; i++) {
				modelMatrix = glm::mat3(1);
				x_s[i] = x_s[i] - deltaTimeSeconds * resol.x * SPEED;
				modelMatrix *= Transform2D::Translate(x_s[i], y_s[i]);
				modelMatrix *= Transform2D::Rotate(alfa);
				if (x_s[i] < -resol.x)
				{
					x_s[i] = resol.x;
					y_s[i] = rand() % resol.y;
				}
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
			}
		}

		{

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(70, 350 + arc_y);
			modelMatrix *= Transform2D::Rotate(alfa_sgt);
			modelMatrix *= Transform2D::Translate(putere, 0);
			RenderMesh2D(meshes["sageata"], shaders["VertexColor"], modelMatrix);

		}


		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(20, 350 + arc_y);
			//daca vreau sa se invarta si arcul dupa sageata
			//modelMatrix *= Transform2D::Rotate(alfa_sgt);
			//rotesc arcul in pozitia lui initiala(pe care o vreau)
			modelMatrix *= Transform2D::Rotate(1.5 * 3.165);
			RenderMesh2D(meshes["arc"], shaders["VertexColor"], modelMatrix);
		}

		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(0, 240 + arc_y);
			if (press_s) {
				modelMatrix *= Transform2D::Scale(speed_s / 2, 1);
			}
			else {
				modelMatrix *= Transform2D::Scale(speed_s_squere / 2 - dim_putere, 1);
			}
			RenderMesh2D(meshes["putere_arc"], shaders["VertexColor"], modelMatrix);
		}

		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(15, 670);
			modelMatrix *= Transform2D::Scale(viata, 1);
			RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);



		}
	}
	else {
		printf("GAME END\n");
		exit(-1);
	}

}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	//deplasare arc + sageata de pe taste
	if (window->KeyHold(GLFW_KEY_W))
	{
		arc_y += deltaTime * s;
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
		arc_y -= deltaTime * s;
	}
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event

}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	//calculez unghiul facut de sageata orientata dupa mouse si Ox
	if(!press)
	alfa_sgt = atan(-((mouseY - 370 + arc_y ) / (mouseX - 70)));

}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	//variabile care imi semnalizeaza cand am apasat pe butonul de la mouse
	//pt a calcula puterea de tragere a sagetii
	press = true;
	press_s = true;
	putere = 0;
	speed_s = 1;
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	press_s = false;
	speed_s_squere = -speed_s;
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
