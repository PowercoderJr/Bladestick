#include "MainForm.h"
#include "Box.h"
#include "Utils.h"
#include "IDrawable.h"
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
	zb->setSize(canvas->Width, canvas->Height);
	zb->clear();
	Random ^ rnd = gcnew Random();
	Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Vector3D(300, 400, 0), gcnew Geometry::Vector3D(600, 500, 100), Color::Lime);
	Geometry::Vector3D ^ offset = box->getOrigin();
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(i, 0, 0);

		offset = offset->add(2, 0, 0);
		box->setPosition(offset);
		box->setOrigin(offset);

		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(0, i, 0);

		offset = offset->add(-2, 2, 0);
		box->setPosition(offset);
		box->setOrigin(offset);

		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(0, 0, i);

		offset = offset->add(0, -2, 0);
		box->setPosition(offset);
		box->setOrigin(offset);

		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(i, 0, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(0, i, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(i, i, 0);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->setRotationAngles(i, i, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}

	/*for (int i = 0; i < 100000; ++i)
	{
		Geometry::Facet ^ facet = gcnew Geometry::Facet(gcnew Geometry::Vector3D(50, 50, 50), gcnew Geometry::Vector3D(100, 300, 50), gcnew Geometry::Vector3D(200, 100, 50), Color::Red);
		zb->drawToBuffer(facet);
	}*/
	return System::Void();
}
