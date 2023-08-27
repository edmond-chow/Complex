#pragma once
#ifndef SEDEN_UNIT_TEST_MOD
#define SEDEN_UNIT_TEST_MOD
namespace SedenionMod
{
	class MySedenionTestor final
	{
	private:
		constexpr MySedenionTestor() noexcept = delete;
		constexpr ~MySedenionTestor() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
