#pragma once
#define _USE_MATH_DEFINES
#include <math.h> //needs fix to cmath
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace draw {
	static std::vector<float> polyeder(int n, float x0, float y0, float r) {
		/* x0, y0 centar, r radius na n-agolnikot */
		std::vector<float> vertices;
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		n++;
		while (n--) {

			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + r * sin(alfa));
			vertices.push_back(0.0f);

			alfa += angle;
		}
		return vertices;
	}
	static std::vector<float> polyeder(int n, float x0, float y0, float r, float rr) {
		/* x0, y0 centar, r radius na n-agolnikot */
		std::vector<float> vertices;
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		n++;
		while (n--) {

			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + rr * sin(alfa));
			vertices.push_back(0.0f);

			alfa += angle;
		}
		return vertices;
	}

	/*static void polyederElement(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		// x0, y0 centar, r radius na n-agolnikot 
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		unsigned int max;
		//najdi sleden indice
		if (indices.empty())
			max = 0;
		else
			max = *max_element(indices.begin(), indices.end())+1;

		int i = max + 1;
		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		vertices.push_back(x0 + r * cos(alfa));
		vertices.push_back(y0 + rr * sin(alfa));
		vertices.push_back(0.0f);

		while (n--) {
			indices.push_back(max);
			indices.push_back(i);
			i++;

			alfa += angle;

			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + rr * sin(alfa));
			vertices.push_back(0.0f);
			indices.push_back(i);
		}
	}*/
	static void polyederElement(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		/* x0, y0 centar, r radius na n-agolnikot */
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		unsigned int max;
		//najdi sleden indice
		if (indices.empty())
			max = 0;
		else
			max = *max_element(indices.begin(), indices.end()) + 1;

		int i = max;

		indices.push_back(i++);
		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		n += 1;

		while (n--) {

			indices.push_back(i++);
			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + rr * sin(alfa));
			vertices.push_back(0.0f);
			alfa += angle;
		}
	
	}
	static void polyederElementColor(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices, float * colors) {
		/* x0, y0 centar, r radius na n-agolnikot */
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		unsigned int max;
		//najdi sleden indice
		if (indices.empty())
			max = 0;
		else
			max = *max_element(indices.begin(), indices.end()) + 1;

		int i = max;

		indices.push_back(i++);
		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		vertices.push_back(colors[0]);
		vertices.push_back(colors[1]);
		vertices.push_back(colors[2]);

		n += 1;

		while (n--) {

			indices.push_back(i++);
			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + rr * sin(alfa));
			vertices.push_back(0.0f);

			vertices.push_back(colors[0]);
			vertices.push_back(colors[1]);
			vertices.push_back(colors[2]);

			alfa += angle;
		}

	}
	static void polyederElementColor(int n, float x0, float y0, float r, std::vector<float> &vertices, std::vector<unsigned int> &indices, float * colors) {
		polyederElementColor(n, x0, y0, r, r, vertices, indices, colors);
	}
	static void polyederColorWheel(int n, float x0, float y0, float r, std::vector<float> &vertices) {
		/* x0, y0 centar, r radius na n-agolnikot */
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = 0;
		

		vertices.push_back(x0);
		vertices.push_back(y0);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		

		float colorInit = 255.0f * 6.0f / n / 255.0f;
		float colorI = colorInit;
		n += 2;
		while (n--) {

			vertices.push_back(x0 + r * cos(alfa));
			vertices.push_back(y0 + r * sin(alfa));
			vertices.push_back(0.0f);

			float a = glm::degrees(alfa)+0.01;

		    if (a >= 0 && a < 60) {
				vertices.push_back(1.0f);
				vertices.push_back(colorI);
				vertices.push_back(0.0f);
			}
		
			else if (a >= 60 && a < 120) {
				vertices.push_back(1.0f- colorI);
				vertices.push_back(1.0f);
				vertices.push_back(0.0f);
			}
			else if (a >= 120 && a < 180) {
				vertices.push_back(0.0f);
				vertices.push_back(1.0f);
				vertices.push_back(colorI);
			}
			else if (a >= 180 && a < 240) {
				vertices.push_back(0.0f);
				vertices.push_back(1.0f-colorI);
				vertices.push_back(1.0f);
			}
			else if (a >= 240 && a < 300) {
				vertices.push_back(colorI);
				vertices.push_back(0.0f);
				vertices.push_back(1.0f);
			}
			else if (a >= 300 && a < 360) {
				vertices.push_back(1.0f);
				vertices.push_back(0.0f);
				vertices.push_back(1.0f- colorI);
			}
			else {
				vertices.push_back(1.0f);
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);

			}
			colorI += colorInit;
			if (colorI >1.0f) {
				colorI = colorInit;
			}
			alfa += angle;
		}

	}
	static void polyederElement(int n, float x0, float y0, float r, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		polyederElement(n, x0, y0, r, r, vertices, indices);
	}
	static void polyederRingElementNotFixed(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		/* x0, y0 centar, r radius na n-agolnikot */
		float angle, alfa=0;
		angle = 2 * M_PI / n; // najdi go agolot
		unsigned int max;
		//najdi sleden indice
		if (indices.empty())
			max = 0;
		else
			max = *max_element(indices.begin(), indices.end()) +1;

		int i = max;
		int index = -2;
		float dis = r;

		while (n--) {

			if (n % 2 == 0)
				dis = r;
			else
				dis = rr;
			if (index > 0) {
				indices.push_back(i-2);
				alfa += angle;
				indices.push_back(i-1);
				index = 0;	

			}
			else {
				indices.push_back(i);
				vertices.push_back(x0 + dis * cos(alfa));
				vertices.push_back(y0 + dis * sin(alfa));
				vertices.push_back(0.0f);
				index++;
				i++;
			}
			alfa += angle;
	
		}
		//indices.erase(indices.begin(), indices.begin() + 6);
	
	}
	static void polyederRingElement(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		float angle, alfa;
		angle = 2 * M_PI / n;
		alfa = angle;
		unsigned int max;
		if (indices.empty())
			max = 0;
		else
			max = *max_element(indices.begin(), indices.end()) + 1;

		int i = max;
		
		n += 2;
		float dis = r;
		while (n--) {

			if (n % 2 == 0)
				dis = r;
			else
				dis = rr;
			indices.push_back(i++);
			vertices.push_back(x0 + dis * cos(alfa));
			vertices.push_back(y0 + dis * sin(alfa));
			vertices.push_back(0.0f);
			alfa += angle;
		}
	}

	static void polyederLegacyFill(int n, float x0, float y0, float r) {
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
		alfa += angle;
		glBegin(GL_POLYGON);
		while (n--) {
			glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
			alfa += angle;
			glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
		}
		glEnd();

	}
	static void polyederLegacyHalfFill(int n, float x0, float y0, float r, float start) {
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = start;
		n = n / 2;
		glBegin(GL_POLYGON);
		while (n--) {
			glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
			alfa += angle;
			glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
		}
		glEnd();
	}
}