#include <type_traits>
#include <cstring>

template<class T>
T* unique(T* a, size_t s) {
    if (s <= 1) return a + s;
    
    size_t write_pos = 1;
   
    for (size_t read_pos = 1; read_pos < s; ++read_pos) {
        bool is_duplicate = false;
        
        for (size_t check_pos = 0; check_pos < write_pos; ++check_pos) {
            if (a[read_pos] == a[check_pos]) {
                is_duplicate = true;
                break;
            }
        }
        
        if (!is_duplicate) {
            if (read_pos != write_pos) {
                if constexpr (std::is_trivially_copyable_v<T>) {
                    std::memcpy(&a[write_pos], &a[read_pos], sizeof(T));
                } else {
                    a[write_pos] = a[read_pos];
                }
            }
            ++write_pos;
        }
    }
    
    return a + write_pos;
}
