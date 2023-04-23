%{
  #include "analyseur.tab.h"

  #include <stdlib.h>
  #include "utils_lex.h"
%}

integer [0-9]
nom [a-zA-Z][a-zA-Z|0-9|-|_]*
chaine_car \"(\\(.|\n)|[^\\"\n])*\"
hexa [0-9a-fA-F]
couleur #({hexa}{6}|{hexa}{3})
num -?{integer}+
coord \({num},{num}\)
dimension {num}x{num}
real {integer}+,{integer}+

%option noyywrap
%%

[Aa][Ll][Ll] {return ALL;}
[Aa][Tt] {return AT; }
[Cc][Ii][Rr][Cc][Ll][Ee] {return CIRCLE; }
[Cc][Oo][Pp][Yy] {return COPY; }
[Cc][Rr][Ee][Aa][Tt][Ee] {return CREATE ;}
[Dd][Ee][Ll][Ee][Tt][Ee] {return DELETE ;}
[Dd][Ee][Ss][Ee][Ll][Ee][Cc][Tt] {return DESELECT; }
[Dd][Oo] {return DO ;}
[Dd][Oo][Nn][Ee] {return DONE; }
[Dd][Uu][Mm][Pp] {return DUMP; } 
[Ee][Ll][Ll][Ii][Pp][Ss][Ee] {return ELLIPSE; }
[Ff][Ii][Ll][Ll] {return FILL; }
[Ff][Oo][Nn][Tt][Ss][Ii][Zz][Ee] {return FONTSIZE; }
[Ff][Oo][Rr][Ee][Aa][Cc][Hh] {return FOREACH; }
[Ii][Nn][Vv][Ii][Ss][Ii][Bb][Ll][Ee] {return INVISIBLE; }
[Ll][Ii][Nn][Ee] {return LINE; }
[Mm][Oo][Vv][Ee] {return MOVE;}
[Nn][Oo][Ff][Ii][Ll][Ll] {return NOFILL; }
[Pp][Oo][Ll][Yy][Gg][Oo][Nn] {return POLYGON; }
[Rr][Aa][Dd][Ii][Uu][Ss] {return RADIUS; }
[Rr][Ee][Nn][Aa][Mm][Ee] {return RENAME; }
[Rr][Ee][Cc][Tt][Aa][Nn][Gg][Ll][Ee] {return RECTANGLE;} 
[Rr][Oo][Tt][Aa][Tt][Ee] {return ROTATE; }
[Ss][Ee][Ll][Ee][Cc][Tt] {return SELECT; }
[Ss][Ee][Tt] {return SET; }
[Tt][Ee][Xx][Tt] {return TEXT; }
[Tt][Hh][Ii][Cc][Kk][Nn][Ee][Ss][Ss] {return THICKNESS; }
[Vv][Ii][Ss][Ii][Bb][Ll][Ee] {return VISIBLE; }
[Ww][Ii][Tt][Hh] {return WITH; }
[Zz][Oo][Oo][Mm] {return ZOOM; }
, {return VIRGULE;}

{coord} {
  yylval.coord = strdup(yytext);
  return COORD;}
{num} {
  yylval.entier = strtoul(yytext, NULL, 10);
  return NUM;}
{dimension} {
  yylval.dimensions = strdup(yytext);
  return DIMENSION;}
{couleur} {
  yylval.couleur = strdup(yytext);
  return COULEUR;}
{chaine_car} {
  char* str = string_no_quotes(yytext);
  yylval.str = strdup(yytext);
  return CHAINE_CAR;}
{nom} {
  yylval.nom = strdup(yytext);
  return NOM;}
{real} {
  yylval.real = str_to_float(yytext);
  return REAL;
}

"\n"  { return EOL; }

.     { /* On ignore */ }

%%