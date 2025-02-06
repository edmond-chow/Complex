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
#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef NUM_STRING
#define NUM_STRING
#pragma pack(push)
#pragma push_macro("I")
#pragma push_macro("Ths")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#if defined(_MSVC_LANG)
#define I __declspec(dllimport)
#define Ths __thiscall
#else
#define I
#define Ths
#endif
namespace Num
{
	class I String
	{
	private:
		wchar_t* Pointer;
	public:
		Ths String();
		Ths String(const wchar_t* Pt);
		String(const String& Self) = delete;
		Ths String(String&& Self) noexcept;
		String& operator =(const String& O) & = delete;
		String& Ths operator =(String&& O) & noexcept;
		Ths ~String() noexcept;
		const wchar_t* Ths Ptr() const&;
	};
}
#pragma pop_macro("Ths")
#pragma pop_macro("I")
#pragma pack(pop)
#endif
#endif
