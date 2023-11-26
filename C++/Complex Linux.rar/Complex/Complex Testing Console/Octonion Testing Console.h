#pragma once
#ifndef OCTON_UNIT_TEST_MOD
#define OCTON_UNIT_TEST_MOD
namespace OctonBasis
{
	class OctonConsole final
	{
	private:
		constexpr OctonConsole() noexcept = delete;
		constexpr ~OctonConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
}
#endif
