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
	this->normals = gcnew array<Vector3D ^>(N);
	this->colors = gcnew array<Color>(N);
}

SceneObject::SceneObject(array<Vector3D^>^ vertices, array<int>^ indices, array<Vector3D^>^ normals, array<Color>^ colors, String ^ name)
{
	this->offset = gcnew Vector3D(0, 0, 0);
	this->scaling = gcnew Vector3D(1, 1, 1);
	this->rotation = gcnew Vector3D(0, 0, 0);

	this->vertices = vertices;
	this->indices = indices;
	this->normals = normals;
	this->colors = colors;

	this->name = gcnew String(name);
}

SceneObject::SceneObject(array<Vector3D^>^ vertices, array<int>^ indices, array<Vector3D^>^ normals, array<Color>^ colors) : SceneObject::SceneObject(vertices, indices, normals, colors, "Объект")
{
}

void SceneObject::transform()
{
	double alpha = degToRad(rotation->x);
	double beta = degToRad(rotation->y);
	double gamma = degToRad(rotation->z);

#define sin Math::Sin
#define cos Math::Cos
	for each (Vector3D ^ v in vertices)
	{
		v->mx = offset->x + scaling->x * (cos(gamma) * (v->x * cos(beta) +
				(v->z * cos(alpha) + v->y * sin(alpha)) * sin(beta)) - (cos(alpha) *
				v->y - v->z * sin(alpha)) * sin(gamma));
		v->my = offset->y + scaling->y * (cos(gamma) * (cos(alpha) * v->y - v->z *
				sin(alpha)) + (v->x * cos(beta) + (v->z * cos(alpha) + v->y * sin(alpha)) *
				sin(beta)) * sin(gamma));
		v->mz = offset->z + scaling->z * (cos(beta) * (v->z * cos(alpha) + v->y * sin(alpha)) - v->x * sin(beta));
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

void SceneObject::saveToStream(StreamWriter ^ writer)
{
	writer->WriteLine("# Объект " + name);
	writer->WriteLine(ObjectMarks::OBJECT + name);
	for (int i = 0; i < vertices->Length; ++i)
		writer->WriteLine(ObjectMarks::VERTEX + vertices[i]->x + " " + vertices[i]->y + " " + vertices[i]->z);

	writer->WriteLine();
	for (int i = 0; i < indices->Length; i += 3)
	{
		int ii = i / 3;
		writer->WriteLine(ObjectMarks::FACET + indices[i] + "//" + normals[ii]->x + "/" + colors[ii].R + " " +
			indices[i + 1] + "//" + normals[ii]->y + "/" + colors[ii].G + " " + 
			indices[i + 2] + "//" + normals[ii]->z + "/" + colors[ii].B);
	}

	writer->WriteLine();
	writer->WriteLine("# Смещение");
	writer->WriteLine(ObjectMarks::OFFSET + offset->x + " " + offset->y + " " + offset->z);
	writer->WriteLine("# Поворот");
	writer->WriteLine(ObjectMarks::ROTATION + rotation->x + " " + rotation->y + " " + rotation->z);
	writer->WriteLine("# Масштаб");
	writer->WriteLine(ObjectMarks::SCALING + scaling->x + " " + scaling->y + " " + scaling->z);
}

void SceneObject::loadFromStream(Stream ^ stream)
{
	List<Vector3D ^> ^ vertices = gcnew List<Vector3D ^>(N);
	List<int> ^ indices = gcnew List<int>(3 * N);
	List<Vector3D ^> ^ normals = gcnew List<Vector3D ^>(N);
	List<Color> ^ colors = gcnew List<Color>(N);
	String ^ line;
	Random ^ rnd = gcnew Random();
	StreamReader ^ reader = gcnew StreamReader(stream);

	while ((line = reader->ReadLine()) != nullptr)
	{
		if (line->Length == 0)
			continue;

		if (line->StartsWith(ObjectMarks::OBJECT))
		{
			this->name = line->Substring(ObjectMarks::OBJECT->Length);
		}
		else if (line->StartsWith(ObjectMarks::VERTEX))
		{
			array<String ^> ^ data = line->Split(' ');
			array<double> ^ coords = gcnew array<double>(3);
			for (int i = 0; i < 3; ++i)
				coords[i] = Double::Parse(data[i + 2]->Split('/')[0]->Replace('.', ','));
			vertices->Add(gcnew Vector3D(coords[0], coords[1], coords[2]));
		}
		else if (line->StartsWith(ObjectMarks::FACET))
		{
			static int nt = 0;
			++nt;
			array<String ^> ^ data = line->Split(' ');
			array<double> ^ normalValues = gcnew array<double>(3);
			array<int> ^ colorValues = gcnew array<int>(3);
			for (int i = 0; i < 3; ++i)
			{
				array<String ^> ^ splitted = data[i + 1]->Split('/');
				indices->Add(int::Parse(splitted[0]));
				normalValues[i] = splitted->Length >= 3 ? double::Parse(splitted[2]) : 0;
				colorValues[i] = splitted->Length >= 4 ? int::Parse(splitted[3]) : rnd->Next(256);
			}
			colors->Add(Color::FromArgb(colorValues[0], colorValues[1], colorValues[2]));
			Vector3D ^ normal = (gcnew Vector3D(normalValues[0], normalValues[1], normalValues[2]))->normalized();
			if (normal->getMagnitude() == 0)
				normal->z = 1;
			normals->Add(normal);
		}
		else if (line->StartsWith(ObjectMarks::OFFSET))
		{
			array<String ^> ^ data = line->Split(' ');
			offset = gcnew Vector3D(double::Parse(data[1]), double::Parse(data[2]), double::Parse(data[3]));
		}
		else if (line->StartsWith(ObjectMarks::ROTATION))
		{
			array<String ^> ^ data = line->Split(' ');
			rotation = gcnew Vector3D(double::Parse(data[1]), double::Parse(data[2]), double::Parse(data[3]));
		}
		else if (line->StartsWith(ObjectMarks::SCALING))
		{
			array<String ^> ^ data = line->Split(' ');
			scaling = gcnew Vector3D(double::Parse(data[1]), double::Parse(data[2]), double::Parse(data[3]));
		}
	}
	this->vertices = vertices->ToArray();
	this->indices = indices->ToArray();
	this->normals = normals->ToArray();
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
	const double primarySpikeCorrection = primarySpikeLength * (1 - Math::Cos(degToRad(primarySpikeAngle / 2)));
	const double secondarySpikeCorrection = secondarySpikeLength * (1 - Math::Cos(degToRad(secondarySpikeAngle / 2)));
	const double primaryExSpikeDist = bevelBladeRadius - primarySpikeCorrection;
	const double secondaryExSpikeDist = bevelBladeRadius - secondarySpikeCorrection;
	const double primarySpikeLengthCorrected = primarySpikeLength + primarySpikeCorrection;
	const double secondarySpikeLengthCorrected = secondarySpikeLength + secondarySpikeCorrection;
	const double primarySpikeBevelStartPoint = primarySpikeLength * 0.5;
	const double secondarySpikeBevelStartPoint = secondarySpikeLength * 0.5;
	const double inPrimarySpikeLength = bevelBladeRadius * 0.4;
	const double inSecondarySpikeLength = bevelBladeRadius * 0.15;
	array<SceneObject ^> ^ spikes = gcnew array<SceneObject ^>(spikesCount);
	double alphaDeg = -90;
	const double dAlphaDeg = 360.0 / spikesCount;
	const int quarter = spikesCount / 4;
	for (int i = 0; i < spikesCount; ++i)
	{
		if (i % quarter == 0)
			spikes[i] = buildSpike(inBladeRadius, primaryExSpikeDist, alphaDeg, primarySpikeAngle, bladeThickness, inPrimarySpikeLength, primarySpikeBevelStartPoint, primarySpikeLengthCorrected, gcnew array<Color>(2) { palette[1], i == 0 ? palette[1] : palette[2] });
		else
			spikes[i] = buildSpike(inBladeRadius, secondaryExSpikeDist, alphaDeg, secondarySpikeAngle, bladeThickness, inSecondarySpikeLength, secondarySpikeBevelStartPoint, secondarySpikeLengthCorrected, gcnew array<Color>(2) { palette[1], palette[2] });
		alphaDeg += dAlphaDeg;
	}
	
	SceneObject ^ result = unite(spikes);
	result->name = "Шипы";
	result = unite(gcnew array<SceneObject ^>(3) {bladeRing, cross, result});
	result->name = "Лезвие целиком";
	result->moveOriginal(0, bevelBladeRadius, 0);

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
	unitedRings->name = "Кольца для рукояти";
	unitedRings->moveOriginal(0, -handleLength, 0);
	
	result = unite(gcnew array<SceneObject ^>(3) { result, handle, unitedRings });
	result->name = "Лезвиепалка";

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

	List<Vector3D ^> ^ vTotal = gcnew List<Vector3D ^>(totalVCount);
	List<int> ^ iTotal = gcnew List<int>(totalICount);
	List<Vector3D ^> ^ nTotal = gcnew List<Vector3D ^>(totalICount / 3);
	List<Color> ^ cTotal = gcnew List<Color>(totalICount / 3);
	for (int i = 0; i < components->Length; ++i)
	{
		int vOffset = vTotal->Count;
		vTotal->AddRange(components[i]->vertices);
		int iOffset = iTotal->Count;
		iTotal->AddRange(components[i]->indices);
		for (int j = iOffset; j < iTotal->Count; ++j)
			iTotal[j] += vOffset;
		nTotal->AddRange(components[i]->normals);
		cTotal->AddRange(components[i]->colors);
	}

	return gcnew SceneObject(vTotal->ToArray(), iTotal->ToArray(), nTotal->ToArray(), cTotal->ToArray());
}

//vertices: nEdges * 2 + 2
//indices: nEdges * 12
SceneObject ^ SceneObject::buildHandle(double radius, double height, int nEdges, array<Color> ^ palette)
{
	const int INDICES_MUL = 12;
	Vector3D ^ bottomCenter = gcnew Vector3D(0, -height / 2, 0);
	Vector3D ^ topCenter = gcnew Vector3D(0, height / 2, 0);
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(nEdges * 2 + 2);
	array<int> ^ iArr = gcnew array<int>(nEdges * INDICES_MUL);
	array<Vector3D ^> ^ nArr = gcnew array<Vector3D ^>(nEdges * INDICES_MUL / 3);
	array<Color> ^ cArr = gcnew array<Color>(nEdges * INDICES_MUL / 3);

	vArr[0] = bottomCenter->clone();
	vArr[nEdges + 1] = topCenter->clone();

	const int FACETS_PER_ITERATION = INDICES_MUL / 3;
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

	for (int i = 0; i < nEdges - 1; ++i)
	{
		int mi = i * FACETS_PER_ITERATION;
		nArr[mi] = (vArr[i + 2] - vArr[0])->normalized()->vectorProduct((vArr[i + 1] - vArr[0])->normalized())->normalized();
		nArr[mi + 1] = (vArr[nEdges + i + 2] - vArr[nEdges + 1])->normalized()->vectorProduct((vArr[nEdges + i + 3] - vArr[nEdges + 1])->normalized())->normalized();
		nArr[mi + 2] = (vArr[nEdges + i + 3] - vArr[i + 2])->normalized()->vectorProduct((vArr[i + 1] - vArr[i + 2])->normalized())->normalized();
		nArr[mi + 3] = nArr[mi + 2]->clone();
	}
	int closing2 = (nEdges - 1) * FACETS_PER_ITERATION;
	nArr[closing2] = (vArr[1] - vArr[0])->normalized()->vectorProduct((vArr[nEdges] - vArr[0])->normalized())->normalized();
	nArr[closing2 + 1] = (vArr[nEdges * 2 - 1] - vArr[nEdges + 1])->normalized()->vectorProduct((vArr[nEdges + 2] - vArr[nEdges + 1])->normalized())->normalized();
	nArr[closing2 + 2] = (vArr[nEdges + 2] - vArr[1])->normalized()->vectorProduct((vArr[nEdges] - vArr[1])->normalized())->normalized();
	nArr[closing2 + 3] = nArr[closing2 + 2]->clone();

	return gcnew SceneObject(vArr, iArr, nArr, cArr, "Рукоять");
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
	array<Vector3D ^> ^ nArr = gcnew array<Vector3D ^>(nEdges * INDICES_MUL / 3);
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

	for (int i = 0; i < nEdges - 1; ++i)
	{
		int mi = i * FACETS_PER_ITERATION;
		nArr[mi] = (vArr[nEdges + i] - vArr[nEdges + i + 1])->normalized()->vectorProduct((vArr[i] - vArr[nEdges + i])->normalized())->normalized();
		nArr[mi + 1] = nArr[mi]->clone();
		nArr[mi + 2] = Vector3D::BACK->clone();
		nArr[mi + 3] = nArr[mi + 2]->clone();
		nArr[mi + 4] = (vArr[nEdges * 3 + i] - vArr[nEdges * 2 + i])->normalized()->vectorProduct((vArr[nEdges * 2 + i] - vArr[nEdges * 2 + i + 1])->normalized())->normalized();
		nArr[mi + 5] = nArr[mi + 4]->clone();
		nArr[mi + 6] = Vector3D::FORTH->clone();
		nArr[mi + 7] = nArr[mi + 6]->clone();
		nArr[mi + 8] = (vArr[i] - vArr[i + 1])->normalized()->vectorProduct((vArr[nEdges * 4 + i] - vArr[i])->normalized())->normalized();
		nArr[mi + 9] = nArr[mi + 8]->clone();
	}
	int closing2 = (nEdges - 1) * FACETS_PER_ITERATION;
	nArr[closing2] = (vArr[nEdges * 2 - 1] - vArr[nEdges])->normalized()->vectorProduct((vArr[nEdges - 1] - vArr[nEdges * 2 - 1])->normalized())->normalized();
	nArr[closing2 + 1] = nArr[closing2]->clone();
	nArr[closing2 + 2] = Vector3D::BACK->clone();
	nArr[closing2 + 3] = nArr[closing2 + 2]->clone();
	nArr[closing2 + 4] = (vArr[nEdges * 4 - 1] - vArr[nEdges * 3 - 1])->normalized()->vectorProduct((vArr[nEdges * 2] - vArr[nEdges * 3 - 1])->normalized())->normalized();
	nArr[closing2 + 5] = nArr[closing2 + 4]->clone();
	nArr[closing2 + 6] = Vector3D::FORTH->clone();
	nArr[closing2 + 7] = nArr[closing2 + 6]->clone();
	nArr[closing2 + 8] = (vArr[nEdges - 1] - vArr[0])->normalized()->vectorProduct((vArr[nEdges * 5 - 1] - vArr[nEdges - 1])->normalized())->normalized();
	nArr[closing2 + 9] = nArr[closing2 + 8]->clone();

	return gcnew SceneObject(vArr, iArr, nArr, cArr, "Кольцевое лезвие");
}

//vertices: 24
//indices: 108
SceneObject ^ SceneObject::buildCross(double pLength, double pWidth, double pThickness, array<Color> ^ palette)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(24);
	const int N_FACETS = 36;
	array<int> ^ iArr = gcnew array<int>(N_FACETS * 3);
	array<Vector3D ^> ^ nArr = gcnew array<Vector3D ^>(N_FACETS);
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

	array<Vector3D ^> ^ dirs1 = gcnew array<Vector3D ^>(4) {Vector3D::BACK, Vector3D::DOWN, Vector3D::FORTH, Vector3D::UP};
	array<Vector3D ^> ^ dirs2 = gcnew array<Vector3D ^>(4) {Vector3D::BACK, Vector3D::LEFT, Vector3D::FORTH, Vector3D::RIGHT};
	for (int i = 0; i < 4; ++i)
	{
		nArr[i * 2] = dirs1[i]->clone();
		nArr[i * 2 + 1] = dirs1[i]->clone();
		nArr[i * 2 + 16] = dirs1[i]->clone();
		nArr[i * 2 + 17] = dirs1[i]->clone();
	}
	for (int i = 0; i < 4; ++i)
	{
		nArr[i * 2 + 8] = dirs2[i]->clone();
		nArr[i * 2 + 9] = dirs2[i]->clone();
		nArr[i * 2 + 24] = dirs2[i]->clone();
		nArr[i * 2 + 25] = dirs2[i]->clone();
	}
	nArr[32] = Vector3D::BACK->clone();
	nArr[33] = Vector3D::BACK->clone();
	nArr[34] = Vector3D::FORTH->clone();
	nArr[35] = Vector3D::FORTH->clone();
	return gcnew SceneObject(vArr, iArr, nArr, cArr, "Крест");
}

//vertices: 14
//indices: 42
SceneObject ^ SceneObject::buildSpike(double inDistance, double exDistance, double alphaDeg, double betaDeg, double thickness, double inLength, double bevelStartPoint, double exLength, array<Color> ^ palette)
{
	array<Vector3D ^> ^ vArr = gcnew array<Vector3D ^>(14);
	const double N_FACETS = 14;
	array<int> ^ iArr = gcnew array<int>(N_FACETS * 3);
	array<Vector3D ^> ^ nArr = gcnew array<Vector3D ^>(N_FACETS);
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
	nArr[0] = (vArr[7] - vArr[3])->normalized()->vectorProduct((vArr[1] - vArr[3])->normalized())->normalized();

	iArr[3] = 1;
	iArr[4] = 2;
	iArr[5] = 9;
	cArr[1] = palette[1];
	nArr[1] = (vArr[8] - vArr[4])->normalized()->vectorProduct((vArr[4] - vArr[1])->normalized())->normalized();

	iArr[6] = 2;
	iArr[7] = 8;
	iArr[8] = 4;
	cArr[2] = palette[1];
	nArr[2] = nArr[0]->clone();

	iArr[9] = 2;
	iArr[10] = 9;
	iArr[11] = 5;
	cArr[3] = palette[1];
	nArr[3] = nArr[1]->clone();

	iArr[12] = 1;
	iArr[13] = 3;
	iArr[14] = 8;
	cArr[4] = palette[1];
	nArr[4] = (vArr[7] - vArr[2])->normalized()->vectorProduct((vArr[5] - vArr[2])->normalized())->normalized();

	iArr[15] = 1;
	iArr[16] = 3;
	iArr[17] = 9;
	cArr[5] = palette[1];
	nArr[5] = (vArr[8] - vArr[6])->normalized()->vectorProduct((vArr[2] - vArr[6])->normalized())->normalized();

	iArr[18] = 3;
	iArr[19] = 8;
	iArr[20] = 6;
	cArr[6] = palette[1];
	nArr[6] = nArr[4]->clone();

	iArr[21] = 3;
	iArr[22] = 9;
	iArr[23] = 7;
	cArr[7] = palette[1];
	nArr[7] = nArr[5]->clone();
	
	iArr[24] = 4;
	iArr[25] = 8;
	iArr[26] = 6;
	cArr[8] = palette[0];
	nArr[8] = Vector3D::BACK->clone();

	iArr[27] = 5;
	iArr[28] = 9;
	iArr[29] = 7;
	cArr[9] = palette[0];
	nArr[9] = Vector3D::FORTH->clone();

	//Внутренняя часть
	iArr[30] = 14;
	iArr[31] = 10;
	iArr[32] = 11;
	cArr[10] = palette[0];
	nArr[10] = (vArr[10] - vArr[9])->normalized()->vectorProduct((vArr[13] - vArr[9])->normalized())->normalized();

	iArr[33] = 14;
	iArr[34] = 11;
	iArr[35] = 12;
	cArr[11] = palette[0];
	nArr[11] = (vArr[11] - vArr[10])->normalized()->vectorProduct((vArr[13] - vArr[10])->normalized())->normalized();
	
	iArr[36] = 14;
	iArr[37] = 12;
	iArr[38] = 13;
	cArr[12] = palette[0];
	nArr[12] = (vArr[12] - vArr[11])->normalized()->vectorProduct((vArr[13] - vArr[11])->normalized())->normalized();

	iArr[39] = 14;
	iArr[40] = 13;
	iArr[41] = 10;
	cArr[13] = palette[0];
	nArr[13] = (vArr[9] - vArr[12])->normalized()->vectorProduct((vArr[13] - vArr[12])->normalized())->normalized();

	return gcnew SceneObject(vArr, iArr, nArr, cArr, "Шип");
}
