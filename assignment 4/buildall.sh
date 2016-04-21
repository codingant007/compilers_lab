bison -tvd -Wconflicts-sr mad_parser.y 2> blah
flex -omad_flex.cpp mad_lexer.l
g++ mad_parser.tab.c mad_flex.cpp -o mad_output.out
