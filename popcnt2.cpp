#include <iostream>
#include <chrono>
#include <x86intrin.h>

int main(int argc, char* argv[]) {

   using namespace std;
   uint64_t size=1<<20;

   uint64_t* buffer = new uint64_t[size/8];
   char* charbuffer=reinterpret_cast<char*>(buffer);
   for (unsigned i=0;i<size;++i) charbuffer[i]=rand()%256;

   uint64_t count,duration;
   chrono::time_point<chrono::system_clock> startP,endP;
   {
      uint64_t c0 = 0;
      uint64_t c1 = 0;
      uint64_t c2 = 0;
      uint64_t c3 = 0;
      startP = chrono::system_clock::now();
      for( unsigned k = 0; k < 10000; k++){
         for (uint64_t i=0;i<size/8;i+=4) {
            uint64_t r0 = buffer[i + 0];
            uint64_t r1 = buffer[i + 1];
            uint64_t r2 = buffer[i + 2];
            uint64_t r3 = buffer[i + 3];
            __asm__(
                "popcnt %4, %4  \n\t"
                "add %4, %0     \n\t"
                "popcnt %5, %5  \n\t"
                "add %5, %1     \n\t"
                "popcnt %6, %6  \n\t"
                "add %6, %2     \n\t"
                "popcnt %7, %7  \n\t"
                "add %7, %3     \n\t"
                : "+r" (c0), "+r" (c1), "+r" (c2), "+r" (c3)
                : "r"  (r0), "r"  (r1), "r"  (r2), "r"  (r3)
            );
         }
      }
      count = c0 + c1 + c2 + c3;
      endP = chrono::system_clock::now();
      duration=chrono::duration_cast<std::chrono::nanoseconds>(endP-startP).count();
      cout << "No Chain\t" << count << '\t' << (duration/1.0E9) << " sec \t"
            << (10000.0*size)/(duration) << " GB/s" << endl;
   }
   {
      uint64_t c0 = 0;
      uint64_t c1 = 0;
      uint64_t c2 = 0;
      uint64_t c3 = 0;
      startP = chrono::system_clock::now();
      for( unsigned k = 0; k < 10000; k++){
         for (uint64_t i=0;i<size/8;i+=4) {
            uint64_t r0 = buffer[i + 0];
            uint64_t r1 = buffer[i + 1];
            uint64_t r2 = buffer[i + 2];
            uint64_t r3 = buffer[i + 3];
            __asm__(
                "popcnt %4, %%rax   \n\t"
                "add %%rax, %0      \n\t"
                "popcnt %5, %%rax   \n\t"
                "add %%rax, %1      \n\t"
                "popcnt %6, %%rax   \n\t"
                "add %%rax, %2      \n\t"
                "popcnt %7, %%rax   \n\t"
                "add %%rax, %3      \n\t"
                : "+r" (c0), "+r" (c1), "+r" (c2), "+r" (c3)
                : "r"  (r0), "r"  (r1), "r"  (r2), "r"  (r3)
                : "rax"
            );
         }
      }
      count = c0 + c1 + c2 + c3;
      endP = chrono::system_clock::now();
      duration=chrono::duration_cast<std::chrono::nanoseconds>(endP-startP).count();
      cout << "Chain 4   \t"  << count << '\t' << (duration/1.0E9) << " sec \t"
            << (10000.0*size)/(duration) << " GB/s" << endl;
   }
   {
      uint64_t c0 = 0;
      uint64_t c1 = 0;
      uint64_t c2 = 0;
      uint64_t c3 = 0;
      startP = chrono::system_clock::now();
      for( unsigned k = 0; k < 10000; k++){
         for (uint64_t i=0;i<size/8;i+=4) {
            uint64_t r0 = buffer[i + 0];
            uint64_t r1 = buffer[i + 1];
            uint64_t r2 = buffer[i + 2];
            uint64_t r3 = buffer[i + 3];
            __asm__(
                "xor %%rax, %%rax   \n\t"   // <--- Break the chain.
                "popcnt %4, %%rax   \n\t"
                "add %%rax, %0      \n\t"
                "popcnt %5, %%rax   \n\t"
                "add %%rax, %1      \n\t"
                "popcnt %6, %%rax   \n\t"
                "add %%rax, %2      \n\t"
                "popcnt %7, %%rax   \n\t"
                "add %%rax, %3      \n\t"
                : "+r" (c0), "+r" (c1), "+r" (c2), "+r" (c3)
                : "r"  (r0), "r"  (r1), "r"  (r2), "r"  (r3)
                : "rax"
            );
         }
      }
      count = c0 + c1 + c2 + c3;
      endP = chrono::system_clock::now();
      duration=chrono::duration_cast<std::chrono::nanoseconds>(endP-startP).count();
      cout << "Broken Chain\t"  << count << '\t' << (duration/1.0E9) << " sec \t"
            << (10000.0*size)/(duration) << " GB/s" << endl;
   }

   free(charbuffer);
}
