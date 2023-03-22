#pragma once
module JNX_threading_engine;

#pragma region ThreadEngine
JNX::ThreadEngine::ThreadEngine(const UINT allocatedThreads)
try : queueSystem(std::make_shared<Queue_System>()), 
	  threadPool(std::make_unique<Thread_Pool>(allocatedThreads, this->queueSystem)) 
{}
catch (std::exception e) {
	OutputDebugStringA(e.what());
}
JNX::ThreadEngine::~ThreadEngine() 
try {

}
catch (std::exception& e) {
	OutputDebugStringA(e.what());
}

bool JNX::ThreadEngine::QueueJob(memory_order&& mem_order, bool*&& function, UINT argumentCount, ...) 
{	
	return false;
}

void JNX::ThreadEngine::Shutdown() {
	threadPool->Shutdown();
}

void JNX::ThreadEngine::test() {
	OutputDebugStringA("Hello!");
}
#pragma endregion

#pragma region Queue_System
JNX::Queue_System::Queue_System() {}
JNX::Queue_System::~Queue_System() {}

bool JNX::Queue_System::fetchNextTask(std::shared_ptr<JNX::Queue_System::Task> task) {
	try {
		task = this->queue.load();
		// Peek if exit here? how to handle?
		while (task && !this->queue.compare_exchange_strong(task, task->next));
		return true;
	}
	catch (std::exception& e) {
		return false;
	}
}
bool JNX::Queue_System::executeTask(std::shared_ptr<JNX::Queue_System::Task> task) {
	try {
		if (task->type & JNX::JOB) {
			std::shared_ptr<Job> job { std::dynamic_pointer_cast<Job>(task) };
			job->functionPointer(job->argumentCount, job->packedArguments);
		}
		else if (task->type & JNX::FENCE) {
			std::shared_ptr<Fence> fence{ std::dynamic_pointer_cast<Fence>(task) };
			//TODO: ++this->fenceTail;
			//TODO: --this->fSize;
		}
		return true;
	}
	catch (const std::exception& const e) {
		return false;
	}
}
#pragma endregion

#pragma region Thread_Pool
JNX::Thread_Pool::Thread_Pool(const UINT allocatedThreads, std::shared_ptr<Queue_System> queueSystem)
try : queueSystem(queueSystem) 
{
	for (size_t i = 0; i < allocatedThreads; ++i) {
		this->threads.push_back(std::jthread([queueSystem](std::stop_token stop_token) {
			while (!stop_token.stop_requested()) {
				std::shared_ptr<JNX::Queue_System::Task> task{};
				queueSystem->fetchNextTask(task);
				queueSystem->executeTask(task);
			};
		}));
	}
}
catch (std::exception& e)
{
	OutputDebugStringA(e.what());
}
JNX::Thread_Pool::~Thread_Pool() {}

void JNX::Thread_Pool::Shutdown() {
	for (auto& _thread : this->threads)
	{
		_thread.request_stop();
	}
}

#pragma endregion