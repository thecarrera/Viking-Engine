#pragma once
export module JNX_threading_engine;
import JNX_Threading_Lib;
#pragma comment(lib, "Onecore.lib")

import <iostream>;
import <Windows.h>;

export typedef unsigned int UINT;

export namespace JNX {
	class ThreadEngine : public IThreadEngine {
	public:
		ThreadEngine(UINT allocatedThreads);
		virtual ~ThreadEngine();
		void test();
	};
}