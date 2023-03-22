#pragma once
export module JNX_Threading_Lib;
import <utility>;
import <vector>;

#ifdef _DLLEXPO
#define DLLFLOW __declspec(dllexport)
#else
#define DLLFLOW __declspec(dllimport)
#endif

export namespace JNX {
	typedef enum memory_order {
		memory_order_relaxed,
		memory_order_consume,
		memory_order_acquire,
		memory_order_release,
		memory_order_acq_rel,
		memory_order_seq_cst
	};

	enum JOBTYPES : char {
		// Is exit really necessary?
		EXIT  = 1 << 0, // 0001
		JOB   = 1 << 1, // 0010
		FENCE = 1 << 2  // 0100
	};

	extern "C++" {
		struct DLLFLOW IThreadEngine {
			virtual bool QueueJob(memory_order&& mem_order, bool*&& functionPointer, unsigned int argumentCount, ...) = 0;
			virtual void test() = 0;
		};

		DLLFLOW IThreadEngine& CreateThreadEngine(const unsigned int);
		typedef IThreadEngine& (__cdecl* CREATETE)(const unsigned int);
	}
}