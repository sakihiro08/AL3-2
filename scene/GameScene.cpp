#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
 
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	 texturehandle_ = TextureManager::Load("sagume.jpg");
	 sprite_ = Sprite::Create(texturehandle_, {100, 50});
	 //texturehandle_ = TextureManager::Load("sagume.jpg");
	 model_ = Model::Create();
	 //拡大
	 worldTransform_.scale_={5.0f, 5.0f, 5.0f};
	 //回転
	 worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	//移動
	 worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	 worldTransform_.Initialize();
	 viewProjection_.Initialize();
	//サウンド
	 soundDatahandle_ = audio_->LoadWave("mokugyo.wav");
	//音声
	 audio_->PlayWave(soundDatahandle_);
	 voiceHandle_ = audio_->PlayWave(soundDatahandle_, true);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void GameScene::Update() { 
	XMFLOAT2 position = sprite_->GetPosition();
   /*position.x += 2.0f;
   position.y += 1.0f;*/
sprite_->SetPosition(position);
   if (input_ -> TriggerKey(DIK_SPACE))
   {
	   audio_->StopWave(voiceHandle_);
   }
   debugText_->Print("tinha saikouno ounanoda",50,50,1.0f);
   debugText_->SetPos(50, 70);
   debugText_->Printf("year%d", 2022);
   value_++;
   char str[100];
   sprintf_s(str, "scale %f", scale_);
   debugText_->Print(str, 200, 10, 2);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	/*sprite_->Draw();*/
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, texturehandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	//model_->Draw(worldTransform_, viewProjection_, texturehandle_);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
