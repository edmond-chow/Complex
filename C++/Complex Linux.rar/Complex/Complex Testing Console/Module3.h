#pragma once
#ifndef CMPLX_UNIT_TEST_MOD_3
#define CMPLX_UNIT_TEST_MOD_3
namespace Mod3
{
	class MyModule3 final
	{
	private:
		constexpr MyModule3() noexcept = delete;
		constexpr ~MyModule3() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
