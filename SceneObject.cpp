#include "SceneObject.h"
#include "Vector3D.h"
#include "Utils.h"

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

void SceneObject::transform()
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

	array<Vector3D ^> ^ vertices;
	array<int> ^ indices;
	//generateVertCylinder(gcnew Vector3D(0, -150, 0), 50, 300, 10, &vertices, &indices);
	generateBladeRing(gcnew Vector3D(0, 0, -10), 40, 75, 20, 10, &vertices, &indices);

	int fcount = indices->Length / 3;
	array<Color> ^ colors = gcnew array<Color>(fcount);
	for (int i = 0; i < fcount; ++i)
		colors[i] = Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256));

	return gcnew SceneObject(vertices, indices, colors);
}

//vertices: nEdges * 2 + 2
//indices: nEdges * 12
void SceneObject::generateHandle(Vector3D ^ bottomCenter, double radius, double height, int nEdges, array<Vector3D ^> ^* vertices, array<int> ^* indices)
{
	const int INDICES_MUL = 12;
	Vector3D ^ topCenter = bottomCenter->add(0, height, 0);
	*vertices = (gcnew array<Vector3D^>(nEdges * 2 + 2));
	*indices = gcnew array<int>(nEdges * INDICES_MUL);

	Vector3D bc = *bottomCenter;
	(*vertices)[0] = %bc;
	Vector3D tc = *topCenter;
	(*vertices)[nEdges + 1] = %tc;

	double dAlpha = degToRad(360.0 / nEdges);
	double alpha = 0;
	for (int i = 1; i <= nEdges; ++i)
	{
		double x = bottomCenter->x + radius * Math::Cos(alpha);
		double z = bottomCenter->z + radius * Math::Sin(alpha);
		alpha += dAlpha;

		(*vertices)[i] = gcnew Vector3D(x, bottomCenter->y, z);
		(*vertices)[nEdges + 1 + i] = gcnew Vector3D(x, topCenter->y, z);

		int mi = (i - 1) * INDICES_MUL;
		(*indices)[mi] = i + 1;
		(*indices)[mi + 1] = i + 2;
		(*indices)[mi + 2] = 1;
		(*indices)[mi + 3] = nEdges + 2 + i;
		(*indices)[mi + 4] = nEdges + 3 + i;
		(*indices)[mi + 5] = nEdges + 1 + 1;
		(*indices)[mi + 6] = (*indices)[mi];
		(*indices)[mi + 7] = (*indices)[mi + 1];
		(*indices)[mi + 8] = (*indices)[mi + 3];
		(*indices)[mi + 9] = (*indices)[mi + 3];
		(*indices)[mi + 10] = (*indices)[mi + 4];
		(*indices)[mi + 11] = (*indices)[mi + 1];
	}

	int closing = (nEdges - 1) * INDICES_MUL;
	(*indices)[closing] = nEdges + 1;
	(*indices)[closing + 1] = 2;
	(*indices)[closing + 2] = 1;
	(*indices)[closing + 3] = nEdges * 2 + 2;
	(*indices)[closing + 4] = nEdges + 3;
	(*indices)[closing + 5] = nEdges + 2;
	(*indices)[closing + 6] = (*indices)[closing];
	(*indices)[closing + 7] = (*indices)[closing + 1];
	(*indices)[closing + 8] = (*indices)[closing + 3];
	(*indices)[closing + 9] = (*indices)[closing + 3];
	(*indices)[closing + 10] = (*indices)[closing + 4];
	(*indices)[closing + 11] = (*indices)[closing + 1];
}

//vertices: nEdges * 5
//indices: nEdges * 30
void SceneObject::generateBladeRing(Vector3D ^ nearCenter, double inRadius, double exRadius, double length, int nEdges, array<Vector3D^>^* vertices, array<int>^* indices)
{
	const int INDICES_MUL = 30;
	Vector3D ^ farCenter = nearCenter->add(0, 0, length);
	double bevelDist = inRadius + (exRadius - inRadius) * 0.4;
	*vertices = (gcnew array<Vector3D^>(nEdges * 5));
	*indices = gcnew array<int>(nEdges * INDICES_MUL);

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
		(*vertices)[ex ] = gcnew Vector3D(exx, exy, exz);
		(*vertices)[nBv] = gcnew Vector3D(bvx, bvy, nearCenter->z);
		(*vertices)[nIn] = gcnew Vector3D(inx, iny, nearCenter->z);
		(*vertices)[fIn] = gcnew Vector3D(inx, iny, farCenter->z);
		(*vertices)[fBv] = gcnew Vector3D(bvx, bvy, farCenter->z);

		int mi = i * INDICES_MUL;
		(*indices)[mi] = nBv + 1;
		(*indices)[mi + 1] = nBv + 2;
		(*indices)[mi + 2] = ex + 1;
		(*indices)[mi + 3] = nBv + 2;
		(*indices)[mi + 4] = ex + 1;
		(*indices)[mi + 5] = ex + 2;

		(*indices)[mi + 6] = nIn + 1;
		(*indices)[mi + 7] = nIn + 2;
		(*indices)[mi + 8] = nBv + 1;
		(*indices)[mi + 9] = nIn + 2;
		(*indices)[mi + 10] = nBv + 1;
		(*indices)[mi + 11] = nBv + 2;

		(*indices)[mi + 12] = nIn + 1;
		(*indices)[mi + 13] = nIn + 2;
		(*indices)[mi + 14] = fIn + 1;
		(*indices)[mi + 15] = nIn + 2;
		(*indices)[mi + 16] = fIn + 1;
		(*indices)[mi + 17] = fIn + 2;

		(*indices)[mi + 18] = fIn + 1;
		(*indices)[mi + 19] = fIn + 2;
		(*indices)[mi + 20] = fBv + 1;
		(*indices)[mi + 21] = fIn + 2;
		(*indices)[mi + 22] = fBv + 1;
		(*indices)[mi + 23] = fBv + 2;

		(*indices)[mi + 24] = ex + 1;
		(*indices)[mi + 25] = ex + 2;
		(*indices)[mi + 26] = fBv + 1;
		(*indices)[mi + 27] = ex + 2;
		(*indices)[mi + 28] = fBv + 1;
		(*indices)[mi + 29] = fBv + 2;
	}

	int closing = (nEdges - 1) * INDICES_MUL;
	(*indices)[closing] = nEdges * 2;
	(*indices)[closing + 1] = nEdges + 1;
	(*indices)[closing + 2] = nEdges;
	(*indices)[closing + 3] = nEdges + 1;
	(*indices)[closing + 4] = nEdges;
	(*indices)[closing + 5] = 1;

	(*indices)[closing + 6] = nEdges * 3;
	(*indices)[closing + 7] = nEdges * 2 + 1;
	(*indices)[closing + 8] = nEdges * 2;
	(*indices)[closing + 9] = nEdges * 2 + 1;
	(*indices)[closing + 10] = nEdges * 2;
	(*indices)[closing + 11] = nEdges + 1;

	(*indices)[closing + 12] = nEdges * 3;
	(*indices)[closing + 13] = nEdges * 2 + 1;
	(*indices)[closing + 14] = nEdges * 4;
	(*indices)[closing + 15] = nEdges * 2 + 1;
	(*indices)[closing + 16] = nEdges * 4;
	(*indices)[closing + 17] = nEdges * 3 + 1;

	(*indices)[closing + 18] = nEdges * 4;
	(*indices)[closing + 19] = nEdges * 3 + 1;
	(*indices)[closing + 20] = nEdges * 5;
	(*indices)[closing + 21] = nEdges * 3 + 1;
	(*indices)[closing + 22] = nEdges * 5;
	(*indices)[closing + 23] = nEdges * 4 + 1;

	(*indices)[closing + 24] = nEdges;
	(*indices)[closing + 25] = 1;
	(*indices)[closing + 26] = nEdges * 5;
	(*indices)[closing + 27] = 1;
	(*indices)[closing + 28] = nEdges * 5;
	(*indices)[closing + 29] = nEdges * 4 + 1;
}
