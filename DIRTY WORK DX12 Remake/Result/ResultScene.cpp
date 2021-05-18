//
// ResultScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

extern void ExitGame() noexcept;

// Initialize a variable and audio resources.
void ResultScene::Initialize()
{

}

// Allocate all memory the Direct3D and Direct2D resources.
void ResultScene::LoadAssets()
{
	resource_descriptors = make_unique<DescriptorHeap>(DXTK->PrimaryDevice, 1);
	ResourceUploadBatch resourceUpload(DXTK->PrimaryDevice);
	resourceUpload.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState);
	sprite_batch = make_unique<SpriteBatch>(DXTK->PrimaryDevice, resourceUpload, pd);

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	DXTK->CreateTextureSRV(DXTK->PrimaryDevice, resourceUpload, L"ƒNƒŠƒA‰æ–Ê.png",
		sprite_bg.ReleaseAndGetAddressOf(),
		resource_descriptors->GetCpuHandle(0));

	auto uploadResourceFinished = resourceUpload.End(DXTK->PrimaryCommandQueue);
	uploadResourceFinished.wait();
}

// Releasing resources required for termination.
void ResultScene::Terminate()
{

}

// Direct3D resource cleanup.
void ResultScene::OnDeviceLost()
{
	sprite_bg.Reset();
	resource_descriptors.reset();
	sprite_batch.reset();
}

// Restart any looped sounds here
void ResultScene::OnRestartSound()
{

}

// Updates the scene.
NextScene ResultScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.
	if (DXTK->KeyEvent->pressed.E) {
		return NextScene::TitleScene;
	}

	return NextScene::Continue;
}

// Draws the scene.
void ResultScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Clear(PrimaryAdapter, Colors::CornflowerBlue);

	ID3D12DescriptorHeap* heaps[] = { resource_descriptors->Heap() };
	DXTK->PrimaryCommandList->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite_batch->Begin(DXTK->PrimaryCommandList);

	sprite_batch->Draw(
		resource_descriptors->GetGpuHandle(0),
		XMUINT2(1280, 720),
		SimpleMath::Vector2(0.0f, 0.0f)
	);

	sprite_batch->End();

	DXTK->ExecutePrimaryCommandLists();
}
