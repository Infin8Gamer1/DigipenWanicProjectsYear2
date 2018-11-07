//------------------------------------------------------------------------------
//
// File Name:	System.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class System
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Initialize the System (Windows, Event Handlers).
	// Params: 
	//   instance = Handle to the application instance.
	//   screenWidth = Width of the window in pixels.
	//   screenHeight = Height of the window in pixels.
	//   framerateCap = Maximum framerate.
	//   showWindow = Whether to show the window upon creation.
	//   debugConsole = Whether to create the debug console.
	void Initialize(HINSTANCE instance, unsigned screenWidth = 800, 
		unsigned screenHeight = 600, unsigned framerateCap = 200, 
		bool showWindow = true, bool debugConsole = true);

	// Update the System (Windows, Event Handlers).
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// End the frame and draw
	void Draw();

	// Shutdown the System (Windows, Event Handlers).
	void Shutdown();

	// Returns the handle for the window used by the program.
	HWND GetWindowHandle() const;

	// Sets the title of the window being used by Beta Framework.
	// Params: 
	//   text = The string that the window title will be set to.
	void SetWindowTitle(const std::string& text);

	// Does the window for this program still exist?
	bool DoesWindowExist() const;

	// Retrieve the instance of the System singleton.
	static System& GetInstance();

	// Default callback function is friend
	friend LRESULT CALLBACK WinCallBack(HWND hWnd, unsigned msg, WPARAM wp, LPARAM lp);

private:
	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	// This struct is used by Beta Framework to initialize the internal systems.
	// Create an instance of this struct and fill out the details to
	// initialize Beta Framework.
	struct SystemInfo
	{
		// Whether Beta Framework should create the window.
		// This is evaluated as a bool, 0 will not create the window, any other value will.
		bool createWindow;
		HWND windowHandle;

		// This is supplied as a parameter to WinMain().
		// Use the first parameter from WinMain().
		HINSTANCE appInstance;

		// This is supplied as a parameter to WinMain().
		// Use the fourth parameter from WinMain().
		bool show;

		// Specifies the width and height of the window created by Beta Framework.
		// Note that mCreateWindow must be a non-zero value for the window to be created.
		unsigned winWidth, winHeight;
		
		// Specify if a debug console should be created.
		bool createConsole;
		
		// Sets the Beta framework framerate controller's max framerate. Defaults to 120.
		unsigned maxFrameRate;
		
		// Specifies the message handling callback function.
		// If you are unsure, use NULL to use the default message handler.
		LRESULT(CALLBACK *winCallBack)(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

		// This is a bitfield for the class style options. Use
		//     CS_HREDRAW | CS_VREDRAW
		unsigned int classStyle;

		// This is a bitfield for the Window Style options. Use WS_OVERLAPPEDWINDOW if unsure.
		unsigned int windowStyle;
		
		// Specifies whether Beta Framework should handle the window for you.
		// This should be set to 1 or your window will not be responsive.
		bool handleWindowMessages;
	};

	class CustomCallback
	{
	public:
		CustomCallback(unsigned long MsgID, LRESULT(*pCallBack)(HWND hWin, unsigned msg, WPARAM wp, LPARAM lp));
		~CustomCallback();

	public:
		unsigned long mMsg;
		LRESULT(*mpCallBack)(HWND hWin, unsigned msg, WPARAM wp, LPARAM lp);
		int dummy;
	};

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Constructor/destructor are private to avoid accidental destruction/instantiation
	System();
	~System();

	// Disable copy constructor and assignment
	System(const System& other) = delete;
	System& operator=(const System& other) = delete;

	// Initializes the Beta systems. Uses the specified options to initialize Beta and
	// the functionality handled by Beta.
	// Params: 
	//   instance = Handle to the application instance.
	//   screenWidth = Width of the window in pixels.
	//   screenHeight = Height of the window in pixels.
	//   framerateCap = Maximum framerate.
	//   showWindow = Whether to show the window upon creation.
	//   debugConsole = Whether to create the debug console.
	void InitHelper(HINSTANCE instance, unsigned screenWidth, unsigned screenHeight, 
		unsigned framerateCap, bool showWindow, bool debugConsole);

	// Windows message pump callback function
	void AddCustomCallBack(unsigned long MsgID, LRESULT(*pCallBack)(HWND hWin, unsigned msg, WPARAM wp, LPARAM lp));
	void RemoveCustomCallBack(unsigned long MsgID, LRESULT(*pCallBack)(HWND hWin, unsigned msg, WPARAM wp, LPARAM lp));
	void ClearCustomCallBacks();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Call back functions
	std::list<CustomCallback> customCallbacks;

	// Other static data
	bool	appActive;
	bool	winExists;

	// Window information
	const char*	winClassName = "Window Class";
	SystemInfo systemInfo;
};
/*----------------------------------------------------------------------------*/
