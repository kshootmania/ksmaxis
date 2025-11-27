#pragma once
#include <cstdint>
#include <array>

namespace ksmaxis
{
	enum class InputMode : std::uint8_t
	{
		kAnalogStick, // X/Y
		kSlider, // Slider0/Slider1
		kMouse, // Mouse X/Y
	};

	enum class Error : std::uint8_t
	{
		kOk,
		kNotInitialized,
		kAlreadyInitialized,
		kPlatform,
	};

	using AxisValues = std::array<double, 2>;

#ifdef _WIN32
	[[nodiscard]]
	Error Init(void* hWnd);
#else
	[[nodiscard]]
	Error Init();
#endif

	void Terminate();

	void Update();

	[[nodiscard]]
	AxisValues GetAxisDeltas(InputMode mode);
}
