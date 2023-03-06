#include <Windows.h>

void InjectDllW(LPCWSTR DllPath, LPCWSTR WindowName) {
  SIZE_T uDllPathLen = wcslen(DllPath) + 1;
  DWORD dwProcessID;
  HWND hWindow;
  HANDLE hProcess;
  LPVOID pDllPathMemory;
  HANDLE hLoadThread;

  hWindow = FindWindowW(NULL, WindowName);

  GetWindowThreadProcessId(hWindow, &dwProcessID);

  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);

  pDllPathMemory =
      VirtualAllocEx(hProcess, 0, uDllPathLen, MEM_COMMIT, PAGE_READWRITE);

  WriteProcessMemory(hProcess, pDllPathMemory, (LPVOID)DllPath, uDllPathLen, 0);

  hLoadThread =
      CreateRemoteThread(hProcess, 0, 0,
                         (LPTHREAD_START_ROUTINE)GetProcAddress(
                             GetModuleHandleA("Kernel32.dll"), "LoadLibraryW"),
                         pDllPathMemory, 0, 0);

  WaitForSingleObject(hLoadThread, INFINITE);

  VirtualFreeEx(hProcess, pDllPathMemory, uDllPathLen, MEM_RELEASE);
}