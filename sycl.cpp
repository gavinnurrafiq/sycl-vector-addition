#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>

constexpr int N = 1000000;

int main() {
    // 1. Select available GPU device
    sycl::queue q{sycl::gpu_selector_v};

    std::cout << "[C++ SYCL] Running vector addition on GPU...\n";

    // 2. Declare data using std::vector
    std::vector<float> a(N, 1.0f);
    std::vector<float> b(N, 2.0f);
    std::vector<float> c(N, 0.0f);

    {
        // 3. Create Buffers for automatic data management and synchronization
        sycl::buffer<float> buf_a(a.data(), sycl::range<1>(N));
        sycl::buffer<float> buf_b(b.data(), sycl::range<1>(N));
        sycl::buffer<float> buf_c(c.data(), sycl::range<1>(N));

        // 4. Submit task to the GPU queue
        q.submit([&](sycl::handler& h) {
            sycl::accessor acc_a(buf_a, h, sycl::read_only);
            sycl::accessor acc_b(buf_b, h, sycl::read_only);
            sycl::accessor acc_c(buf_c, h, sycl::write_only);

            // Parallel computation on the GPU
            h.parallel_for(sycl::range<1>(N), [=](sycl::id<1> i) {
                acc_c[i] = acc_a[i] + acc_b[i];
            });
        });
    } // Buffers go out of scope here; results are automatically copied back to vector 'c'

    // Verification
    std::cout << "Result c[0] = " << c[0] << " (Expected: 3.0)\n";

    return 0;
}