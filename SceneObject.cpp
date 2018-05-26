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

SceneObject::SceneObject(array<Vector3D^>^ vertices, array<int>^ indices, array<Color>^ colors, String ^ name)
{
	this->offset = gcnew Vector3D(0, 0, 0);
	this->scaling = gcnew Vector3D(1, 1, 1);
	this->rotation = gcnew Vector3D(0, 0, 0);

	this->vertices = vertices;
	this->indices = indices;
	this->colors = colors;

	this->name = gcnew String(name);
}

SceneObject::SceneObject(array<Vector3D^>^ vertices, array<int>^ indices, array<Color>^ colors) : SceneObject::SceneObject(vertices, indices, colors, "Объект")
{
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

String ^ SceneObject::ToString()
{
	return gcnew String(name);
}

SceneObject ^ SceneObject::buildBladestick(double handleLength, int handleRingsCount,
	int handleEdgesCount, double inBladeRadius, double exBladeRadius,
	int bladeEdgesCount, double bladeThickness,
	double primarySpikeLength, double primarySpikeAngle,
	double secondarySpikeLength, double secondarySpikeAngle,
	int secondarySpikesCount, array<Color> ^ palette)
{
	Random ^ rnd = gcnew Random();

	const double bevelBladeRadius = inBladeRadius + (exBladeRadius - inBladeRadius) * 0.6;
	SceneObject ^ bladeRing = buildBladeRing(inBladeRadius, bevelBladeRadius, exBladeRadius, bladeThickness, bladeEdgesCount, gcnew array<Color>(2) { palette[1], palette[2] });

	const double crossPartLength = inBladeRadius;
	const double crossPartWidth = inBladeRadius * 0.25;
	const double crossPartThickness = bladeThickness * 0.8;
	SceneObject ^ cross = buildCross(crossPartLength, crossPartWidth, crossPartThickness, gcnew array<Color>(1) { palette[1] });

	const int spikesCount = secondarySpikesCount + 4;
	const double primarySpikeBevelStartPoint = primarySpikeLength * 0.5;
	const double secondarySpikeBevelStartPoint = secondarySpikeLength * 0.5;
	const double inPrimarySpikeLength = bevelBladeRadius * 0.4;
	const double inSecondarySpikeLength = bevelBladeRadius * 0.15;
	array<SceneObject ^> ^ spikes = gcnew array<SceneObject ^>(spikesCount);
	double alphaDeg = -90;
	const double dAlphaDeg = 360.0 / spikesCount;
	for (int i = 0; i < spikesCount; ++i)
	{
		int tmp = Math::Floor(alphaDeg);
		if (!cmpDoubles(alphaDeg, tmp) && tmp % 90 == 0)
			spikes[i] = buildSpike(inBladeRadius, bevelBladeRadius, alphaDeg, primarySpikeAngle, bladeThickness, inPrimarySpikeLength, primarySpikeBevelStartPoint, primarySpikeLength, gcnew array<Color>(2) { palette[1], cmpDoubles(alphaDeg, -90) ? palette[2] : palette[1] });
		else
			spikes[i] = buildSpike(inBladeRadius, bevelBladeRadius, alphaDeg, secondarySpikeAngle, bladeThickness, inSecondarySpikeLength, secondarySpikeBevelStartPoint, secondarySpikeLength, gcnew array<Color>(2) { palette[1], palette[2] });
		alphaDeg += dAlphaDeg;
	}
	
	SceneObject ^ result = unite(spikes);
	result = unite(gcnew array<SceneObject ^>(3) {bladeRing, cross, result});
	result->moveOriginal(0, exBladeRadius, 0);

	const double handleRadius = bladeThickness / 2;
	array<SceneObject ^> ^ handleRings = gcnew array<SceneObject ^>(handleRingsCount);

	const double handleRingRadius = handleRadius + 3;
	const double handleRingHeight = 3;
	const double handleRingInterval = handleLength / 3 / (handleRingsCount + 1);
	SceneObject ^ handle = buildHandle(handleRadius, handleLength, handleEdgesCount, gcnew array<Color>(1) { palette[0] });
	handle->moveOriginal(0, -handleLength / 2, 0);

	for (int i = 0; i < handleRingsCount; ++i)
	{
		handleRings[i] = buildHandle(handleRingRadius, handleRingHeight, handleEdgesCount, gcnew array<Color>(1) { palette[1] });
		handleRings[i]->moveOriginal(0, (i + 1) * handleRingInterval, 0);
	}
	SceneObject ^ unitedRings = unite(handleRings);
	unitedRings->moveOriginal(0, -handleLength, 0);
	
	result = unite(gcnew array<SceneObject ^>(3) { result, handle, unitedRings });

	//DEBUG
	/*int colorsCount = result->indices->Length / 3;
	result->colors = gcnew array<Color>(colorsCount);
	for (int i = 0; i < colorsCount; ++i)
		//result->colors[i] = Color::RosyBrown;
		result->colors[i] = Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256));*/

	return result;
}

SceneObject ^ SceneObject::unite(array<SceneObject^>^ components)
{
	int totalVCount = 0, totalICount = 0;
	for (int i = 0; i < components->Length; ++i)
	{
		totalVCount += components[i]->vertices->Length;
		totalICount += components[i]->indices->Length;
	}

	Random ^ rnd = gcnew Random();
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
SceneObject ^ SceneObject::buildHandle(double radius, double height, int nEdges, array<Color> ^ palette)
{
	const int INDICES_MUL = 12;
	Vector3D ^ bottomCenter = gcnew Vector3D(0, -height / 2, 0);
	Vector3D ^ topCenter = bottomCenter->add(0, height, 0);
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(nEdges * 2 + 2);
	array<int> ^ iArr = gcnew array<int>(nEdges * INDICES_MUL);
	array<Color> ^ cArr = gcnew array<Color>(nEdges * INDICES_MUL / 3);

	Vector3D bc = *bottomCenter;
	vArr[0] = %bc;
	Vector3D tc = *topCenter;
	vArr[nEdges + 1] = %tc;

	const double FACETS_PER_ITERATION = INDICES_MUL / 3;
	double dAlpha = degToRad(360.0 / nEdges);
	double alpha = degToRad(-90);
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

		for (int j = FACETS_PER_ITERATION * (i - 1); j < FACETS_PER_ITERATION * i; ++j)
			cArr[j] = palette[0];
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

	return gcnew SceneObject(vArr, iArr, cArr);
}

//vertices: nEdges * 5
//indices: nEdges * 30
SceneObject ^ SceneObject::buildBladeRing(double inRadius, double bevelRadius, double exRadius, double thickness, int nEdges, array<Color> ^ palette)
{
	const int INDICES_MUL = 30;
	Vector3D ^ nearCenter = gcnew Vector3D(0, 0, -thickness / 2);
	Vector3D ^ farCenter = nearCenter->add(0, 0, thickness);
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(nEdges * 5);
	array<int> ^ iArr = gcnew array<int>(nEdges * INDICES_MUL);
	array<Color> ^ cArr = gcnew array<Color>(nEdges * INDICES_MUL / 3);

	double const FACETS_PER_ITERATION = INDICES_MUL / 3;
	double dAlpha = degToRad(360.0 / nEdges);
	double alpha = degToRad(-90);
	for (int i = 0; i < nEdges; ++i)
	{
		double sin = Math::Sin(alpha);
		double cos = Math::Cos(alpha);
		double inx = nearCenter->x + inRadius * cos;
		double iny = nearCenter->y + inRadius * sin;
		double bvx = nearCenter->x + bevelRadius * cos;
		double bvy = nearCenter->y + bevelRadius * sin;
		double exx = nearCenter->x + exRadius * cos;
		double exy = nearCenter->y + exRadius * sin;
		double exz = nearCenter->z + (farCenter->z - nearCenter->z) / 2;
		alpha += dAlpha;

		int ex = i;
		int nBv = nEdges + i;
		int nIn = nEdges * 2 + i;
		int fIn = nEdges * 3 + i;
		int fBv = nEdges * 4 + i;
		vArr[ex] = gcnew Vector3D(exx, exy, exz);
		vArr[nBv] = gcnew Vector3D(bvx, bvy, nearCenter->z);
		vArr[nIn] = gcnew Vector3D(inx, iny, nearCenter->z);
		vArr[fIn] = gcnew Vector3D(inx, iny, farCenter->z);
		vArr[fBv] = gcnew Vector3D(bvx, bvy, farCenter->z);

		int mii = i * INDICES_MUL;
		int mci = i * FACETS_PER_ITERATION;
		iArr[mii] = nBv + 1;
		iArr[mii + 1] = nBv + 2;
		iArr[mii + 2] = ex + 1;
		iArr[mii + 3] = nBv + 2;
		iArr[mii + 4] = ex + 1;
		iArr[mii + 5] = ex + 2;
		cArr[mci] = cArr[mci + 1] = palette[1];

		iArr[mii + 6] = nIn + 1;
		iArr[mii + 7] = nIn + 2;
		iArr[mii + 8] = nBv + 1;
		iArr[mii + 9] = nIn + 2;
		iArr[mii + 10] = nBv + 1;
		iArr[mii + 11] = nBv + 2;
		cArr[mci + 2] = cArr[mci + 3] = palette[0];

		iArr[mii + 12] = nIn + 1;
		iArr[mii + 13] = nIn + 2;
		iArr[mii + 14] = fIn + 1;
		iArr[mii + 15] = nIn + 2;
		iArr[mii + 16] = fIn + 1;
		iArr[mii + 17] = fIn + 2;
		cArr[mci + 4] = cArr[mci + 5] = palette[0];

		iArr[mii + 18] = fIn + 1;
		iArr[mii + 19] = fIn + 2;
		iArr[mii + 20] = fBv + 1;
		iArr[mii + 21] = fIn + 2;
		iArr[mii + 22] = fBv + 1;
		iArr[mii + 23] = fBv + 2;
		cArr[mci + 6] = cArr[mci + 7] = palette[0];

		iArr[mii + 24] = ex + 1;
		iArr[mii + 25] = ex + 2;
		iArr[mii + 26] = fBv + 1;
		iArr[mii + 27] = ex + 2;
		iArr[mii + 28] = fBv + 1;
		iArr[mii + 29] = fBv + 2;
		cArr[mci + 8] = cArr[mci + 9] = palette[1];
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

	return gcnew SceneObject(vArr, iArr, cArr);
}

//vertices: 24
//indices: 108
SceneObject ^ SceneObject::buildCross(double pLength, double pWidth, double pThickness, array<Color> ^ palette)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(24);
	const int N_FACETS = 36;
	array<int> ^ iArr = gcnew array<int>(N_FACETS * 3);
	array<Color> ^ cArr = gcnew array<Color>(N_FACETS);

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

	for (int i = 0; i < N_FACETS; ++i)
		cArr[i] = palette[0];

	return gcnew SceneObject(vArr, iArr, cArr);
}

//vertices: 14
//indices: 42
SceneObject ^ SceneObject::buildSpike(double inDistance, double exDistance, double alphaDeg, double betaDeg, double thickness, double inLength, double bevelStartPoint, double exLength, array<Color> ^ palette)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(14);
	const double N_FACETS = 14;
	array<int> ^ iArr = gcnew array<int>(N_FACETS * 3);
	array<Color> ^ cArr = gcnew array<Color>(N_FACETS);

	const double alpha = degToRad(alphaDeg);
	const double beta = degToRad(betaDeg);
	const double cos = Math::Cos(alpha);
	const double sin = Math::Sin(alpha);
	Vector3D ^ inCenter = gcnew Vector3D(inDistance * cos, inDistance * sin, 0);
	Vector3D ^ exCenter = gcnew Vector3D(exDistance * cos, exDistance * sin, 0);
	Vector3D ^ inV = gcnew Vector3D((inDistance - inLength) * cos, (inDistance - inLength) * sin, 0);
	Vector3D ^ exV = gcnew Vector3D((exDistance + exLength) * cos, (exDistance + exLength) * sin, 0);
	const double sideDist = exLength * Math::Tan(beta / 2);
	Vector3D ^ dir = (exV - exCenter)->normalized();
	Vector3D ^ sideVec = (gcnew Vector3D(dir->y, -dir->x, 0))->scale(sideDist);
	const double hThickness = thickness / 2;
	const double sideBevelDist = bevelStartPoint * sideDist / exLength;
	Vector3D ^ sideBevelVec = (gcnew Vector3D(dir->y, -dir->x, 0))->scale(sideBevelDist);
	Vector3D ^ nearTop = exCenter->add(bevelStartPoint * cos, bevelStartPoint * sin, -hThickness);
	Vector3D ^ nearLeft = exCenter->subtract(0, 0, hThickness) - sideBevelVec;
	Vector3D ^ nearRight = nearLeft + sideBevelVec->scale(2);
	Vector3D ^ farTop = nearTop->scale(1, 1, -1);
	Vector3D ^ farLeft = nearLeft->scale(1, 1, -1);
	Vector3D ^ farRight = nearRight->scale(1, 1, -1);

	vArr[0] = exV;
	vArr[1] = exCenter - sideVec;
	vArr[2] = exCenter + sideVec;
	vArr[3] = nearLeft;
	vArr[4] = farLeft;
	vArr[5] = nearRight;
	vArr[6] = farRight;
	vArr[7] = nearTop;
	vArr[8] = farTop;
	vArr[9] = inCenter->subtract(sideVec->x, sideVec->y, hThickness);
	vArr[10] = inCenter->subtract(sideVec->x, sideVec->y, -hThickness);
	vArr[11] = inCenter->add(sideVec->x, sideVec->y, hThickness);
	vArr[12] = inCenter->add(sideVec->x, sideVec->y, -hThickness);
	vArr[13] = inV;

	//Внешняя часть
	iArr[0] = 1;
	iArr[1] = 2;
	iArr[2] = 8;
	cArr[0] = palette[1];

	iArr[3] = 1;
	iArr[4] = 2;
	iArr[5] = 9;
	cArr[1] = palette[1];

	iArr[6] = 2;
	iArr[7] = 8;
	iArr[8] = 4;
	cArr[2] = palette[1];

	iArr[9] = 2;
	iArr[10] = 9;
	iArr[11] = 5;
	cArr[3] = palette[1];

	iArr[12] = 1;
	iArr[13] = 3;
	iArr[14] = 8;
	cArr[4] = palette[1];

	iArr[15] = 1;
	iArr[16] = 3;
	iArr[17] = 9;
	cArr[5] = palette[1];

	iArr[18] = 3;
	iArr[19] = 8;
	iArr[20] = 6;
	cArr[6] = palette[1];

	iArr[21] = 3;
	iArr[22] = 9;
	iArr[23] = 7;
	cArr[7] = palette[1];
	
	iArr[24] = 4;
	iArr[25] = 8;
	iArr[26] = 6;
	cArr[8] = palette[0];

	iArr[27] = 5;
	iArr[28] = 9;
	iArr[29] = 7;
	cArr[9] = palette[0];

	//Внутренняя часть
	iArr[30] = 14;
	iArr[31] = 10;
	iArr[32] = 11;
	cArr[10] = palette[1];

	iArr[33] = 14;
	iArr[34] = 11;
	iArr[35] = 12;
	cArr[11] = palette[0];
	
	iArr[36] = 14;
	iArr[37] = 12;
	iArr[38] = 13;
	cArr[12] = palette[0];

	iArr[39] = 14;
	iArr[40] = 13;
	iArr[41] = 10;
	cArr[13] = palette[0];


	//Старый вариант
	/*vArr[0] = inV;
	vArr[1] = inCenter - sideVec;
	vArr[2] = inCenter->subtract(0, 0, thickness / 2);
	vArr[3] = inCenter + sideVec;
	vArr[4] = inCenter->add(0, 0, thickness / 2);
	vArr[5] = exCenter - sideVec;
	vArr[6] = exCenter->subtract(0, 0, thickness / 2);
	vArr[7] = exCenter + sideVec;
	vArr[8] = exCenter->add(0, 0, thickness / 2);
	vArr[9] = exV;

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
	iArr[12] = 10;
	iArr[13] = 6;
	iArr[14] = 7;
	iArr[15] = 10;
	iArr[16] = 7;
	iArr[17] = 8;
	iArr[18] = 10;
	iArr[19] = 8;
	iArr[20] = 9;
	iArr[21] = 10;
	iArr[22] = 9;
	iArr[23] = 6;*/

	return gcnew SceneObject(vArr, iArr, cArr);
}
