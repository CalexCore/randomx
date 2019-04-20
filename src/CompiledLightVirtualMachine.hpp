/*
Copyright (c) 2019 tevador

This file is part of RandomX.

RandomX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RandomX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RandomX.  If not, see<http://www.gnu.org/licenses/>.
*/

#pragma once
//#define TRACEVM
#include <new>
#include "CompiledVirtualMachine.hpp"
#include "JitCompilerX86.hpp"
#include "intrinPortable.h"

namespace randomx {

	template<class Allocator, bool softAes>
	class CompiledLightVm : public CompiledVm<Allocator, softAes> {
	public:
		void* operator new(size_t size) {
			void* ptr = AlignedAllocator<CacheLineSize>::allocMemory(size);
			if (ptr == nullptr)
				throw std::bad_alloc();
			return ptr;
		}
		void operator delete(void* ptr) {
			AlignedAllocator<CacheLineSize>::freeMemory(ptr, sizeof(CompiledLightVm));
		}
		void setCache(randomx_cache* cache) override;
		void setDataset(randomx_dataset* dataset) override {}
		void initialize() override;
	};

	using CompiledLightVmDefault = CompiledLightVm<AlignedAllocator<CacheLineSize>, true>;
	using CompiledLightVmHardAes = CompiledLightVm<AlignedAllocator<CacheLineSize>, false>;
	using CompiledLightVmLargePage = CompiledLightVm<LargePageAllocator, false>;
	using CompiledLightVmLargePageHardAes = CompiledLightVm<LargePageAllocator, true>;
}