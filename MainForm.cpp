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
	SceneObject ^ so = gcnew SceneObject();
	IO::FileStream ^ stream;
	try
	{
		stream = gcnew IO::FileStream("cube.obj", IO::FileMode::Open);
		so->loadFromStream(stream);
	}
	finally
	{
		stream->Close();
	}
	zb->setSize(canvas->Width, canvas->Height);
	so->setScaling(1, 2, 1.5);
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		so->setRotation(i, 0, 0);
		so->setOffset(400 + i, 400, 0);
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
	}

	/*for (int i = 0; i < 100000; ++i)
	{
		Geometry::Facet ^ facet = gcnew Geometry::Facet(gcnew Geometry::Vector3D(50, 50, 50), gcnew Geometry::Vector3D(100, 300, 50), gcnew Geometry::Vector3D(200, 100, 50), Color::Red);
		zb->drawToBuffer(facet);
	}*/
	return System::Void();
}
