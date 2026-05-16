#include "main.h"
#include "lib_sys.h"
#include "graph_path.h"
#include <cstring>


// the first value is always a pointer to a function that take 
// an array of void pointers(this are the arguments of the update function which the user interpreats)
struct usr_data
{
    void (*update_func)(void*);
    slint::ComponentHandle<AppWindow>* ui_ptr;
    struct log_data* log_data_ptr;
    char cpuG_draw_cmd[SIZE_CMD];
    char memG_draw_cmd[SIZE_CMD];
    uint8_t last_percentage;
};
// intead use slint's even callbacks in the main thread(kepping this in c case i need it)
void update_stats(void* usr_data_ptr)
{
    static uint8_t i{0};
    struct usr_data* _usr_data_ptr = (struct usr_data*)usr_data_ptr;
    if (_usr_data_ptr->ui_ptr != NULL)
        slint::invoke_from_event_loop([_usr_data_ptr]()
            {
                make_graph_path(_usr_data_ptr->cpuG_draw_cmd, _usr_data_ptr->log_data_ptr->cpu_info_ptr->arr_percentages);
                (*_usr_data_ptr->ui_ptr)->
                    set_cpuG_draw_cmd(_usr_data_ptr->cpuG_draw_cmd);

                // make_graph_path(_usr_data_ptr->memG_draw_cmd, _usr_data_ptr->log_data_ptr->mem_info_ptr->usage_percent);
                // (*_usr_data_ptr->ui_ptr)->
                //     set_memG_draw_cmd(_usr_data_ptr->cpuG_draw_cmd);
            }
        );
}
void init(struct usr_data* usr_data_ptr, struct log_data* log_data_ptr)
{

}
int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    struct log_data _log_data{0};
    struct usr_data _usr_data{0};

    _log_data.usr_data_ptr  = &_usr_data;
    _usr_data.ui_ptr        = &ui;
    _usr_data.update_func   = update_stats;
    _usr_data.log_data_ptr  = &_log_data;

    memset(_usr_data.cpuG_draw_cmd, ' ', SIZE_CMD);
    memset(_usr_data.memG_draw_cmd, ' ', SIZE_CMD);
    
    lib_sys_log_cpu(&_log_data);
    lib_sys_log_mem(&_log_data);

    thrd_t thread_ptr = lib_sys_log(&_log_data);

    ui->run();
    
    thrd_join(thread_ptr, NULL);

    return 0;
}