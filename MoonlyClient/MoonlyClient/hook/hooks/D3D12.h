#pragma once

#include "../Hook.h"

#include <windows.h>
#include <cstdio>

#include <dxgi.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")
#include "../../../lib/imgui/imgui.h"
#include "../../../lib/imgui/backends/imgui_impl_win32.h"
#include "../../../lib/imgui/backends/imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>

#include "../../../lib/kiero/kiero.h"


class D3D12Hook : public Hook {
public:
	void install();
};

typedef long(__fastcall* PresentD3D12) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern PresentD3D12 oPresentD3D12;

typedef void(__fastcall* DrawInstancedD3D12)(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
extern DrawInstancedD3D12 oDrawInstancedD3D12;

typedef void(__fastcall* DrawIndexedInstancedD3D12)(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex);
extern DrawIndexedInstancedD3D12 oDrawIndexedInstancedD3D12;

extern void(*oExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
extern HRESULT(*oSignalD3D12)(ID3D12CommandQueue*, ID3D12Fence*, UINT64);

extern long __fastcall hookPresentD3D12(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
extern void __fastcall hookkDrawInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
extern void __fastcall hookDrawIndexedInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex);
extern void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);
extern HRESULT hookSignalD3D12(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value);
extern void release();

ID3D12Device* d3d12Device = nullptr;
ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
ID3D12Fence* d3d12Fence = nullptr;
UINT64 d3d12FenceValue = 0;
ID3D12CommandQueue* d3d12CommandQueue = nullptr;

PresentD3D12 oPresentD3D12;
DrawInstancedD3D12 oDrawInstancedD3D12;
DrawIndexedInstancedD3D12 oDrawIndexedInstancedD3D12;

void(*oExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
HRESULT(*oSignalD3D12)(ID3D12CommandQueue*, ID3D12Fence*, UINT64);

struct __declspec(uuid("189819f1-1db6-4b57-be54-1821339b85f7")) ID3D12Device;

struct FrameContext {
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12Resource* main_render_target_resource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};

uint32_t buffersCounts = -1;
FrameContext* frameContext;

bool shut = false;
bool menuOpen = true;

typedef long(__stdcall* Present12) (IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
Present12 oPresent12 = NULL;

typedef void(__stdcall* DrawInstanced)(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
DrawInstanced oDrawInstanced = NULL;

typedef void(__stdcall* DrawIndexedInstanced)(ID3D12GraphicsCommandList* dCommandList, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
DrawIndexedInstanced oDrawIndexedInstanced = NULL;

WNDPROC	oWndProc;
static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

long __fastcall hookPresentD3D12(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {
	static bool init = false;

	// ToDo : Menu keybinds

	if (!init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&d3d12Device))) {
			ImGui::CreateContext();

			unsigned char* pixels;
			int width, height;
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			io.Fonts->AddFontDefault();
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
			io.IniFilename = NULL;

			CreateEvent(nullptr, false, false, nullptr);

			DXGI_SWAP_CHAIN_DESC sdesc;
			pSwapChain->GetDesc(&sdesc);
			sdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			sdesc.OutputWindow = (HWND)FindWindow(0, L"Minecraft");
			sdesc.Windowed = ((GetWindowLongPtr((HWND)FindWindow(0, L"Minecraft"), GWL_STYLE) & WS_POPUP) != 0) ? false : true;

			buffersCounts = sdesc.BufferCount;
			frameContext = new FrameContext[buffersCounts];

			D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
			descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			descriptorImGuiRender.NumDescriptors = buffersCounts;
			descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

			if (d3d12Device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&d3d12DescriptorHeapImGuiRender)) != S_OK)
				return false;

			ID3D12CommandAllocator* allocator;
			if (d3d12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)) != S_OK)
				return false;

			for (size_t i = 0; i < buffersCounts; i++) {
				frameContext[i].commandAllocator = allocator;
			}

			if (d3d12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, NULL, IID_PPV_ARGS(&d3d12CommandList)) != S_OK ||
				d3d12CommandList->Close() != S_OK)
				return false;

			D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
			descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			descriptorBackBuffers.NumDescriptors = buffersCounts;
			descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			descriptorBackBuffers.NodeMask = 1;

			if (d3d12Device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&d3d12DescriptorHeapBackBuffers)) != S_OK)
				return false;

			const auto rtvDescriptorSize = d3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3d12DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();

			for (size_t i = 0; i < buffersCounts; i++) {
				ID3D12Resource* pBackBuffer = nullptr;

				frameContext[i].main_render_target_descriptor = rtvHandle;
				pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
				d3d12Device->CreateRenderTargetView(pBackBuffer, nullptr, rtvHandle);
				frameContext[i].main_render_target_resource = pBackBuffer;
				rtvHandle.ptr += rtvDescriptorSize;
			}

			ImGui_ImplWin32_Init((HWND)FindWindow(0, L"Minecraft"));
			ImGui_ImplDX12_Init(d3d12Device, buffersCounts,
				DXGI_FORMAT_R8G8B8A8_UNORM, d3d12DescriptorHeapImGuiRender,
				d3d12DescriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(),
				d3d12DescriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());

			ImGui_ImplDX12_CreateDeviceObjects();

			oWndProc = (WNDPROC)SetWindowLongPtr((HWND)FindWindow(0, L"Minecraft"), GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
		}

		init = true;
	}

	if (shut == false) {
		if (d3d12CommandQueue == nullptr)
			return oPresentD3D12(pSwapChain, SyncInterval, Flags);

		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// ImGui overlay
		{
			// ToDo

			ImGui::End();
		}

		FrameContext& currentFrameContext = frameContext[pSwapChain->GetCurrentBackBufferIndex()];
		currentFrameContext.commandAllocator->Reset();

		D3D12_RESOURCE_BARRIER barrier;
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		d3d12CommandList->Reset(currentFrameContext.commandAllocator, nullptr);
		d3d12CommandList->ResourceBarrier(1, &barrier);
		d3d12CommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
		d3d12CommandList->SetDescriptorHeaps(1, &d3d12DescriptorHeapImGuiRender);

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), d3d12CommandList);

		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		d3d12CommandList->ResourceBarrier(1, &barrier);
		d3d12CommandList->Close();

		d3d12CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&d3d12CommandList));
	}

	return oPresentD3D12(pSwapChain, SyncInterval, Flags);
}

void __fastcall hookkDrawInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {
	return oDrawInstancedD3D12(dCommandList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void __fastcall hookDrawIndexedInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex) {
	return oDrawIndexedInstancedD3D12(dCommandList, IndexCount, InstanceCount, StartIndex, BaseVertex);
}

void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
	if (!d3d12CommandQueue)
		d3d12CommandQueue = queue;

	oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
}

HRESULT hookSignalD3D12(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value) {
	if (d3d12CommandQueue != nullptr && queue == d3d12CommandQueue) {
		d3d12Fence = fence;
		d3d12FenceValue = value;
	}

	return oSignalD3D12(queue, fence, value);
}

void release() {
	shut = true;
	d3d12Device->Release();
	d3d12DescriptorHeapBackBuffers->Release();
	d3d12DescriptorHeapImGuiRender->Release();
	d3d12CommandList->Release();
	d3d12Fence->Release();
	d3d12CommandQueue->Release();
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		ImGui::GetIO().MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		ImGui::GetIO().MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		ImGui::GetIO().MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		ImGui::GetIO().MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		ImGui::GetIO().MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		ImGui::GetIO().MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		ImGui::GetIO().MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		ImGui::GetIO().MousePos.x = (signed short)(lParam); ImGui::GetIO().MousePos.y = (signed short)(lParam >> 16); return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

void D3D12Hook::install() {
	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		Utils::DebugLogOutput("[HookManager] Kiero initialized successfully!");

		kiero::bind(54, (void**)&oExecuteCommandListsD3D12, hookExecuteCommandListsD3D12);
		kiero::bind(58, (void**)&oSignalD3D12, hookSignalD3D12);
		kiero::bind(140, (void**)&oPresentD3D12, hookPresentD3D12);
		kiero::bind(84, (void**)&oDrawInstancedD3D12, hookkDrawInstancedD3D12);
		kiero::bind(85, (void**)&oDrawIndexedInstancedD3D12, hookDrawIndexedInstancedD3D12);
	}
	else
		Utils::DebugLogOutput("[HookManager] Cannot iniatialize Kiero!");
}