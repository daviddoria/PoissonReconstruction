/*
Copyright (c) 2006, Michael Kazhdan and Matthew Bolitho
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer. Redistributions in binary form must reproduce
the above copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the distribution. 

Neither the name of the Johns Hopkins University nor the names of its contributors
may be used to endorse or promote products derived from this software without specific
prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/

#ifndef MEMORY_USAGEWIN32_INCLUDED
#define MEMORY_USAGEWIN32_INCLUDED

#include <Windows.h>
class MemoryInfo{
public:
	size_t TotalPhysicalMemory;
	size_t FreePhysicalMemory;
	size_t TotalSwapSpace;
	size_t FreeSwapSpace;
	size_t TotalVirtualAddressSpace;
	size_t FreeVirtualAddressSpace;
	size_t PageSize;

	void set(void){
		MEMORYSTATUSEX Mem;
		SYSTEM_INFO Info;
		ZeroMemory( &Mem, sizeof(Mem));
		ZeroMemory( &Info, sizeof(Info)); 
		Mem.dwLength = sizeof(Mem);
		::GlobalMemoryStatusEx( &Mem );
		::GetSystemInfo( &Info );

		TotalPhysicalMemory = (size_t)Mem.ullTotalPhys;
		FreePhysicalMemory = (size_t)Mem.ullAvailPhys;
		TotalSwapSpace = (size_t)Mem.ullTotalPageFile;
		FreeSwapSpace = (size_t)Mem.ullAvailPageFile;
		TotalVirtualAddressSpace = (size_t)Mem.ullTotalVirtual;
		FreeVirtualAddressSpace = (size_t)Mem.ullAvailVirtual;
		PageSize = (size_t)Info.dwPageSize;
	}
	size_t usage(void) const {return TotalVirtualAddressSpace-FreeVirtualAddressSpace;}

	static size_t Usage(void){
		MEMORY_BASIC_INFORMATION mbi; 
		size_t      dwMemUsed = 0; 
		PVOID      pvAddress = 0; 


		memset(&mbi, 0, sizeof(MEMORY_BASIC_INFORMATION)); 
		while(VirtualQuery(pvAddress, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION)){ 
			if(mbi.State == MEM_COMMIT && mbi.Type == MEM_PRIVATE){dwMemUsed += mbi.RegionSize;}
			pvAddress = ((BYTE*)mbi.BaseAddress) + mbi.RegionSize; 
		} 
		return dwMemUsed; 
	} 
};

#endif

