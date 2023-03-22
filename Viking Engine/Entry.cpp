#pragma once
#pragma comment(lib, "Onecore.lib")

import JNX_Threading_Lib;
import <iostream>;
import <Windows.h>;
import <stdexcept>;

void main() {
	try {
		//auto threadingLibrary { LoadLibrary(L"Threading Engine.dll") };
		//if (!threadingLibrary)
		//	throw std::exception("ERR: Lib not found!\n");
		//
		//auto threadingEngineProc{ (JNX::CREATETE)GetProcAddress(threadingLibrary, "CreateThreadEngine") };
		//if (!threadingEngineProc) {
		//	FreeLibrary(threadingLibrary);
		//	throw std::exception("ERR: Proc not found!\n");
		//}
		//
		//JNX::IThreadEngine* threadEngine { &threadingEngineProc(10) };
		//if (threadEngine)
		//	threadEngine->test();
		//
		//FreeLibrary(threadingLibrary);



	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
	}
}