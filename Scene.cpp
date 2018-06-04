#include "Scene.h"
#include "Utils.h"
#include "Matrix.h"

using namespace Bladestick::Drawing;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;

Scene::Scene(int width, int height, Color bgColor, Color edgeColor)
{
	setSize(width, height);
	this->bgColor = bgColor;
	this->edgeColor = edgeColor;
	this->camera = gcnew Camera(gcnew Vector3D(0, 0, 1000), gcnew Vector3D(0, 0, 0), 1, 5000, 40, false);
	this->objTotalCount = 0;
	this->objects = gcnew BindingList<SceneObject ^>();
}

Scene::Scene(int width, int height) : Scene::Scene(width, height, Color::Black, Color::White) {}

Scene::Scene() : Scene::Scene(600, 400) {}

void Scene::setSize(int width, int height)
{
	this->width = width < 1 ? 1 : width;
	this->height = height < 1 ? 1 : height;
	this->bitmap = gcnew Bitmap(this->width, this->height);
	this->zbuffer = gcnew array<double>(this->width * this->height);
}

int Scene::getWidth()
{
	return width;
}

int Scene::getHeight()
{
	return height;
}

void Scene::clear()
{
	int index = 0;
	double ninf = Double::NegativeInfinity;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			zbuffer[index++] = ninf;
	Graphics ^ g = Graphics::FromImage(bitmap);
	g->Clear(bgColor);
	delete g;
}

bool Scene::isPointInRect(Vector3D ^ p)
{
	return p->mx >= 0 && p->mx <= width && p->my >= 0 && p->my <= height;
}

Vector3D ^ Scene::getPointAtX(Vector3D ^ A, Vector3D ^ B, double x)
{
	double xRatio = (B->x - A->x) / (x - A->x);
	double y = A->y + (B->y - A->y) / xRatio;
	double z = A->z + (B->z - A->z) / xRatio;
	return gcnew Vector3D(x, y, z);
}

Vector3D ^ Scene::getPointAtY(Vector3D ^ A, Vector3D ^ B, double y)
{
	double yRatio = (B->y - A->y) / (y - A->y);
	double x = A->x + (B->x - A->x) / yRatio;
	double z = A->z + (B->z - A->z) / yRatio;
	return gcnew Vector3D(x, y, z);
}

array<Vector3D ^> ^ Scene::clipLineXY(Vector3D ^ p1, Vector3D ^ p2)
{
	//Версия с пруфом
	/*if (p1->mx < 5 && p2->mx < 5 ||
		p1->mx > width - 5 && p2->mx > width - 5 ||
		p1->my < 5 && p2->my < 5 ||
		p1->my > height - 5 && p2->my > height - 5)
		return gcnew array<Vector3D ^>(2) { nullptr, nullptr };*/

	if (p1->mx < 0 && p2->mx < 0 ||
		p1->mx > width && p2->mx > width ||
		p1->my < 0 && p2->my < 0 ||
		p1->my > height && p2->my > height)
		return gcnew array<Vector3D ^>(2) { nullptr, nullptr };

	p1->swapModifiedAndMain();
	p2->swapModifiedAndMain();
	array<Vector3D ^> ^ input = gcnew array<Vector3D ^>(2) {p1, p2};
	array<Vector3D ^> ^ copies = gcnew array<Vector3D ^>(2) {p1->clone(), p2->clone()};

	for (int i = 0; i < input->Length; ++i)
	{
		//Версия с пруфом
		/*if (input[i]->x < 5)
			input[i] = getPointAtX(p1, p2, 5);
		else if (input[i]->x > width - 5)
			input[i] = getPointAtX(p1, p2, width - 5);

		if (input[i]->y < 5)
			input[i] = getPointAtY(p1, p2, 5);
		else if (input[i]->y > height - 5)
			input[i] = getPointAtY(p1, p2, height - 5);*/

		if (input[i]->x < 0)
			input[i] = getPointAtX(p1, p2, 0);
		else if (input[i]->x > width)
			input[i] = getPointAtX(p1, p2, width);

		if (input[i]->y < 0)
			input[i] = getPointAtY(p1, p2, 0);
		else if (input[i]->y > height)
			input[i] = getPointAtY(p1, p2, height);

		input[i]->mx = copies[i]->x;
		input[i]->my = copies[i]->y;
		input[i]->mz = copies[i]->z;
		input[i]->mw = copies[i]->w;
	}

	p1 = input[0];
	p2 = input[1];
	p1->swapModifiedAndMain();
	p2->swapModifiedAndMain();

	return gcnew array<Vector3D ^>(2) {p1, p2};
}

void Scene::setPixel(int x, int y, double z, Color color)
{
	if (x < 1 || x >= width || y < 1 || y >= height) return;

	int index = x * height + y;
	if (z >= zbuffer[index])
	{
		zbuffer[index] = z;
		bitmap->SetPixel(x, y, color);
	}
}

void Scene::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, Color color)
{
	bool steep = false;
	if (Math::Abs(x0 - x1) < Math::Abs(y0 - y1))
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
		steep = true;
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int y = y0;
	double z = z0;
	double zStep = (z1 - z0) / dx;
	int derror2 = Math::Abs(dy) * 2;
	int error2 = 0;
	int diry = y1 > y0 ? 1 : -1;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			setPixel(y, x, z, color);
		else
			setPixel(x, y, z, color);
		error2 += derror2;
		z += zStep;

		if (error2 > dx)
		{
			y += diry;
			error2 -= dx * 2;
		}
	}
}

void Scene::drawLine(Vector3D ^ p1, Vector3D ^ p2, Color color)
{
	drawLine(p1->mx, p1->my, p1->mz, p2->mx, p2->my, p2->mz, color);
}

void Scene::drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, Color color, char drawFlags)
{
	if (cmpDoubles(p1->my, p2->my) == 0 && cmpDoubles(p2->my, p3->my) == 0) return;

	if (-p1->mz > camera->far || -p1->mz < camera->near ||
		-p2->mz > camera->far || -p2->mz < camera->near ||
		-p3->mz > camera->far || -p3->mz < camera->near) return;

	if (p1->my > p2->my) swap(&p1, &p2);
	if (p1->my > p3->my) swap(&p1, &p3);
	if (p2->my > p3->my) swap(&p2, &p3);

	if (cmpDoubles(p1->my, p2->my) != 0 && cmpDoubles(p2->my, p3->my) != 0)
	{
		double yRatio = (p3->my - p1->my) / (p2->my - p1->my);
		Vector3D ^ breakPoint = gcnew Vector3D();
		breakPoint->mx = p1->mx + (p3->mx - p1->mx) / yRatio;
		breakPoint->my = p1->my + (p3->my - p1->my) / yRatio;
		breakPoint->mz = p1->mz + (p3->mz - p1->mz) / yRatio;
		drawTriangle(p1, p2, breakPoint, color, drawFlags);
		drawTriangle(breakPoint, p2, p3, color, drawFlags);
	}
	else
	{
		//Заливка
		if ((drawFlags & DrawFlags::DRAW_FILL) > 0)
		{
			int height = p3->my - p1->my;
			Vector3D ^leftSmaller, ^leftBigger, ^rightSmaller, ^rightBigger;
#pragma region Узнаю кто левый-правый-верхний-нижний
			if (cmpDoubles(p1->my, p2->my) == 0)
			{
				leftBigger = rightBigger = p3;
				if (p1->mx < p2->mx)
				{
					leftSmaller = p1;
					rightSmaller = p2;
				}
				else
				{
					leftSmaller = p2;
					rightSmaller = p1;
				}
			}
			else
			{
				leftSmaller = rightSmaller = p1;
				if (p2->mx < p3->mx)
				{
					leftBigger = p2;
					rightBigger = p3;
				}
				else
				{
					leftBigger = p3;
					rightBigger = p2;
				}
			}
#pragma endregion

			for (int i = 0; i <= height; i++)
			{
				double k = (double)i / height;
				int leftX = leftSmaller->mx + (leftBigger->mx - leftSmaller->mx) * k;
				int rightX = rightSmaller->mx + (rightBigger->mx - rightSmaller->mx) * k;
				int leftZ = leftSmaller->mz + (leftBigger->mz - leftSmaller->mz) * k;
				int rightZ = rightSmaller->mz + (rightBigger->mz - rightSmaller->mz) * k;
				int length = rightX - leftX;
				for (int j = 0; j <= length; j++)
				{
					double k2 = (double)j / length;
					double mz = leftZ + (rightZ - leftZ) * k2;
					setPixel(leftX + j, p1->my + i, mz, color);
				}
			}
		}

		//Контур
		if ((drawFlags & DrawFlags::DRAW_EDGES) > 0)
		{
			drawLine(p1, p2, edgeColor);
			drawLine(p2, p3, edgeColor);
			drawLine(p3, p1, edgeColor);
		}
	}
}

void Scene::drawToBuffer(SceneObject ^ obj, char drawFlags)
{
	if ((drawFlags & DRAW_FILL | drawFlags & DRAW_EDGES) == 0) return;

	int vCount = obj->vertices->Length;
	array<Vector3D ^> ^ vertices = gcnew array<Vector3D ^>(vCount);
	for (int i = 0; i < vCount; ++i)
		vertices[i] = obj->vertices[i]->clone();
	for each (Vector3D ^ v in vertices)
	{
		//Преобразование вида
		double xOffset = v->mx - camera->position->x;
		double yOffset = v->my - camera->position->y;
		double zOffset = v->mz - camera->position->z;
		v->mx = camera->rightDir->x * xOffset + camera->rightDir->y * yOffset + camera->rightDir->z * zOffset;
		v->my = camera->upDir->x * xOffset + camera->upDir->y * yOffset + camera->upDir->z * zOffset;
		v->mz = camera->backDir->x * xOffset + camera->backDir->y * yOffset + camera->backDir->z * zOffset;

		double aspect = (double)width / height;
		double vfov = camera->fov / aspect;
		double ctg = 1 / Math::Tan(vfov / 2);
		double n = camera->near, f = camera->far;
		if (camera->perspective)
		{		
			double hfov = camera->fov;
			double vfov = hfov / width * height;
			float r = Math::Tan(degToRad(hfov / 2));
			float l = -r;
			float t = Math::Tan(degToRad(vfov / 2));
			float b = -t;
			Vector3D ^ src = v->clone();
			v->mw = src->mz;
			v->mx = -(2 * src->mx * n) / (-l + r) - (src->mz * (l + r)) / (l - r);
			v->my = (2 * src->my * n) / (-b + t) + (src->mz * (b + t)) / (b - t);
			v->mz = -(2 * f * n) / (f - n) + (src->mz * (f + n)) / (f - n);

			if (v->mw != 1)
			{
				v->mx /= v->mw;
				v->my /= v->mw;
				//v->mz /= v->mw;
			}

			v->mx = (v->mx + 1) * this->width / 2;
			v->my = (v->my + 1) * this->height / 2;
			int i = 1;
		}
		else
		{
			//Нужно ли искажение X и Y?
			/*v->mx = -ctg / aspect * v->mx;
			v->my = -ctg * v->my;*/
			v->mz = (2 * f * n / (n - f) + (f + n) / (f - n) * v->mz);
			v->mx += width / 2;
			v->my = height / 2 - v->my;
		}
	}

	Random ^ rnd = gcnew Random();
	for (int i = 0; i < obj->indices->Length; i += 3)
	{
		Vector3D ^ v1 = vertices[obj->indices[i] - 1];
		Vector3D ^ v2 = vertices[obj->indices[i + 1] - 1];
		Vector3D ^ v3 = vertices[obj->indices[i + 2] - 1];

		Color color = (drawFlags & DRAW_FILL) && (drawFlags & USE_RND_COLORS) ? Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256)) : obj->colors[i / 3];
		//Освещение
		if ((drawFlags & DRAW_FILL) && (drawFlags & SIMULATE_LIGHT))
		{
			Vector3D ^ n = obj->normals[i / 3]->clone();
			double alpha = degToRad(obj->rotation->x);
			double beta = degToRad(obj->rotation->y);
			double gamma = degToRad(obj->rotation->z);
			double sinAlpha = Math::Sin(alpha);
			double cosAlpha = Math::Cos(alpha);
			double sinBeta = Math::Sin(beta);
			double cosBeta = Math::Cos(beta);
			double sinGamma = Math::Sin(gamma);
			double cosGamma = Math::Cos(gamma);
			double sinAlphaSqr = sinAlpha * sinAlpha;
			double cosAlphaSqr = cosAlpha * cosAlpha;
			double sinBetaSqr = sinBeta * sinBeta;
			double cosBetaSqr = cosBeta * cosBeta;
			double sinGammaSqr = sinGamma * sinGamma;
			double cosGammaSqr = cosGamma * cosGamma;
			n->mx = (n->x * (cosAlphaSqr * cosBeta * cosGamma + cosBeta * cosGamma * sinAlphaSqr)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->y * (cosGamma * sinAlpha * sinBeta - cosAlpha * cosBetaSqr * sinGamma - cosAlpha * sinBetaSqr * sinGamma)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->z * (cosAlpha * cosGamma * sinBeta + cosBetaSqr * sinAlpha * sinGamma + sinAlpha * sinBetaSqr * sinGamma)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr);
			n->my = (n->x * (cosAlphaSqr * cosBeta * sinGamma + cosBeta * sinAlphaSqr * sinGamma)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->z * (-cosBetaSqr * cosGamma * sinAlpha - cosGamma * sinAlpha * sinBetaSqr + cosAlpha * sinBeta * sinGamma)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->y * (cosAlpha * cosBetaSqr * cosGamma + cosAlpha * cosGamma * sinBetaSqr + sinAlpha * sinBeta * sinGamma)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr);
			n->mz = (n->z * (cosAlpha * cosBeta * cosGammaSqr + cosAlpha * cosBeta * sinGammaSqr)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->y * (cosBeta * cosGammaSqr * sinAlpha + cosBeta * sinAlpha * sinGammaSqr)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr) + (n->x * (-cosAlphaSqr * cosGammaSqr * sinBeta - cosGammaSqr * sinAlphaSqr * sinBeta - cosAlphaSqr * sinBeta * sinGammaSqr - sinAlphaSqr * sinBeta * sinGammaSqr)) / (cosAlphaSqr * cosBetaSqr * cosGammaSqr + cosBetaSqr * cosGammaSqr * sinAlphaSqr + cosAlphaSqr * cosGammaSqr * sinBetaSqr + cosGammaSqr * sinAlphaSqr * sinBetaSqr + cosAlphaSqr * cosBetaSqr * sinGammaSqr + cosBetaSqr * sinAlphaSqr * sinGammaSqr + cosAlphaSqr * sinBetaSqr * sinGammaSqr + sinAlphaSqr * sinBetaSqr * sinGammaSqr);

			n->modifiedToMain();
			double intensity = camera->backDir->normalized()->scale(-1, -1, -1)->scalarProduct(n);
			if (intensity > 0)
				color = Color::FromArgb(color.R * intensity, color.G * intensity, color.B * intensity);
			else
				color = Color::Black;
		}

		//Отсечение граней
		array<Vector3D ^> ^ vAfterClip = gcnew array<Vector3D ^>(6);
		array<Vector3D ^> ^ buf;
		buf = clipLineXY(v1->clone(), v2->clone());
		vAfterClip[0] = buf[0];
		vAfterClip[1] = buf[1];
		buf = clipLineXY(v2->clone(), v3->clone());
		vAfterClip[2] = buf[0];
		vAfterClip[3] = buf[1];
		buf = clipLineXY(v3->clone(), v1->clone());
		vAfterClip[4] = buf[0];
		vAfterClip[5] = buf[1];
		List<Vector3D ^> ^ uniques = gcnew List<Vector3D ^>(6);
		for (int i2 = 0; i2 < vAfterClip->Length; ++i2)
		{
			if (vAfterClip[i2] == nullptr)
				continue;

			bool repeat = false;
			for (int j2 = 0; !repeat && j2 < uniques->Count; ++j2)
				repeat = cmpDoubles(vAfterClip[i2]->mx, uniques[j2]->mx) == 0 &&
				cmpDoubles(vAfterClip[i2]->my, uniques[j2]->my) == 0 &&
				cmpDoubles(vAfterClip[i2]->mz, uniques[j2]->mz) == 0;
			if (!repeat)
				uniques->Add(vAfterClip[i2]);
		}

		for (int i = 1; i + 1 < uniques->Count; ++i)
			drawTriangle(uniques[0], uniques[i], uniques[i + 1], color, drawFlags);
	}
}

void Scene::render(Graphics ^ g)
{
	g->DrawImage(bitmap, 0, 0, width, height);
}

void Scene::drawObjectsToBuffer(char drawFlags)
{
	for each (SceneObject ^ so in objects)
		drawToBuffer(so, drawFlags);
}

Color Scene::getBgColor()
{
	return this->bgColor;
}

void Scene::setBgColor(Color color)
{
	this->bgColor = color;
}

void Scene::saveToStream(StreamWriter ^ writer)
{
	writer->WriteLine("### Параметры сцены и камеры");

	writer->WriteLine("# Позиция камеры");
	writer->WriteLine(SceneMarks::CAMERA_POSITION + camera->position->x + " " + camera->position->y + " " + camera->position->z);
	writer->WriteLine("# Цель камеры");
	writer->WriteLine(SceneMarks::CAMERA_TARGET + camera->target->x + " " + camera->target->y + " " + camera->target->z);
	writer->WriteLine("# Отсекающие плоскости");
	writer->WriteLine(SceneMarks::FUSTRUM + camera->near + " " + camera->far);
	writer->WriteLine("# FOV");
	writer->WriteLine(SceneMarks::FOV + camera->fov);
	writer->WriteLine("# Вид проецирования");
	writer->WriteLine(SceneMarks::PROJ_TYPE + (camera->perspective ? "1" : "0"));
	writer->WriteLine("# Цвет фона");
	writer->WriteLine(SceneMarks::BG_COLOR + bgColor.R + " " + bgColor.G + " " + bgColor.B);
	writer->WriteLine("# Цвет линии");
	writer->WriteLine(SceneMarks::LINE_COLOR + edgeColor.R + " " + edgeColor.G + " " + edgeColor.B);
	writer->WriteLine("# Счётчик объектов");
	writer->WriteLine(SceneMarks::OBJ_COUNT + objTotalCount);
	writer->WriteLine();

	writer->WriteLine("### Объекты");
	for each (SceneObject ^ obj in objects)
	{
		obj->saveToStream(writer);
		writer->WriteLine(SceneMarks::END_OF_OBJECT);
		writer->WriteLine();
		writer->WriteLine();
	}
}

void Scene::loadFromStream(Stream ^ stream)
{
	objects->Clear();
	StreamReader ^ reader = gcnew StreamReader(stream);

	String ^ line;
	while ((line = reader->ReadLine()) != nullptr)
	{
		if (line->Length == 0)
			continue;
		if (line->StartsWith(SceneMarks::CAMERA_POSITION))
		{
			array<String ^> ^ data = line->Split(' ');
			camera->position = gcnew Vector3D(double::Parse(data[1]), double::Parse(data[2]), double::Parse(data[3]));
		}
		else if (line->StartsWith(SceneMarks::CAMERA_TARGET))
		{
			array<String ^> ^ data = line->Split(' ');
			camera->target = gcnew Vector3D(double::Parse(data[1]), double::Parse(data[2]), double::Parse(data[3]));
		}
		else if (line->StartsWith(SceneMarks::FUSTRUM))
		{
			array<String ^> ^ data = line->Split(' ');
			camera->near = double::Parse(data[1]);
			camera->far = double::Parse(data[2]);
		}
		else if (line->StartsWith(SceneMarks::FOV))
		{
			array<String ^> ^ data = line->Split(' ');
			camera->fov = double::Parse(data[1]);
		}
		else if (line->StartsWith(SceneMarks::PROJ_TYPE))
		{
			camera->perspective = line[SceneMarks::PROJ_TYPE->Length] == '1';
		}
		else if (line->StartsWith(SceneMarks::BG_COLOR))
		{
			array<String ^> ^ data = line->Split(' ');
			bgColor = Color::FromArgb(int::Parse(data[1]), int::Parse(data[2]), int::Parse(data[3]));
		}
		else if (line->StartsWith(SceneMarks::LINE_COLOR))
		{
			array<String ^> ^ data = line->Split(' ');
			edgeColor = Color::FromArgb(int::Parse(data[1]), int::Parse(data[2]), int::Parse(data[3]));
		}
		else if (line->StartsWith(SceneMarks::OBJ_COUNT))
		{
			array<String ^> ^ data = line->Split(' ');
			objTotalCount = int::Parse(data[1]);
		}
		else if (line->StartsWith(ObjectMarks::OBJECT))
		{
			Stream ^ buf = gcnew MemoryStream();
			StreamWriter ^ writer = gcnew StreamWriter(buf);
			writer->WriteLine(line);

			while ((line = reader->ReadLine()) != nullptr)
			{
				if (line->Equals(SceneMarks::END_OF_OBJECT))
					break;

				writer->WriteLine(line);
			}
			writer->Flush();
			SceneObject ^ obj = gcnew SceneObject();
			buf->Seek(0, ::SeekOrigin::Begin);
			obj->loadFromStream(buf);
			buf->Close();
			obj->transform();
			objects->Add(obj);
		}
	}
}
