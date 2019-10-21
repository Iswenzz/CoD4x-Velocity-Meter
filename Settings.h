namespace COD4 
{
    [::System::Runtime::CompilerServices::CompilerGeneratedAttribute()]
    [::System::CodeDom::Compiler::GeneratedCodeAttribute("Microsoft::VisualStudio::Editors::SettingsDesigner::SettingsSingleFileGenerator", "15.9.0.0")]
	public ref class Settings : ::System::Configuration::ApplicationSettingsBase 
	{
        private:
        	static Settings ^defaultInstance = ((Settings ^)(::System::Configuration::ApplicationSettingsBase
				::Synchronized(gcnew Settings())));
        
        public:
	        property static Settings ^Default 
			{
	            Settings^ get() 
				{
	                return defaultInstance;
	            }
	        }
	        
	        [::System::Configuration::UserScopedSettingAttribute()]
	        [::System::Diagnostics::DebuggerNonUserCodeAttribute()]
	        [::System::Configuration::DefaultSettingValueAttribute("")]
	        property ::System::String ^AlwaysOnTop 
			{
				::System::String^ get() 
				{
	                return ((::System::String ^)(this["AlwaysOnTop"]));
	            }
	            void set(::System::String ^value) 
				{
	                this["AlwaysOnTop"] = value;
	            }
	        }

			[::System::Configuration::UserScopedSettingAttribute()]
			[::System::Diagnostics::DebuggerNonUserCodeAttribute()]
			[::System::Configuration::DefaultSettingValueAttribute("")]
			property ::System::String ^AppBackColor
			{
				::System::String^ get()
				{
					return ((::System::String ^)(this["AppBackColor"]));
				}
				void set(::System::String ^value)
				{
					this["AppBackColor"] = value;
				}
			}

			[::System::Configuration::UserScopedSettingAttribute()]
			[::System::Diagnostics::DebuggerNonUserCodeAttribute()]
			[::System::Configuration::DefaultSettingValueAttribute("")]
			property ::System::String ^AppSize
			{
				::System::String^ get()
				{
					return ((::System::String ^)(this["AppSize"]));
				}
				void set(::System::String ^value)
				{
					this["AppSize"] = value;
				}
			}

			[::System::Configuration::UserScopedSettingAttribute()]
			[::System::Diagnostics::DebuggerNonUserCodeAttribute()]
			[::System::Configuration::DefaultSettingValueAttribute("")]
			property ::System::String ^AppLocation
			{
				::System::String^ get()
				{
					return ((::System::String ^)(this["AppLocation"]));
				}
				void set(::System::String ^value)
				{
					this["AppLocation"] = value;
				}
			}

			[::System::Configuration::UserScopedSettingAttribute()]
			[::System::Diagnostics::DebuggerNonUserCodeAttribute()]
			[::System::Configuration::DefaultSettingValueAttribute("")]
			property ::System::String ^AppTransparency
			{
				::System::String^ get()
				{
					return ((::System::String ^)(this["AppTransparency"]));
				}
				void set(::System::String ^value)
				{
					this["AppTransparency"] = value;
				}
			}
	};
}
