#pragma once

#include <string>
#include <filesystem>

#include "Janus/Core/Core.h"

namespace Janus {
	struct ProjectConfig {
		std::string Name = "Untitled";

		std::filesystem::path StartScene;

		std::filesystem::path AssetDirectory;
	};

	class Project {
	public:
		static const std::filesystem::path& GetProjectDirectory() {
			JN_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->m_ProjectDirectory;
		}

		static const std::filesystem::path GetAssetDirectory() {
			JN_CORE_ASSERT(s_ActiveProject);
			return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
		}

		static const std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& path) {
			JN_CORE_ASSERT(s_ActiveProject);
			return GetAssetDirectory() / path;
		}

		ProjectConfig& GetConfig() { return m_Config; }

		static Ref<Project> GetActive() { return s_ActiveProject; }

		static Ref<Project> New(const std::string& m_ProjDir);
		static Ref<Project> Load(const std::filesystem::path& path);
		static bool SaveActive(const std::filesystem::path& path);
	private:
		ProjectConfig m_Config;
		std::filesystem::path m_ProjectDirectory;

		inline static Ref<Project> s_ActiveProject;
	};
}