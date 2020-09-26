#pragma once
/**
* @file c_2d_base.h
* @brief 2D用のベースクラス
* @author 佐々木　将幸
* @date 2020～
* @details 未完成
*/

//-------------------------------------------------------------------------------
//ヘッダーファイル読み込み
//-------------------------------------------------------------------------------
//*******************************************************************************
//-------------------------------------------------------------------------------
//システムヘッダー
//-------------------------------------------------------------------------------
#include<algorithm>
#include<list>
//-------------------------------------------------------------------------------
//他作ヘッダー
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//自作ヘッダー
//-------------------------------------------------------------------------------
#include"c_base.h"
#include"c_texture_animation.h"

//*******************************************************************************

//-------------------------------------------------------------------------------
//クラス定義
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
class C_2d_Base : public CBase
{
private:
	//*******************************************************************************
	//静的メンバ変数
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//定数
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//非定数
	//-------------------------------------------------------------------------------
	//! 頂点バッファ
	static ID3D11Buffer* sm_vertex_buffer;
	//! 初期頂点情報
	static VERTEX_3D sm_vertex[4];
	//!　頂点バッファが初期化されているか？
	static bool sm_is_vertex_initialized;

	//*******************************************************************************
	//メンバ変数
	//*******************************************************************************
	//! ポジション
	D3DXVECTOR2 m_pos = D3DXVECTOR2(0.0f,0.0f);
	//! 回転の中心 多分スケールされた後の位置を指定しないといけない※リファレンス見てないのでしっかり知りたい人は見ること。
	D3DXVECTOR2 m_rot_cent = D3DXVECTOR2(50.0f,50.0f);
	//! 回転
	FLOAT m_rot =  D3DXToRadian(0.0f);
	//! スケールの中心　多分頂点生成時からの位置を指定しないといけない※リファレンス見てないのでしっかり知りたい人は見ること。
	D3DXVECTOR2 m_scale_cent = D3DXVECTOR2(0.0f,0.0f);
	//! スケール
	D3DXVECTOR2 m_scale = D3DXVECTOR2(100.0f,100.0f);
	//! テクスチャアニメーション
	C_Texture_Animation* m_tex_anim = nullptr;
	
	//テクスチャ
	ID3D11ShaderResourceView* m_texture = nullptr;
	//! 点滅させるか
	bool mb_should_flash = false;
	//! 点滅時のフレームカウンター
	int m_flash_counter = 0;
	//! 点滅スピード
	int m_flash_speed = 60;
	//! 点滅切り替え true:点灯　false:消灯
	bool mb_flash_switcher = false;
	//! カラー
	D3DXVECTOR4 m_color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//! 頂点情報
protected:VERTEX_3D m_vertex[4];
public:
	//*******************************************************************************
	//メンバー関数
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//コンストラクタ
	//-------------------------------------------------------------------------------
	C_2d_Base() = delete;

	/**
* @brief 最低限の設定で初期化したクラスを生成
* @param[in] ID3D11ShaderResourceView*(a_texture) テクスチャ
* @param[in] D3DXVECTOR2(a_pos) 位置
* @param[in] FLOAT(a_rot) 回転
* @param[in] D3DXVECTOR2(a_scale) スケール
* @details scaleにマイナスの値を代入した場合多分カリングの影響で表示されない事があります。どうしても反転したものを表示したい場合はカリング
			の設定を自分でいじってください。
			　また初期設定では回転の中心はポリゴンの中心、スケールの中心は左上で設定されます。
			   アニメーションの設定はおこないません。
*/
	C_2d_Base(ID3D11ShaderResourceView* a_texture ,const D3DXVECTOR2& a_pos, const FLOAT& a_rot, const D3DXVECTOR2& a_scale)
	{
		//頂点情報コピー
		for (int i = 0; i < 4; i++)
		{
			m_vertex[i] = sm_vertex[i];
		}
		m_texture = a_texture;
		m_pos = a_pos;
		m_rot = a_rot;
		m_scale = a_scale;
		m_scale_cent = D3DXVECTOR2(0.0f, 0.0f);
		m_rot_cent = D3DXVECTOR2((m_scale.x / 2), (m_scale.y / 2));
		
	}



	//-------------------------------------------------------------------------------
	//コピーコンストラクタ
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//デストラクタ
	//-------------------------------------------------------------------------------

	//*******************************************************************************
	//ゲッター・セッター
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//静的
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//非静的
	//-------------------------------------------------------------------------------

	inline void Set_Pos(const D3DXVECTOR2& a_pos)
	{
		m_pos = a_pos;
	}

	inline void Add_Pos(const D3DXVECTOR2& a_pos)
	{
		m_pos += a_pos;
	}

	inline void Set_Rot(const FLOAT& a_rot)
	{
		m_rot = a_rot;
	}

	inline void Add_Rot(const FLOAT& a_rot)
	{
		m_rot += a_rot;
	}

	inline void Set_Color(const D3DXVECTOR4& a_color)
	{
		CBase::Set_Color(m_color, a_color);
	}

	inline void Add_Color(const D3DXVECTOR4& a_color)
	{
		CBase::Add_Color(m_color, a_color);
	}

	//! 常に回転の中心が画像の中心になるようにscaleの変更時には回転の中心の変更も同時に行われます。
	inline void Set_Scale(const D3DXVECTOR2& a_scale)
	{
		m_scale = a_scale;
		Calc_Rot_Center();
	}

	//! 常に回転の中心が画像の中心になるようにscaleの変更時には回転の中心の変更も同時に行われます。
	inline void Add_Scale(const D3DXVECTOR2& a_scale)
	{
		m_scale += a_scale;
		Calc_Rot_Center();
	}

	inline const D3DXVECTOR2& Get_Scale()
	{
		return m_scale;
	}
/**
* @brief 色のアドレスを返します
* @return D3DXVECTOR4*　色のアドレス
* @details 
*/
	inline D3DXVECTOR4* Get_Color_Address()
	{
		return &m_color;
	}

	void Set_Tex_Anim(C_Texture_Animation* a_tex_anim)
	{
		if (m_tex_anim != nullptr)
		{
			delete m_tex_anim;
			m_tex_anim = nullptr;
		}
		m_tex_anim = a_tex_anim;
	}

	C_Texture_Animation* Get_Tex_Anim_Module()
	{
		if (m_tex_anim != nullptr)
		{
			return m_tex_anim;
		}
		return nullptr;
	}
	//*******************************************************************************
	//操作
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//静的
	//-------------------------------------------------------------------------------

/**
* @brief 初期の頂点情報を生成
* @details このクラスや継承先のクラスを使う前に一度だけどこかで呼び出してください。
*/
	static void Gen_Vertex();
	/**
	* @brief 頂点情報などの終了処理
	* @details バッファの開放、boolの初期化など
	*/
	static void St_Uninit();




/**
* @brief 2Dで描画する為の関数
* @param[in] ID3D11Buffer*　a_vertex_buffer　頂点バッファ
* @param[in] ID3D11ShaderResourceView* a_texture テクスチャ情報
* @param[in] VERTEX_3D a_vertex 頂点配列※必ず４配列
* @param[in] D3DXVECTOR2 a_scaling_center スケーリングの中心
* @param[in] D3DXVECTOR2 a_scale スケーリング値
* @param[in] D3DXVECTOR2 a_rotation_center 回転の中心
* @param[in] FLOAT a_rotation 回転
* @param[in] D3DXVECTOR2 a_translation 平行移動
* @details ※外部から関数を使用したい時用です。クラス内に代替があるのでそちらを使用してください。
*/
	static void Draw_2D(ID3D11Buffer* a_vertex_buffer, ID3D11ShaderResourceView*	a_texture, const VERTEX_3D(&a_vertex)[4], const D3DXVECTOR2& a_scaling_center, const D3DXVECTOR2& a_scale, const D3DXVECTOR2& a_rotation_center,
		const FLOAT& a_rotation, const D3DXVECTOR2& a_translation);

/**
* @brief 中心が左上の時に指定位置が中心となるように調整した位置を返します。
* @param[in] D3DXVECTOR2&(a_target_point) 指定位置
* @param[in] D3DXVECTOR2&(a_size) サイズ※スケール
* @return D3DXVECTOR2 調整後の値
* @details 
*/
	static D3DXVECTOR2 Calc_Center_Left_Up_Adjust_Center(const D3DXVECTOR2& a_target_point,const D3DXVECTOR2& a_size)
	{
		D3DXVECTOR2 temp;
		temp.x = a_target_point.x - (a_size.x / 2);
		temp.y = a_target_point.y - (a_size.y / 2);
		return temp;
	}
/**
* @brief x+方向に横に整列して配置します。
* @param[in] D3DXVECTOR2&(a_first_pos_left_up) 並べる時の最初の位置※中心が左上で指定
* @param[in,out] std::list<C_2d_Base*>(a_target_list) 整列対象※必ず中心が左上でないと正常に動かない可能性があります
* @details 
*/
	static void Align_Horizontally_X_Plus(const D3DXVECTOR2& a_first_pos_left_up, std::vector<C_2d_Base*> a_target_vector)
	{
		D3DXVECTOR2 now_pos = a_first_pos_left_up;
		for (C_2d_Base* target : a_target_vector)
		{
			target->Set_Pos(now_pos);
			now_pos.x += target->Get_Scale().x;
		}
	}
	//-------------------------------------------------------------------------------
	//非静的
	//-------------------------------------------------------------------------------
	void Init()override
	{

	}

	void Uninit()override
	{

	}

	void Update()override
	{
		Flash();
	}

	void Draw()override
	{
		Draw_2D(m_texture);
	}

/**
* @brief 2D用Draw関数
* @param[in] ID3D11ShaderResourceView* a_texture テクスチャ情報
* @details ※staticでオーバーロードされた関数があります。詳細はそちらを参照してください。
*/
	void Draw_2D(ID3D11ShaderResourceView*	a_texture)
	{
		Set_Color_VERTEX_3D(m_color);
		Draw_2D(sm_vertex_buffer, a_texture, m_vertex, m_scale_cent, m_scale, m_rot_cent, m_rot, m_pos);
	}

	void Set_Flash(const bool a_flash,const int a_flash_speed)
	{
		mb_should_flash = a_flash;
		m_flash_speed = a_flash_speed;
		m_flash_counter = 0;
	}

private:
	//*******************************************************************************
	//操作
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//静的
	//-------------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------------
	//非静的
	//-------------------------------------------------------------------------------
/**
* @brief メンバーのVERTEX_3Dに色をセットする関数
* @param[in] D3DXVECTOR4&(a_color) セットしたい色
* @details 
*/
	void Set_Color_VERTEX_3D(const D3DXVECTOR4& a_color)
	{
		for (int i = 0; i < 4; i++)
		{
			m_vertex[i].Diffuse = a_color;
		}
	}
	
	inline void Calc_Rot_Center()
	{
		m_rot_cent = m_scale / 2;
	}


	//後々fadeの処理に変える
	void Flash()
	{
		if (mb_should_flash)
		{
			m_flash_counter++;
			if (mb_flash_switcher)
			{
				//点灯処理
				if (m_flash_counter <= m_flash_speed)
				{
					Add_Color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f / (float)m_flash_speed));
				}
				else
				{
					m_flash_counter = 0;
					mb_flash_switcher = false;
				}
			}
			else
			{
				//消灯処理
				if (m_flash_counter <= m_flash_speed)
				{
					Add_Color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, -1.0f / (float)m_flash_speed));
				}
				else
				{
					m_flash_counter = 0;
					mb_flash_switcher = true;
				}
			}

		}
	}


};