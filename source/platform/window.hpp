//-----------------------------------------------------------------------------
// MIT License
// 
// Copyright (c) 2017 Jeff Hutchinson
// Copyright (c) 2017 Tim Barnes
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _PLATFORM_WINDOW_H_
#define _PLATFORM_WINDOW_H_

#include <string>
#include "platform/input/iInputListener.hpp"
#include <jikken/jikken.hpp>

class IWindow : public IInputListener
{
	// Only the WindowManager class can allocate/deallocate Window
	// objects.
	friend class WindowManager;

public:
	virtual void onKeyPressEvent(const KeyPressEventData &data) override 
	{
		if (data.keyState == Input::KeyState::ePRESSED)
		{
			if (data.key == Input::Key::eESCAPE)
				toggleCursor();
		}
	}

	virtual void setTitle(const std::string &title) = 0;

	virtual bool shouldClose() const = 0;

	virtual void toggleCursor() = 0;

	virtual Jikken::NativeWindowData getJikkenNativeWindowData() = 0;

};

#endif