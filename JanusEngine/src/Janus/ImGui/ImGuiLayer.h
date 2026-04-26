#pragma once

#include "Janus/Core/Layer.h"

#include "Janus/Events/KeyEvent.h"
#include "Janus/Events/MouseEvent.h"
#include "Janus/Events/ApplicationEvent.h"


namespace Janus {
	class JANUS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}
