#pragma once
#include "Entity.h"
#include "Mesh.h"
#include <string>
class Tree :
	public Entity
{
private:
	const std::string type1 = "f_tree1\\obj__tree1.obj";
	const std::string type2 = "f_tree2\\obj__tree2.obj";
	const std::string type3 = "f_tree3\\obj__tree3.obj";
	const std::string type4 = "f_tree4\\obj__tree4.obj";
	const std::string type5 = "f_tree5\\obj__tree5.obj";
	const std::string type6 = "f_tree6\\obj__tree6.obj";

	std::string type;
	std::unique_ptr<Mesh> model;
	Shader shader = Shader("model.vert", "model.frag");
	glm::mat4 shaderModel = glm::mat4(1.0f);
public:
	enum Type {
		TYPE1 = 0,
		TYPE2 = 1,
		TYPE3 = 2,
		TYPE4 = 3,
		TYPE5 = 4,
		TYPE6 = 5,
	};
	Tree(Type type, glm::vec3 position);
	void Init();
	void Update(double delta);
	void Render();
	void SetScale(float size);
	~Tree();
};

