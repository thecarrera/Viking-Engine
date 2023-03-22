#pragma once

module JNX_Threading_Lib;
import JNX_threading_engine;
import <memory>;

static JNX::ThreadEngine* s_threadEngine;

static JNX::IThreadEngine& JNX::CreateThreadEngine(const unsigned int allocatedThreads) {
	try {
		if (!s_threadEngine)
			s_threadEngine = new ThreadEngine(allocatedThreads);
		return *s_threadEngine;
	}
	catch (const std::exception& const e){
		if (s_threadEngine)
			delete s_threadEngine;
			exit(-1);
	}
}