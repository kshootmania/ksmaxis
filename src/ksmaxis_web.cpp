#ifdef __EMSCRIPTEN__

#include "ksmaxis/ksmaxis.hpp"
#include <emscripten/html5.h>

namespace ksmaxis
{
	namespace
	{
		DeviceFlags s_initializedDevices = DeviceFlags::None;

		// mousemoveイベントで蓄積し、Update()で確定するマウス移動量
		double s_accumMouseX = 0.0;
		double s_accumMouseY = 0.0;

		AxisValues s_deltaMouse = { 0.0, 0.0 };

		EM_BOOL OnMouseMove([[maybe_unused]] int eventType, const EmscriptenMouseEvent* pMouseEvent, [[maybe_unused]] void* pUserData)
		{
			s_accumMouseX += pMouseEvent->movementX;
			s_accumMouseY += pMouseEvent->movementY;
			return EM_FALSE;
		}
	}

	bool Init(DeviceFlags deviceFlags, std::string* pErrorString, std::vector<std::string>* pWarningStrings)
	{
		if (pErrorString)
		{
			pErrorString->clear();
		}

		if ((deviceFlags & DeviceFlags::Mouse) != DeviceFlags::None)
		{
			emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, OnMouseMove);
			s_initializedDevices |= DeviceFlags::Mouse;
		}

		// Web版ではジョイスティックのアナログ軸入力は未対応
		if ((deviceFlags & DeviceFlags::Joystick) != DeviceFlags::None && pWarningStrings)
		{
			pWarningStrings->push_back("Joystick analog input is not supported on Web");
		}

		return true;
	}

	void Terminate()
	{
		if ((s_initializedDevices & DeviceFlags::Mouse) != DeviceFlags::None)
		{
			emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, nullptr);
		}
		s_initializedDevices = DeviceFlags::None;
		s_accumMouseX = 0.0;
		s_accumMouseY = 0.0;
		s_deltaMouse = { 0.0, 0.0 };
	}

	bool IsInitialized()
	{
		return s_initializedDevices != DeviceFlags::None;
	}

	bool IsInitialized(DeviceFlags deviceFlags)
	{
		return (s_initializedDevices & deviceFlags) == deviceFlags;
	}

	void Update()
	{
		s_deltaMouse = { s_accumMouseX, s_accumMouseY };
		s_accumMouseX = 0.0;
		s_accumMouseY = 0.0;
	}

	AxisValues GetAxisDeltas(InputMode mode)
	{
		if (mode == InputMode::kMouse)
		{
			return s_deltaMouse;
		}
		return AxisValues{ 0.0, 0.0 };
	}
}

#endif
