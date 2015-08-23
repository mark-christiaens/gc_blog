#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

void show_help(void) {
    std::cerr << "gc element_size element_count allocation_count" << std::endl;
}

void do_benchmark(int el_size, int el_count, int alloc_count) {
    typedef std::vector <char> element_t;
    typedef std::vector <element_t*> elements_t;
    elements_t elements(el_count);

    for (size_t i = 0; i < alloc_count; i++) {
        size_t slot = i % el_count;
        element_t* element_p = elements [slot];
        if (element_p != NULL) {
            delete element_p;
        }
        element_p = new element_t(el_size);
        for (size_t j = 0; j < el_size; j++) {
            (*element_p) [j] = (char) i;
        }
        elements[slot] = element_p;
    }

    long tot = 0l;

    for (auto element_p : elements) {
        if (element_p != NULL) {
            for (auto c : *element_p) {
                tot += c;
            }
        }
    }

    std::cout << "Sum: " << tot << std::endl;

    //    private static void doBenchmark(
    //            int elSize,
    //            int elCount,
    //            int allocCount)
    //            throws InterruptedException {
    //        byte[][] elements = new byte[elCount][];
    //
    //        for (int i = 0; i < allocCount; i++) {
    //            int slot = i % elCount;
    //            elements[slot] = new byte[elSize];
    //            for (int j = 0; j < elSize; j++) {
    //                elements[slot][j] = (byte) i;
    //            }
    //        }
    //
    //        long tot = 0l;
    //        for (byte[] element : elements) {
    //            if (element != null) {
    //                for (byte b : element) {
    //                    tot += b;
    //                }
    //            }
    //        }
    //
    //        System.out.println("Sum: " + tot);
    //
    //        System.gc();
    //    }

    return;

}

int main(int argc, char** argv) {
    if (argc != 4) {
        show_help();
        exit(-1);
    }

    int el_size = std::stoi(argv[1]);
    int el_count = std::stoi(argv[2]);
    int alloc_count = std::stoi(argv[3]);

    std::cout << "Element size: " << el_size << std::endl;
    std::cout << "Element count: " << el_count << std::endl;
    std::cout << "Allocation count: " << alloc_count << std::endl;

    std::clock_t start = std::clock();
    do_benchmark(el_size, el_count, alloc_count);
    std::clock_t stop = std::clock();
    std::clock_t exec_time = stop - start;
    double seconds = exec_time / (double) CLOCKS_PER_SEC;

    double allocs_per_sec = alloc_count / seconds;
    double mb_per_sec = (1L * alloc_count * el_size / 1e6) / seconds;

    std::cout << "Time: " << seconds << " seconds" << std::endl;
    std::cout << "Allocations: " << allocs_per_sec << " allocations per second" << std::endl;
    std::cout << "Allocations: " << mb_per_sec << " MB/s";

    return 0;
}
