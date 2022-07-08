#include "D2DDrawMng.h"

#include "D2DText.h"
//#include "D2DFunctions.h"

using namespace F_lib_Render;
//using namespace D2DFunctions;

namespace F_lib_Render
{
#pragma region TextManager
	D2DTextMng::D2DTextMng()
	{
		// 何もしない
	}

	D2DTextMng::~D2DTextMng()
	{
		RemoveAll();
	}

	void D2DTextMng::Add(D2DTextParams * text)
	{
		// ソート済みの配列で挿入点を見つける
		int myDrawOrder = text->GetDrawOrder();
		auto iter = List.begin();
		for (;
			iter != List.end();
			++iter) {
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		// イテレータの位置の前に要素を挿入する
		List.insert(iter, text);
	}

	void D2DTextMng::Remove(D2DTextParams * text)
	{
		// DrawOrderの順番が崩れてしまうので、std::iter_swapしない
		// iterの位置を削除する
		auto iter = std::find(List.begin(), List.end(), text);
		List.erase(iter);

		// 文字表示は描画順をコントロールしたいので以下のswap処理は採用しない
		//auto iter = std::find(textList.begin(), textList.end(), text);
		//if (iter != textList.end()) {
		//	std::iter_swap(iter, textList.end() - 1);
		//	textList.pop_back();
		//}
	}

	void D2DTextMng::RemoveAll()
	{
		while (!List.empty()) {
			List.pop_back();
		}
	}

	void D2DTextMng::ChangeDrawOrder(D2DTextParams * text, int drawOrder)
	{
		auto iter = std::find(List.begin(), List.end(), text);
		if ((*iter)->GetDrawOrder() == drawOrder) {
			return;
		}
		// Note : 以下は少々無駄な処理をしていると思われるが、他に方法を思いつかない
		D2DTextParams* copy = *iter;
		List.erase(iter);
		Add(copy);
	}

	void D2DTextMng::Render()
	{
		if (List.size()) {
			for (auto&& t : List) {
				t->Draw();
			}
		}
	}
#pragma endregion TextManager


//#pragma region FuncManager
//	D2DFuncMng::D2DFuncMng()
//	{
//		// 何もしない
//	}
//
//	D2DFuncMng::~D2DFuncMng()
//	{
//		RemoveAll();
//	}
//
//
//	void D2DFuncMng::Add(D2DFuncComponent * comp)
//	{
//		// ソート済みの配列で挿入点を見つける
//		int myDrawOrder = comp->GetDrawOrder();
//		auto iter = List.begin();
//		for (;
//			iter != List.end();
//			++iter) {
//			if (myDrawOrder < (*iter)->GetDrawOrder()) {
//				break;
//			}
//		}
//		// イテレータの位置の前に要素を挿入する
//		List.insert(iter, comp);
//	}
//
//	void D2DFuncMng::Remove(D2DFuncComponent * comp)
//	{
//		auto iter = std::find(List.begin(), List.end(), comp);
//		List.erase(iter);
//	}
//
//	void D2DFuncMng::RemoveAll()
//	{
//		while (!List.empty()) {
//			List.pop_back();
//		}
//	}
//
//	void D2DFuncMng::ChangeDrawOrder(D2DFuncComponent * comp, int drawOrder)
//	{
//		auto iter = std::find(List.begin(), List.end(), comp);
//		if ((*iter)->GetDrawOrder() == drawOrder) {
//			return;
//		}
//		// Note : 以下は少々無駄な処理をしていると思われるが、他に方法を思いつかない
//		D2DFuncComponent* copy = *iter;
//		List.erase(iter);
//		Add(copy);
//
//	}
//
//	void D2DFuncMng::Render()
//	{
//		if (List.size()) {
//			for (auto&& c : List) {
//				c->Render();
//			}
//		}
//	}
//#pragma endregion FuncManager
}