#include <Windows.h>

#include "fileapi.h"
#include <psapi.h>

typedef HRESULT (*DirectInput8CreateOriginal)(HINSTANCE hinst, DWORD dwVersion,
                                              REFIID riidltf, LPVOID *ppvOut,
                                              LPUNKNOWN punkOuter);
DirectInput8CreateOriginal DInput8OriginalFunc;
HMODULE DInput8Dll;

extern "C" __declspec(dllexport) HRESULT WINAPI
    DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf,
                       LPVOID *ppvOut, LPUNKNOWN punkOuter) {
  return DInput8OriginalFunc(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

void InitW() {

  wchar_t DInput8DllPath[MAX_PATH];
  GetSystemDirectoryW(DInput8DllPath, MAX_PATH);
  wcscat_s(DInput8DllPath, MAX_PATH, L"\\dinput8.dll");
  DInput8Dll = LoadLibraryW(DInput8DllPath);
  DInput8OriginalFunc = (DirectInput8CreateOriginal)GetProcAddress(
      DInput8Dll, "DirectInput8Create");
}

void PrintModulesW() {
  AllocConsole();
  HMODULE ModuleHandle[128];
  DWORD ByteNeeded;

  if (EnumProcessModules(GetCurrentProcess(), ModuleHandle,
                         sizeof(ModuleHandle), &ByteNeeded)) {
    for (unsigned int i = 0; i < (ByteNeeded / sizeof(HMODULE)); i++) {
      wchar_t ModuleName[MAX_PATH];

      if (GetModuleFileNameExW(GetCurrentProcess(), ModuleHandle[i], ModuleName,
                               sizeof(ModuleName) / sizeof(wchar_t))) {

        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), ModuleName,
                      wcslen(ModuleName), nullptr, nullptr);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, nullptr,
                      nullptr);
      }
    }
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    InitW();
    PrintModulesW();

  } else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    ;
  return TRUE;
}
