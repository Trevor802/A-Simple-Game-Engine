#pragma once
#include <Windows.h>
namespace Engine {
	class WaitableObject
	{
	public:
		typedef DWORD wait_t;
		static const wait_t WaitInfinite = INFINITE;
	};
}


