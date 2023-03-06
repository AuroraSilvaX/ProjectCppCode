#include <Windows.h>

#include <shellapi.h>

#pragma comment(lib, "Shell32.lib")

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
    if (argc < 2) {
        return 0;
    }

    for (unsigned char i = 1; i < argc; i++) {
        SHELLEXECUTEINFOW seiw = {sizeof(SHELLEXECUTEINFOW)};
        seiw.lpVerb = L"runas";
        seiw.lpFile = argv[i];
        seiw.nShow = SW_SHOWNORMAL;
        ShellExecuteExW(&seiw);
    }
    return 0;
}
