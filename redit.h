
#ifndef REDIT_H
#define REDIT_H
#include "../rlib/rlib.h"
typedef struct session_t {
    char * document;
    int first_line;
    size_t file_size;
    int original_x;   
    char * line; 
} session_t;

char * get_line_by_pos(rterm_t *rterm);
int get_document_pos(rterm_t *rterm);

void * print_document(rterm_t * rterm)
{
    session_t * session = (session_t *)rterm->session;
    rterm_clear_screen();
    char * document = session->document;
    char new_document[strlen(document)+1];
    char *new_document_ptr = new_document;
    new_document[0] = 0;
    int line = 0;
    int line_count = 0;
    int max_lines = rterm->size.ws_row - 1;
    for(int i = 0; i < rterm->cursor.available; i++){
        if(!*document){
            break;
        }
         
        if(*document == '\n'){
            line_count++;
            line++;
        }
        

        if(line - session->first_line - 1 == max_lines)
            break;
        if(line >= session->first_line){
            *new_document_ptr = *document;
            *new_document_ptr++;;
        }
        document++;
    }*new_document_ptr = 0;
    printf("%s",new_document);
}

void move_document(rterm_t * rterm,int pos){
    session_t * session = (session_t *)rterm->session;
    if(session->first_line == 0 && pos < 0){
     //   return;
    }else{
    ///if(session->first_line && pos < 0)
        session->first_line += pos;
    }
    //else //if (session->first_line !=rterm->size.ws_row -1)
    //session->first_line += pos;
    
    print_document(rterm);
}

void on_before_cursor_move(rterm_t * rterm){
    size_t length = strlen(get_line_by_pos(rterm));
    if(rterm->cursor.x > length){
        rterm->cursor.x = length;
    }
    

}

void document_insert_char(rterm_t * rterm, int pos, char chr){
    session_t * session = (session_t *)rterm->session;
    char * new_document = (char *)malloc(strlen(session->document)+10);
    char * document_ptr = session->document;
    strcpy(new_document,session->document);
    new_document[pos] = chr;
    new_document[pos + 1] = 0;
    session->document += pos;
    strcat(new_document,session->document);
    //session->document += pos;
    //strcat(new_document,(char *){chr,0});
    //strcat(new_document, session->document);
    free(document_ptr);
    session->document = new_document;
}



int get_document_pos(rterm_t *rterm){
    session_t * session = (session_t *)rterm->session;

    int to_pos = 0;
    char * document = session->document;
    static char line[4096];
    int line_index = 0;
    int line_count = 0;
    int posx = 0;

    //int res = rterm->cursor.y * rterm->size.ws_col + rterm->cursor.x;
    
    while(true){
        line[line_index] = *document;
        line_index++;
        
        if(line_count >= rterm->cursor.y + session->first_line){
                to_pos += rterm->cursor.x;
                break;
            }

        if(*document == '\n'){
            
            
            line_count++;
            line_index = 0;
            posx = 0;
        }
        
        document++;
        to_pos++;
        posx++;
    }
    line[line_index-1] = 0;
    return to_pos;
}

char * get_line_by_pos(rterm_t *rterm){
    session_t * session = (session_t *)rterm->session;

    int to_pos = 0;
    char * document = session->document;
    static char line[4096];
    int line_index = 0;
    int line_count = 0;
    while(true){
        line[line_index] = *document;
        line_index++;
        
        if(*document == '\n'){
            
            if(line_count >= rterm->cursor.y + session->first_line){
                break;
            }
            line_count++;
            line_index = 0;
        }
        document++;
        to_pos++;
    }
    line[line_index-1] = 0;
    return line;
}

#endif 