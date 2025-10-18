%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <map>
    #include <algorithm>
    #include "parser.tab.hpp"

    void yyerror() {
        std::cerr << "leksicka greska: " << *yytext << std::endl;
        exit(EXIT_FAILURE);
    }
%}

%%

start { return START; }

end { return END; }

string { return STRING; }

std_output { return STD_OUTPUT; }

std_error { return STD_ERROR; }

std_input { return STD_INPUT; }

print_ALL { return PRINT_ALL; }

if { return IF; }

else { return ELSE; }

"<<" { return SHL; }

">>" { return SHR; }

"==" { return EQ; }

"!=" { return NEQ; }

[a-zA-Z_][a-zA-Z_0-9]* { yylval.s = new std::string(yytext); return ID; }
 
["][^"]*["] { yylval.s = new std::string(yytext); return string; }

"//".* { }

[ \t\n] { }

[+*~(),:;={}] { return *yytext; }

. { yyerror(); }

%%