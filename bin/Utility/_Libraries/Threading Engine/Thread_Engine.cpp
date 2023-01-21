#pragma once
module JNX_threading_engine;
using namespace JNX;

ThreadEngine::ThreadEngine(UINT allocatedThreads) {

}
ThreadEngine::~ThreadEngine() {

}
void ThreadEngine::test() {
	OutputDebugStringA("Hello!");
}