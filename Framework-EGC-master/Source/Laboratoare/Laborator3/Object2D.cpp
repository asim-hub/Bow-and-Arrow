#include "Object2D.h"
#include <iostream>
#include <vector>
#include <Core/Engine.h>
using namespace std;
Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(2*length, 0, 0), color),
		VertexFormat(corner + glm::vec3(2*length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


Mesh* Object2D::CreateBalon(std::string name, glm::vec3 centru, float dime, glm::vec3 color){
	int num_segments = 50;
	std::vector<VertexFormat> vertices;

	//cerc
	vertices.push_back(VertexFormat(centru, color));
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = dime * cosf(theta);//calculate the x component 
		float y = dime * sinf(theta);//calculate the y component 
		vertices.push_back(VertexFormat(centru + glm::vec3(x, y, 0), color));
	}

	//codita
	vertices.push_back(VertexFormat(centru - glm::vec3(-dime/2, 1.5*dime/2, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(dime, 2* 1.5 * dime/2, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(dime + 5, 2 * 1.5 * dime/2, 0), color));
	
	
	vertices.push_back(VertexFormat(centru - glm::vec3(-0.6*dime, 3 * 1.5 * dime/2, 0), color));

	vertices.push_back(VertexFormat(centru - glm::vec3(-0.6 * dime, 3 * 1.5 * dime/2 - 3, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(2* 1.5 * dime/2, 4 * 1.5 * dime/2, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(2 * 1.5 * dime/2- 10, 4 * 1.5 * dime/2, 0), color));
	//tringhi
	vertices.push_back(VertexFormat(centru - glm::vec3(-dime / 2 +10, 1.5 * dime / 2, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(-dime/2, 1.5 * dime / 2+ 20, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(dime/2, 1.5 * dime / 2 + 20, 0), color));


	vector<GLushort> indices;

	for (int i = 1; i < num_segments; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	indices.push_back(0);
	indices.push_back(num_segments);
	indices.push_back(1);

	indices.push_back(num_segments + 1);
	indices.push_back(num_segments + 2);
	indices.push_back(num_segments + 3);

	indices.push_back(num_segments + 2);
	indices.push_back(num_segments + 3);
	indices.push_back(num_segments + 4);

	indices.push_back(num_segments + 5);
	indices.push_back(num_segments + 6);
	indices.push_back(num_segments + 7);

	indices.push_back(num_segments + 8);
	indices.push_back(num_segments + 9);
	indices.push_back(num_segments + 10);

	// Create a new mesh from buffer data
	Mesh* balon = new Mesh(name);
	balon->InitFromData(vertices, indices);
	return balon;

	
}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 centru, float dime, glm::vec3 color) {
	
	std::vector<VertexFormat> vertices;
	
	vertices.push_back(VertexFormat(centru, glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(centru + glm::vec3(30 , 40 , 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(centru + glm::vec3(40 , 10 , 0), glm::vec3(1, 0, 0)));

	vertices.push_back(VertexFormat(centru + glm::vec3(40, -20, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(centru + glm::vec3(10, -40, 0), glm::vec3(1, 0, 0)));

	vertices.push_back(VertexFormat(centru + glm::vec3(-10, 40, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(centru + glm::vec3(-40, 20, 0), glm::vec3(1, 0, 0)));

	vertices.push_back(VertexFormat(centru + glm::vec3(-40, -10, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(centru + glm::vec3(-30, -40, 0), glm::vec3(1, 0, 0)));


	std::vector<GLushort> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(8);


	// Create a new mesh from buffer data
	Mesh* shuriken = new Mesh(name);
	shuriken->InitFromData(vertices, indices);
	return shuriken;


}

Mesh* Object2D::CreateSageata(std::string name, glm::vec3 centru, float dime, glm::vec3 color) {

	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(centru, color));
	vertices.push_back(VertexFormat(centru + glm::vec3(0, 3, 0), color));
	vertices.push_back(VertexFormat(centru + glm::vec3(100, 3, 0), color));
	
	vertices.push_back(VertexFormat(centru + glm::vec3(100, 0, 0), color));

	vertices.push_back(VertexFormat(centru + glm::vec3(100, 10, 0), color));
	vertices.push_back(VertexFormat(centru + glm::vec3(100, -10, 0), color));
	vertices.push_back(VertexFormat(centru + glm::vec3(120, 0, 0), color));


	std::vector<GLushort> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);

	// Create a new mesh from buffer data
	Mesh* sageata = new Mesh(name);
	sageata->InitFromData(vertices, indices);
	return sageata;

}


Mesh* Object2D::CreateArc(std::string name, glm::vec3 centru, float dime, glm::vec3 color) {

	int num_segments = 50;
	std::vector<VertexFormat> vertices;

	//vertices.push_back(VertexFormat(centru, glm::vec3(1, 0, 0)));
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = dime * cosf(theta);//calculate the x component 
		float y = dime * sinf(theta);//calculate the y component 
		vertices.push_back(VertexFormat(centru + glm::vec3(x, y, 0), color));
	}

	for (int i = num_segments; i < 2*num_segments - 2; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = (dime - 4) * cosf(theta);//calculate the x component 
		float y = (dime - 4) * sinf(theta);//calculate the y component 
		vertices.push_back(VertexFormat(centru + glm::vec3(x, y, 0), color));
	}

	vertices.push_back(VertexFormat(centru + glm::vec3(dime, 0, 0), color));
	vertices.push_back(VertexFormat(centru + glm::vec3(dime, 5, 0), color));
	vertices.push_back(VertexFormat(centru - glm::vec3(dime, -7, 0), color));

	vertices.push_back(VertexFormat(centru - glm::vec3(dime, -12, 0), color));
	

	vector<GLushort> indices;

	for (int i = 0; i < num_segments/2 - 1; i++) {
		indices.push_back(i);
		indices.push_back(i+1);
		indices.push_back(num_segments + i);
	}

	for (int i = num_segments; i < num_segments + num_segments/2 -1; i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i - num_segments + 1);
	}

	indices.push_back(2*num_segments -1);
	indices.push_back(2*num_segments - 2);
	indices.push_back(2*num_segments);

	indices.push_back(2*num_segments);
	indices.push_back(2*num_segments + 1);
	indices.push_back(2*num_segments - 1);

	// Create a new mesh from buffer data
	Mesh* balon = new Mesh(name);
	balon->InitFromData(vertices, indices);
	return balon;



}