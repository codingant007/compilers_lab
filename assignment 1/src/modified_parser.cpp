/* Revised parser  */

#include <stdio.h>
#include "include/lex.h"
#include "include/modified_parser.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;


int ddCount;
stringstream mainCode;
stringstream dataSection;
set<int> idCollection;
RegisterManager registerManager = new RegisterManager();
LabelManagerm labelManager = new LabelManager();


getDDCount(){
    ddCount = ddCount + 100;
    return ddCount;
}
/* GRAMMAR
expr -> sub_expr expr'
expr' -> EQ sub_expr | LT sub_expr | GT sub_expr
sub_expr -> term pm_expr
pm_expr -> MINUS term pm_expr | PLUS term pm_expr | EPS
term -> factor mul_term
mul_term -> MUL term | div_term | EPS
div_term -> DIV term
factor -> NUM | ID | LP expr RP 
*/

void statementList(){
    dataSection << "org 100h\nJMP start\n";
    error = false;
    ddCount = 800;
    while(1){
        if(match(EOI))
            break;
        statement();
    }
    if (!error)
    {
     cout<< dataSection.str() << "\nstart:"<<endl;
     cout<< mainCode << "\nRET" <<endl;
    }
}

void statement(){
    
    /*  stmt -> ID ASSIGN expr SEMI 
                IF expr THEN stmt_list 
                WHILE expr DO stmt_list 
                BEGIN stmt_list END 
                expr SEMI */
    
    if (!legal_lookahead(NUM,ID,IF,WHILE,BEGIN,LP))
        return;
    
    if (match(ID)){
        string currentID = getCurrentToken();
        if (idCollection.find(currentID) == idCollection.end()){
            dataSection<<currentID<<" DD "<<getDDCount()<<endl;
        }
        advance();
        
        if(match(ASSIGN)){
            advance();
            int currentRegister = expression();
            mainCode << "MOV " << currentID << " , " << registerManager.getRegName(currentRegister);
            registerManager.deallocReg(currentRegister);
            
            //Check SemiColon;
            if(match(SEMI)){
               advance();
            }
            else{
                fprintf(stderr,"Equality Statement without semi colon not valid.");
                error = true;
            }
        }
        else{
            fprintf(stderr,"No Equals in Assign statement. ")
            error = true;
        }
        
        return;    
    }
    
    
    //Check for reserved keywords IF
    if (match(IF)){
        advance();
        registerManager.deallocReg(expression());
        if(match(THEN)){
            
            advance();
            statement();
            mainCode << "\n" << labelManager.getLabel() <<":\n";
        }
        else{
            fprintf(stderr,"if without then is invalid.");
            error = true;
        }
        
        return;
    }
    
    if(match(WHILE)){
        advance();
        mainCode<<labelManager.getLabel()<<":\n";
        registerManager.deallocReg(expression());
        
        if (match(DO)){
            advance();
            statement();
            mainCode <<"JMP "<<labelManager.freeLabel()<<"\n";
            mainCode <<labelManager.getLabel()<<"\n";
        }
        else{
            fprintf(stderr,"while without do is invalid");
            error = true;
        }
        
        return;
    }
    
    if (match(BEGIN)){
        advance();
        while(!match(EOI) && !match(END)){
            statement();
        }
        if(match(END)){
            advance();
        }
        else{
            fprintf(stderr,"begin without end is not valid");
            error = true;
        }
        
        return;
    }
    
    expression();
    if(match(SEMI)){
       advance(); 
    }
    else{
        fprintf(stderr,"An expression without semicolon is invalid.");
        error = true;
    }
    
}

int expression(){
    //expr -> sub_expr expr'
    //expr' -> EQQ sub_expr | LT sub_expr | GT sub_expr


    int subExpressionReturn,oldValue;
    bool noExpressionPrime = true;
    subExpressionReturn = subExpression();
    
    int tempEQQ,tempLS,tempGR;
    tempEQ = match(EQQ);
    tempLS = match(LS);
    tempGR = match(GR);
    
    if (match(EQQ)){
        mainCode << " PUSH "<< registerManager.getRegName(subExpression)<<endl;
    
        advance();
        registerManager.deallocReg(subExpressionReturn);    
        
        subExpressionReturn = subExpression();
        oldValue = registerManager.allocReg();
        mainCode<<" POP "<<oldValue<<endl;
        mainCode<<" CMP "<<oldValue<<" , "<< subExpressionReturn<<endl;
        //codeSection<<" JNZ "<< labelManager.getLabel();
    }
}

int  expressionPrime(){

}

int subExpression(){
// sub_expr -> term pm_expr
// pm_expr -> MINUS term pm_expr | PLUS term pm_expr | EPS
    int termOne = term();
    if ( match(MINUS) )
    {
        mainCode << "PUSH " << termOne <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << termOne <<endl;
        mainCode << "SUB " << termOne << " , " << termTwo <<endl;
    }
    else if( match(PLUS) )
    {
        mainCode << "PUSH " << termOne <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << termOne <<endl;
        mainCode << "ADD " << termOne << " , " << termTwo <<endl;
    }
    return termOne;
}

int plusMinusExpression(){
// sub_expr -> term pm_expr
// pm_expr -> MINUS term pm_expr | PLUS term pm_expr | EPS
    int termOne = term();
    if ( match(MINUS) )
    {
        mainCode << "PUSH " << termOne <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << termOne <<endl;
        mainCode << "SUB " << termOne << " , " << termTwo <<endl;
    }
    else if( match(PLUS) )
    {
        mainCode << "PUSH " << termOne <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << termOne <<endl;
        mainCode << "ADD " << termOne << " , " << termTwo <<endl;
    }
    return termOne;
}


int term(){
    int factorValReg = factor();
    mainCode << "PUSH " << registerManager.getRegName(factorValReg) << endl;
    return mulTerm();
}

int mulTerm(){
    if(match(MUL)){
        advance();
        mainCode << "POP ax" << endl;
        int termValReg = term();
        mainCode << "MUL " << registerManager.getRegName(termValreg) << endl;
        registerManager.deallocReg(termValReg);
        int reg = registerManager.allocReg();
        mainCode << "MOV " << registerManager.getRegName(reg) ",eax" << endl;
        return reg;
    }
    else{
        return divTerm();
    }
}


int divTerm(){
    if(!legal_lookahead(DIV)){
        return;
    }
    if(match(DIV)){
        advance();
        mainCode << "POP eax" << endl;
        int reg = registerManager.allocReg();
        int termValReg = term();
        mainCode << "DIV " << registerManager.getRegName(termValReg) << endl;
        mainCode << "MOV " << registerManager.getRegName(reg) << "," <<   << endl;
        ree
    }
    else{
        mainCode << "POP eax" << endl;
        int reg = registerManager.allocReg(reg);
    } 
}

int factor(){
    if(!legal_lookahead(NUM,ID,LP)){
        return;
    }
    if(match(NUM)){
        int reg = registerManager.allocReg();
        string currToken = getCurrentToken();
        mainCode << "MOV " << registerManager.getRegName(reg) ","<< currToken << endl;
        advance();
        return reg;
    }
    if(match(ID)){
        int reg = registerManager.allocReg();
        string currId = getCurrentToken();
        if(idCollection.find(currId) == idCollection.end()){
            dataSection << currId <<" DD "<<getDDCount()<<endl;
        }
        mainCode << "MOV " << registerManager.getRegName(reg) "," << currId << endl;
        advance();
        return reg;
    }
    if(match(LP)){
        advance();
        int exprValReg = expression();
        if(match(RP)){
            advance();
            return exprValReg;
        }
        fprintf(stderr,"Right parenthesis at not found at line %d\n",yylineno);
        error = true;
    }
    fprintf(stderr,"Number or Identifier or expression not found at line no %d\n"yylineno);
    error = true;
    return 0;
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
