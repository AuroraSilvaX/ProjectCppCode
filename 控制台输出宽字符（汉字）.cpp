#include <stdio.h>
#include <wchar.h>

int main() {
  wchar_t s[256];
  wscanf_s(L"%s", s, s - 2);
  for (unsigned int n = 0; n < wcslen(s); n++) {
    wprintf(L"%c", s[n]);
  }
  return 0;
}
