#include "PacmanState.h"


PacmanState::PacmanState() :
	shader2(Shader(vertexShaderSource2, fragmentShaderSource2)),
	shader1(Shader(vertexShaderSource, fragmentShaderSource))
{

}

void PacmanState::Init()
{

	pacman.position = glm::vec3(0.0f, 0.0f, 0.0f);
	ghost.position = glm::vec3(500.0f, 400.0f,0.0f);

	float color[] = { 1.0f, 1.0f, 0.0f };
	draw::polyederElementColorAngle(200, 300.0f, 300.0f, 50.0f, 50.0f, vertices, indices, color, glm::radians(30.0f), glm::radians(330.0f));
	indicesSize.push_back(indices.size());
	float color2[] = { 0.0f, 0.0f, 0.0f };
	draw::polyederElementColor(30, 315.0f, 270.0f, 10.0f, vertices, indices, color2);
	indicesSize.push_back(indices.size() - indicesSize.at(0));
	float color3[] = { 1.0f, 0.0f, 0.0f };
	draw::polyederElementColorAngle(200, 50.0f, 0.0f, 50.0f, 50.0f, vertices, indices, color3, glm::radians(178.0f), glm::radians(360.0f));
	indicesSize.push_back(indices.size() - indicesSize.at(1) - indicesSize.at(0));


	float off = 100.0f / 8.0f;
	int max = *max_element(indices.begin(), indices.end())+1;

	for (int i = 0; i < 8; i+=2) {
		indices.push_back(max++);
		vertices.push_back(off * i);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		
		indices.push_back(max++);
		vertices.push_back(off * (i+1));
		vertices.push_back(0.0f + 30.0f);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		indices.push_back(max++);
		vertices.push_back(off * (i+2));
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);


	}
	indicesSize.push_back(indices.size() - indicesSize.at(2) - indicesSize.at(1) - indicesSize.at(0));


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));
	ib = new IndexBuffer(&indices[0], indices.size() * sizeof(indices[0]));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	ib->Unblind();
	vb->Unblind();
}


void PacmanState::Pause()
{

}

void PacmanState::Resume()
{

}

void PacmanState::HandleEvents(StateManager* stateManager, int key, int action)
{
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
			pacman.direction[0] = true;
		else if (action == GLFW_RELEASE)
			pacman.direction[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS)
			pacman.direction[1] = true;
		else if (action == GLFW_RELEASE)
			pacman.direction[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
			pacman.direction[2] = true;
		else if (action == GLFW_RELEASE)
			pacman.direction[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
			pacman.direction[3] = true;
		else if (action == GLFW_RELEASE)
			pacman.direction[3] = false;
	}
}

void PacmanState::Update(StateManager* stateManager, double delta)
{
	pacman.model = glm::mat4(1.0f);
	ghost.model = glm::mat4(1.0f);
	if (pacman.direction[0]) {
		pacman.position.y -= pacman.speed * delta;
	}
	if (pacman.direction[1]) {
		pacman.position.y += pacman.speed * delta;
	}
	if (pacman.direction[2]) {
		pacman.position.x -= pacman.speed * delta;
		pacman.flip = true;
	}
	if (pacman.direction[3]) {
		pacman.position.x += pacman.speed * delta;
		pacman.flip = false;
		
	}
	pacman.model = glm::translate(pacman.model, pacman.position);
	if (pacman.flip) {
		pacman.model = glm::translate(pacman.model, glm::vec3(600.0f, 0.0f, 0.0f));
		pacman.model = glm::scale(pacman.model, glm::vec3(-1.0f, 1.0f, 1.0f));
	}
	else {
		pacman.model = glm::scale(pacman.model, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (!ghost.flip && ghost.position.x > 500.0f)
		ghost.flip = true;
	else if(ghost.flip && ghost.position.x < 0.0f)
		ghost.flip = false;
	if (ghost.flip)
		ghost.position.x -= ghost.speed*delta;
	
	else 
		ghost.position.x += ghost.speed*delta;
	
	ghost.model = glm::translate(ghost.model, ghost.position);
	std::cout <<"x: "<< ghost.position.x << "	y: " << ghost.flip << std::endl;

	

}

void PacmanState::Render(StateManager* stateManager)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader1.Bind();
	glBindVertexArray(VAO);
	ib->Bind();
	shader1.SetUniformMatrix4fv("projection", projection);
	shader1.SetUniformMatrix4fv("model", pacman.model);
	glDrawElements(GL_TRIANGLE_FAN, indicesSize.at(0), GL_UNSIGNED_INT, nullptr);
	glDrawElements(GL_TRIANGLE_FAN, indicesSize.at(1), GL_UNSIGNED_INT, (void*)(indicesSize.at(0) * sizeof(unsigned int)));
	shader2.Bind();
	shader2.SetUniformMatrix4fv("projection", projection);
	shader2.SetUniformMatrix4fv("model", ghost.model);
	glDrawElements(GL_TRIANGLE_FAN, indicesSize.at(2), GL_UNSIGNED_INT, (void*)((indicesSize.at(1) + indicesSize.at(0)) * sizeof(unsigned int)));
	glDrawElements(GL_TRIANGLES, indicesSize.at(3), GL_UNSIGNED_INT, (void*)((indicesSize.at(2) + indicesSize.at(1) + indicesSize.at(0)) * sizeof(unsigned int)));
}
PacmanState::~PacmanState() {
	shader1.Unbind();
	shader2.Unbind();
	glDeleteVertexArrays(1, &VAO);
	vb->Unblind();
	delete vb;
	ib->Unblind();
	delete ib;
}

