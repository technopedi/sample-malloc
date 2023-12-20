#include <dlfcn.h>
#include <stdio.h>
#include <assert.h>
#include <thread>
#include <unistd.h>
#include <emscripten/wasmfs.h>
#include <fstream>
#include "../lib_run_time/run_time_hello_world.h"
#include <sstream>
#include <iomanip>
#include <iostream>

extern "C" {
    // Declare the global variable as extern
    // extern int flag;
}

#include <mutex>

std::ofstream globalFile("example.txt", std::ios::app);
std::mutex fileMutex;

extern "C" {
//     void writeToGlobalFile(const char* data) {
// //         printf("trying to write here...   %s \n" ,data);
// //        std::lock_guard<std::mutex> lock(fileMutex);
// //        printf("trying to write here...   %s \n" ,data);
// //        globalFile << data <<std::endl;
//     }
}

// void writeNewAddressToFile(void * addr)
// {
////     if (outputFile.is_open()) {
////     // // Define a memory address (e.g., a pointer)
////     int* memoryAddress = reinterpret_cast<int*>(addr);
////     std::cout<<"malloc - "<<memoryAddress<<std::endl;
////     // newCount++;
////
////     // // Write the memory address to the file
////     outputFile << memoryAddress << std::endl;
////
////     // Close the file
////     // outputFile.close();
////     }
//
//     char buffer[100];
//     sprintf(buffer, "malloc - %p\n", addr);
//
//     writeToGlobalFile(buffer);
// }
//
// void writeFreeAddressToFile(void * addr)
// {
////     if (outputFreeFile.is_open()) {
////     // // Define a memory address (e.g., a pointer)
////     int* memoryAddress = reinterpret_cast<int*>(addr);
////     std::cout<<"free - "<<memoryAddress<<std::endl;
////     // freeCount++;
////
////     // // Write the memory address to the file
////     outputFreeFile << memoryAddress << std::endl;
////
////     // // Close the file
////     // // outputFreeFile.close();
////     }
//
//
//     char buffer[100];
//     sprintf(buffer, "free - %p\n", addr);
//
//     writeToGlobalFile(buffer);
// }
//
// void* operator new(std::size_t size)
// {
//    // printf("new1 is called....");
//     void* addr = nullptr;
//     if (size == 0) size = 1;
//     addr =  (void *)malloc(size);
//      writeNewAddressToFile(addr);
//     return addr;
// }
//
// void operator delete(void* p) noexcept
// {
//     // printf("delete1 is called....");
//     if (p != 0)
//     {
//          writeFreeAddressToFile(p);
//         free(p);
//     }
// }
//
// void* operator new(std::size_t size, const std::nothrow_t&) noexcept
// {
//     // printf("new1 is called....");
//     void* addr = nullptr;
//     if (size == 0) size = 1;
//
//     addr =  (void *)malloc(size);
//      writeNewAddressToFile(addr);
//     return addr;
// }
//
// void operator delete(void* ptr, const std::nothrow_t&) noexcept
// {
//     // printf("delete1  is called....");
//     if (ptr != 0)
//     {
//          writeFreeAddressToFile(ptr);
//             free(ptr);
//     }
// }
//
// // throws std::bad_alloc on failure
// void* operator new[](std::size_t size)
// {
//     // printf("new1 is called....");
//     void* addr = nullptr;
//     if (size == 0) size = 1;
//     addr =  (void *)malloc(size);
//      writeNewAddressToFile(addr);
//     return addr;
// }
//
// void operator delete[](void* p) noexcept
// {
//     operator delete (p);
// }
//
// void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
// {
//     return operator new (size, std::nothrow);
// }
//
// void operator delete[](void* p, const std::nothrow_t&) noexcept
// {
//     operator delete (p, std::nothrow);
// }


void RunDynamicLibraryFunc() 
{
    printf("RunDynamicLibraryFunc called\n");
    void* lib_handle = dlopen("run_time_hello_world.wasm", RTLD_NOW | RTLD_GLOBAL);
    if (!lib_handle) {
        puts(dlerror());
        printf("Error: Loading of library run_time_hello_world.wasm failed\n");
        assert(0);
    }
    else
    {
       printf("Loading of library run_time_hello_world.wasm successful\n");
    }

    int (*fun)(void) = (int (*)(void))dlsym(lib_handle, "func_run_time");
    (fun)();
}

int main() {
    printf("main hello, world!\n");
    int * n = new int(5);
    printf("main - will try to call runtime hello world\n");
    // flag=1;
//    std::thread thread_id(RunDynamicLibraryFunc);
//    thread_id.join();
    RunDynamicLibraryFunc();

    return 0;
}
