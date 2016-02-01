/* Revised parser  */

#include <stdio.h>
#include "include/lex.h"
#include "include/modified_parser.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;
//void    factor      ( void );
//void    term        ( void );
//void    expression  ( void );

/* GRAMMAR
expr -> sub_expr expr'
expr' -> EQ sub_expr | LT sub_expr | GT sub_expr
sub_expr -> term pm_expr
pm_expr -> MINUS sub_expr | plus_expr | EPS
plus_expr -> PLUS sub_expr
term -> factor mul_term
mul_term -> MUL term | div_term | EPS
div_term -> DIV term
factor -> NUM | ID | LP expr RP 
*/


void statementList(){

}

void statement(){

}

string expression(){

}

string  expressionPrime(){

}

string subExpression(){

}

string plusMinusExpression(){

}

string plusExpression(){

}

string term(){

}

string mulTerm(){

}

string divTerm(){

}

string factor(){

}

void statements()
{
    /*  statements -> expression SEMI |  expression SEMI statements */

    while( !match(EOI) )
    {
        expression();

        if( match( SEMI ) )
            advance();
        else
            fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );
    }
}

#include <stdarg.h>

#define MAXFIRST 16
#define SYNCH    SEMI

int legal_lookahead(  int first_arg ,... )
{
    /* Simple error detection and recovery. Arguments are a 0-terminated list of
     * those tokens that can legitimately come next in the input. If the list is
     * empty, the end of file must come next. Print an error message if
     * necessary. Error recovery is performed by discarding all input symbols
     * until one that's in the input list is found
     *
     * Return true if there's no error or if we recovered from the error,
     * false if we can't recover.
     */

    va_list     args;
    int     tok;
    int     lookaheads[MAXFIRST], *p = lookaheads, *current;
    int     error_printed = 0;
    int     rval          = 0;

    va_start( args, first_arg );

    if( !first_arg )
    {
    if( match(EOI) )
        rval = 1;
    }
    else
    {
    *p++ = first_arg;
    while( (tok = va_arg(args, int)) && p < &lookaheads[MAXFIRST] )
        *p++ = tok;

    while( !match( SYNCH ) )
    {
        for( current = lookaheads; current < p ; ++current )
        if( match( *current ) )
        {
            rval = 1;
            goto exit;
        }

        if( !error_printed )
        {
        fprintf( stderr, "Line %d: Syntax error\n", yylineno );
        error_printed = 1;
        }

        advance();
    }
    }

exit:
    va_end( args );
    return rval;
}
