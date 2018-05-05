#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"

#include <time.h>

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

System::Void Bladestick::MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//Some debugging here	
	const int N = 5;
	Random ^ rnd = gcnew Random();
	array<SceneObject ^> ^ objects = gcnew array<SceneObject^>(N);
	IO::FileStream ^ stream;
	try
	{
		for (int i = 0; i < N; ++i)
		{
			stream = gcnew IO::FileStream("cube.obj", IO::FileMode::Open);
			objects[i] = gcnew SceneObject();
			objects[i]->loadFromStream(stream);
			//objects[i]->setScaling(0.5, 0.5, 0.5);
			stream->Close();
		}
	}
	finally
	{
		stream->Close();
	}
	zb->setSize(canvas->Width, canvas->Height);
	array<Vector3D ^> ^ dirs = gcnew array<Vector3D ^>(N);
	array<Vector3D ^> ^ rots = gcnew array<Vector3D ^>(N);
	for (int i = 0; i < 10; ++i)
	{
		for (int k = 0; k < N; ++k)
		{
			objects[k]->setScaling(rnd->NextDouble() * 2, rnd->NextDouble() * 2, rnd->NextDouble() * 2);
			objects[k]->setOffset(canvas->Width / 2, canvas->Height / 2, rnd->NextDouble() * 1000 - 500);
			dirs[k] = gcnew Vector3D(rnd->NextDouble() * 50 - 25, rnd->NextDouble() * 50 - 25, rnd->NextDouble() * 50 - 25);
			rots[k] = gcnew Vector3D(rnd->NextDouble() * 8 - 4, rnd->NextDouble() * 8 - 4, rnd->NextDouble() * 8 - 4);
		}

		for (int j = 0; j < 50; ++j)
		{
			zb->clear();
			for (int k = 0; k < N; ++k)
			{
				objects[k]->setRotation(objects[k]->rotation + rots[k]);
				objects[k]->setOffset(objects[k]->offset + dirs[k]);
				objects[k]->transform();
				zb->drawToBuffer(objects[k]);
			}
			zb->render(g);
		}
	}

	/*for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(i, 0, i * 2);
		so->setOffset(-100 + i * 3, -100 + i * 2.5, 0);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(0, i, 0);
		so->setOffset(760 - i, 400 + i, 0);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(0, 0, i);
		so->setOffset(400, 760 - i, 0);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(i, 0, i);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(0, i, i);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(i, i, 0);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(i, i, i);
		so->transform();
		zb->drawToBuffer(so);
		zb->render(g);
	}*/
	return System::Void();
}
