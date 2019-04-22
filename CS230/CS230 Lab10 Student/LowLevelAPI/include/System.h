//------------------------------------------------------------------------------
//
// File Name:	System.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

struct GLFWwindow;

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
	//   screenWidth = Width of the window in pixels.
	//   screenHeight = Height of the window in pixels.
	//   framerateCap = Maximum framerate.
	//   showWindow = Whether to show the window upon creation.
	//   debugConsole = Whether to create the debug console.
	void Initialize(unsigned screenWidth = 800, unsigned screenHeight = 600, unsigned framerateCap = 200, 
		bool showWindow = true, bool debugConsole = true);

	// End the frame and draw
	void Draw();

	// Shutdown the System (Windows, Event Handlers).
	void Shutdown();

	// Set the title of the window being used by Beta Framework.
	// Params: 
	//   text = The string that the window title will be set to.
	void SetWindowTitle(const std::string& text);

	// Does the window for this program still exist?
	bool DoesWindowExist() const;

	// Test whether the application is in fullscreen mode.
	bool IsFullScreen() const;
	// Set whether the window is fullscreen.
	void SetFullScreen(bool fullscreen);

	// Set the resolution of the window.
	// Params:
	//   width = The new width of the window.
	//   height = The new height of the window.
	void SetResolution(unsigned width, unsigned height);

	// Retrieve the instance of the System singleton.
	static System& GetInstance();

	// GLFW callbacks
	friend void WinCloseCallback(GLFWwindow* window);

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

		// This is supplied as a parameter to WinMain().
		// Use the fourth parameter from WinMain().
		bool show;
		
		// Specify if a debug console should be created.
		bool createConsole;
		
		// Sets the Beta framework framerate controller's max framerate. Defaults to 120.
		unsigned maxFrameRate;
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
	//   width = Width of the window in pixels.
	//   height = Height of the window in pixels.
	//   framerateCap = Maximum framerate.
	//   showWindow = Whether to show the window upon creation.
	//   debugConsole = Whether to create the debug console.
	void InitHelper(unsigned width, unsigned height, 
		unsigned framerateCap, bool showWindow, bool debugConsole);

	// Window creation
	void CreateWindowGLFW(unsigned width, unsigned height, bool fullscreen);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Window information
	bool		winExists;
	SystemInfo	systemInfo;
	GLFWwindow* glfwWindow;
	bool fullscreen;
	int windowPositionX;
	int windowPositionY;
};
/*----------------------------------------------------------------------------*/
