#include "PerlinNoise.h"
#include <Math.h>
PerlinNoise::PerlinNoise()
{
	persistence = 0;
	frequency = 0;
	amplitude = 0;
	octaves = 0;
	randomseed = 0;
	for (int i = 0; i < 256; i++) p[256 + i] = p[i] = permutation[i];
}

PerlinNoise::PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
	persistence = _persistence;
	frequency = _frequency;
	amplitude = _amplitude;
	octaves = _octaves;
	randomseed = 2 + _randomseed * _randomseed;
}

void PerlinNoise::Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
	persistence = _persistence;
	frequency = _frequency;
	amplitude = _amplitude;
	octaves = _octaves;
	randomseed = 2 + _randomseed * _randomseed;
}

double PerlinNoise::GetHeight(double x, double y) const
{
	return amplitude * Total(x, y);
}

double PerlinNoise::Total(double i, double j) const
{
	//properties of one octave (changing each loop)
	double t = 0.0f;
	double _amplitude = 1;
	double maxAmp = 0.0f;
	double freq = frequency;

	for (int k = 0; k < octaves; k++)
	{
		t += GetValue(j * freq + randomseed, i * freq + randomseed) * _amplitude;
		//t += noise2(j * freq + randomseed, i * freq + randomseed, randomseed) * _amplitude;
		maxAmp += _amplitude;
		_amplitude *= persistence;
		freq *= 2;
	}

	return t/* /maxAmp */;
}

double PerlinNoise::GetValue(double x, double y) const
{
	int Xint = (int)x;
	int Yint = (int)y;
	double Xfrac = x - Xint;
	double Yfrac = y - Yint;

	//noise values
	double n01 = Noise(Xint - 1, Yint - 1);
	double n02 = Noise(Xint + 1, Yint - 1);
	double n03 = Noise(Xint - 1, Yint + 1);
	double n04 = Noise(Xint + 1, Yint + 1);
	double n05 = Noise(Xint - 1, Yint);
	double n06 = Noise(Xint + 1, Yint);
	double n07 = Noise(Xint, Yint - 1);
	double n08 = Noise(Xint, Yint + 1);
	double n09 = Noise(Xint, Yint);

	double n12 = Noise(Xint + 2, Yint - 1);
	double n14 = Noise(Xint + 2, Yint + 1);
	double n16 = Noise(Xint + 2, Yint);

	double n23 = Noise(Xint - 1, Yint + 2);
	double n24 = Noise(Xint + 1, Yint + 2);
	double n28 = Noise(Xint, Yint + 2);

	double n34 = Noise(Xint + 2, Yint + 2);

	//find the noise values of the four corners
	double x0y0 = 0.0625*(n01 + n02 + n03 + n04) + 0.125*(n05 + n06 + n07 + n08) + 0.25*(n09);
	double x1y0 = 0.0625*(n07 + n12 + n08 + n14) + 0.125*(n09 + n16 + n02 + n04) + 0.25*(n06);
	double x0y1 = 0.0625*(n05 + n06 + n23 + n24) + 0.125*(n03 + n04 + n09 + n28) + 0.25*(n08);
	double x1y1 = 0.0625*(n09 + n16 + n28 + n34) + 0.125*(n08 + n14 + n06 + n24) + 0.25*(n04);

	//interpolate between those values according to the x and y fractions
	double v1 = Interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
	double v2 = Interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
	double fin = Interpolate(v1, v2, Yfrac);  //interpolate in y direction

	return fin;
}

double PerlinNoise::Interpolate(double x, double y, double a) const
{
	double negA = 1.0 - a;
	double negASqr = negA * negA;
	double fac1 = 3.0 * (negASqr)-2.0 * (negASqr * negA);
	double aSqr = a * a;
	double fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

	return x * fac1 + y * fac2; //add the weighted factors
}

double PerlinNoise::Noise(int x, int y) const
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}
double PerlinNoise::fade(double t) const { return t * t * t * (t * (t * 6 - 15) + 10); }
double PerlinNoise::lerp(double t, double a, double b) const { return a + t * (b - a); }
double PerlinNoise::grad(int hash, double x, double y, double z) const {
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
		v = h<4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
double PerlinNoise::noise2(double x, double y, double z) const {
	int X = (int)floor(x) & 255,                  // FIND UNIT CUBE THAT
		Y = (int)floor(y) & 255,                  // CONTAINS POINT.
		Z = (int)floor(z) & 255;
	x -=floor(x);                                // FIND RELATIVE X,Y,Z
	y -=floor(y);                                // OF POINT IN CUBE.
	z -=floor(z);
	double u = fade(x),                                // COMPUTE FADE CURVES
		v = fade(y),                                // FOR EACH OF X,Y,Z.
		w = fade(z);
	int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,      // HASH COORDINATES OF
		B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;      // THE 8 CUBE CORNERS,

	return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),  // AND ADD
		grad(p[BA], x - 1, y, z)), // BLENDED
		lerp(u, grad(p[AB], x, y - 1, z),  // RESULTS
			grad(p[BB], x - 1, y - 1, z))),// FROM  8
		lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),  // CORNERS
			grad(p[BA + 1], x - 1, y, z - 1)), // OF CUBE
			lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
				grad(p[BB + 1], x - 1, y - 1, z - 1))));
}