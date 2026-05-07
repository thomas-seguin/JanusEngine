#include "jnpch.h"
#include "Janus/Utils/PlatformUtils.h"

#include <commdlg.h>
#include <ShObjIdl.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Janus/Core/Application.h"

namespace Janus {

	std::string FileDialogs::OpenFile(const char* filter) {
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

	std::string FileDialogs::SaveFile(const char* filter) {
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

	std::string FileDialogs::ChooseFolder() {
        std::string result;

        IFileDialog* pfd = nullptr;
        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pfd));

        if (FAILED(hr))
            return result;

        // Configure dialog options
        DWORD options;
        pfd->GetOptions(&options);
        pfd->SetOptions(options | FOS_PICKFOLDERS | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR);

        // Set initial directory
        CHAR currentDir[MAX_PATH];
        if (GetCurrentDirectoryA(MAX_PATH, currentDir))
        {
            IShellItem* folderItem = nullptr;
            std::wstring wdir = std::wstring(currentDir, currentDir + strlen(currentDir));
            if (SUCCEEDED(SHCreateItemFromParsingName(wdir.c_str(), nullptr, IID_PPV_ARGS(&folderItem))))
            {
                pfd->SetFolder(folderItem);
                folderItem->Release();
            }
        }

        // Show dialog
        HWND hwnd = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
        hr = pfd->Show(hwnd);

        if (SUCCEEDED(hr))
        {
            IShellItem* item = nullptr;
            if (SUCCEEDED(pfd->GetResult(&item)))
            {
                PWSTR path = nullptr;
                if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &path)))
                {
                    // Convert wide string to UTF‑8
                    int size = WideCharToMultiByte(CP_UTF8, 0, path, -1, nullptr, 0, nullptr, nullptr);
                    std::string utf8(size - 1, 0);
                    WideCharToMultiByte(CP_UTF8, 0, path, -1, utf8.data(), size, nullptr, nullptr);

                    result = utf8;
                    CoTaskMemFree(path);
                }
                item->Release();
            }
        }

        pfd->Release();
        return result;
	}
}