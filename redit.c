#include "../rlib/rlib.h"
#include "wren_wrapper.h"

void on_before_draw(rterm_t * rterm){
    session_t * session = (session_t *)rterm->session;
    print_document(rterm);
    session->line = get_line_by_pos(rterm);
    wren_handle();

    
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
