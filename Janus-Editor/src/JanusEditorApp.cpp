#include <Janus.h>
#include <Janus/Core/Entrypoint.h>

#include "EditorLayer.h"

namespace Janus {
	class JanusEditor : public Application {
	public:
		JanusEditor() : Application("Janus Editor") {
			PushLayer(new EditorLayer());
		}

		~JanusEditor() {

		}
	};

	Application* CreateApplication() {
		return new JanusEditor();
	}
}
