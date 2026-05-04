#pragma once

#include <filesystem>

namespace Janus {
	class ContentBrowserPanel {
	public:
		ContentBrowserPanel();
		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
	};
}