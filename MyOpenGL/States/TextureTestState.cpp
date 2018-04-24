#include "TextureTestState.h"
#include <stb/stb_image.h>
void TextureTestState::Init()
{
	vertices = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	};
	indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	shader = new Shader("BasicTexture.vert", "Mix2Texture.frag");


	va = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2); //textures

	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());


	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);// tell stb_image.h to flip loaded texture's on the y-axis.
	std::string filename = RESOURCES_PATH + "Textures\\container.jpg";
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,width,height,0,GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	filename = RESOURCES_PATH + "Textures\\awesomeface.png";
	data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	shader->Bind();
	shader->SetUniform1i("texture1",0);
	shader->SetUniform1i("texture2",1);
	//clear all binding
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
	glBindTexture(GL_TEXTURE_2D, 0);
}


void TextureTestState::Pause()
{

}

void TextureTestState::Resume()
{

}

void TextureTestState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void TextureTestState::Update(StateManager* stateManager, double delta)
{

}

void TextureTestState::Render(StateManager* stateManager)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

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
	glBindTexture(GL_TEXTURE_2D, 0);
}
