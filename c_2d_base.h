#pragma once
/**
* @file c_2d_base.h
* @brief 2D�p�̃x�[�X�N���X
* @author ���X�؁@���K
* @date 2020�`
* @details ������
*/

//-------------------------------------------------------------------------------
//�w�b�_�[�t�@�C���ǂݍ���
//-------------------------------------------------------------------------------
//*******************************************************************************
//-------------------------------------------------------------------------------
//�V�X�e���w�b�_�[
//-------------------------------------------------------------------------------
#include<algorithm>
#include<list>
//-------------------------------------------------------------------------------
//����w�b�_�[
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//����w�b�_�[
//-------------------------------------------------------------------------------
#include"c_base.h"
#include"c_texture_animation.h"

//*******************************************************************************

//-------------------------------------------------------------------------------
//�N���X��`
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
class C_2d_Base : public CBase
{
private:
	//*******************************************************************************
	//�ÓI�����o�ϐ�
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//�萔
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//��萔
	//-------------------------------------------------------------------------------
	//! ���_�o�b�t�@
	static ID3D11Buffer* sm_vertex_buffer;
	//! �������_���
	static VERTEX_3D sm_vertex[4];
	//!�@���_�o�b�t�@������������Ă��邩�H
	static bool sm_is_vertex_initialized;

	//*******************************************************************************
	//�����o�ϐ�
	//*******************************************************************************
	//! �|�W�V����
	D3DXVECTOR2 m_pos = D3DXVECTOR2(0.0f,0.0f);
	//! ��]�̒��S �����X�P�[�����ꂽ��̈ʒu���w�肵�Ȃ��Ƃ����Ȃ������t�@�����X���ĂȂ��̂ł�������m�肽���l�͌��邱�ƁB
	D3DXVECTOR2 m_rot_cent = D3DXVECTOR2(50.0f,50.0f);
	//! ��]
	FLOAT m_rot =  D3DXToRadian(0.0f);
	//! �X�P�[���̒��S�@�������_����������̈ʒu���w�肵�Ȃ��Ƃ����Ȃ������t�@�����X���ĂȂ��̂ł�������m�肽���l�͌��邱�ƁB
	D3DXVECTOR2 m_scale_cent = D3DXVECTOR2(0.0f,0.0f);
	//! �X�P�[��
	D3DXVECTOR2 m_scale = D3DXVECTOR2(100.0f,100.0f);
	//! �e�N�X�`���A�j���[�V����
	C_Texture_Animation* m_tex_anim = nullptr;
	
	//�e�N�X�`��
	ID3D11ShaderResourceView* m_texture = nullptr;
	//! �_�ł����邩
	bool mb_should_flash = false;
	//! �_�Ŏ��̃t���[���J�E���^�[
	int m_flash_counter = 0;
	//! �_�ŃX�s�[�h
	int m_flash_speed = 60;
	//! �_�Ő؂�ւ� true:�_���@false:����
	bool mb_flash_switcher = false;
	//! �J���[
	D3DXVECTOR4 m_color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//! ���_���
protected:VERTEX_3D m_vertex[4];
public:
	//*******************************************************************************
	//�����o�[�֐�
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//�R���X�g���N�^
	//-------------------------------------------------------------------------------
	C_2d_Base() = delete;

	/**
* @brief �Œ���̐ݒ�ŏ����������N���X�𐶐�
* @param[in] ID3D11ShaderResourceView*(a_texture) �e�N�X�`��
* @param[in] D3DXVECTOR2(a_pos) �ʒu
* @param[in] FLOAT(a_rot) ��]
* @param[in] D3DXVECTOR2(a_scale) �X�P�[��
* @details scale�Ƀ}�C�i�X�̒l���������ꍇ�����J�����O�̉e���ŕ\������Ȃ���������܂��B�ǂ����Ă����]�������̂�\���������ꍇ�̓J�����O
			�̐ݒ�������ł������Ă��������B
			�@�܂������ݒ�ł͉�]�̒��S�̓|���S���̒��S�A�X�P�[���̒��S�͍���Őݒ肳��܂��B
			   �A�j���[�V�����̐ݒ�͂����Ȃ��܂���B
*/
	C_2d_Base(ID3D11ShaderResourceView* a_texture ,const D3DXVECTOR2& a_pos, const FLOAT& a_rot, const D3DXVECTOR2& a_scale)
	{
		//���_���R�s�[
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
	//�R�s�[�R���X�g���N�^
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//�f�X�g���N�^
	//-------------------------------------------------------------------------------

	//*******************************************************************************
	//�Q�b�^�[�E�Z�b�^�[
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//�ÓI
	//-------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	//��ÓI
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

	//! ��ɉ�]�̒��S���摜�̒��S�ɂȂ�悤��scale�̕ύX���ɂ͉�]�̒��S�̕ύX�������ɍs���܂��B
	inline void Set_Scale(const D3DXVECTOR2& a_scale)
	{
		m_scale = a_scale;
		Calc_Rot_Center();
	}

	//! ��ɉ�]�̒��S���摜�̒��S�ɂȂ�悤��scale�̕ύX���ɂ͉�]�̒��S�̕ύX�������ɍs���܂��B
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
* @brief �F�̃A�h���X��Ԃ��܂�
* @return D3DXVECTOR4*�@�F�̃A�h���X
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
	//����
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//�ÓI
	//-------------------------------------------------------------------------------

/**
* @brief �����̒��_���𐶐�
* @details ���̃N���X��p����̃N���X���g���O�Ɉ�x�����ǂ����ŌĂяo���Ă��������B
*/
	static void Gen_Vertex();
	/**
	* @brief ���_���Ȃǂ̏I������
	* @details �o�b�t�@�̊J���Abool�̏������Ȃ�
	*/
	static void St_Uninit();




/**
* @brief 2D�ŕ`�悷��ׂ̊֐�
* @param[in] ID3D11Buffer*�@a_vertex_buffer�@���_�o�b�t�@
* @param[in] ID3D11ShaderResourceView* a_texture �e�N�X�`�����
* @param[in] VERTEX_3D a_vertex ���_�z�񁦕K���S�z��
* @param[in] D3DXVECTOR2 a_scaling_center �X�P�[�����O�̒��S
* @param[in] D3DXVECTOR2 a_scale �X�P�[�����O�l
* @param[in] D3DXVECTOR2 a_rotation_center ��]�̒��S
* @param[in] FLOAT a_rotation ��]
* @param[in] D3DXVECTOR2 a_translation ���s�ړ�
* @details ���O������֐����g�p���������p�ł��B�N���X���ɑ�ւ�����̂ł�������g�p���Ă��������B
*/
	static void Draw_2D(ID3D11Buffer* a_vertex_buffer, ID3D11ShaderResourceView*	a_texture, const VERTEX_3D(&a_vertex)[4], const D3DXVECTOR2& a_scaling_center, const D3DXVECTOR2& a_scale, const D3DXVECTOR2& a_rotation_center,
		const FLOAT& a_rotation, const D3DXVECTOR2& a_translation);

/**
* @brief ���S������̎��Ɏw��ʒu�����S�ƂȂ�悤�ɒ��������ʒu��Ԃ��܂��B
* @param[in] D3DXVECTOR2&(a_target_point) �w��ʒu
* @param[in] D3DXVECTOR2&(a_size) �T�C�Y���X�P�[��
* @return D3DXVECTOR2 ������̒l
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
* @brief x+�����ɉ��ɐ��񂵂Ĕz�u���܂��B
* @param[in] D3DXVECTOR2&(a_first_pos_left_up) ���ׂ鎞�̍ŏ��̈ʒu�����S������Ŏw��
* @param[in,out] std::list<C_2d_Base*>(a_target_list) ����Ώہ��K�����S������łȂ��Ɛ���ɓ����Ȃ��\��������܂�
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
	//��ÓI
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
* @brief 2D�pDraw�֐�
* @param[in] ID3D11ShaderResourceView* a_texture �e�N�X�`�����
* @details ��static�ŃI�[�o�[���[�h���ꂽ�֐�������܂��B�ڍׂ͂�������Q�Ƃ��Ă��������B
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
	//����
	//*******************************************************************************
	//-------------------------------------------------------------------------------
	//�ÓI
	//-------------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------------
	//��ÓI
	//-------------------------------------------------------------------------------
/**
* @brief �����o�[��VERTEX_3D�ɐF���Z�b�g����֐�
* @param[in] D3DXVECTOR4&(a_color) �Z�b�g�������F
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


	//��Xfade�̏����ɕς���
	void Flash()
	{
		if (mb_should_flash)
		{
			m_flash_counter++;
			if (mb_flash_switcher)
			{
				//�_������
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
				//��������
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