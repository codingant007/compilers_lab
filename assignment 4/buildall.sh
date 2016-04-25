bison -tvd -v -Wconflicts-sr mad_parser.y
flex -omad_flex.cpp mad_lexer.l
g++ -g mad_parser.tab.c mad_flex.cpp -o mad_output.out
