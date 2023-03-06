#include <Windows.h>
#include <iostream>

void RedirectConsole() {
  AllocConsole();
  freopen_s((FILE **)stdin, "CONIN$", "r", stdin);
  freopen_s((FILE **)stdout, "CONOUT$", "w", stdout);
  freopen_s((FILE **)stdout, "CONOUT$", "w", stderr);
}
