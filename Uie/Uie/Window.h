
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_WINDOW_H

#define _CLASS_UIE_WINDOW_H

#include "UieDLL.h"

#include "WindowMessageHandler.h"

#include <unordered_map>
#include <cstdint>
#include <string>
#include <utility>
#include <Windows.h>

namespace Uie
{
	class UIE_DLL Window final
	{
	public:
		static const auto NoHandler{static_cast<LRESULT>(-1)};

		enum class ClassStyle : UINT
		{
			ByteAlignClient = CS_BYTEALIGNCLIENT,
			ByteAlignWindow = CS_BYTEALIGNWINDOW,
			ClassDeviceContext = CS_CLASSDC,
			DoubleClick = CS_DBLCLKS,
			DropShadow = CS_DROPSHADOW,
			GlobalClass = CS_GLOBALCLASS,
			HorizontalRedraw = CS_HREDRAW,
			VerticalRedraw = CS_VREDRAW,
			NoClose = CS_NOCLOSE,
			OwnDeviceContext = CS_OWNDC,
			ParentDeviceContext = CS_PARENTDC,
			SaveBit = CS_SAVEBITS
		};

		enum class Style : DWORD
		{
			Border = WS_BORDER,
			Caption = WS_CAPTION,
			Child = WS_CHILD,
			ClipChild = WS_CLIPCHILDREN,
			ClipSibling = WS_CLIPSIBLINGS,
			Disabled = WS_DISABLED,
			DialogFrame = WS_DLGFRAME,
			Group = WS_GROUP,
			HorizontalScrollBar = WS_HSCROLL,
			VerticalScrollBar = WS_VSCROLL,
			Maximized = WS_MAXIMIZE,
			Minimized = WS_MINIMIZE,
			MaximizeBox = WS_MAXIMIZEBOX,
			MinimizeBox = WS_MINIMIZEBOX,
			Titled = WS_TILED,
			TitledWindow = WS_TILEDWINDOW,
			Popup = WS_POPUP,
			PopupWindow = WS_POPUPWINDOW,
			ResizingFrame = WS_SIZEBOX,
			SystemMenu = WS_SYSMENU,
			TabStop = WS_TABSTOP,
			Visible = WS_VISIBLE
		};

		enum class ExtendedStyle : DWORD
		{
			Empty = 0,
			AcceptFile = WS_EX_ACCEPTFILES,
			AppWindow = WS_EX_APPWINDOW,
			Topmost = WS_EX_TOPMOST,
			ClientEdge = WS_EX_CLIENTEDGE,
			Composited = WS_EX_COMPOSITED,
			HelpMenu = WS_EX_CONTEXTHELP,
			TakeParentFlow = WS_EX_CONTROLPARENT,
			DoubleBorder = WS_EX_DLGMODALFRAME,
			Layered = WS_EX_LAYERED,
			RTLLayout = WS_EX_LAYOUTRTL,
			LeftAligned = WS_EX_LEFT,
			RightAligned = WS_EX_RIGHT,
			LeftScrollBar = WS_EX_LEFTSCROLLBAR,
			RightScrollBar = WS_EX_RIGHTSCROLLBAR,
			LTRReading = WS_EX_LTRREADING,
			RTLReading = WS_EX_RTLREADING,
			MDIChiled = WS_EX_MDICHILD,
			NoActivate = WS_EX_NOACTIVATE,
			NoInheritLayout = WS_EX_NOINHERITLAYOUT,
			NoParentNotify = WS_EX_NOPARENTNOTIFY,
			NoBitmapBuffer = WS_EX_NOREDIRECTIONBITMAP,
			OverlappedWindow = WS_EX_OVERLAPPEDWINDOW,
			PaletteWindow = WS_EX_PALETTEWINDOW,
			StaticEdge = WS_EX_STATICEDGE,
			ToolWindow = WS_EX_TOOLWINDOW,
			Transparent = WS_EX_TRANSPARENT,
			WindowEdge = WS_EX_WINDOWEDGE
		};

		enum class SizingMode : bool
		{
			ClientAreaOnly = true,
			EntireArea = false
		};

		enum class Visibility : int
		{
			ForceMinimize = SW_FORCEMINIMIZE,
			Hide = SW_HIDE,
			Maximize = SW_MAXIMIZE,
			Minimize = SW_MINIMIZE,
			Restore = SW_RESTORE,
			Show = SW_SHOW,
			ShowDefault = SW_SHOWDEFAULT,
			ShowMaximized = SW_SHOWMAXIMIZED,
			ShowMinimized = SW_SHOWMINIMIZED,
			ShowMinimizedNoActive = SW_SHOWMINNOACTIVE,
			ShowNoActive = SW_SHOWNA,
			ShowNormal = SW_SHOWNORMAL,
			ShowNormalNoActive = SW_SHOWNOACTIVATE
		};

		struct Attribute
		{
		public:
			int32_t nX;
			int32_t nY;
			uint32_t nWidth;
			uint32_t nHeight;
			SizingMode eSizingMode;
			HMENU hMenu;
			HICON hIcon;
			HCURSOR hCursor;
			HBRUSH hBackgroundBrush;
			HWND hParentWindow;
			LPCWSTR pMenuName;
			std::wstring sClassName;
			std::wstring sTitleText;
			ClassStyle eClassStyle;
			Window::Style eStyle;
			Window::ExtendedStyle eExtendedStyle;
			LPVOID pExtraPointer;
		};

		struct SizeInfo
		{
			int32_t nEntireX;
			int32_t nEntireY;
			uint32_t nEntireWidth;
			uint32_t nEntireHeight;
			uint32_t nClientWidth;
			uint32_t nClientHeight;
		};

	private:
		static std::unordered_map<HWND, Window *> sWindowMap;
		static std::unordered_map<UINT, std::vector<WindowMessageHandler *>> sGlobalHandlerListMap;
		std::unordered_map<UINT, std::vector<WindowMessageHandler *>> sHandlerListMap;
		SizeInfo sSizeInfo{0, 0, 0, 0, 0, 0};
		HINSTANCE hInstance{nullptr};
		HWND hHandle{nullptr};
		HDC hContext{nullptr};
		std::wstring sClassName;
		BYTE nColorBit{0};
		BYTE nDepthBit{0};
		BYTE nStencilBit{0};

	public:
		Window() = default;
		Window(const Window &sSrc) = delete;
		~Window();

	public:
		Window &operator=(const Window &sSrc) = delete;

	public:
		inline SizeInfo &sizeInfo();
		inline const SizeInfo &sizeInfo() const;
		inline HINSTANCE instance() const;
		inline HWND handle() const;
		inline HDC context() const;
		inline const std::wstring &className() const;
		inline BYTE colorBit() const;
		inline BYTE depthBit() const;
		inline BYTE stencilBit() const;
		inline bool created() const;
		inline bool contextCreated() const;
		void destroy();
		bool create(const Attribute &sAttribute);
		void destroyContext();
		bool createContext(BYTE nColorBit, BYTE nDepthBit, BYTE nStencilBit);
		bool setVisible(Visibility eNewVisibility);
		void setFileDraggable(bool bNewDraggable);
		bool setTitle(const std::wstring &sNewTitle);
		bool moveWindow(int nNewX, int nNewY, int nNewWidth, int nNewHeight, bool bRepaint = true);
		void registerHandler(WindowMessageHandler *pNewWindowMessageHandler);
		void unregisterHandler(WindowMessageHandler *pNewWindowMessageHandler);
		void unregisterHandlerAll();
		bool peekMessage();
		WPARAM loopMessage();
		LRESULT handleMessage(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
		static Window *findWindow(HWND hWindow);
		static void registerGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler);
		static void unregisterGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler);
		static void unregisterGlobalHandlerAll();
		static LRESULT CALLBACK windowMessageProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
	};

	inline Window::SizeInfo &Window::sizeInfo()
	{
		return this->sSizeInfo;
	}

	inline const Window::SizeInfo &Window::sizeInfo() const
	{
		return this->sSizeInfo;
	}

	inline HINSTANCE Window::instance() const
	{
		return this->hInstance;
	}

	inline HWND Window::handle() const
	{
		return this->hHandle;
	}

	inline HDC Window::context() const
	{
		return this->hContext;
	}

	inline const std::wstring &Window::className() const
	{
		return this->sClassName;
	}

	inline BYTE Window::colorBit() const
	{
		return this->nColorBit;
	}

	inline BYTE Window::depthBit() const
	{
		return this->nDepthBit;
	}

	inline BYTE Window::stencilBit() const
	{
		return this->nStencilBit;
	}

	inline bool Window::created() const
	{
		return this->hHandle != nullptr;
	}

	inline bool Window::contextCreated() const
	{
		return this->hContext != nullptr;
	}

	template<class T> inline constexpr T combineEnum(T tFirst)
	{
		return tFirst;
	}

	template<class T, class ...P> inline constexpr T combineEnum(T tFirst, P ...tSecond)
	{
		return static_cast<T>(static_cast<std::underlying_type_t<T>>(tFirst) | static_cast<std::underlying_type_t<T>>(combineEnum(static_cast<T>(tSecond)...)));
	}
}

#endif