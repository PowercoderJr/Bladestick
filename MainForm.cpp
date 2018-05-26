#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"

using namespace Bladestick::Drawing;
using namespace Bladestick;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System;

[STAThreadAttribute]
void Main(array<String^> ^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MainForm form;
	Application::Run(%form);
}

Void MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//Some debugging here	
	bool flipVertical = true;
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
				objects[k]->transform(scene->camera);
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, 0, 0);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, i, 0);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, 0, i);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, i, 0);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, 0, i);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(0, i, i);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
				for (int i = 0; i <= 360; i += 3)
				{
					scene->clear();
					objects[k]->setRotation(i, i, i);
					objects[k]->transform(scene->camera);
					scene->drawToBuffer(objects[k], flipVertical);
					scene->render(g);
				}
			}
			scene->render(g);
		}
	}*/
	/*so->setOffset(400, 300, 0);
	scene->setSize(canvas->Width, canvas->Height);

	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, 0, 0);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}*/
	/*for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, i, 0);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, 0, i);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, i, 0);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, 0, i);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(0, i, i);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}
	for (int i = 0; i <= 360; i += 3)
	{
		scene->clear();
		so->setRotation(i, i, i);
		so->transform(scene->camera);
		scene->drawToBuffer(so, flipVertical);
		scene->render(g);
	}*/
	return Void();
}

void MainForm::redrawScene()
{
	scene->setSize(canvas->Width, canvas->Height);
	scene->clear();
	scene->drawObjectsToBuffer();
	scene->render(g);
}

void MainForm::applyObjParams()
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	SceneObject ^ newSO = SceneObject::buildBladestick(Convert::ToDouble(handleLengthInput->Value),
		Convert::ToInt32(handleRingsCountInput->Value),
		Convert::ToInt32(handleEdgesCountInput->Value),
		Convert::ToDouble(inBladeRadiusInput->Value),
		Convert::ToDouble(exBladeRadiusInput->Value),
		Convert::ToInt32(bladeEdgesCountInput->Value),
		Convert::ToDouble(bladeThicknessInput->Value),
		Convert::ToDouble(primarySpikeLengthInput->Value),
		Convert::ToDouble(primarySpikeAngleInput->Value),
		Convert::ToDouble(secondarySpikeLengthInput->Value),
		Convert::ToDouble(secondarySpikeAngleInput->Value),
		Convert::ToInt32(secondarySpikesCountInput->Value * 4),
		gcnew array<Color>(3) { color1Btn->BackColor, color2Btn->BackColor, color3Btn->BackColor });

	SceneObject ^ so = safe_cast<SceneObject ^>(objectsListBox->SelectedItems[0]);
	so->vertices = newSO->vertices;
	so->indices = newSO->indices;
	so->colors = newSO->colors;
	//TODO: изменить список передаваемых аргументов после слияния
	so->transform(scene->camera);

	redrawScene();
}

Void MainForm::secondarySpikesCountInput_ValueChanged(Object ^ sender, EventArgs ^ e)
{
	secondarySpikesCountLabel->Text = "" + (secondarySpikesCountInput->Value * 4);
}

Void MainForm::createObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	SceneObject ^ so = SceneObject::buildBladestick(
		SceneObject::DEFAULT_HANDLE_LENGTH,
		SceneObject::DEFAULT_HANDLE_RINGS_COUNT,
		SceneObject::DEFAULT_HANDLE_EDGES_COUNT,
		SceneObject::DEFAULT_IN_BLADE_RADIUS,
		SceneObject::DEFAULT_EX_BLADE_RADIUS,
		SceneObject::DEFAULT_BLADE_EDGES_COUNT,
		SceneObject::DEFAULT_BLADE_THICKNESS,
		SceneObject::DEFAULT_PRIMARY_SPIKE_LENGTH,
		SceneObject::DEFAULT_PRIMARY_SPIKE_ANGLE,
		SceneObject::DEFAULT_SECONDARY_SPIKE_LENGTH,
		SceneObject::DEFAULT_SECONDARY_SPIKE_ANGLE,
		SceneObject::DEFAULT_SECONDARY_SPIKES_COUNT,
		gcnew array<Color>(3) { SceneObject::DEFAULT_COLOR_1, SceneObject::DEFAULT_COLOR_2, SceneObject::DEFAULT_COLOR_3}
	);
	so->name = "Объект #" + ++scene->objCount;
	scene->objects->Add(so);
	objectsListBox->ClearSelected();
	objectsListBox->SelectedItem = so;

	redrawScene();
}

Void MainForm::deleteObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	String ^ question = objectsListBox->SelectedItems->Count > 1 ?
		"Удалить выделенные объекты (" + objectsListBox->SelectedItems->Count + " шт.)?" :
		"Удалить " + ((SceneObject ^)objectsListBox->SelectedItem)->name + "?";
	if (MessageBox::Show(this, question, "Подтвердите операцию", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
	{
		Collections::Generic::List<SceneObject ^> ^ items = gcnew Collections::Generic::List<SceneObject ^>(objectsListBox->SelectedItems->Count);
		for (int i = 0; i < objectsListBox->SelectedItems->Count; ++i)
			items->Add(scene->objects[objectsListBox->SelectedIndices[i]]);
		for (int i = 0; i < items->Count; ++i)
			scene->objects->Remove(items[i]);
		objectsListBox->ClearSelected();
	}

	redrawScene();
}

Void MainForm::clearObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (MessageBox::Show(this, "Очистить список объектов?", "Подтвердите операцию", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
	{
		scene->objects->Clear();
	}

	redrawScene();
}

Void MainForm::colorBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (colorDialog1->ShowDialog() == ::DialogResult::OK)
		safe_cast<Button ^>(sender)->BackColor = colorDialog1->Color;
}

Void MainForm::onObjTransformationChanged(Object ^ sender, EventArgs ^ e)
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	if (sender == objPosX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->x = Convert::ToDouble(objPosX->Value);
	else if (sender == objPosY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->y = Convert::ToDouble(objPosY->Value);
	else if (sender == objPosZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->z = Convert::ToDouble(objPosZ->Value);
	else if (sender == objRotX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->x = Convert::ToDouble(objRotX->Value);
	else if (sender == objRotY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->y = Convert::ToDouble(objRotY->Value);
	else if (sender == objRotZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->z = Convert::ToDouble(objRotZ->Value);
	else if (sender == objScaleX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->x = Convert::ToDouble(objScaleX->Value);
	else if (sender == objScaleY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->y = Convert::ToDouble(objScaleY->Value);
	else if (sender == objScaleZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->z = Convert::ToDouble(objScaleZ->Value);

	for each (SceneObject ^ so in objectsListBox->SelectedItems)
		//TODO: изменить список передаваемых аргументов после слияния
		so->transform(scene->camera);
	
	redrawScene();
}

Void MainForm::onObjParamChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyChb->Checked)
		applyObjParams();
}

Void MainForm::objectsListBox_SelectedValueChanged(Object ^ sender, EventArgs ^ e)
{
	for each (Control ^ control in selectionDependedControls)
		control->Enabled = objectsListBox->SelectedItems->Count > 0;

	if (autoApplyChb->Checked)
		applyBtn->Enabled = false;
}

Void MainForm::autoApplyChb_CheckedChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyChb->Checked)
		applyBtn->Enabled = false;
	else
		applyBtn->Enabled = objectsListBox->SelectedItems->Count > 0;;
}

Void MainForm::applyBtn_Click(Object ^ sender, EventArgs ^ e)
{
	applyObjParams();
}

Void MainForm::setDefaultParamsBtn_Click(Object ^ sender, EventArgs ^ e)
{
	bool autoApplyChecked = autoApplyChb->Checked;
	autoApplyChb->Checked = false;

	handleLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_LENGTH);
	handleRingsCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_RINGS_COUNT);
	handleEdgesCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_EDGES_COUNT);
	inBladeRadiusInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_IN_BLADE_RADIUS);
	exBladeRadiusInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_EX_BLADE_RADIUS);
	bladeEdgesCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_BLADE_EDGES_COUNT);
	bladeThicknessInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_BLADE_THICKNESS);
	primarySpikeLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_PRIMARY_SPIKE_LENGTH);
	primarySpikeAngleInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_PRIMARY_SPIKE_ANGLE);
	secondarySpikeLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_SECONDARY_SPIKE_LENGTH);
	secondarySpikeAngleInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_SECONDARY_SPIKE_ANGLE);
	secondarySpikesCountInput->Value = SceneObject::DEFAULT_SECONDARY_SPIKES_COUNT / 4;
	color1Btn->BackColor = SceneObject::DEFAULT_COLOR_1;
	color2Btn->BackColor = SceneObject::DEFAULT_COLOR_2;
	color3Btn->BackColor = SceneObject::DEFAULT_COLOR_3;
	
	autoApplyChb->Checked = autoApplyChecked;
	if (autoApplyChb->Checked)
		applyObjParams();
}
