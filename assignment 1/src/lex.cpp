#include <stdio.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <iostream>

#include "include/lex.h"

using namespace std;


char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void){

   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;

            //Relational Operators
            case '>':
             return GR;
            case '<':
             return LS;

           case '\n':
           case '\t':
           case ' ' :
            break;


           default:

           //Reserved Keywords OR Identifier

           if (isalpha(*current)){
              char tempWord[1024];
              int iterat=0;
              while(isalnum(*(current+iterat))){
                tempWord[iterat] = *(current + iterat);
                iterat++;
              }
              tempWord[iterat]='\0';
              //cout<<strcmp(tempWord,"then")<<endl;
              yyleng = current - yytext;
              if(strcmp(tempWord,"if")==0)
                //printf("a");
                return IF;
              if (strcmp(tempWord,"then")==0)
                return THEN;
              if (strcmp(tempWord,"while")==0)
                return WHILE;
              if (strcmp(tempWord,"do")==0)
                return DO;
              if (strcmp(tempWord,"begin")==0)
                return BEGIN;
              if (strcmp(tempWord,"end")==0)
                return END;

              return ID;

           }

            //Check if it's a number
            if (isdigit(*current)){
              while(isdigit(*current)){
                ++current;
              }
              yyleng = current - yytext;
              return NUM;
            }

            if ((*current) == '=' && (current+1) <=&input_buffer[1023] && *(current+1)== '=' ){
              yyleng = 2;
              return EQQ;
            }
            else if (*(current) == '='){
              return EQ;
            }


            /*
            if(!isalnum(*current))
               fprintf(stderr, "Not alphanumeric <%c>\n", *current);
            else{
               while(isalnum(*current))
                  ++current;
               yyleng = current - yytext;
               return NUM_OR_ID;
            }*/
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}

string getCurrentToken(){
  return string(yytext, yytext + yyleng);
}

// To be completed // -Nikhil
string getNextToken(){

}
