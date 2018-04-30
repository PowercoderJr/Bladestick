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
	/*Matrix ^ m1 = gcnew Matrix(2, 3);
	m1(0, 0) = 4;
	m1(0, 1) = 1;
	m1(0, 2) = -5;
	m1(1, 0) = 6;
	m1(1, 1) = 0;
	m1(1, 2) = 9;
	Matrix ^ m2 = gcnew Matrix(3, 2);
	m2(0, 0) = 16;
	m2(0, 1) = 0;
	m2(1, 0) = 1;
	m2(1, 1) = -4;
	m2(2, 0) = 5;
	m2(2, 1) = -2;
	Matrix ^ m3 = m1 * m2;*/
	
	zb->setSize(canvas->Width, canvas->Height);
	zb->clear();
	Random ^ rnd = gcnew Random();
	Geometry::Box ^ box;// = gcnew Geometry::Box(gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::Orange);
	//Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Vector3D(0, 0, 0), gcnew Geometry::Vector3D(100, 200, 100), Color::Orange);
	//box->update();	
	/*zb->drawLine(Color::Red, 100, 0, 0, 300, 200, 0);
	zb->drawLine(Color::Green, 100, 0, -50, 300, 200, 50);*/
	/*for (int i = 0; i < 10; ++i)
		zb->drawToBuffer(gcnew Geometry::Facet(gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, -100 + rnd->Next(200)), gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, -100 + rnd->Next(200)), gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, -100 + rnd->Next(200)), Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))));*/
	box = gcnew Geometry::Box(gcnew Geometry::Vector3D(300, 400, 0), gcnew Geometry::Vector3D(600, 500, 100), Color::Lime);
	//box = gcnew Geometry::Box(gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Vector3D(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::Lime);
	box->update();
	static int angle = 0;
	box->rotate(++angle, 0, 0);
	zb->drawToBuffer(box);
	/*clock_t start, stop;
	start = clock();
	for (int i = 0; i < 100000; ++i)
	{
		Geometry::Facet ^ facet = gcnew Geometry::Facet(gcnew Geometry::Vector3D(50, 50, 50), gcnew Geometry::Vector3D(100, 300, 50), gcnew Geometry::Vector3D(200, 100, 50), Color::Red);
		zb->drawToBuffer(facet);
	}
	stop = clock();*/
	zb->render(g);
	return System::Void();
}
