#include "jnpch.h"
#include "EditorPrefs.h"

#include <yaml-cpp/yaml.h>

namespace Janus {
    std::filesystem::path EditorPrefs::LastProject = "";
    std::filesystem::path EditorPrefs::LastScene = "";

    void EditorPrefs::Load() {
        YAML::Node data = YAML::LoadFile("EditorPrefs.yaml");

        if (data["LastProject"])
            LastProject = data["LastProject"].as<std::string>();

        if (data["LastScene"])
            LastScene = data["LastScene"].as<std::string>();
    }

    void EditorPrefs::Save() {
        YAML::Emitter out;
        out << YAML::BeginMap;

        out << YAML::Key << "LastProject" << YAML::Value << LastProject.string();
        out << YAML::Key << "LastScene" << YAML::Value << LastScene.string();

        out << YAML::EndMap;

        std::ofstream fout("EditorPrefs.yaml");
        fout << out.c_str();
    }

}