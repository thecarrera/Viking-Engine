#pragma once

module JNX_Threading_Lib;
import JNX_threading_engine;
import <memory>;

static std::shared_ptr<JNX::ThreadEngine> s_threadEngine;

static JNX::IThreadEngine& JNX::CreateThreadEngine(unsigned int allocatedThreads) {
	if (!s_threadEngine)
		s_threadEngine = std::make_shared<ThreadEngine>(allocatedThreads);
	return *s_threadEngine;
}

