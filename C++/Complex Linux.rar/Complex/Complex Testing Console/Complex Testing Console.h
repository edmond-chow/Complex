#pragma once
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
