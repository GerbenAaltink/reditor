#include <math.h>
#include "wren.h"
#include "redit.h"

WrenConfiguration config;
WrenVM *vm;

void writeFn(WrenVM *vm, const char *text)
{
  printf("%s", text);
}

const char *footer;
rterm_t *_rterm;
session_t *_session;

void wSetCursorX(WrenVM *vm)
{
  _rterm->cursor.x = (int)wrenGetSlotDouble(vm, 1);
}

void wSetCursorY(WrenVM *vm)
{
  _rterm->cursor.y = (int)wrenGetSlotDouble(vm, 1);
}

void wInsert(WrenVM *vm)
{
  const char *str = wrenGetSlotString(vm, 1);
  int pos = get_document_pos(_rterm);
  for (size_t i = 0; i < strlen(str); i++)
  {
    document_insert_char(_rterm, pos, str[i]);
  }
}
void wExit(WrenVM *vm)
{
  rterm_clear_screen();
  printf("Exited by plugin: %s\n", wrenGetSlotString(vm, 1));
  exit(0);
}
void wGetDocumentPos(WrenVM *vm)
{
  wrenSetSlotDouble(vm, 0, get_document_pos(_rterm));
}
void wGetLineIndex(WrenVM *vm)
{
  wrenSetSlotDouble(vm, 0, get_document_pos(_rterm));

  // wrenSetSlotDouble(vm,0,get_(_rterm));
}
void wGetCursorX(WrenVM *vm)
{
  wrenSetSlotDouble(vm, 0, (double)_rterm->cursor.x);
}

void wGetCursorY(WrenVM *vm)
{
  wrenSetSlotDouble(vm, 0, (double)_rterm->cursor.y);
}
void wGetLine(WrenVM *vm)
{
  wrenSetSlotString(vm, 0, _session->line);
}

void wsetFooter(WrenVM *vm)
{
  _rterm->status_text = (char *)wrenGetSlotString(vm, 1);
}

WrenForeignMethodFn bindForeignMethodFn(
    WrenVM *vm,
    const char *module,
    const char *className,
    bool isStatic,
    const char *signature)

{

  // printf("JAA OOOR %s\n",signature)
  if (!strcmp(signature, "setCursorX(_)"))
  {
    return wSetCursorX;
  }
  if (!strcmp(signature, "setCursorY(_)"))
  {
    return wGetCursorY;
  }
  if (!strcmp(signature, "getDocumentPos()"))
  {
    return wGetDocumentPos;
  }
  if (!strcmp(signature, "getLineIndex()"))
  {
    return wGetLineIndex;
  }
  if (!strcmp(signature, "getCursorX()"))
  {
    return wGetCursorX;
  }
  if (!strcmp(signature, "getCursorY()"))
  {
    return wGetCursorY;
  }
  if (!strcmp(signature, "insert(_)"))
  {
    return wInsert;
  }
  else if (!strcmp(signature, "setFooter(_)"))
  {

    return wsetFooter;
  }
  else if (!strcmp(signature, "getLine()"))
  {
    return wGetLine;
  }
  else if (!strcmp(signature, "exit(_)"))
  {
    return wExit;
  }
  printf("Uncatched: %s\n", signature);
  exit(3);
}

void wren_interpret_string(char *str)
{
  WrenInterpretResult result = wrenInterpret(vm, "main", str);
  switch (result)
  {
  case WREN_RESULT_COMPILE_ERROR:
  {
    printf("Compile Error!\n");
    exit(2);
  }
  break;
  case WREN_RESULT_RUNTIME_ERROR:
  {
    printf("Runtime Error!\n");
    exit(2);
  }
  break;
  case WREN_RESULT_SUCCESS:
  {
  }
  break;
  }
}

void wren_interpret_file(char *path)
{
  size_t file_length = rfile_size(path);
  char file_content[file_length + 1];
  rfile_readb(path, file_content, file_length);
  file_content[file_length] = 0;
  wren_interpret_string(file_content);
}

void wren_init(rterm_t *rterm)
{
  _rterm = rterm;
  _session = (session_t *)rterm->session;

  wrenInitConfiguration(&config);
  config.writeFn = &writeFn;
  config.bindForeignMethodFn = &bindForeignMethodFn;

  vm = wrenNewVM(&config);
  wrenEnsureSlots(vm, 100);
  // bindForeignMethodFn(vm,"my_module","Editor",false,"setFooter(x,y)");
  // ByteBuffer bf = wrenBindMethod(     )
  char str_class_source[1024] = {0};
  strcat(str_class_source, "var globals = {}\n");
  strcat(str_class_source, "class Editor{\n");
  strcat(str_class_source, "foreign static getLine() \n");
  strcat(str_class_source, "foreign static setFooter(text) \n");
  strcat(str_class_source, "foreign static insert(text) \n");

  strcat(str_class_source, "foreign static getCursorX() \n");

  strcat(str_class_source, "foreign static getCursorY() \n");
  strcat(str_class_source, "foreign static getLineIndex() \n");
  strcat(str_class_source, "foreign static getDocumentPos() \n");
  strcat(str_class_source, "foreign static setCursorX(value) \n");
  strcat(str_class_source, "foreign static setCursorY(value) \n");
  strcat(str_class_source, "foreign static exit(msg) \n");

  strcat(str_class_source, "}\n");
  strcat(str_class_source, "Editor.setFooter(\"Loading...\")\n");
  printf("%s\n", str_class_source);
  wren_interpret_string(str_class_source);

  wren_interpret_file("init.wren");
}

void wren_key_press(char *key)
{
  char cmd[1024] = {0};
  sprintf(cmd, "plugin.keyPress(\"%s\")", key);
  wren_interpret_string(cmd);
}

void wren_handle()
{
  wren_interpret_string("plugin.tick()");
  // wren_interpret_file("plugin.wren");
  // WrenHandle * handle = wrenMakeCallHandle(vm,"Plugin.tick()");
  // wrenCall(vm, handle);
  //  wrenCall()
  //  wren_interpret_string("tick()");
  //  wren_interpret_string("tick()");

  //   wrenGetVariable(vm,"main","plugin",0);

  //  WrenHandle * handle = wrenMakeCallHandle(vm, "tick()");
  //  wrenCall(vm,handle);
}

void wren_free()
{

  wrenFreeVM(vm);
}