/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    ASSIGN = 258,
    BEG = 259,
    COLON = 260,
    COMMA = 261,
    DO = 262,
    DOT = 263,
    ELSE = 264,
    END = 265,
    FORWARD = 266,
    FUNCTION = 267,
    IF = 268,
    LBRAC = 269,
    NOT = 270,
    OUTPUT = 271,
    PARAMSTR = 272,
    PROGRAM = 273,
    RBRAC = 274,
    REPEAT = 275,
    SEMIC = 276,
    THEN = 277,
    UNTIL = 278,
    VAL = 279,
    VAR = 280,
    WHILE = 281,
    WRITELN = 282,
    OR = 283,
    AND = 284,
    GREATER = 285,
    LESS = 286,
    GEQUAL = 287,
    LEQUAL = 288,
    EQUALS = 289,
    DIFFERENT = 290,
    PLUS = 291,
    MINUS = 292,
    MULT = 293,
    DIV = 294,
    MOD = 295,
    RESERVED = 296,
    ID = 297,
    INTLIT = 298,
    REALLIT = 299,
    STRING = 300
  };
#endif
/* Tokens.  */
#define ASSIGN 258
#define BEG 259
#define COLON 260
#define COMMA 261
#define DO 262
#define DOT 263
#define ELSE 264
#define END 265
#define FORWARD 266
#define FUNCTION 267
#define IF 268
#define LBRAC 269
#define NOT 270
#define OUTPUT 271
#define PARAMSTR 272
#define PROGRAM 273
#define RBRAC 274
#define REPEAT 275
#define SEMIC 276
#define THEN 277
#define UNTIL 278
#define VAL 279
#define VAR 280
#define WHILE 281
#define WRITELN 282
#define OR 283
#define AND 284
#define GREATER 285
#define LESS 286
#define GEQUAL 287
#define LEQUAL 288
#define EQUALS 289
#define DIFFERENT 290
#define PLUS 291
#define MINUS 292
#define MULT 293
#define DIV 294
#define MOD 295
#define RESERVED 296
#define ID 297
#define INTLIT 298
#define REALLIT 299
#define STRING 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 13 "mpaparser.y" /* yacc.c:1909  */

	char *str;

#line 148 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
