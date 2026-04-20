#include <lib_sys.h>
#include "procfs/procfs.h"
#include <stdlib.h>
#include <stdio.h>
// PUBLIC
uint8_t lib_sys_log_cpu(struct log_data* log_data_ptr)
{
    if (log_data_ptr == NULL)
        return 1;
    // allocate cpu_struct
    struct cpu_struct* cpu_struct_ptr = malloc(sizeof *cpu_struct_ptr);
    if (cpu_struct_ptr == NULL)
        return 2;

    log_data_ptr->cpu_struct_ptr = cpu_struct_ptr;
    return 0;
}

uint8_t lib_sys_log_stop_cpu(struct log_data* log_data)
{
    // deallocate cpu_struct
    // 
}
// PRIVATE
uint8_t _log_cpu(struct cpu_struct* cpu_struct_ptr)
{
    // if nothing else to do here, this function should be redacted
    parse_cpu_usage(cpu_struct_ptr);
    return 0;
}
