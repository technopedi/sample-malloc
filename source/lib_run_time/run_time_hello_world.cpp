#include <stdio.h>
#include <thread> 
#include <stdexcept>

#include "run_time_hello_world.h"
#include "../lib_static/static_hello_world.h"

void writeNewAddressToFile(void * addr)
{
//     if (outputFile.is_open()) {
//     // // Define a memory address (e.g., a pointer)
//     int* memoryAddress = reinterpret_cast<int*>(addr);
//     std::cout<<"malloc - "<<memoryAddress<<std::endl;
//     // newCount++;
//
//     // // Write the memory address to the file
//     outputFile << memoryAddress << std::endl;
//
//     // Close the file
//     // outputFile.close();
//     }

    // char buffer[100];
    // sprintf(buffer, "malloc - %p\n", addr);

    // writeToGlobalFile(buffer);
}

void writeFreeAddressToFile(void * addr)
{
//     if (outputFreeFile.is_open()) {
//     // // Define a memory address (e.g., a pointer)
//     int* memoryAddress = reinterpret_cast<int*>(addr);
//     std::cout<<"free - "<<memoryAddress<<std::endl;
//     // freeCount++;
//
//     // // Write the memory address to the file
//     outputFreeFile << memoryAddress << std::endl;
//
//     // // Close the file
//     // // outputFreeFile.close();
//     }


    // char buffer[100];
    // sprintf(buffer, "free - %p\n", addr);

    // writeToGlobalFile(buffer);
}

void* operator new(std::size_t size)
{
   printf("new1 is called....\n");
    void* addr = nullptr;
    if (size == 0) size = 1;
    addr =  (void *)malloc(size);
     writeNewAddressToFile(addr);
    return addr;
}

void operator delete(void* p) noexcept
{
    printf("delete1 is called....\n");
    if (p != 0)
    {
         writeFreeAddressToFile(p);
        free(p);
    }
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    printf("new1 is called....\n");
    void* addr = nullptr;
    if (size == 0) size = 1;

    addr =  (void *)malloc(size);
     writeNewAddressToFile(addr);
    return addr;
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept
{
    printf("delete1  is called....\n");
    if (ptr != 0)
    {
         writeFreeAddressToFile(ptr);
            free(ptr);
    }
}

// throws std::bad_alloc on failure
void* operator new[](std::size_t size)
{
    printf("new1 is called....\n");
    void* addr = nullptr;
    if (size == 0) size = 1;
    addr =  (void *)malloc(size);
     writeNewAddressToFile(addr);
    return addr;
}

void operator delete[](void* p) noexcept
{
    operator delete (p);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return operator new (size, std::nothrow);
}

void operator delete[](void* p, const std::nothrow_t&) noexcept
{
    operator delete (p, std::nothrow);
}


void func_local_runtime_lib()
{
    printf("Run-time lib func_local_runtime_lib hello, world!\n");
}

int func_run_time() {
    printf("Run-time lib hello, world!\n");
    
    std::thread thread_id1(func_local_runtime_lib); 
    std::thread thread_id2(func_local_runtime_lib); 
    std::thread thread_id3(func_local_runtime_lib); 
    std::thread thread_id4(func_local_runtime_lib); 

    thread_id1.join();
    thread_id2.join();
    thread_id3.join();
    thread_id4.join();

    func_static_time();

    return 0;
}

//void testFunc(std::shared_ptr<int>& ptr, std::vector<int>& v)
//{
//    printf("we are inside test Function.....\n");
//    ptr = std::make_shared<int>(42);
//    v.resize(1000);
//    int n = 20;
//}
