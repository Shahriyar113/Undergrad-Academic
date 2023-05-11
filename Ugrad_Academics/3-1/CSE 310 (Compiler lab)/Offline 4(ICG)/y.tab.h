/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    INT = 259,                     /* INT  */
    FOR = 260,                     /* FOR  */
    DO = 261,                      /* DO  */
    WHILE = 262,                   /* WHILE  */
    FLOAT = 263,                   /* FLOAT  */
    VOID = 264,                    /* VOID  */
    SWITCH = 265,                  /* SWITCH  */
    DEFAULT = 266,                 /* DEFAULT  */
    ELSE = 267,                    /* ELSE  */
    CHAR = 268,                    /* CHAR  */
    BREAK = 269,                   /* BREAK  */
    DOUBLE = 270,                  /* DOUBLE  */
    RETURN = 271,                  /* RETURN  */
    CASE = 272,                    /* CASE  */
    CONTINUE = 273,                /* CONTINUE  */
    ADDOP = 274,                   /* ADDOP  */
    MULOP = 275,                   /* MULOP  */
    INCOP = 276,                   /* INCOP  */
    DECOP = 277,                   /* DECOP  */
    ASSIGNOP = 278,                /* ASSIGNOP  */
    NOT = 279,                     /* NOT  */
    RELOP = 280,                   /* RELOP  */
    LOGICOP = 281,                 /* LOGICOP  */
    LPAREN = 282,                  /* LPAREN  */
    RPAREN = 283,                  /* RPAREN  */
    LCURL = 284,                   /* LCURL  */
    RCURL = 285,                   /* RCURL  */
    LTHIRD = 286,                  /* LTHIRD  */
    RTHIRD = 287,                  /* RTHIRD  */
    COMMA = 288,                   /* COMMA  */
    SEMICOLON = 289,               /* SEMICOLON  */
    STRING = 290,                  /* STRING  */
    PRINTLN = 291,                 /* PRINTLN  */
    ID = 292,                      /* ID  */
    CONST_INT = 293,               /* CONST_INT  */
    CONST_FLOAT = 294,             /* CONST_FLOAT  */
    CONST_CHAR = 295,              /* CONST_CHAR  */
    WITHOUT_ELSE = 296             /* WITHOUT_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define INT 259
#define FOR 260
#define DO 261
#define WHILE 262
#define FLOAT 263
#define VOID 264
#define SWITCH 265
#define DEFAULT 266
#define ELSE 267
#define CHAR 268
#define BREAK 269
#define DOUBLE 270
#define RETURN 271
#define CASE 272
#define CONTINUE 273
#define ADDOP 274
#define MULOP 275
#define INCOP 276
#define DECOP 277
#define ASSIGNOP 278
#define NOT 279
#define RELOP 280
#define LOGICOP 281
#define LPAREN 282
#define RPAREN 283
#define LCURL 284
#define RCURL 285
#define LTHIRD 286
#define RTHIRD 287
#define COMMA 288
#define SEMICOLON 289
#define STRING 290
#define PRINTLN 291
#define ID 292
#define CONST_INT 293
#define CONST_FLOAT 294
#define CONST_CHAR 295
#define WITHOUT_ELSE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "1805113.y"


int integer_val;
double double_val;
char char_val;
SymbolInfo *symbol;
vector<SymbolInfo*> *symbols;




#line 161 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
