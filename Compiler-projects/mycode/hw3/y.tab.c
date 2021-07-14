/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "compiler_hw3.y"

    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    #define codegen(...) \
        do { \
            for (int i = 0; i < INDENT; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;
    
    /* Other global variables */
    FILE *fout = NULL;
    bool HAS_ERROR = false;
    int INDENT = 0;
    
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
        HAS_ERROR = true;
    }

   /* Symbol table function - you can add new function if needed. */
    typedef struct symbol_table{
        int Index;
        char Name[20];
        char TypeS[20];
        int Address;
        int Lineno;
        char Element[20];
    };

    struct symbol_table table_list[20][20];
    int Index_con[20]={};
    int addno = 0;
    int scope_level = 0;
    int print_type = 0; // 0bool, 1int, 2float, 3string
    char tempstring[20];
    char tempyaya[20];
    int preload_no = 0;
    int pre_intlit=0;
    int b_even = 0;
    int b_odd = 1;
    int loop_n= 0;
    bool wh_flag=false;
    int in_dec=0;
    int conver_no;
    bool conver_flag = false;
    int array_counter=0;
    bool array_flag = false;
    int array_size_counter =0;
    bool array_store=true;
    bool array_type_float=false;
    
    static void create_symbol(/* ... */){}
    static void insert_symbol(char *Name_insert, char *Type_insert ,char *Element_insert){
        int the_lineno = -1;
        
        for(int j=0;j < Index_con[scope_level];j++)
        {
            if(!strcmp(Name_insert,table_list[scope_level][j].Name))
            {    
                the_lineno = table_list[scope_level][j].Lineno;
            }
        }
        
        if(the_lineno == -1)
        {
            printf("> Insert {%s} into symbol table (scope level: %d)\n", Name_insert, scope_level);
            table_list[scope_level][Index_con[scope_level]].Index = Index_con[scope_level];
            strcpy(table_list[scope_level][Index_con[scope_level]].Name , Name_insert);
            strcpy(table_list[scope_level][Index_con[scope_level]].TypeS , Type_insert);
            table_list[scope_level][Index_con[scope_level]].Address = addno;
            table_list[scope_level][Index_con[scope_level]].Lineno = yylineno;
            strcpy(table_list[scope_level][Index_con[scope_level]].Element ,Element_insert);
            addno++;
            Index_con[scope_level]++;
            if(Element_insert[0]=='i')
            {    
                codegen("newarray int\n");
                codegen("astore %d\n",array_counter);
                array_store = false;
                array_counter++;
                array_size_counter =0;
            }
            if(Element_insert[0]=='f')
            {    
                codegen("newarray float\n");
                codegen("astore %d\n",array_counter);
                array_store = false;
                array_counter++;
                array_size_counter =0;
                array_type_float = true;
            }
        }
        else
            printf("error:%d: %s redeclared in this block. previous declaration at line %d\n",yylineno,Name_insert,the_lineno);
    };

    static void lookup_symbol(char* input_string){
        int the_address = -1;
        char type_gen='Z';
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    the_address = table_list[i][j].Address;
                    type_gen=table_list[i][j].TypeS[0];
                }
            }
        }
        if(the_address != -1)
            {
                printf("IDENT (name=%s, address=%d)\n",input_string, the_address);
                if(type_gen=='s')
                    codegen("aload %d\n",the_address);
                else if(type_gen == 'b')
                    codegen("iload %d\n",the_address);
                else
                    codegen("%cload %d\n",type_gen,the_address);
                preload_no = the_address;
                if(the_address>1)
                    conver_no = the_address;
            }
        else
            {
                printf("error:%d: undefined: %s\n",yylineno,input_string);
                HAS_ERROR = true;
            }
    };

    static void lookup_symbol_arraytype(char* input_string){
        char temp_type[20];
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    strcpy(temp_type , table_list[i][j].Element);
                }
            }
        }
        if(!strcmp(temp_type,"int"))
            print_type = 1;
        if(!strcmp(temp_type,"float"))
            print_type = 2;
        if(!strcmp(temp_type,"string"))
            print_type = 3;
        if(!strcmp(temp_type,"bool"))
            print_type = 0;
    };

    static void lookup_symbol_arraytype_print(char* input_string){
        char temp_type[20];
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    strcpy(temp_type , table_list[i][j].Element);
                }
            }
        }
        if(!strcmp(temp_type,"int"))
            printf("PRINT int\n");
        if(!strcmp(temp_type,"float"))
            printf("PRINT float\n");
        if(!strcmp(temp_type,"string"))
            printf("PRINT string\n");
        if(!strcmp(temp_type,"bool"))
            printf("PRINT bool\n");
    };

    static void lookup_symbol_IDENTtype(char* input_string){
        char temp_type[20];
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    strcpy(temp_type , table_list[i][j].TypeS);
                }
            }
        }
        if(!strcmp(temp_type,"int"))
            print_type = 1;
        if(!strcmp(temp_type,"float"))
            print_type = 2;
        if(!strcmp(temp_type,"string"))
            print_type = 3;
        if(!strcmp(temp_type,"bool"))
            print_type = 0;
    };

    static char lookup_symbol_conversiontype(char* input_string){
        char temp_type[20];
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    strcpy(temp_type , table_list[i][j].TypeS);
                }
            }
        }
        if(!strcmp(temp_type,"int"))
            return 'i';
        else if(!strcmp(temp_type,"float"))
            return 'f';
        else if(!strcmp(temp_type,"string"))
            return 's';
        else if(!strcmp(temp_type,"bool"))
            return 'b';
        else
            return 'W';
    };

    //codegen lookup symbol
    static char lookup_symbol_codegen_type(char* input_string){
        int the_address = -1;
        char type_gen='Z';
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    the_address = table_list[i][j].Address;
                    type_gen=table_list[i][j].TypeS[0];
                }
            }
        }
        if(the_address != -1)
                return type_gen;
        else
            return 'Z';
    };
    //get type
    static char get_type()
    {
        if(print_type == 0 )
            return 'b';
        if(print_type == 1 )
            return 'i';
        if(print_type == 2 )
            return 'f';
        if(print_type == 3 )
            return 's';
        else
            return 'w';
    }

    static void dump_symbol(/* ... */){
        printf("> Dump symbol table (scope level: %d)\n",scope_level);
        printf("%-10s%-10s%-10s%-10s%-10s%s\n", "Index", "Name", "Type", "Address", "Lineno", "Element type");
        for(int i=0; i<Index_con[scope_level] ;i++)
            printf("%-10d%-10s%-10s%-10d%-10d%s\n",table_list[scope_level][i].Index, table_list[scope_level][i].Name, table_list[scope_level][i].TypeS, table_list[scope_level][i].Address, table_list[scope_level][i].Lineno, table_list[scope_level][i].Element);
        Index_con[scope_level]=0;
    };

#line 343 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

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
#line 280 "compiler_hw3.y"

    int i_val;
    float f_val;
    char *s_val;
    bool b_val;

    struct ctr{
        char* id_name;
        char id_type[20];
    }ctr;

#line 495 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,    51,     2,     2,
       2,     2,    49,    47,     2,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      45,    53,    46,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   317,   317,   321,   325,   326,   327,   328,   332,   333,
     337,   338,   342,   400,   404,   405,   409,   410,   414,   418,
     419,   441,   442,   443,   444,   445,   446,   450,   451,   455,
     456,   457,   461,   462,   463,   467,   468,   469,   473,   474,
     479,   483,   490,   496,   502,   519,   544,   560,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   589,   594,   599,
     604,   609,   616,   620,   620,   631,   652,   652,   658,   725,
     729,   730,   731,   732,   733,   734,   738,   749,   763,   767,
     767,   767,   771,   772,   776,   777,   778,   782,   787,   794,
     786,   820,   837,   819,   861,   865,   860,   872,   876,   880,
     881,   882,   886
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "BOOL", "STRING",
  "SEMICOLON", "INC", "DEC", "GEQ", "LEQ", "EQL", "NEQ", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "QUO_ASSIGN", "REM_ASSIGN", "AND", "OR",
  "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "COMMA",
  "QUOTA", "RETURN", "IF", "ELSE", "FOR", "WHILE", "TRUE", "FALSE",
  "CONTINUE", "BREAK", "VOID", "PRINT", "IDENT", "INT_LIT", "FLOAT_LIT",
  "STRING_LIT", "BOOL_LIT", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "'='", "$accept", "Program", "Type", "TypeName",
  "Expression", "AA", "BB", "CC", "DD", "EE", "UnaryExpr", "cmp_op",
  "add_op", "mul_op", "unary_op", "PrimaryExpr", "Operand", "Literal",
  "IndexExpr", "ConversionExpr", "Statement", "ExpressionExpr",
  "ExpressionStmt", "DeclarationStmt", "$@1", "$@2", "AssignmetExpr",
  "AssignmetStmt", "assign_op", "IncDecExpr", "IncDecStmt", "Block", "$@3",
  "$@4", "StatementList", "IfStmt", "Condition", "WhileStmt", "$@5", "$@6",
  "ForStmt", "$@7", "$@8", "ForClause", "$@9", "$@10", "InitStmt",
  "PostStmt", "SimpleExpr", "PrintStmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,    60,    62,    43,    45,    42,
      47,    37,    33,    61
};
# endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      14,  -102,  -102,  -102,  -102,    67,  -102,    96,    27,    38,
      44,    30,  -102,  -102,  -102,  -102,  -102,  -102,  -102,    51,
      28,  -102,     7,    48,    -4,    16,   -37,  -102,  -102,    96,
      52,  -102,  -102,  -102,  -102,    14,    75,  -102,  -102,    76,
    -102,    77,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
      63,    11,    14,    54,    69,    96,  -102,    96,    56,    57,
      59,    62,    64,  -102,     3,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,    96,  -102,    96,    96,  -102,  -102,  -102,  -102,
    -102,  -102,    96,  -102,  -102,    96,  -102,  -102,  -102,    96,
    -102,    96,  -102,  -102,  -102,  -102,    49,  -102,  -102,    72,
       7,  -102,  -102,    83,    99,  -102,    96,    18,  -102,  -102,
    -102,  -102,  -102,  -102,    60,    89,    48,    54,    -4,    16,
     -37,  -102,    12,  -102,  -102,    90,     4,  -102,  -102,  -102,
     111,    96,    96,  -102,  -102,  -102,  -102,    69,    96,    98,
    -102,    23,    25,  -102,  -102,    69,  -102,   114,  -102,   115,
    -102,  -102,    96,  -102,  -102
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     5,     7,     6,     0,    79,     0,     0,     0,
       0,    39,    41,    42,    43,    44,    32,    33,    34,     0,
       0,     3,     0,     9,    11,    13,    15,    17,    18,     0,
      19,    35,    38,    36,    37,    83,     0,    56,    48,     0,
      49,     0,    50,    51,     2,    52,    53,    54,    55,    39,
       0,     0,     0,    87,     0,     0,    88,     0,     0,     0,
       0,     0,     0,     1,    63,    76,    77,    71,    72,    73,
      74,    75,     0,    70,     0,     0,    26,    24,    21,    22,
      23,    25,     0,    27,    28,     0,    29,    30,    31,     0,
      20,     0,    82,    62,    69,    78,     0,    40,    80,    84,
     100,    99,   101,     0,     0,    97,     0,     0,    57,    58,
      59,    60,    61,    65,     0,     0,     8,    68,    10,    12,
      14,    16,     0,    46,    47,     0,     0,    91,    94,    89,
       0,     0,     0,    45,    81,    86,    85,     0,     0,     0,
     102,     0,     0,    92,    95,     0,    64,     0,    93,     0,
      90,    67,     0,    96,    98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,  -102,   118,  -102,    -5,    53,    55,    42,    43,    40,
     102,  -102,  -102,  -102,  -102,  -102,  -102,    36,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,   -54,  -102,  -102,   -52,
    -102,   -50,  -102,  -102,   -24,     8,  -101,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,   -17,  -102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    82,    85,    89,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   114,   115,    39,    40,    74,    41,
      42,    43,    52,   125,    44,    45,    54,    46,   106,   139,
      47,   137,   148,   103,   138,   149,   104,   153,   105,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   101,    53,   102,    99,   129,    76,    77,    78,    79,
     113,    92,    86,    87,    88,    65,    66,     1,     2,     3,
       4,    67,    68,    69,    70,    71,   -66,    72,    98,     6,
     146,    72,    72,    97,     7,     5,   133,   144,    72,     6,
     130,    80,    81,    72,     7,    72,     8,     9,    55,   147,
     100,    63,   107,    10,    11,    12,    13,    14,    15,    56,
      73,    16,    17,    83,    84,    57,    18,    75,    64,   117,
       1,     2,     3,     4,    72,    91,   135,    58,    59,    60,
      61,    62,    93,    94,    95,    96,   122,   143,     5,   123,
      12,    13,    14,    15,     6,   150,   108,   109,   101,   110,
     102,    53,   111,   126,   112,   127,   128,    49,    12,    13,
      14,    15,   132,   131,    16,    17,   134,     5,   140,    18,
     145,   151,   152,    50,   119,   116,   141,   142,   120,   121,
     118,    90,   124,    53,   136,   154,    49,    12,    13,    14,
      15,     0,     0,    16,    17,     0,     0,   100,    18
};

static const yytype_int16 yycheck[] =
{
       5,    55,     7,    55,    54,   106,    10,    11,    12,    13,
       7,    35,    49,    50,    51,     8,     9,     3,     4,     5,
       6,    14,    15,    16,    17,    18,    23,    20,    52,    25,
       7,    20,    20,    22,    30,    21,    24,   138,    20,    25,
      22,    45,    46,    20,    30,    20,    32,    33,    21,    24,
      55,     0,    57,    39,    40,    41,    42,    43,    44,    21,
      53,    47,    48,    47,    48,    21,    52,    19,    40,    74,
       3,     4,     5,     6,    20,    23,   126,    47,    48,    49,
      50,    51,     7,     7,     7,    22,    91,   137,    21,    40,
      41,    42,    43,    44,    25,   145,    40,    40,   152,    40,
     152,   106,    40,    31,    40,    22,     7,    40,    41,    42,
      43,    44,    23,    53,    47,    48,    26,    21,     7,    52,
      22,     7,     7,     5,    82,    72,   131,   132,    85,    89,
      75,    29,    96,   138,   126,   152,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,   152,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    21,    25,    30,    32,    33,
      39,    40,    41,    42,    43,    44,    47,    48,    52,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    80,
      81,    83,    84,    85,    88,    89,    91,    94,   103,    40,
      56,    58,    86,    58,    90,    21,    21,    21,    47,    48,
      49,    50,    51,     0,    40,     8,     9,    14,    15,    16,
      17,    18,    20,    53,    82,    19,    10,    11,    12,    13,
      45,    46,    65,    47,    48,    66,    49,    50,    51,    67,
      64,    23,    88,     7,     7,     7,    22,    22,    88,    85,
      58,    80,    83,    97,   100,   102,    92,    58,    40,    40,
      40,    40,    40,     7,    78,    79,    59,    58,    60,    61,
      62,    63,    58,    40,    71,    87,    31,    22,     7,    90,
      22,    53,    23,    24,    26,    85,    89,    95,    98,    93,
       7,    58,    58,    85,    90,    22,     7,    24,    96,    99,
      85,     7,     7,   101,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    57,    57,    57,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    64,
      64,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    72,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    75,    76,    78,    77,    77,    79,    77,    80,    81,
      82,    82,    82,    82,    82,    82,    83,    83,    84,    86,
      87,    85,    88,    88,    89,    89,    89,    90,    92,    93,
      91,    95,    96,    94,    98,    99,    97,   100,   101,   102,
     102,   102,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     2,     0,     6,     3,     0,     7,     3,     2,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     0,
       0,     5,     2,     1,     3,     5,     5,     1,     0,     0,
       7,     0,     0,     7,     0,     0,     7,     1,     1,     1,
       1,     1,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 317 "compiler_hw3.y"
                    { dump_symbol();}
#line 1791 "y.tab.c"
    break;

  case 3:
#line 321 "compiler_hw3.y"
               { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1797 "y.tab.c"
    break;

  case 4:
#line 325 "compiler_hw3.y"
          { (yyval.s_val) = "i";}
#line 1803 "y.tab.c"
    break;

  case 5:
#line 326 "compiler_hw3.y"
           { (yyval.s_val) = "f";}
#line 1809 "y.tab.c"
    break;

  case 6:
#line 327 "compiler_hw3.y"
            { (yyval.s_val) = "s";}
#line 1815 "y.tab.c"
    break;

  case 7:
#line 328 "compiler_hw3.y"
          { (yyval.s_val) = "b";}
#line 1821 "y.tab.c"
    break;

  case 8:
#line 332 "compiler_hw3.y"
                       { printf("OR\n"); codegen("ior\n"); print_type = 0; (yyval.s_val) = "B";}
#line 1827 "y.tab.c"
    break;

  case 9:
#line 333 "compiler_hw3.y"
         { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1833 "y.tab.c"
    break;

  case 10:
#line 337 "compiler_hw3.y"
                { printf("AND\n");codegen("iand\n");}
#line 1839 "y.tab.c"
    break;

  case 11:
#line 338 "compiler_hw3.y"
         { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1845 "y.tab.c"
    break;

  case 12:
#line 343 "compiler_hw3.y"
    { 
        printf("%s\n",(yyvsp[-1].s_val));
        if(get_type()=='i')
        {
            if((yyvsp[-1].s_val)=="EQL")
            {
                codegen("isub\n");
                codegen("ifeq L_cmp_%d\n",b_even);
                codegen("iconst_0\n");
                codegen("goto L_cmp_%d\n",b_odd);
                codegen("L_cmp_%d :\n",b_even);
                codegen("iconst_1\n");
                codegen("L_cmp_%d :\n",b_odd);
                b_even +=2;
                b_odd +=2;
            }
            if((yyvsp[-1].s_val) == "GTR")
            {
                codegen("isub\n");
                codegen("ifgt L_cmp_%d\n",b_even);
                codegen("iconst_0\n");
                codegen("goto L_cmp_%d\n",b_odd);
                codegen("L_cmp_%d:\n",b_even);
                codegen("iconst_1\n");
                codegen("L_cmp_%d:\n",b_odd);
                b_even +=2;
                b_odd +=2;
            }
            if((yyvsp[-1].s_val) == "LEQ")
            {
                codegen("isub\n");
                codegen("ifle L_cmp_%d\n",b_even);
                codegen("iconst_0\n");
                codegen("goto L_cmp_%d\n",b_odd);
                codegen("L_cmp_%d:\n",b_even);
                codegen("iconst_1\n");
                codegen("L_cmp_%d:\n",b_odd);
                b_even +=2;
                b_odd +=2;
            }
        }
        if(get_type()=='f')
        {
            if((yyvsp[-1].s_val) == "GTR")
            {
                codegen("fcmpl\n");
                codegen("iflt L_cmp_%d\n",b_even);
                codegen("iconst_1\n");
                codegen("goto L_cmp_%d\n",b_odd);
                codegen("L_cmp_%d:\n",b_even);
                codegen("iconst_0\n");
                codegen("L_cmp_%d:\n",b_odd);
                b_even +=2;
                b_odd +=2;
            }
        }
    }
#line 1907 "y.tab.c"
    break;

  case 13:
#line 400 "compiler_hw3.y"
         { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1913 "y.tab.c"
    break;

  case 14:
#line 404 "compiler_hw3.y"
                   { printf("%s\n",(yyvsp[-1].s_val));codegen("%c%s\n",get_type(),(yyvsp[-1].s_val));}
#line 1919 "y.tab.c"
    break;

  case 15:
#line 405 "compiler_hw3.y"
         { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1925 "y.tab.c"
    break;

  case 16:
#line 409 "compiler_hw3.y"
                   { printf("%s\n",(yyvsp[-1].s_val));codegen("%c%s\n",get_type(),(yyvsp[-1].s_val));}
#line 1931 "y.tab.c"
    break;

  case 17:
#line 410 "compiler_hw3.y"
         { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1937 "y.tab.c"
    break;

  case 18:
#line 414 "compiler_hw3.y"
                { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1943 "y.tab.c"
    break;

  case 19:
#line 418 "compiler_hw3.y"
                  { (yyval.s_val) = (yyvsp[0].s_val);}
#line 1949 "y.tab.c"
    break;

  case 20:
#line 420 "compiler_hw3.y"
    { 
        printf("%s\n",(yyvsp[-1].s_val));
        if((yyvsp[-1].s_val) == "neg")
            codegen("%c%s\n",get_type(),(yyvsp[-1].s_val));
        if((yyvsp[-1].s_val) == "not")
            {
                codegen("iconst_1 ;load true for not\n");
                codegen("ixor\n");
            }
    }
#line 1964 "y.tab.c"
    break;

  case 21:
#line 441 "compiler_hw3.y"
         { (yyval.s_val) ="EQL";}
#line 1970 "y.tab.c"
    break;

  case 22:
#line 442 "compiler_hw3.y"
         { (yyval.s_val) ="NEQ";}
#line 1976 "y.tab.c"
    break;

  case 23:
#line 443 "compiler_hw3.y"
         { (yyval.s_val) ="LSS";}
#line 1982 "y.tab.c"
    break;

  case 24:
#line 444 "compiler_hw3.y"
         { (yyval.s_val) ="LEQ";}
#line 1988 "y.tab.c"
    break;

  case 25:
#line 445 "compiler_hw3.y"
         { (yyval.s_val) ="GTR";}
#line 1994 "y.tab.c"
    break;

  case 26:
#line 446 "compiler_hw3.y"
         { (yyval.s_val) ="GEQ";}
#line 2000 "y.tab.c"
    break;

  case 27:
#line 450 "compiler_hw3.y"
         { (yyval.s_val) ="add";}
#line 2006 "y.tab.c"
    break;

  case 28:
#line 451 "compiler_hw3.y"
         { (yyval.s_val) ="sub";}
#line 2012 "y.tab.c"
    break;

  case 29:
#line 455 "compiler_hw3.y"
         { (yyval.s_val) ="mul";}
#line 2018 "y.tab.c"
    break;

  case 30:
#line 456 "compiler_hw3.y"
         { (yyval.s_val) ="div";}
#line 2024 "y.tab.c"
    break;

  case 31:
#line 457 "compiler_hw3.y"
         { (yyval.s_val) ="rem";}
#line 2030 "y.tab.c"
    break;

  case 32:
#line 461 "compiler_hw3.y"
          { (yyval.s_val) = "pos";}
#line 2036 "y.tab.c"
    break;

  case 33:
#line 462 "compiler_hw3.y"
          { (yyval.s_val) = "neg";}
#line 2042 "y.tab.c"
    break;

  case 34:
#line 463 "compiler_hw3.y"
          { (yyval.s_val) = "not";}
#line 2048 "y.tab.c"
    break;

  case 35:
#line 467 "compiler_hw3.y"
              { (yyval.s_val) = (yyvsp[0].s_val);}
#line 2054 "y.tab.c"
    break;

  case 38:
#line 473 "compiler_hw3.y"
              { (yyval.s_val) = (yyvsp[0].s_val);}
#line 2060 "y.tab.c"
    break;

  case 39:
#line 474 "compiler_hw3.y"
            {
        lookup_symbol(yylval.ctr.id_name);
        (yyval.s_val) = lookup_symbol_codegen_type(yylval.ctr.id_name);
        lookup_symbol_IDENTtype(yylval.ctr.id_name);
    }
#line 2070 "y.tab.c"
    break;

  case 41:
#line 483 "compiler_hw3.y"
              {
        printf("INT_LIT %d\n", (yyval.i_val));
        codegen("ldc %d\n",(yyval.i_val));
        print_type = 1;
        pre_intlit = (yyval.i_val);
        (yyval.s_val) = "i";
    }
#line 2082 "y.tab.c"
    break;

  case 42:
#line 490 "compiler_hw3.y"
                {
        printf("FLOAT_LIT %f\n", (yyval.f_val));
        codegen("ldc %f\n",(yyval.f_val));
        print_type = 2;
        (yyval.s_val) = "f";
    }
#line 2093 "y.tab.c"
    break;

  case 43:
#line 496 "compiler_hw3.y"
                 {
        printf("STRING_LIT %s\n", (yyval.s_val));
        codegen("ldc \"%s\"\n",(yyval.s_val));
        print_type = 3;
        (yyval.s_val) = "s";
    }
#line 2104 "y.tab.c"
    break;

  case 44:
#line 502 "compiler_hw3.y"
               {
        if((yyval.b_val))
        {    
            printf("TRUE\n");
            codegen("iconst_1\n");
        }
        else
        {    
            printf("FALSE\n");
            codegen("iconst_0\n");
        }
        print_type = 0;
        (yyval.s_val) = "b";
    }
#line 2123 "y.tab.c"
    break;

  case 45:
#line 520 "compiler_hw3.y"
    {   
        array_flag=true;
        //$$ = $1; 
        //lookup_symbol_arraytype($1);
        //to set array type here
        if(array_type_float)
        {
            if(array_store || array_size_counter>=3)
            {    
                codegen("faload\n");
                print_type=2;
            }

        }
        else
        {
            if(array_store || array_size_counter>=3)
                codegen("iaload\n");
        }
        array_store = true;
    }
#line 2149 "y.tab.c"
    break;

  case 46:
#line 544 "compiler_hw3.y"
                               {
        lookup_symbol((yyvsp[0].s_val));
        printf("%c to %s\n", lookup_symbol_conversiontype((yyvsp[0].s_val)), (yyvsp[-2].s_val));
        codegen("%c2%s\n", lookup_symbol_conversiontype((yyvsp[0].s_val)), (yyvsp[-2].s_val));

        if(!strcmp((yyvsp[-2].s_val),"i"))
        {
            print_type=1;
        }

        if(!strcmp((yyvsp[-2].s_val),"f"))
        {
            print_type=2;
        }
        conver_flag = true;
    }
#line 2170 "y.tab.c"
    break;

  case 47:
#line 560 "compiler_hw3.y"
                                 {
        printf("%s to %s\n", (yyvsp[0].s_val), (yyvsp[-2].s_val));
        codegen("%s2%s\n", (yyvsp[0].s_val),(yyvsp[-2].s_val));
        if(!strcmp((yyvsp[-2].s_val),"i"))
        {
            print_type=1;
        }

        if(!strcmp((yyvsp[-2].s_val),"f"))
        {
            print_type=2;
        }
        conver_flag = true;
    }
#line 2189 "y.tab.c"
    break;

  case 57:
#line 589 "compiler_hw3.y"
                      {
        lookup_symbol((yyvsp[-2].s_val));
        lookup_symbol((yyvsp[0].s_val));
        printf("ADD\n");
    }
#line 2199 "y.tab.c"
    break;

  case 58:
#line 594 "compiler_hw3.y"
                      {
        lookup_symbol((yyvsp[-2].s_val));
        lookup_symbol((yyvsp[0].s_val));
        printf("SUB\n");
    }
#line 2209 "y.tab.c"
    break;

  case 59:
#line 599 "compiler_hw3.y"
                      {
        lookup_symbol((yyvsp[-2].s_val));
        lookup_symbol((yyvsp[0].s_val));
        printf("MUL\n");
    }
#line 2219 "y.tab.c"
    break;

  case 60:
#line 604 "compiler_hw3.y"
                      {
        lookup_symbol((yyvsp[-2].s_val));
        lookup_symbol((yyvsp[0].s_val));
        printf("QUO\n");
    }
#line 2229 "y.tab.c"
    break;

  case 61:
#line 609 "compiler_hw3.y"
                      {
        lookup_symbol((yyvsp[-2].s_val));
        lookup_symbol((yyvsp[0].s_val));
        printf("REM\n");
    }
#line 2239 "y.tab.c"
    break;

  case 63:
#line 620 "compiler_hw3.y"
                 {strcpy(tempstring,yylval.ctr.id_name);}
#line 2245 "y.tab.c"
    break;

  case 64:
#line 620 "compiler_hw3.y"
                                                                                  {
        if(yylval.ctr.id_type[0]=='b')
            codegen("istore %d\n",addno);
        else if(yylval.ctr.id_type[0]=='s')
            codegen("astore %d\n",addno);
        else
            codegen("%cstore %d\n",yylval.ctr.id_type[0],addno);
        
        insert_symbol(tempstring, yylval.ctr.id_type, "-");
    }
#line 2260 "y.tab.c"
    break;

  case 65:
#line 631 "compiler_hw3.y"
                          {
        if(yylval.ctr.id_type[0]=='s')
        {
            codegen("ldc \"\"\n");
            codegen("astore %d\n",addno);
        }
        if(yylval.ctr.id_type[0]=='f')
        {
            codegen("ldc 0.0\n");
            codegen("fstore %d\n",addno);
        }
        if(yylval.ctr.id_type[0]=='i')
        {
            codegen("ldc 0\n");
            codegen("istore %d\n",addno);
        }
        
        //to do another type
        insert_symbol(yylval.ctr.id_name, yylval.ctr.id_type, "-");
    }
#line 2285 "y.tab.c"
    break;

  case 66:
#line 652 "compiler_hw3.y"
                 { strcpy(tempstring,yylval.ctr.id_name);}
#line 2291 "y.tab.c"
    break;

  case 67:
#line 652 "compiler_hw3.y"
                                                                                              {
        insert_symbol(tempstring, "array" , yylval.ctr.id_type);
    }
#line 2299 "y.tab.c"
    break;

  case 68:
#line 658 "compiler_hw3.y"
                                      {
            if((yyvsp[-1].s_val) == "ASSIGN")
            {
                if(conver_flag)
                {
                    if(get_type()=='i')
                    {
                        codegen("istore %d\n",conver_no);
                    }
                    if(get_type()=='f')
                    {
                        codegen("fstore %d\n",conver_no);
                    }
                }
                else
                {
                    if(array_flag)
                    {
                        if(get_type() == 'i')
                            codegen("iastore\n");
                        if(get_type()=='f')
                            codegen("fastore\n");
                        array_size_counter++;
                        array_store = false;
                    }
                    else
                    {
                        if(get_type()=='s')
                            codegen("astore %d\n",preload_no);
                        else if(get_type()=='b')
                            codegen("istore %d\n",preload_no);
                        else
                            codegen("%cstore %d\n",get_type(),preload_no);
                    }
                }
            }
            if((yyvsp[-1].s_val) == "ADD_ASSIGN")
            {
                codegen("%cadd\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
                
            }
            if((yyvsp[-1].s_val) == "SUB_ASSIGN")
            {
                codegen("%csub\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if((yyvsp[-1].s_val) == "MUL_ASSIGN")
            {
                codegen("%cmul\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if((yyvsp[-1].s_val) == "QUO_ASSIGN")
            {
                codegen("%cdiv\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if((yyvsp[-1].s_val) == "REM_ASSIGN")
            {
                codegen("%crem\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            printf("%s\n",(yyvsp[-1].s_val)); 
        }
#line 2368 "y.tab.c"
    break;

  case 70:
#line 729 "compiler_hw3.y"
          { (yyval.s_val) = "ASSIGN";}
#line 2374 "y.tab.c"
    break;

  case 71:
#line 730 "compiler_hw3.y"
                 { (yyval.s_val) = "ADD_ASSIGN";}
#line 2380 "y.tab.c"
    break;

  case 72:
#line 731 "compiler_hw3.y"
                 { (yyval.s_val) = "SUB_ASSIGN";}
#line 2386 "y.tab.c"
    break;

  case 73:
#line 732 "compiler_hw3.y"
                 { (yyval.s_val) = "MUL_ASSIGN";}
#line 2392 "y.tab.c"
    break;

  case 74:
#line 733 "compiler_hw3.y"
                 { (yyval.s_val) = "QUO_ASSIGN";}
#line 2398 "y.tab.c"
    break;

  case 75:
#line 734 "compiler_hw3.y"
                 { (yyval.s_val) = "REM_ASSIGN";}
#line 2404 "y.tab.c"
    break;

  case 76:
#line 739 "compiler_hw3.y"
    { 
        printf("INC\n");
        if((yyvsp[-1].s_val) == 'i')
            codegen("ldc 1\n");
        else
            codegen("ldc 1.0\n");
        codegen("%cadd\n",get_type());
        codegen("%cstore %d\n",get_type(),preload_no);
        in_dec = 1;
    }
#line 2419 "y.tab.c"
    break;

  case 77:
#line 750 "compiler_hw3.y"
    { 
        printf("DEC\n");
        if((yyvsp[-1].s_val) == 'i')
            codegen("ldc 1\n");
        else
            codegen("ldc 1.0\n");
        codegen("%csub\n",get_type());
        codegen("%cstore %d\n",get_type(),preload_no);
        in_dec = 0;
    }
#line 2434 "y.tab.c"
    break;

  case 79:
#line 767 "compiler_hw3.y"
             { scope_level++;}
#line 2440 "y.tab.c"
    break;

  case 80:
#line 767 "compiler_hw3.y"
                                             { dump_symbol(); scope_level--;}
#line 2446 "y.tab.c"
    break;

  case 88:
#line 787 "compiler_hw3.y"
    {
        if(wh_flag)
            codegen("L_for_begin%d :\n",scope_level);
        else
            codegen("L_for_begin%d :\n",scope_level+10);
    }
#line 2457 "y.tab.c"
    break;

  case 89:
#line 794 "compiler_hw3.y"
    {   
        if(wh_flag)
            codegen("ifeq L_for_exit%d\n",scope_level);
        else
            codegen("ifeq L_for_exit%d\n",scope_level+10);
    }
#line 2468 "y.tab.c"
    break;

  case 90:
#line 801 "compiler_hw3.y"
    {
        if(wh_flag)
        {
            codegen("goto L_for_begin%d\n",scope_level);
            codegen("L_for_exit%d :\n",scope_level);
        }
        else
        {
            codegen("goto L_for_begin%d\n",scope_level+10);
            codegen("L_for_exit%d :\n",scope_level+10);
        }
        loop_n++;
        if(scope_level==0)
            wh_flag = true;
    }
#line 2488 "y.tab.c"
    break;

  case 91:
#line 820 "compiler_hw3.y"
    {
        if(in_dec==0)
        {
            codegen("iload %d\n",preload_no);
            codegen("ldc 1\n");
            codegen("%cadd\n",get_type());
            codegen("%cstore %d\n",get_type(),preload_no);
        }
        else
        {
            codegen("iload %d\n",preload_no);
            codegen("ldc 1\n");
            codegen("%csub\n",get_type());
            codegen("%cstore %d\n",get_type(),preload_no);
        }
    }
#line 2509 "y.tab.c"
    break;

  case 92:
#line 837 "compiler_hw3.y"
    {
        if(in_dec==0)
        {
            codegen("iload %d\n",preload_no);
            codegen("ldc 1\n");
            codegen("%csub\n",get_type());
            codegen("%cstore %d\n",get_type(),preload_no);
        }
        else
        {
            codegen("iload %d\n",preload_no);
            codegen("ldc 1\n");
            codegen("%cadd\n",get_type());
            codegen("%cstore %d\n",get_type(),preload_no);
        }
    }
#line 2530 "y.tab.c"
    break;

  case 93:
#line 853 "compiler_hw3.y"
    {
        codegen("goto for_begin\n");
        codegen("for_exit :\n");
    }
#line 2539 "y.tab.c"
    break;

  case 94:
#line 861 "compiler_hw3.y"
    {
        codegen("for_begin :\n");
    }
#line 2547 "y.tab.c"
    break;

  case 95:
#line 865 "compiler_hw3.y"
    {
        codegen("ifeq for_exit\n");
    }
#line 2555 "y.tab.c"
    break;

  case 102:
#line 886 "compiler_hw3.y"
                                               {
        if(print_type == 0 )
            printf("PRINT bool\n");
        if(print_type == 1 )
            printf("PRINT int\n");
        if(print_type == 2 )
            printf("PRINT float\n");
        if(print_type == 3 )
            printf("PRINT string\n");
        if(print_type == 0)
        {
            codegen("ifne L_cmp_%d\n",b_even);
            codegen("ldc \"false\"\n");
            codegen("goto L_cmp_%d\n",b_odd);
            codegen("L_cmp_%d:\n",b_even);
            codegen("ldc \"true\"\n");
            codegen("L_cmp_%d:\n",b_odd);
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n\n");
            b_even+=2;
            b_odd+=2;
        }
        if(print_type == 1)
        {
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(I)V\n\n");
        }

        if(print_type==2)
        {
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(F)V\n\n");
        }

        if(print_type == 3)
        {
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n\n");
        }
    }
#line 2604 "y.tab.c"
    break;


#line 2608 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 932 "compiler_hw3.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    codegen(".source hw3.j\n");
    codegen(".class public Main\n");
    codegen(".super java/lang/Object\n");
    codegen(".method public static main([Ljava/lang/String;)V\n");
    codegen(".limit stack 100\n");
    codegen(".limit locals 100\n");
    INDENT++;

    yyparse();

	printf("Total lines: %d\n", yylineno);

    /* Codegen end */
    codegen("return\n");
    INDENT--;
    codegen(".end method\n");
    fclose(fout);
    fclose(yyin);

    if (HAS_ERROR) {
        remove(bytecode_filename);
    }
    return 0;
}
