#pragma once

#include <vector>

/*
*	目的 :	描画対象のリストを保持し、Drawコールを特定の場所でまとめて出すためのクラス
*	理由 :	①Window.cpp(藤岡製not標準Windows)でのDraw内記述でSceneDrawがRenderTargetのクリア前に行われている
			(これではレンダーターゲットに反映されない)
*			②そもそもDrawコールの実装内容がRenderingEngine(藤岡製)の***_Listへのpush_backになっている
*			(つまり***_List->render()以外のグローバルなDrawコールは全部無視される)
*	結論 :	RenderingEngineのDrawコールは実質push_back命令の実装になっているのでそれに合わせた記述が必要
*			また、機能追加する際はRenderingEngine側に専用の***_Listを作成しなければならない
*			(グローバル関数として好きなタイミングで呼べないので、静的なlibに手を加えなければいけない)
			このクラスは上記を満たすために存在する
*/

// 前方宣言
namespace F_lib_Render
{
	class D2DTextParams;
	//class D2DFuncComponent;
}
namespace D2DFunctions
{
}
//ここまで

namespace F_lib_Render
{
	using namespace D2DFunctions;
	class D2DTextMng
	{
	public:
		D2DTextMng();
		~D2DTextMng();

		void Add(F_lib_Render::D2DTextParams* text);
		void Remove(F_lib_Render::D2DTextParams* text);
		void RemoveAll();
		void ChangeDrawOrder(F_lib_Render::D2DTextParams* text, int drawOrder);
		void Render();

	private:
		std::vector<F_lib_Render::D2DTextParams*> List;
	};

	//class D2DFuncMng
	//{
	//public:
	//	D2DFuncMng();
	//	~D2DFuncMng();

	//	void Add(D2DFuncComponent* comp);
	//	void Remove(F_lib_Render::D2DFuncComponent* comp);
	//	void RemoveAll();
	//	void ChangeDrawOrder(F_lib_Render::D2DFuncComponent* comp, int drawOrder);
	//	void Render();

	//private:
	//	std::vector<F_lib_Render::D2DFuncComponent*> List;
	//};

}