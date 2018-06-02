#pragma once

#include "Scene.h"

namespace Bladestick
{
	/*using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	/// <summary>
	/// Ñâîäêà äëÿ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		System::Drawing::Graphics ^ g;
		System::ComponentModel::BackgroundWorker^  backgroundWorker;
		System::Windows::Forms::MenuStrip^  menuStrip;
		System::Windows::Forms::Panel^  objControllerPanel;
		System::Windows::Forms::Button^  clearObjBtn;
		System::Windows::Forms::Button^  deleteObjBtn;
		System::Windows::Forms::Button^  createObjBtn;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::ListBox^  objectsListBox;
		System::Windows::Forms::PictureBox^  canvas;
		System::Windows::Forms::GroupBox^  objTransformGroup;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label4;
		System::Windows::Forms::GroupBox^  objParamsGroup;
		System::Windows::Forms::Label^  label16;
		System::Windows::Forms::NumericUpDown^  secondarySpikeAngleInput;
		System::Windows::Forms::Label^  label14;
		System::Windows::Forms::NumericUpDown^  primarySpikeAngleInput;
		System::Windows::Forms::Label^  label15;
		System::Windows::Forms::NumericUpDown^  secondarySpikeLengthInput;
		System::Windows::Forms::Label^  label13;
		System::Windows::Forms::NumericUpDown^  primarySpikeLengthInput;
		System::Windows::Forms::Label^  label12;
		System::Windows::Forms::NumericUpDown^  bladeThicknessInput;
		System::Windows::Forms::Label^  label11;
		System::Windows::Forms::NumericUpDown^  bladeEdgesCountInput;
		System::Windows::Forms::Label^  label10;
		System::Windows::Forms::NumericUpDown^  exBladeRadiusInput;
		System::Windows::Forms::Label^  label9;
		System::Windows::Forms::NumericUpDown^  inBladeRadiusInput;
		System::Windows::Forms::Label^  label8;
		System::Windows::Forms::NumericUpDown^  handleEdgesCountInput;
		System::Windows::Forms::Label^  label7;
		System::Windows::Forms::NumericUpDown^  handleRingsCountInput;
		System::Windows::Forms::Label^  label6;
		System::Windows::Forms::NumericUpDown^  handleLengthInput;
		System::Windows::Forms::Label^  label5;
		System::Windows::Forms::TrackBar^  secondarySpikesCountInput;
		System::Windows::Forms::Button^  color3Btn;
		System::Windows::Forms::Button^  color2Btn;
		System::Windows::Forms::Button^  color1Btn;
		System::Windows::Forms::Label^  label17;
		System::Windows::Forms::ColorDialog^  colorDialog;
		System::Windows::Forms::CheckBox^  autoApplyParamsChb;
		System::Windows::Forms::Button^  applyParamsBtn;
		System::Windows::Forms::Button^  setDefaultParamsBtn;
		System::Windows::Forms::Label^  secondarySpikesCountLabel;
		System::Windows::Forms::NumericUpDown^  objScaleZ;
		System::Windows::Forms::NumericUpDown^  objScaleY;
		System::Windows::Forms::NumericUpDown^  objScaleX;
		System::Windows::Forms::NumericUpDown^  objRotZ;
		System::Windows::Forms::NumericUpDown^  objRotY;
		System::Windows::Forms::NumericUpDown^  objRotX;
		System::Windows::Forms::NumericUpDown^  objPosZ;
		System::Windows::Forms::NumericUpDown^  objPosY;
		System::Windows::Forms::NumericUpDown^  objPosX;
		System::Windows::Forms::ToolStripMenuItem^  ñöåíàToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  îáíîâèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  î÷èñòèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		System::Windows::Forms::ToolStripMenuItem^  ñîõðàíèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  çàãðóçèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  ïóëüòToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  íàñòðîéêèÐåíäåðàToolStripMenuItem;
		System::Windows::Forms::Panel^  cameraControllerPanel;
		System::Windows::Forms::Panel^  renderControllerPanel;
		System::Windows::Forms::Panel^  controllersPanel;
		System::Windows::Forms::GroupBox^  groupBox2;
		System::Windows::Forms::NumericUpDown^  cameraRelativePosZ;
		System::Windows::Forms::NumericUpDown^  cameraRelativePosY;
		System::Windows::Forms::NumericUpDown^  cameraRelativePosX;
		System::Windows::Forms::Label^  label22;
		System::Windows::Forms::Label^  label21;
		System::Windows::Forms::ComboBox^  placeCameraRelativeCb;
		System::Windows::Forms::GroupBox^  groupBox1;
		System::Windows::Forms::NumericUpDown^  cameraRoll;
		System::Windows::Forms::NumericUpDown^  cameraPitch;
		System::Windows::Forms::NumericUpDown^  cameraYaw;
		System::Windows::Forms::NumericUpDown^  cameraTargetZ;
		System::Windows::Forms::NumericUpDown^  cameraTargetY;
		System::Windows::Forms::NumericUpDown^  cameraTargetX;
		System::Windows::Forms::NumericUpDown^  cameraPosZ;
		System::Windows::Forms::NumericUpDown^  cameraPosY;
		System::Windows::Forms::NumericUpDown^  cameraPosX;
		System::Windows::Forms::Label^  label18;
		System::Windows::Forms::Label^  label19;
		System::Windows::Forms::Label^  label20;
		System::Windows::Forms::GroupBox^  groupBox3;
		System::Windows::Forms::Button^  cameraLookAtBtn;
		System::Windows::Forms::Label^  label24;
		System::Windows::Forms::ComboBox^  cameraLookAtCb;
		System::Windows::Forms::Button^  placeCameraRelativeBtn;
		System::Windows::Forms::GroupBox^  groupBox7;
		System::Windows::Forms::Button^  edgesColorBtn;
		System::Windows::Forms::Label^  label28;
		System::Windows::Forms::Button^  sceneBgColorBtn;
		System::Windows::Forms::Label^  label27;
		System::Windows::Forms::GroupBox^  groupBox6;
		System::Windows::Forms::CheckBox^  useRandomPaletteChb;
		System::Windows::Forms::CheckBox^  drawFillChb;
		System::Windows::Forms::CheckBox^  drawEdgesChb;
		System::Windows::Forms::GroupBox^  groupBox5;
		System::Windows::Forms::Label^  fovLabel;
		System::Windows::Forms::TrackBar^  fovInput;
		System::Windows::Forms::Label^  label26;
		System::Windows::Forms::NumericUpDown^  farPlaneInput;
		System::Windows::Forms::NumericUpDown^  nearPlaneInput;
		System::Windows::Forms::Label^  label25;
		System::Windows::Forms::Label^  label23;
		System::Windows::Forms::GroupBox^  groupBox4;
		System::Windows::Forms::RadioButton^  cProjectionRb;
		System::Windows::Forms::RadioButton^  pProjectionRb;
		Drawing::Scene ^ scene;
		array<Control ^> ^ selectionDependedControls;
		System::Windows::Forms::CheckBox^  simulateLightChb;
		System::Windows::Forms::SaveFileDialog^  saveFileDialog;
		System::Windows::Forms::OpenFileDialog^  openFileDialog;
		bool autoApplyInputs;
		void redrawScene();
		void applyObjTransform(Object ^ sender);
		void applyObjParams();
		bool applyCameraTransform(Object ^ sender);
		void updateObjComboBoxes();
		void updateCameraTransformInputs();
		System::Void secondarySpikesCountInput_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void createObjBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void deleteObjBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void clearObjBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void onObjTransformationChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onObjParamChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void objectsListBox_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void applyBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void setDefaultParamsBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void colorBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void onObjTransformationKeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		System::Void onCameraTransformationChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void placeCameraRelativeCb_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void cameraLookAtCb_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void placeCameraRelativeBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void cameraLookAtBtn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void canvas_Resize(System::Object^  sender, System::EventArgs^  e);
		System::Void îáíîâèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void controllerPanelSwitch_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void onProjectionTypeChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onFrustumChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onPaletteBtnClicked(System::Object^  sender, System::EventArgs^  e);
		System::Void onFovInputValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onDrawMethodChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void MainForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		System::Void ñîõðàíèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void çàãðóçèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

	public:
		MainForm(void);

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ðåñóðñû.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåðåìåííàÿ êîíñòðóêòîðà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òðåáóåìûé ìåòîä äëÿ ïîääåðæêè êîíñòðóêòîðà — íå èçìåíÿéòå 
		/// ñîäåðæèìîå ýòîãî ìåòîäà ñ ïîìîùüþ ðåäàêòîðà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->ñöåíàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îáíîâèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->î÷èñòèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ñîõðàíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàãðóçèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïóëüòToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->objControllerPanel = (gcnew System::Windows::Forms::Panel());
			this->objParamsGroup = (gcnew System::Windows::Forms::GroupBox());
			this->autoApplyParamsChb = (gcnew System::Windows::Forms::CheckBox());
			this->setDefaultParamsBtn = (gcnew System::Windows::Forms::Button());
			this->secondarySpikesCountLabel = (gcnew System::Windows::Forms::Label());
			this->applyParamsBtn = (gcnew System::Windows::Forms::Button());
			this->color3Btn = (gcnew System::Windows::Forms::Button());
			this->color2Btn = (gcnew System::Windows::Forms::Button());
			this->color1Btn = (gcnew System::Windows::Forms::Button());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->secondarySpikesCountInput = (gcnew System::Windows::Forms::TrackBar());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->secondarySpikeAngleInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->primarySpikeAngleInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->secondarySpikeLengthInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->primarySpikeLengthInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->bladeThicknessInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->bladeEdgesCountInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->exBladeRadiusInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->inBladeRadiusInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->handleEdgesCountInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->handleRingsCountInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->handleLengthInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->objTransformGroup = (gcnew System::Windows::Forms::GroupBox());
			this->objScaleZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->objScaleY = (gcnew System::Windows::Forms::NumericUpDown());
			this->objScaleX = (gcnew System::Windows::Forms::NumericUpDown());
			this->objRotZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->objRotY = (gcnew System::Windows::Forms::NumericUpDown());
			this->objRotX = (gcnew System::Windows::Forms::NumericUpDown());
			this->objPosZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->objPosY = (gcnew System::Windows::Forms::NumericUpDown());
			this->objPosX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->clearObjBtn = (gcnew System::Windows::Forms::Button());
			this->deleteObjBtn = (gcnew System::Windows::Forms::Button());
			this->createObjBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->objectsListBox = (gcnew System::Windows::Forms::ListBox());
			this->canvas = (gcnew System::Windows::Forms::PictureBox());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->cameraControllerPanel = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->cameraLookAtBtn = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->cameraLookAtCb = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->placeCameraRelativeBtn = (gcnew System::Windows::Forms::Button());
			this->cameraRelativePosZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraRelativePosY = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraRelativePosX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->placeCameraRelativeCb = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->fovLabel = (gcnew System::Windows::Forms::Label());
			this->fovInput = (gcnew System::Windows::Forms::TrackBar());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->farPlaneInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->nearPlaneInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->cameraRoll = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraPitch = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraYaw = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraTargetZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraTargetY = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraTargetX = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraPosZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraPosY = (gcnew System::Windows::Forms::NumericUpDown());
			this->cameraPosX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->cProjectionRb = (gcnew System::Windows::Forms::RadioButton());
			this->pProjectionRb = (gcnew System::Windows::Forms::RadioButton());
			this->renderControllerPanel = (gcnew System::Windows::Forms::Panel());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->edgesColorBtn = (gcnew System::Windows::Forms::Button());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->sceneBgColorBtn = (gcnew System::Windows::Forms::Button());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->simulateLightChb = (gcnew System::Windows::Forms::CheckBox());
			this->useRandomPaletteChb = (gcnew System::Windows::Forms::CheckBox());
			this->drawFillChb = (gcnew System::Windows::Forms::CheckBox());
			this->drawEdgesChb = (gcnew System::Windows::Forms::CheckBox());
			this->controllersPanel = (gcnew System::Windows::Forms::Panel());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip->SuspendLayout();
			this->objControllerPanel->SuspendLayout();
			this->objParamsGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikesCountInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikeAngleInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->primarySpikeAngleInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikeLengthInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->primarySpikeLengthInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bladeThicknessInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bladeEdgesCountInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->exBladeRadiusInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inBladeRadiusInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleEdgesCountInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleRingsCountInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleLengthInput))->BeginInit();
			this->objTransformGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->BeginInit();
			this->cameraControllerPanel->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosX))->BeginInit();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fovInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->farPlaneInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nearPlaneInput))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRoll))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPitch))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraYaw))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosX))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->renderControllerPanel->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->controllersPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ñöåíàToolStripMenuItem,
					this->ïóëüòToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1264, 24);
			this->menuStrip->TabIndex = 3;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// ñöåíàToolStripMenuItem
			// 
			this->ñöåíàToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->îáíîâèòüToolStripMenuItem,
					this->î÷èñòèòüToolStripMenuItem, this->toolStripSeparator1, this->ñîõðàíèòüToolStripMenuItem, this->çàãðóçèòüToolStripMenuItem
			});
			this->ñöåíàToolStripMenuItem->Name = L"ñöåíàToolStripMenuItem";
			this->ñöåíàToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->ñöåíàToolStripMenuItem->Text = L"Ñöåíà";
			// 
			// îáíîâèòüToolStripMenuItem
			// 
			this->îáíîâèòüToolStripMenuItem->Name = L"îáíîâèòüToolStripMenuItem";
			this->îáíîâèòüToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F5;
			this->îáíîâèòüToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->îáíîâèòüToolStripMenuItem->Text = L"Îáíîâèòü";
			this->îáíîâèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::îáíîâèòüToolStripMenuItem_Click);
			// 
			// î÷èñòèòüToolStripMenuItem
			// 
			this->î÷èñòèòüToolStripMenuItem->Name = L"î÷èñòèòüToolStripMenuItem";
			this->î÷èñòèòüToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->î÷èñòèòüToolStripMenuItem->Text = L"Î÷èñòèòü";
			this->î÷èñòèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearObjBtn_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(178, 6);
			// 
			// ñîõðàíèòüToolStripMenuItem
			// 
			this->ñîõðàíèòüToolStripMenuItem->Name = L"ñîõðàíèòüToolStripMenuItem";
			this->ñîõðàíèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->ñîõðàíèòüToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->ñîõðàíèòüToolStripMenuItem->Text = L"Ñîõðàíèòü...";
			this->ñîõðàíèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîõðàíèòüToolStripMenuItem_Click);
			// 
			// çàãðóçèòüToolStripMenuItem
			// 
			this->çàãðóçèòüToolStripMenuItem->Name = L"çàãðóçèòüToolStripMenuItem";
			this->çàãðóçèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->çàãðóçèòüToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->çàãðóçèòüToolStripMenuItem->Text = L"Çàãðóçèòü...";
			this->çàãðóçèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::çàãðóçèòüToolStripMenuItem_Click);
			// 
			// ïóëüòToolStripMenuItem
			// 
			this->ïóëüòToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem,
					this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem, this->íàñòðîéêèÐåíäåðàToolStripMenuItem
			});
			this->ïóëüòToolStripMenuItem->Name = L"ïóëüòToolStripMenuItem";
			this->ïóëüòToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->ïóëüòToolStripMenuItem->Text = L"Ïóëüò";
			// 
			// ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem
			// 
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->Name = L"ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem";
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D1));
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->Size = System::Drawing::Size(278, 22);
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->Tag = L"0";
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->Text = L"Ïóëüò óïðàâëåíèÿ îáúåêòàìè";
			this->ïóëüòÓïðàâëåíèÿÎáúåêòàìèToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::controllerPanelSwitch_Click);
			// 
			// ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem
			// 
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->Name = L"ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem";
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D2));
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->Size = System::Drawing::Size(278, 22);
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->Tag = L"1";
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->Text = L"Ïóëüò óïðàâëåíèÿ êàìåðîé";
			this->ïóëüòÓïðàâëåíèÿÊàìåðîéToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::controllerPanelSwitch_Click);
			// 
			// íàñòðîéêèÐåíäåðàToolStripMenuItem
			// 
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->Name = L"íàñòðîéêèÐåíäåðàToolStripMenuItem";
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D3));
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->Size = System::Drawing::Size(278, 22);
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->Tag = L"2";
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->Text = L"Íàñòðîéêè ðåíäåðà";
			this->íàñòðîéêèÐåíäåðàToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::controllerPanelSwitch_Click);
			// 
			// objControllerPanel
			// 
			this->objControllerPanel->AutoScroll = true;
			this->objControllerPanel->Controls->Add(this->objParamsGroup);
			this->objControllerPanel->Controls->Add(this->objTransformGroup);
			this->objControllerPanel->Controls->Add(this->clearObjBtn);
			this->objControllerPanel->Controls->Add(this->deleteObjBtn);
			this->objControllerPanel->Controls->Add(this->createObjBtn);
			this->objControllerPanel->Controls->Add(this->label1);
			this->objControllerPanel->Controls->Add(this->objectsListBox);
			this->objControllerPanel->Location = System::Drawing::Point(288, 33);
			this->objControllerPanel->Name = L"objControllerPanel";
			this->objControllerPanel->Size = System::Drawing::Size(310, 740);
			this->objControllerPanel->TabIndex = 4;
			// 
			// objParamsGroup
			// 
			this->objParamsGroup->Controls->Add(this->autoApplyParamsChb);
			this->objParamsGroup->Controls->Add(this->setDefaultParamsBtn);
			this->objParamsGroup->Controls->Add(this->secondarySpikesCountLabel);
			this->objParamsGroup->Controls->Add(this->applyParamsBtn);
			this->objParamsGroup->Controls->Add(this->color3Btn);
			this->objParamsGroup->Controls->Add(this->color2Btn);
			this->objParamsGroup->Controls->Add(this->color1Btn);
			this->objParamsGroup->Controls->Add(this->label17);
			this->objParamsGroup->Controls->Add(this->secondarySpikesCountInput);
			this->objParamsGroup->Controls->Add(this->label16);
			this->objParamsGroup->Controls->Add(this->secondarySpikeAngleInput);
			this->objParamsGroup->Controls->Add(this->label14);
			this->objParamsGroup->Controls->Add(this->primarySpikeAngleInput);
			this->objParamsGroup->Controls->Add(this->label15);
			this->objParamsGroup->Controls->Add(this->secondarySpikeLengthInput);
			this->objParamsGroup->Controls->Add(this->label13);
			this->objParamsGroup->Controls->Add(this->primarySpikeLengthInput);
			this->objParamsGroup->Controls->Add(this->label12);
			this->objParamsGroup->Controls->Add(this->bladeThicknessInput);
			this->objParamsGroup->Controls->Add(this->label11);
			this->objParamsGroup->Controls->Add(this->bladeEdgesCountInput);
			this->objParamsGroup->Controls->Add(this->label10);
			this->objParamsGroup->Controls->Add(this->exBladeRadiusInput);
			this->objParamsGroup->Controls->Add(this->label9);
			this->objParamsGroup->Controls->Add(this->inBladeRadiusInput);
			this->objParamsGroup->Controls->Add(this->label8);
			this->objParamsGroup->Controls->Add(this->handleEdgesCountInput);
			this->objParamsGroup->Controls->Add(this->label7);
			this->objParamsGroup->Controls->Add(this->handleRingsCountInput);
			this->objParamsGroup->Controls->Add(this->label6);
			this->objParamsGroup->Controls->Add(this->handleLengthInput);
			this->objParamsGroup->Controls->Add(this->label5);
			this->objParamsGroup->Location = System::Drawing::Point(8, 287);
			this->objParamsGroup->Name = L"objParamsGroup";
			this->objParamsGroup->Size = System::Drawing::Size(280, 448);
			this->objParamsGroup->TabIndex = 7;
			this->objParamsGroup->TabStop = false;
			this->objParamsGroup->Text = L"Ïàðàìåòðû";
			// 
			// autoApplyParamsChb
			// 
			this->autoApplyParamsChb->Appearance = System::Windows::Forms::Appearance::Button;
			this->autoApplyParamsChb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7));
			this->autoApplyParamsChb->Location = System::Drawing::Point(5, 402);
			this->autoApplyParamsChb->Name = L"autoApplyParamsChb";
			this->autoApplyParamsChb->Size = System::Drawing::Size(90, 40);
			this->autoApplyParamsChb->TabIndex = 28;
			this->autoApplyParamsChb->Text = L"Ïðèìåíÿòü àâòîìàòè÷åñêè";
			this->autoApplyParamsChb->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->autoApplyParamsChb->UseVisualStyleBackColor = true;
			// 
			// setDefaultParamsBtn
			// 
			this->setDefaultParamsBtn->Enabled = false;
			this->setDefaultParamsBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->setDefaultParamsBtn->Location = System::Drawing::Point(185, 402);
			this->setDefaultParamsBtn->Name = L"setDefaultParamsBtn";
			this->setDefaultParamsBtn->Size = System::Drawing::Size(90, 40);
			this->setDefaultParamsBtn->TabIndex = 30;
			this->setDefaultParamsBtn->Text = L"Çàïîëíèòü ïî óìîë÷àíèþ";
			this->setDefaultParamsBtn->UseVisualStyleBackColor = true;
			this->setDefaultParamsBtn->Click += gcnew System::EventHandler(this, &MainForm::setDefaultParamsBtn_Click);
			// 
			// secondarySpikesCountLabel
			// 
			this->secondarySpikesCountLabel->AutoSize = true;
			this->secondarySpikesCountLabel->Location = System::Drawing::Point(172, 306);
			this->secondarySpikesCountLabel->Name = L"secondarySpikesCountLabel";
			this->secondarySpikesCountLabel->Size = System::Drawing::Size(13, 13);
			this->secondarySpikesCountLabel->TabIndex = 29;
			this->secondarySpikesCountLabel->Text = L"4";
			// 
			// applyParamsBtn
			// 
			this->applyParamsBtn->Enabled = false;
			this->applyParamsBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->applyParamsBtn->Location = System::Drawing::Point(95, 402);
			this->applyParamsBtn->Name = L"applyParamsBtn";
			this->applyParamsBtn->Size = System::Drawing::Size(90, 40);
			this->applyParamsBtn->TabIndex = 29;
			this->applyParamsBtn->Text = L"Ïðèìåíèòü";
			this->applyParamsBtn->UseVisualStyleBackColor = true;
			this->applyParamsBtn->Click += gcnew System::EventHandler(this, &MainForm::applyBtn_Click);
			// 
			// color3Btn
			// 
			this->color3Btn->BackColor = System::Drawing::Color::White;
			this->color3Btn->Enabled = false;
			this->color3Btn->Location = System::Drawing::Point(210, 365);
			this->color3Btn->Name = L"color3Btn";
			this->color3Btn->Size = System::Drawing::Size(64, 23);
			this->color3Btn->TabIndex = 27;
			this->color3Btn->UseVisualStyleBackColor = false;
			this->color3Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			// 
			// color2Btn
			// 
			this->color2Btn->BackColor = System::Drawing::Color::White;
			this->color2Btn->Enabled = false;
			this->color2Btn->Location = System::Drawing::Point(139, 365);
			this->color2Btn->Name = L"color2Btn";
			this->color2Btn->Size = System::Drawing::Size(64, 23);
			this->color2Btn->TabIndex = 26;
			this->color2Btn->UseVisualStyleBackColor = false;
			this->color2Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			// 
			// color1Btn
			// 
			this->color1Btn->BackColor = System::Drawing::Color::White;
			this->color1Btn->Enabled = false;
			this->color1Btn->Location = System::Drawing::Point(68, 365);
			this->color1Btn->Name = L"color1Btn";
			this->color1Btn->Size = System::Drawing::Size(64, 23);
			this->color1Btn->TabIndex = 25;
			this->color1Btn->UseVisualStyleBackColor = false;
			this->color1Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(5, 370);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(53, 13);
			this->label17->TabIndex = 24;
			this->label17->Text = L"Ïàëèòðà:";
			// 
			// secondarySpikesCountInput
			// 
			this->secondarySpikesCountInput->Enabled = false;
			this->secondarySpikesCountInput->LargeChange = 4;
			this->secondarySpikesCountInput->Location = System::Drawing::Point(5, 322);
			this->secondarySpikesCountInput->Maximum = 15;
			this->secondarySpikesCountInput->Minimum = 1;
			this->secondarySpikesCountInput->Name = L"secondarySpikesCountInput";
			this->secondarySpikesCountInput->Size = System::Drawing::Size(270, 45);
			this->secondarySpikesCountInput->TabIndex = 23;
			this->secondarySpikesCountInput->Value = 1;
			this->secondarySpikesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::secondarySpikesCountInput_ValueChanged);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 306);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(160, 13);
			this->label16->TabIndex = 22;
			this->label16->Text = L"Êîëè÷åñòâî âòîðè÷íûõ øèïîâ:";
			// 
			// secondarySpikeAngleInput
			// 
			this->secondarySpikeAngleInput->DecimalPlaces = 2;
			this->secondarySpikeAngleInput->Enabled = false;
			this->secondarySpikeAngleInput->Location = System::Drawing::Point(210, 278);
			this->secondarySpikeAngleInput->Name = L"secondarySpikeAngleInput";
			this->secondarySpikeAngleInput->Size = System::Drawing::Size(64, 20);
			this->secondarySpikeAngleInput->TabIndex = 21;
			this->secondarySpikeAngleInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(78, 280);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(126, 13);
			this->label14->TabIndex = 20;
			this->label14->Text = L"Óãîë âòîðè÷íûõ øèïîâ:";
			// 
			// primarySpikeAngleInput
			// 
			this->primarySpikeAngleInput->DecimalPlaces = 2;
			this->primarySpikeAngleInput->Enabled = false;
			this->primarySpikeAngleInput->Location = System::Drawing::Point(210, 226);
			this->primarySpikeAngleInput->Name = L"primarySpikeAngleInput";
			this->primarySpikeAngleInput->Size = System::Drawing::Size(64, 20);
			this->primarySpikeAngleInput->TabIndex = 19;
			this->primarySpikeAngleInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(77, 228);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(127, 13);
			this->label15->TabIndex = 18;
			this->label15->Text = L"Óãîë ïåðâè÷íûõ øèïîâ:";
			// 
			// secondarySpikeLengthInput
			// 
			this->secondarySpikeLengthInput->DecimalPlaces = 2;
			this->secondarySpikeLengthInput->Enabled = false;
			this->secondarySpikeLengthInput->Location = System::Drawing::Point(210, 252);
			this->secondarySpikeLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->secondarySpikeLengthInput->Name = L"secondarySpikeLengthInput";
			this->secondarySpikeLengthInput->Size = System::Drawing::Size(64, 20);
			this->secondarySpikeLengthInput->TabIndex = 17;
			this->secondarySpikeLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(70, 254);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(134, 13);
			this->label13->TabIndex = 16;
			this->label13->Text = L"Äëèíà âòîðè÷íûõ øèïîâ:";
			// 
			// primarySpikeLengthInput
			// 
			this->primarySpikeLengthInput->DecimalPlaces = 2;
			this->primarySpikeLengthInput->Enabled = false;
			this->primarySpikeLengthInput->Location = System::Drawing::Point(210, 200);
			this->primarySpikeLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->primarySpikeLengthInput->Name = L"primarySpikeLengthInput";
			this->primarySpikeLengthInput->Size = System::Drawing::Size(64, 20);
			this->primarySpikeLengthInput->TabIndex = 15;
			this->primarySpikeLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(69, 202);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(135, 13);
			this->label12->TabIndex = 14;
			this->label12->Text = L"Äëèíà ïåðâè÷íûõ øèïîâ:";
			// 
			// bladeThicknessInput
			// 
			this->bladeThicknessInput->DecimalPlaces = 2;
			this->bladeThicknessInput->Enabled = false;
			this->bladeThicknessInput->Location = System::Drawing::Point(210, 174);
			this->bladeThicknessInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->bladeThicknessInput->Name = L"bladeThicknessInput";
			this->bladeThicknessInput->Size = System::Drawing::Size(64, 20);
			this->bladeThicknessInput->TabIndex = 13;
			this->bladeThicknessInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(109, 176);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(95, 13);
			this->label11->TabIndex = 12;
			this->label11->Text = L"Òîëùèíà ëåçâèÿ:";
			// 
			// bladeEdgesCountInput
			// 
			this->bladeEdgesCountInput->Enabled = false;
			this->bladeEdgesCountInput->Location = System::Drawing::Point(210, 148);
			this->bladeEdgesCountInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->bladeEdgesCountInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			this->bladeEdgesCountInput->Name = L"bladeEdgesCountInput";
			this->bladeEdgesCountInput->Size = System::Drawing::Size(64, 20);
			this->bladeEdgesCountInput->TabIndex = 11;
			this->bladeEdgesCountInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			this->bladeEdgesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(30, 150);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(174, 13);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Êîëè÷åñòâî îáðàçóþùèõ ëåçâèÿ:";
			// 
			// exBladeRadiusInput
			// 
			this->exBladeRadiusInput->DecimalPlaces = 2;
			this->exBladeRadiusInput->Enabled = false;
			this->exBladeRadiusInput->Location = System::Drawing::Point(210, 122);
			this->exBladeRadiusInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->exBladeRadiusInput->Name = L"exBladeRadiusInput";
			this->exBladeRadiusInput->Size = System::Drawing::Size(64, 20);
			this->exBladeRadiusInput->TabIndex = 9;
			this->exBladeRadiusInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(72, 124);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(132, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Âíåøíèé ðàäèóñ ëåçâèÿ:";
			// 
			// inBladeRadiusInput
			// 
			this->inBladeRadiusInput->DecimalPlaces = 2;
			this->inBladeRadiusInput->Enabled = false;
			this->inBladeRadiusInput->Location = System::Drawing::Point(210, 96);
			this->inBladeRadiusInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->inBladeRadiusInput->Name = L"inBladeRadiusInput";
			this->inBladeRadiusInput->Size = System::Drawing::Size(64, 20);
			this->inBladeRadiusInput->TabIndex = 7;
			this->inBladeRadiusInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(58, 98);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(146, 13);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Âíóòðåííèé ðàäèóñ ëåçâèÿ:";
			// 
			// handleEdgesCountInput
			// 
			this->handleEdgesCountInput->Enabled = false;
			this->handleEdgesCountInput->Location = System::Drawing::Point(210, 70);
			this->handleEdgesCountInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->handleEdgesCountInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->handleEdgesCountInput->Name = L"handleEdgesCountInput";
			this->handleEdgesCountInput->Size = System::Drawing::Size(64, 20);
			this->handleEdgesCountInput->TabIndex = 5;
			this->handleEdgesCountInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->handleEdgesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(26, 72);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(178, 13);
			this->label7->TabIndex = 4;
			this->label7->Text = L"Êîëè÷åñòâî îáðàçóþùèõ ðóêîÿòè:";
			// 
			// handleRingsCountInput
			// 
			this->handleRingsCountInput->Enabled = false;
			this->handleRingsCountInput->Location = System::Drawing::Point(210, 44);
			this->handleRingsCountInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->handleRingsCountInput->Name = L"handleRingsCountInput";
			this->handleRingsCountInput->Size = System::Drawing::Size(64, 20);
			this->handleRingsCountInput->TabIndex = 3;
			this->handleRingsCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(11, 46);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(193, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Êîëè÷åñòâî êîëåö íà êîíöå ðóêîÿòè:";
			// 
			// handleLengthInput
			// 
			this->handleLengthInput->DecimalPlaces = 2;
			this->handleLengthInput->Enabled = false;
			this->handleLengthInput->Location = System::Drawing::Point(210, 18);
			this->handleLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->handleLengthInput->Name = L"handleLengthInput";
			this->handleLengthInput->Size = System::Drawing::Size(64, 20);
			this->handleLengthInput->TabIndex = 1;
			this->handleLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(118, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Äëèíà ðóêîÿòè:";
			// 
			// objTransformGroup
			// 
			this->objTransformGroup->Controls->Add(this->objScaleZ);
			this->objTransformGroup->Controls->Add(this->objScaleY);
			this->objTransformGroup->Controls->Add(this->objScaleX);
			this->objTransformGroup->Controls->Add(this->objRotZ);
			this->objTransformGroup->Controls->Add(this->objRotY);
			this->objTransformGroup->Controls->Add(this->objRotX);
			this->objTransformGroup->Controls->Add(this->objPosZ);
			this->objTransformGroup->Controls->Add(this->objPosY);
			this->objTransformGroup->Controls->Add(this->objPosX);
			this->objTransformGroup->Controls->Add(this->label4);
			this->objTransformGroup->Controls->Add(this->label3);
			this->objTransformGroup->Controls->Add(this->label2);
			this->objTransformGroup->Location = System::Drawing::Point(8, 179);
			this->objTransformGroup->Name = L"objTransformGroup";
			this->objTransformGroup->Size = System::Drawing::Size(280, 102);
			this->objTransformGroup->TabIndex = 6;
			this->objTransformGroup->TabStop = false;
			this->objTransformGroup->Text = L"Ïðåîáðàçîâàíèÿ (âûáåðèòå îáúåêò)";
			// 
			// objScaleZ
			// 
			this->objScaleZ->DecimalPlaces = 2;
			this->objScaleZ->Enabled = false;
			this->objScaleZ->Location = System::Drawing::Point(210, 75);
			this->objScaleZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->objScaleZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, System::Int32::MinValue });
			this->objScaleZ->Name = L"objScaleZ";
			this->objScaleZ->Size = System::Drawing::Size(64, 20);
			this->objScaleZ->TabIndex = 20;
			this->objScaleZ->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->objScaleZ->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objScaleZ->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objScaleY
			// 
			this->objScaleY->DecimalPlaces = 2;
			this->objScaleY->Enabled = false;
			this->objScaleY->Location = System::Drawing::Point(139, 75);
			this->objScaleY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->objScaleY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, System::Int32::MinValue });
			this->objScaleY->Name = L"objScaleY";
			this->objScaleY->Size = System::Drawing::Size(64, 20);
			this->objScaleY->TabIndex = 19;
			this->objScaleY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->objScaleY->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objScaleY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objScaleX
			// 
			this->objScaleX->DecimalPlaces = 2;
			this->objScaleX->Enabled = false;
			this->objScaleX->Location = System::Drawing::Point(68, 75);
			this->objScaleX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->objScaleX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, System::Int32::MinValue });
			this->objScaleX->Name = L"objScaleX";
			this->objScaleX->Size = System::Drawing::Size(64, 20);
			this->objScaleX->TabIndex = 18;
			this->objScaleX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->objScaleX->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objScaleX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objRotZ
			// 
			this->objRotZ->DecimalPlaces = 2;
			this->objRotZ->Enabled = false;
			this->objRotZ->Location = System::Drawing::Point(210, 49);
			this->objRotZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 359, 0, 0, 0 });
			this->objRotZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->objRotZ->Name = L"objRotZ";
			this->objRotZ->Size = System::Drawing::Size(64, 20);
			this->objRotZ->TabIndex = 17;
			this->objRotZ->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objRotZ->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objRotY
			// 
			this->objRotY->DecimalPlaces = 2;
			this->objRotY->Enabled = false;
			this->objRotY->Location = System::Drawing::Point(139, 49);
			this->objRotY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 359, 0, 0, 0 });
			this->objRotY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->objRotY->Name = L"objRotY";
			this->objRotY->Size = System::Drawing::Size(64, 20);
			this->objRotY->TabIndex = 16;
			this->objRotY->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objRotY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objRotX
			// 
			this->objRotX->DecimalPlaces = 2;
			this->objRotX->Enabled = false;
			this->objRotX->Location = System::Drawing::Point(68, 49);
			this->objRotX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 359, 0, 0, 0 });
			this->objRotX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->objRotX->Name = L"objRotX";
			this->objRotX->Size = System::Drawing::Size(64, 20);
			this->objRotX->TabIndex = 15;
			this->objRotX->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objRotX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objPosZ
			// 
			this->objPosZ->DecimalPlaces = 2;
			this->objPosZ->Enabled = false;
			this->objPosZ->Location = System::Drawing::Point(210, 23);
			this->objPosZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->objPosZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->objPosZ->Name = L"objPosZ";
			this->objPosZ->Size = System::Drawing::Size(64, 20);
			this->objPosZ->TabIndex = 14;
			this->objPosZ->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objPosZ->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objPosY
			// 
			this->objPosY->DecimalPlaces = 2;
			this->objPosY->Enabled = false;
			this->objPosY->Location = System::Drawing::Point(139, 23);
			this->objPosY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->objPosY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->objPosY->Name = L"objPosY";
			this->objPosY->Size = System::Drawing::Size(64, 20);
			this->objPosY->TabIndex = 13;
			this->objPosY->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objPosY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// objPosX
			// 
			this->objPosX->DecimalPlaces = 2;
			this->objPosX->Enabled = false;
			this->objPosX->Location = System::Drawing::Point(68, 23);
			this->objPosX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->objPosX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->objPosX->Name = L"objPosX";
			this->objPosX->Size = System::Drawing::Size(64, 20);
			this->objPosX->TabIndex = 12;
			this->objPosX->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjTransformationChanged);
			this->objPosX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::onObjTransformationKeyPress);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 77);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(56, 13);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Ìàñøòàá:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Ïîâîðîò:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Ïîçèöèÿ:";
			// 
			// clearObjBtn
			// 
			this->clearObjBtn->Location = System::Drawing::Point(198, 140);
			this->clearObjBtn->Name = L"clearObjBtn";
			this->clearObjBtn->Size = System::Drawing::Size(90, 23);
			this->clearObjBtn->TabIndex = 5;
			this->clearObjBtn->Text = L"Î÷èñòèòü";
			this->clearObjBtn->UseVisualStyleBackColor = true;
			this->clearObjBtn->Click += gcnew System::EventHandler(this, &MainForm::clearObjBtn_Click);
			// 
			// deleteObjBtn
			// 
			this->deleteObjBtn->Enabled = false;
			this->deleteObjBtn->Location = System::Drawing::Point(102, 140);
			this->deleteObjBtn->Name = L"deleteObjBtn";
			this->deleteObjBtn->Size = System::Drawing::Size(90, 23);
			this->deleteObjBtn->TabIndex = 4;
			this->deleteObjBtn->Text = L"Óäàëèòü";
			this->deleteObjBtn->UseVisualStyleBackColor = true;
			this->deleteObjBtn->Click += gcnew System::EventHandler(this, &MainForm::deleteObjBtn_Click);
			// 
			// createObjBtn
			// 
			this->createObjBtn->Location = System::Drawing::Point(6, 140);
			this->createObjBtn->Name = L"createObjBtn";
			this->createObjBtn->Size = System::Drawing::Size(90, 23);
			this->createObjBtn->TabIndex = 3;
			this->createObjBtn->Text = L"Ñîçäàòü";
			this->createObjBtn->UseVisualStyleBackColor = true;
			this->createObjBtn->Click += gcnew System::EventHandler(this, &MainForm::createObjBtn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ñïèñîê îáúåêòîâ:";
			// 
			// objectsListBox
			// 
			this->objectsListBox->FormattingEnabled = true;
			this->objectsListBox->Location = System::Drawing::Point(6, 25);
			this->objectsListBox->Name = L"objectsListBox";
			this->objectsListBox->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->objectsListBox->Size = System::Drawing::Size(282, 108);
			this->objectsListBox->TabIndex = 1;
			this->objectsListBox->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::objectsListBox_SelectedValueChanged);
			// 
			// canvas
			// 
			this->canvas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->canvas->Location = System::Drawing::Point(310, 24);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(954, 808);
			this->canvas->TabIndex = 5;
			this->canvas->TabStop = false;
			this->canvas->Resize += gcnew System::EventHandler(this, &MainForm::canvas_Resize);
			// 
			// cameraControllerPanel
			// 
			this->cameraControllerPanel->AutoScroll = true;
			this->cameraControllerPanel->Controls->Add(this->groupBox3);
			this->cameraControllerPanel->Controls->Add(this->groupBox2);
			this->cameraControllerPanel->Controls->Add(this->groupBox5);
			this->cameraControllerPanel->Controls->Add(this->groupBox1);
			this->cameraControllerPanel->Controls->Add(this->groupBox4);
			this->cameraControllerPanel->Location = System::Drawing::Point(296, 22);
			this->cameraControllerPanel->Name = L"cameraControllerPanel";
			this->cameraControllerPanel->Size = System::Drawing::Size(310, 740);
			this->cameraControllerPanel->TabIndex = 6;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->cameraLookAtBtn);
			this->groupBox3->Controls->Add(this->label24);
			this->groupBox3->Controls->Add(this->cameraLookAtCb);
			this->groupBox3->Location = System::Drawing::Point(8, 245);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(280, 96);
			this->groupBox3->TabIndex = 9;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Íàïðàâèòü íà îáúåêò";
			// 
			// cameraLookAtBtn
			// 
			this->cameraLookAtBtn->Enabled = false;
			this->cameraLookAtBtn->Location = System::Drawing::Point(6, 49);
			this->cameraLookAtBtn->Name = L"cameraLookAtBtn";
			this->cameraLookAtBtn->Size = System::Drawing::Size(268, 40);
			this->cameraLookAtBtn->TabIndex = 19;
			this->cameraLookAtBtn->Text = L"Ïðèìåíèòü";
			this->cameraLookAtBtn->UseVisualStyleBackColor = true;
			this->cameraLookAtBtn->Click += gcnew System::EventHandler(this, &MainForm::cameraLookAtBtn_Click);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(14, 25);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(48, 13);
			this->label24->TabIndex = 1;
			this->label24->Text = L"Îáúåêò:";
			// 
			// cameraLookAtCb
			// 
			this->cameraLookAtCb->FormattingEnabled = true;
			this->cameraLookAtCb->Location = System::Drawing::Point(68, 22);
			this->cameraLookAtCb->Name = L"cameraLookAtCb";
			this->cameraLookAtCb->Size = System::Drawing::Size(206, 21);
			this->cameraLookAtCb->TabIndex = 0;
			this->cameraLookAtCb->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::cameraLookAtCb_SelectedValueChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->placeCameraRelativeBtn);
			this->groupBox2->Controls->Add(this->cameraRelativePosZ);
			this->groupBox2->Controls->Add(this->cameraRelativePosY);
			this->groupBox2->Controls->Add(this->cameraRelativePosX);
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->label21);
			this->groupBox2->Controls->Add(this->placeCameraRelativeCb);
			this->groupBox2->Location = System::Drawing::Point(8, 117);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(280, 122);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Ðàñïîëîæèòü ïî îòíîøåíèþ ê îáúåêòó";
			// 
			// placeCameraRelativeBtn
			// 
			this->placeCameraRelativeBtn->Enabled = false;
			this->placeCameraRelativeBtn->Location = System::Drawing::Point(6, 75);
			this->placeCameraRelativeBtn->Name = L"placeCameraRelativeBtn";
			this->placeCameraRelativeBtn->Size = System::Drawing::Size(268, 40);
			this->placeCameraRelativeBtn->TabIndex = 19;
			this->placeCameraRelativeBtn->Text = L"Ïðèìåíèòü";
			this->placeCameraRelativeBtn->UseVisualStyleBackColor = true;
			this->placeCameraRelativeBtn->Click += gcnew System::EventHandler(this, &MainForm::placeCameraRelativeBtn_Click);
			// 
			// cameraRelativePosZ
			// 
			this->cameraRelativePosZ->DecimalPlaces = 2;
			this->cameraRelativePosZ->Enabled = false;
			this->cameraRelativePosZ->Location = System::Drawing::Point(210, 49);
			this->cameraRelativePosZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraRelativePosZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraRelativePosZ->Name = L"cameraRelativePosZ";
			this->cameraRelativePosZ->Size = System::Drawing::Size(64, 20);
			this->cameraRelativePosZ->TabIndex = 18;
			// 
			// cameraRelativePosY
			// 
			this->cameraRelativePosY->DecimalPlaces = 2;
			this->cameraRelativePosY->Enabled = false;
			this->cameraRelativePosY->Location = System::Drawing::Point(139, 49);
			this->cameraRelativePosY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraRelativePosY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraRelativePosY->Name = L"cameraRelativePosY";
			this->cameraRelativePosY->Size = System::Drawing::Size(64, 20);
			this->cameraRelativePosY->TabIndex = 17;
			// 
			// cameraRelativePosX
			// 
			this->cameraRelativePosX->DecimalPlaces = 2;
			this->cameraRelativePosX->Enabled = false;
			this->cameraRelativePosX->Location = System::Drawing::Point(68, 49);
			this->cameraRelativePosX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraRelativePosX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraRelativePosX->Name = L"cameraRelativePosX";
			this->cameraRelativePosX->Size = System::Drawing::Size(64, 20);
			this->cameraRelativePosX->TabIndex = 16;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(8, 51);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(54, 13);
			this->label22->TabIndex = 15;
			this->label22->Text = L"Ïîçèöèÿ:";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(14, 25);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(48, 13);
			this->label21->TabIndex = 1;
			this->label21->Text = L"Îáúåêò:";
			// 
			// placeCameraRelativeCb
			// 
			this->placeCameraRelativeCb->FormattingEnabled = true;
			this->placeCameraRelativeCb->Location = System::Drawing::Point(68, 22);
			this->placeCameraRelativeCb->Name = L"placeCameraRelativeCb";
			this->placeCameraRelativeCb->Size = System::Drawing::Size(206, 21);
			this->placeCameraRelativeCb->TabIndex = 0;
			this->placeCameraRelativeCb->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::placeCameraRelativeCb_SelectedValueChanged);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->fovLabel);
			this->groupBox5->Controls->Add(this->fovInput);
			this->groupBox5->Controls->Add(this->label26);
			this->groupBox5->Controls->Add(this->farPlaneInput);
			this->groupBox5->Controls->Add(this->nearPlaneInput);
			this->groupBox5->Controls->Add(this->label25);
			this->groupBox5->Controls->Add(this->label23);
			this->groupBox5->Location = System::Drawing::Point(8, 417);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(280, 134);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Ïèðàìèäà âèäèìîñòè";
			// 
			// fovLabel
			// 
			this->fovLabel->AutoSize = true;
			this->fovLabel->Location = System::Drawing::Point(87, 65);
			this->fovLabel->Name = L"fovLabel";
			this->fovLabel->Size = System::Drawing::Size(19, 13);
			this->fovLabel->TabIndex = 6;
			this->fovLabel->Text = L"40";
			// 
			// fovInput
			// 
			this->fovInput->Location = System::Drawing::Point(6, 82);
			this->fovInput->Maximum = 180;
			this->fovInput->Name = L"fovInput";
			this->fovInput->Size = System::Drawing::Size(268, 45);
			this->fovInput->TabIndex = 5;
			this->fovInput->TickFrequency = 10;
			this->fovInput->Value = 40;
			this->fovInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onFovInputValueChanged);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(6, 65);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(75, 13);
			this->label26->TabIndex = 4;
			this->label26->Text = L"Ïîëå çðåíèÿ:";
			// 
			// farPlaneInput
			// 
			this->farPlaneInput->DecimalPlaces = 2;
			this->farPlaneInput->Location = System::Drawing::Point(190, 41);
			this->farPlaneInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->farPlaneInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->farPlaneInput->Name = L"farPlaneInput";
			this->farPlaneInput->Size = System::Drawing::Size(64, 20);
			this->farPlaneInput->TabIndex = 3;
			this->farPlaneInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
			this->farPlaneInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onFrustumChanged);
			// 
			// nearPlaneInput
			// 
			this->nearPlaneInput->DecimalPlaces = 2;
			this->nearPlaneInput->Location = System::Drawing::Point(190, 17);
			this->nearPlaneInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->nearPlaneInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nearPlaneInput->Name = L"nearPlaneInput";
			this->nearPlaneInput->Size = System::Drawing::Size(64, 20);
			this->nearPlaneInput->TabIndex = 2;
			this->nearPlaneInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nearPlaneInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onFrustumChanged);
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(6, 43);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(178, 13);
			this->label25->TabIndex = 1;
			this->label25->Text = L"Äàëüíÿÿ îòñåêàþùàÿ ïëîñêîñòü:";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(6, 19);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(178, 13);
			this->label23->TabIndex = 0;
			this->label23->Text = L"Áëèæíÿÿ îòñåêàþùàÿ ïëîñêîñòü:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->cameraRoll);
			this->groupBox1->Controls->Add(this->cameraPitch);
			this->groupBox1->Controls->Add(this->cameraYaw);
			this->groupBox1->Controls->Add(this->cameraTargetZ);
			this->groupBox1->Controls->Add(this->cameraTargetY);
			this->groupBox1->Controls->Add(this->cameraTargetX);
			this->groupBox1->Controls->Add(this->cameraPosZ);
			this->groupBox1->Controls->Add(this->cameraPosY);
			this->groupBox1->Controls->Add(this->cameraPosX);
			this->groupBox1->Controls->Add(this->label18);
			this->groupBox1->Controls->Add(this->label19);
			this->groupBox1->Controls->Add(this->label20);
			this->groupBox1->Location = System::Drawing::Point(8, 9);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(280, 102);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ïîëîæåíèå êàìåðû";
			// 
			// cameraRoll
			// 
			this->cameraRoll->DecimalPlaces = 2;
			this->cameraRoll->Location = System::Drawing::Point(210, 75);
			this->cameraRoll->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 359, 0, 0, 0 });
			this->cameraRoll->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->cameraRoll->Name = L"cameraRoll";
			this->cameraRoll->Size = System::Drawing::Size(64, 20);
			this->cameraRoll->TabIndex = 20;
			this->cameraRoll->Visible = false;
			this->cameraRoll->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraPitch
			// 
			this->cameraPitch->DecimalPlaces = 2;
			this->cameraPitch->Location = System::Drawing::Point(139, 75);
			this->cameraPitch->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8999999, 0, 0, 327680 });
			this->cameraPitch->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8999999, 0, 0, -2147155968 });
			this->cameraPitch->Name = L"cameraPitch";
			this->cameraPitch->Size = System::Drawing::Size(64, 20);
			this->cameraPitch->TabIndex = 19;
			this->cameraPitch->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraYaw
			// 
			this->cameraYaw->DecimalPlaces = 2;
			this->cameraYaw->Location = System::Drawing::Point(68, 75);
			this->cameraYaw->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 359, 0, 0, 0 });
			this->cameraYaw->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->cameraYaw->Name = L"cameraYaw";
			this->cameraYaw->Size = System::Drawing::Size(64, 20);
			this->cameraYaw->TabIndex = 18;
			this->cameraYaw->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraTargetZ
			// 
			this->cameraTargetZ->DecimalPlaces = 2;
			this->cameraTargetZ->Location = System::Drawing::Point(210, 49);
			this->cameraTargetZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraTargetZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraTargetZ->Name = L"cameraTargetZ";
			this->cameraTargetZ->Size = System::Drawing::Size(64, 20);
			this->cameraTargetZ->TabIndex = 17;
			this->cameraTargetZ->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraTargetY
			// 
			this->cameraTargetY->DecimalPlaces = 2;
			this->cameraTargetY->Location = System::Drawing::Point(139, 49);
			this->cameraTargetY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraTargetY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraTargetY->Name = L"cameraTargetY";
			this->cameraTargetY->Size = System::Drawing::Size(64, 20);
			this->cameraTargetY->TabIndex = 16;
			this->cameraTargetY->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraTargetX
			// 
			this->cameraTargetX->DecimalPlaces = 2;
			this->cameraTargetX->Location = System::Drawing::Point(68, 49);
			this->cameraTargetX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraTargetX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraTargetX->Name = L"cameraTargetX";
			this->cameraTargetX->Size = System::Drawing::Size(64, 20);
			this->cameraTargetX->TabIndex = 15;
			this->cameraTargetX->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraPosZ
			// 
			this->cameraPosZ->DecimalPlaces = 2;
			this->cameraPosZ->Location = System::Drawing::Point(210, 23);
			this->cameraPosZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraPosZ->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraPosZ->Name = L"cameraPosZ";
			this->cameraPosZ->Size = System::Drawing::Size(64, 20);
			this->cameraPosZ->TabIndex = 14;
			this->cameraPosZ->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->cameraPosZ->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraPosY
			// 
			this->cameraPosY->DecimalPlaces = 2;
			this->cameraPosY->Location = System::Drawing::Point(139, 23);
			this->cameraPosY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraPosY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraPosY->Name = L"cameraPosY";
			this->cameraPosY->Size = System::Drawing::Size(64, 20);
			this->cameraPosY->TabIndex = 13;
			this->cameraPosY->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// cameraPosX
			// 
			this->cameraPosX->DecimalPlaces = 2;
			this->cameraPosX->Location = System::Drawing::Point(68, 23);
			this->cameraPosX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, 0 });
			this->cameraPosX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99999, 0, 0, System::Int32::MinValue });
			this->cameraPosX->Name = L"cameraPosX";
			this->cameraPosX->Size = System::Drawing::Size(64, 20);
			this->cameraPosX->TabIndex = 12;
			this->cameraPosX->ValueChanged += gcnew System::EventHandler(this, &MainForm::onCameraTransformationChanged);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(9, 77);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(53, 13);
			this->label18->TabIndex = 2;
			this->label18->Text = L"Ïîâîðîò:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(26, 51);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(36, 13);
			this->label19->TabIndex = 1;
			this->label19->Text = L"Öåëü:";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(8, 25);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(54, 13);
			this->label20->TabIndex = 0;
			this->label20->Text = L"Ïîçèöèÿ:";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->cProjectionRb);
			this->groupBox4->Controls->Add(this->pProjectionRb);
			this->groupBox4->Location = System::Drawing::Point(8, 347);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(280, 64);
			this->groupBox4->TabIndex = 0;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Âèä ïðîåöèðîâàíèÿ";
			// 
			// cProjectionRb
			// 
			this->cProjectionRb->AutoSize = true;
			this->cProjectionRb->Location = System::Drawing::Point(6, 42);
			this->cProjectionRb->Name = L"cProjectionRb";
			this->cProjectionRb->Size = System::Drawing::Size(90, 17);
			this->cProjectionRb->TabIndex = 1;
			this->cProjectionRb->Text = L"öåíòðàëüíîå";
			this->cProjectionRb->UseVisualStyleBackColor = true;
			this->cProjectionRb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onProjectionTypeChanged);
			// 
			// pProjectionRb
			// 
			this->pProjectionRb->AutoSize = true;
			this->pProjectionRb->Checked = true;
			this->pProjectionRb->Location = System::Drawing::Point(6, 19);
			this->pProjectionRb->Name = L"pProjectionRb";
			this->pProjectionRb->Size = System::Drawing::Size(97, 17);
			this->pProjectionRb->TabIndex = 0;
			this->pProjectionRb->TabStop = true;
			this->pProjectionRb->Text = L"ïàðàëëåëüíîå";
			this->pProjectionRb->UseVisualStyleBackColor = true;
			this->pProjectionRb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onProjectionTypeChanged);
			// 
			// renderControllerPanel
			// 
			this->renderControllerPanel->AutoScroll = true;
			this->renderControllerPanel->Controls->Add(this->groupBox7);
			this->renderControllerPanel->Controls->Add(this->groupBox6);
			this->renderControllerPanel->Location = System::Drawing::Point(0, 51);
			this->renderControllerPanel->Name = L"renderControllerPanel";
			this->renderControllerPanel->Size = System::Drawing::Size(310, 740);
			this->renderControllerPanel->TabIndex = 7;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->edgesColorBtn);
			this->groupBox7->Controls->Add(this->label28);
			this->groupBox7->Controls->Add(this->sceneBgColorBtn);
			this->groupBox7->Controls->Add(this->label27);
			this->groupBox7->Location = System::Drawing::Point(8, 124);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(280, 79);
			this->groupBox7->TabIndex = 3;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Ïàëèòðà ñöåíû";
			// 
			// edgesColorBtn
			// 
			this->edgesColorBtn->BackColor = System::Drawing::Color::White;
			this->edgesColorBtn->Location = System::Drawing::Point(49, 48);
			this->edgesColorBtn->Name = L"edgesColorBtn";
			this->edgesColorBtn->Size = System::Drawing::Size(75, 23);
			this->edgesColorBtn->TabIndex = 10;
			this->edgesColorBtn->UseVisualStyleBackColor = false;
			this->edgesColorBtn->Click += gcnew System::EventHandler(this, &MainForm::onPaletteBtnClicked);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(6, 53);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(41, 13);
			this->label28->TabIndex = 9;
			this->label28->Text = L"Ð¸áðà:";
			// 
			// sceneBgColorBtn
			// 
			this->sceneBgColorBtn->BackColor = System::Drawing::Color::Black;
			this->sceneBgColorBtn->Location = System::Drawing::Point(49, 19);
			this->sceneBgColorBtn->Name = L"sceneBgColorBtn";
			this->sceneBgColorBtn->Size = System::Drawing::Size(75, 23);
			this->sceneBgColorBtn->TabIndex = 8;
			this->sceneBgColorBtn->UseVisualStyleBackColor = false;
			this->sceneBgColorBtn->Click += gcnew System::EventHandler(this, &MainForm::onPaletteBtnClicked);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(10, 24);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(33, 13);
			this->label27->TabIndex = 7;
			this->label27->Text = L"Ôîí:";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->simulateLightChb);
			this->groupBox6->Controls->Add(this->useRandomPaletteChb);
			this->groupBox6->Controls->Add(this->drawFillChb);
			this->groupBox6->Controls->Add(this->drawEdgesChb);
			this->groupBox6->Location = System::Drawing::Point(8, 9);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(280, 109);
			this->groupBox6->TabIndex = 2;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Ñïîñîá ðèñîâàíèÿ";
			// 
			// simulateLightChb
			// 
			this->simulateLightChb->AutoSize = true;
			this->simulateLightChb->Checked = true;
			this->simulateLightChb->CheckState = System::Windows::Forms::CheckState::Checked;
			this->simulateLightChb->Location = System::Drawing::Point(6, 88);
			this->simulateLightChb->Name = L"simulateLightChb";
			this->simulateLightChb->Size = System::Drawing::Size(159, 17);
			this->simulateLightChb->TabIndex = 3;
			this->simulateLightChb->Text = L"Ñèìóëèðîâàòü îñâåùåíèå";
			this->simulateLightChb->UseVisualStyleBackColor = true;
			this->simulateLightChb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onDrawMethodChanged);
			// 
			// useRandomPaletteChb
			// 
			this->useRandomPaletteChb->AutoSize = true;
			this->useRandomPaletteChb->Location = System::Drawing::Point(6, 65);
			this->useRandomPaletteChb->Name = L"useRandomPaletteChb";
			this->useRandomPaletteChb->Size = System::Drawing::Size(185, 17);
			this->useRandomPaletteChb->TabIndex = 2;
			this->useRandomPaletteChb->Text = L"Çàëèâàòü ñëó÷àéíûìè öâåòàìè";
			this->useRandomPaletteChb->UseVisualStyleBackColor = true;
			this->useRandomPaletteChb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onDrawMethodChanged);
			// 
			// drawFillChb
			// 
			this->drawFillChb->AutoSize = true;
			this->drawFillChb->Checked = true;
			this->drawFillChb->CheckState = System::Windows::Forms::CheckState::Checked;
			this->drawFillChb->ForeColor = System::Drawing::SystemColors::ControlText;
			this->drawFillChb->Location = System::Drawing::Point(6, 42);
			this->drawFillChb->Name = L"drawFillChb";
			this->drawFillChb->Size = System::Drawing::Size(118, 17);
			this->drawFillChb->TabIndex = 1;
			this->drawFillChb->Text = L"Ðèñîâàòü çàëèâêó";
			this->drawFillChb->UseVisualStyleBackColor = true;
			this->drawFillChb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onDrawMethodChanged);
			// 
			// drawEdgesChb
			// 
			this->drawEdgesChb->AutoSize = true;
			this->drawEdgesChb->Location = System::Drawing::Point(6, 19);
			this->drawEdgesChb->Name = L"drawEdgesChb";
			this->drawEdgesChb->Size = System::Drawing::Size(107, 17);
			this->drawEdgesChb->TabIndex = 0;
			this->drawEdgesChb->Text = L"Ðèñîâàòü ð¸áðà";
			this->drawEdgesChb->UseVisualStyleBackColor = true;
			this->drawEdgesChb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::onDrawMethodChanged);
			// 
			// controllersPanel
			// 
			this->controllersPanel->Controls->Add(this->cameraControllerPanel);
			this->controllersPanel->Controls->Add(this->renderControllerPanel);
			this->controllersPanel->Controls->Add(this->objControllerPanel);
			this->controllersPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->controllersPanel->Location = System::Drawing::Point(0, 24);
			this->controllersPanel->Name = L"controllersPanel";
			this->controllersPanel->Size = System::Drawing::Size(310, 808);
			this->controllersPanel->TabIndex = 8;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 832);
			this->Controls->Add(this->canvas);
			this->Controls->Add(this->controllersPanel);
			this->Controls->Add(this->menuStrip);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->Text = L"Bladestick";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->objControllerPanel->ResumeLayout(false);
			this->objControllerPanel->PerformLayout();
			this->objParamsGroup->ResumeLayout(false);
			this->objParamsGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikesCountInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikeAngleInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->primarySpikeAngleInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondarySpikeLengthInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->primarySpikeLengthInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bladeThicknessInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bladeEdgesCountInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->exBladeRadiusInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inBladeRadiusInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleEdgesCountInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleRingsCountInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->handleLengthInput))->EndInit();
			this->objTransformGroup->ResumeLayout(false);
			this->objTransformGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objScaleX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objRotX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->objPosX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->EndInit();
			this->cameraControllerPanel->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRelativePosX))->EndInit();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fovInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->farPlaneInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nearPlaneInput))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraRoll))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPitch))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraYaw))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraTargetX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cameraPosX))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->renderControllerPanel->ResumeLayout(false);
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->controllersPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}
