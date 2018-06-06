#include "ProceduralTerrain.h"

void ProceduralTerrain::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), true);
	camera->SetMovementSpeed(imGuiVars.cameraSpeed);
	light = new Light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	imGuiVars.vertexCount = pow(2, imGuiVars.vertexCount);
	imGuiVars.vertexFull = pow(2, imGuiVars.vertexFull);

	generator = new TerrainGenerator(imGuiVars.vertexCount, imGuiVars.vertexCount, imGuiVars.size, imGuiVars.randomseed, imGuiVars.persistence, imGuiVars.frequency, imGuiVars.amplitude, imGuiVars.octaves);
	generator->Generate(vertices, indices);
	lightingShader = new Shader("Terrain.vert", "Terrain.frag");
	lampShader = new Shader("lampColor.vert", "lampColor.frag");

	modelPlate = glm::translate(modelPlate, modelPos);


	cubeVAO = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]), false);
	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	cubeVAO->AddBuffer(*vb, layout);

	lightVAO = new VertexArray();

	VertexBufferLayout layout2; // ?
	layout2.Push<float>(3);
	layout2.Push<float>(3);
	layout2.Push<float>(2);

	lightVAO->AddBuffer(*vb, layout2);

	material = new Terrain();
	material->Bind();

	lightingShader->Bind();
	material->BindUniforms(*lightingShader);

	//clear all binding
	cubeVAO->Unbind();
	lightVAO->Unbind();
	vb->Unblind();
	ib->Unblind();
	GenerateTrees();
	for (auto& tree : trees) {
		tree->Init();
	}
}


void ProceduralTerrain::Pause()
{

}

void ProceduralTerrain::Resume()
{

}

void ProceduralTerrain::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard(key, action);
}

void ProceduralTerrain::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);
}

void ProceduralTerrain::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}
void ProceduralTerrain::RenderGui(StateManager* stateManager) {
	//ImGui::Begin("Edit");
	ImGui::SliderFloat3("Light Translation", &lightPos.x, -200.0f, 200.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	light->SetPosition(lightPos);
	ImGui::ColorEdit3("Light Color", &lightColor.x); // Edit 3 floats representing a color
	light->SetDiffuse(lightColor);
	light->SetSpecular(lightColor);
	ImGui::SliderFloat("Camera speed", &imGuiVars.cameraSpeed, 0.0f, 100.0f);
	if (ImGui::SliderInt("Vertex Count", &imGuiVars.vertexCount, 0.0f, 512.0f))
		imGuiVars.vertexCount = pow(2, round(log2(imGuiVars.vertexCount)));
	ImGui::SliderInt("Size", &imGuiVars.size, 0.0f, 1000.0f);
	ImGui::SliderInt("Seed", &imGuiVars.randomseed, 0.0f, 10000.0f);
	ImGui::SliderFloat("Persistence", &imGuiVars.persistence, 0.0f, 2.0f);
	ImGui::SliderFloat("Frequency", &imGuiVars.frequency, 0.0f, 1.0f);
	ImGui::SliderFloat("Amplitude", &imGuiVars.amplitude, 0.0f, 100.0f);
	ImGui::SliderInt("Octaves", &imGuiVars.octaves, 0.0f, 20.0f);
	ImGui::SliderInt("Scale Tiles", &imGuiVars.scaleTiles, 0.0f, 100.0f);
	if (ImGui::Button("Material Update")) {
		delete material;
		material = new Terrain();
		material->Bind();
		lightingShader->Bind();
		material->BindUniforms(*lightingShader);
	}
	if (ImGui::Button("Generate")) {
		vertices.clear();
		indices.clear();
		delete generator;
		generator = new TerrainGenerator(/*imGuiVars.vertexFull*/imGuiVars.vertexCount, imGuiVars.vertexCount, imGuiVars.size, imGuiVars.randomseed, imGuiVars.persistence, imGuiVars.frequency, imGuiVars.amplitude, imGuiVars.octaves);
		generator->Generate(vertices, indices);
		vb->updateBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));
		ib->updateBuffer(&indices[0], indices.size() * sizeof(indices[0]));
		delete material;
		material = new Terrain();
		material->Bind();
		lightingShader->Bind();
		material->BindUniforms(*lightingShader);
		GenerateTrees();
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//::End();
}

void ProceduralTerrain::GenerateTrees()
{
	trees.clear();
		for (int i = 0; i < imGuiVars.vertexCount; i++) {
			for (int j = 0; j < imGuiVars.vertexCount; j++) {
				double noise = generator->GetPerlinNoise().GetHeight(j, i);
				if (noise * 60 < 0) {
					if (rand() % 1000 == 999) {
						int type = rand() % 6;
						float offset = sqrt(imGuiVars.vertexCount) / 4;
						trees.push_back(std::make_unique<Tree>(static_cast<Tree::Type>(type), glm::vec3((float)j / ((float)imGuiVars.vertexCount /5) * imGuiVars.size, noise*offset*1.3f, (float)i / ((float)imGuiVars.vertexCount / 5) * imGuiVars.size)));
					}
				}
			}
		}
}

void ProceduralTerrain::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
	camera->SetMovementSpeed(imGuiVars.cameraSpeed);
	for (auto &tree : trees) {
		tree->Update(delta);
	}
	//modelPlate = glm::translate(modelPlate,glm::vec3(0.0f,0.0f, delta));
}

void ProceduralTerrain::Render(StateManager* stateManager)
{
	renderer.Clear();

	lightingShader->Bind();
	lightingShader->SetUniform3fv("light.position", light->GetPosition());
	lightingShader->SetUniform3fv("viewPos", camera->GetPosition());

	lightingShader->SetUniform3f("light.ambient", 0.1f, 0.1f, 0.1f);
	lightingShader->SetUniform3fv("light.diffuse", light->GetDiffuse());
	lightingShader->SetUniform3fv("light.specular", light->GetSpecular());

	lightingShader->SetUniform1f("material.shininess", static_cast<Terrain*>(material)->GetShininess());
	lightingShader->SetUniform1i("scaleTiles", imGuiVars.scaleTiles);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 150.0f);
	glm::mat4 view = camera->GetViewMatrix();
	lightingShader->SetUniformMatrix4fv("projection", projection);
	lightingShader->SetUniformMatrix4fv("view", view);

	// world transformation
	lightingShader->SetUniformMatrix4fv("model", modelPlate);

	renderer.Render(*lightVAO, *ib, *lightingShader);


	lampShader->Bind();
	lampShader->SetUniform3fv("color", light->GetDiffuse());
	lampShader->SetUniformMatrix4fv("projection", projection);
	lampShader->SetUniformMatrix4fv("view", view);
	modelLamp = glm::mat4(1.0f);
	modelLamp = glm::translate(modelLamp, light->GetPosition());
	modelLamp = glm::scale(modelLamp, glm::vec3(0.2f)); // a smaller cube
	lampShader->SetUniformMatrix4fv("model", modelLamp);

	renderer.RenderArrays(*lightVAO, 3, *lampShader);
	for (auto &tree : trees) {
		tree->UpdateProView(projection, view);
		tree->Render();
	}



}

ProceduralTerrain::~ProceduralTerrain() {
	glDisable(GL_CULL_FACE);
	lightingShader->Unbind();
	lampShader->Unbind();
	cubeVAO->Unbind();
	lightVAO->Unbind();
	vb->Unblind();
	ib->Unblind();
	Texture::Unbind();
	delete lightingShader;
	delete lampShader;
	delete cubeVAO;
	delete lightVAO;
	delete vb;
	delete ib;
	delete material;
	delete camera;
	delete light;
	delete generator;
}
