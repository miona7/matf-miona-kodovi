%option noyywrap  

%{
    #include <iostream>
    #include <cstdio>
    #include <string>
    #include <map>
    #include <bitset>
    #include "parser.tab.hpp"

    void yyerror() {
        std::cerr << "leksicka greska: " << *yytext << std::endl;
        exit(EXIT_FAILURE);
    }
%}

%%

def { return DEF; }

print { return PRINT; }

"==" { return EQ; }

"!=" { return NEQ; }

"<=" { return LEQ; }

">=" { return GEQ; }

"<<" { return SHL; }

">>" { return SHR; }

%[bdh] { yylval.c = yytext[1]; return FORMAT; } // sa yylval pristupamo polju unije

[a-zA-Z_][a-zA-Z_0-9]* { yylval.s = new std::string(yytext); return ID; }

[0-9]+ { yylval.b = atoi(yytext); return BROJ; }

[+*/%&|^~,;"()=-] { return *yytext; }

[ \t\n] { }

. { yyerror(); }

%%