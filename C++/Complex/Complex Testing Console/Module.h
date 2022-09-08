#pragma once
#ifndef CMPLX_UNIT_TEST_MOD
#define CMPLX_UNIT_TEST_MOD
namespace Mod
{
	class MyModule final
	{
	private:
		constexpr MyModule() noexcept = delete;
		constexpr ~MyModule() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
