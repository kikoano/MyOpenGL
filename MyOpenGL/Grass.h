#pragma once
#include "Entity.h"
#include "Mesh.h"
#include <string>
class Grass :
	public Entity
{
private:
	const std::string type1 = "w_grass\\obj__grass.obj";
	const std::string type2 = "w_flower2\\obj__flow2.obj";
	const std::string type3 = "w_flower3\\obj__flow3.obj";
	const std::string type4 = "w_fern1\\obj__fern1.obj";
	const std::string type5 = "w_fern2\\obj__fern2.obj";
	const std::string type6 = "w_fern3\\obj__fern3.obj";
	const std::string type7 = "w_weed5\\obj__weed5.obj";
	const std::string type8 = "w_shrub2\\obj__shr2.obj";
	const std::string type9 = "w_shrub15\\obj__shr15.obj";

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
		TYPE7 = 6,
		TYPE8 = 7,
		TYPE9 = 8,
	};
	Grass(Type type, glm::vec3 position);
	void Init();
	void Update(double delta);
	void Render();
	void SetScale(float size);
	~Grass();
};

