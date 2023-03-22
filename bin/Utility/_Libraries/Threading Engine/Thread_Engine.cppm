#pragma once
export module JNX_threading_engine;
import JNX_Threading_Lib;
#pragma comment(lib, "Onecore.lib")

import <iostream>;
import <Windows.h>;
import <utility>;
import <functional>;
import <vector>;
import <exception>;
import <thread>;
import <atomic>;

export typedef unsigned int UINT;


export namespace JNX {
	class Queue_System {
		friend class Thread_Pool;
		class Task {
		public:
			JOBTYPES type {};
			memory_order mem_order {};
			std::shared_ptr<Task> next {};

			Task();
			virtual ~Task();
		};
		class Job : public Task {
		public:
			void (*functionPointer)(UINT argumentCount, ...) {};
			va_list packedArguments {};
			UINT argumentCount {};

			Job() = delete;
			Job(void(*function)(UINT, ...), UINT argumentCount, ...);
			virtual ~Job();
		};
		class Fence : public Task {
			UINT id {};
			bool (*eventPointer)(UINT argumentCount, ...)  {};
			va_list eventArguments {};
		public:
			Fence();
			virtual ~Fence();
		};
		

		std::atomic<UINT> currentFence           {};
		std::atomic<std::shared_ptr<Task>> queue {};
	public:
		Queue_System();
		virtual ~Queue_System();
		void shutdown();

		void addJob();
		void addFence();
		bool fetchNextTask(std::shared_ptr<Task>);
		bool executeTask(std::shared_ptr<Task>);
		const UINT const getCurrentFence() { return currentFence; };
	};

	class Thread_Pool {
		std::shared_ptr<Queue_System> queueSystem {};
		std::vector<std::jthread> threads {};

	public:
		Thread_Pool() = delete;
		Thread_Pool(const UINT allocatedThreads, std::shared_ptr<Queue_System> queueSystem);
		virtual ~Thread_Pool();

		void Shutdown();
		void ShutdownThread(UINT threadID);
		void ShutdownThreadByIndex(UINT index);
	};

	class ThreadEngine : public IThreadEngine {
		std::shared_ptr<Queue_System> queueSystem {};
		std::unique_ptr<Thread_Pool>  threadPool  {};
	
	public:
		ThreadEngine(const UINT allocatedThreads);
		virtual ~ThreadEngine();

		bool QueueJob(memory_order&& mem_order, bool*&& function, UINT argumentCount, ...);
		void QueueFence();
		void Shutdown();
		void ShutdownThread(UINT threadID);
		void ShutdownThreadByIndex(UINT index);
		void test();
	};
}