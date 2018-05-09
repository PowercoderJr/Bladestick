#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"

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
	const int N = 1;
	Random ^ rnd = gcnew Random();
	array<SceneObject ^> ^ objects = gcnew array<SceneObject^>(N);
	/*IO::FileStream ^ stream;
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
				scene->drawToBuffer(objects[k]);
			}
			scene->render(g);
		}
	}*/

	SceneObject ^ so = SceneObject::buildBladestick(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	so->setOffset(400, 300, 0);
	scene->setSize(canvas->Width, canvas->Height);

	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(i, 0, 0);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(0, i, 0);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(0, 0, i);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(i, i, 0);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(i, 0, i);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(0, i, i);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 1)
	{
		scene->clear();
		so->setRotation(i, i, i);
		so->transform();
		scene->drawToBuffer(so);
		scene->render(g);
	}
	return Void();
}
