#pragma once
#ifndef CMPLX_UNIT_TEST_MOD
#define CMPLX_UNIT_TEST_MOD
namespace CmplxBasis
{
	class CmplxConsole final
	{
	private:
		constexpr CmplxConsole() noexcept = delete;
		constexpr ~CmplxConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
