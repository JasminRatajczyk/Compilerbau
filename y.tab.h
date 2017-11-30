
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMENTSTART = 258,
     COMMENTEND = 259,
     PLUS = 260,
     MINUS = 261,
     MUL = 262,
     DIV = 263,
     KLA_AUF = 264,
     KLA_ZU = 265,
     ODD = 266,
     EQUAL = 267,
     NEQUAL = 268,
     LESS = 269,
     LEQUAL = 270,
     GREATER = 271,
     GREQUAL = 272,
     COMMA = 273,
     SEMICOLON = 274,
     PERIOD = 275,
     BECOME = 276,
     BEGINSYM = 277,
     END = 278,
     IF = 279,
     THEN = 280,
     WHILE = 281,
     DO = 282,
     CALL = 283,
     CONST = 284,
     INT = 285,
     PROCEDURE = 286,
     OUT = 287,
     IN = 288,
     ELSE = 289,
     ZAHL = 290,
     VARIABLE = 291,
     STRING = 292,
     FEHLER = 293
   };
#endif
/* Tokens.  */
#define COMMENTSTART 258
#define COMMENTEND 259
#define PLUS 260
#define MINUS 261
#define MUL 262
#define DIV 263
#define KLA_AUF 264
#define KLA_ZU 265
#define ODD 266
#define EQUAL 267
#define NEQUAL 268
#define LESS 269
#define LEQUAL 270
#define GREATER 271
#define GREQUAL 272
#define COMMA 273
#define SEMICOLON 274
#define PERIOD 275
#define BECOME 276
#define BEGINSYM 277
#define END 278
#define IF 279
#define THEN 280
#define WHILE 281
#define DO 282
#define CALL 283
#define CONST 284
#define INT 285
#define PROCEDURE 286
#define OUT 287
#define IN 288
#define ELSE 289
#define ZAHL 290
#define VARIABLE 291
#define STRING 292
#define FEHLER 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


