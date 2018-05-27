#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"
#include "Scene.h"

#include <time.h>

using namespace Bladestick;
using namespace Bladestick::Drawing;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^> ^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Bladestick::MainForm form;
	Application::Run(%form);
}

Void MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//Some debugging here	
	scene->setSize(canvas->Width, canvas->Height);
	Random ^ rnd = gcnew Random();

	/*const int N = 1;
	array<SceneObject ^> ^ objects = gcnew array<SceneObject^>(N);
	IO::FileStream ^ stream;
	try
	{
		for (int i = 0; i < N; ++i)
		{
			stream = gcnew IO::FileStream("cube.obj", IO::FileMode::Open);
			objects[i] = gcnew SceneObject();
			objects[i]->loadFromStream(stream);
			stream->Close();
		}
	}
	finally
	{
		stream->Close();
	}
	array<Vector3D ^> ^ dirs = gcnew array<Vector3D ^>(N);
	array<Vector3D ^> ^ rots = gcnew array<Vector3D ^>(N);
	for (int k = 0; k < N; ++k)
	{
		objects[k]->setScaling(3, 3, 3);
		objects[k]->setScaling(rnd->NextDouble() * 2, rnd->NextDouble() * 2, rnd->NextDouble() * 2);
		objects[k]->setOffset(canvas->Width / 2, canvas->Height / 2, rnd->NextDouble() * 100 - 50);
		dirs[k] = gcnew Vector3D(rnd->NextDouble() * 50 - 25, rnd->NextDouble() * 50 - 25, rnd->NextDouble() * 50 - 25);
		rots[k] = gcnew Vector3D(rnd->NextDouble() * 8 - 4, rnd->NextDouble() * 8 - 4, rnd->NextDouble() * 8 - 4);
		for (int j = 0; j < 50; ++j)
		{
			scene->clear();
			for (int k = 0; k < N; ++k)
			{
				objects[k]->setRotation(objects[k]->rotation + rots[k]);
				objects[k]->setOffset(objects[k]->offset + dirs[k]);
				objects[k]->transform();
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, 0, 0);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, i, 0);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, 0, i);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, i, 0);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, 0, i);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, i, i);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, i, i);
					objects[k]->transform();
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
			}
			scene->render(g);
		}
	}*/

	SceneObject ^ so;
	IO::FileStream ^ stream;
	try
	{
		stream = gcnew IO::FileStream("cube.obj", IO::FileMode::Open);
		so = gcnew SceneObject();
		so->loadFromStream(stream);
		stream->Close();
	}
	finally
	{
		stream->Close();
	}
	so->transform();
	scene->setSize(canvas->Width, canvas->Height);
	scene->camera->perspective = true;

	so = SceneObject::buildBladestick(300, 5, 8, 100, 150, /*64*/32, 30, 60, 40, 50, 50, 4, gcnew array<Color>(3) { Color::SaddleBrown, Color::DarkGray, Color::LightGray });
	/*for (int i = 0; i <= 360; i += 5)
	{
		scene->clear();
		so->setOffset(0, 0, i*4);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
		//scene->camera->perspective = i % 10 < 5;
	}*/
	scene->camera->setTarget(0, 0, 0);
	const double distance = 1000;
	for (int i = -90; i <= 270; i += 3)
	{
		double a = Math::Cos(degToRad(i)) * distance;
		double b = Math::Sin(degToRad(i)) * distance;
		scene->camera->setPosition(a, 0, b);
		//scene->camera->setPosition(0, 0, i);
		//scene->camera->fov = i;
		scene->camera->updateDirs();
		/*so->setRotation(i, 0, 0);
		so->transform();*/
		scene->clear();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	/*for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, 0, 0);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, i, 0);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, 0, i);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, i, 0);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, 0, i);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, i, i);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, i, i);
		so->transform();
		scene->drawToBuffer(so, DrawFlags::DRAW_FILL);
		scene->render(g);
	}*/
	return Void();
}
