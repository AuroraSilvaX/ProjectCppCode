#include <Windows.h>

#include <dxgi.h>
#include <iostream>
#include <vector>
#include <wrl.h>
using namespace Microsoft::WRL;

void EnumrateOutputDisplayModesW(IDXGIOutput *output, DXGI_FORMAT format) {
  unsigned int count = 0;
  unsigned int flags = 0;

  output->GetDisplayModeList(format, flags, &count, nullptr);

  std::vector<DXGI_MODE_DESC> ModeList(count);
  output->GetDisplayModeList(format, flags, &count, &ModeList[0]);

  for (auto x : ModeList) {
    unsigned int n = x.RefreshRate.Numerator;
    unsigned int d = x.RefreshRate.Denominator;

    std::wcout << L"Width: " << x.Width << "\t" << L"Height: " << x.Height
               << "\t" << L"RefreshHZ: " << n / d << std::endl;
  }
}

std::vector<IDXGIOutput *> EnumerateOutputsW(IDXGIAdapter *adapter) {
  IDXGIOutput *pOutput = nullptr;
  std::vector<IDXGIOutput *> OutputList;
  for (unsigned int i = 0;
       adapter->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND; i++) {

    DXGI_OUTPUT_DESC desc;
    pOutput->GetDesc(&desc);
    std::wcout << desc.DeviceName << "\t"
               << (desc.AttachedToDesktop ? "Desktop" : "NoDesktop")
               << std::endl;
    OutputList.push_back(pOutput);
  }
  return OutputList;
}

std::vector<IDXGIAdapter *> EnumerateAdaptersW(void) {

  IDXGIFactory *pFactory = nullptr;
  IDXGIAdapter *pAdapter = nullptr;
  std::vector<IDXGIAdapter *> AdapterList;

  if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&pFactory))) {
    return AdapterList;
  }

  for (unsigned int i = 0;
       pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
    DXGI_ADAPTER_DESC ad;
    pAdapter->GetDesc(&ad);

    std::wcout << ad.Description << std::endl;
    AdapterList.push_back(pAdapter);
  }
    return AdapterList;
}
