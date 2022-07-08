#pragma once

//
// 次の参考サイトを元にデフォルトパラメータの設定方法を見直した(元の設計は修正コストが高かった)
// https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040
// Windows標準フォントビューワー
// https://p.rakda3.net/windows_font/
// 参考サイトではグローバルな機能として実装しているが、今回はコンポーネントとして使うことを前提として実装した
// UIに乗せる際に描画の有無と前後関係のコントロールが必要になると想定したからである。
// D2DText : プログラム中にインスタンス1つ
// D2DD2DTextParams : コンポーネントとして必要なクラスに所有させる
//
#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>


// lib指定
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//前方宣言
namespace F_lib_Render
{
	class D2DTextMng;
}
//ここまで

namespace F_lib_Render
{
	/* @brief
	*  フォントリストの配置とフォント名の配置は一致させること
	*/
	//=============================================================================
	//	フォントリスト
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
	//	フォント名
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
			L"ＭＳ Ｐゴシック",
			L"ＭＳ Ｐ明朝",
			L"ＭＳ ゴシック",
			L"ＭＳ 明朝",
			L"MS UI Gothic",
			L"メイリオ",
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
	//	フォント設定
	//=============================================================================
	struct FontData	//TextFormat, SolidBrushをまとめて設定
	{
		Font font;								// フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）,enum classで置き換えている
		IDWriteFontCollection* fontCollection;	// フォントコレクション（nullptr）
		DWRITE_FONT_WEIGHT fontWeight;			// フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
		DWRITE_FONT_STYLE fontStyle;			// フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
		DWRITE_FONT_STRETCH fontStretch;		// フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
		FLOAT fontSize;							// フォントサイズ（20, 30等）
		WCHAR const* localeName;				// ロケール名（L""）
		DWRITE_TEXT_ALIGNMENT textAlignment;	// テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, DWRITE_TEXT_ALIGNMENT_TRAILING：後, DWRITE_TEXT_ALIGNMENT_CENTER：中央, DWRITE_TEXT_ALIGNMENT_JUSTIFIED：行いっぱい）
		D2D1_COLOR_F Color;						// フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
		FLOAT Opacity;							// フォントの透明度(0.0~1.0f)

		// デフォルト設定
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
	//	テキストクラス
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
		
	private://ヘルパー
		std::wstring StringToWString(std::string str);	// stringをwstringへ変換する

	public:
		// Drawコール
		void DrawString(const std::string str, D2D1_POINT_2F pos,
			D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE);
		void DrawString(const std::string str, D2D1_RECT_F rect,
			D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE);
		
		//setter
		/* @brief フォント設定
		* @param[in]	struct FontData
		* @param[out]	FontData out_preFont 一つ前に設定されているフォント情報
		* @return		HRESUTL	処理結果
		*/
		HRESULT SetFont(FontData* set, FontData* out_preFont = nullptr);
		HRESULT SetFont(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight,
			DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize,
			WCHAR const* localeName, DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F color, FLOAT opacity
			, FontData* out_preFont = nullptr);
		// @brief 座標原点の変更
		void SetOrigin(ORIGIN pos);
		void ReverseYAxis(bool enable);
	private:
		// 生成メンバ : 各インスタンスは固有値を保持するものとする
		IDWriteTextFormat*		TextFormat;	// フォーマット情報 : struct FontDataで生成する
		ID2D1SolidColorBrush*	SolidBrush; // 描画色
		IDWriteTextLayout*		TextLayout;	// レイアウト
		FontData*				Setting;	// フォント設定
		//以下は同一シーンの全てのデータに適用されるので注意
		ORIGIN					Origin;		// 座標原点の位置
		bool					Y_Axis;		// Y座標の反転
		// 外部インスタンスのポインタ
		ID2D1RenderTarget* RenderTarget;		// 利用するレンダーターゲット
		IDWriteFactory* DWriteFactory;			// 利用するインターフェース
	};

	//=============================================================================
	//	描画されるテキストに最低限必要な引数パラメータクラス
	//=============================================================================
	struct TextData
	{
		enum class FORM {
			Point,
			Rect,
		};

		std::string		Str;		// 表示文字列
		D2D1_POINT_2F	Pos;		// 文字列の開始点
		D2D1_RECT_F		Rect;		// 文字列を描画する長方形
		FORM			Form;		// D2DText.DrawString()のうち、どちらを使うか指定
		FontData*		Data;		// フォント情報(フォント名,サイズ,色など)
		
		TextData()	//初期値
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
		// デフォルト描画順
		static const int defDrawOrder;

	public:
		//引数有コンストラクタ、もしくはSetで各パラメータを設定すること。
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
		int	DrawOrder;	// 文字列の描画順を指定する(大きいほど手前表示)
		bool DrawFlag;	// Drawerに描画させるかを指示(true:描画する/false:しない)
		// 外部インスタンスのポインタ
		D2DText* TextComponent;
		F_lib_Render::D2DTextMng*	Manager;	// 描画管理クラス
	};
}


namespace
{
	// デバッグ用関数
	// 登録されているフォントを一覧で表示する
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

		//deleteされないのでメモリリークする。
		//修正は後ほど
	//	for (auto&& t : texts) {
	//		delete t;
	//	}
	}
}