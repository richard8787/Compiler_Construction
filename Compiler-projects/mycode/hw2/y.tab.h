/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    BOOL = 260,
    STRING = 261,
    SEMICOLON = 262,
    INC = 263,
    DEC = 264,
    GEQ = 265,
    LEQ = 266,
    EQL = 267,
    NEQ = 268,
    ADD_ASSIGN = 269,
    SUB_ASSIGN = 270,
    MUL_ASSIGN = 271,
    QUO_ASSIGN = 272,
    REM_ASSIGN = 273,
    AND = 274,
    OR = 275,
    LPAREN = 276,
    RPAREN = 277,
    LBRACK = 278,
    RBRACK = 279,
    LBRACE = 280,
    RBRACE = 281,
    COMMA = 282,
    QUOTA = 283,
    RETURN = 284,
    IF = 285,
    ELSE = 286,
    FOR = 287,
    WHILE = 288,
    TRUE = 289,
    FALSE = 290,
    CONTINUE = 291,
    BREAK = 292,
    VOID = 293,
    PRINT = 294,
    IDENT = 295,
    INT_LIT = 296,
    FLOAT_LIT = 297,
    STRING_LIT = 298,
    BOOL_LIT = 299
  };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define BOOL 260
#define STRING 261
#define SEMICOLON 262
#define INC 263
#define DEC 264
#define GEQ 265
#define LEQ 266
#define EQL 267
#define NEQ 268
#define ADD_ASSIGN 269
#define SUB_ASSIGN 270
#define MUL_ASSIGN 271
#define QUO_ASSIGN 272
#define REM_ASSIGN 273
#define AND 274
#define OR 275
#define LPAREN 276
#define RPAREN 277
#define LBRACK 278
#define RBRACK 279
#define LBRACE 280
#define RBRACE 281
#define COMMA 282
#define QUOTA 283
#define RETURN 284
#define IF 285
#define ELSE 286
#define FOR 287
#define WHILE 288
#define TRUE 289
#define FALSE 290
#define CONTINUE 291
#define BREAK 292
#define VOID 293
#define PRINT 294
#define IDENT 295
#define INT_LIT 296
#define FLOAT_LIT 297
#define STRING_LIT 298
#define BOOL_LIT 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 188 "compiler_hw2.y"

    int i_val;
    float f_val;
    char *s_val;
    bool b_val;

    struct ctr{
        char* id_name;
        char id_type[20];
    }ctr;

#line 157 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
