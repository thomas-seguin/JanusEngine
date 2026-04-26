#pragma once

#include "Janus/Core/Core.h"
#include "Janus/Core/MouseCodes.h"
#include "Janus/Core/KeyCodes.h"

namespace Janus {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode key);
		
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}