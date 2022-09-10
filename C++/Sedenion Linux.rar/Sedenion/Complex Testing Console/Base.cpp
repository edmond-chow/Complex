#include <string>
#include <iostream>
#include "Module.h"
#include "Module2.h"
#include "Module3.h"
#include "SedenionMod.h"
#include "Base Extension.h"
using namespace CmplxConExt;
namespace ComplexTestingConsole
{
	class Base final
	{
	private:
		constexpr Base() noexcept = delete;
		constexpr ~Base() noexcept = delete;
		///
		/// Base
		///
		static constexpr const wchar_t* TestingConsole[] { L"Exit", L"Complex Testing Console", L"Quaternion Testing Console", L"Octonion Testing Console" };
		static constexpr const wchar_t* SedenionModeConsole[] { L"SedenionMode", L"Sedenion", L"Trigintaduonion", L"Sexagintaquatronion", L"Centumduodetrigintanion", L"Ducentiquinquagintasexion" };
		static std::size_t Index;
	public:
		static std::wstring GetTitle();
		static std::wstring GetStartupLine();
		static std::wstring GetSedenTitle();
		static bool IsSwitchTo(const std::wstring& Str);
		///
		/// Main Thread
		///
		static void Main();
		///
		/// Console Line Materials
		///
		static std::wstring Exception(const std::exception& ex);
		static std::wstring Exception();
		static std::wstring Selection(const std::wstring& str);
		static std::wstring Selection();
		static std::wstring Input(const std::wstring& str);
		static std::wstring Input();
		static std::wstring Output(const std::wstring& main, const std::wstring& str);
		static std::wstring Output(const std::wstring& str);
		static std::wstring Output();
		static std::wstring Comment(const std::wstring& head, const std::wstring& str);
		static std::wstring Comment(const std::wstring& str);
		static std::wstring Comment();
		static void Startup(const std::wstring& title);
	};
	///
	/// Base
	///
	std::size_t Base::Index = std::extent_v<decltype(Base::TestingConsole)> - 1;
	std::wstring Base::GetTitle() { return Index != std::extent_v<decltype(Base::TestingConsole)> ? TestingConsole[Index] : SedenionModeConsole[0]; };
	std::wstring Base::GetStartupLine()
	{
		std::wstring Output = L" >> ";
		for (const wchar_t* Name : TestingConsole)
		{
			if (std::wstring(Name) == TestingConsole[0]) { continue; }
			Output.append(L"[").append(Name).append(L"]   ");
		}
		return Output.append(L"[").append(SedenionModeConsole[0]).append(L"]");
	};
	std::wstring Base::GetSedenTitle()
	{
		std::wstring Output;
		for (std::size_t i = 1; i < std::extent_v<decltype(Base::SedenionModeConsole)>; ++i)
		{
			Output += SedenionModeConsole[i];
			Output += L", ";
		}
		return Output += L"...";
	};
	bool Base::IsSwitchTo(const std::wstring& Str)
	{
		for (std::size_t s = 0; s < std::extent_v<decltype(TestingConsole)> +1; ++s)
		{
			if (Str == std::wstring{}.append(L"[").append(s != std::extent_v<decltype(Base::TestingConsole)> ? TestingConsole[s] : SedenionModeConsole[0]).append(L"]"))
			{
				Index = s;
				return true;
			}
		}
		return false;
	};
	///
	/// Main Thread
	///
	void Base::Main()
	{
		while (true)
		{
			switch (Index)
			{
			case 0:
				clear();
				return;
			case 1:
				Mod::MyModule::Load();
				break;
			case 2:
				Mod2::MyModule2::Load();
				break;
			case 3:
				Mod3::MyModule3::Load();
				break;
			case 4:
				SedenionMod::MySedenionTestor::Load();
				break;
			default:
				throw;
			}
		}
	};
	///
	/// Console Line Materials
	///
	std::wstring Base::Exception(const std::exception& ex)
	{
		setForegroundColor(ConsoleColor::DarkCyan);
		std::wcout << std::endl << L"   [" << typeid(decltype(ex)).name() << L"] ";
		setForegroundColor(ConsoleColor::Cyan);
		std::wcout << ex.what() << std::endl;
		setForegroundColor(ConsoleColor::White);
		std::wcout << L"   Press any key to continue . . .   " << std::endl;
		pressAnyKey();
		std::wcout << std::endl;
		return L"";
	};
	std::wstring Base::Exception() { return Exception(std::exception()); };
	std::wstring Base::Selection(const std::wstring& str)
	{
		setForegroundColor(ConsoleColor::DarkCyan);
		std::wcout << L" %   ";
		setForegroundColor(ConsoleColor::Blue);
		std::wcout << str << std::endl;
		return str;
	};
	std::wstring Base::Selection() { return Selection(L""); };
	std::wstring Base::Input(const std::wstring& str)
	{
		setForegroundColor(ConsoleColor::Yellow);
		std::wcout << L" >   ";
		setForegroundColor(ConsoleColor::DarkGreen);
		std::wcout << str;
		setForegroundColor(ConsoleColor::Green);
		std::wstring output;
		std::getline(std::wcin, output);
		return output;
	};
	std::wstring Base::Input() { return Input(L""); };
	std::wstring Base::Output(const std::wstring& main, const std::wstring& str)
	{
		setForegroundColor(ConsoleColor::Magenta);
		std::wcout << L" #   ";
		setForegroundColor(ConsoleColor::DarkRed);
		std::wcout << main;
		setForegroundColor(ConsoleColor::Red);
		std::wcout << str << std::endl;
		return str;
	};
	std::wstring Base::Output(const std::wstring& str) { return Output(L"", str); };
	std::wstring Base::Output() { return Output(L""); };
	std::wstring Base::Comment(const std::wstring& head, const std::wstring& str)
	{
		setForegroundColor(ConsoleColor::White);
		std::wcout << L" /   ";
		setForegroundColor(ConsoleColor::Cyan);
		std::wcout << head;
		setForegroundColor(ConsoleColor::Gray);
		std::wcout << str << std::endl;
		return str;
	};
	std::wstring Base::Comment(const std::wstring& str) { return Comment(L"", str); };
	std::wstring Base::Comment() { return Comment(L""); };
	void Base::Startup(const std::wstring& title)
	{
		clear();
		setTitle(title);
		std::wcout << std::endl;
	};
}
