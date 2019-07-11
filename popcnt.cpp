#include <iostream>
#include <chrono>
#include <x86intrin.h>

int main(int argc, char* argv[]) {

    using namespace std;
    if (argc != 2) {
       cerr << "usage: array_size in MB" << endl;
       return -1;
    }

    uint64_t size = atol(argv[1])<<20;
    uint64_t* buffer = new uint64_t[size/8];
    char* charbuffer = reinterpret_cast<char*>(buffer);
    for (unsigned i=0; i<size; ++i)
        charbuffer[i] = rand()%256;

    uint64_t count,duration;
    chrono::time_point<chrono::system_clock> startP,endP;
    {
        startP = chrono::system_clock::now();
        count = 0;
        for( unsigned k = 0; k < 10000; k++){
            // Tight unrolled loop with unsigned
            for (unsigned i=0; i<size/8; i+=4) {
                count += _mm_popcnt_u64(buffer[i]);
                count += _mm_popcnt_u64(buffer[i+1]);
                count += _mm_popcnt_u64(buffer[i+2]);
                count += _mm_popcnt_u64(buffer[i+3]);
            }
        }
        endP = chrono::system_clock::now();
        duration = chrono::duration_cast<std::chrono::nanoseconds>(endP-startP).count();
        cout << "unsigned\t" << count << '\t' << (duration/1.0E9) << " sec \t"
             << (10000.0*size)/(duration) << " GB/s" << endl;
    }
    {
        startP = chrono::system_clock::now();
        count=0;
        for( unsigned k = 0; k < 10000; k++){
            // Tight unrolled loop with uint64_t
            for (uint64_t i=0;i<size/8;i+=4) {
                count += _mm_popcnt_u64(buffer[i]);
                count += _mm_popcnt_u64(buffer[i+1]);
                count += _mm_popcnt_u64(buffer[i+2]);
                count += _mm_popcnt_u64(buffer[i+3]);
            }
        }
        endP = chrono::system_clock::now();
        duration = chrono::duration_cast<std::chrono::nanoseconds>(endP-startP).count();
        cout << "uint64_t\t"  << count << '\t' << (duration/1.0E9) << " sec \t"
             << (10000.0*size)/(duration) << " GB/s" << endl;
    }

    free(charbuffer);
}
