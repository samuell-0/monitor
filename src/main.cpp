#include "main.h"

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->set_cpu_usage(3);

    ui->run();
    return 0;
}