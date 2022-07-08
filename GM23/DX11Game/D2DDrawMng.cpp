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
		// �������Ȃ�
	}

	D2DTextMng::~D2DTextMng()
	{
		RemoveAll();
	}

	void D2DTextMng::Add(D2DTextParams * text)
	{
		// �\�[�g�ς݂̔z��ő}���_��������
		int myDrawOrder = text->GetDrawOrder();
		auto iter = List.begin();
		for (;
			iter != List.end();
			++iter) {
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		// �C�e���[�^�̈ʒu�̑O�ɗv�f��}������
		List.insert(iter, text);
	}

	void D2DTextMng::Remove(D2DTextParams * text)
	{
		// DrawOrder�̏��Ԃ�����Ă��܂��̂ŁAstd::iter_swap���Ȃ�
		// iter�̈ʒu���폜����
		auto iter = std::find(List.begin(), List.end(), text);
		List.erase(iter);

		// �����\���͕`�揇���R���g���[���������̂ňȉ���swap�����͍̗p���Ȃ�
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
		// Note : �ȉ��͏��X���ʂȏ��������Ă���Ǝv���邪�A���ɕ��@���v�����Ȃ�
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
//		// �������Ȃ�
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
//		// �\�[�g�ς݂̔z��ő}���_��������
//		int myDrawOrder = comp->GetDrawOrder();
//		auto iter = List.begin();
//		for (;
//			iter != List.end();
//			++iter) {
//			if (myDrawOrder < (*iter)->GetDrawOrder()) {
//				break;
//			}
//		}
//		// �C�e���[�^�̈ʒu�̑O�ɗv�f��}������
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
//		// Note : �ȉ��͏��X���ʂȏ��������Ă���Ǝv���邪�A���ɕ��@���v�����Ȃ�
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