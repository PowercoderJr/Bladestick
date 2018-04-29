#include "MainForm.h"
#include "Box.h"
#include "Utils.h"
#include "IDrawable.h"

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
	//Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::Orange);
	//Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Point(0, 0, 0), gcnew Geometry::Point(100, 200, 100), Color::Orange);
	//box->update();	
	for (int i = 0; i < 100; ++i)
		zb->drawToBuffer(gcnew Geometry::Facet(gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))));
	//box = gcnew Geometry::Box(gcnew Geometry::Point(300, 400, 0), gcnew Geometry::Point(600, 500, 100), Color::Lime);
	//box = gcnew Geometry::Box(gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::Lime);
	//box->update();
	//zb->drawToBuffer(box);
	zb->render(g);
	/*clock_t start, stop;
	start = clock();
	for (int i = 0; i < 100000; ++i)
	{
		Geometry::Facet ^ facet = gcnew Geometry::Facet(gcnew Geometry::Point(50, 50, 50), gcnew Geometry::Point(100, 300, 50), gcnew Geometry::Point(200, 100, 50), Color::Red);
		zb->drawToBuffer(facet);
		zb->render(g);
	}
	stop = clock();*/

	return System::Void();
}
