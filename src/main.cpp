#include "main.h"
#include "lib_sys.h"


// the first value is always a pointer to a function that take 
// an array of void pointers(this are the arguments of the update function which the user interpreats)
struct ui_data
{
    void (*update_func)(void* [], uint8_t);
    void** args;
    uint8_t n_args;
};
// intead use slint's even callbacks in the main thread(kepping this in c case i need it)
void update_stats(void* args[], uint8_t n_args)
{
    if (args ==  NULL)
        return;
    printf("%s\n", (char*)args[0]);
    // if (args[1] != NULL)// can't call this(and many) slint api functions from another thread
    //     (*((slint::ComponentHandle<AppWindow>*)(args[1])))->set_cpu_usage(343);
}
int main(int argc, char **argv)
{

    auto ui = AppWindow::create();

    struct log_data _log_data{0};
    struct ui_data _ui_data{0};
    void* arr[2]{0};

    _ui_data.update_func = update_stats;
    _ui_data.args = arr;
    _ui_data.n_args = 2;
    _ui_data.args[0] = (void*)"hi";
    _ui_data.args[1] = &ui;
    
    _log_data.user_data_ptr = &_ui_data;
    
    lib_sys_log_cpu(&_log_data);

    // slint::invoke_from_event_loop;

    thrd_t thread_ptr = lib_sys_log(&_log_data);


    ui->run();
    
    thrd_join(thread_ptr, NULL);

    return 0;
}