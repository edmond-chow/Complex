#pragma once
#ifndef QUTER_UNIT_TEST_MOD
#define QUTER_UNIT_TEST_MOD
namespace QuterBasis
{
	class QuterConsole final
	{
	private:
		constexpr QuterConsole() noexcept = delete;
		constexpr ~QuterConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
