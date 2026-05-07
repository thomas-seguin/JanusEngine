#pragma once
#include <filesystem>

namespace Janus {
	class EditorPrefs {
	public:
		static void Load();
		static void Save();

		static std::filesystem::path LastProject;
		static std::filesystem::path LastScene;
	};
}