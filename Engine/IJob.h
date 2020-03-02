#pragma once
#include <Windows.h>
#include <functional>
namespace Engine {
	namespace JobSystem {
		struct IJob {
			virtual ~IJob() {};
			virtual bool RunJob() = 0;
		};

		struct JobFunc : IJob {
			std::function<void()> pFunc;

			JobFunc(std::function<void()> i_Func) : pFunc(i_Func) {};
			virtual bool RunJob() override {
				pFunc();
				return true;
			}
		};

		/*template <typename T>
		struct JobMemberFunc : IJob {
			T* pParent;
			void(T::* pFunc)(void*, DWORD);

			JobMemberFunc(T* i_Parent, void(T::* i_pFunc)(void*, DWORD))
				: pParent(i_Parent), pFunc(i_pFunc) {};
			virtual bool RunJob(void* i_Args, DWORD i_Index) override {
				if (!pParent) return false;
				(pParent->*pFunc)(i_Args, i_Index);
				return true;
			}
		};*/
	}
}

