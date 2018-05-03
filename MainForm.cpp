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
	box->update();
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(i, 0, 0);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(0, i, 0);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(0, 0, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(i, 0, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(0, i, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(i, i, 0);
		zb->drawToBuffer(box);
		zb->render(g);
	}
	for (int i = 0; i <= 360; i += 5)
	{
		zb->clear();
		box->rotate(i, i, i);
		zb->drawToBuffer(box);
		zb->render(g);
	}

	zb->drawToBuffer(box);
	zb->render(g);
	/*for (int i = 0; i < 100000; ++i)
	{
		Geometry::Facet ^ facet = gcnew Geometry::Facet(gcnew Geometry::Vector3D(50, 50, 50), gcnew Geometry::Vector3D(100, 300, 50), gcnew Geometry::Vector3D(200, 100, 50), Color::Red);
		zb->drawToBuffer(facet);
	}*/
	return System::Void();
}
