#include <math.h>
#include "wren.h"
#include "redit.h"

WrenConfiguration config;
WrenVM* vm;

void writeFn(WrenVM* vm, const char* text) {
  printf("%s", text);
}

const char * footer;
rterm_t * _rterm;
session_t * _session;

void wInsert(WrenVM * vm){
    const char * str = wrenGetSlotString(vm,1);
    int pos = get_document_pos(_rterm);
    for(size_t i = 0; i < strlen(str); i++){
        document_insert_char(_rterm,pos,str[i]);
    }
}
void wGetDocumentPos(WrenVM * vm){
    wrenSetSlotDouble(vm,0,get_document_pos(_rterm));
}
void wGetLineIndex(WrenVM * vm){
    wrenSetSlotDouble(vm,0,get_document_pos(_rterm));
    
    //wrenSetSlotDouble(vm,0,get_(_rterm));
}
void wGetCursorX(WrenVM *vm){
    wrenSetSlotDouble(vm,0, (double)_rterm->cursor.x);
}

void wGetCursorY(WrenVM *vm){
    wrenSetSlotDouble(vm,0, (double)_rterm->cursor.y);
}
void wGetLine(WrenVM * vm){
    wrenSetSlotString(vm, 0, _session->line);
}

void wsetFooter(WrenVM * vm){
   _rterm->status_text = (char *)wrenGetSlotString(vm, 1);

}

WrenForeignMethodFn bindForeignMethodFn(
    WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature)
    
  
  {

      //printf("JAA OOOR %s\n",signature)
      if(!strcmp(signature,"getDocumentPos()")){
            return wGetDocumentPos;
        }
        if(!strcmp(signature,"getLineIndex()")){
            return wGetLineIndex;
        }
        if(!strcmp(signature,"getCursorX()")){
            return wGetCursorX;
        }
        if(!strcmp(signature,"getCursorY()")){
            return wGetCursorY;
        }
        if(!strcmp(signature,"insert(_)")){
            return wInsert;
        }else 
        if(!strcmp(signature,"setFooter(_)")){
            
        return wsetFooter;
        }else if(!strcmp(signature,"getLine()")){
            return wGetLine;
        }
        printf("Uncatched: %s\n",signature);
        exit(3);
    }

void wren_init(rterm_t * rterm){
    _rterm = rterm;
    _session = (session_t *)rterm->session;
  
  wrenInitConfiguration(&config);
 config.writeFn = &writeFn;
   config.bindForeignMethodFn = &bindForeignMethodFn; 
  
   vm = wrenNewVM(&config);
  
    //bindForeignMethodFn(vm,"my_module","Editor",false,"setFooter(x,y)");
    //ByteBuffer bf = wrenBindMethod(     )
    char str_class_source[1024] = {0};
 strcat(str_class_source, "var globals = {}\n");
    //strcat(str_class_source, "System.print(\"gggg\")\n");
    strcat(str_class_source, "class Editor{\n");
    
   //  strcat(str_class_source, "construct init() {} \n");
    //strcat(str_class_source, "x = 0 \n");
    //strcat(str_class_source, "y = 0 \n");
    //strcat(str_class_source, "footer = "" \n");
    strcat(str_class_source, "foreign static getLine() \n");
     strcat(str_class_source, "foreign static setFooter(text) \n");
     strcat(str_class_source, "foreign static insert(text) \n");

     strcat(str_class_source, "foreign static getCursorX() \n");

     strcat(str_class_source, "foreign static getCursorY() \n");
     strcat(str_class_source, "foreign static getLineIndex() \n");
     strcat(str_class_source, "foreign static getDocumentPos() \n");
    strcat(str_class_source, "}\n");
     strcat(str_class_source, "Editor.setFooter(\"Loading...\")");
   // strcat(str_class_source, "aaa = \"20\"\n");  

    printf("%s\n",str_class_source); 
    //config.bindForeighn(vm, "my_module", "Math", true, "add(_,_)");
  wrenEnsureSlots(vm, 10);
   WrenInterpretResult result = wrenInterpret(
    vm,
    "main",
    str_class_source);
    switch (result) {
    case WREN_RESULT_COMPILE_ERROR:
      { printf("Compile Error!\n"); exit(2); } break;
    case WREN_RESULT_RUNTIME_ERROR:
      { printf("Runtime Error!\n"); exit(2); } break;
    case WREN_RESULT_SUCCESS:
      { } break;
  }
   wrenEnsureSlots(vm, 10);
 
 // wrenEnsureSlots(vm, 10);
 
   //renSetSlotString(vm,5,"hahaha");
    //wrenGetVariable(vm,"my_module","aaa",5);
    //Value val =  wrenGetModuleVariable(vm,str,s);
    //wrenDumpValue(val);
    //printf("%s\n",val);
    //wrenCall(vm,NULL);
   // exit(0);
//wrenCall(vm,NULL);
}

void wren_handle(){
     size_t file_length = rfile_size("plugin.wren");
     char file_content[file_length + 1];
     rfile_readb("plugin.wren",file_content,file_length);
    file_content[file_length] = 0;
  
  //_session = (session_t *)rterm->session; 
    WrenInterpretResult result = wrenInterpret(vm,"main",file_content);
    switch (result) {
    case WREN_RESULT_COMPILE_ERROR:
      { printf("Compile Error!\n"); exit(2); } break;
    case WREN_RESULT_RUNTIME_ERROR:
      { printf("Runtime Error!\n"); exit(2); } break;
    case WREN_RESULT_SUCCESS:
      {  } break;
  }
  //rterm->status_text = (char *)footer;
  return;
   Value module_name =wrenNewString(vm, "my_module");
   Value var_name = wrenNewString(vm, "aaa");
   //wrenSetSlotString(vm,1,"aaaa"); 
    Value val =  wrenGetModuleVariable(vm,module_name,var_name);
   //  const char * v = wrenGetSlotString(vm,1);
   int slot = 0;
   int slots = wrenGetSlotCount(vm);
   printf("\n\\n\n\n\n<%d>\n",slots);
    wrenGetVariable(vm,"my_module","aaa",slot);
    wrenSetSlotString(vm,slot,"haha");
    const char * res = wrenGetSlotString(vm,slot);
    printf("\n\\n\n\n\n%s\n",res);
    //exit(0);
   // printf("%s\n",val);
}

void wren_free(){
   
    wrenFreeVM(vm);
}