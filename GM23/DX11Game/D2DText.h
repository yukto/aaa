#pragma once

//
// ���̎Q�l�T�C�g�����Ƀf�t�H���g�p�����[�^�̐ݒ���@����������(���̐݌v�͏C���R�X�g����������)
// https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040
// Windows�W���t�H���g�r���[���[
// https://p.rakda3.net/windows_font/
// �Q�l�T�C�g�ł̓O���[�o���ȋ@�\�Ƃ��Ď������Ă��邪�A����̓R���|�[�l���g�Ƃ��Ďg�����Ƃ�O��Ƃ��Ď�������
// UI�ɏ悹��ۂɕ`��̗L���ƑO��֌W�̃R���g���[�����K�v�ɂȂ�Ƒz�肵������ł���B
// D2DText : �v���O�������ɃC���X�^���X1��
// D2DD2DTextParams : �R���|�[�l���g�Ƃ��ĕK�v�ȃN���X�ɏ��L������
//
#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>


// lib�w��
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//�O���錾
namespace F_lib_Render
{
	class D2DTextMng;
}
//�����܂�

namespace F_lib_Render
{
	/* @brief
	*  �t�H���g���X�g�̔z�u�ƃt�H���g���̔z�u�͈�v�����邱��
	*/
	//=============================================================================
	//	�t�H���g���X�g
	//=============================================================================
	enum class Font
	{
		AndaleMono,
		Arial,
		ArialBlack,
		ComicSansMS,
		Courier,
		CourierNew,
		FixedSys,
		Georgia,
		Helvetica,
		Impact,
		LucidaConsole,
		MSPGothic,
		MSPMincho,
		MSGothic,
		MSMincho,
		MSUIGothic,
		Meiryo,
		MeiryoUI,
		SmallFonts,
		Symbol,
		System,
		Terminal,
		TimesNewRoman,
		TrebuchetMS,
		Verdana,
		Webdings
	};

	//=============================================================================
	//	�t�H���g��
	//=============================================================================
	namespace
	{
		const WCHAR* FontList[]
		{
			L"Andale Mono",
			L"Arial",
			L"Arial Black",
			L"Comic Sans MS",
			L"Courier",
			L"Courier New",
			L"FixedSys",
			L"Georgia",
			L"Helvetica",
			L"Impact",
			L"Lucida Console",
			L"�l�r �o�S�V�b�N",
			L"�l�r �o����",
			L"�l�r �S�V�b�N",
			L"�l�r ����",
			L"MS UI Gothic",
			L"���C���I",
			L"Meiryo UI",
			L"Small Fonts",
			L"Symbol",
			L"System",
			L"Terminal",
			L"Times New Roman",
			L"Trebuchet MS",
			L"Verdana",
			L"Webdings"
		};
	}

	//=============================================================================
	//	�t�H���g�ݒ�
	//=============================================================================
	struct FontData	//TextFormat, SolidBrush���܂Ƃ߂Đݒ�
	{
		Font font;								// �t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j,enum class�Œu�������Ă���
		IDWriteFontCollection* fontCollection;	// �t�H���g�R���N�V�����inullptr�j
		DWRITE_FONT_WEIGHT fontWeight;			// �t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
		DWRITE_FONT_STYLE fontStyle;			// �t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
		DWRITE_FONT_STRETCH fontStretch;		// �t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
		FLOAT fontSize;							// �t�H���g�T�C�Y�i20, 30���j
		WCHAR const* localeName;				// ���P�[�����iL""�j
		DWRITE_TEXT_ALIGNMENT textAlignment;	// �e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, DWRITE_TEXT_ALIGNMENT_TRAILING�F��, DWRITE_TEXT_ALIGNMENT_CENTER�F����, DWRITE_TEXT_ALIGNMENT_JUSTIFIED�F�s�����ς��j
		D2D1_COLOR_F Color;						// �t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w��j
		FLOAT Opacity;							// �t�H���g�̓����x(0.0~1.0f)

		// �f�t�H���g�ݒ�
		FontData()
		{
			font           = Font::Meiryo;
			fontCollection = nullptr;
			fontWeight     = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
			fontStyle      = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
			fontStretch    = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
			fontSize       = 20;
			localeName     = L"ja-jp";
			textAlignment  = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
			Color          = D2D1::ColorF(D2D1::ColorF::White);
			Opacity        = 1.0f;
		}
	};

	//=============================================================================
	//	�e�L�X�g�N���X
	//=============================================================================
	class D2DText
	{
	public:
		enum class ORIGIN {
			LEFTTOP,
			RIGHTTOP,
			LEFTBOTTOM,
			RIGHTBOTTOM,
			CENTER
		};
	public:
		D2DText(IDWriteFactory* factory, ID2D1RenderTarget* target);
		~D2DText();
		
	private://�w���p�[
		std::wstring StringToWString(std::string str);	// string��wstring�֕ϊ�����

	public:
		// Draw�R�[��
		void DrawString(const std::string str, D2D1_POINT_2F pos,
			D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE);
		void DrawString(const std::string str, D2D1_RECT_F rect,
			D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE);
		
		//setter
		/* @brief �t�H���g�ݒ�
		* @param[in]	struct FontData
		* @param[out]	FontData out_preFont ��O�ɐݒ肳��Ă���t�H���g���
		* @return		HRESUTL	��������
		*/
		HRESULT SetFont(FontData* set, FontData* out_preFont = nullptr);
		HRESULT SetFont(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight,
			DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize,
			WCHAR const* localeName, DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F color, FLOAT opacity
			, FontData* out_preFont = nullptr);
		// @brief ���W���_�̕ύX
		void SetOrigin(ORIGIN pos);
		void ReverseYAxis(bool enable);
	private:
		// ���������o : �e�C���X�^���X�͌ŗL�l��ێ�������̂Ƃ���
		IDWriteTextFormat*		TextFormat;	// �t�H�[�}�b�g��� : struct FontData�Ő�������
		ID2D1SolidColorBrush*	SolidBrush; // �`��F
		IDWriteTextLayout*		TextLayout;	// ���C�A�E�g
		FontData*				Setting;	// �t�H���g�ݒ�
		//�ȉ��͓���V�[���̑S�Ẵf�[�^�ɓK�p�����̂Œ���
		ORIGIN					Origin;		// ���W���_�̈ʒu
		bool					Y_Axis;		// Y���W�̔��]
		// �O���C���X�^���X�̃|�C���^
		ID2D1RenderTarget* RenderTarget;		// ���p���郌���_�[�^�[�Q�b�g
		IDWriteFactory* DWriteFactory;			// ���p����C���^�[�t�F�[�X
	};

	//=============================================================================
	//	�`�悳���e�L�X�g�ɍŒ���K�v�Ȉ����p�����[�^�N���X
	//=============================================================================
	struct TextData
	{
		enum class FORM {
			Point,
			Rect,
		};

		std::string		Str;		// �\��������
		D2D1_POINT_2F	Pos;		// ������̊J�n�_
		D2D1_RECT_F		Rect;		// �������`�悷�钷���`
		FORM			Form;		// D2DText.DrawString()�̂����A�ǂ�����g�����w��
		FontData*		Data;		// �t�H���g���(�t�H���g��,�T�C�Y,�F�Ȃ�)
		
		TextData()	//�����l
		{
			Pos = { 0,0 };
			Rect = { 0,0,10,10 };
			Form = FORM::Point;
			Data = new FontData();
		}
	};
	class D2DTextParams
	{
	protected:
		// �f�t�H���g�`�揇
		static const int defDrawOrder;

	public:
		//�����L�R���X�g���N�^�A��������Set�Ŋe�p�����[�^��ݒ肷�邱�ƁB
		D2DTextParams();
		D2DTextParams(TextData* data, int drawOrder = defDrawOrder);
		D2DTextParams(std::string str, D2D1_POINT_2F pos, D2D1_RECT_F rect, 
			TextData::FORM form, FontData* data, int drawOrder = defDrawOrder);
		~D2DTextParams();

		void SetData(TextData* data);
		void SetDrawOrder(int drawOrder);
		void SetDrawFlag(bool enable);
		void Draw();

		int GetDrawOrder() const { return DrawOrder; }
	public:
		TextData* TextSetting;
	private:
		int	DrawOrder;	// ������̕`�揇���w�肷��(�傫���قǎ�O�\��)
		bool DrawFlag;	// Drawer�ɕ`�悳���邩���w��(true:�`�悷��/false:���Ȃ�)
		// �O���C���X�^���X�̃|�C���^
		D2DText* TextComponent;
		F_lib_Render::D2DTextMng*	Manager;	// �`��Ǘ��N���X
	};
}


namespace
{
	// �f�o�b�O�p�֐�
	// �o�^����Ă���t�H���g���ꗗ�ŕ\������
	void DisplayFontList(D2D1_POINT_2F pos)
	{
		using namespace F_lib_Render;
		D2DTextParams* texts[static_cast<int>(Font::Webdings) + 1];
		TextData td[static_cast<int>(Font::Webdings) + 1];
		for (auto&& s : texts) {
			s = new D2DTextParams();
		}

		float y = 0;
		int num = 0;
		for (auto&& d : td) {
			d.Str = "This is Japan.";
			d.Pos = { pos.x,pos.y + y };
			y -= 25;
			d.Form = TextData::FORM::Point;
			d.Data->fontSize = 20;
			d.Data->font = static_cast<Font>(num);
			num++;
		}
		for (int i = 0; i < static_cast<int>(Font::Webdings) + 1; i++) {
			texts[i]->SetData(&td[i]);
		}

		//delete����Ȃ��̂Ń��������[�N����B
		//�C���͌�ق�
	//	for (auto&& t : texts) {
	//		delete t;
	//	}
	}
}