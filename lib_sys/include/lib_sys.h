#include <stddef.h>
#include <stdint.h>
#include <threads.h>
#include <stdbool.h>


struct log_data
{
    uint8_t signal;
    struct timespec time;
    struct cpu_struct* cpu_struct_ptr;
};
struct cpu_struct
{
    char* name;
    // usage_persent
    // proc_running
    // 
};

// make a new thread, allocate log_data, loop though the work with a given Hz equal for all, exposes pointers to data structures, 
thrd_t lib_sys_log(struct log_data* log_data_ptr);

// CPU
uint8_t lib_sys_log_cpu(struct log_data* log_data);

uint8_t lib_sys_log_stop_cpu(struct log_data* log_data);
