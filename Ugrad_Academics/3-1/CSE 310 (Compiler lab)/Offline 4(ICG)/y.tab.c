/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805113.y"

//#include<bits/stdc++.h>
#include"Symbol_Table.cpp"

int yyparse(void);
int yylex(void);

extern FILE *yyin; //aita na likhle bison "yyin" k chinbe na

ofstream f_log_out("log.txt");
ofstream f_error_out("error.txt");
ofstream f_code("code.asm");
ofstream f_optimized_code("optimized_code.asm");
ifstream f_read_code;
int line_count = 1;
int total_errors = 0;

SymbolTable st(30); 

string type;
vector<SymbolInfo*> *function_definition_parameter_list;
//this variable is for creating new scope (without function definition)

bool function_scope_flag = true;  //jokhn function scope "true" thakbe tokhn "{" dekha mane oi kono akti function er scope shuru hocche


void yyerror(char *s){
	f_log_out << "Error at line " << line_count << ": Syntax Error\n";
	f_error_out << "Error at line " << line_count << ": Syntax Error\n";
	total_errors++;
}

int temp_variable_count = 0;
int label_count = 0;
string initial_code = "";
vector<pair<string, string>> data_list;

//converting a_1.1 to a_1_1
string makeScopeID(string id){
	string x = ".";
	string y = "_";
	size_t pos;
	while ((pos = id.find(x)) != std::string::npos) {
        id.replace(pos, 1, y);
    }
	return id;
}

string newTemp(){
	string temp_variable  = "t" + to_string(temp_variable_count);
	temp_variable_count++;
	data_list.push_back({temp_variable,"0"});
	return temp_variable;
}

string newLabel(){
	string label  = "l" + to_string(label_count);
	label_count++;
	return label;
}

void Optimized_Code(string filename){
	f_read_code.open(filename);
	//f_optimized_code.open("optimized_code.asm");
	string first_line;
	string second_line;
	string first_words;
	string final_first_words;
	string second_words;
	string final_second_words;

	while(getline(f_read_code,first_line)){
		vector <string> first_tokens;
		vector <string> second_tokens;
		stringstream check_first(first_line);
      
		// Tokenizing w.r.t. space ' '
		while(getline(check_first, first_words, ' ')){	
			stringstream check_first_word(first_words);
			while(getline(check_first_word, final_first_words, ',')){
				first_tokens.push_back(final_first_words);
			}
		}
		
		if(first_tokens.size() == 3 && first_tokens.at(0) == "\tmov"){
			getline(f_read_code,second_line);
			
			stringstream check_second(second_line);

			while(getline(check_second, second_words, ' ')){
				stringstream check_second_word(second_words);
				while(getline(check_second_word, final_second_words, ',')){
					second_tokens.push_back(final_second_words);
				}
			}
			if(second_tokens.size() == 3 && second_tokens.at(0) == "\tmov"){
				int match = first_tokens.at(1).compare(second_tokens.at(2));
				int match2 = first_tokens.at(2).compare(second_tokens.at(1));

				if(match == 0 && match2 == 0)
				{
				//mov ax,t1
				//mov t1,ax type found
				
				f_optimized_code <<first_line << "\n";
				f_optimized_code <<";\t"<< second_line<<"; peepholed" << "\n";	
				
				
				}
				else{
					f_optimized_code << first_line << "\n";
					//f_optimized_code << second_line << "\n";
					f_read_code.seekg(-second_line.size()-1,ios::cur);
				}	
			}
			else
			{	f_optimized_code << first_line << "\n";
				f_optimized_code << second_line << "\n";	
			}
		}	
		else
		{
		
		f_optimized_code << first_line << "\n";
		}	
	}
	f_optimized_code << "END main" << "\n";
	f_read_code.close();
	f_optimized_code.close();
}






#line 208 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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




#line 355 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_DO = 6,                         /* DO  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_SWITCH = 10,                    /* SWITCH  */
  YYSYMBOL_DEFAULT = 11,                   /* DEFAULT  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_CHAR = 13,                      /* CHAR  */
  YYSYMBOL_BREAK = 14,                     /* BREAK  */
  YYSYMBOL_DOUBLE = 15,                    /* DOUBLE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_CASE = 17,                      /* CASE  */
  YYSYMBOL_CONTINUE = 18,                  /* CONTINUE  */
  YYSYMBOL_ADDOP = 19,                     /* ADDOP  */
  YYSYMBOL_MULOP = 20,                     /* MULOP  */
  YYSYMBOL_INCOP = 21,                     /* INCOP  */
  YYSYMBOL_DECOP = 22,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 23,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_RELOP = 25,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 26,                   /* LOGICOP  */
  YYSYMBOL_LPAREN = 27,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 28,                    /* RPAREN  */
  YYSYMBOL_LCURL = 29,                     /* LCURL  */
  YYSYMBOL_RCURL = 30,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 31,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 32,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 34,                 /* SEMICOLON  */
  YYSYMBOL_STRING = 35,                    /* STRING  */
  YYSYMBOL_PRINTLN = 36,                   /* PRINTLN  */
  YYSYMBOL_ID = 37,                        /* ID  */
  YYSYMBOL_CONST_INT = 38,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 39,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 40,                /* CONST_CHAR  */
  YYSYMBOL_WITHOUT_ELSE = 41,              /* WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_start = 43,                     /* start  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_unit = 45,                      /* unit  */
  YYSYMBOL_func_declaration = 46,          /* func_declaration  */
  YYSYMBOL_func_definition = 47,           /* func_definition  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_parameter_list = 52,            /* parameter_list  */
  YYSYMBOL_compound_statement = 53,        /* compound_statement  */
  YYSYMBOL_var_declaration = 54,           /* var_declaration  */
  YYSYMBOL_type_specifier = 55,            /* type_specifier  */
  YYSYMBOL_declaration_list = 56,          /* declaration_list  */
  YYSYMBOL_statements = 57,                /* statements  */
  YYSYMBOL_statement = 58,                 /* statement  */
  YYSYMBOL_59_5 = 59,                      /* $@5  */
  YYSYMBOL_60_6 = 60,                      /* $@6  */
  YYSYMBOL_expression_statement = 61,      /* expression_statement  */
  YYSYMBOL_variable = 62,                  /* variable  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_logic_expression = 64,          /* logic_expression  */
  YYSYMBOL_rel_expression = 65,            /* rel_expression  */
  YYSYMBOL_simple_expression = 66,         /* simple_expression  */
  YYSYMBOL_term = 67,                      /* term  */
  YYSYMBOL_unary_expression = 68,          /* unary_expression  */
  YYSYMBOL_factor = 69,                    /* factor  */
  YYSYMBOL_argument_list = 70,             /* argument_list  */
  YYSYMBOL_arguments = 71                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   186

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   303,   361,   409,   441,   474,   523,   617,
     658,   847,   658,   929,   993,   929,  1076,  1132,  1172,  1190,
    1212,  1278,  1311,  1357,  1367,  1378,  1394,  1453,  1522,  1572,
    1629,  1677,  1736,  1781,  1812,  1812,  1812,  1859,  1951,  2021,
    2102,  2184,  2230,  2277,  2301,  2336,  2391,  2470,  2497,  2670,
    2696,  2764,  2790,  2859,  2885,  2940,  2967,  3093,  3137,  3164,
    3192,  3218,  3473,  3512,  3534,  3563,  3609,  3656,  3691,  3698,
    3734
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "INT", "FOR",
  "DO", "WHILE", "FLOAT", "VOID", "SWITCH", "DEFAULT", "ELSE", "CHAR",
  "BREAK", "DOUBLE", "RETURN", "CASE", "CONTINUE", "ADDOP", "MULOP",
  "INCOP", "DECOP", "ASSIGNOP", "NOT", "RELOP", "LOGICOP", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON",
  "STRING", "PRINTLN", "ID", "CONST_INT", "CONST_FLOAT", "CONST_CHAR",
  "WITHOUT_ELSE", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "$@1", "$@2", "$@3", "$@4",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@5",
  "$@6", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,   -75,   -75,   -75,    17,    12,   -75,   -75,   -75,   -75,
     -10,   -75,   -75,    30,    -8,     6,    -3,     8,   -75,     9,
      -5,    23,    22,    42,   -75,    50,    52,    12,   -75,   -75,
      49,    73,   -75,   -75,    50,    51,    58,    64,    66,    67,
      14,    14,    14,    14,   -75,   -75,    68,    32,   -75,   -75,
     -75,    59,   110,   -75,    50,   -75,    62,    65,   -75,    72,
      -7,    81,   -75,   -75,   -75,   -75,   -75,   -75,    14,    31,
      14,    70,    45,   -75,   -75,    74,    69,    14,    14,    77,
     -75,   -75,   -75,   -75,   -75,    14,   -75,    14,    14,    14,
      14,   -75,    88,    31,    92,   -75,   -75,    93,   -75,    94,
      90,    95,   -75,   -75,   -75,    81,    86,   -75,   147,    14,
     147,    91,   -75,    14,   -75,   112,   100,   -75,   -75,   -75,
     147,   147,   -75,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,     0,    22,    13,
       0,    19,     0,    26,     9,     0,    10,     0,    18,    29,
       0,    34,    14,     8,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    43,     0,    45,    63,    64,
      32,     0,    34,    30,     0,    33,    60,     0,    47,    49,
      51,    53,    55,    59,    15,    11,    16,    27,     0,     0,
       0,     0,    60,    57,    58,     0,     0,    68,     0,    28,
      20,    31,    35,    65,    66,     0,    44,     0,     0,     0,
       0,    12,     0,     0,     0,    42,    62,     0,    70,     0,
      67,     0,    36,    48,    50,    54,    52,    56,    34,     0,
      34,     0,    61,     0,    46,    38,     0,    40,    41,    69,
      34,    34,    39,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   125,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -12,    24,     4,   -75,   -75,   -46,   -75,   -75,   -56,
     -41,   -38,   -74,    44,    43,    47,   -34,   -75,   -75,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    34,    91,    25,    64,
      20,    32,    50,    51,    14,    52,    53,    54,   102,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    99,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      72,    72,    71,    98,    10,    75,    81,    73,    74,    10,
       1,   103,    88,    93,     2,     3,     1,    11,    89,    21,
       2,     3,    65,    26,     9,    17,    18,    13,    27,     9,
      92,    35,    94,    41,    19,    22,    72,   109,    42,   119,
     101,    43,    82,    24,    72,    23,    72,    72,    72,    72,
      41,    47,    48,    49,    29,    42,   107,    15,    43,    77,
      28,    16,   115,    78,   117,    45,    83,    84,    47,    48,
      49,   116,    72,    30,   122,   123,    37,     1,    38,    31,
      39,     2,     3,    83,    84,    85,    33,    36,    66,    40,
      67,    68,    41,    69,    70,    76,    79,    42,    87,    86,
      43,    90,    96,    44,    95,    88,    97,    45,    16,    46,
      47,    48,    49,    37,     1,    38,   108,    39,     2,     3,
     110,   111,   112,   113,   120,   118,    40,   114,   121,    41,
      12,   104,   106,     0,    42,   105,     0,    43,     0,     0,
      80,     0,     0,     0,    45,     0,    46,    47,    48,    49,
      37,     1,    38,     0,    39,     2,     3,     0,     0,     0,
       0,     0,     0,    40,     0,     0,    41,     0,     0,     0,
       0,    42,     0,     0,    43,     0,     0,     0,     0,     0,
       0,    45,     0,    46,    47,    48,    49
};

static const yytype_int8 yycheck[] =
{
      41,    42,    40,    77,     0,    43,    52,    41,    42,     5,
       4,    85,    19,    69,     8,     9,     4,     0,    25,    15,
       8,     9,    34,    28,     0,    33,    34,    37,    33,     5,
      68,    27,    70,    19,    28,    38,    77,    93,    24,   113,
      78,    27,    54,    34,    85,    37,    87,    88,    89,    90,
      19,    37,    38,    39,    32,    24,    90,    27,    27,    27,
      37,    31,   108,    31,   110,    34,    21,    22,    37,    38,
      39,   109,   113,    31,   120,   121,     3,     4,     5,    29,
       7,     8,     9,    21,    22,    23,    34,    38,    37,    16,
      32,    27,    19,    27,    27,    27,    37,    24,    26,    34,
      27,    20,    28,    30,    34,    19,    37,    34,    31,    36,
      37,    38,    39,     3,     4,     5,    28,     7,     8,     9,
      28,    28,    28,    33,    12,    34,    16,    32,    28,    19,
       5,    87,    89,    -1,    24,    88,    -1,    27,    -1,    -1,
      30,    -1,    -1,    -1,    34,    -1,    36,    37,    38,    39,
       3,     4,     5,    -1,     7,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     8,     9,    43,    44,    45,    46,    47,    54,
      55,     0,    45,    37,    56,    27,    31,    33,    34,    28,
      52,    55,    38,    37,    34,    50,    28,    33,    37,    32,
      31,    29,    53,    34,    48,    55,    38,     3,     5,     7,
      16,    19,    24,    27,    30,    34,    36,    37,    38,    39,
      54,    55,    57,    58,    59,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    51,    53,    37,    32,    27,    27,
      27,    63,    62,    68,    68,    63,    27,    27,    31,    37,
      30,    58,    53,    21,    22,    23,    34,    26,    19,    25,
      20,    49,    63,    61,    63,    34,    28,    37,    64,    70,
      71,    63,    60,    64,    65,    67,    66,    68,    28,    61,
      28,    28,    28,    33,    32,    58,    63,    58,    34,    64,
      12,    28,    58,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      48,    49,    47,    50,    51,    47,    52,    52,    52,    52,
      53,    53,    54,    55,    55,    55,    56,    56,    56,    56,
      57,    57,    58,    58,    59,    60,    58,    58,    58,    58,
      58,    58,    58,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    71,
      71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     0,     8,     0,     0,     7,     4,     3,     2,     1,
       3,     2,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     0,     0,     3,     7,     5,     7,
       5,     5,     3,     1,     2,     1,     4,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     2,     2,     1,
       1,     4,     3,     1,     1,     2,     2,     1,     0,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 176 "1805113.y"
        {
		//write your code in this block in all the similar blocks below
		f_log_out << "Line " << line_count <<  ": start : program  \n\n\n";
		
		
			//assembly code
			if(total_errors == 0){
				initial_code += ".MODEL small\n.STACK 100h\n.DATA\n\tprint_var dw ?\n\tdigit_count dw ?\n\tbackup_cx dw ?\n\tret_temp dw ?\n";

				//$$->setCode(initial_code);
				for(int i = 0; i < data_list.size(); i++){
					
					//if the data is normal variable
					if(data_list.at(i).second == "0")
						initial_code += "\t" + data_list.at(i).first + " dw ?\n";	
					else //if the data is an array
						initial_code += "\t" + data_list.at(i).first + " dw " + data_list.at(i).second + " dup(?)\n";
				}
				initial_code += ".CODE\n";
				
				//print function

   
				initial_code += "print PROC\n";
				initial_code +=	"\tpush ax\n";
				initial_code += "\tpush bx\n"; 
				initial_code += "\tpush cx\n";
				initial_code += "\tpush dx\n";
				initial_code += "\tmov ax, print_var\n";
				initial_code += "\tmov bx, print_var\n";
				initial_code += "\tcmp ax, 0\n";
				initial_code += "\tjl negative\n";

				initial_code += "\tjmp non_negative\n";
				
				 
				initial_code += "negative:\n";
				initial_code += "\tneg ax\n";
				initial_code += "\tpush ax\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, '-'\n";
				initial_code += "\tint 21h\n";

				initial_code += "\tpop ax\n";
				initial_code += "\tjmp integer_breaking_loop\n";
				
				
				initial_code += "non_negative:\n";
				initial_code += "\tcmp bx, 0\n";
				initial_code += "\tje print_zero\n";
				initial_code += "\tjmp integer_breaking_loop\n";
				initial_code += "print_zero:\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, 48\n";
				initial_code += "\tint 21h\n";
				
			
	                         initial_code += "\tmov ah, 2\n";
	                         initial_code += "\tmov dl, 10\n";
	                         initial_code += "\tint 21h\n";
	                         initial_code += "\tmov dl, 13\n";
	                         initial_code += "\tint 21h\n";
	                         initial_code += "\tpop dx\n";
	                         initial_code += "\tpop cx\n";
	                         initial_code += "\tpop bx\n";
	                         initial_code += "\tpop ax\n";
	                         
	                         
				initial_code += "\tret\n";
				
						
				initial_code += "integer_breaking_loop:\n";
				initial_code += "\tcmp ax, 0\n";
				initial_code += "\tje end_integer_breaking\n";
				initial_code += "\tmov dx, 0\n";
				initial_code += "\tmov bx, 10\n";
				initial_code += "\tdiv bx\n";
				initial_code += "\tpush dx\n";
				
				initial_code += "\tinc digit_count\n";
				
				initial_code += "\tjmp integer_breaking_loop\n";
				initial_code += "end_integer_breaking:\n";
				
				initial_code += "\tmov backup_cx, cx\n";
				initial_code += "\tmov cx, digit_count\n";
				
	
     
     				initial_code += "\tprint_integer_loop:\n";
				initial_code += "\tpop dx\n";
				
						
				initial_code += "\tadd dx, 48\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tint 21h\n";
				initial_code += "\tloop print_integer_loop\n";
				initial_code += "\tmov cx, backup_cx\n";
				initial_code += "\tmov ax, digit_count\n";
				initial_code += "\txor ax, ax\n";
				
				initial_code += "\tmov digit_count, ax\n";
				
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, 10\n";
				
				initial_code += "\tint 21h\n";
				initial_code += "\tmov dl, 13\n";
				initial_code += "\tint 21h\n";
				
				initial_code += "\tpop dx\n";
				initial_code += "\tpop cx\n";
				initial_code += "\tpop bx\n";
				initial_code += "\tpop ax\n";
				initial_code += "\tret\n";
				initial_code += "print endp\n";

				


				f_code << initial_code;
				f_code << (yyvsp[0].symbols)->at(0)->getCode();
				f_code << "END main\n";
			}	
	}
#line 1627 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 305 "1805113.y"
         {
                f_log_out << "Line " << line_count <<  ": program : program unit  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
			//type = "INT";
			
		//assembly code
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + (yyvsp[0].symbols)->at(0)->getCode());
                
                
                }
#line 1686 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 362 "1805113.y"
        {
                f_log_out << "Line " << line_count <<  ": program : unit  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;;
			//type = "INT";
                
                
                }
#line 1736 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 410 "1805113.y"
                {
                f_log_out << "Line " << line_count <<  ": unit : var_declaration \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyvsp[0].symbols)->at(i)->getName() == "int" || (yyvsp[0].symbols)->at(i)->getName() == "float" || (yyvsp[0].symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;;
			//type = "INT";
                
                
                }
#line 1770 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 443 "1805113.y"
     {
                f_log_out << "Line " << line_count <<  ": unit : func_declaration \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;
			//type = "INT";
                
                
                }
#line 1804 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 476 "1805113.y"
     {
                f_log_out << "Line " << line_count <<  ": unit : func_definition  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl ;
			//type = "INT";
                
                
                }
#line 1854 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 525 "1805113.y"
{ //declared function er name and parameters symbol gulo store kore rakha hocche

             
             function_definition_parameter_list = new vector<SymbolInfo*>();
             
             for(int i=0; i<(yyvsp[-2].symbols)->size();i++)
             {
             
             if((yyvsp[-2].symbols)->at(i)->getName() == "int" ||(yyvsp[-2].symbols)->at(i)->getName() == "float" )
             {
             
             if(i+1 < (yyvsp[-2].symbols)->size() && (yyvsp[-2].symbols)->at(i+1)->getName() != ",")
             {
             function_definition_parameter_list->push_back(new SymbolInfo((yyvsp[-2].symbols)->at(i+1)->getName(),"ID",(yyvsp[-2].symbols)->at(i)->getName(),"var",NULL));
             }
             
             else 
             {
             function_definition_parameter_list->push_back(new SymbolInfo((yyvsp[-2].symbols)->at(i)->getName(),(yyvsp[-2].symbols)->at(i)->getName(),(yyvsp[-2].symbols)->at(i)->getName(),"",NULL));
             
             }
             
             
             }
         
              
              }
           
              
              //inserting id for function in symbol table
              SymbolInfo *temp = st.Look_up((yyvsp[-4].symbol)->getName());
              
              if(temp == NULL) //the id name is not used before
              
              {  st.Insert((yyvsp[-4].symbol)->getName(),(yyvsp[-4].symbol)->getType(),(yyvsp[-5].symbol)->getName(),"func",function_definition_parameter_list,true);
              }
              
              else
              
              { //if the id name is already used before
              
              f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
              }
              
             
                
                
                   f_log_out << "Line " << line_count <<  ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-5].symbol));
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
                 	for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			 
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
			
                
                
             

}
#line 1950 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 619 "1805113.y"
                {
		//inserting the declared non parameterized function in the gloabal scope of symbol table
		
		   SymbolInfo *temp = st.Look_up((yyvsp[-3].symbol)->getName());
              
              if(temp == NULL) //the id name is not used before
              {
		st.Insert((yyvsp[-3].symbol)->getName(),(yyvsp[-3].symbol)->getType(),(yyvsp[-4].symbol)->getName(),"func",NULL,true);
                }
                
               else  //the id name is already used before
               {
               
                
              f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
               }  
               
               
               
                  f_log_out << "Line " << line_count <<  ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n";
                 
                (yyval.symbols) = new vector<SymbolInfo*>();
		
		(yyval.symbols)->push_back((yyvsp[-4].symbol));
		(yyval.symbols)->push_back((yyvsp[-3].symbol));
		(yyval.symbols)->push_back((yyvsp[-2].symbol));
		(yyval.symbols)->push_back((yyvsp[-1].symbol));
		(yyval.symbols)->push_back((yyvsp[0].symbol));
		
		f_log_out << (yyvsp[-4].symbol)->getName() <<" "<< (yyvsp[-3].symbol)->getName() << (yyvsp[-2].symbol)->getName() << (yyvsp[-1].symbol)->getName() << (yyvsp[0].symbol)->getName()<<endl << endl<< endl;
			
                 
                 
                 
                 }
#line 1992 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 658 "1805113.y"
                                                                 {


		function_definition_parameter_list = new vector<SymbolInfo*>();
             
             for(int i=0; i<(yyvsp[-1].symbols)->size();i++)
             {
             
             if((yyvsp[-1].symbols)->at(i)->getName() == "int" ||(yyvsp[-1].symbols)->at(i)->getName() == "float" )
             {
             
             if(i+1 < (yyvsp[-1].symbols)->size() && (yyvsp[-1].symbols)->at(i+1)->getName() != ",")
             {
             
             function_definition_parameter_list->push_back(new SymbolInfo((yyvsp[-1].symbols)->at(i+1)->getName(),"ID",(yyvsp[-1].symbols)->at(i)->getName(),"var",NULL));
             }
             
             else 
             {
             
             f_log_out<<"Error at line "<<line_count<<": Invalid parameter definition for function "<<(yyvsp[-3].symbol)->getName() << endl << endl;
              f_error_out<<"Error at line "<<line_count<<": Invalid parameter definition for function "<<(yyvsp[-3].symbol)->getName() << endl << endl;
              total_errors++;
             
             }
             
             
             }
         
              
              }
           
              

    
           SymbolInfo *temp=st.Look_up((yyvsp[-3].symbol)->getName());
           
     		if(temp == NULL)//if the function is not declared or defined before
             
            { 
                // f_log_out << $2->getName() << endl << endl ;
                 
            
              //inserting id for function in symbol table
                st.Insert((yyvsp[-3].symbol)->getName(),(yyvsp[-3].symbol)->getType(),(yyvsp[-4].symbol)->getName(),"func",function_definition_parameter_list);
                
                st.Enter_Scope(); //Entering a new scope for this function
                //function_scope_flag = true;
                
                
                //inserting the parameter variable into the scope of this function
                 for(int i=0; i<function_definition_parameter_list->size();i++)
                 {
                 st.Insert(function_definition_parameter_list->at(i)->getName(),"ID",function_definition_parameter_list->at(i)->getDataType(),"var",NULL);
                 
                 
        //assembly code
	string symbol = function_definition_parameter_list->at(i)->getName() + "_" + st.getCurrentScopeTableID();
	//setting assembly symbol in parameter as well as in the symbol table
	function_definition_parameter_list->at(i)->setAssemblySymbol(makeScopeID(symbol));
	
	(st.Look_up(function_definition_parameter_list->at(i)->getName()))->setAssemblySymbol(makeScopeID(symbol));
	
	data_list.push_back({makeScopeID(symbol),"0"});
	
						
                 
                 }
                 
                 

}

     else //if the function is declared before  or function name is used before or variable name used before
     {
     //f_log_out << "Hereeee1" << endl << endl << endl;
     if(temp->isDeclared() == true)  //if the function is declared but not define yet
     
     {
     
     
     
    // f_log_out << "Hereeeee2" << endl << endl << endl;
     
     temp->setDeclared(false);
     
     //parameter gula match kore kina dekhte hobe....na korle error..jodi match kore tahole
    // parameter gulo current scope a enter hobe
  
  //if declared function parameter number is not matched with the defined function parameter number
  
   //checking if the return type of declared function is matched with the defined one
    if(temp->getDataType() != (yyvsp[-4].symbol)->getName())
    {
   
      f_log_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       f_error_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       total_errors++;
    
    
    }
    
    
    else if(function_definition_parameter_list->size() != temp->getParameters()->size() )
    {
    f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    total_errors++;
    
    }
    
    //if declared function parameter types is not matched with the defined function parameter types
    else if(function_definition_parameter_list->size() == temp->getParameters()->size())
    {
    
    for(int i=0;i<temp->getParameters()->size();i++)
    {
    	if(function_definition_parameter_list->at(i)->getDataType() != temp->getParameters()->at(i)->getDataType() )
    	{
    	 f_log_out <<"Error at line "<<line_count<<": Types of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    	 f_error_out <<"Error at line "<<line_count<<": Types of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    	 total_errors++;
    	 break;
    	
    	}
    	
    	
    }
    
    
    
    }
    
    
   
    
    
    st.Enter_Scope(); //Entering a new scope for this function
   // f_log_out <<"Yes"<<endl;
     //function_scope_flag = true;
                
            
                //inserting the parameter variable into the scope of this function
           
                
                  for(int i=0; i<temp->getParameters()->size();i++)
                 {
                 st.Insert(temp->getParameters()->at(i)->getName(),"ID",temp->getParameters()->at(i)->getDataType(),"var",NULL);
     
     }
     
     
     
     
     }
     
     
     else // function name is used before or variable name used before
     {
    // f_log_out << "Hereeeee3" << endl << endl << endl;
     
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
			
			
			 st.Enter_Scope(); //Entering a new scope for this function
   // f_log_out <<"Yes"<<endl;
     //function_scope_flag = true;
                
              
                //inserting the parameter variable into the scope of this function
                
                  for(int i=0; i<function_definition_parameter_list->size();i++)
                 {
                 st.Insert(function_definition_parameter_list->at(i)->getName(),"ID",function_definition_parameter_list->at(i)->getDataType(),"var",NULL);
                 
                 }
                
                 
     
     }



  }
}
#line 2184 "y.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 847 "1805113.y"
                  {




}
#line 2195 "y.tab.c"
    break;

  case 12: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement $@2  */
#line 854 "1805113.y"
 {
                f_log_out << "Line " << line_count <<  ": func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-7].symbol));
			(yyval.symbols)->push_back((yyvsp[-6].symbol));
			(yyval.symbols)->push_back((yyvsp[-5].symbol));
			
			for(int i=0;i<(yyvsp[-4].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-4].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
  			
  			
  			//assembly code
			string segment_code = "";
			segment_code += (yyvsp[-6].symbol)->getName() + " PROC\n";
			if((yyvsp[-6].symbol)->getName() == "main")
				segment_code += "\tmov ax, @data\n\tmov ds, ax\n";
			else 
				segment_code += "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

			segment_code += (yyvsp[-1].symbols)->at(0)->getCode();
			if((yyvsp[-6].symbol)->getName() != "main")
				segment_code += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tret\n";

			segment_code += (yyvsp[-6].symbol)->getName() + " ENDP\n";
			
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
		
                
                
                }
#line 2274 "y.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 929 "1805113.y"
                                                  {
		
		
		 SymbolInfo *temp=st.Look_up((yyvsp[-2].symbol)->getName());
		
		if(temp == NULL) //if the function is not declared before
		
		{
		 
              //inserting id for function in symbol table
                st.Insert((yyvsp[-2].symbol)->getName(),(yyvsp[-2].symbol)->getType(),(yyvsp[-3].symbol)->getName(),"func",NULL);
                
                st.Enter_Scope(); //Entering a new scope for this function
                //function_scope_flag = true;
		}
		
		else  //if the function is declared before  or function name is used before or variable name used before
		
		{
		
		 if(temp->isDeclared() == true)  //if the function is declared but not define yet
     
    		 {
     
     		temp->setDeclared(false);
     		
     			//checking if the return type of declared function is matched with the defined one
          if(temp->getDataType() != (yyvsp[-3].symbol)->getName())
    {
      f_log_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       f_error_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       total_errors++;
    
    
    }
		
     
		
		st.Enter_Scope(); //Entering a new scope for this function
		//function_scope_flag = true;
		
		}
		
	
		else
		
		{
		  f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
		
		}
		
		
      }
		
		
		
}
#line 2338 "y.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 993 "1805113.y"
                {
		
		
		}
#line 2347 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement $@4  */
#line 999 "1805113.y"
        {
		
		
		 f_log_out << "Line " << line_count <<  ": func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-6].symbol));
			(yyval.symbols)->push_back((yyvsp[-5].symbol));
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
  			
  			//assembly code
			string segment_code = "";
			segment_code += (yyvsp[-5].symbol)->getName() + " PROC\n";
			if((yyvsp[-5].symbol)->getName() == "main")
				segment_code += "\tmov ax, @data\n\tmov ds, ax\n";
			else 
				segment_code += "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

			segment_code += (yyvsp[-1].symbols)->at(0)->getCode();
			if((yyvsp[-5].symbol)->getName() != "main")
				segment_code += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tret\n";
			else
			{
			segment_code+="\tmov ah,4ch\n\tint 21h\n"; 
			
			}

			segment_code += (yyvsp[-5].symbol)->getName() + " ENDP\n";
			
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
		
		
		
		
		}
#line 2426 "y.tab.c"
    break;

  case 16: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 1077 "1805113.y"
                {
                //int a,int b,int c......
                
                //checking if any parameter is declared multiple times or not
                
                for(int i=0;i<(yyvsp[-3].symbols)->size();i++)
                {
                
                if((yyvsp[-3].symbols)->at(i)->getName() == (yyvsp[0].symbol)->getName())
                {
                f_log_out <<"Error at line "<<line_count<<": Multiple declaration of "<<(yyvsp[0].symbol)->getName()<<" in parameter" << endl << endl;
                f_error_out <<"Error at line "<<line_count<<": Multiple declaration of "<<(yyvsp[0].symbol)->getName()<<" in parameter" << endl << endl;
                 total_errors++;
                 break;
                
                }
                
                }
                
                
                
                f_log_out << "Line " << line_count <<  ": parameter_list : parameter_list COMMA type_specifier ID\n\n";
                 
                (yyval.symbols) = new vector<SymbolInfo*>();
                
  		for(int i=0;i<(yyvsp[-3].symbols)->size();i++)
	        {
		(yyval.symbols)->push_back((yyvsp[-3].symbols)->at(i));
		}
                           		   
		(yyval.symbols)->push_back((yyvsp[-2].symbol));
		(yyval.symbols)->push_back((yyvsp[-1].symbol));
		(yyval.symbols)->push_back((yyvsp[0].symbol));
		
		
		
		for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
		
 		
 		}
#line 2484 "y.tab.c"
    break;

  case 17: /* parameter_list: parameter_list COMMA type_specifier  */
#line 1133 "1805113.y"
                {
                //int a,int b,int......
                
           
                     f_log_out << "Line " << line_count <<  ": parameter_list : parameter_list COMMA type_specifier\n\n";
                 
                (yyval.symbols) = new vector<SymbolInfo*>();
                
  		for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
	        {
		(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
		}
                           		   
		(yyval.symbols)->push_back((yyvsp[-1].symbol));
		(yyval.symbols)->push_back((yyvsp[0].symbol));
		
		
		
		
		for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
		
 		
 		}
#line 2525 "y.tab.c"
    break;

  case 18: /* parameter_list: type_specifier ID  */
#line 1174 "1805113.y"
                {
 		
 		
 		 f_log_out << "Line " << line_count <<  ": parameter_list : type_specifier ID\n\n";
                 
                (yyval.symbols) = new vector<SymbolInfo*>();
		
		(yyval.symbols)->push_back((yyvsp[-1].symbol));
		(yyval.symbols)->push_back((yyvsp[0].symbol));
		
		//f_log_out << "Here1" << endl;
		f_log_out << (yyvsp[-1].symbol)->getName() <<" "<< (yyvsp[0].symbol)->getName() << endl << endl;
		
 		//f_log_out << "Here" << endl;
 		}
#line 2545 "y.tab.c"
    break;

  case 19: /* parameter_list: type_specifier  */
#line 1193 "1805113.y"
                {
 		
 		
 		 f_log_out << "Line " << line_count <<  ": parameter_list : type_specifier\n\n";
                 
                (yyval.symbols) = new vector<SymbolInfo*>();
		
		(yyval.symbols)->push_back((yyvsp[0].symbol));
		
		//f_log_out << "Here1" << endl;
		f_log_out << (yyvsp[0].symbol)->getName()<< endl << endl;
		
 		//f_log_out << "Here" << endl;
 		}
#line 2564 "y.tab.c"
    break;

  case 20: /* compound_statement: LCURL statements RCURL  */
#line 1214 "1805113.y"
                   {
                f_log_out << "Line " << line_count <<  ": compound_statement : LCURL statements RCURL\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
               
			
			
			 
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			 if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			  
			  
			}
			
			 
			 
			
  			f_log_out << endl << endl<<endl<<endl;
  			
  			
  		//exiting from current scope	
    	        st.Print_All_Scope_Table(f_log_out);
    	        st.Exit_Scope();
			//type = "INT";
			
		//assembly code
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + (yyvsp[-1].symbols)->at(0)->getCode());
                
                
                }
#line 2633 "y.tab.c"
    break;

  case 21: /* compound_statement: LCURL RCURL  */
#line 1280 "1805113.y"
                    {
                f_log_out << "Line " << line_count <<  ": compound_statement : LCURL RCURL\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
               
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
			 
			f_log_out << endl << endl<<endl;
  			
  			
  		//exiting from current scope	
    	        st.Print_All_Scope_Table(f_log_out);
    	        st.Exit_Scope();
			//type = "INT";
                
                
                }
#line 2666 "y.tab.c"
    break;

  case 22: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 1312 "1805113.y"
                 {
                f_log_out << "Line " << line_count <<  ": var_declaration : type_specifier declaration_list SEMICOLON\n\n";
                
                if((yyvsp[-2].symbol)->getName()=="void")
                {
               
                f_log_out <<"Error at line "<<line_count<<": Variable type cannot be void" <<endl << endl;
                  f_error_out <<"Error at line "<<line_count<<": Variable type cannot be void" <<endl << endl;
                  total_errors++;
                
                
                }
                
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
                
		
			f_log_out << (yyvsp[-2].symbol)->getName() << " ";
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			  f_log_out << (yyvsp[-1].symbols)->at(i)->getName() ;
			}
			
			f_log_out << (yyvsp[0].symbol)->getName() << " ";
			
  			f_log_out << endl << endl;
			
                
                
                }
#line 2713 "y.tab.c"
    break;

  case 23: /* type_specifier: INT  */
#line 1358 "1805113.y"
                { //cout << "returned INT" << endl;
                
                f_log_out << "Line " << line_count <<  ": type_specifier : INT\n\n";
			f_log_out << (yyvsp[0].symbol)->getName() << endl << endl;
			(yyval.symbol) = (yyvsp[0].symbol);
			type = "int";
                
                
                }
#line 2727 "y.tab.c"
    break;

  case 24: /* type_specifier: FLOAT  */
#line 1369 "1805113.y"
                {
                f_log_out << "Line " << line_count <<  ": type_specifier : FLOAT\n\n";
			f_log_out << (yyvsp[0].symbol)->getName()  << endl << endl;
			(yyval.symbol) = (yyvsp[0].symbol);
			type = "float";
                
                
                }
#line 2740 "y.tab.c"
    break;

  case 25: /* type_specifier: VOID  */
#line 1380 "1805113.y"
                {
 		
                f_log_out << "Line " << line_count <<  ": type_specifier : VOID\n\n";
			f_log_out << (yyvsp[0].symbol)->getName()  << endl << endl;
			(yyval.symbol) = (yyvsp[0].symbol);
		    type = "void";
                
                
                }
#line 2754 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID  */
#line 1395 "1805113.y"
                   {
                   
                   //inserting ID to symbol table
                 //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up((yyvsp[0].symbol)->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[0].symbol)->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[0].symbol)->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert((yyvsp[0].symbol)->getName(),(yyvsp[0].symbol)->getType(),type,"var",NULL);
 		 
 		 }
 		 
                   //cout << "declaration_list COMMA ID matched" << endl;
                     f_log_out << "Line " << line_count <<  ": declaration_list : declaration_list COMMA ID\n\n";
			
			(yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
			//type = "INT";
			
			
			//assembly code
			string symbol = (yyvsp[0].symbol)->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up((yyvsp[0].symbol)->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),"0"});
                
                
                  }
#line 2814 "y.tab.c"
    break;

  case 27: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 1455 "1805113.y"
                  {
 		  
 		  //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up((yyvsp[-3].symbol)->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[-3].symbol)->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[-3].symbol)->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert((yyvsp[-3].symbol)->getName(),(yyvsp[-3].symbol)->getType(),type,"array",NULL);
 		 
 		 }
 		  
 		   f_log_out << "Line " << line_count <<  ": declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n";
 		   
 		   
 		  //inserting ID to symbol table
 		  
 		  //this condition checks if the id is already inserted into symbol table or not
 		 
			
			(yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-5].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-5].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
 		 
 		 
			//assembly code
			string symbol = (yyvsp[-3].symbol)->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up((yyvsp[-3].symbol)->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),(yyvsp[-1].symbol)->getName()});
 		 
 		 
 		  
 		  
 		  
 		  
 		  
 		  
 		  }
#line 2886 "y.tab.c"
    break;

  case 28: /* declaration_list: ID  */
#line 1523 "1805113.y"
                  {
 		  
 		 // cout << "declaration_list: ID matched" << endl;
 		 
 		  //inserting ID to symbol table
 		  
 		 // st.Print_All_Scope_Table(f_log_out);

             //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up((yyvsp[0].symbol)->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[0].symbol)->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[0].symbol)->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert((yyvsp[0].symbol)->getName(),(yyvsp[0].symbol)->getType(),type,"var",NULL);
 		 
 		 }
 		  
 		 
 		  
                     f_log_out << "Line " << line_count <<  ": declaration_list : ID\n\n";
		     f_log_out << (yyvsp[0].symbol)->getName()  << "\n\n";
		     
		     (yyval.symbols) = new vector<SymbolInfo*>();
		     (yyval.symbols)->push_back((yyvsp[0].symbol));
			//type = "INT";
			
			
			//assembly code
			string symbol = (yyvsp[0].symbol)->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up((yyvsp[0].symbol)->getName())->setAssemblySymbol(makeScopeID(symbol));
			//for "var" type id
			data_list.push_back({makeScopeID(symbol),"0"});
                
                
                  }
#line 2938 "y.tab.c"
    break;

  case 29: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 1574 "1805113.y"
                  {
 		  //inserting an array id to symbol table
 		  
 		  
 		 //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up((yyvsp[-3].symbol)->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[-3].symbol)->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << (yyvsp[-3].symbol)->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert((yyvsp[-3].symbol)->getName(),(yyvsp[-3].symbol)->getType(),type,"array",NULL);
 		 
 		 }
 		 
 		 f_log_out << "Line " << line_count <<  ": declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n";
 		 
			
			(yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
			//type = "INT";
			
			//assembly code
			string symbol = (yyvsp[-3].symbol)->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up((yyvsp[-3].symbol)->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),(yyvsp[-1].symbol)->getName()});
                
 		   
 		   
 		  }
#line 2996 "y.tab.c"
    break;

  case 30: /* statements: statement  */
#line 1631 "1805113.y"
            {
                f_log_out << "Line " << line_count <<  ": statements : statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			 if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 3046 "y.tab.c"
    break;

  case 31: /* statements: statements statement  */
#line 1679 "1805113.y"
           {
                f_log_out << "Line " << line_count <<  ": statements : statements statement  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl ;
  			
  			
  		//assembly code
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + (yyvsp[0].symbols)->at(0)->getCode());
		
                
                
                }
#line 3105 "y.tab.c"
    break;

  case 32: /* statement: var_declaration  */
#line 1738 "1805113.y"
{
  f_log_out << "Line " << line_count <<  ": statement : var_declaration\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl;

}
#line 3153 "y.tab.c"
    break;

  case 33: /* statement: expression_statement  */
#line 1782 "1805113.y"
         {
                f_log_out << "Line " << line_count <<  ": statement : expression_statement  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;
			
                
                
                }
#line 3187 "y.tab.c"
    break;

  case 34: /* $@5: %empty  */
#line 1812 "1805113.y"
             {st.Enter_Scope();}
#line 3193 "y.tab.c"
    break;

  case 35: /* $@6: %empty  */
#line 1812 "1805113.y"
                                                    { /* st.Exit_Scope();*/}
#line 3199 "y.tab.c"
    break;

  case 36: /* statement: $@5 compound_statement $@6  */
#line 1813 "1805113.y"
          {
	  
	   f_log_out << "Line " << line_count <<  ": statement : compound_statement  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl;
			
	  
	  }
#line 3249 "y.tab.c"
    break;

  case 37: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 1861 "1805113.y"
          {
                f_log_out << "Line " << line_count <<  ": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-6].symbol));
			(yyval.symbols)->push_back((yyvsp[-5].symbol));
			
			for(int i=0;i<(yyvsp[-4].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-4].symbols)->at(i));
			}
			
		
			for(int i=0;i<(yyvsp[-3].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-3].symbols)->at(i));
			}
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  			
  			
  		//assembly code
		string label1 = newLabel();
		string label2 = newLabel();
		
		string segment_code = "";
		segment_code += (yyvsp[-4].symbols)->at(0)->getCode();
		segment_code += label1 + ":\n";
		segment_code += (yyvsp[-3].symbols)->at(0)->getCode();
		segment_code += "\tmov ax, " + (yyvsp[-3].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label2 + "\n";
		segment_code += (yyvsp[0].symbols)->at(0)->getCode();
		segment_code += (yyvsp[-2].symbols)->at(0)->getCode();
		segment_code += "\tjmp " + label1 + "\n";
		segment_code += label2 + ":\n";

		(yyval.symbols)->at(0)->setCode(segment_code);
  			
  		

                
                
                }
#line 3344 "y.tab.c"
    break;

  case 38: /* statement: IF LPAREN expression RPAREN statement  */
#line 1952 "1805113.y"
          {
                f_log_out << "Line " << line_count <<  ": statement : IF LPAREN expression RPAREN statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  		//assembly code
		string label = newLabel();
		string segment_code = "";
		segment_code += "\tmov ax, " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label + "\n";
		segment_code += (yyvsp[0].symbols)->at(0)->getCode();
		segment_code += label + ":\n";

		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() +(yyvsp[-2].symbols)->at(0)->getCode() + segment_code);

                
                
                }
#line 3417 "y.tab.c"
    break;

  case 39: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 2023 "1805113.y"
          {
                f_log_out << "Line " << line_count <<  ": statement : IF LPAREN expression RPAREN statement ELSE statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-6].symbol));
			(yyval.symbols)->push_back((yyvsp[-5].symbol));
			
			for(int i=0;i<(yyvsp[-4].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-4].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  		//assembly code
		string label1 = newLabel();
		string label2 = newLabel();
		string segment_code = "";

		segment_code += "\tmov ax, " + (yyvsp[-4].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label1 + "\n";
		segment_code += (yyvsp[-2].symbols)->at(0)->getCode();
		segment_code += "\tjmp " + label2 + "\n";
		segment_code += label1 + ":\n";
		segment_code += (yyvsp[0].symbols)->at(0)->getCode();
		segment_code += label2 + ":\n";

		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode()+(yyvsp[-4].symbols)->at(0)->getCode()+ segment_code);
  			
  			
	  }
#line 3501 "y.tab.c"
    break;

  case 40: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 2103 "1805113.y"
          {

                f_log_out << "Line " << line_count <<  ": statement : WHILE LPAREN expression RPAREN statement\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
           
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			   if((yyval.symbols)->at(i)->getName() == "int" || (yyval.symbols)->at(i)->getName() == "float" || (yyval.symbols)->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if((yyval.symbols)->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if((yyval.symbols)->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if((yyval.symbols)->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  			
  			
  			//assembly code
  		
  		//1st a "expression" evaluate hobe
  		//then "expression" 1 naki 0 sheta check hobe
  		//"expression" 1 hole loop er moddhe "statement" execute hote thakbe
  		//"expressio" 0 hole loop theke ber hoye jabe
  		
		string label1 = newLabel();
		string label2 = newLabel();
		
		string segment_code = "";
		segment_code += label1 + ":\n";
		segment_code += (yyvsp[-2].symbols)->at(0)->getCode();
		segment_code += "\tmov ax, " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label2 + "\n";
		segment_code += (yyvsp[0].symbols)->at(0)->getCode();
		segment_code += "\tjmp " + label1 + "\n";
		segment_code += label2 + ":\n";

		(yyval.symbols)->at(0)->setCode(segment_code);

                
                
                }
#line 3586 "y.tab.c"
    break;

  case 41: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 2186 "1805113.y"
          {

                f_log_out << "Line " << line_count <<  ": statment : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n";
                
                if(st.Look_up((yyvsp[-2].symbol)->getName()) == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[-2].symbol)->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[-2].symbol)->getName() << "\n\n";
			total_errors++;
		   }
		   
                
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-4].symbol));
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl<<endl;
  			
  			
  		//assembly code
		string segment_code = "";
		segment_code += "\tmov ax, " + (st.Look_up((yyvsp[-2].symbol)->getName()))->getAssemblySymbol() + "\n";
		segment_code += "\tmov print_var, ax\n";
		segment_code +=	"\tcall print\n";

		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
    
                }
#line 3632 "y.tab.c"
    break;

  case 42: /* statement: RETURN expression SEMICOLON  */
#line 2232 "1805113.y"
          {
                f_log_out << "Line " << line_count <<  ": statement : RETURN expression SEMICOLON\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			
			f_log_out << (yyval.symbols)->at(i)->getName() ;
			
			if((yyval.symbols)->at(i)->getName()=="return")
			{
			f_log_out << " ";
			}
			  
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			
		//assembly code
		string segment_code = "";
		segment_code += (yyvsp[-1].symbols)->at(0)->getCode();
		segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tmov ret_temp, ax\n";

		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
                
                
                }
#line 3680 "y.tab.c"
    break;

  case 43: /* expression_statement: SEMICOLON  */
#line 2280 "1805113.y"
                         {
                f_log_out << "Line " << line_count <<  ": expression_statement : SEMICOLON\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
           		for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
			
			}
#line 3704 "y.tab.c"
    break;

  case 44: /* expression_statement: expression SEMICOLON  */
#line 2305 "1805113.y"
                         {
                f_log_out << "Line " << line_count <<  ": expression_statement : expression SEMICOLON\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			//assembly code (Ai line na likhleo hoto)
			(yyval.symbols)->at(0)->setCode((yyvsp[-1].symbols)->at(0)->getCode());
                
			
			}
#line 3738 "y.tab.c"
    break;

  case 45: /* variable: ID  */
#line 2337 "1805113.y"
          {
           f_log_out << "Line " << line_count <<  ": variable : ID"<<endl<<endl;
 		 
 		 SymbolInfo *temp=st.Look_up((yyvsp[0].symbol)->getName());
                    
                      //f_log_out << "Hereeeeeeeeeeeeeeeeeeeeee" << endl;
                     if(temp == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[0].symbol)->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[0].symbol)->getName() << "\n\n";
			total_errors++;
		   }
		   
		   else if(temp ->getIdType() == "array") //if array variable is used like normal variable
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Type mismatch, " << (yyvsp[0].symbol)->getName() << " is an array\n\n";
			f_error_out << "Error at line " << line_count << ": Type mismatch, " << (yyvsp[0].symbol)->getName() << " is an array\n\n";
			total_errors++;
		   }
		   
		   if(temp != NULL)
		   {
		   
		   	(yyvsp[0].symbol)->setDataType(temp->getDataType());
		   	(yyvsp[0].symbol)->setIdType(temp->getIdType());
		   	//f_log_out << $1->getDataType() << endl;
		   	
		   }
		   
		   
		  
		     
		     
		     (yyval.symbols) = new vector<SymbolInfo*>();
		     (yyval.symbols)->push_back((yyvsp[0].symbol));
			//type = "INT";
			
		   for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
  			
  			
  		//assembly code
		(yyval.symbols)->at(0)->setAssemblySymbol((st.Look_up((yyvsp[0].symbol)->getName()))->getAssemblySymbol());
		
		(yyval.symbols)->at(0)->setCode("");
                
                  }
#line 3796 "y.tab.c"
    break;

  case 46: /* variable: ID LTHIRD expression RTHIRD  */
#line 2393 "1805113.y"
            {
 		
                     f_log_out << "Line " << line_count <<  ": variable : ID LTHIRD expression RTHIRD\n\n";
                     
                     SymbolInfo *temp=st.Look_up((yyvsp[-3].symbol)->getName());
                    
                      //f_log_out << "Hereeeeeeeeeeeeeeeeeeeeee" << endl;
                     if(temp == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[-3].symbol)->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << (yyvsp[-3].symbol)->getName() << "\n\n";
			total_errors++;
		   }
		   
		   else if(temp ->getIdType() == "var") //if normal variable is used like array variable
                     
                     {  
			f_log_out << "Error at line " << line_count << ": " << (yyvsp[-3].symbol)->getName() << " not an array\n\n";
			f_error_out << "Error at line " << line_count << ": " << (yyvsp[-3].symbol)->getName() << " not an array\n\n";
			total_errors++;
		   }
		   
		   
		   if(temp != NULL)
		   {
		   
		   	(yyvsp[-3].symbol)->setDataType(temp->getDataType());
		   	(yyvsp[-3].symbol)->setIdType(temp->getIdType());
		   	
		   }
                     
                     if((yyvsp[-1].symbols)->at(0)->getType() == "CONST_FLOAT") //if array index is not integer
                     {
                     f_log_out << "Error at line " << line_count << ": Expression inside third brackets not an integer\n\n";
			f_error_out << "Error at line " << line_count << ": Expression inside third brackets not an integer\n\n";
			total_errors++;
                     
                     }

		     
		     
		     (yyval.symbols) = new vector<SymbolInfo*>();
		     (yyval.symbols)->push_back((yyvsp[-3].symbol));
		     (yyval.symbols)->push_back((yyvsp[-2].symbol));
			//type = "INT";
			
	           for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
	           {
	           
	           (yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
	           
	           }	
	           
	            (yyval.symbols)->push_back((yyvsp[0].symbol));
			
		   for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
  			
  			
  		//assembly code
		(yyval.symbols)->at(0)->setAssemblySymbol((st.Look_up((yyvsp[-3].symbol)->getName()))->getAssemblySymbol());

		string segment_code = "";
		segment_code += "\tmov di, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tadd di, di\n";
		(yyval.symbols)->at(0)->setCode(segment_code);
                
    }
#line 3874 "y.tab.c"
    break;

  case 47: /* expression: logic_expression  */
#line 2472 "1805113.y"
                 {
                f_log_out << "Line " << line_count <<  ": expression : logic_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 3903 "y.tab.c"
    break;

  case 48: /* expression: variable ASSIGNOP logic_expression  */
#line 2499 "1805113.y"
           {
	    f_log_out << "Line " << line_count <<  ": expression : variable ASSIGNOP logic_expression \n\n";
	    
	    //Handling the type mismatch error
	    SymbolInfo *temp = st.Look_up((yyvsp[-2].symbols)->at(0)->getName());
	    
	   
	   //ASSIGNOP er right a jodi kono "void" function thake
	   
	   for(int i=0;i<(yyvsp[0].symbols)->size();i++)
	   {
	   if((yyvsp[0].symbols)->at(i)->getIdType() == "func" && (yyvsp[0].symbols)->at(i)->getDataType() == "void" )
	   {
	    f_log_out <<"Error at line "<<line_count <<": Void function used in expression" << endl<< endl;
	     f_error_out <<"Error at line "<<line_count <<": Void function used in expression" << endl<< endl;
	     total_errors++;
	     break;
	   
	   }
	   
	   }
	   
	   //ASSIGNOP er Left variable INT but right variable er kono akti float tahole type mismatch
	   
	   if((yyvsp[-2].symbols)->at(0)->getDataType() == "int" )
	   {
	    for(int i=0;i<(yyvsp[0].symbols)->size();i++)
	    {
	      if((yyvsp[0].symbols)->at(i)->getIdType()=="var" && (yyvsp[0].symbols)->at(i)->getDataType()=="float" )
	      {
	      {
	    //cout << temp->getName()<<"  "<< $3->at($3->size()-1)->getName()<< endl;
	    
	     f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    }
	    break;
	      
	      }
	      
	      else if((yyvsp[0].symbols)->at(i)->getIdType()=="cons" &&  (yyvsp[0].symbols)->at(i)->getDataType()=="float" )
	      {
	      
	      f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	       else if((yyvsp[0].symbols)->at(i)->getIdType()=="array" && (yyvsp[0].symbols)->at(i)->getDataType()=="float" )
	      {
	      
	      f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	      else if((yyvsp[0].symbols)->at(i)->getIdType()=="func" && (yyvsp[0].symbols)->at(i)->getDataType()=="float")
	      {
	       f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	      else if((yyvsp[0].symbols)->at(i)->getIdType()=="array" && (yyvsp[0].symbols)->at(i)->getDataType()=="float")
	      {
	      
	       f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	   
	    break;
	      
	      }
	      
	      else if((yyvsp[0].symbols)->at(i)->getIdType()=="array" )
	      {
	       if(i+3 < (yyvsp[0].symbols)->size())
	      {
	      i=i+3;
	      }
	      
	      
	      }
	      
	      else if((yyvsp[0].symbols)->at(i)->getIdType() == "func") //if return type of function "INT"
	      {
	      
	      while(i<(yyvsp[0].symbols)->size() && (yyvsp[0].symbols)->at(i)->getName()!=")")
	      {
	      
	      i++; //ignoring all the function arguments;
	      }
	      
	      }
	      
	    
	    
	    }
	    
	    
	   }
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
  			
  			//assembly code
			string ID_type = (st.Look_up((yyvsp[-2].symbols)->at(0)->getName()))->getIdType();
			string segment_code = "";
			string tempp;
			
			if((yyvsp[0].symbols)->size() == 4){
				tempp = newTemp();
				segment_code += (yyvsp[0].symbols)->at(0)->getCode();
				segment_code += "\tmov ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "[di]\n";
				segment_code += "\tmov " + tempp + ", ax\n";
				segment_code += (yyvsp[-2].symbols)->at(0)->getCode();
				if(ID_type != "array")
					segment_code += "\tmov " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + ", ax\n";
				else{
					segment_code += "\tmov ax, " + tempp + "\n"; 
					segment_code += "\tmov " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "[di], ax\n";
				}
			}

			else{
				segment_code += (yyvsp[0].symbols)->at(0)->getCode();
				segment_code += (yyvsp[-2].symbols)->at(0)->getCode();
				segment_code += "\tmov ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";
				
				if(ID_type != "array")
					segment_code += "\tmov " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + ", ax\n";
				else
					segment_code += "\tmov " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "[di], ax\n";
				
			}
			(yyval.symbols)->at(0)->setCode(segment_code);
	   
	   
	   
	   }
#line 4077 "y.tab.c"
    break;

  case 49: /* logic_expression: rel_expression  */
#line 2671 "1805113.y"
                   {
                f_log_out << "Line " << line_count <<  ": logic_expression : rel_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4106 "y.tab.c"
    break;

  case 50: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 2698 "1805113.y"
                 {
		 
                f_log_out << "Line " << line_count <<  ": rel_expression : rel_expression LOGICOP rel_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                	//assembly code
			string label1 = newLabel();
			string label2 = newLabel();
			string temp = newTemp();

			string segment_code = "";
			if((yyvsp[-1].symbol)->getName() == "&&"){
				segment_code += "\tcmp " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tje " + label1 + "\n";
				segment_code += "\tcmp " +  (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tje " + label1 + "\n";
				segment_code += "\tmov " + temp + ", 1\n";
				segment_code += "\tjmp " + label2 + "\n";
				segment_code += label1 + ":\n";
				segment_code += "\tmov " + temp + ", 0\n";
				segment_code += label2 + ":\n";
			}
			else if((yyvsp[-1].symbol)->getName() == "||"){
				segment_code += "\tcmp " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tjne " + label1 + "\n";
				segment_code += "\tcmp " +  (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tjne " + label1 + "\n";
				segment_code += "\tmov " + temp + ", 0\n";
				segment_code += "\tjmp " + label2 + "\n";
				segment_code += label1 + ":\n";
				segment_code += "\tmov " + temp + ", 1\n";
				segment_code += label2 + ":\n";
			}
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
			(yyval.symbols)->at(0)->setAssemblySymbol(temp);
                
                
		
		
		}
#line 4175 "y.tab.c"
    break;

  case 51: /* rel_expression: simple_expression  */
#line 2766 "1805113.y"
             {
                f_log_out << "Line " << line_count <<  ": rel_expression : simple_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4204 "y.tab.c"
    break;

  case 52: /* rel_expression: simple_expression RELOP simple_expression  */
#line 2792 "1805113.y"
                {
		 
                f_log_out << "Line " << line_count <<  ": rel_expression : simple_expression RELOP simple_expression  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			string label1 = newLabel();
			string label2 = newLabel();
			string temp = newTemp();
			string segment_code = "";

			segment_code += (yyvsp[0].symbols)->at(0)->getCode();
			segment_code += "\tmov ax, " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tcmp ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";

			if((yyvsp[-1].symbol)->getName() == ">")
				segment_code += "\tjg " + label1 + "\n";
			else if((yyvsp[-1].symbol)->getName() == ">=")
				segment_code += "\tjge " + label1 + "\n";
			else if((yyvsp[-1].symbol)->getName() == "<")
				segment_code += "\tjl " + label1 + "\n";
			else if((yyvsp[-1].symbol)->getName() == "<=")
				segment_code += "\tjle " + label1 + "\n";
			else if((yyvsp[-1].symbol)->getName() == "==")
				segment_code += "\tje " + label1 + "\n";
			else if((yyvsp[-1].symbol)->getName() == "!=")
				segment_code += "\tjne " + label1 + "\n";

			segment_code += "\tmov " + temp + ", 0\n";
			segment_code += "\tjmp " + label2 + "\n";
			segment_code += label1 + ":\n";
			segment_code += "\tmov " + temp + ", 1\n";
			segment_code += label2 + ":\n";

			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
			(yyval.symbols)->at(0)->setAssemblySymbol(temp);
                
                
                
		
		
		}
#line 4274 "y.tab.c"
    break;

  case 53: /* simple_expression: term  */
#line 2861 "1805113.y"
                  {
                f_log_out << "Line " << line_count <<  ": simple_expression : term\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4303 "y.tab.c"
    break;

  case 54: /* simple_expression: simple_expression ADDOP term  */
#line 2887 "1805113.y"
                   {
                f_log_out << "Line " << line_count <<  ": simple_expression : simple_expression ADDOP term\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			
			//assembly code

			string temp = newTemp();

			string segment_code = "";
			segment_code += (yyvsp[0].symbols)->at(0)->getCode();
			segment_code += "\tmov ax, " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "\n";
			if((yyvsp[-1].symbol)->getName() == "+")
				segment_code += "\tadd ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";
			else
				segment_code += "\tsub ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
			(yyval.symbols)->at(0)->setAssemblySymbol(temp);
                
                
                }
#line 4356 "y.tab.c"
    break;

  case 55: /* term: unary_expression  */
#line 2942 "1805113.y"
{
                f_log_out << "Line " << line_count <<  ": term : unary_expression  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4385 "y.tab.c"
    break;

  case 56: /* term: term MULOP unary_expression  */
#line 2969 "1805113.y"
     {
                f_log_out << "Line " << line_count <<  ": term : term MULOP unary_expression  \n\n";
                if((yyvsp[-1].symbol)->getName() == "%") //if MULOP = "%"
               {
                
                if((yyvsp[-2].symbols)->at(0)->getDataType() == "float" || (yyvsp[0].symbols)->at(0)->getDataType() == "float")
                {
                f_log_out <<"Error at line "<<line_count<<": Non-Integer operand on modulus operator" << endl<<endl;
                f_error_out <<"Error at line "<<line_count<<": Non-Integer operand on modulus operator" << endl<<endl;
                total_errors++;
                
                }
                
               }
               
               
               //if right or left operand of MULOP is a void return type function
               
               if((yyvsp[0].symbols)->at(0)->getIdType()=="func" && (yyvsp[0].symbols)->at(0)->getDataType()=="void")
               {
                 f_log_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  total_errors++;
               
               
               }
               
               else if((yyvsp[-2].symbols)->at(0)->getIdType()=="func" && (yyvsp[-2].symbols)->at(0)->getDataType()=="void")
               {
               f_log_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  total_errors++;
               
               
               }
               
               
               //Modulas by zero or divided by zero
                if((yyvsp[-1].symbol)->getName() == "%" && (yyvsp[0].symbols)->at(0)->getName()=="0") 
                {
                
                f_log_out <<"Error at line "<<line_count<<": Modulus by Zero" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Modulus by Zero" << endl<<endl;
                  total_errors++;
               
                }
                
                else if((yyvsp[-1].symbol)->getName() == "/" && (yyvsp[0].symbols)->at(0)->getName()=="0") 
                {
                
                 f_log_out <<"Error at line "<<line_count<<": Divied by Zero" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Divided by Zero" << endl<<endl;
                  total_errors++;
                }


               
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
                
                        for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			 
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			  
			}
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			
			  
			}
			
			
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			//assembly code

			string temp = newTemp();

			string segment_code = "";
			segment_code += (yyvsp[0].symbols)->at(0)->getCode(); //unary expression calculation er code lekha holo
			segment_code += "\tmov ax, " + (yyvsp[-2].symbols)->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov bx, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";

			if((yyvsp[-1].symbol)->getName() == "*"){
				segment_code += "\tmul bx\n";
				segment_code += "\tmov " + temp + ", ax\n";
			}
				
			else if((yyvsp[-1].symbol)->getName() == "/"){
				segment_code += "\txor dx, dx\n";
				segment_code += "\tdiv bx\n";
				segment_code += "\tmov " + temp + ", ax\n";
			}
			else{   //operator % 
				segment_code += "\txor dx, dx\n";
				segment_code += "\tdiv bx\n";
				segment_code += "\tmov " + temp + ", dx\n";
			}
			
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
			(yyval.symbols)->at(0)->setAssemblySymbol(temp); //propagating the calculated result of MULOP operation

			
			
			
                
                
                }
#line 4512 "y.tab.c"
    break;

  case 57: /* unary_expression: ADDOP unary_expression  */
#line 3095 "1805113.y"
{
                f_log_out << "Line " << line_count <<  ": unary_expression : ADDOP unary_expression  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			 
			}
			
  			f_log_out << endl <<endl ;
  			
  			
  		//assembly code
		string temp_var = newTemp();
		string segment_code = ""; 
		
		segment_code += "\tmov ax, " + (yyvsp[0].symbols)->at(0)->getAssemblySymbol() + "\n";
		if((yyvsp[-1].symbol)->getName()=="-")
		{
			segment_code += "\tneg ax \n"; 
			
		}
		segment_code += "\tmov "+temp_var+", ax"  + "\n"; 
		
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
		(yyval.symbols)->at(0)->setAssemblySymbol(temp_var);

                
                
                }
#line 4558 "y.tab.c"
    break;

  case 58: /* unary_expression: NOT unary_expression  */
#line 3139 "1805113.y"
                 {
                f_log_out << "Line " << line_count <<  ": unary_expression : NOT unary_expression  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			 
			}
			
  			f_log_out << endl << endl; ;
		
                
                
                }
#line 4588 "y.tab.c"
    break;

  case 59: /* unary_expression: factor  */
#line 3166 "1805113.y"
                 {
                f_log_out << "Line " << line_count <<  ": unary_expression : factor  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4617 "y.tab.c"
    break;

  case 60: /* factor: variable  */
#line 3193 "1805113.y"
       {
                f_log_out << "Line " << line_count <<  ": factor : variable  \n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
                
               
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
#line 4646 "y.tab.c"
    break;

  case 61: /* factor: ID LPAREN argument_list RPAREN  */
#line 3220 "1805113.y"
        {
	
	//finding each argument and putting into "arguments"
	
	vector<SymbolInfo*> *arguments = new vector<SymbolInfo*> ();
	
	/*for(int i=0;i<$3->size();i++)
	{
	
	if($3->at(i)->getName()!=",")
	{
	
	if((i+1) < $3->size() && $3->at(i+1)->getName()=="[" )
	{
	
	SymbolInfo *temp2 = new SymbolInfo($3->at(i)->getName(),$3->at(i)->getType(),$3->at(i)->getDataType(),$3->at(i)->getIdType(),NULL);
	temp2->setName(temp2->getName() + "["+ $3->at(i+2)->getName()+"]");
	//cout << "pushing " << temp2->getName()<< " in "<<$1->getName() <<endl;
	 arguments -> push_back(temp2);
	 i=i+3;
	
	
	}
	
	
	else
	{
         arguments -> push_back($3->at(i));
         }
	}
	
	
	
	}*/
	bool float_flag = false; 

	//cout << $3->size() << endl;
	for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
	{
	 while(i<(yyvsp[-1].symbols)->size() && (yyvsp[-1].symbols)->at(i)->getName() != ",")
	 {
	 	if(float_flag==false && (yyvsp[-1].symbols)->at(i)->getIdType()=="var" && (yyvsp[-1].symbols)->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	
	 	}
	 	
	 	else if(float_flag==false && (yyvsp[-1].symbols)->at(i)->getIdType()=="cons" && (yyvsp[-1].symbols)->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	//cout << line_count<<": " <<$3->at(i)->getName() << endl;
	 	
	 	}
	 	
	 	else if(float_flag==false && (yyvsp[-1].symbols)->at(i)->getIdType()=="array" && (yyvsp[-1].symbols)->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	
	 	if(i+3 < (yyvsp[-1].symbols)->size())
	 	{
	 	i=i+3;
	 	}
	 	
	 	}
	 	
	 	
	 	else if(float_flag==false && (yyvsp[-1].symbols)->at(i)->getIdType()=="array" && (yyvsp[-1].symbols)->at(i)->getDataType()=="int")
	 	{
	 	
	 	if(i+3 < (yyvsp[-1].symbols)->size())
	 	{
	 	i=i+3;
	 	}
	 	
	 	}
	 	
	 	
	 	
	 	
	 	i++;
	 	
	 }
	 
	 if(float_flag == false)
	 {
	 arguments -> push_back(new SymbolInfo("int","int","int","",NULL));
	// cout << line_count <<$3->at(i)->getName() << endl;
	 }
	 
	 float_flag = false;
	
	}
	
	
                f_log_out << "Line " << line_count <<  ": factor : ID LPAREN argument_list RPAREN\n\n";
                
               
                
                
                //checking if the function call is valid
                
	SymbolInfo *temp = st.Look_up((yyvsp[-3].symbol)->getName());
	
	
	if(temp != NULL //declared or defined earlier
	&& temp->isDeclared() == false //if both declared and defined
        ) //if the function is defined earlier
        
        {
        //setting the id to pass the info of calling function upward through rules
        (yyvsp[-3].symbol)->setName(temp->getName());
        (yyvsp[-3].symbol)->setType(temp->getType());
        (yyvsp[-3].symbol)->setDataType(temp->getDataType());
        (yyvsp[-3].symbol)->setIdType(temp->getIdType());
        (yyvsp[-3].symbol)->setParameters(temp->getParameters());
        
    
        
        if(temp->getParameters() == NULL && arguments->size()!=0) //if callee function has no parameter but passing an argument to it from caller
        {
        
         //  cout << line_count << ": "<<temp->getName()<<" " << temp->getParameters()->size() << " " << arguments->size()<< endl; 
        f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        total_errors++;
        }  
        
        else if(temp->getParameters() == NULL && arguments->size()==0) //calling a non parameterized function correctly 
        {
        //nothing to do
        }
        
        else if(temp->getParameters() != NULL  && temp->getParameters()->size() != arguments->size())   //checking if the argument number match with function parameter number
        {
        
      //  cout << line_count << ": "<<temp->getName()<<" " << temp->getParameters()->size() << " " << arguments->size()<< endl; 
        f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        total_errors++;
        }
        
        else if(temp->getParameters() != NULL  && temp->getParameters()->size() == arguments->size()) //checking if the argument type match with function parameter number
        {
        
        for(int i=0;i<arguments->size();i++)
        {
        	if(arguments->at(i)->getDataType() != temp->getParameters()->at(i)->getDataType() )
        	{
        	
        	
        	//cout<<line_count<<": " << temp->getName() << " 1 " << arguments->at(i)->getDataType() << " 2 " << temp->getParameters()->at(i)->getDataType() << endl;
        	
        	//type convertion from int to float
        	if(arguments->at(i)->getDataType()=="int" && temp->getParameters()->at(i)->getDataType()=="float")
        	{
        	
        	continue;
        	}
        	    f_log_out <<"Error at line "<<line_count<<": "<< (i+1)<<"th argument mismatch in function "<<temp->getName()<<  endl << endl;
          f_error_out <<"Error at line "<<line_count<<": "<< (i+1)<<"th argument mismatch in function "<<temp->getName()<<  endl << endl;
        total_errors++;
        	    break;
        	}
        }
        
        }
        
        
        
        }
        
        else
        {
        
        //function was not defined
          f_log_out <<"Error at line "<<line_count<<": "<< "Undeclared function "<<(yyvsp[-3].symbol)->getName()<<  endl << endl;
         f_error_out <<"Error at line "<<line_count<<": "<< "Undeclared function "<<(yyvsp[-3].symbol)->getName()<< endl << endl;
        total_errors++;
        }
		
              
                
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			
			(yyval.symbols)->push_back((yyvsp[-3].symbol));
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
		
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
               
                //assembly code
		string temp_var = newTemp();
		string segment_code = "";  
		int parameter_count=0;
		
		
	
		for(int i = 0; i < (yyvsp[-1].symbols)->size(); i++){
				if((yyvsp[-1].symbols)->at(i)->getAssemblySymbol() != ""){
					segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(i)->getAssemblySymbol() + "\n";
					segment_code += "\tmov " + temp->getParameters()->at(parameter_count)->getAssemblySymbol() + ", ax\n";
					parameter_count++;
					
				}
			}
			segment_code += "\tcall " + (yyvsp[-3].symbol)->getName() + "\n";
			
			if(temp->getDataType() != "void")
			{
			segment_code += "\tmov ax, ret_temp\n";
			segment_code += "\tmov " + temp_var + ", ax\n";
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
		        (yyval.symbols)->at(0)->setAssemblySymbol(temp_var);
			}
			
			else
			{
			
			(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
			
			}
			

		
         
         
		
		}
#line 4904 "y.tab.c"
    break;

  case 62: /* factor: LPAREN expression RPAREN  */
#line 3477 "1805113.y"
        {
		 
                f_log_out << "Line " << line_count <<  ": factor : LPAREN expression RPAREN\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			(yyval.symbols)->push_back((yyvsp[-2].symbol));
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                //assembly code
		(yyval.symbols)->at(0)->setAssemblySymbol((yyvsp[-1].symbols)->at(0)->getAssemblySymbol());
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + (yyvsp[-1].symbols)->at(0)->getCode());
                
		
		
		}
#line 4941 "y.tab.c"
    break;

  case 63: /* factor: CONST_INT  */
#line 3513 "1805113.y"
        {
	
	f_log_out << "Line " << line_count <<  ": factor : CONST_INT  \n\n";
	
	(yyval.symbols) = new vector<SymbolInfo*>();
	(yyval.symbols)->push_back((yyvsp[0].symbol));
	
	for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
  			
  	//assembly code
	(yyvsp[0].symbol)->setAssemblySymbol((yyvsp[0].symbol)->getName());
	
	
	}
#line 4966 "y.tab.c"
    break;

  case 64: /* factor: CONST_FLOAT  */
#line 3535 "1805113.y"
        {
	
	
	f_log_out << "Line " << line_count <<  ": factor : CONST_FLOAT  \n\n";
	
	(yyval.symbols) = new vector<SymbolInfo*>();
	(yyval.symbols)->push_back((yyvsp[0].symbol));
	
	for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
	
	

  	 f_log_out <<"Error at line "<<line_count<<": "<< "Float number is not supported"<<  endl << endl;
         f_error_out <<"Error at line "<<line_count<<": "<< "Float number is not supported"<< endl << endl;
          cout <<"Error at line "<<line_count<<": "<< "Float number is not supported"<< endl << endl;
        total_errors++;
        
	
	
	}
#line 4997 "y.tab.c"
    break;

  case 65: /* factor: variable INCOP  */
#line 3565 "1805113.y"
          {
                f_log_out << "Line " << line_count <<  ": factor : variable INCOP\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
				
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  
			}
			
  			f_log_out << endl<<endl;
  			
  			
  			string temp = newTemp();
		string segment_code = "";

		string ID_type = (st.Look_up((yyvsp[-1].symbols)->at(0)->getName()))->getIdType();

		if(ID_type != "array"){
			segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tinc " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol()   + "\n";
		}

		else if(ID_type == "array"){
			segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "[di]\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tinc " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "[di]\n";
		}

		(yyval.symbols)->at(0)->setAssemblySymbol(temp);
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
	  }
#line 5045 "y.tab.c"
    break;

  case 66: /* factor: variable DECOP  */
#line 3611 "1805113.y"
         {
                f_log_out << "Line " << line_count <<  ": factor : variable DECOP\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			for(int i=0;i<(yyvsp[-1].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-1].symbols)->at(i));
			}
			(yyval.symbols)->push_back((yyvsp[0].symbol));
			
				
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			  
			}
			
  			f_log_out << endl<<endl;
  			
  		//assembly code
		string temp = newTemp();
		string segment_code = "";

		string ID_type = (st.Look_up((yyvsp[-1].symbols)->at(0)->getName()))->getIdType();

		if(ID_type != "array"){
			segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tdec " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol()   + "\n";
		}

		else if(ID_type == "array"){
			segment_code += "\tmov ax, " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "[di]\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tdec " + (yyvsp[-1].symbols)->at(0)->getAssemblySymbol() + "[di]\n";
		}

		(yyval.symbols)->at(0)->setAssemblySymbol(temp);
		(yyval.symbols)->at(0)->setCode((yyval.symbols)->at(0)->getCode() + segment_code);
	  }
#line 5093 "y.tab.c"
    break;

  case 67: /* argument_list: arguments  */
#line 3658 "1805113.y"
{
		 
                f_log_out << "Line " << line_count <<  ": argument_list : arguments\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}
#line 5127 "y.tab.c"
    break;

  case 68: /* argument_list: %empty  */
#line 3691 "1805113.y"
                           {
			(yyval.symbols) = new vector<SymbolInfo*>();
		  	f_log_out << "Line no: " << line_count <<  " argument_list : \n\n";
	  		f_log_out << endl << endl;
		  }
#line 5137 "y.tab.c"
    break;

  case 69: /* arguments: arguments COMMA logic_expression  */
#line 3700 "1805113.y"
 {
		 
                f_log_out << "Line " << line_count <<  ": arguments : arguments COMMA logic_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<(yyvsp[-2].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[-2].symbols)->at(i));
			}
			
			(yyval.symbols)->push_back((yyvsp[-1].symbol));
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}
#line 5176 "y.tab.c"
    break;

  case 70: /* arguments: logic_expression  */
#line 3736 "1805113.y"
              {
		 
                f_log_out << "Line " << line_count <<  ": arguments : logic_expression\n\n";
                
                
                        (yyval.symbols) = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<(yyvsp[0].symbols)->size();i++)
			{
			(yyval.symbols)->push_back((yyvsp[0].symbols)->at(i));
			}
			
			
			for(int i=0;i<(yyval.symbols)->size();i++)
			{
			  f_log_out << (yyval.symbols)->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}
#line 5209 "y.tab.c"
    break;


#line 5213 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 3766 "1805113.y"



int main(int argc,char *argv[])
{



	if(argc!=2){
		cout << "Please provide input file name and try again\n";
		return 0;
	}
	
	FILE *input_file=fopen(argv[1],"r");
	if(input_file==NULL){
		cout << "Cannot open specified file\n";
		return 0;
	}
	
	yyin=input_file;
	
	
	yyparse();
	
	st.Print_All_Scope_Table(f_log_out);
	f_log_out << "Total lines: " << line_count-1 << endl;
        f_log_out << "Total errors: " << total_errors << endl<<endl;
	
	
	fclose(yyin);
	f_log_out.close();
	f_error_out.close();
	Optimized_Code("code.asm");
	
	
	return 0;
}

