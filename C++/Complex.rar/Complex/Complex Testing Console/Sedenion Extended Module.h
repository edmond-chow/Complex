#pragma once
#ifndef SEDEN_UNIT_TEST_MOD
#define SEDEN_UNIT_TEST_MOD
namespace SedenBasis
{
	class SedenConsole final
	{
	private:
		constexpr SedenConsole() noexcept = delete;
		constexpr ~SedenConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
