/*   */

#include <stdio.h>
#include "include/lex.h"
#include "include/modified_parser.h"
#include "include/managers.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;


static int ddCount;
stringstream mainCode;
stringstream dataSection;
set<string> idCollection;
RegisterManager registerManager;// = new RegisterManager();
LabelManager labelManager;// = new LabelManager();


int getDDCount(){
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
    dataSection << "org 100h\n\n";    
    ddCount = 800;
    while(1){
        if(match(EOI))
            break;
        statement();
        mainCode<<"\n";
    }
    dataSection <<" JMP start \n";
    cout<< dataSection.str() << "\nstart:"<<endl;
    cout<< mainCode.str() << "\nRET" <<endl;
}

void statement(){
    
    /*  stmt -> ID ASSIGN expr SEMI 
                IF expr THEN stmt_list 
                WHILE expr DO stmt_list 
                BEGIN stmt_list END 
                 */
    
    if (!legal_lookahead(NUM,ID,IF,WHILE,BEGIN,LP))
    {
        fprintf(stderr, "ERROR: Expected token at line %d\n", yylineno);
        assert(6==4);        
        return;
    }
    if (match(ID)){
        string currentID = getCurrentToken();
        if (idCollection.find(currentID) == idCollection.end()){
            dataSection<<currentID<<" DD "<<getDDCount()<<endl;
            idCollection.insert(currentID);
        }
        advance();
        
        if(match(EQ)){
            advance();
            int currentRegister = expression();
            mainCode << "MOV " << currentID << " , " << registerManager.getRegName(currentRegister)<<endl;
            
            registerManager.deallocReg(currentRegister);
            
            //Check SemiColon;
            if(match(SEMI)){
               advance();
               return;
            }
            else{
                fprintf(stderr,"Equality Statement without semi colon not valid.");                
                assert(5==4);
                return;
            }
        }
        else{
            fprintf(stderr,"No Equals in Assign statement. ");            
            assert(5==4);
            return;
        }
    }
    
    
    //Check for reserved keywords IF
    if (match(IF)){
        advance();
        int outputExpression = expression();
        string labelIfEnd = labelManager.getLabel();
        //mainCode << labelIf <<" :\n";
        mainCode<< "CMP "<< registerManager.getRegName(outputExpression)<<", 1"<<endl;
        
        registerManager.deallocReg(outputExpression);
        //registerManager.deallocReg(expression());
        
        mainCode<<"\n JNZ " << labelIfEnd <<"\n";
        if(match(THEN)){            
            advance();
            statement();
            mainCode << "\n" << labelIfEnd <<":\n";
            return ;
        }
        else{
            fprintf(stderr,"if without then is invalid.");        
            assert(5==4);
            return;
        }  
    }
    
    if(match(WHILE)){
        advance();
        string labelWhileBegin = labelManager.getLabel();
        mainCode<<labelWhileBegin<<":\n";
        int outputExpression = expression();
        mainCode << "CMP " << registerManager.getRegName( outputExpression )<<", 1"<<endl;
        registerManager.deallocReg(outputExpression);
        //registerManager.deallocReg(expression());
        string labelWhileEnd = labelManager.getLabel();
        mainCode << "JNZ " << labelWhileEnd << "\n";  
        if (match(DO)){
            advance();
            statement();
            mainCode << "JMP "<< labelWhileBegin<< endl;
            mainCode << "\n" << labelWhileEnd << ":\n";

        }
        else{
            fprintf(stderr,"while without do is invalid");            
            assert(5==4);
            return;
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
            return;
        }
        else{
            fprintf(stderr,"begin without end is not valid at line no %d",yylineno);
            assert(5==4);
            return;
        }       
    }
    
    /*expression();
    if(match(SEMI)){
       advance(); 
    }
    else{*/
        fprintf(stderr,"An expression without semicolon is invalid.");        
        assert(5==4);
        return;
    //}
    
}

string jumpOn(int relationalOperator){
     if(relationalOperator == GR)
       return "JNG ";
     if (relationalOperator == LS)
       return "JNL ";
     return "JNZ ";
}

int expression(){
    //expr -> sub_expr expr'
    //expr' -> EQQ sub_expr | LT sub_expr | GT sub_expr 

    int subExpressionReturn,oldValue;
    int tempRegisterValue,relationalOperator;
    string labelEq,labelEqq;
    //bool noExpressionPrime = true;
    subExpressionReturn = subExpression();
    
    if(match(EQQ))
      relationalOperator = EQQ;
    if(match(GR))
      relationalOperator = GR;
    if(match(LS))
       relationalOperator = LS;
           
    if (match(EQQ)|| match(LS)|| match(GR)){
        mainCode << " PUSH "<< registerManager.getRegName(subExpressionReturn)<<endl;
    
        advance();

        registerManager.deallocReg(subExpressionReturn);    
        
        subExpressionReturn = subExpression();
        oldValue = registerManager.allocReg();
        mainCode<<" POP "<< registerManager.getRegName(oldValue)<<endl;
        mainCode<<" CMP "<< registerManager.getRegName(oldValue) <<" , "<< registerManager.getRegName(subExpressionReturn)<<endl;
        //Deallocation
        registerManager.deallocReg(subExpressionReturn);
        registerManager.deallocReg(oldValue);
      
        tempRegisterValue = registerManager.allocReg();
        labelEq = labelManager.getLabel();
        mainCode<< jumpOn(relationalOperator) << labelEq <<"\n";
        mainCode<<"MOV "<< registerManager.getRegName(tempRegisterValue) << ", 1\n";
        labelEqq = labelManager.getLabel();
        mainCode <<"JMP "<< labelEqq<< endl;
        mainCode<< labelEq<<":\n";
        mainCode<< "MOV "<< registerManager.getRegName(tempRegisterValue) <<", 0\n";
        mainCode<<labelEqq<<":\n";
        
        return tempRegisterValue;
        //codeSection<<" JNZ "<< labelManager.getLabel();
    }
    else{
      return subExpressionReturn;
    }
}


int subExpression(){
// sub_expr -> term pm_expr
// pm_expr -> MINUS term pm_expr | PLUS term pm_expr | EPS
    int termOne = term();
    if ( match(MINUS) )
    {
        mainCode << "PUSH " << registerManager.getRegName(termOne) <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << registerManager.getRegName(termOne) <<endl;
        mainCode << "SUB " << registerManager.getRegName(termOne) << " , " << registerManager.getRegName(termTwo) <<endl;
        registerManager.deallocReg(termTwo);
    }
    else if( match(PLUS) )
    {
        mainCode << "PUSH " << registerManager.getRegName(termOne) <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << registerManager.getRegName(termOne) <<endl;
        mainCode << "ADD " << registerManager.getRegName(termOne) << " , " << registerManager.getRegName(termTwo) <<endl;
        registerManager.deallocReg(termTwo);
    }
    return termOne;
}

int plusMinusExpression(){
// sub_expr -> term pm_expr
// pm_expr -> MINUS term pm_expr | PLUS term pm_expr | EPS
    int termOne = term();
    if ( match(MINUS) )
    {
        mainCode << "PUSH " << registerManager.getRegName(termOne) <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << registerManager.getRegName(termOne) <<endl;
        mainCode << "SUB " << registerManager.getRegName(termOne) << " , " << registerManager.getRegName(termTwo) <<endl;
        registerManager.deallocReg(termTwo);
    }
    else if( match(PLUS) )
    {
        mainCode << "PUSH " << registerManager.getRegName(termOne) <<endl;
        registerManager.deallocReg(termOne);
        advance();
        int termTwo = plusMinusExpression();
        termOne = registerManager.allocReg();
        mainCode << "POP " << registerManager.getRegName(termOne) <<endl;
        mainCode << "ADD " << registerManager.getRegName(termOne) << " , " << registerManager.getRegName(termTwo) <<endl;
        registerManager.deallocReg(termTwo);
    }
    return termOne;
}


int term(){
    int factorValReg = factor();
    mainCode << "PUSH " << registerManager.getRegName(factorValReg) << endl;
    registerManager.deallocReg(factorValReg);
    return mulTerm();
}

int mulTerm(){
    if(match(MUL)){
        advance();
        int termValReg = term();
        mainCode << "POP ax" << endl;
        mainCode << "MUL " << registerManager.getRegName(termValReg) << endl;
        mainCode << "MOV " << registerManager.getRegName(termValReg) << ",ax" << endl;
        return termValReg;
    }
    else{
        return divTerm();
    }
}


int divTerm(){
    // if(!legal_lookahead(DIV)){
    //     fprintf(stderr, "ERROR: Expected token DIV at line %d\n", yylineno);        
    //     assert(5==4);
    //     return -1;
    // }

    
    int reg = registerManager.allocReg();

    if(match(DIV)){
        advance();
        int termValReg = term();
        mainCode << "POP ax" << endl;
        mainCode << "DIV " << registerManager.getRegName(termValReg) << endl;
        registerManager.deallocReg(termValReg);
        mainCode << "MOV " << registerManager.getRegName(reg) << ", ax" << endl;
    }
    else{
        mainCode << "POP ax" << endl;
        mainCode << "MOV " << registerManager.getRegName(reg) << ", ax" << endl;
    }
    return reg;
}

int factor(){
    if(!legal_lookahead(NUM,ID,LP,0)){
        fprintf(stderr, "ERROR: Expected token at line %d\n", yylineno);
        assert(5==4);
        return -1;
    }
    if(match(NUM)){
        int reg = registerManager.allocReg();
        string currLiteral = getCurrentToken();
        mainCode << "MOV " << registerManager.getRegName(reg) << ","<< currLiteral << endl;
        advance();
        return reg;
    }
    if(match(ID)){
        int reg = registerManager.allocReg();
        string currId = getCurrentToken();
        // If not already present then only allow on RHS
        if(idCollection.find(currId) == idCollection.end()){                
            fprintf(stderr, "declaration error at line no %d\n",yylineno);        
            assert(6==4);
            return -1;
        }
        mainCode << "MOV " << registerManager.getRegName(reg) << " , " << currId << endl;
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
        assert(5==4);
        return -1;
    }
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
