#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include<random>
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
	// texturehandle_ = TextureManager::Load("sagume.jpg");

	model_ = Model::Create();
	//乱数シード
	std::random_device seed_gen;
	//メルセンヌ
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//乱数範囲(座標)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
	//for (size_t i = 0; i < _countof(worldTransform_); i++) {
	//	//拡大
	//	worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
	//	//回転
	//	worldTransform_[i].rotation_ = {rotDist(engine), rotDist(engine), rotDist(engine)};
	//	//移動
	//	worldTransform_[i].translation_ = {posDist(engine), posDist(engine), posDist(engine)};
	//worldTransform_.Initialize();
		//	//親0番
		//worldTransform_[0].Initialize();
		////子１番
		//worldTransform_[1].translation_ = {0, 4.5f, 0};
		//worldTransform_[1].parent_ = &worldTransform_[0];
		//worldTransform_[1].Initialize();
		//キャラクターの大元
	    worldTransform_[PartId::Root].Initialize();
		//脊髄
	    worldTransform_[PartId::Spine].translation_ = {0, 4.5f, 0};
	    worldTransform_[PartId::Spine].parent_ = &worldTransform_[PartId::Root];
	    worldTransform_[PartId::Spine].Initialize();
		//上半身
		//親Spine子chest
	    //キャラクターの大元
	   
	    //胸
	    worldTransform_[PartId::Chest].translation_ = {0, 0, 0};
	    worldTransform_[PartId::Chest].parent_ = &worldTransform_[PartId::Spine];
	    worldTransform_[PartId::Chest].Initialize();
	    //親Chest子Head
	    //キャラクターの大元
	    
	    //頭
	    worldTransform_[PartId::Head].translation_ = {0, 4.5f, 0};
	    worldTransform_[PartId::Head].parent_ = &worldTransform_[PartId::Chest];
	    worldTransform_[PartId::Head].Initialize();
	    //親Chest子ArmL
	    //キャラクターの大元
	 /*   worldTransform_[PartId::ArmL].Initialize();*/
	    //左
	    worldTransform_[PartId::ArmL].translation_ = {-4.5, 0, 0};
	    worldTransform_[PartId::ArmL].parent_ = &worldTransform_[PartId::Chest];
	    worldTransform_[PartId::ArmL].Initialize();
	    //親Chest子ArmR
	    //キャラクターの大元
	
	    //右
	    worldTransform_[PartId::ArmR].translation_ = {4.5, 0, 0};
	    worldTransform_[PartId::ArmR].parent_ = &worldTransform_[PartId::Chest];
	    worldTransform_[PartId::ArmR].Initialize();
		//下半身
	    //親spine子spine
	    //キャラクターの大元
	  ;
	    //尻
	    worldTransform_[PartId::Hip].translation_ = {0, -4.5f, 0};
	    worldTransform_[PartId::Hip].parent_ = &worldTransform_[PartId::Spine];
	    worldTransform_[PartId::Hip].Initialize();
	    //親spine子LegL
	    //キャラクターの大元
	//左足
	    worldTransform_[PartId::LegL].translation_ = {-3, -7.5f, 0};
	    worldTransform_[PartId::LegL].parent_ = &worldTransform_[PartId::Hip];
	    worldTransform_[PartId::LegL].Initialize();
	    //親spine子LegR
	    //キャラクターの大元

	    //左足
	    worldTransform_[PartId::LegR].translation_ = {3, -7.5f, 0};
	    worldTransform_[PartId::LegR].parent_ = &worldTransform_[PartId::Hip];
	    worldTransform_[PartId::LegR].Initialize();
	    
	//}
	/*viewProjection_.eye = {0, 0, -10};
	viewProjection_.target = {10, 0, 0};
	viewProjection_.up = {cosf(XM_PI / 4.0f), sinf(XM_PI / 4.0f), 0.0f};*/
	/*viewProjection_.fovAngleY = XMConvertToRadians(10.0f);*/
	/*viewProjection_.aspectRatio = 1.0f;
	viewProjection_.nearZ = 52.0f;
	viewProjection_.farZ = 53.0f;*/
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
  /* debugText_->Print("tinha saikouno ounanoda",50,50,1.0f);
   debugText_->SetPos(50, 70);
   debugText_->Printf("year%d", 2022);*/
   value_++;
   char str[100];
   char str2[100];
   char str3[100];
  /* sprintf_s(
	 str, "scale %f,%f,%f,", worldTransform_.scale_.x,
	 worldTransform_.scale_.y,worldTransform_.scale_.z);


   sprintf_s(str2, "rotasion %f,%f,%f,", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	 worldTransform_.rotation_.z);
   sprintf_s(
	 str3, "translation %f,%f,%f,", worldTransform_.translation_.x, worldTransform_.translation_.y,
	 worldTransform_.translation_.z);
   debugText_->Print(str, 200, 20, 2);
   debugText_->Print(str2, 200, 45, 2);
   debugText_->Print(str3, 200, 70, 2);*/
   //視点移動
   //{
	  // //支店の移動
	  // XMFLOAT3 viewAngle = {0, 0, 0};
	  // //視点の移動速さ
	  // const float KEYspeed = 0.2f;
	  // //押した方向
	  // if (input_->PushKey(DIK_W)) {
		 //  viewAngle = {0, 0, KEYspeed};
	  // } else if (input_->PushKey(DIK_S)) {
		 //  viewAngle = {0, 0, -KEYspeed};
	  // }

	  // //視点移動
	  // viewProjection_.eye.x += viewAngle.x;
	  // viewProjection_.eye.y += viewAngle.y;
	  // viewProjection_.eye.z += viewAngle.z;
	  // //行列の再計算
	  // viewProjection_.UpdateMatrix();
	  //// //でばっぐ
	   debugText_->SetPos(50, 50);
	   debugText_->Printf(
		 "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

 /*  }*/
   ////注視点移動
   //{
	  // //支店の移動
	  // XMFLOAT3 viewAngle = {0, 0, 0};
	  // //注視点の移動速さ
	  // const float ktargetspeed = 0.2f;
	  // //押した方向
	  // if (input_->PushKey(DIK_LEFT)) {
		 //  viewAngle = {ktargetspeed, 0, 0};
	  // } else if (input_->PushKey(DIK_RIGHT)) {
		 //  viewAngle = {-ktargetspeed, 0, 0};
	  // }

	  // //注視点移動
	  // viewProjection_.target.x += viewAngle.x;
	  // viewProjection_.target.y += viewAngle.y;
	  // viewProjection_.target.z += viewAngle.z;
	  // //行列の再計算
	  // viewProjection_.UpdateMatrix();
	  // //でばっぐ
	   debugText_->SetPos(50, 70);
	   debugText_->Printf(
		 "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
   /*}*/
   ////上方向
   //{
	  // //上方向の回転
	  // const float kupRotspeed = 0.05f;


	 
	  // //押した方向
	  // if (input_->PushKey(DIK_SPACE)) {
		 //  viewAngle += kupRotspeed;
	  //  //2πをこえたら戻れ
		 // viewAngle = fmodf(viewAngle,XM_2PI);
	  // }

	  // //上方向の計算
	  // viewProjection_.up = {cosf(viewAngle), sinf(viewAngle),0.0f};
	  //
	  // //行列の再計算
	  // viewProjection_.UpdateMatrix();
	  // //でばっぐ
	   debugText_->SetPos(50, 90);
	   debugText_->Printf(
		 "target:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y,
		 viewProjection_.up.z);
   //}
   //fov変更
   //if (input_->PushKey(DIK_UP)) {
	  // viewProjection_.fovAngleY += 0.01f;
	  //
	  // viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
   //    
   //} else if (input_->PushKey(DIK_DOWN)){
	  // viewProjection_.fovAngleY -= 0.01f;
	  // viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, 0.01f);
   //}
   ////行列の再計算
   //viewProjection_.UpdateMatrix();
   ////でばっぐ
   debugText_->SetPos(50, 110);
   debugText_->Printf("fovAngleY(Degree):%f", XMConvertToDegrees(viewProjection_.fovAngleY));
 /*   クリップ距離変更*/
   //{
	  // if (input_->PushKey(DIK_UP)) {
		 //  viewProjection_.nearZ += 0.1f;
	  // 

	  // } else if (input_->PushKey(DIK_DOWN)) {
		 //  viewProjection_.nearZ -= 0.1f;
	  // }
	  // //行列の再計算
	  // viewProjection_.UpdateMatrix();
	  // //でばっぐ
	  // debugText_->SetPos(50, 130);
	  // debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
   //}
   //キャラクターの移動
   { 
	   //移動ベクトル
	   XMFLOAT3 move = {0, 0, 0};
	   //移動速さ
	   const float kcharacterSpeed = 0.7f;
	   //押した方向で移動ベクトルを変更
	   if (input_->PushKey(DIK_LEFT)) {
		   move = {-kcharacterSpeed, 0, 0};
	   }
		   else if (input_->PushKey(DIK_RIGHT)) {
		   move = {kcharacterSpeed, 0, 0};
		   }
	  //注視
		   worldTransform_[PartId::Root].translation_.x += move.x;
		   worldTransform_[PartId::Root].translation_.y += move.y;
		worldTransform_[PartId::Root].translation_.z += move.z;
		   debugText_->SetPos(50, 150);
		debugText_->Printf("Root:%f,%f,%f", worldTransform_[PartId::Root].translation_.x ,
		     worldTransform_[PartId::Root].translation_.y,
		     worldTransform_[PartId::Root].translation_.z );
   }
   //上半身回転
   { 
	   const float kChestRotSpeed = 0.05f;
	   if (input_->PushKey(DIK_U)) {
			worldTransform_[PartId::Chest].rotation_.y -= kChestRotSpeed;
	   } else if (input_->PushKey(DIK_I)) {
		   worldTransform_[PartId::Chest].rotation_.y += kChestRotSpeed;
	   }

   }
   //↓半身回転
   {
	   const float kHipRotSpeed = 0.05f;
	   if (input_->PushKey(DIK_J)) {
		   worldTransform_[PartId::Hip].rotation_.y -= kHipRotSpeed;
	   } else if (input_->PushKey(DIK_K)) {
		   worldTransform_[PartId::Hip].rotation_.y += kHipRotSpeed;
	   }
   }
  /* worldTransform_[0].UpdateMatrix();
   worldTransform_[1].UpdateMatrix();*/
   worldTransform_[PartId::Root].UpdateMatrix();
   worldTransform_[PartId::Spine].UpdateMatrix();
   worldTransform_[PartId::Head].UpdateMatrix();
   worldTransform_[PartId::Chest].UpdateMatrix();
   worldTransform_[PartId::ArmL].UpdateMatrix();
   worldTransform_[PartId::ArmR].UpdateMatrix();
   worldTransform_[PartId::Hip].UpdateMatrix();
   worldTransform_[PartId::LegL].UpdateMatrix();
   worldTransform_[PartId::LegR].UpdateMatrix();
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
	/*for (size_t i = 0; i < _countof(worldTransform_); i++) {
	model_->Draw(worldTransform_[i], viewProjection_, texturehandle_);*/
	/*model_->Draw(worldTransform_[PartId::Root], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::Spine], viewProjection_, texturehandle_)*/;
	model_->Draw(worldTransform_[PartId::Head], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::Chest], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::ArmL], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::ArmR], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::Hip], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::LegL], viewProjection_, texturehandle_);
	model_->Draw(worldTransform_[PartId::LegR], viewProjection_, texturehandle_);
	/*model_->Draw(worldTransform_[1], viewProjection_, texturehandle_);*/
	/*} */// 3Dオブジェクト描画後処理
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
