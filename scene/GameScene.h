#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t texturehandle_ = 0;
	Sprite* sprite_ = nullptr;
	uint32_t soundDatahandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_[100];
	//カメラ上
	float viewAngle = 0.0f;
	uint32_t voiceHandle_ = 0;
	int32_t value_ = 0;
	// BGスプライト
	uint32_t textureHandleBG_ = 0;
	Sprite* spriteBG_ = nullptr;
	//ビュー
	ViewProjection viewProjection_;
	int scale_;

  public:
	enum PartId {
		Root,  //大元
		Spine, //脊髄
		Chest, //胸
		Head,  //あたま
		ArmL,  //左手
		ArmR,  //右手
		Hip,   //尻
		LegL,  //左足
		LegR,  //右足
	};
 
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
