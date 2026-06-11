#pragma once

#include <Windows.h>
#include <vector>
#include <memory>

#include <d3d11.h>
#include "imgui/imgui.h"

namespace RBX::Visuals
{
	inline IDXGISwapChain* SwapChain;

	inline ID3D11Device* D3D11Device;
	inline ID3D11DeviceContext* D3D11Context;

	inline ID3D11RenderTargetView* D3D11RenderTargetView;
	inline ID3D11Texture2D* D3D11Texture;

	using tPresent = HRESULT(WINAPI*)(IDXGISwapChain* InSwapChain, UINT SyncInterval, UINT Flags);
	using tResizeBuffers = HRESULT(WINAPI*)(IDXGISwapChain* InSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	inline tPresent PresentOrg = nullptr;
	inline tResizeBuffers ResizeBuffersOrg = nullptr;
	inline WNDPROC WndProcOrg = nullptr;

	static HRESULT HookedPresent(
		IDXGISwapChain* InSwapChain,
		UINT SyncInterval,
		UINT Flags
	);

	static HRESULT HookedResizeBuffers(
		IDXGISwapChain* InSwapChain,
		UINT        BufferCount,
		UINT        Width,
		UINT        Height,
		DXGI_FORMAT NewFormat,
		UINT        SwapChainFlags
	);

	static LRESULT CALLBACK HookedWndProc(
		HWND Hwnd,
		UINT Message,
		WPARAM WParam,
		LPARAM LParam
	);

	inline bool UserInterface = false;
	inline float DpiScale = 1.0f;

	void Initialize();
}