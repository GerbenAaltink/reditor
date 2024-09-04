#include <math.h>
#include "wren.h"

WrenConfiguration config;
WrenVM* vm;

void writeFn(WrenVM* vm, const char* text) {
  printf("%s", text);
}

void wren_init(){
        
  wrenInitConfiguration(&config);
    config.writeFn = &writeFn;
   vm = wrenNewVM(&config);
   WrenInterpretResult result = wrenInterpret(
    vm,
    "my_module",
    "System.print(\"var aaa = 20\nI am running in a VM!\")");

}

void wren_handle(){
    return;
    char name[] = "my_module";
    Value module_name =wrenStringFormat(vm, "my_module");
    char * vname = "aaa";
    Value var_name = wrenStringFormat(vm, "aaa");
    
     Value val =  wrenGetModuleVariable(vm,module_name,var_name);
     //const char * v = wrenGetSlotString(vm,val);
    //printf("%s\n",v);
   // printf("%s\n",val);
}

void wren_free(){
   
    wrenFreeVM(vm);
}