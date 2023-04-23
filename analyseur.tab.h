/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ANALYSEUR_TAB_H_INCLUDED
# define YY_YY_ANALYSEUR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 15 "analyseur.y"

    #include "figures.h"

#line 53 "analyseur.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ALL = 258,                     /* ALL  */
    AT = 259,                      /* AT  */
    CIRCLE = 260,                  /* CIRCLE  */
    COPY = 261,                    /* COPY  */
    CREATE = 262,                  /* CREATE  */
    DELETE = 263,                  /* DELETE  */
    DESELECT = 264,                /* DESELECT  */
    DO = 265,                      /* DO  */
    DONE = 266,                    /* DONE  */
    DUMP = 267,                    /* DUMP  */
    ELLIPSE = 268,                 /* ELLIPSE  */
    FILL = 269,                    /* FILL  */
    FONTSIZE = 270,                /* FONTSIZE  */
    FOREACH = 271,                 /* FOREACH  */
    INVISIBLE = 272,               /* INVISIBLE  */
    LINE = 273,                    /* LINE  */
    MOVE = 274,                    /* MOVE  */
    NOFILL = 275,                  /* NOFILL  */
    POLYGON = 276,                 /* POLYGON  */
    RADIUS = 277,                  /* RADIUS  */
    RENAME = 278,                  /* RENAME  */
    RECTANGLE = 279,               /* RECTANGLE  */
    ROTATE = 280,                  /* ROTATE  */
    SELECT = 281,                  /* SELECT  */
    SET = 282,                     /* SET  */
    TEXT = 283,                    /* TEXT  */
    THICKNESS = 284,               /* THICKNESS  */
    VISIBLE = 285,                 /* VISIBLE  */
    WITH = 286,                    /* WITH  */
    ZOOM = 287,                    /* ZOOM  */
    EOL = 288,                     /* EOL  */
    VIRGULE = 289,                 /* VIRGULE  */
    NOM = 290,                     /* NOM  */
    COORD = 291,                   /* COORD  */
    NUM = 292,                     /* NUM  */
    CHAINE_CAR = 293,              /* CHAINE_CAR  */
    COULEUR = 294,                 /* COULEUR  */
    DIMENSION = 295,               /* DIMENSION  */
    REAL = 296                     /* REAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "analyseur.y"

    Figure figure;
    char* str;
    char* couleur;
    char* nom;
    char* coord;
    char* dimensions;
    int entier;
    Options* opt;
    float real;

#line 123 "analyseur.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ANALYSEUR_TAB_H_INCLUDED  */
