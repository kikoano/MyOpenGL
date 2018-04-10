#include "TextureTestState.h"

void TextureTestState::CreateVertex(glm::vec4 v, int& index, int type, float color) {
	indices.push_back(index++);
	vertices.push_back(v.x);
	vertices.push_back(v.y);
	vertices.push_back(v.z);
	if (type == 0) {
		vertices.push_back(color);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}
	else if (type == 1) {
		vertices.push_back(0.0f);
		vertices.push_back(color);
		vertices.push_back(0.0f);
	}
	else if (type == 2) {
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(color);
	}
}
void TextureTestState::Init()
{

	//shader = new Shader(vertexShaderSource, fragmentShaderSource);
	shader = new Shader("../Shaders/BasicColor.vert", "../Shaders/BasicColor.frag");
	int index = 0;


	for (int y = 0; y < 3; y++) {
		float colorInc = 1.0f / 10.0f;
		float color = 0.0f;

		for (int x = 0; x < 10; x++) {
			glm::mat4 transformModel = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.2f, -y * 0.7f, 0.0f));

			glm::vec4 v = transformModel * glm::vec4(-1.0f, 1.0, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			v = transformModel * glm::vec4(-1.0f, 0.3f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			v = transformModel * glm::vec4(-0.8f, 0.3f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			indices.push_back(index-1);

			v = transformModel * glm::vec4(-0.8f, 1.0f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			indices.push_back(index-4);

			color += colorInc;
		}
	}

	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	va = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());
	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/


	//clear all binding
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
}


void TextureTestState::Pause()
{

}

void TextureTestState::Resume()
{

}

void TextureTestState::HandleEvents(StateManager* stateManager, int key, int action)
{

}

void TextureTestState::Update(StateManager* stateManager, double delta)
{

}

void TextureTestState::Render(StateManager* stateManager)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	va->Bind();
	ib->Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

TextureTestState::~TextureTestState() {
	shader->Unbind();
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
	delete shader;
	delete va;
	delete vb;
	delete ib;
}
