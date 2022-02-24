#include "pch.h"
#include "EventArgs.h"
#include <mutex>

namespace EventArgs
{
	DLL_EXPORT std::atomic<bool> hasNewQuote = false;
	DLL_EXPORT std::atomic<bool> hasOrderUpdate = true;
}
