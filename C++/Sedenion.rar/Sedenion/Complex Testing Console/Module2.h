#pragma once
#ifndef CMPLX_UNIT_TEST_MOD_2
#define CMPLX_UNIT_TEST_MOD_2
namespace Mod2
{
	class MyModule2 final
	{
	private:
		constexpr MyModule2() noexcept = delete;
		constexpr ~MyModule2() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
