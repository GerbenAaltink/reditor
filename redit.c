#include "../rlib/rlib.h"
#include "wren_wrapper.h"

void on_before_draw(rterm_t * rterm){
    session_t * session = (session_t *)rterm->session;
    print_document(rterm);
    session->line = get_line_by_pos(rterm);
    wren_handle();

    
}

char * key_to_str(rterm_t * rterm){
    static char key[1024];
    memset(key,0,sizeof(key));
    
    if(rterm->key.ctrl){
        strcat(key,"Ctrl+");
    }
    if(rterm->key.escape){
        strcat(key, "Esc+");
    }
    
    
    key[strlen(key)] = rterm->key.c;;
    return key;
}

void on_key(rterm_t * rterm){

    session_t * session = (session_t * )rterm->session;
    if(!rterm->key.ctrl && !rterm->key.shift){
    
    }
    if(rterm->key.c == 67 || rterm->key.c == 88){
        session->original_x = rterm->cursor.x;
    }
    if(rterm->key.c == 66 || rterm->key.c == 65){
        
        if(rterm->cursor.y >= rterm->size.ws_row - 1){
            move_document(rterm,1);
            rterm->cursor.y--; 
        }
        if(rterm->cursor.y < 1){
            rterm->cursor.y = 0;
            move_document(rterm,-1);
        }
    }
    
    int pos = get_document_pos(rterm);
    
   // printf("%d\n", pos);
    if(!rterm->key.escape){
       document_insert_char(rterm,pos,rterm->key.c);
         if(rterm->key.c == 10){
            rterm->cursor.x = 0;
            rterm->cursor.y++;
       }else{ 
    //session->document[pos] = rterm->key.c;
    rterm_move_cursor(rterm->cursor.y,rterm->cursor.x++);
       }
    }else{
      
    }
    if(rterm->key.shift){
        exit(0);
    }
    wren_key_press(key_to_str(rterm));
}

void on_after_cursor_move(rterm_t * rterm){
   // print_document(rterm);

}
int main() {
    setbuf(stdout,NULL);
   
    session_t session;
    session.file_size = rfile_size("redit.c");
    session.document = (char *)rmalloc(session.file_size);
    session.original_x = 0;
    
    rfile_readb("redit.c",session.document,session.file_size);
    
    rterm_t rterm;
    rterm_init(&rterm);
    rterm.session = (void *)&session;
    rterm.before_draw = on_before_draw;;
    rterm.before_cursor_move = on_before_cursor_move;
    rterm.after_cursor_move = on_after_cursor_move;
    rterm.after_key_press = on_key;
     wren_init(&rterm);
    rterm_loop(&rterm);



}
