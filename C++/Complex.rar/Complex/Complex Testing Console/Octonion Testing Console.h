#pragma once
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
