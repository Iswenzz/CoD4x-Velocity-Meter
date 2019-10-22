#include "UI.h"
#include "Settings.h"

namespace COD4
{
	UI::UI()
	{
		InitializeComponent();
		KeyPreview = true;
		SetStyle(ControlStyles::ResizeRedraw, true);

		Thread ^velocityThread = gcnew Thread(gcnew ThreadStart(this, &UI::GetVelocityTask));
		velocityThread->Start();
	}

	UI::~UI()
	{
		if (components)
			delete components;
	}

	void UI::OnPaint(PaintEventArgs ^e)
	{
		Form::OnPaint(e);

		StringFormat ^drawFormat = gcnew StringFormat();
		drawFormat->Alignment = StringAlignment::Center;
		drawFormat->LineAlignment = StringAlignment::Near;

		Color fcolor = AppForeColor.IsEmpty ? Color::Gainsboro : AppForeColor;
		float fontSize = Math::Sqrt(Size.Height * Size.Height) / 2;
		System::Drawing::Font ^font = gcnew System::Drawing::Font(Font->FontFamily, fontSize);
		System::Drawing::SolidBrush ^forecolor = gcnew System::Drawing::SolidBrush(fcolor);

		e->Graphics->InterpolationMode = InterpolationMode::HighQualityBilinear;
		e->Graphics->SmoothingMode = SmoothingMode::HighQuality;
		e->Graphics->TextRenderingHint = System::Drawing::Text::TextRenderingHint::ClearTypeGridFit;
		e->Graphics->DrawString(Velocity.ToString("0"), font, forecolor, DisplayRectangle, drawFormat);
	}

	void UI::WndProc(Message %msg)
	{
		Form::WndProc(msg);

		switch (msg.Msg)
		{
			case WM_NCHITTEST: // Resize
			{
				Point cursor = PointToClient(Cursor->Position);

				if (TopLeft.Contains(cursor))			msg.Result = (IntPtr)HTTOPLEFT;
				else if (TopRight.Contains(cursor))		msg.Result = (IntPtr)HTTOPRIGHT;
				else if (BottomLeft.Contains(cursor))	msg.Result = (IntPtr)HTBOTTOMLEFT;
				else if (BottomRight.Contains(cursor))	msg.Result = (IntPtr)HTBOTTOMRIGHT;
				else if (Top.Contains(cursor))			msg.Result = (IntPtr)HTTOP;
				else if (Left.Contains(cursor))			msg.Result = (IntPtr)HTLEFT;
				else if (Right.Contains(cursor))		msg.Result = (IntPtr)HTRIGHT;
				else if (Bottom.Contains(cursor))		msg.Result = (IntPtr)HTBOTTOM;
			}
			break;
		}
	}

	void UI::UI_FormClosing(Object ^sender, FormClosingEventArgs ^e)
	{
		Settings::Default->AlwaysOnTop = AlwaysOnTopButton->Checked.ToString();
		Settings::Default->AppTransparency = TransparencyButton->Checked.ToString();
		Settings::Default->AppBackColor = AppBackColor.ToArgb().ToString();
		Settings::Default->AppForeColor = AppForeColor.ToArgb().ToString();
		Settings::Default->AppSize = Size.Width + " " + Size.Height;
		Settings::Default->AppLocation = Location.X + " " + Location.Y;
		Settings::Default->Save();
	}

	void UI::UI_Load(Object ^sender, EventArgs ^e)
	{
		if (!DesignMode)
		{
			if (!String::IsNullOrEmpty(Settings::Default->AlwaysOnTop))
				TopMost = Convert::ToBoolean(Settings::Default->AlwaysOnTop);
			if (!String::IsNullOrEmpty(Settings::Default->AppTransparency))
			{
				TransparencyButton->Checked = Convert::ToBoolean(Settings::Default->AppTransparency);
				TransparencyButton_Click(nullptr, nullptr);
			}
			if (!String::IsNullOrEmpty(Settings::Default->AppBackColor))
			{
				AppBackColor = Color::FromArgb(Convert::ToInt32(Settings::Default->AppBackColor));
				if (!TransparencyButton->Checked)
					BackColor = AppBackColor;
			}
			if (!String::IsNullOrEmpty(Settings::Default->AppForeColor))
				AppForeColor = Color::FromArgb(Convert::ToInt32(Settings::Default->AppForeColor));
			if (!String::IsNullOrEmpty(Settings::Default->AppSize))
			{
				array<String ^> ^location = Settings::Default->AppSize->Split(' ');
				Size = System::Drawing::Size(Convert::ToInt32(location[0]), Convert::ToInt32(location[1]));
			}
			if (!String::IsNullOrEmpty(Settings::Default->AppLocation))
			{
				array<String ^> ^location = Settings::Default->AppLocation->Split(' ');
				Location = Point(Convert::ToInt32(location[0]), Convert::ToInt32(location[1]));
			}
		}
	}

	void UI::ExitButton_Click(Object ^sender, EventArgs ^e)
	{
		Application::Exit();
	}

	void UI::TransparencyButton_Click(Object ^sender, EventArgs ^e)
	{
		try
		{
			if (TransparencyButton->Checked)
			{
				TransparencyKey = Color::FromArgb(255, 20, 20, 20);
				BackColor = Color::FromArgb(255, 20, 20, 20);
			}
			else
			{
				TransparencyKey = Color::Empty;
				BackColor = AppBackColor;
			}
		}
		catch (Exception ^e) { }
	}
	
	void UI::ColorButton_Click(Object ^sender, EventArgs ^e)
	{
		ColorDialog ^dialog = gcnew ColorDialog();
		if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if (ToolStripMenuItem ^item = dynamic_cast<ToolStripMenuItem ^>(sender))
			{
				String ^controlName = item->Name;
				if (controlName->Equals("BackgroundColorButton"))
				{
					AppBackColor = dialog->Color;
					if (!TransparencyButton->Checked)
						BackColor = AppBackColor;
				}
				else if (controlName->Equals("ForegroundColorButton"))
					AppForeColor = dialog->Color;

				Invalidate();
			}
		}
	}

	void UI::UI_MouseDown(Object ^sender, MouseEventArgs ^e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			IsMoving = true;
			MouseDownPos = Point(e->X, e->Y);
		}
	}

	void UI::UI_MouseUp(Object ^sender, MouseEventArgs ^e)
	{
		IsMoving = false;
	}

	void UI::UI_MouseMove(Object ^sender, MouseEventArgs ^e)
	{
		if (IsMoving)
			SetDesktopLocation(MousePosition.X - MouseDownPos.X, MousePosition.Y - MouseDownPos.Y);
	}

	void UI::AlwaysOnTopButton_CheckedChanged(Object ^sender, EventArgs ^e)
	{
		TopMost = AlwaysOnTopButton->Checked;
	}

	HANDLE UI::GetCOD4Process()
	{
		PROCESSENTRY32W entry;
		entry.dwSize = sizeof(PROCESSENTRY32W);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (wcsicmp(entry.szExeFile, L"iw3mp.exe") == 0)
					return OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
			}
		}
		CloseHandle(snapshot);
		return nullptr;
	}

	void UI::GetVelocityTask()
	{
		HANDLE cod4 = nullptr;
		while (!IsDisposed)
		{
			if ((cod4 = GetCOD4Process()) == nullptr)
				Thread::Sleep(5000);
			else
			{
				float x, y;
				ReadProcessMemory(cod4, reinterpret_cast<PVOID>(0x79449C), &x, sizeof(x), nullptr);
				ReadProcessMemory(cod4, reinterpret_cast<PVOID>(0x7944A0), &y, sizeof(y), nullptr);
				Velocity = (float)Math::Sqrt((x * x) + (y * y));
				Invalidate();
			}
			Thread::Sleep(50);
		}
	}
}