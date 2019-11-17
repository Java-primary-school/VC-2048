/**
 * \file OwnerDrawButton.h
 *
 * \brief �Ի水ť��ʵ����
 *
 * \author
 */

#pragma once
#include "framework.h"
#include <iostream>
class COwnerDrawButton
{
public:
	COwnerDrawButton(LPCWSTR,);
	~COwnerDrawButton(void);
private:
	COwnerDrawButton(const COwnerDrawButton& OtherOwnerDrawButton);
	COwnerDrawButton& operator=(const COwnerDrawButton& OtherOwnerDrawButton);
public:
	/**
	 * \brief ˢ�¿ؼ�
	 */
	bool InvalidataCtrl();
public:
	/**
	 * \brief ������ť
	 * \param lpszCaption ������Ϊ��ť����ʾ�ı�
	 * \param lpszImage ������Ϊ��ť��λͼ·��
	 * \param rect ������Ϊ��ť������
	 * \param hParentWnd ������Ϊ��ť�ĸ����ھ��
	 * \param nID ������Ϊ��ť�Ŀؼ�ID
	 * \param lpszImage ������Ϊ��ť�ؼ�һ��״̬λͼ·��
	 */
	BOOL Create(LPCSTR lpszCaption, const RECT& rect, HWND hParentWnd, \
		UINT nID, LPCWSTR lpszImage, HINSTANCE hInstance);
	/**
	 * \brief ���ư�ť
	 * \param hDC ������Ϊ��ť�Ļ�����DC���
	 */
	void Draw(HDC hDC);
	void DrawFocusRect(HDC hDC, RECT& rcWnd);
	/**
	 * \brief ���ð�ť
	 * \param fEnable ������Ϊ���ð�ť�Ƿ����
	 */
	void EnableButton(bool fEnable);

	void OnLbuttonDown(WPARAM wParam, LPARAM lParam);
	void OnLbuttonUp(WPARAM wParam, LPARAM lParam);
	void OnLbuttonDBClick(WPARAM wParam, LPARAM lParam);
	void OnMouseMove(WPARAM wParam, LPARAM lParam);
	void OnMouseLeave(WPARAM wParam, LPARAM lParam);
private:
	/**
	 * \brief ��ť��Ϣ�ص�����
	 */
	static LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	enum STATE
	{
		STATE_UP,
		STATE_DOWN,
		STATE_FOCUS,
		STATE_DISABLE
	};
	WNDPROC     m_OldProc;//!��ť��Ĭ����Ϣ�ص�����
	HWND        m_hWnd;      //!�˰�ť�ľ��
	void   ShowButton();
	void   HideButton();
private:
	HBITMAP     m_hFourStateBitmap; //!��ť����ͨ��״̬λͼ
	BOOL        m_fRoundButton;  //!��ǰ�ؼ����ͣ�TRUEΪ��ť���ͣ�FALSEΪһ�����ʾλͼ�ؼ�
	BOOL        m_fTrackMouse;
	int         m_nButtonState;//!��ť�ĵ�ǰ״̬
	HFONT       m_hFont;//!�ؼ�����
	LPCWSTR     className;

};


