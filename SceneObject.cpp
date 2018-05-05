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
	//this->vertices = gcnew array<Vector3D ^>(N);
	List<Vector3D ^> ^ vertices = gcnew List<Vector3D ^>(N);
	List<int> ^ indices = gcnew List<int>(3 * N);
	List<Color> ^ colors = gcnew List<Color>(N);
	StreamReader ^ reader = gcnew StreamReader(stream);
	String ^ line, ^ line2;
	//array<String ^> ^ codes = gcnew array<String^>(2){"v ", "f "}; //Пробелы для исключения "vn" итп, когда ищется "v"
	while ((line = reader->ReadLine()) != nullptr && (line->Length < 2 || !line->Substring(0, 2)->Equals("v "))) {}
	while ((line2 = reader->ReadLine()) != nullptr && line->Length >= 2 && line->Substring(0, 2)->Equals("v "))
	{
		array<String ^> ^ data = line->Split(' ');
		array<double> ^ coords = gcnew array<double>(3);
		for (int i = 0; i < 3; ++i)
			coords[i] = Double::Parse(data[i + 1]->Split('/')[0]->Replace('.', ','));
		vertices->Add(gcnew Vector3D(coords[0], coords[1], coords[2]));
		line = line2;
	}

	Random ^ rnd = gcnew Random();
	while ((line = reader->ReadLine()) != nullptr && (line->Length < 2 || !line->Substring(0, 2)->Equals("f "))) {}
	while ((line2 = reader->ReadLine()) != nullptr && line->Length >= 2 && line->Substring(0, 2)->Equals("f "))
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
		line = line2;
	}
	this->vertices = vertices->ToArray();
	this->indices = indices->ToArray();
	this->colors = colors->ToArray();
}
