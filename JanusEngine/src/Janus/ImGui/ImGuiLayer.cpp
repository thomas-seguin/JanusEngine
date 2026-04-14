#include "jnpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Janus/Application.h"

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Janus {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(JN_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	static ImGuiKey GLFWKeyToImGuiKey(int key) {
		switch (key) {
		case GLFW_KEY_TAB:           return ImGuiKey_Tab;
		case GLFW_KEY_LEFT:          return ImGuiKey_LeftArrow;
		case GLFW_KEY_RIGHT:         return ImGuiKey_RightArrow;
		case GLFW_KEY_UP:            return ImGuiKey_UpArrow;
		case GLFW_KEY_DOWN:          return ImGuiKey_DownArrow;
		case GLFW_KEY_PAGE_UP:       return ImGuiKey_PageUp;
		case GLFW_KEY_PAGE_DOWN:     return ImGuiKey_PageDown;
		case GLFW_KEY_HOME:          return ImGuiKey_Home;
		case GLFW_KEY_END:           return ImGuiKey_End;
		case GLFW_KEY_INSERT:        return ImGuiKey_Insert;
		case GLFW_KEY_DELETE:        return ImGuiKey_Delete;
		case GLFW_KEY_BACKSPACE:     return ImGuiKey_Backspace;
		case GLFW_KEY_SPACE:         return ImGuiKey_Space;
		case GLFW_KEY_ENTER:         return ImGuiKey_Enter;
		case GLFW_KEY_ESCAPE:        return ImGuiKey_Escape;
		case GLFW_KEY_APOSTROPHE:    return ImGuiKey_Apostrophe;
		case GLFW_KEY_COMMA:         return ImGuiKey_Comma;
		case GLFW_KEY_MINUS:         return ImGuiKey_Minus;
		case GLFW_KEY_PERIOD:        return ImGuiKey_Period;
		case GLFW_KEY_SLASH:         return ImGuiKey_Slash;
		case GLFW_KEY_SEMICOLON:     return ImGuiKey_Semicolon;
		case GLFW_KEY_EQUAL:         return ImGuiKey_Equal;
		case GLFW_KEY_LEFT_BRACKET:  return ImGuiKey_LeftBracket;
		case GLFW_KEY_BACKSLASH:     return ImGuiKey_Backslash;
		case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
		case GLFW_KEY_GRAVE_ACCENT:  return ImGuiKey_GraveAccent;
		case GLFW_KEY_CAPS_LOCK:     return ImGuiKey_CapsLock;
		case GLFW_KEY_SCROLL_LOCK:   return ImGuiKey_ScrollLock;
		case GLFW_KEY_NUM_LOCK:      return ImGuiKey_NumLock;
		case GLFW_KEY_PRINT_SCREEN:  return ImGuiKey_PrintScreen;
		case GLFW_KEY_PAUSE:         return ImGuiKey_Pause;
		case GLFW_KEY_LEFT_SHIFT:    return ImGuiKey_LeftShift;
		case GLFW_KEY_LEFT_CONTROL:  return ImGuiKey_LeftCtrl;
		case GLFW_KEY_LEFT_ALT:      return ImGuiKey_LeftAlt;
		case GLFW_KEY_LEFT_SUPER:    return ImGuiKey_LeftSuper;
		case GLFW_KEY_RIGHT_SHIFT:   return ImGuiKey_RightShift;
		case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
		case GLFW_KEY_RIGHT_ALT:     return ImGuiKey_RightAlt;
		case GLFW_KEY_RIGHT_SUPER:   return ImGuiKey_RightSuper;
		case GLFW_KEY_MENU:          return ImGuiKey_Menu;
		default:
			// A-Z
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
				return (ImGuiKey)(ImGuiKey_A + (key - GLFW_KEY_A));
			// 0-9
			if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
				return (ImGuiKey)(ImGuiKey_0 + (key - GLFW_KEY_0));
			// F1-F12
			if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12)
				return (ImGuiKey)(ImGuiKey_F1 + (key - GLFW_KEY_F1));
			// Numpad 0-9
			if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9)
				return (ImGuiKey)(ImGuiKey_Keypad0 + (key - GLFW_KEY_KP_0));
			return ImGuiKey_None;
		}
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(GLFWKeyToImGuiKey(e.GetKeyCode()), true);
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(GLFWKeyToImGuiKey(e.GetKeyCode()), false);
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int c = e.GetKeyCode();
		if (c > 0 && c < 0x10000)
			io.AddInputCharacter((ImWchar)c);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

}