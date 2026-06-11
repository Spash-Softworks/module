#include "Hook.hpp"

#include <mutex>

#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"

#include "update.hpp"

HRESULT RBX::Visuals::HookedPresent(IDXGISwapChain* InSwapChain, UINT SyncInterval, UINT Flags)
{
	static std::once_flag call;
	std::call_once(call, []() {
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		Visuals::SwapChain->GetDesc(&SwapChainDesc);

		HDC hdc = GetDC(SwapChainDesc.OutputWindow);
		int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
		ReleaseDC(SwapChainDesc.OutputWindow, hdc);
		Visuals::DpiScale = dpi / 96.0f;

		if (!Visuals::D3D11RenderTargetView) {
			ID3D11Texture2D* Texture2D = nullptr;

			if (SUCCEEDED(Visuals::SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&Texture2D)))) {
				Visuals::D3D11Device->CreateRenderTargetView(Texture2D, nullptr, &Visuals::D3D11RenderTargetView);
				Texture2D->Release();
			}
		}

		ImGui_ImplWin32_Init(SwapChainDesc.OutputWindow);
		ImGui_ImplDX11_Init(Visuals::D3D11Device, Visuals::D3D11Context);

		ImFontConfig fontConfig{};

		fontConfig.SizePixels = 13.0f * DpiScale;
		io.Fonts->AddFontDefault(&fontConfig);

		style.ScaleAllSizes(DpiScale);
	});

	if (!Visuals::D3D11RenderTargetView) {
		ID3D11Texture2D* Texture2D = nullptr;

		if (SUCCEEDED(InSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&Texture2D)))) {
			Visuals::D3D11Device->CreateRenderTargetView(Texture2D, nullptr, &Visuals::D3D11RenderTargetView);
			Texture2D->Release();
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	ImGui::NewFrame();

	if (Visuals::UserInterface) {
		// render your ui here
		ImGui::ShowDemoWindow();
	}

	ImGui::Render();

	ImDrawData* data = ImGui::GetDrawData();

	Visuals::D3D11Context->OMSetRenderTargets(1, &Visuals::D3D11RenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(data);

	return Visuals::PresentOrg(InSwapChain, SyncInterval, Flags);
}

HRESULT RBX::Visuals::HookedResizeBuffers(IDXGISwapChain* InSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (Visuals::D3D11RenderTargetView) {
		Visuals::D3D11RenderTargetView->Release();
		Visuals::D3D11RenderTargetView = nullptr;
	}

	return Visuals::ResizeBuffersOrg(InSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT RBX::Visuals::HookedWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_KEYDOWN:
			if (wParam == VK_INSERT) {
				Visuals::UserInterface = !Visuals::UserInterface;
			}
			break;
		case WM_DPICHANGED:
			DpiScale = LOWORD(wParam) / 96.0f;
			break;
	}

	if (UserInterface && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return TRUE;
	}

	if (UserInterface)
	{
		switch (msg)
		{
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_SETCURSOR:
		case WM_INPUT:
			return TRUE;
		}
	}

	return CallWindowProcA(Visuals::WndProcOrg, hWnd, msg, wParam, lParam);
}

void RBX::Visuals::Initialize()
{
	uintptr_t VisualEngine = *reinterpret_cast<uintptr_t*>(RBX::Offsets::VisualEngine::Pointer);
	if (!VisualEngine) {
		return;
	}

	uintptr_t DeviceD3D11 = *reinterpret_cast<uintptr_t*>(VisualEngine + RBX::Offsets::VisualEngine::DeviceD3D11);
	if (!DeviceD3D11) {
		return;
	}

	Visuals::SwapChain = *reinterpret_cast<IDXGISwapChain**>(DeviceD3D11 + RBX::Offsets::VisualEngine::SwapChain);
	if (!Visuals::SwapChain) {
		return;
	}

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	if (FAILED(Visuals::SwapChain->GetDesc(&SwapChainDesc))) {
		return;
	}

	if (FAILED(Visuals::SwapChain->GetDevice(__uuidof(ID3D11Device), (void**)(&Visuals::D3D11Device)))) {
		return;
	}
	
	Visuals::D3D11Device->GetImmediateContext(&Visuals::D3D11Context);

	constexpr size_t VftableSize = 18;
	
	void** Vftable = *reinterpret_cast<void***>(Visuals::SwapChain);

	static void** ShadowVftable = new void* [VftableSize];
	memcpy(ShadowVftable, Vftable, sizeof(void*) * VftableSize);

	Visuals::PresentOrg = reinterpret_cast<Visuals::tPresent>(Vftable[8]);
	Visuals::ResizeBuffersOrg = reinterpret_cast<Visuals::tResizeBuffers>(Vftable[13]);

	ShadowVftable[8] = reinterpret_cast<void*>(&Visuals::HookedPresent);
	ShadowVftable[13] = reinterpret_cast<void*>(&Visuals::HookedResizeBuffers);

	*reinterpret_cast<void***>(Visuals::SwapChain) = ShadowVftable;

	Visuals::WndProcOrg = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(SwapChainDesc.OutputWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Visuals::HookedWndProc)));
}