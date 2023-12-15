#pragma once
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
