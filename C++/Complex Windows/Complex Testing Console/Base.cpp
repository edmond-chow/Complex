/*
 *   Copyright 2022 Edmond Chow
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include <cstddef>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Complex Testing Console.h"
#include "Quaternion Testing Console.h"
#include "Octonion Testing Console.h"
#include "Sedenion Extended Module.h"
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
		static constexpr const wchar_t* const Name[] { L"Exit", L"Complex Testing Console", L"Quaternion Testing Console", L"Octonion Testing Console", L"Sedenion Extended Module" };
		static constexpr void(*const Func[])() { nullptr, CmplxBasis::CmplxConsole::Load, QuterBasis::QuterConsole::Load, OctonBasis::OctonConsole::Load, SedenBasis::SedenConsole::Load };
		static constexpr const std::size_t HidLen = 1;
		static constexpr const std::size_t DefIdx = 3;
		static std::size_t Idx;
		static std::wstring AddSquares(const std::wstring& Opt)
		{
			return L"[" + Opt + L"]";
		};
	public:
		static std::wstring GetTitle();
		static std::wstring GetStartupLine();
		static bool IsSwitchTo(const std::wstring& Opt);
		///
		/// Main Thread
		///
		static void Main();
		///
		/// Console Line Materials
		///
		static std::wstring Exception(const std::exception& Exc);
		static std::wstring Exception();
		static std::wstring Selection(const std::wstring& Con);
		static std::wstring Selection();
		static std::wstring Input(const std::wstring& Con);
		static std::wstring Input();
		static std::wstring Output(const std::wstring& Pre, const std::wstring& Con);
		static std::wstring Output(const std::wstring& Con);
		static std::wstring Output();
		static std::wstring Comment(const std::wstring& Pre, const std::wstring& Con);
		static std::wstring Comment(const std::wstring& Con);
		static std::wstring Comment();
		static void Startup(const std::wstring& Tle);
	};
	///
	/// Base
	///
	std::size_t Base::Idx = DefIdx;
	std::wstring Base::GetTitle()
	{
		return Idx > DefIdx ? L"Extended Module (Sedenion, Pathion, Chingon, Routon, Voudon, ...)" : Name[Idx];
	};
	std::wstring Base::GetStartupLine()
	{
		std::wstring Rst = L" >> ";
		bool Fst = true;
		for (std::size_t i = HidLen; i < std::extent_v<decltype(Name)>; ++i, Fst = false)
		{
			if (Fst == false) { Rst += L"   "; }
			Rst += AddSquares(Name[i]);
		}
		return Rst;
	};
	bool Base::IsSwitchTo(const std::wstring& Opt)
	{
		for (std::size_t i = 0; i < std::extent_v<decltype(Name)>; ++i)
		{
			if (Opt == AddSquares(Name[i]))
			{
				Idx = i;
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
		while (Func[Idx] != nullptr)
		{
			Func[Idx]();
		}
		Idx = DefIdx;
		Clear();
	};
	///
	/// Console Line Materials
	///
	std::wstring Base::Exception(const std::exception& Exc)
	{
		SetForegroundColor(ConsoleColor::DarkCyan);
		std::wcout << std::endl << L"   [" << typeid(Exc).name() << L"] ";
		SetForegroundColor(ConsoleColor::Cyan);
		std::wcout << Exc.what() << std::endl;
		SetForegroundColor(ConsoleColor::White);
		std::wcout << L"   Press any key to continue . . .   " << std::endl;
		PressAnyKey();
		std::wcout << std::endl;
		return L"";
	};
	std::wstring Base::Exception()
	{
		return Exception(std::exception{});
	};
	std::wstring Base::Selection(const std::wstring& Con)
	{
		SetForegroundColor(ConsoleColor::DarkCyan);
		std::wcout << L" %   ";
		SetForegroundColor(ConsoleColor::Blue);
		std::wcout << Con << std::endl;
		return Con;
	};
	std::wstring Base::Selection()
	{
		return Selection(L"");
	};
	std::wstring Base::Input(const std::wstring& Con)
	{
		SetForegroundColor(ConsoleColor::Yellow);
		std::wcout << L" >   ";
		SetForegroundColor(ConsoleColor::DarkGreen);
		std::wcout << Con;
		SetForegroundColor(ConsoleColor::Green);
		std::wstring Rst;
		std::getline(std::wcin, Rst);
		return Rst;
	};
	std::wstring Base::Input()
	{
		return Input(L"");
	};
	std::wstring Base::Output(const std::wstring& Pre, const std::wstring& Con)
	{
		SetForegroundColor(ConsoleColor::Magenta);
		std::wcout << L" #   ";
		SetForegroundColor(ConsoleColor::DarkRed);
		std::wcout << Pre;
		SetForegroundColor(ConsoleColor::Red);
		std::wcout << Con << std::endl;
		return Con;
	};
	std::wstring Base::Output(const std::wstring& Con)
	{
		return Output(L"", Con);
	};
	std::wstring Base::Output()
	{
		return Output(L"");
	};
	std::wstring Base::Comment(const std::wstring& Pre, const std::wstring& Con)
	{
		SetForegroundColor(ConsoleColor::White);
		std::wcout << L" /   ";
		SetForegroundColor(ConsoleColor::Cyan);
		std::wcout << Pre;
		SetForegroundColor(ConsoleColor::Gray);
		std::wcout << Con << std::endl;
		return Con;
	};
	std::wstring Base::Comment(const std::wstring& Con)
	{
		return Comment(L"", Con);
	};
	std::wstring Base::Comment()
	{
		return Comment(L"");
	};
	void Base::Startup(const std::wstring& Tle)
	{
		Clear();
		SetTitle(Tle);
		std::wcout << std::endl;
	};
}
