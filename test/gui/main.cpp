
#include "avm_gui.hpp"
#include "avm_gui_def.hpp"
#include <unistd.h>
#include<iostream>
#include<string.h>
#include<malloc.h>
int main(int argc, char *argv[])
{
    mallopt(M_ARENA_MAX, 1);
    vagoo::gui::VAGOO_GUI_INPUT_S input;
    memset(&input,0,sizeof(input));
    vagoo::gui::VG_GUI_OPS_S ops =  vagoo::gui::VG_stGetGUIOps();
    ops._init(input);
    while(1){
        usleep(1000000);
    }
}
