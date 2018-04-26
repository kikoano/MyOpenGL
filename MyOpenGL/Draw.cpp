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
	static void polyederElementColorAngle(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices, float * colors, float start, float end) {
		/* x0, y0 centar, r radius na n-agolnikot */
		float angle, alfa;
		angle = 2 * M_PI / n; // najdi go agolot
		alfa = start;
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


		while (alfa <= end) {

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

			float a = glm::degrees(alfa) + 0.01;

			if (a >= 0 && a < 60) {
				vertices.push_back(1.0f);
				vertices.push_back(colorI);
				vertices.push_back(0.0f);
			}

			else if (a >= 60 && a < 120) {
				vertices.push_back(1.0f - colorI);
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
				vertices.push_back(1.0f - colorI);
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
				vertices.push_back(1.0f - colorI);
			}
			else {
				vertices.push_back(1.0f);
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);

			}
			colorI += colorInit;
			if (colorI > 1.0f) {
				colorI = colorInit;
			}
			alfa += angle;
		}

	}
	static void polyederElement(int n, float x0, float y0, float r, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		polyederElement(n, x0, y0, r, r, vertices, indices);
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
	static void sphere(float x0, float y0, float z0, int lats, int longs, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		int i, j;
		int indicator = 0;
		for (i = 0; i <= lats; i++) {
			double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
			double z0 = sin(lat0);
			double zr0 = cos(lat0);

			double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			for (j = 0; j <= longs; j++) {
				double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
				double x = cos(lng);
				double y = sin(lng);

				vertices.push_back(x * zr0);
				vertices.push_back(y * zr0);
				vertices.push_back(z0);
				indices.push_back(indicator);
				indicator++;


				vertices.push_back(x * zr0 * x * zr0);
				vertices.push_back(y * zr0 * y * zr0);
				vertices.push_back(1.0f);


				vertices.push_back(x * zr1);
				vertices.push_back(y * zr1);
				vertices.push_back(z1);
				indices.push_back(indicator);
				indicator++;

				vertices.push_back(x * zr0 * x * zr0);
				vertices.push_back(y * zr0 * y * zr0);
				vertices.push_back(1.0f);

			}
		}
	}
	static void spherePacman(float x0, float y0, float z0, int lats, int longs, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		int i, j;
		int indicator = 0;
		for (i = 0; i <= lats; i++) {
			double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
			double z0 = sin(lat0);
			double zr0 = cos(lat0);

			double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			for (j = 0; j <= longs; j++) {
				double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
				double x = cos(lng);
				double y = sin(lng);

				if (lng > glm::pi<double>()/2)
					break;

				vertices.push_back(x * zr0);
				vertices.push_back(y * zr0);
				vertices.push_back(z0);
				indices.push_back(indicator);
				indicator++;

				vertices.push_back(x * zr1);
				vertices.push_back(y * zr1);
				vertices.push_back(z1);
				indices.push_back(indicator);
				indicator++;


			}
		}
	}
	static void sphere2(float x0, float y0, float z0, int lats, int longs, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		int i, j;
		int indicator = 0;
		for (i = 0; i <= lats; i++) {
			double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
			double z0 = sin(lat0);
			double zr0 = cos(lat0);

			double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			for (j = 0; j <= longs; j++) {
				double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
				double x = cos(lng);
				double y = sin(lng);

				vertices.push_back(x * zr0);
				vertices.push_back(y * zr0);
				vertices.push_back(z0);
				indices.push_back(indicator);
				indicator++;

				vertices.push_back(x * zr1);
				vertices.push_back(y * zr1);
				vertices.push_back(z1);
				indices.push_back(indicator);
				indicator++;


			}
		}
	}
	static void drawTorus(int numc,int numt,std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		int index = 0;
		int i, j, k;
		double s, t, x, y, z, twopi;
		twopi = 2 * glm::pi<float>();
		for (i = 0; i < numc; i++) {
			for (j = 0; j <= numt; j++) {
				for (k = 1; k >= 0; k--) {
					s = (i + k) % numc + 0.5;
					t = j % numt;

					x = (1 + .1*cos(s*twopi / numc))*cos(t*twopi / numt);
					y = (1 + .1*cos(s*twopi / numc))*sin(t*twopi / numt);
					z = .1 * sin(s * twopi / numc);
					vertices.push_back(x);
					vertices.push_back(y);
					vertices.push_back(z);
					indices.push_back(index++);
				}
			}
		}
	}
	
	static void sphereTexture2(int n, float x0, float y0, float r, float rr, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
		float res = 0.02f;
		int i = 0;
		for (float angle2 = -glm::half_pi<float>(); angle2 <= glm::half_pi<float>(); angle2 += res) {
			for (float angle1 = 0.0f; angle1 <= glm::two_pi<float>(); angle1 += res) {

				vertices.push_back(cos(angle1)*cos(angle2)); //x
				vertices.push_back(sin(angle2)); //y
				vertices.push_back(sin(angle1)*cos(angle2)); //z
				indices.push_back(i++);

				vertices.push_back(sin(angle2) * sin(angle2));
				vertices.push_back(cos(angle1)*cos(angle2) *cos(angle1)*cos(angle2));
				vertices.push_back(1.0f);

				vertices.push_back(cos(angle1)*cos(angle2) + res); //x
				vertices.push_back(sin(angle2) + res); //y
				vertices.push_back(sin(angle1)*cos(angle2) + res); //z
				indices.push_back(i++);

				vertices.push_back(sin(angle2) * sin(angle2));
				vertices.push_back(cos(angle1)*cos(angle2) *cos(angle1)*cos(angle2));
				vertices.push_back(1.0f);
			}
			//}
		}
	}

	/*  6  void drawSphere(double r, int lats, int longs) {
  7      int i, j;
  8      for(i = 0; i <= lats; i++) {
  9          double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
 10          double z0  = sin(lat0);
 11          double zr0 =  cos(lat0);

 12          double lat1 = M_PI * (-0.5 + (double) i / lats);
 13          double z1 = sin(lat1);
 14          double zr1 = cos(lat1);

 15          glBegin(GL_QUAD_STRIP);
 16          for(j = 0; j <= longs; j++) {
 17              double lng = 2 * M_PI * (double) (j - 1) / longs;
 18              double x = cos(lng);
 19              double y = sin(lng);

 20              glNormal3f(x * zr0, y * zr0, z0);
 21              glVertex3f(x * zr0, y * zr0, z0);
 22              glNormal3f(x * zr1, y * zr1, z1);
 23              glVertex3f(x * zr1, y * zr1, z1);
 24          }
 25          glEnd();
 26      }
 27  }*/
 /*

 x = r * sin(Lat) * cos(lat)
 y = r * sin(Lat) * sin(lon)
 z = r * cos(Lat)

 where
 r = radius
 lat = the angle down from the north pole
 lon = Longitude East from Prime Meridian
 */
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