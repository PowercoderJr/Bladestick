#include "SceneObject.h"
#include "Vector3D.h"
#include "Utils.h"
#include "Scene.h"

using namespace Bladestick::Drawing;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System;

const int N = 10;

SceneObject::SceneObject()
{
	this->offset = gcnew Vector3D(0, 0, 0);
	this->scaling = gcnew Vector3D(1, 1, 1);
	this->rotation = gcnew Vector3D(0, 0, 0);

	this->vertices = gcnew array<Vector3D ^>(N);
	this->indices = gcnew array<int>(3 * N);
	this->colors = gcnew array<Color>(N);
}

SceneObject::SceneObject(array<Vector3D^>^ vertices, array<int>^ indices, array<System::Drawing::Color>^ colors)
{
	this->offset = gcnew Vector3D(0, 0, 0);
	this->scaling = gcnew Vector3D(1, 1, 1);
	this->rotation = gcnew Vector3D(0, 0, 0);

	this->vertices = vertices;
	this->indices = indices;
	this->colors = colors;
}

void SceneObject::transform(Camera camera)
{
	double alpha = degToRad(rotation->x);
	double beta = degToRad(rotation->y);
	double gamma = degToRad(rotation->z);

#define sin Math::Sin
#define cos Math::Cos
	for each (Vector3D ^ v in vertices)
	{
		//Масштабирование, вращение, смещение
		v->mx = offset->x + cos(gamma) * (v->x * scaling->x * cos(beta) +
				(v->z* scaling->z * cos(alpha) + v->y * scaling->y * sin(alpha)) *
				sin(beta)) - (v->y * scaling->y * cos(alpha) - v->z * scaling->z *
				sin(alpha)) * sin(gamma);
		v->my = offset->y + cos(gamma) * (v->y * scaling->y * cos(alpha) - v->z *
				scaling->z * sin(alpha)) + (v->x * scaling->x * cos(beta) +
				(v->z* scaling->z * cos(alpha) + v->y * scaling->y * sin(alpha)) *
				sin(beta)) * sin(gamma);
		v->mz = offset->z + cos(beta) * (v->z* scaling->z * cos(alpha) + v->y *
				scaling->y * sin(alpha)) - v->x * scaling->x * sin(beta);

		if (camera.perspective)
		{
			double persp = -v->mz / camera.position->z + 1;
			v->mx /= persp;
			v->my /= persp;
			v->mz /= persp;
		}
	}
#undef sin
#undef cos
}

void SceneObject::setOffset(double x, double y, double z)
{
	this->offset = gcnew Vector3D(x, y, z);
}

void SceneObject::setOffset(Vector3D ^ offset)
{
	setOffset(offset->x, offset->y, offset->z);
}

void SceneObject::setScaling(double a, double b, double c)
{
	this->scaling = gcnew Vector3D(a, b, c);
}

void SceneObject::setScaling(Vector3D ^ factors)
{
	setScaling(factors->x, factors->y, factors->z);
}

void SceneObject::setRotation(double alphaDeg, double betaDeg, double gammaDeg)
{
	this->rotation = gcnew Vector3D(alphaDeg, betaDeg, gammaDeg);
}

void SceneObject::setRotation(Vector3D ^ angles)
{
	setRotation(angles->x, angles->y, angles->z);
}

void SceneObject::moveOriginal(double x, double y, double z)
{
	for (int i = 0; i < vertices->Length; ++i)
		vertices[i] = vertices[i]->add(x, y, z);
}

void SceneObject::moveOriginal(Vector3D ^ offset)
{
	moveOriginal(offset->x, offset->y, offset->z);
}

void SceneObject::loadFromStream(Stream ^ stream)
{
	List<Vector3D ^> ^ vertices = gcnew List<Vector3D ^>(N);
	List<int> ^ indices = gcnew List<int>(3 * N);
	List<Color> ^ colors = gcnew List<Color>(N);
	String ^ line;
	Random ^ rnd = gcnew Random();
	StreamReader ^ reader = gcnew StreamReader(stream);

	while ((line = reader->ReadLine()) != nullptr)
	{
		if (line->Length == 0)
			continue;

		if (line->Length >= 3 && line->Substring(0, 3)->Equals("v  "))
		{
			array<String ^> ^ data = line->Split(' ');
			array<double> ^ coords = gcnew array<double>(3);
			for (int i = 0; i < 3; ++i)
				coords[i] = Double::Parse(data[i + 2]->Split('/')[0]->Replace('.', ','));
			vertices->Add(gcnew Vector3D(coords[0], coords[1], coords[2]));
		}
		else if (line->Length >= 2 && line->Substring(0, 2)->Equals("f "))
		{
			array<String ^> ^ data = line->Split(' ');
			array<int> ^ colorValues = gcnew array<int>(3);
			for (int i = 0; i < 3; ++i)
			{
				array<String ^> ^ splitted = data[i + 1]->Split('/');
				indices->Add(int::Parse(splitted[0]));
				colorValues[i] = splitted->Length >= 4 ? int::Parse(splitted[3]) : rnd->Next(256);
			}
			colors->Add(Color::FromArgb(colorValues[0], colorValues[1], colorValues[2]));
		}
	}
	this->vertices = vertices->ToArray();
	this->indices = indices->ToArray();
	this->colors = colors->ToArray();
}

SceneObject ^ SceneObject::buildBladestick(double handleLength, double inBladeRadius,
	double exBladeRadius, double bladeThickness, double primarySpikeLength,
	double secondarySpikeLength, double primarySpikeAngle, double secondarySpikeAngle,
	int secondarySpikesCount, int ringsCount)
{
	Random ^ rnd = gcnew Random();

	SceneObject ^ handle = buildHandle(gcnew Vector3D(0, -150, 0), 10, 200, 10);
	SceneObject ^ bladeRing = buildBladeRing(gcnew Vector3D(0, 0, -10), 40, 75, 20, 10);
	SceneObject ^ cross = buildCross(250, 50, 40);

	//SceneObject ^ result = Unite(gcnew array<SceneObject ^>(3){ handle, bladeRing, cross });
	const int N_SPIKES = 8;
	array<SceneObject ^> ^ spikes = gcnew array<SceneObject ^>(N_SPIKES);
	double alpha = 0;
	double dAlpha = 360.0 / N_SPIKES;
	for (int i = 0; i < N_SPIKES; ++i)
	{
		spikes[i] = buildSpike(100, alpha, 40, 25, 60, 30);
		alpha += dAlpha;
	}
	SceneObject ^ result = Unite(spikes);
	//DEBUG
	int colorsCount = result->indices->Length / 3;
	result->colors = gcnew array<Color>(colorsCount);
	for (int i = 0; i < colorsCount; ++i)
		result->colors[i] = Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256));

	return result;
}

SceneObject ^ SceneObject::Unite(array<SceneObject^>^ components)
{
	int totalVCount = 0, totalICount = 0;
	for (int i = 0; i < components->Length; ++i)
	{
		totalVCount += components[i]->vertices->Length;
		totalICount += components[i]->indices->Length;
	}

	List<Vector3D ^> ^ vTotal = gcnew List<Vector3D ^>(totalVCount);
	List<int> ^ iTotal = gcnew List<int>(totalICount);
	List<Color> ^ cTotal = gcnew List<Color>(totalICount / 3);
	for (int i = 0; i < components->Length; ++i)
	{
		int vOffset = vTotal->Count;
		vTotal->AddRange(components[i]->vertices);
		int iOffset = iTotal->Count;
		iTotal->AddRange(components[i]->indices);
		for (int j = iOffset; j < iTotal->Count; ++j)
			iTotal[j] += vOffset;
		cTotal->AddRange(components[i]->colors);
	}

	return gcnew SceneObject(vTotal->ToArray(), iTotal->ToArray(), cTotal->ToArray());
}

//vertices: nEdges * 2 + 2
//indices: nEdges * 12
SceneObject ^ SceneObject::buildHandle(Vector3D ^ bottomCenter, double radius, double height, int nEdges)
{
	const int INDICES_MUL = 12;
	Vector3D ^ topCenter = bottomCenter->add(0, height, 0);
	//*vertices = gcnew List<Vector3D^>(nEdges * 2 + 2);
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(nEdges * 2 + 2);
	//*indices = gcnew List<int>(nEdges * INDICES_MUL);
	array<int> ^ iArr = gcnew array<int>(nEdges * INDICES_MUL);

	Vector3D bc = *bottomCenter;
	vArr[0] = %bc;
	Vector3D tc = *topCenter;
	vArr[nEdges + 1] = %tc;

	double dAlpha = degToRad(360.0 / nEdges);
	double alpha = 0;
	for (int i = 1; i <= nEdges; ++i)
	{
		double x = bottomCenter->x + radius * Math::Cos(alpha);
		double z = bottomCenter->z + radius * Math::Sin(alpha);
		alpha += dAlpha;

		vArr[i] = gcnew Vector3D(x, bottomCenter->y, z);
		vArr[nEdges + 1 + i] = gcnew Vector3D(x, topCenter->y, z);

		int mi = (i - 1) * INDICES_MUL;
		iArr[mi] = i + 1;
		iArr[mi + 1] = i + 2;
		iArr[mi + 2] = 1;
		iArr[mi + 3] = nEdges + 2 + i;
		iArr[mi + 4] = nEdges + 3 + i;
		iArr[mi + 5] = nEdges + 1 + 1;
		iArr[mi + 6] = iArr[mi];
		iArr[mi + 7] = iArr[mi + 1];
		iArr[mi + 8] = iArr[mi + 3];
		iArr[mi + 9] = iArr[mi + 3];
		iArr[mi + 10] = iArr[mi + 4];
		iArr[mi + 11] = iArr[mi + 1];
	}

	int closing = (nEdges - 1) * INDICES_MUL;
	iArr[closing] = nEdges + 1;
	iArr[closing + 1] = 2;
	iArr[closing + 2] = 1;
	iArr[closing + 3] = nEdges * 2 + 2;
	iArr[closing + 4] = nEdges + 3;
	iArr[closing + 5] = nEdges + 2;
	iArr[closing + 6] = iArr[closing];
	iArr[closing + 7] = iArr[closing + 1];
	iArr[closing + 8] = iArr[closing + 3];
	iArr[closing + 9] = iArr[closing + 3];
	iArr[closing + 10] = iArr[closing + 4];
	iArr[closing + 11] = iArr[closing + 1];

	return gcnew SceneObject(vArr, iArr, gcnew array<Color>(0));
}

//vertices: nEdges * 5
//indices: nEdges * 30
SceneObject ^ SceneObject::buildBladeRing(Vector3D ^ nearCenter, double inRadius, double exRadius, double length, int nEdges)
{
	const int INDICES_MUL = 30;
	Vector3D ^ farCenter = nearCenter->add(0, 0, length);
	double bevelDist = inRadius + (exRadius - inRadius) * 0.4;
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(nEdges * 5);
	array<int> ^ iArr = gcnew array<int>(nEdges * INDICES_MUL);

	double dAlpha = degToRad(360.0 / nEdges);
	double alpha = 0;
	for (int i = 0; i < nEdges; ++i)
	{
		double sin = Math::Sin(alpha);
		double cos = Math::Cos(alpha);
		double inx = nearCenter->x + inRadius * cos;
		double iny = nearCenter->y + inRadius * sin;
		double bvx = nearCenter->x + bevelDist * cos;
		double bvy = nearCenter->y + bevelDist * sin;
		double exx = nearCenter->x + exRadius * cos;
		double exy = nearCenter->y + exRadius * sin;
		double exz = nearCenter->z + (farCenter->z - nearCenter->z) / 2; //TOOD: >>1?
		alpha += dAlpha;

		int ex = i;
		int nBv = nEdges + i;
		int nIn = nEdges * 2 + i;
		int fIn = nEdges * 3 + i;
		int fBv = nEdges * 4 + i;
		vArr[ex ] = gcnew Vector3D(exx, exy, exz);
		vArr[nBv] = gcnew Vector3D(bvx, bvy, nearCenter->z);
		vArr[nIn] = gcnew Vector3D(inx, iny, nearCenter->z);
		vArr[fIn] = gcnew Vector3D(inx, iny, farCenter->z);
		vArr[fBv] = gcnew Vector3D(bvx, bvy, farCenter->z);

		int mi = i * INDICES_MUL;
		iArr[mi] = nBv + 1;
		iArr[mi + 1] = nBv + 2;
		iArr[mi + 2] = ex + 1;
		iArr[mi + 3] = nBv + 2;
		iArr[mi + 4] = ex + 1;
		iArr[mi + 5] = ex + 2;

		iArr[mi + 6] = nIn + 1;
		iArr[mi + 7] = nIn + 2;
		iArr[mi + 8] = nBv + 1;
		iArr[mi + 9] = nIn + 2;
		iArr[mi + 10] = nBv + 1;
		iArr[mi + 11] = nBv + 2;

		iArr[mi + 12] = nIn + 1;
		iArr[mi + 13] = nIn + 2;
		iArr[mi + 14] = fIn + 1;
		iArr[mi + 15] = nIn + 2;
		iArr[mi + 16] = fIn + 1;
		iArr[mi + 17] = fIn + 2;

		iArr[mi + 18] = fIn + 1;
		iArr[mi + 19] = fIn + 2;
		iArr[mi + 20] = fBv + 1;
		iArr[mi + 21] = fIn + 2;
		iArr[mi + 22] = fBv + 1;
		iArr[mi + 23] = fBv + 2;

		iArr[mi + 24] = ex + 1;
		iArr[mi + 25] = ex + 2;
		iArr[mi + 26] = fBv + 1;
		iArr[mi + 27] = ex + 2;
		iArr[mi + 28] = fBv + 1;
		iArr[mi + 29] = fBv + 2;
	}

	int closing = (nEdges - 1) * INDICES_MUL;
	iArr[closing] = nEdges * 2;
	iArr[closing + 1] = nEdges + 1;
	iArr[closing + 2] = nEdges;
	iArr[closing + 3] = nEdges + 1;
	iArr[closing + 4] = nEdges;
	iArr[closing + 5] = 1;

	iArr[closing + 6] = nEdges * 3;
	iArr[closing + 7] = nEdges * 2 + 1;
	iArr[closing + 8] = nEdges * 2;
	iArr[closing + 9] = nEdges * 2 + 1;
	iArr[closing + 10] = nEdges * 2;
	iArr[closing + 11] = nEdges + 1;

	iArr[closing + 12] = nEdges * 3;
	iArr[closing + 13] = nEdges * 2 + 1;
	iArr[closing + 14] = nEdges * 4;
	iArr[closing + 15] = nEdges * 2 + 1;
	iArr[closing + 16] = nEdges * 4;
	iArr[closing + 17] = nEdges * 3 + 1;

	iArr[closing + 18] = nEdges * 4;
	iArr[closing + 19] = nEdges * 3 + 1;
	iArr[closing + 20] = nEdges * 5;
	iArr[closing + 21] = nEdges * 3 + 1;
	iArr[closing + 22] = nEdges * 5;
	iArr[closing + 23] = nEdges * 4 + 1;

	iArr[closing + 24] = nEdges;
	iArr[closing + 25] = 1;
	iArr[closing + 26] = nEdges * 5;
	iArr[closing + 27] = 1;
	iArr[closing + 28] = nEdges * 5;
	iArr[closing + 29] = nEdges * 4 + 1;

	return gcnew SceneObject(vArr, iArr, gcnew array<Color>(0));
}

//vertices: 24
//indices: 108
SceneObject ^ SceneObject::buildCross(double pLength, double pWidth, double pThickness)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(24);
	array<int> ^ iArr = gcnew array<int>(108); //(8 * 4 + 4) * 3

	double hWidth = pWidth / 2;
	double hThickness = pThickness / 2;

	const int VERTICES_PER_PART = 4;
	////Каря лопастей
	//Левая
	vArr[0] = gcnew Vector3D(-pLength, -hWidth, -hThickness);
	vArr[1] = vArr[0]->scale(1, -1, 1);
	vArr[2] = vArr[0]->scale(1, -1, -1);
	vArr[3] = vArr[0]->scale(1, 1, -1);

	//Верхняя
	vArr[4] = gcnew Vector3D(-hWidth, pLength, -hThickness);
	vArr[5] = vArr[4]->scale(-1, 1, 1);
	vArr[6] = vArr[4]->scale(-1, 1, -1);
	vArr[7] = vArr[4]->scale(1, 1, -1);

	//Правая
	for (int i = 0; i < VERTICES_PER_PART; ++i)
		vArr[i + VERTICES_PER_PART * 2] = vArr[i]->scale(-1, 1, 1);

	//Нижняя
	for (int i = VERTICES_PER_PART; i < VERTICES_PER_PART * 2; ++i)
		vArr[i + VERTICES_PER_PART * 2] = vArr[i]->scale(1, -1, 1);
	////

	//Центральный куб
	vArr[16] = gcnew Vector3D(-hWidth, -hWidth, -hThickness);
	vArr[17] = vArr[16]->scale(1, -1, 1);
	vArr[18] = vArr[16]->scale(-1, -1, 1);
	vArr[19] = vArr[16]->scale(-1, 1, 1);
	vArr[20] = vArr[16]->scale(1, 1, -1);
	vArr[21] = vArr[16]->scale(1, -1, -1);
	vArr[22] = vArr[16]->scale(-1, -1, -1);
	vArr[23] = vArr[16]->scale(-1, 1, -1);

#pragma region Indices
	//Левая
	iArr[0] = 1;
	iArr[1] = 2;
	iArr[2] = 17;
	iArr[3] = 2;
	iArr[4] = 17;
	iArr[5] = 18;
	iArr[6] = 2;
	iArr[7] = 3;
	iArr[8] = 18;
	iArr[9] = 3;
	iArr[10] = 18;
	iArr[11] = 22;
	iArr[12] = 3;
	iArr[13] = 4;
	iArr[14] = 22;
	iArr[15] = 4;
	iArr[16] = 22;
	iArr[17] = 21;
	iArr[18] = 4;
	iArr[19] = 1;
	iArr[20] = 21;
	iArr[21] = 1;
	iArr[22] = 21;
	iArr[23] = 17;

	//Верхняя
	iArr[24] = 5;
	iArr[25] = 6;
	iArr[26] = 18;
	iArr[27] = 6;
	iArr[28] = 18;
	iArr[29] = 19;
	iArr[30] = 6;
	iArr[31] = 7;
	iArr[32] = 19;
	iArr[33] = 7;
	iArr[34] = 19;
	iArr[35] = 23;
	iArr[36] = 7;
	iArr[37] = 8;
	iArr[38] = 23;
	iArr[39] = 8;
	iArr[40] = 23;
	iArr[41] = 22;
	iArr[42] = 8;
	iArr[43] = 5;
	iArr[44] = 22;
	iArr[45] = 5;
	iArr[46] = 22;
	iArr[47] = 18;

	//Правая
	iArr[48] = 9;
	iArr[49] = 10;
	iArr[50] = 20;
	iArr[51] = 10;
	iArr[52] = 20;
	iArr[53] = 19;
	iArr[54] = 10;
	iArr[55] = 11;
	iArr[56] = 19;
	iArr[57] = 11;
	iArr[58] = 19;
	iArr[59] = 23;
	iArr[60] = 11;
	iArr[61] = 12;
	iArr[62] = 23;
	iArr[63] = 12;
	iArr[64] = 23;
	iArr[65] = 24;
	iArr[66] = 12;
	iArr[67] = 9;
	iArr[68] = 24;
	iArr[69] = 9;
	iArr[70] = 24;
	iArr[71] = 20;

	//Нижняя
	iArr[72] = 13;
	iArr[73] = 14;
	iArr[74] = 17;
	iArr[75] = 14;
	iArr[76] = 17;
	iArr[77] = 20;
	iArr[78] = 14;
	iArr[79] = 15;
	iArr[80] = 20;
	iArr[81] = 15;
	iArr[82] = 20;
	iArr[83] = 24;
	iArr[84] = 15;
	iArr[85] = 16;
	iArr[86] = 24;
	iArr[87] = 16;
	iArr[88] = 24;
	iArr[89] = 21;
	iArr[90] = 16;
	iArr[91] = 13;
	iArr[92] = 21;
	iArr[93] = 13;
	iArr[94] = 21;
	iArr[95] = 17;

	//Центр
	iArr[96] = 17;
	iArr[97] = 18;
	iArr[98] = 20;
	iArr[99] = 18;
	iArr[100] = 20;
	iArr[101] = 19;
	iArr[102] = 21;
	iArr[103] = 22;
	iArr[104] = 24;
	iArr[105] = 22;
	iArr[106] = 24;
	iArr[107] = 23;
#pragma endregion

	return gcnew SceneObject(vArr, iArr, gcnew array<Color>(0));
}

//vertices: 6
//indices: 24
SceneObject ^ SceneObject::buildSpike(double distance, double alphaDeg, double betaDeg, double thickness, double exLength, double inLength)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(6);
	array<int> ^ iArr = gcnew array<int>(24);

	double alpha = degToRad(alphaDeg);
	double beta = degToRad(betaDeg);
	Vector3D ^ center = gcnew Vector3D(distance * Math::Cos(alpha), distance * Math::Sin(alpha), 0);
	Vector3D ^ inV = gcnew Vector3D((distance - inLength) * Math::Cos(alpha), (distance - inLength) * Math::Sin(alpha), 0);
	Vector3D ^ exV = gcnew Vector3D((distance + exLength) * Math::Cos(alpha), (distance + exLength) * Math::Sin(alpha), 0);
	double sideDist = exLength * Math::Tan(beta / 2);
	Vector3D ^ dir = (exV - center)->normalized();
	Vector3D ^ sideVec = (gcnew Vector3D(-dir->y, dir->x, 0))->scale(sideDist);
	
	vArr[0] = inV;
	vArr[1] = center - sideVec;
	vArr[2] = center->subtract(0, 0, thickness / 2);
	vArr[3] = center + sideVec;
	vArr[4] = center->add(0, 0, thickness / 2);
	vArr[5] = exV;

	iArr[0] = 1;
	iArr[1] = 2;
	iArr[2] = 3;
	iArr[3] = 1;
	iArr[4] = 3;
	iArr[5] = 4;
	iArr[6] = 1;
	iArr[7] = 4;
	iArr[8] = 5;
	iArr[9] = 1;
	iArr[10] = 5;
	iArr[11] = 2;
	iArr[12] = 6;
	iArr[13] = 2;
	iArr[14] = 3;
	iArr[15] = 6;
	iArr[16] = 3;
	iArr[17] = 4;
	iArr[18] = 6;
	iArr[19] = 4;
	iArr[20] = 5;
	iArr[21] = 6;
	iArr[22] = 5;
	iArr[23] = 2;

	return gcnew SceneObject(vArr, iArr, gcnew array<Color>(0));
}
