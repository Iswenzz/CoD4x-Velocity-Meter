#pragma once
#include <Windows.h>
#include <tlhelp32.h>

namespace COD4 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Threading;

	/// <summary>
	/// Summary for UI
	/// </summary>
	public ref class UI : public System::Windows::Forms::Form
	{
		public:
			property Color AppBackColor;
			property Color AppForeColor;
			property float Velocity;

			/// <summary>
			/// Initialize a new <see cref="UI"/> form instance.
			/// </summary>
			UI();

		protected:
			property Point MouseDownPos;

			/// <summary>
			/// Override WndProc to process custom resize messages.
			/// </summary>
			void WndProc(Message %msg) override;
			/// <summary>
			/// Override OnPaint to draw the velocity string in the form area.
			/// </summary>
			void OnPaint(PaintEventArgs ^e) override;

			/// <summary>
			/// Form closing callback: Save properties to setting file.
			/// </summary>
			void UI_FormClosing(Object ^sender, FormClosingEventArgs ^e);
			/// <summary>
			/// Form loading callback: Load properties from setting file.
			/// </summary>
			void UI_Load(Object ^sender, EventArgs ^e);

			void UI_MouseDown(Object ^sender, MouseEventArgs ^e);
			void UI_MouseUp(Object ^sender, MouseEventArgs ^e);
			void UI_MouseMove(Object ^sender, MouseEventArgs ^e);
			void AlwaysOnTopButton_CheckedChanged(Object ^sender, EventArgs ^e);
			void ColorButton_Click(Object ^sender, EventArgs ^e);
			void ExitButton_Click(Object ^sender, EventArgs ^e);
			void TransparencyButton_Click(Object ^sender, EventArgs ^e);

			/// <summary>
			/// Get COD4 <see cref="HANDLE"/>, return nullptr if not found.
			/// </summary>
			HANDLE GetCOD4Process();
			/// <summary>
			/// Thread to update velocity property from COD4 memory.
			/// </summary>
			void GetVelocityTask();

			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~UI();

		private:
			property bool IsMoving;

			const int _ = 10; // Border size
			property System::Drawing::Rectangle Top{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(0, 0, this->ClientSize.Width, _); } }
			property System::Drawing::Rectangle Left{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(0, 0, _, this->ClientSize.Height); } }
			property System::Drawing::Rectangle Bottom{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(0, this->ClientSize.Height - _, this->ClientSize.Width, _); } }
			property System::Drawing::Rectangle Right{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(this->ClientSize.Width - _, 0, _, this->ClientSize.Height); } }
			property System::Drawing::Rectangle TopLeft{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(0, 0, _, _); } }
			property System::Drawing::Rectangle TopRight{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(this->ClientSize.Width - _, 0, _, _); } }
			property System::Drawing::Rectangle BottomLeft{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(0, this->ClientSize.Height - _, _, _); } }
			property System::Drawing::Rectangle BottomRight{ System::Drawing::Rectangle get() { return System::Drawing::Rectangle(this->ClientSize.Width - _, this->ClientSize.Height - _, _, _); } }


			System::Windows::Forms::ContextMenuStrip^ AppContextMenu;
			System::Windows::Forms::ToolStripMenuItem^ AlwaysOnTopButton;
			System::Windows::Forms::ToolStripMenuItem^ BackgroundColorButton;
			System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
			System::Windows::Forms::ToolStripMenuItem^ ExitButton;
			System::Windows::Forms::ToolStripMenuItem^ TransparencyButton;
			System::Windows::Forms::ToolStripMenuItem^  ForegroundColorButton;
			System::ComponentModel::IContainer^ components;

			#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(UI::typeid));
				this->AppContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				this->BackgroundColorButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ForegroundColorButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->TransparencyButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->AlwaysOnTopButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->ExitButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->AppContextMenu->SuspendLayout();
				this->SuspendLayout();
				// 
				// AppContextMenu
				// 
				this->AppContextMenu->ImageScalingSize = System::Drawing::Size(20, 20);
				this->AppContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
					this->BackgroundColorButton,
						this->ForegroundColorButton, this->TransparencyButton, this->AlwaysOnTopButton, this->toolStripSeparator1, this->ExitButton
				});
				this->AppContextMenu->Name = L"AppContextMenu";
				this->AppContextMenu->Size = System::Drawing::Size(217, 140);
				// 
				// BackgroundColorButton
				// 
				this->BackgroundColorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
					static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
				this->BackgroundColorButton->ForeColor = System::Drawing::Color::Gainsboro;
				this->BackgroundColorButton->Name = L"BackgroundColorButton";
				this->BackgroundColorButton->Size = System::Drawing::Size(216, 26);
				this->BackgroundColorButton->Text = L"Background color";
				this->BackgroundColorButton->Click += gcnew System::EventHandler(this, &UI::ColorButton_Click);
				// 
				// ForegroundColorButton
				// 
				this->ForegroundColorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
					static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
				this->ForegroundColorButton->ForeColor = System::Drawing::Color::Gainsboro;
				this->ForegroundColorButton->Name = L"ForegroundColorButton";
				this->ForegroundColorButton->Size = System::Drawing::Size(216, 26);
				this->ForegroundColorButton->Text = L"Foreground color";
				this->ForegroundColorButton->Click += gcnew System::EventHandler(this, &UI::ColorButton_Click);
				// 
				// TransparencyButton
				// 
				this->TransparencyButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
					static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
				this->TransparencyButton->CheckOnClick = true;
				this->TransparencyButton->ForeColor = System::Drawing::Color::Gainsboro;
				this->TransparencyButton->Name = L"TransparencyButton";
				this->TransparencyButton->Size = System::Drawing::Size(216, 26);
				this->TransparencyButton->Text = L"Toggle Transparency";
				this->TransparencyButton->Click += gcnew System::EventHandler(this, &UI::TransparencyButton_Click);
				// 
				// AlwaysOnTopButton
				// 
				this->AlwaysOnTopButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
					static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
				this->AlwaysOnTopButton->Checked = true;
				this->AlwaysOnTopButton->CheckOnClick = true;
				this->AlwaysOnTopButton->CheckState = System::Windows::Forms::CheckState::Checked;
				this->AlwaysOnTopButton->ForeColor = System::Drawing::Color::Gainsboro;
				this->AlwaysOnTopButton->Name = L"AlwaysOnTopButton";
				this->AlwaysOnTopButton->Size = System::Drawing::Size(216, 26);
				this->AlwaysOnTopButton->Text = L"Always on top";
				this->AlwaysOnTopButton->CheckedChanged += gcnew System::EventHandler(this, &UI::AlwaysOnTopButton_CheckedChanged);
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->BackColor = System::Drawing::Color::DimGray;
				this->toolStripSeparator1->ForeColor = System::Drawing::Color::DarkGray;
				this->toolStripSeparator1->Name = L"toolStripSeparator1";
				this->toolStripSeparator1->Size = System::Drawing::Size(213, 6);
				// 
				// ExitButton
				// 
				this->ExitButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
					static_cast<System::Int32>(static_cast<System::Byte>(40)));
				this->ExitButton->ForeColor = System::Drawing::Color::Gainsboro;
				this->ExitButton->Name = L"ExitButton";
				this->ExitButton->Size = System::Drawing::Size(216, 26);
				this->ExitButton->Text = L"Exit";
				this->ExitButton->Click += gcnew System::EventHandler(this, &UI::ExitButton_Click);
				// 
				// UI
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(20, 39);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
					static_cast<System::Int32>(static_cast<System::Byte>(20)));
				this->ClientSize = System::Drawing::Size(345, 76);
				this->ContextMenuStrip = this->AppContextMenu;
				this->DoubleBuffered = true;
				this->Font = (gcnew System::Drawing::Font(L"Bitstream Vera Sans", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->ForeColor = System::Drawing::Color::Gainsboro;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				this->Margin = System::Windows::Forms::Padding(8, 7, 8, 7);
				this->Name = L"UI";
				this->Text = L"UI";
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &UI::UI_FormClosing);
				this->Load += gcnew System::EventHandler(this, &UI::UI_Load);
				this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::UI_MouseDown);
				this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::UI_MouseMove);
				this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::UI_MouseUp);
				this->AppContextMenu->ResumeLayout(false);
				this->ResumeLayout(false);
			}
			#pragma endregion
	};
}
