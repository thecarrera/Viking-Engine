#pragma once
export module JNX_Threading_Lib;

#ifdef _DLLEXPO
#define DLLFLOW __declspec(dllexport)
#else
#define DLLFLOW __declspec(dllimport)
#endif

export namespace JNX {
	enum memory_order {
		memory_order_relaxed,
		memory_order_consume,
		memory_order_acquire,
		memory_order_release,
		memory_order_acq_rel,
		memory_order_seq_cst
	};

	enum JOBTYPES : char {
		EXIT = 1 << 0, // 0001
		JOB = 1 << 1, // 0010
		FENCE = 1 << 2  // 0100
	};
	extern "C" {
		struct DLLFLOW IThreadEngine {
			virtual void test() = 0;
		};

		DLLFLOW IThreadEngine& CreateThreadEngine(unsigned int);
		typedef IThreadEngine& (__cdecl* CREATETE)(unsigned int);
	}
}