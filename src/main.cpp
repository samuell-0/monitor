#include "main.h"
#include "lib_sys.h"


// the first value is always a pointer to a function that take 
// an array of void pointers(this are the arguments of the update function which the user interpreats)
struct ui_data
{
    void (*update_func)(void*);
    void** args;
    uint8_t n_args;
    struct log_data* log_data_ptr;
};
// intead use slint's even callbacks in the main thread(kepping this in c case i need it)
void update_stats(void* usr_data_ptr)
{
    struct ui_data* ui_data_ptr = (struct ui_data*)(usr_data_ptr);
    if (ui_data_ptr->args ==  NULL)
        return;
    if (ui_data_ptr->args[0] != NULL)
        slint::invoke_from_event_loop([ui_data_ptr]()
            {
                (*((slint::ComponentHandle<AppWindow>*)(ui_data_ptr->args[0])))->set_cpu_usage(ui_data_ptr->log_data_ptr->cpu_info_ptr->usage);
            }
        );
}
int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    struct log_data _log_data{0};
    struct ui_data _ui_data{0};
    void* arr[1]{0};

    _ui_data.log_data_ptr = &_log_data;
    _ui_data.update_func = update_stats;
    _ui_data.args = arr;
    _ui_data.n_args = 1;
    _ui_data.args[0] = &ui;
    
    _log_data.usr_data_ptr = &_ui_data;
    
    lib_sys_log_cpu(&_log_data);

    thrd_t thread_ptr = lib_sys_log(&_log_data);


    ui->run();
    
    thrd_join(thread_ptr, NULL);

    return 0;
}