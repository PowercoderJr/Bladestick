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
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		System::Drawing::Graphics ^ g;
		System::ComponentModel::BackgroundWorker ^ backgroundWorker1;
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::Panel^  objPanel;
		System::Windows::Forms::Button^  clearObjBtn;
		System::Windows::Forms::Button^  deleteObjBtn;
		System::Windows::Forms::Button^  createObjBtn;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::ListBox^  objectsListBox;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::PictureBox^  canvas;
		System::Windows::Forms::GroupBox^  groupBox1;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label4;
		System::Windows::Forms::GroupBox^  groupBox2;
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
		System::Windows::Forms::ColorDialog^  colorDialog1;
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
		Drawing::Scene ^ scene;
		array<Control ^> ^ selectionDependedControls;
		bool autoApplyTransform;

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
		void redrawScene();
		void applyObjTransform(Object ^ sender);
		void applyObjParams();
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

	public:
		MainForm(void)
		{
			InitializeComponent();
			scene = gcnew Drawing::Scene();
			objectsListBox->DataSource = scene->objects;
			g = canvas->CreateGraphics();
			autoApplyTransform = true;
			selectionDependedControls = gcnew array<Control ^>(27)
			{
				deleteObjBtn, objPosX, objPosY, objPosZ,
					objRotX, objRotY, objRotZ,
					objScaleX, objScaleY, objScaleZ,
					color1Btn, color2Btn, color3Btn,
					handleLengthInput,
					handleRingsCountInput,
					handleEdgesCountInput,
					inBladeRadiusInput,
					exBladeRadiusInput,
					bladeThicknessInput,
					bladeEdgesCountInput,
					primarySpikeLengthInput,
					primarySpikeAngleInput,
					secondarySpikeLengthInput,
					secondarySpikeAngleInput,
					secondarySpikesCountInput,
					applyParamsBtn,
					setDefaultParamsBtn
			};
			setDefaultParamsBtn_Click(this, nullptr);

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->objPanel = (gcnew System::Windows::Forms::Panel());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
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
			this->button1 = (gcnew System::Windows::Forms::Button());
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
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
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->objPanel->SuspendLayout();
			this->groupBox2->SuspendLayout();
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
			this->groupBox1->SuspendLayout();
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
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1264, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// objPanel
			// 
			this->objPanel->AutoScroll = true;
			this->objPanel->Controls->Add(this->groupBox2);
			this->objPanel->Controls->Add(this->groupBox1);
			this->objPanel->Controls->Add(this->clearObjBtn);
			this->objPanel->Controls->Add(this->deleteObjBtn);
			this->objPanel->Controls->Add(this->createObjBtn);
			this->objPanel->Controls->Add(this->label1);
			this->objPanel->Controls->Add(this->objectsListBox);
			this->objPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->objPanel->Location = System::Drawing::Point(0, 24);
			this->objPanel->Name = L"objPanel";
			this->objPanel->Size = System::Drawing::Size(310, 740);
			this->objPanel->TabIndex = 4;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->autoApplyParamsChb);
			this->groupBox2->Controls->Add(this->setDefaultParamsBtn);
			this->groupBox2->Controls->Add(this->secondarySpikesCountLabel);
			this->groupBox2->Controls->Add(this->applyParamsBtn);
			this->groupBox2->Controls->Add(this->color3Btn);
			this->groupBox2->Controls->Add(this->color2Btn);
			this->groupBox2->Controls->Add(this->color1Btn);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->secondarySpikesCountInput);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->secondarySpikeAngleInput);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->primarySpikeAngleInput);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->secondarySpikeLengthInput);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->primarySpikeLengthInput);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->bladeThicknessInput);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->bladeEdgesCountInput);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->exBladeRadiusInput);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->inBladeRadiusInput);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->handleEdgesCountInput);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->handleRingsCountInput);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->handleLengthInput);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Location = System::Drawing::Point(7, 286);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(281, 450);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Параметры";
			// 
			// autoApplyParamsChb
			// 
			this->autoApplyParamsChb->Appearance = System::Windows::Forms::Appearance::Button;
			this->autoApplyParamsChb->Checked = true;
			this->autoApplyParamsChb->CheckState = System::Windows::Forms::CheckState::Checked;
			this->autoApplyParamsChb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7));
			this->autoApplyParamsChb->Location = System::Drawing::Point(5, 402);
			this->autoApplyParamsChb->Name = L"autoApplyParamsChb";
			this->autoApplyParamsChb->Size = System::Drawing::Size(90, 40);
			this->autoApplyParamsChb->TabIndex = 28;
			this->autoApplyParamsChb->Text = L"Применять автоматически";
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
			this->setDefaultParamsBtn->Text = L"Заполнить по умолчанию";
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
			this->applyParamsBtn->Text = L"Применить";
			this->applyParamsBtn->UseVisualStyleBackColor = true;
			this->applyParamsBtn->Click += gcnew System::EventHandler(this, &MainForm::applyBtn_Click);
			// 
			// color3Btn
			// 
			this->color3Btn->BackColor = System::Drawing::Color::White;
			this->color3Btn->Enabled = false;
			this->color3Btn->Location = System::Drawing::Point(208, 365);
			this->color3Btn->Name = L"color3Btn";
			this->color3Btn->Size = System::Drawing::Size(67, 23);
			this->color3Btn->TabIndex = 27;
			this->color3Btn->UseVisualStyleBackColor = false;
			this->color3Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			this->color3Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// color2Btn
			// 
			this->color2Btn->BackColor = System::Drawing::Color::White;
			this->color2Btn->Enabled = false;
			this->color2Btn->Location = System::Drawing::Point(136, 365);
			this->color2Btn->Name = L"color2Btn";
			this->color2Btn->Size = System::Drawing::Size(67, 23);
			this->color2Btn->TabIndex = 26;
			this->color2Btn->UseVisualStyleBackColor = false;
			this->color2Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			this->color2Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// color1Btn
			// 
			this->color1Btn->BackColor = System::Drawing::Color::White;
			this->color1Btn->Enabled = false;
			this->color1Btn->Location = System::Drawing::Point(64, 365);
			this->color1Btn->Name = L"color1Btn";
			this->color1Btn->Size = System::Drawing::Size(67, 23);
			this->color1Btn->TabIndex = 25;
			this->color1Btn->UseVisualStyleBackColor = false;
			this->color1Btn->Click += gcnew System::EventHandler(this, &MainForm::colorBtn_Click);
			this->color1Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(5, 370);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(53, 13);
			this->label17->TabIndex = 24;
			this->label17->Text = L"Палитра:";
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
			this->secondarySpikesCountInput->TickFrequency = 4;
			this->secondarySpikesCountInput->Value = 1;
			this->secondarySpikesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::secondarySpikesCountInput_ValueChanged);
			this->secondarySpikesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 306);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(160, 13);
			this->label16->TabIndex = 22;
			this->label16->Text = L"Количество вторичных шипов:";
			// 
			// secondarySpikeAngleInput
			// 
			this->secondarySpikeAngleInput->DecimalPlaces = 2;
			this->secondarySpikeAngleInput->Enabled = false;
			this->secondarySpikeAngleInput->Location = System::Drawing::Point(211, 278);
			this->secondarySpikeAngleInput->Name = L"secondarySpikeAngleInput";
			this->secondarySpikeAngleInput->Size = System::Drawing::Size(64, 20);
			this->secondarySpikeAngleInput->TabIndex = 21;
			this->secondarySpikeAngleInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(79, 280);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(126, 13);
			this->label14->TabIndex = 20;
			this->label14->Text = L"Угол вторичных шипов:";
			// 
			// primarySpikeAngleInput
			// 
			this->primarySpikeAngleInput->DecimalPlaces = 2;
			this->primarySpikeAngleInput->Enabled = false;
			this->primarySpikeAngleInput->Location = System::Drawing::Point(211, 226);
			this->primarySpikeAngleInput->Name = L"primarySpikeAngleInput";
			this->primarySpikeAngleInput->Size = System::Drawing::Size(64, 20);
			this->primarySpikeAngleInput->TabIndex = 19;
			this->primarySpikeAngleInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(78, 228);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(127, 13);
			this->label15->TabIndex = 18;
			this->label15->Text = L"Угол первичных шипов:";
			// 
			// secondarySpikeLengthInput
			// 
			this->secondarySpikeLengthInput->DecimalPlaces = 2;
			this->secondarySpikeLengthInput->Enabled = false;
			this->secondarySpikeLengthInput->Location = System::Drawing::Point(211, 252);
			this->secondarySpikeLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->secondarySpikeLengthInput->Name = L"secondarySpikeLengthInput";
			this->secondarySpikeLengthInput->Size = System::Drawing::Size(64, 20);
			this->secondarySpikeLengthInput->TabIndex = 17;
			this->secondarySpikeLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(200, -11);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"TEST";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(71, 254);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(134, 13);
			this->label13->TabIndex = 16;
			this->label13->Text = L"Длина вторичных шипов:";
			// 
			// primarySpikeLengthInput
			// 
			this->primarySpikeLengthInput->DecimalPlaces = 2;
			this->primarySpikeLengthInput->Enabled = false;
			this->primarySpikeLengthInput->Location = System::Drawing::Point(211, 200);
			this->primarySpikeLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->primarySpikeLengthInput->Name = L"primarySpikeLengthInput";
			this->primarySpikeLengthInput->Size = System::Drawing::Size(64, 20);
			this->primarySpikeLengthInput->TabIndex = 15;
			this->primarySpikeLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(70, 202);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(135, 13);
			this->label12->TabIndex = 14;
			this->label12->Text = L"Длина первичных шипов:";
			// 
			// bladeThicknessInput
			// 
			this->bladeThicknessInput->DecimalPlaces = 2;
			this->bladeThicknessInput->Enabled = false;
			this->bladeThicknessInput->Location = System::Drawing::Point(211, 174);
			this->bladeThicknessInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->bladeThicknessInput->Name = L"bladeThicknessInput";
			this->bladeThicknessInput->Size = System::Drawing::Size(64, 20);
			this->bladeThicknessInput->TabIndex = 13;
			this->bladeThicknessInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(110, 176);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(95, 13);
			this->label11->TabIndex = 12;
			this->label11->Text = L"Толщина лезвия:";
			// 
			// bladeEdgesCountInput
			// 
			this->bladeEdgesCountInput->Enabled = false;
			this->bladeEdgesCountInput->Location = System::Drawing::Point(211, 148);
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
			this->label10->Location = System::Drawing::Point(31, 150);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(174, 13);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Количество образующих лезвия:";
			// 
			// exBladeRadiusInput
			// 
			this->exBladeRadiusInput->DecimalPlaces = 2;
			this->exBladeRadiusInput->Enabled = false;
			this->exBladeRadiusInput->Location = System::Drawing::Point(211, 122);
			this->exBladeRadiusInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->exBladeRadiusInput->Name = L"exBladeRadiusInput";
			this->exBladeRadiusInput->Size = System::Drawing::Size(64, 20);
			this->exBladeRadiusInput->TabIndex = 9;
			this->exBladeRadiusInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(73, 124);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(132, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Внешний радиус лезвия:";
			// 
			// inBladeRadiusInput
			// 
			this->inBladeRadiusInput->DecimalPlaces = 2;
			this->inBladeRadiusInput->Enabled = false;
			this->inBladeRadiusInput->Location = System::Drawing::Point(211, 96);
			this->inBladeRadiusInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->inBladeRadiusInput->Name = L"inBladeRadiusInput";
			this->inBladeRadiusInput->Size = System::Drawing::Size(64, 20);
			this->inBladeRadiusInput->TabIndex = 7;
			this->inBladeRadiusInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(59, 98);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(146, 13);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Внутренний радиус лезвия:";
			// 
			// handleEdgesCountInput
			// 
			this->handleEdgesCountInput->Enabled = false;
			this->handleEdgesCountInput->Location = System::Drawing::Point(211, 70);
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
			this->label7->Location = System::Drawing::Point(27, 72);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(178, 13);
			this->label7->TabIndex = 4;
			this->label7->Text = L"Количество образующих рукояти:";
			// 
			// handleRingsCountInput
			// 
			this->handleRingsCountInput->Enabled = false;
			this->handleRingsCountInput->Location = System::Drawing::Point(211, 44);
			this->handleRingsCountInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->handleRingsCountInput->Name = L"handleRingsCountInput";
			this->handleRingsCountInput->Size = System::Drawing::Size(64, 20);
			this->handleRingsCountInput->TabIndex = 3;
			this->handleRingsCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 46);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(193, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Количество колец на конце рукояти:";
			// 
			// handleLengthInput
			// 
			this->handleLengthInput->DecimalPlaces = 2;
			this->handleLengthInput->Enabled = false;
			this->handleLengthInput->Location = System::Drawing::Point(211, 18);
			this->handleLengthInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->handleLengthInput->Name = L"handleLengthInput";
			this->handleLengthInput->Size = System::Drawing::Size(64, 20);
			this->handleLengthInput->TabIndex = 1;
			this->handleLengthInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(119, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Длина рукояти:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->objScaleZ);
			this->groupBox1->Controls->Add(this->objScaleY);
			this->groupBox1->Controls->Add(this->objScaleX);
			this->groupBox1->Controls->Add(this->objRotZ);
			this->groupBox1->Controls->Add(this->objRotY);
			this->groupBox1->Controls->Add(this->objRotX);
			this->groupBox1->Controls->Add(this->objPosZ);
			this->groupBox1->Controls->Add(this->objPosY);
			this->groupBox1->Controls->Add(this->objPosX);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(6, 179);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(282, 100);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Преобразования";
			// 
			// objScaleZ
			// 
			this->objScaleZ->DecimalPlaces = 2;
			this->objScaleZ->Enabled = false;
			this->objScaleZ->Location = System::Drawing::Point(212, 71);
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
			this->objScaleY->Location = System::Drawing::Point(140, 71);
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
			this->objScaleX->Location = System::Drawing::Point(68, 71);
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
			this->objRotZ->Location = System::Drawing::Point(212, 46);
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
			this->objRotY->Location = System::Drawing::Point(140, 46);
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
			this->objRotX->Location = System::Drawing::Point(68, 46);
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
			this->objPosZ->Location = System::Drawing::Point(212, 23);
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
			this->objPosY->Location = System::Drawing::Point(140, 23);
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
			this->label4->Location = System::Drawing::Point(6, 73);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(56, 13);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Масштаб:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 48);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Поворот:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Позиция:";
			// 
			// clearObjBtn
			// 
			this->clearObjBtn->Location = System::Drawing::Point(198, 140);
			this->clearObjBtn->Name = L"clearObjBtn";
			this->clearObjBtn->Size = System::Drawing::Size(90, 23);
			this->clearObjBtn->TabIndex = 5;
			this->clearObjBtn->Text = L"Очистить";
			this->clearObjBtn->UseVisualStyleBackColor = true;
			this->clearObjBtn->Click += gcnew System::EventHandler(this, &MainForm::clearObjBtn_Click);
			// 
			// deleteObjBtn
			// 
			this->deleteObjBtn->Location = System::Drawing::Point(102, 140);
			this->deleteObjBtn->Name = L"deleteObjBtn";
			this->deleteObjBtn->Size = System::Drawing::Size(90, 23);
			this->deleteObjBtn->TabIndex = 4;
			this->deleteObjBtn->Text = L"Удалить";
			this->deleteObjBtn->UseVisualStyleBackColor = true;
			this->deleteObjBtn->Click += gcnew System::EventHandler(this, &MainForm::deleteObjBtn_Click);
			// 
			// createObjBtn
			// 
			this->createObjBtn->Location = System::Drawing::Point(6, 140);
			this->createObjBtn->Name = L"createObjBtn";
			this->createObjBtn->Size = System::Drawing::Size(90, 23);
			this->createObjBtn->TabIndex = 3;
			this->createObjBtn->Text = L"Создать";
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
			this->label1->Text = L"Список объектов:";
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
			this->canvas->Size = System::Drawing::Size(954, 740);
			this->canvas->TabIndex = 5;
			this->canvas->TabStop = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 764);
			this->Controls->Add(this->canvas);
			this->Controls->Add(this->objPanel);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->objPanel->ResumeLayout(false);
			this->objPanel->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
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
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void onObjTransformationKeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
};
}
