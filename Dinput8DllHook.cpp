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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    InitW();
  } else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    ;
  return TRUE;
}
