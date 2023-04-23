%{

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "figures.h"

int yyerror(char*);
int yylex();

Image image ;

%}

%code requires {
    #include "figures.h"
}

%union{
    Figure figure;
    char* str;
    char* couleur;
    char* nom;
    char* coord;
    char* dimensions;
    int entier;
    Options* opt;
    float real;
}


%token ALL AT CIRCLE COPY CREATE DELETE DESELECT DO DONE DUMP ELLIPSE FILL FONTSIZE FOREACH INVISIBLE LINE MOVE NOFILL POLYGON RADIUS RENAME RECTANGLE ROTATE SELECT SET TEXT THICKNESS VISIBLE WITH ZOOM EOL VIRGULE
%token <nom> NOM 
%token <coord> COORD 
%token <entier> NUM 
%token <str> CHAINE_CAR
%token <couleur> COULEUR
%token <dimensions> DIMENSION  
%token <real> REAL

%type <opt> SetOptions

%start S
%%

S:
    Command                 { }
  | S Command               { }
  ;


Command:
    EOL {printf("VIDE\n");}
    | CommandCreate EOL {}
    | CommandDump EOL {}
    | CommandDelete EOL {}
    | CommandRename EOL {}
    | CommandSet EOL {}
    | CommandSelect EOL {}
    | CommandZoom EOL {}
    | CommandMove EOL {}
    | CommandDeselect EOL {}
    ;

CommandCreate:
    CREATE CIRCLE NOM AT COORD RADIUS NUM          {Add_figure(&image,Create_circle($3,$5,$7)); }
  | CREATE CIRCLE NOM RADIUS NUM AT COORD      {Add_figure(&image,Create_circle($3,$7,$5));}
  | CREATE LINE NOM COORD COORD      {Add_figure(&image,Create_line($3,$4,$5));}
  | CREATE RECTANGLE NOM AT COORD DIMENSION      {Add_figure(&image,Create_rectangle($3,$5,$6));}
  | CREATE RECTANGLE NOM DIMENSION AT COORD      {Add_figure(&image,Create_rectangle($3,$6,$4));}
  | CREATE TEXT NOM AT COORD CHAINE_CAR     {Add_figure(&image,Create_text($3,$6,$5));}
  | CREATE TEXT NOM CHAINE_CAR AT COORD     {Add_figure(&image,Create_text($3,$4,$6));}
  ;

CommandDump:
  DUMP {Dump_figures(image);}
  | DUMP CHAINE_CAR {Dump_figures_file(image,$2);}
  ;

CommandDelete:
  DELETE NOM {Delete_figure(&image,$2);}
  ;

CommandRename:
  RENAME NOM WITH NOM {Rename_figure(&image,$2,$4);}
  ;

CommandSet:
  SET NOM SetOptions {Set_options(&image,$2,$3);}
  ;

SetOptions:
  %empty {$$ = Default_options();}
  | COULEUR SetOptions {$$ = Set_couleur_tour($2,$1);}
  | THICKNESS NUM SetOptions {$$ = Set_epaisseur($3,$2);}
  | FILL WITH COULEUR SetOptions {$$ = Set_couleur_remplissage($4,$3); }
  | NOFILL SetOptions {$$ = Set_couleur_remplissage($2,"transparent");}
  | INVISIBLE SetOptions {$$ = Set_visibility($2,"hidden");}
  | VISIBLE SetOptions {$$ = Set_visibility($2,"visible");}
  | FONTSIZE NUM SetOptions {$$ = Set_fontsize($3,$2);}
  ;

CommandSelect:
  SELECT ALL {Set_selected_all(&image,1);}
  | SELECT NOM SelectNames {Set_selected(&image,$2,1);}
  ;

SelectNames:
  %empty {}
  |  VIRGULE NOM SelectNames {Set_selected(&image,$2,1);}
  ;

CommandDeselect:
  DESELECT ALL {Set_selected_all(&image,0);}
  | DESELECT NOM DeselectNames {Set_selected(&image,$2,0);}
  ;

DeselectNames:
  %empty {}
  |  VIRGULE NOM DeselectNames {Set_selected(&image,$2,0);}
  ;


CommandMove:
  MOVE COORD {Move(&image,$2);}
  ;

CommandZoom:
  ZOOM REAL {Zoom(&image,$2);}
  ;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(int argc, char **argv) {
    Init_image(&image);

    if(argc == 2){
      fprintf(stdout,"MODE NON-INTERACTIF\n");
      FILE * sfd = fopen(argv[1], "r" );
      int fd = fileno(sfd);
      dup2(fd,0);
    }
   
    yyparse();
}