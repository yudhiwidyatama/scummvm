/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 54 "engines/director/lingo/lingo-gr.y"

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/endian.h"
#include "common/hash-str.h"
#include "common/rect.h"

#include "director/director.h"
#include "director/lingo/lingo.h"
#include "director/lingo/lingo-ast.h"
#include "director/lingo/lingo-code.h"
#include "director/lingo/lingo-codegen.h"
#include "director/lingo/lingo-gr.h"
#include "director/lingo/lingo-object.h"
#include "director/lingo/lingo-the.h"

extern int yylex();
extern int yyparse();

using namespace Director;

static void yyerror(const char *s) {
	LingoCompiler *compiler = g_lingo->_compiler;
	compiler->_hadError = true;
	warning("######################  LINGO: %s at line %d col %d in %s id: %d",
		s, compiler->_linenumber, compiler->_colnumber, scriptType2str(compiler->_assemblyContext->_scriptType),
		compiler->_assemblyContext->_id);
	if (compiler->_lines[2] != compiler->_lines[1])
		warning("# %3d: %s", compiler->_linenumber - 2, Common::String(compiler->_lines[2], compiler->_lines[1] - 1).c_str());

	if (compiler->_lines[1] != compiler->_lines[0])
		warning("# %3d: %s", compiler->_linenumber - 1, Common::String(compiler->_lines[1], compiler->_lines[0] - 1).c_str());

	const char *ptr = compiler->_lines[0];

	while (*ptr && *ptr != '\n')
		ptr++;

	warning("# %3d: %s", compiler->_linenumber, Common::String(compiler->_lines[0], ptr).c_str());

	Common::String arrow;
	for (uint i = 0; i < compiler->_colnumber; i++)
		arrow += ' ';

	warning("#      %s^ about here", arrow.c_str());
}

static void checkEnd(Common::String *token, Common::String *expect, bool required) {
	if (required) {
		if (token->compareToIgnoreCase(*expect)) {
			Common::String err = Common::String::format("end mismatch. Expected %s but got %s", expect->c_str(), token->c_str());
			yyerror(err.c_str());
		}
	}
}


#line 129 "engines/director/lingo/lingo-gr.cpp"

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

#include "lingo-gr.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tUNARY = 3,                     /* tUNARY  */
  YYSYMBOL_tINT = 4,                       /* tINT  */
  YYSYMBOL_tFLOAT = 5,                     /* tFLOAT  */
  YYSYMBOL_tVARID = 6,                     /* tVARID  */
  YYSYMBOL_tSTRING = 7,                    /* tSTRING  */
  YYSYMBOL_tSYMBOL = 8,                    /* tSYMBOL  */
  YYSYMBOL_tENDCLAUSE = 9,                 /* tENDCLAUSE  */
  YYSYMBOL_tCAST = 10,                     /* tCAST  */
  YYSYMBOL_tFIELD = 11,                    /* tFIELD  */
  YYSYMBOL_tSCRIPT = 12,                   /* tSCRIPT  */
  YYSYMBOL_tWINDOW = 13,                   /* tWINDOW  */
  YYSYMBOL_tDELETE = 14,                   /* tDELETE  */
  YYSYMBOL_tDOWN = 15,                     /* tDOWN  */
  YYSYMBOL_tELSE = 16,                     /* tELSE  */
  YYSYMBOL_tEXIT = 17,                     /* tEXIT  */
  YYSYMBOL_tFRAME = 18,                    /* tFRAME  */
  YYSYMBOL_tGLOBAL = 19,                   /* tGLOBAL  */
  YYSYMBOL_tGO = 20,                       /* tGO  */
  YYSYMBOL_tHILITE = 21,                   /* tHILITE  */
  YYSYMBOL_tIF = 22,                       /* tIF  */
  YYSYMBOL_tIN = 23,                       /* tIN  */
  YYSYMBOL_tINTO = 24,                     /* tINTO  */
  YYSYMBOL_tMACRO = 25,                    /* tMACRO  */
  YYSYMBOL_tMOVIE = 26,                    /* tMOVIE  */
  YYSYMBOL_tNEXT = 27,                     /* tNEXT  */
  YYSYMBOL_tOF = 28,                       /* tOF  */
  YYSYMBOL_tPREVIOUS = 29,                 /* tPREVIOUS  */
  YYSYMBOL_tPUT = 30,                      /* tPUT  */
  YYSYMBOL_tREPEAT = 31,                   /* tREPEAT  */
  YYSYMBOL_tSET = 32,                      /* tSET  */
  YYSYMBOL_tTHEN = 33,                     /* tTHEN  */
  YYSYMBOL_tTO = 34,                       /* tTO  */
  YYSYMBOL_tWHEN = 35,                     /* tWHEN  */
  YYSYMBOL_tWITH = 36,                     /* tWITH  */
  YYSYMBOL_tWHILE = 37,                    /* tWHILE  */
  YYSYMBOL_tFACTORY = 38,                  /* tFACTORY  */
  YYSYMBOL_tOPEN = 39,                     /* tOPEN  */
  YYSYMBOL_tPLAY = 40,                     /* tPLAY  */
  YYSYMBOL_tINSTANCE = 41,                 /* tINSTANCE  */
  YYSYMBOL_tGE = 42,                       /* tGE  */
  YYSYMBOL_tLE = 43,                       /* tLE  */
  YYSYMBOL_tEQ = 44,                       /* tEQ  */
  YYSYMBOL_tNEQ = 45,                      /* tNEQ  */
  YYSYMBOL_tAND = 46,                      /* tAND  */
  YYSYMBOL_tOR = 47,                       /* tOR  */
  YYSYMBOL_tNOT = 48,                      /* tNOT  */
  YYSYMBOL_tMOD = 49,                      /* tMOD  */
  YYSYMBOL_tAFTER = 50,                    /* tAFTER  */
  YYSYMBOL_tBEFORE = 51,                   /* tBEFORE  */
  YYSYMBOL_tCONCAT = 52,                   /* tCONCAT  */
  YYSYMBOL_tCONTAINS = 53,                 /* tCONTAINS  */
  YYSYMBOL_tSTARTS = 54,                   /* tSTARTS  */
  YYSYMBOL_tCHAR = 55,                     /* tCHAR  */
  YYSYMBOL_tCHARS = 56,                    /* tCHARS  */
  YYSYMBOL_tITEM = 57,                     /* tITEM  */
  YYSYMBOL_tITEMS = 58,                    /* tITEMS  */
  YYSYMBOL_tLINE = 59,                     /* tLINE  */
  YYSYMBOL_tLINES = 60,                    /* tLINES  */
  YYSYMBOL_tWORD = 61,                     /* tWORD  */
  YYSYMBOL_tWORDS = 62,                    /* tWORDS  */
  YYSYMBOL_tABBREVIATED = 63,              /* tABBREVIATED  */
  YYSYMBOL_tABBREV = 64,                   /* tABBREV  */
  YYSYMBOL_tABBR = 65,                     /* tABBR  */
  YYSYMBOL_tLONG = 66,                     /* tLONG  */
  YYSYMBOL_tSHORT = 67,                    /* tSHORT  */
  YYSYMBOL_tDATE = 68,                     /* tDATE  */
  YYSYMBOL_tLAST = 69,                     /* tLAST  */
  YYSYMBOL_tMENU = 70,                     /* tMENU  */
  YYSYMBOL_tMENUITEM = 71,                 /* tMENUITEM  */
  YYSYMBOL_tMENUITEMS = 72,                /* tMENUITEMS  */
  YYSYMBOL_tNUMBER = 73,                   /* tNUMBER  */
  YYSYMBOL_tTHE = 74,                      /* tTHE  */
  YYSYMBOL_tTIME = 75,                     /* tTIME  */
  YYSYMBOL_tSOUND = 76,                    /* tSOUND  */
  YYSYMBOL_tSPRITE = 77,                   /* tSPRITE  */
  YYSYMBOL_tINTERSECTS = 78,               /* tINTERSECTS  */
  YYSYMBOL_tWITHIN = 79,                   /* tWITHIN  */
  YYSYMBOL_tTELL = 80,                     /* tTELL  */
  YYSYMBOL_tPROPERTY = 81,                 /* tPROPERTY  */
  YYSYMBOL_tON = 82,                       /* tON  */
  YYSYMBOL_tMETHOD = 83,                   /* tMETHOD  */
  YYSYMBOL_tENDIF = 84,                    /* tENDIF  */
  YYSYMBOL_tENDREPEAT = 85,                /* tENDREPEAT  */
  YYSYMBOL_tENDTELL = 86,                  /* tENDTELL  */
  YYSYMBOL_tASSERTERROR = 87,              /* tASSERTERROR  */
  YYSYMBOL_88_ = 88,                       /* '<'  */
  YYSYMBOL_89_ = 89,                       /* '>'  */
  YYSYMBOL_90_ = 90,                       /* '&'  */
  YYSYMBOL_91_ = 91,                       /* '+'  */
  YYSYMBOL_92_ = 92,                       /* '-'  */
  YYSYMBOL_93_ = 93,                       /* '*'  */
  YYSYMBOL_94_ = 94,                       /* '/'  */
  YYSYMBOL_95_n_ = 95,                     /* '\n'  */
  YYSYMBOL_96_ = 96,                       /* ','  */
  YYSYMBOL_97_ = 97,                       /* '('  */
  YYSYMBOL_98_ = 98,                       /* ')'  */
  YYSYMBOL_99_ = 99,                       /* '['  */
  YYSYMBOL_100_ = 100,                     /* ']'  */
  YYSYMBOL_101_ = 101,                     /* ':'  */
  YYSYMBOL_YYACCEPT = 102,                 /* $accept  */
  YYSYMBOL_script = 103,                   /* script  */
  YYSYMBOL_scriptpartlist = 104,           /* scriptpartlist  */
  YYSYMBOL_scriptpart = 105,               /* scriptpart  */
  YYSYMBOL_macro = 106,                    /* macro  */
  YYSYMBOL_factory = 107,                  /* factory  */
  YYSYMBOL_method = 108,                   /* method  */
  YYSYMBOL_methodlist = 109,               /* methodlist  */
  YYSYMBOL_nonemptymethodlist = 110,       /* nonemptymethodlist  */
  YYSYMBOL_methodlistline = 111,           /* methodlistline  */
  YYSYMBOL_handler = 112,                  /* handler  */
  YYSYMBOL_endargdef = 113,                /* endargdef  */
  YYSYMBOL_CMDID = 114,                    /* CMDID  */
  YYSYMBOL_ID = 115,                       /* ID  */
  YYSYMBOL_idlist = 116,                   /* idlist  */
  YYSYMBOL_nonemptyidlist = 117,           /* nonemptyidlist  */
  YYSYMBOL_stmt = 118,                     /* stmt  */
  YYSYMBOL_stmt_insideif = 119,            /* stmt_insideif  */
  YYSYMBOL_stmtoneliner = 120,             /* stmtoneliner  */
  YYSYMBOL_proc = 121,                     /* proc  */
  YYSYMBOL_cmdargs = 122,                  /* cmdargs  */
  YYSYMBOL_trailingcomma = 123,            /* trailingcomma  */
  YYSYMBOL_frameargs = 124,                /* frameargs  */
  YYSYMBOL_asgn = 125,                     /* asgn  */
  YYSYMBOL_to = 126,                       /* to  */
  YYSYMBOL_definevars = 127,               /* definevars  */
  YYSYMBOL_ifstmt = 128,                   /* ifstmt  */
  YYSYMBOL_ifelsestmt = 129,               /* ifelsestmt  */
  YYSYMBOL_endif = 130,                    /* endif  */
  YYSYMBOL_loop = 131,                     /* loop  */
  YYSYMBOL_tell = 132,                     /* tell  */
  YYSYMBOL_when = 133,                     /* when  */
  YYSYMBOL_stmtlist = 134,                 /* stmtlist  */
  YYSYMBOL_nonemptystmtlist = 135,         /* nonemptystmtlist  */
  YYSYMBOL_stmtlistline = 136,             /* stmtlistline  */
  YYSYMBOL_stmtlist_insideif = 137,        /* stmtlist_insideif  */
  YYSYMBOL_nonemptystmtlist_insideif = 138, /* nonemptystmtlist_insideif  */
  YYSYMBOL_stmtlistline_insideif = 139,    /* stmtlistline_insideif  */
  YYSYMBOL_simpleexpr_nounarymath = 140,   /* simpleexpr_nounarymath  */
  YYSYMBOL_var = 141,                      /* var  */
  YYSYMBOL_varorchunk = 142,               /* varorchunk  */
  YYSYMBOL_varorthe = 143,                 /* varorthe  */
  YYSYMBOL_chunk = 144,                    /* chunk  */
  YYSYMBOL_chunktype = 145,                /* chunktype  */
  YYSYMBOL_object = 146,                   /* object  */
  YYSYMBOL_refargs = 147,                  /* refargs  */
  YYSYMBOL_the = 148,                      /* the  */
  YYSYMBOL_theobj = 149,                   /* theobj  */
  YYSYMBOL_menu = 150,                     /* menu  */
  YYSYMBOL_thedatetime = 151,              /* thedatetime  */
  YYSYMBOL_thenumberof = 152,              /* thenumberof  */
  YYSYMBOL_inof = 153,                     /* inof  */
  YYSYMBOL_writablethe = 154,              /* writablethe  */
  YYSYMBOL_writabletheobj = 155,           /* writabletheobj  */
  YYSYMBOL_list = 156,                     /* list  */
  YYSYMBOL_proplist = 157,                 /* proplist  */
  YYSYMBOL_proppair = 158,                 /* proppair  */
  YYSYMBOL_unarymath = 159,                /* unarymath  */
  YYSYMBOL_simpleexpr = 160,               /* simpleexpr  */
  YYSYMBOL_expr = 161,                     /* expr  */
  YYSYMBOL_expr_nounarymath = 162,         /* expr_nounarymath  */
  YYSYMBOL_expr_noeq = 163,                /* expr_noeq  */
  YYSYMBOL_sprite = 164,                   /* sprite  */
  YYSYMBOL_exprlist = 165,                 /* exprlist  */
  YYSYMBOL_nonemptyexprlist = 166          /* nonemptyexprlist  */
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
typedef yytype_int16 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  190
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4482

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  325
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  606

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
      95,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    90,     2,
      97,    98,    93,    91,    96,    92,     2,    94,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   101,     2,
      88,     2,    89,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    99,     2,   100,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   203,   209,   216,   217,   218,   219,   220,
     221,   250,   254,   256,   258,   259,   262,   268,   275,   276,
     281,   285,   289,   290,   291,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   374,   375,   376,
     379,   383,   393,   394,   397,   398,   399,   400,   401,   402,
     405,   406,   407,   410,   411,   412,   413,   414,   415,   416,
     417,   422,   423,   424,   425,   426,   427,   430,   433,   438,
     442,   448,   453,   456,   461,   467,   467,   473,   478,   484,
     490,   496,   504,   505,   506,   507,   510,   510,   512,   513,
     514,   517,   521,   525,   531,   535,   539,   543,   544,   546,
     548,   550,   552,   556,   560,   564,   566,   567,   571,   577,
     584,   585,   588,   589,   593,   599,   606,   607,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   628,   630,   631,   634,   635,   638,   639,   640,   642,
     644,   646,   648,   650,   652,   654,   656,   659,   660,   661,
     662,   665,   666,   669,   674,   677,   682,   688,   689,   690,
     691,   692,   695,   696,   697,   698,   699,   702,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   717,   718,
     719,   720,   721,   724,   724,   726,   727,   730,   731,   732,
     733,   734,   737,   738,   739,   742,   746,   751,   752,   753,
     756,   757,   760,   761,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   774,   775,   776,   777,   778,   779,   780,
     781,   782,   783,   790,   791,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   805,   806,
     807,   808,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   828,
     831,   832,   835,   836,   839,   843
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "tUNARY", "tINT", "tFLOAT",
  "tVARID", "tSTRING", "tSYMBOL", "tENDCLAUSE", "tCAST", "tFIELD",
  "tSCRIPT", "tWINDOW", "tDELETE", "tDOWN", "tELSE", "tEXIT", "tFRAME",
  "tGLOBAL", "tGO", "tHILITE", "tIF", "tIN", "tINTO", "tMACRO", "tMOVIE",
  "tNEXT", "tOF", "tPREVIOUS", "tPUT", "tREPEAT", "tSET", "tTHEN", "tTO",
  "tWHEN", "tWITH", "tWHILE", "tFACTORY", "tOPEN", "tPLAY", "tINSTANCE",
  "tGE", "tLE", "tEQ", "tNEQ", "tAND", "tOR", "tNOT", "tMOD", "tAFTER",
  "tBEFORE", "tCONCAT", "tCONTAINS", "tSTARTS", "tCHAR", "tCHARS", "tITEM",
  "tITEMS", "tLINE", "tLINES", "tWORD", "tWORDS", "tABBREVIATED",
  "tABBREV", "tABBR", "tLONG", "tSHORT", "tDATE", "tLAST", "tMENU",
  "tMENUITEM", "tMENUITEMS", "tNUMBER", "tTHE", "tTIME", "tSOUND",
  "tSPRITE", "tINTERSECTS", "tWITHIN", "tTELL", "tPROPERTY", "tON",
  "tMETHOD", "tENDIF", "tENDREPEAT", "tENDTELL", "tASSERTERROR", "'<'",
  "'>'", "'&'", "'+'", "'-'", "'*'", "'/'", "'\\n'", "','", "'('", "')'",
  "'['", "']'", "':'", "$accept", "script", "scriptpartlist", "scriptpart",
  "macro", "factory", "method", "methodlist", "nonemptymethodlist",
  "methodlistline", "handler", "endargdef", "CMDID", "ID", "idlist",
  "nonemptyidlist", "stmt", "stmt_insideif", "stmtoneliner", "proc",
  "cmdargs", "trailingcomma", "frameargs", "asgn", "to", "definevars",
  "ifstmt", "ifelsestmt", "endif", "loop", "tell", "when", "stmtlist",
  "nonemptystmtlist", "stmtlistline", "stmtlist_insideif",
  "nonemptystmtlist_insideif", "stmtlistline_insideif",
  "simpleexpr_nounarymath", "var", "varorchunk", "varorthe", "chunk",
  "chunktype", "object", "refargs", "the", "theobj", "menu", "thedatetime",
  "thenumberof", "inof", "writablethe", "writabletheobj", "list",
  "proplist", "proppair", "unarymath", "simpleexpr", "expr",
  "expr_nounarymath", "expr_noeq", "sprite", "exprlist",
  "nonemptyexprlist", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,    60,    62,
      38,    43,    45,    42,    47,    10,    44,    40,    41,    91,
      93,    58
};
#endif

#define YYPACT_NINF (-519)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2899,  -519,  3463,  -519,  -519,  -519,  -519,     4,  -519,   -13,
    -519,  3463,  1847,     4,  1943,  -519,  -519,  3463,  -519,     3,
    -519,  -519,  2039,    32,  3542,  -519,  -519,  -519,  -519,  3463,
    2039,  1847,  3463,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  1943,  3463,  3463,   -37,
    3778,  -519,    43,  2899,  -519,  -519,  -519,  -519,  2039,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,   -64,  -519,  -519,  2135,  2135,  1943,  1943,
    1943,  1943,     6,   -29,    25,  -519,  -519,    27,    34,  -519,
    -519,  -519,  -519,  2135,  2135,  2135,  2135,  1943,  1943,  2231,
    1943,  1943,  1943,  1943,  3621,  1943,  2231,  2231,  1367,   789,
       7,    33,    54,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,   887,  -519,    87,  1943,  3969,  3463,    93,
      94,   983,  3463,  1943,  3463,  -519,  -519,    -5,  -519,    97,
      98,  1079,   100,   102,   103,  3896,   110,  3463,  -519,  -519,
    -519,  -519,   116,  1175,  -519,  3463,  1463,  -519,  -519,  -519,
     370,   397,   540,   614,   153,  -519,  -519,  -519,  3463,  -519,
    -519,  1271,  4296,  -519,   -45,    48,    50,    65,    76,   153,
     115,   118,  4243,  -519,  -519,  -519,  3982,    55,   112,   119,
      75,    84,  -519,  4296,   120,   122,  1559,  -519,  -519,   189,
    1943,  1943,  1943,  1943,  2615,  2615,  2807,  1943,  2711,  2711,
    1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,  -519,  -519,
    4065,  -519,  -519,  4052,  2978,  1943,  1943,  1943,  1943,  1943,
     121,  -519,  -519,  3700,  3700,  3700,    39,  4078,   193,  -519,
    -519,  1943,   -43,  -519,  1943,  -519,  -519,  -519,  3778,  3057,
    -519,   127,  -519,  -519,  -519,  3995,  2231,  1943,  2231,  1943,
    2231,  1943,  2231,  1943,  -519,  -519,  -519,  -519,   124,  -519,
     199,  4309,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  2327,  2423,  2231,  2231,  1655,  -519,  1943,  1943,
    -519,  1943,  3384,  -519,  -519,  1943,  -519,   133,  1943,    15,
      15,    15,    15,  4375,  4375,  -519,    -7,    15,    15,    15,
      15,    -7,    61,    61,  -519,  -519,   133,  1943,  1943,  1943,
    1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,
    1943,  1943,  1943,  1943,  1943,  -519,  3294,   215,  3057,     6,
    -519,   137,  -519,   138,   156,  1943,  1943,  3057,  2519,  4132,
    3463,  -519,  -519,  -519,   -43,  -519,  4145,  -519,  -519,  -519,
     170,  3057,  -519,  3057,  1751,  -519,   683,  -519,  3830,  -519,
    3843,  -519,  3863,  -519,  -519,  2231,  1943,   124,   124,   124,
     124,  2231,  2231,   124,  2231,  2231,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,   133,  4296,  4296,  4296,    55,   112,   157,
    -519,  4296,  1943,   159,  4296,  -519,    15,    15,    15,    15,
    4375,  4375,  -519,    -7,    15,    15,    15,    15,    -7,    61,
      61,  -519,  -519,   133,  -519,  -519,    -3,  3294,  -519,  3136,
    -519,  -519,  -519,  -519,  4158,     2,   181,  1943,  1943,  1943,
    1943,  -519,  -519,  -519,  3463,  -519,  -519,   172,  -519,   259,
    -519,   133,  2231,  2231,  2231,  2231,  -519,  4296,  2231,  2231,
    2231,  2231,  -519,   244,   203,  -519,  -519,   176,  -519,  -519,
    3215,   182,  -519,  -519,  3294,  -519,  3057,   242,  1943,   184,
    -519,  4322,  -519,  3916,  4322,  4322,   185,  -519,  3463,   183,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,   216,  2231,
    -519,  -519,  3294,  -519,  -519,   201,   202,  1943,  4212,  -519,
    1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,  1943,
    1943,  1943,  1943,  1943,  1943,  1943,   220,  3057,    78,  -519,
    2231,   201,  -519,   197,  4225,  3057,    72,    72,    72,  4388,
    4388,  -519,     8,    72,    72,    72,    72,     8,    77,    77,
    -519,  -519,  1943,  -519,  -519,  -519,  -519,  -519,  3057,   209,
    4322,   211,   219,   223,  -519,  -519
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    25,    22,    32,    39,    63,    73,    37,    38,     0,
      40,    97,   127,    41,     0,    42,    44,     0,    55,    56,
      59,    61,   127,    62,     0,    71,   165,    74,    72,     0,
     127,   127,    97,    30,    60,    57,    54,    29,    31,    35,
      68,    33,    34,    45,    46,    48,    49,    76,    77,    26,
      27,    28,    50,    65,    36,    47,    51,    52,    53,    58,
      69,    70,    66,    67,    43,    75,     0,    97,     0,     0,
      64,     5,     0,     2,     3,     6,     7,     8,   127,     9,
     102,   104,   110,   111,   112,   105,   106,   107,   108,   109,
      80,    37,    79,    81,    83,    84,    41,    85,    87,    56,
      93,    62,    94,    96,    82,    90,    91,    86,    95,    92,
      89,    88,    64,     0,    78,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,   100,     0,    98,   178,
     179,   181,   180,    32,    39,    63,    73,    40,    55,    57,
      33,    45,    48,    76,    69,    67,     0,     0,     0,   322,
     191,     0,     0,   262,   186,   187,   188,   189,   220,   221,
     190,   263,   264,   135,   265,     0,     0,     0,    97,     0,
       0,   135,     0,     0,    69,   191,   194,     0,   195,     0,
       0,   135,     0,     0,     0,     0,     0,    97,   103,   126,
       1,     4,     0,   135,    10,     0,     0,   197,   213,   196,
       0,     0,     0,     0,     0,   124,   122,   148,    99,   211,
     212,   137,   138,   182,    26,    27,    28,    50,    65,    47,
      58,   217,     0,   260,   261,   132,     0,   181,   180,     0,
     191,     0,   255,   324,     0,   323,     0,   115,   116,    59,
       0,     0,     0,     0,    30,    60,    54,     0,    35,    68,
       0,     0,     0,     0,     0,     0,     0,   136,   128,   283,
     135,   284,   125,     0,     0,     0,     0,     0,     0,     0,
       0,   121,   114,    44,    29,    31,     0,     0,   245,   146,
     147,     0,    14,   119,    74,   117,   118,   150,     0,   166,
     149,     0,   113,    24,   214,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   207,   209,   210,   208,     0,   101,
      59,   141,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,     0,     0,     0,     0,     0,   185,     0,     0,
     253,     0,     0,   254,   252,     0,   183,   135,     0,   275,
     276,   273,   274,   277,   278,   270,   280,   281,   282,   272,
     271,   279,   266,   267,   268,   269,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   130,   172,   151,   166,    69,
     192,     0,   193,     0,     0,     0,     0,   166,     0,     0,
       0,    18,    19,    12,    15,    16,     0,   163,   170,   171,
       0,   167,   168,   166,     0,   198,     0,   202,     0,   204,
       0,   200,     0,   243,   244,     0,     0,    34,    46,    49,
      77,    51,    52,    53,    66,    67,   219,   223,   222,   218,
     320,   321,   133,   135,   259,   257,   258,     0,     0,     0,
     256,   325,   136,     0,   140,   129,   294,   295,   292,   293,
     296,   297,   289,   299,   300,   301,   291,   290,   298,   285,
     286,   287,   288,   135,   176,   177,   157,   173,   174,     0,
      11,   142,   143,   144,     0,     0,     0,    51,    52,    66,
      67,   246,   247,   145,    97,    17,   120,     0,   169,    21,
     215,   135,     0,     0,     0,     0,   206,   139,     0,     0,
       0,     0,   227,     0,     0,   225,   226,     0,   184,   131,
       0,     0,   152,   175,   172,   153,   166,     0,     0,     0,
     302,   248,   303,     0,   250,   251,     0,   164,    22,     0,
     199,   203,   205,   201,   238,   240,   241,   239,     0,     0,
     242,   134,   172,   155,   158,   157,     0,     0,     0,   159,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   166,     0,   216,
       0,   157,   154,     0,     0,   166,   312,   313,   311,   314,
     315,   308,   317,   318,   319,   310,   309,   316,   304,   305,
     306,   307,     0,    13,    20,   224,   156,   162,   166,     0,
     249,     0,     0,     0,   160,   161
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -519,  -519,  -519,   246,  -519,  -519,  -519,  -519,  -519,   -79,
    -519,  -208,     0,     9,   -30,  -519,     1,  -364,   -65,  -519,
      49,  -239,   290,  -519,  -519,  -519,  -519,  -519,  -518,  -519,
    -519,  -519,  -368,  -519,   -77,  -492,  -519,  -141,   -52,   -20,
    -186,  -519,    -4,  -519,  -519,    51,  -519,     5,  -177,  -519,
    -519,  -217,  -519,  -519,  -519,  -519,    -1,  -519,   200,    -6,
     126,  -252,    -2,  -519,  -229
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    72,    73,    74,    75,    76,   392,   393,   394,   395,
      77,   113,   114,   150,   127,   128,   399,    80,    81,    82,
     151,   258,   152,    83,   281,    84,    85,    86,   512,    87,
      88,    89,   400,   401,   402,   466,   467,   468,   153,   154,
     381,   177,   155,   308,   156,   197,   157,   426,   427,   158,
     159,   415,   178,   481,   160,   231,   232,   161,   162,   233,
     260,   521,   164,   234,   235
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    79,   184,   123,   176,   189,   163,   337,   167,   165,
     470,   115,   465,   510,   116,   117,   171,   517,   124,   476,
     126,   375,   545,   312,   181,   163,   168,   572,   356,   279,
     313,   194,   195,   175,   169,   489,   518,   186,   179,   280,
     390,   126,   267,   190,   240,   241,   242,   243,   265,   266,
     571,   267,   391,   596,   247,   268,   269,   555,   188,   118,
     185,   119,   385,   120,   267,   121,   205,   247,   172,   173,
      78,   170,   193,    78,    79,   204,   126,   187,   122,   180,
     182,   511,   125,   386,   253,   254,   255,   256,   383,   384,
     250,   251,   252,   253,   254,   255,   256,   433,   443,   562,
     563,   564,   565,   465,   236,   252,   253,   254,   255,   256,
     267,   259,   200,   201,   202,   203,   314,   445,   316,   259,
     206,   555,   207,   315,   556,   317,   555,   192,   237,   259,
     208,   211,   212,   318,   200,   201,   202,   203,   270,   222,
     319,   259,   226,   322,   320,   463,   323,   413,   546,   238,
     465,   321,   414,   221,   255,   256,   328,   291,   230,   259,
     263,   261,   561,   562,   563,   564,   565,   277,   199,   261,
     564,   565,   236,   594,   195,   491,   331,   126,   465,   261,
     332,   276,   262,   278,   333,   199,   209,   210,   271,   272,
     295,   261,   282,   283,   507,   285,   126,   286,   287,   593,
     498,   499,   500,   501,   293,   290,   504,   599,   304,   261,
     305,   292,   306,   329,   307,   338,   378,   309,   335,   330,
     334,   388,   403,   397,   509,   416,   523,   524,   525,   442,
     601,   469,   471,   472,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   473,   529,   380,   380,   380,   487,   508,   331,   343,
     344,   345,   347,   348,    78,   377,   519,   527,   528,   382,
     382,   382,   538,   539,   541,   389,   547,   544,   396,   549,
     567,   569,   175,   175,   175,   511,   570,   573,    78,    78,
     592,   406,   597,   408,   602,   410,   603,   412,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   604,   485,   198,   198,   605,   191,
     568,   183,   434,   435,   488,   436,   513,   540,   429,   441,
       0,   440,   444,   198,   198,   198,   198,   311,     0,   213,
     600,   439,     0,     0,     0,     0,   223,   224,     0,     0,
       0,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,    78,   474,
     475,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   296,   484,
       0,    78,     0,    78,   297,     0,     0,     0,     0,     0,
     497,     0,   240,   241,   242,   243,   265,   266,     0,   267,
       0,     0,   247,   268,   269,   298,     0,     0,     0,     0,
       0,   299,     0,     0,     0,     0,   441,     0,     0,   240,
     241,   242,   243,   265,   266,     0,   267,     0,     0,   247,
     268,   269,     0,     0,   526,     0,     0,     0,   250,   251,
     252,   253,   254,   255,   256,     0,     0,    78,     0,    78,
     515,     0,     0,     0,     0,   522,   522,   522,   522,     0,
       0,     0,     0,     0,     0,   250,   251,   252,   253,   254,
     255,   256,     0,   126,     0,     0,   405,     0,   407,     0,
     409,     0,   411,     0,     0,     0,     0,     0,     0,     0,
      78,   543,   548,     0,    78,     0,    78,     0,     0,     0,
       0,     0,   428,   428,   430,   431,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,     0,
       0,   574,    78,     0,     0,     0,     0,     0,   522,   522,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   522,   522,     0,     0,     0,    78,   300,     0,
       0,     0,     0,     0,   301,    78,     0,     0,     0,     0,
       0,     0,   240,   241,   242,   243,   265,   266,   482,   267,
     522,     0,   247,   268,   269,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   496,     0,     0,     0,     0,
       0,   502,   503,     0,   505,   506,     0,     0,   250,   251,
     252,   253,   254,   255,   256,     0,     0,     0,     0,     0,
       0,     0,   302,     0,     0,     0,     0,     0,   303,     0,
       0,     0,     0,     0,     0,     0,   240,   241,   242,   243,
     265,   266,     0,   267,     0,     0,   247,   268,   269,     0,
       0,     0,     0,     0,     0,     0,     0,   520,   520,   520,
     520,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   530,   531,   532,   533,     0,     0,   534,   535,
     536,   537,   250,   251,   252,   253,   254,   255,   256,     0,
       0,   492,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   240,   241,   242,   243,   265,
     266,     0,   267,     0,     0,   247,   268,   269,     0,   502,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     520,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,     0,     0,     0,     0,
     595,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,   129,   130,     1,   227,   228,    90,   133,
     134,   135,   136,    91,     8,    92,    93,    10,    94,    95,
      96,    97,    15,    16,    98,    18,    99,    20,    21,   100,
     101,   102,   103,    25,     0,    27,    28,   104,   105,   106,
     107,     0,     0,     0,     0,    33,    34,   139,    36,    37,
      38,     0,    39,    40,   140,    42,   141,    44,   142,    46,
     143,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,   144,    61,    62,   145,    64,    65,   108,
     109,   110,   111,     0,     0,     0,   112,     0,     0,     0,
     146,   147,     0,     0,     0,     0,   166,     0,   149,     0,
     229,   129,   130,     1,   131,   132,    90,   133,   134,   135,
     136,    91,     8,    92,    93,    10,    94,    95,    96,    97,
      15,    16,    98,    18,    99,   239,    21,   100,   101,   102,
     103,    25,     0,    27,    28,   104,   105,   106,   107,   240,
     241,   242,   243,   244,   245,   139,   246,    37,    38,   247,
     248,   249,   140,    42,   141,    44,   142,    46,   143,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   144,    61,    62,   145,    64,    65,   108,   109,   110,
     111,     0,     0,     0,   112,   250,   251,   252,   253,   254,
     255,   256,     0,   257,   166,     0,   149,   129,   130,     1,
     131,   132,    90,   133,   134,   135,   136,    91,     8,    92,
      93,    10,    94,    95,    96,    97,    15,   273,    98,    18,
      99,    20,    21,   100,   101,   102,   103,    25,     0,    27,
      28,   104,   105,   106,   107,   240,   241,   242,   243,   244,
     245,   139,   246,   274,   275,   247,   248,   249,   140,    42,
     141,    44,   142,    46,   143,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,   144,    61,    62,
     145,    64,    65,   108,   109,   110,   111,     0,     0,     0,
     112,   250,   251,   252,   253,   254,   255,   256,     0,   257,
     166,     0,   149,   129,   130,     1,   131,   132,    90,   133,
     134,   135,   136,    91,     8,    92,    93,    10,    94,    95,
      96,    97,    15,    16,    98,    18,    99,    20,    21,   100,
     101,   102,   103,    25,     0,   284,    28,   104,   105,   106,
     107,   240,   241,   242,   243,   244,   245,   139,   246,    37,
      38,   247,   248,   249,   140,    42,   141,    44,   142,    46,
     143,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,   144,    61,    62,   145,    64,    65,   108,
     109,   110,   111,     0,     0,     0,   112,   250,   251,   252,
     253,   254,   255,   256,     0,   257,   166,     0,   149,   129,
     130,     1,   131,   132,    90,   133,   134,   135,   136,    91,
       8,    92,    93,    10,    94,    95,    96,    97,    15,    16,
      98,    18,    99,    20,    21,   100,   101,   102,   103,    25,
       0,    27,    28,   104,   105,   106,   107,   240,   241,   242,
     243,   244,   245,   139,   246,    37,    38,   247,   248,   249,
     140,    42,   141,    44,   142,    46,   143,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,   144,
      61,    62,   145,    64,    65,   108,   109,   110,   111,     0,
       0,     0,   112,   250,   251,   252,   253,   254,   255,   256,
       0,   257,   166,     0,   149,   129,   130,     1,   131,   132,
      90,   133,   134,   135,   136,    91,     8,    92,    93,    10,
      94,    95,    96,    97,    15,    16,    98,    18,    99,   310,
      21,   100,   101,   102,   103,    25,     0,    27,    28,   104,
     105,   106,   107,   240,   241,   242,   243,   244,   245,   139,
     246,    37,    38,   247,   248,   249,   140,    42,   141,    44,
     142,    46,   143,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   144,    61,    62,   145,    64,
      65,   108,   109,   110,   111,     0,     0,     0,   112,   250,
     251,   252,   253,   254,   255,   256,     0,     0,   166,     0,
     149,   129,   130,     1,   131,   132,    90,   133,   134,   135,
     136,    91,     8,    92,    93,    10,    94,    95,    96,    97,
      15,    16,    98,    18,    99,    20,    21,   100,   101,   102,
     103,    25,     0,    27,    28,   104,   105,   106,   107,     0,
       0,     0,     0,    33,    34,   139,    36,    37,    38,     0,
      39,    40,   140,    42,   141,    44,   142,    46,   143,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   144,    61,    62,   145,    64,    65,   108,   109,   110,
     111,     0,     0,     0,   112,     0,     0,     0,   146,   147,
       0,     0,     0,     0,   166,   225,   149,   129,   130,     1,
     131,   132,    90,   133,   134,   135,   136,    91,     8,    92,
      93,    10,    94,    95,    96,    97,    15,    16,    98,    18,
      99,    20,    21,   100,   101,   102,   103,    25,     0,    27,
      28,   104,   105,   106,   107,     0,     0,     0,     0,    33,
      34,   139,    36,    37,    38,     0,    39,    40,   140,    42,
     141,    44,   142,    46,   143,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,   144,    61,    62,
     145,    64,    65,   108,   109,   110,   111,     0,     0,     0,
     112,     0,     0,     0,   146,   147,     0,     0,     0,     0,
     166,   294,   149,   129,   130,     1,   131,   132,    90,   133,
     134,   135,   136,    91,     8,    92,    93,    10,    94,    95,
      96,    97,    15,    16,    98,    18,    99,    20,    21,   100,
     101,   102,   103,    25,     0,    27,    28,   104,   105,   106,
     107,     0,     0,     0,     0,    33,    34,   139,    36,    37,
      38,     0,    39,    40,   140,    42,   141,    44,   142,    46,
     143,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,   144,    61,    62,   145,    64,    65,   108,
     109,   110,   111,     0,     0,     0,   112,     0,     0,     0,
     146,   147,     0,     0,     0,     0,   166,   336,   149,   129,
     130,     1,   131,   132,    90,   133,   134,   135,   136,    91,
       8,    92,    93,    10,    94,    95,    96,    97,    15,    16,
      98,    18,    99,    20,    21,   100,   101,   102,   103,    25,
       0,    27,    28,   104,   105,   106,   107,     0,     0,     0,
       0,    33,    34,   139,    36,    37,    38,     0,    39,    40,
     140,    42,   141,    44,   142,    46,   143,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,   144,
      61,    62,   145,    64,    65,   108,   109,   110,   111,     0,
       0,     0,   112,     0,     0,     0,   146,   147,     0,     0,
       0,     0,   166,   432,   149,   129,   130,     1,   131,   132,
      90,   133,   134,   135,   136,    91,     8,    92,    93,    10,
      94,    95,    96,    97,    15,    16,    98,    18,    99,    20,
      21,   100,   101,   102,   103,    25,     0,    27,    28,   104,
     105,   106,   107,     0,     0,     0,     0,    33,    34,   139,
      36,    37,    38,     0,    39,    40,   140,    42,   141,    44,
     142,    46,   143,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   144,    61,    62,   145,    64,
      65,   108,   109,   110,   111,     0,     0,     0,   112,     0,
       0,     0,   146,   147,     0,     0,     0,     0,   166,   490,
     149,   129,   130,     1,   131,   132,    90,   133,   134,   135,
     136,    91,     8,    92,    93,   137,    94,    95,    96,    97,
      15,    16,    98,   138,    99,    20,    21,   100,   101,   102,
     103,    25,     0,    27,    28,   104,   105,   106,   107,     0,
       0,     0,     0,    33,    34,   139,    36,    37,    38,     0,
      39,    40,   140,    42,   141,    44,   142,    46,   143,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   144,    61,    62,   145,    64,    65,   108,   109,   110,
     111,     0,     0,     0,   112,     0,     0,     0,   146,   147,
       0,     0,     0,     0,   148,     0,   149,   129,   130,     1,
     131,   132,    90,   133,   134,   135,   136,    91,     8,    92,
      93,    10,    94,    95,    96,    97,    15,    16,    98,    18,
      99,    20,    21,   100,   101,   102,   103,    25,     0,    27,
      28,   104,   105,   106,   107,     0,     0,     0,     0,    33,
      34,   139,    36,    37,    38,     0,    39,    40,   140,    42,
     141,    44,   142,    46,   143,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,   144,    61,    62,
     145,    64,    65,   108,   109,   110,   111,     0,     0,     0,
     112,     0,     0,     0,   146,   147,     0,     0,     0,     0,
     166,     0,   149,   129,   130,     1,   131,   132,    90,   133,
     134,   135,   136,    91,     8,    92,    93,    10,    94,    95,
      96,    97,    15,    16,    98,    18,    99,    20,    21,   100,
     101,   102,   103,    25,     0,    27,    28,   104,   105,   106,
     107,     0,     0,     0,     0,    33,    34,   139,    36,    37,
      38,     0,    39,    40,   140,    42,   141,    44,   142,    46,
     143,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,   144,    61,    62,   145,    64,    65,   108,
     109,   110,   111,     0,     0,     0,   112,     0,     0,     0,
     146,   147,     0,     0,     0,     0,   148,     0,   149,   129,
     130,     1,   131,   132,    90,   133,   134,   135,   136,    91,
       8,    92,    93,    10,    94,    95,    96,    97,    15,    16,
      98,    18,    99,    20,    21,   100,   101,   102,   103,    25,
       0,    27,    28,   104,   105,   106,   107,     0,     0,     0,
       0,    33,    34,   139,    36,    37,    38,     0,    39,    40,
     140,    42,   141,    44,   142,    46,   143,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,   144,
      61,    62,    63,    64,    65,   108,   109,   110,   111,     0,
       0,     0,   112,     0,     0,     0,   146,   147,     0,     0,
       0,     0,   196,     0,   149,   129,   130,     1,   131,   132,
      90,   133,   134,   135,   136,    91,     8,    92,    93,    10,
      94,    95,    96,    97,    15,    16,    98,    18,    99,    20,
      21,   100,   101,   102,   103,    25,     0,    27,    28,   104,
     105,   106,   107,     0,     0,     0,     0,    33,    34,   139,
      36,    37,    38,     0,    39,    40,   140,    42,   141,    44,
     142,    46,   143,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   144,    61,    62,    63,    64,
      65,   108,   109,   110,   111,     0,     0,     0,   112,     0,
       0,     0,   146,   147,     0,     0,     0,     0,   166,     0,
     149,   129,   130,     1,   131,   132,    90,   133,   134,   135,
     136,    91,     8,    92,    93,    10,    94,    95,    96,    97,
      15,    16,    98,    18,    99,    20,    21,   100,   101,   102,
     103,    25,     0,    27,    28,   104,   105,   106,   107,     0,
       0,     0,     0,    33,    34,   139,    36,    37,    38,     0,
      39,    40,   140,   417,   141,   418,   142,   419,   143,   420,
      49,    50,    51,    52,    53,    54,    55,   421,   422,   423,
      59,   144,    61,   424,   425,    64,    65,   108,   109,   110,
     111,     0,     0,     0,   112,     0,     0,     0,   146,   147,
       0,     0,     0,     0,   166,     0,   149,   129,   130,     1,
     131,   132,    90,   133,   134,   135,   136,    91,     8,    92,
      93,    10,    94,    95,    96,    97,    15,    16,    98,    18,
      99,    20,    21,   100,   101,   102,   103,    25,     0,    27,
      28,   104,   105,   106,   107,     0,     0,     0,     0,    33,
      34,   139,    36,    37,    38,     0,    39,    40,   140,    42,
     141,    44,   142,    46,   143,    48,    49,    50,    51,    52,
      53,    54,    55,   421,   422,    58,    59,   144,    61,   424,
     425,    64,    65,   108,   109,   110,   111,     0,     0,     0,
     112,     0,     0,     0,   146,   147,     0,     0,     0,     0,
     166,     0,   149,   129,   130,     1,   131,   132,    90,   133,
     134,   135,   136,    91,     8,    92,    93,    10,    94,    95,
      96,    97,    15,    16,    98,    18,    99,    20,    21,   100,
     101,   102,   103,    25,     0,    27,    28,   104,   105,   106,
     107,     0,     0,     0,     0,    33,    34,   139,    36,    37,
      38,     0,    39,    40,   140,    42,   141,    44,   142,    46,
     143,    48,    49,    50,    51,    52,    53,    54,    55,   477,
     478,    58,    59,   144,    61,   479,   480,    64,    65,   108,
     109,   110,   111,     0,     0,     0,   112,     0,     0,     0,
     146,   147,     0,     0,     0,     0,   166,     0,   149,   129,
     130,     1,   131,   132,    90,   133,   134,   135,   136,    91,
       8,    92,    93,    10,    94,    95,    96,    97,    15,    16,
      98,    18,    99,    20,    21,   100,   101,   102,   103,    25,
       0,    27,    28,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   139,    36,    37,    38,     0,    39,    40,
     140,    42,   141,    44,   142,    46,   143,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,   144,
      61,    62,   145,    64,    65,   108,   109,   110,   111,     0,
       0,     0,   112,     0,     0,     0,   146,   147,     0,     0,
       0,     0,   166,     0,   149,   129,   130,     1,   131,   132,
      90,   133,   134,   135,   136,    91,     8,    92,    93,    10,
      94,    95,    96,    97,    15,    16,    98,    18,    99,    20,
      21,   100,   101,   102,   103,    25,     0,    27,    28,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   139,
      36,    37,    38,     0,     0,     0,   140,    42,   141,    44,
     142,    46,   143,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   144,    61,    62,   145,    64,
      65,   108,   109,   110,   111,     0,     0,     0,   112,     0,
       0,     0,   146,   147,     0,     0,     0,     0,   166,     0,
     149,   129,   130,     1,   131,   132,    90,   133,   134,   135,
     136,    91,     8,    92,    93,    10,    94,    95,    96,    97,
      15,    16,    98,    18,    99,    20,    21,   100,   101,   102,
     103,    25,     0,    27,    28,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   139,     0,    37,    38,     0,
       0,     0,   140,    42,   141,    44,   142,    46,   143,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   144,    61,    62,   145,    64,    65,   108,   109,   110,
     111,     0,     0,     0,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   166,     1,   149,     0,     2,     3,
       4,     5,     6,     7,     8,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,     0,    69,     1,     0,    70,     0,     3,     4,
       5,     6,     7,     8,    71,     9,    10,    11,    12,    13,
      14,    15,    16,     0,    18,    19,    20,    21,    22,    23,
      24,     0,    25,    26,    27,    28,     0,    30,    31,    32,
       0,     0,     0,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    69,     1,     0,    70,     0,     3,     4,     5,
       6,     7,     8,   376,     9,    10,    11,    12,    13,    14,
      15,    16,     0,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,    30,    31,    32,     0,
       0,     0,     0,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,     0,
       0,    69,     1,     0,    70,     0,     3,     4,     5,     6,
       7,     8,   398,     9,    10,    11,    12,    13,    14,    15,
      16,     0,    18,    19,    20,    21,    22,    23,    24,     0,
      25,    26,    27,    28,     0,    30,    31,    32,     0,     0,
       0,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      69,     1,     0,    70,     0,     3,     4,     5,     6,     7,
       8,   514,     9,    10,    11,    12,    13,    14,    15,    16,
       0,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,    28,     0,    30,    31,    32,     0,     0,     0,
       0,    33,    34,    35,    36,    37,    38,     0,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,     0,    69,
       1,     0,    70,     0,     3,     4,     5,     6,     7,     8,
     542,     9,    10,    11,    12,    13,    14,    15,    16,     0,
      18,    19,    20,    21,    22,    23,    24,     0,    25,    26,
      27,    28,     0,    30,    31,    32,     0,     0,     0,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,   464,
       1,   437,   438,    90,     3,     4,     5,     6,    91,     8,
      92,    93,    10,    94,    95,    96,    97,    15,    16,    98,
      18,    99,    20,    21,   100,   101,   102,   103,    25,     0,
      27,    28,   104,   105,   106,   107,     0,     0,     0,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   108,   109,   110,   111,     0,     1,
       0,   112,    90,     3,     4,     5,     6,    91,     8,    92,
      93,    10,    94,    95,    96,    97,    15,    16,    98,    18,
      99,    20,    21,   100,   101,   102,   103,    25,     0,    27,
      28,   104,   105,   106,   107,     0,     0,     0,     0,    33,
      34,    35,    36,    37,    38,     0,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   108,   109,   110,   111,     0,     1,     0,
     112,    90,     3,     4,     5,     6,    91,     8,    92,    93,
      10,    94,    95,    96,    97,    15,    16,    98,    18,    99,
      20,    21,   100,   101,   102,   103,    25,     0,    27,    28,
     104,   105,   106,   107,     0,     0,     0,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,   174,    61,    62,    63,
      64,    65,   108,   109,   110,   111,     0,     1,     0,   112,
      90,     3,     4,     5,     6,    91,     8,    92,    93,    10,
      94,    95,    96,    97,    15,    16,    98,    18,    99,    20,
      21,   100,   101,   102,   103,    25,     0,    27,    28,   104,
     105,   106,   107,     0,     0,     0,     0,    33,    34,    35,
      36,    37,    38,     0,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,   214,   215,   216,   217,   218,    54,
     219,    56,    57,    58,   220,    60,    61,    62,    63,    64,
      65,   108,   109,   110,   111,     0,     1,     0,   112,    90,
     133,   134,     5,     6,    91,     8,    92,    93,    10,    94,
      95,    96,    97,    15,    16,    98,    18,    99,    20,    21,
     100,   101,   102,   103,    25,     0,    27,    28,   104,   105,
     106,   107,     0,     0,     0,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,   140,    42,   141,    44,   142,
      46,   143,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,   379,    61,    62,    63,    64,    65,
     108,   109,   110,   111,     1,     0,     0,   112,     3,     4,
       5,     6,     7,     8,     0,     9,    10,    11,    12,    13,
       0,    15,    16,     0,    18,    19,    20,    21,    22,   101,
      24,     0,    25,     0,    27,    28,     0,    30,    31,    32,
       0,     0,     0,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   493,    67,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,   494,   240,   241,   242,   243,   265,   266,     0,   267,
       0,     0,   247,   268,   269,   240,   241,   242,   243,   265,
     266,   495,   267,     0,     0,   247,   268,   269,     0,     0,
       0,     0,     0,     0,     0,   240,   241,   242,   243,   265,
     266,     0,   267,     0,     0,   247,   268,   269,   250,   251,
     252,   253,   254,   255,   256,     0,     0,     0,     0,     0,
     288,   250,   251,   252,   253,   254,   255,   256,   240,   241,
     242,   243,   265,   266,   566,   267,     0,     0,   247,   268,
     269,   250,   251,   252,   253,   254,   255,   256,   550,   551,
       0,   552,   553,   554,     0,   555,     0,     0,   556,   557,
     558,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,   253,   254,   255,
     256,   289,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   264,     0,   559,   560,   561,   562,   563,   564,
     565,   240,   241,   242,   243,   265,   266,     0,   267,     0,
       0,   247,   268,   269,   240,   241,   242,   243,   265,   266,
       0,   267,     0,     0,   247,   268,   269,   240,   241,   242,
     243,   265,   266,     0,   267,     0,     0,   247,   268,   269,
       0,     0,     0,     0,     0,     0,     0,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
     250,   251,   252,   253,   254,   255,   256,     0,   326,     0,
     327,     0,     0,   250,   251,   252,   253,   254,   255,   256,
       0,   404,     0,   327,   240,   241,   242,   243,   265,   266,
       0,   267,     0,     0,   247,   268,   269,   357,   358,   359,
     360,   361,   362,     0,   363,     0,     0,   364,   365,   366,
     240,   241,   242,   243,   265,   266,     0,   267,     0,     0,
     247,   268,   269,     0,     0,     0,     0,     0,     0,     0,
     250,   251,   252,   253,   254,   255,   256,     0,     0,     0,
     327,     0,     0,   367,   368,   369,   370,   371,   372,   373,
       0,   374,     0,     0,     0,     0,   250,   251,   252,   253,
     254,   255,   256,   387,   240,   241,   242,   243,   265,   266,
       0,   267,     0,     0,   247,   268,   269,   240,   241,   242,
     243,   265,   266,     0,   267,     0,     0,   247,   268,   269,
     240,   241,   242,   243,   265,   266,     0,   267,     0,     0,
     247,   268,   269,     0,     0,     0,     0,     0,     0,     0,
     250,   251,   252,   253,   254,   255,   256,   483,     0,     0,
       0,     0,     0,   250,   251,   252,   253,   254,   255,   256,
     486,     0,     0,     0,     0,     0,   250,   251,   252,   253,
     254,   255,   256,   516,   240,   241,   242,   243,   265,   266,
       0,   267,     0,     0,   247,   268,   269,   240,   241,   242,
     243,   265,   266,     0,   267,     0,     0,   247,   268,   269,
       0,     0,     0,     0,     0,   240,   241,   242,   243,   265,
     266,     0,   267,     0,     0,   247,   268,   269,     0,     0,
     250,   251,   252,   253,   254,   255,   256,   575,     0,     0,
       0,     0,     0,   250,   251,   252,   253,   254,   255,   256,
     598,   324,   325,     0,     0,     0,     0,     0,     0,     0,
       0,   250,   251,   252,   253,   254,   255,   256,   240,   241,
     242,   243,   265,   266,     0,   267,     0,     0,   247,   268,
     269,   357,   358,   359,   360,   361,   362,     0,   363,     0,
       0,   364,   365,   366,   550,   551,     0,   552,   553,   554,
       0,   555,     0,     0,   556,   557,   558,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,   253,   254,   255,
     256,     0,     0,     0,     0,     0,     0,   367,   368,   369,
     370,   371,   372,   373,     0,     0,     0,     0,     0,     0,
     559,   560,   561,   562,   563,   564,   565,   240,   241,   242,
     243,     0,     0,     0,   267,     0,     0,   247,   268,   269,
     550,   551,     0,   552,     0,     0,     0,   555,     0,     0,
     556,   557,   558,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   251,   252,   253,   254,   255,   256,
       0,     0,     0,     0,     0,     0,   559,   560,   561,   562,
     563,   564,   565
};

static const yytype_int16 yycheck[] =
{
       0,     0,    32,     7,    24,    70,    12,   236,    14,    13,
     378,     2,   376,    16,    10,    11,    22,    15,    31,   387,
      11,   260,   514,    68,    30,    31,    17,   545,   257,    34,
      75,    95,    96,    24,    31,   403,    34,    67,    29,    44,
      83,    32,    49,     0,    42,    43,    44,    45,    46,    47,
     542,    49,    95,   571,    52,    53,    54,    49,    95,    55,
      66,    57,    23,    59,    49,    61,    95,    52,    36,    37,
      70,    22,    78,    73,    73,    69,    67,    68,    74,    30,
      31,    84,    95,    44,    91,    92,    93,    94,   274,   275,
      88,    89,    90,    91,    92,    93,    94,   326,   337,    91,
      92,    93,    94,   467,    97,    90,    91,    92,    93,    94,
      49,   163,   118,   119,   120,   121,    68,   356,    68,   171,
      95,    49,    95,    75,    52,    75,    49,    78,    95,   181,
      96,   137,   138,    68,   140,   141,   142,   143,   168,   145,
      75,   193,   148,    28,    68,   374,    28,    23,   516,    95,
     514,    75,    28,   144,    93,    94,   101,   187,   149,   211,
     166,   163,    90,    91,    92,    93,    94,   173,   117,   171,
      93,    94,    97,    95,    96,   404,   101,   168,   542,   181,
      96,   172,    95,   174,   100,   134,   135,   136,    95,    95,
     196,   193,    95,    95,   433,    95,   187,    95,    95,   567,
     417,   418,   419,   420,   195,    95,   423,   575,    55,   211,
      57,    95,    59,   101,    61,    26,    95,   208,    96,   100,
     100,    28,    95,   288,   463,    26,   478,   479,   480,    96,
     598,    16,    95,    95,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,    95,   491,   273,   274,   275,    86,    98,   101,   265,
     266,   267,   268,   269,   264,   264,    85,    95,     9,   273,
     274,   275,    28,    70,    98,   281,    34,    95,   284,    95,
      95,    98,   273,   274,   275,    84,    70,    85,   288,   289,
      70,   297,    95,   299,    85,   301,    85,   303,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,    95,   394,   116,   117,    95,    73,
     528,    31,   328,   329,   401,   331,   467,   504,   323,   335,
      -1,   332,   338,   133,   134,   135,   136,   211,    -1,   139,
     592,   332,    -1,    -1,    -1,    -1,   146,   147,    -1,    -1,
      -1,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,   378,   385,
     386,    -1,    -1,    -1,    -1,    -1,    -1,   387,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,   390,
      -1,   401,    -1,   403,    34,    -1,    -1,    -1,    -1,    -1,
     416,    -1,    42,    43,    44,    45,    46,    47,    -1,    49,
      -1,    -1,    52,    53,    54,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,   442,    -1,    -1,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    52,
      53,    54,    -1,    -1,   484,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,   467,    -1,   469,
     469,    -1,    -1,    -1,    -1,   477,   478,   479,   480,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    -1,   484,    -1,    -1,   296,    -1,   298,    -1,
     300,    -1,   302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     510,   510,   518,    -1,   514,    -1,   516,    -1,    -1,    -1,
      -1,    -1,   322,   323,   324,   325,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,    -1,    -1,
      -1,   547,   542,    -1,    -1,    -1,    -1,    -1,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,    -1,    -1,    -1,   567,    28,    -1,
      -1,    -1,    -1,    -1,    34,   575,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,   388,    49,
     592,    -1,    52,    53,    54,    -1,    -1,    -1,   598,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   415,    -1,    -1,    -1,    -1,
      -1,   421,   422,    -1,   424,   425,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   477,   478,   479,
     480,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   492,   493,   494,   495,    -1,    -1,   498,   499,
     500,   501,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    54,    -1,   539,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,    -1,    -1,    -1,    -1,
     570,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   592,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,
     101,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    96,    97,    -1,    99,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    93,    94,    -1,    96,
      97,    -1,    99,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    88,    89,    90,
      91,    92,    93,    94,    -1,    96,    97,    -1,    99,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    96,    97,    -1,    99,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    -1,    97,    -1,
      99,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    -1,    -1,    -1,    91,    92,
      -1,    -1,    -1,    -1,    97,    98,    99,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,
      97,    98,    99,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    97,    98,    99,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    91,    92,    -1,    -1,
      -1,    -1,    97,    98,    99,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    97,    98,
      99,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    -1,    -1,    -1,    91,    92,
      -1,    -1,    -1,    -1,    97,    -1,    99,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,
      97,    -1,    99,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    97,    -1,    99,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    91,    92,    -1,    -1,
      -1,    -1,    97,    -1,    99,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    97,    -1,
      99,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    -1,    -1,    -1,    91,    92,
      -1,    -1,    -1,    -1,    97,    -1,    99,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,
      97,    -1,    99,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    97,    -1,    99,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    91,    92,    -1,    -1,
      -1,    -1,    97,    -1,    99,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    97,    -1,
      99,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    97,     6,    99,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    84,     6,    -1,    87,    -1,    10,    11,
      12,    13,    14,    15,    95,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,     6,    -1,    87,    -1,    10,    11,    12,
      13,    14,    15,    95,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    84,     6,    -1,    87,    -1,    10,    11,    12,    13,
      14,    15,    95,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    -1,    39,    40,    41,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      84,     6,    -1,    87,    -1,    10,    11,    12,    13,    14,
      15,    95,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    -1,    84,
       6,    -1,    87,    -1,    10,    11,    12,    13,    14,    15,
      95,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,     6,
      -1,    87,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,     6,    -1,
      87,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,     6,    -1,    87,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,     6,    -1,    87,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     6,    -1,    -1,    87,    10,    11,
      12,    13,    14,    15,    -1,    17,    18,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    -1,    36,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    28,    81,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    28,    42,    43,    44,    45,    46,    47,    -1,    49,
      -1,    -1,    52,    53,    54,    42,    43,    44,    45,    46,
      47,    28,    49,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    54,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
      34,    88,    89,    90,    91,    92,    93,    94,    42,    43,
      44,    45,    46,    47,    28,    49,    -1,    -1,    52,    53,
      54,    88,    89,    90,    91,    92,    93,    94,    42,    43,
      -1,    45,    46,    47,    -1,    49,    -1,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    88,    89,    90,    91,    92,    93,
      94,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    52,    53,    54,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    -1,    96,    -1,
      98,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      -1,    96,    -1,    98,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    52,    53,    54,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      98,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      -1,    96,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    52,    53,    54,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    54,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,    52,    53,
      54,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    52,    53,    54,    42,    43,    -1,    45,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    42,    43,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    52,    53,    54,
      42,    43,    -1,    45,    -1,    -1,    -1,    49,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    10,    11,    12,    13,    14,    15,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    34,    35,    36,    37,    38,
      39,    40,    41,    46,    47,    48,    49,    50,    51,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      87,    95,   103,   104,   105,   106,   107,   112,   114,   118,
     119,   120,   121,   125,   127,   128,   129,   131,   132,   133,
       9,    14,    16,    17,    19,    20,    21,    22,    25,    27,
      30,    31,    32,    33,    38,    39,    40,    41,    80,    81,
      82,    83,    87,   113,   114,   115,    10,    11,    55,    57,
      59,    61,    74,   144,    31,    95,   115,   116,   117,     4,
       5,     7,     8,    10,    11,    12,    13,    18,    26,    48,
      55,    57,    59,    61,    74,    77,    91,    92,    97,    99,
     115,   122,   124,   140,   141,   144,   146,   148,   151,   152,
     156,   159,   160,   161,   164,   144,    97,   161,   115,    31,
     122,   161,    36,    37,    74,   115,   141,   143,   154,   115,
     122,   161,   122,   124,   116,   161,   116,   115,    95,   120,
       0,   105,   122,   161,    95,    96,    97,   147,   160,   147,
     161,   161,   161,   161,    69,    95,    95,    95,    96,   147,
     147,   161,   161,   160,    63,    64,    65,    66,    67,    69,
      73,   115,   161,   160,   160,    98,   161,     7,     8,   101,
     115,   157,   158,   161,   165,   166,    97,    95,    95,    28,
      42,    43,    44,    45,    46,    47,    49,    52,    53,    54,
      88,    89,    90,    91,    92,    93,    94,    96,   123,   140,
     162,   164,    95,   161,    33,    46,    47,    49,    53,    54,
     116,    95,    95,    24,    50,    51,   115,   161,   115,    34,
      44,   126,    95,    95,    36,    95,    95,    95,    34,    95,
      95,   116,    95,   115,    98,   161,    28,    34,    28,    34,
      28,    34,    28,    34,    55,    57,    59,    61,   145,   115,
      28,   162,    68,    75,    68,    75,    68,    75,    68,    75,
      68,    75,    28,    28,    78,    79,    96,    98,   101,   101,
     100,   101,    96,   100,   100,    96,    98,   166,    26,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   166,    42,    43,    44,
      45,    46,    47,    49,    52,    53,    54,    88,    89,    90,
      91,    92,    93,    94,    96,   123,    95,   118,    95,    74,
     141,   142,   144,   142,   142,    23,    44,    95,    28,   161,
      83,    95,   108,   109,   110,   111,   161,   120,    95,   118,
     134,   135,   136,    95,    96,   160,   161,   160,   161,   160,
     161,   160,   161,    23,    28,   153,    26,    56,    58,    60,
      62,    70,    71,    72,    76,    77,   149,   150,   160,   149,
     160,   160,    98,   166,   161,   161,   161,     7,     8,   115,
     158,   161,    96,   123,   161,   123,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   166,    95,   119,   137,   138,   139,    16,
     134,    95,    95,    95,   161,   161,   134,    70,    71,    76,
      77,   155,   160,    95,   115,   111,    95,    86,   136,   134,
      98,   166,    28,    28,    28,    28,   160,   161,   153,   153,
     153,   153,   160,   160,   153,   160,   160,   123,    98,   123,
      16,    84,   130,   139,    95,   118,    95,    15,    34,    85,
     160,   163,   164,   163,   163,   163,   116,    95,     9,   123,
     160,   160,   160,   160,   160,   160,   160,   160,    28,    70,
     150,    98,    95,   118,    95,   137,   134,    34,   161,    95,
      42,    43,    45,    46,    47,    49,    52,    53,    54,    88,
      89,    90,    91,    92,    93,    94,    28,    95,   113,    98,
      70,   137,   130,    85,   161,    95,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,    70,   134,    95,   160,   130,    95,    95,   134,
     163,   134,    85,    85,    95,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   106,   107,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     120,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   124,
     124,   124,   125,   125,   125,   125,   126,   126,   127,   127,
     127,   128,   128,   129,   129,   129,   129,   130,   130,   131,
     131,   131,   131,   132,   132,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   142,   142,   143,   143,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   145,   145,   145,
     145,   146,   146,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   150,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   152,   152,
     152,   152,   152,   153,   153,   154,   154,   155,   155,   155,
     155,   155,   156,   156,   156,   157,   157,   158,   158,   158,
     159,   159,   160,   160,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     164,   164,   165,   165,   166,   166
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     5,     4,     5,     0,     1,     1,     2,     1,     1,
       8,     5,     0,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     2,
       1,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       5,     3,     3,     2,     3,     3,     2,     0,     2,     4,
       3,     5,     2,     4,     6,     0,     1,     2,     2,     5,
       4,     3,     5,     5,     5,     5,     1,     1,     3,     3,
       3,     4,     6,     6,     8,     7,     9,     0,     2,     7,
      11,    12,     9,     4,     6,     1,     0,     1,     1,     2,
       1,     1,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     2,     3,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     6,
       4,     6,     4,     6,     4,     6,     5,     1,     1,     1,
       1,     2,     2,     1,     2,     4,     6,     2,     4,     4,
       1,     1,     1,     1,     5,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     6,
       6,     6,     6,     1,     1,     2,     4,     1,     2,     5,
       2,     2,     3,     3,     3,     1,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     4,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}



/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx);

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
  switch (yykind)
    {
    case YYSYMBOL_tVARID: /* tVARID  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2305 "engines/director/lingo/lingo-gr.cpp"
        break;

    case YYSYMBOL_tSTRING: /* tSTRING  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2311 "engines/director/lingo/lingo-gr.cpp"
        break;

    case YYSYMBOL_tSYMBOL: /* tSYMBOL  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2317 "engines/director/lingo/lingo-gr.cpp"
        break;

    case YYSYMBOL_tENDCLAUSE: /* tENDCLAUSE  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2323 "engines/director/lingo/lingo-gr.cpp"
        break;

    case YYSYMBOL_CMDID: /* CMDID  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2329 "engines/director/lingo/lingo-gr.cpp"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 195 "engines/director/lingo/lingo-gr.y"
            { delete ((*yyvaluep).s); }
#line 2335 "engines/director/lingo/lingo-gr.cpp"
        break;

      default:
        break;
    }
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
  case 2: /* script: scriptpartlist  */
#line 201 "engines/director/lingo/lingo-gr.y"
                                                        { g_lingo->_compiler->_assemblyAST = new ScriptNode((yyvsp[0].nodelist)); }
#line 2603 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 3: /* scriptpartlist: scriptpart  */
#line 203 "engines/director/lingo/lingo-gr.y"
                                                                {
		NodeList *list = new NodeList;
		if ((yyvsp[0].node)) {
			list->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = list; }
#line 2614 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 4: /* scriptpartlist: scriptpartlist scriptpart  */
#line 209 "engines/director/lingo/lingo-gr.y"
                                                        {
		if ((yyvsp[0].node)) {
			(yyvsp[-1].nodelist)->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 2624 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 5: /* scriptpart: '\n'  */
#line 216 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = nullptr; }
#line 2630 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 10: /* scriptpart: tENDCLAUSE endargdef '\n'  */
#line 221 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = nullptr; delete (yyvsp[-2].s); }
#line 2636 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 11: /* macro: tMACRO ID idlist '\n' stmtlist  */
#line 250 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new HandlerNode((yyvsp[-3].s), (yyvsp[-2].idlist), (yyvsp[0].nodelist)); }
#line 2642 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 12: /* factory: tFACTORY ID '\n' methodlist  */
#line 254 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new FactoryNode((yyvsp[-2].s), (yyvsp[0].nodelist)); }
#line 2648 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 13: /* method: tMETHOD ID idlist '\n' stmtlist  */
#line 256 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new HandlerNode((yyvsp[-3].s), (yyvsp[-2].idlist), (yyvsp[0].nodelist)); }
#line 2654 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 14: /* methodlist: %empty  */
#line 258 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.nodelist) = new NodeList; }
#line 2660 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 16: /* nonemptymethodlist: methodlistline  */
#line 262 "engines/director/lingo/lingo-gr.y"
                                                                {
		NodeList *list = new NodeList;
		if ((yyvsp[0].node)) {
			list->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = list; }
#line 2671 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 17: /* nonemptymethodlist: nonemptymethodlist methodlistline  */
#line 268 "engines/director/lingo/lingo-gr.y"
                                                        {
		if ((yyvsp[0].node)) {
			(yyvsp[-1].nodelist)->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 2681 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 18: /* methodlistline: '\n'  */
#line 275 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = nullptr; }
#line 2687 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 20: /* handler: tON ID idlist '\n' stmtlist tENDCLAUSE endargdef '\n'  */
#line 281 "engines/director/lingo/lingo-gr.y"
                                                               {	// D3
		(yyval.node) = new HandlerNode((yyvsp[-6].s), (yyvsp[-5].idlist), (yyvsp[-3].nodelist));
		checkEnd((yyvsp[-2].s), (yyvsp[-6].s), false);
		delete (yyvsp[-2].s); }
#line 2696 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 21: /* handler: tON ID idlist '\n' stmtlist  */
#line 285 "engines/director/lingo/lingo-gr.y"
                                      {	// D4. No 'end' clause
		(yyval.node) = new HandlerNode((yyvsp[-3].s), (yyvsp[-2].idlist), (yyvsp[0].nodelist)); }
#line 2703 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 23: /* endargdef: ID  */
#line 290 "engines/director/lingo/lingo-gr.y"
                                                        { delete (yyvsp[0].s); }
#line 2709 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 24: /* endargdef: endargdef ',' ID  */
#line 291 "engines/director/lingo/lingo-gr.y"
                                                { delete (yyvsp[0].s); }
#line 2715 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 26: /* CMDID: tABBREVIATED  */
#line 299 "engines/director/lingo/lingo-gr.y"
                        { (yyval.s) = new Common::String("abbreviated"); }
#line 2721 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 27: /* CMDID: tABBREV  */
#line 300 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("abbrev"); }
#line 2727 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 28: /* CMDID: tABBR  */
#line 301 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("abbr"); }
#line 2733 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 29: /* CMDID: tAFTER  */
#line 302 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("after"); }
#line 2739 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 30: /* CMDID: tAND  */
#line 303 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("and"); }
#line 2745 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 31: /* CMDID: tBEFORE  */
#line 304 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("before"); }
#line 2751 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 32: /* CMDID: tCAST  */
#line 305 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("cast"); }
#line 2757 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 33: /* CMDID: tCHAR  */
#line 306 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("char"); }
#line 2763 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 34: /* CMDID: tCHARS  */
#line 307 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("chars"); }
#line 2769 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 35: /* CMDID: tCONTAINS  */
#line 308 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("contains"); }
#line 2775 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 36: /* CMDID: tDATE  */
#line 309 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("date"); }
#line 2781 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 37: /* CMDID: tDELETE  */
#line 310 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("delete"); }
#line 2787 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 38: /* CMDID: tDOWN  */
#line 311 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("down"); }
#line 2793 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 39: /* CMDID: tFIELD  */
#line 312 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("field"); }
#line 2799 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 40: /* CMDID: tFRAME  */
#line 313 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("frame"); }
#line 2805 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 41: /* CMDID: tHILITE  */
#line 314 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("hilite"); }
#line 2811 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 42: /* CMDID: tIN  */
#line 315 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("in"); }
#line 2817 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 43: /* CMDID: tINTERSECTS  */
#line 316 "engines/director/lingo/lingo-gr.y"
                        { (yyval.s) = new Common::String("intersects"); }
#line 2823 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 44: /* CMDID: tINTO  */
#line 317 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("into"); }
#line 2829 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 45: /* CMDID: tITEM  */
#line 318 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("item"); }
#line 2835 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 46: /* CMDID: tITEMS  */
#line 319 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("items"); }
#line 2841 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 47: /* CMDID: tLAST  */
#line 320 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("last"); }
#line 2847 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 48: /* CMDID: tLINE  */
#line 321 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("line"); }
#line 2853 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 49: /* CMDID: tLINES  */
#line 322 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("lines"); }
#line 2859 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 50: /* CMDID: tLONG  */
#line 323 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("long"); }
#line 2865 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 51: /* CMDID: tMENU  */
#line 324 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("menu"); }
#line 2871 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 52: /* CMDID: tMENUITEM  */
#line 325 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("menuItem"); }
#line 2877 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 53: /* CMDID: tMENUITEMS  */
#line 326 "engines/director/lingo/lingo-gr.y"
                        { (yyval.s) = new Common::String("menuItems"); }
#line 2883 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 54: /* CMDID: tMOD  */
#line 327 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("mod"); }
#line 2889 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 55: /* CMDID: tMOVIE  */
#line 328 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("movie"); }
#line 2895 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 56: /* CMDID: tNEXT  */
#line 329 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("next"); }
#line 2901 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 57: /* CMDID: tNOT  */
#line 330 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("not"); }
#line 2907 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 58: /* CMDID: tNUMBER  */
#line 331 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("number"); }
#line 2913 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 59: /* CMDID: tOF  */
#line 332 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("of"); }
#line 2919 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 60: /* CMDID: tOR  */
#line 333 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("or"); }
#line 2925 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 61: /* CMDID: tPREVIOUS  */
#line 334 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("previous"); }
#line 2931 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 62: /* CMDID: tREPEAT  */
#line 335 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("repeat"); }
#line 2937 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 63: /* CMDID: tSCRIPT  */
#line 336 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("script"); }
#line 2943 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 64: /* CMDID: tASSERTERROR  */
#line 337 "engines/director/lingo/lingo-gr.y"
                        { (yyval.s) = new Common::String("scummvmAssertError"); }
#line 2949 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 65: /* CMDID: tSHORT  */
#line 338 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("short"); }
#line 2955 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 66: /* CMDID: tSOUND  */
#line 339 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("sound"); }
#line 2961 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 67: /* CMDID: tSPRITE  */
#line 340 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("sprite"); }
#line 2967 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 68: /* CMDID: tSTARTS  */
#line 341 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("starts"); }
#line 2973 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 69: /* CMDID: tTHE  */
#line 342 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("the"); }
#line 2979 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 70: /* CMDID: tTIME  */
#line 343 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("time"); }
#line 2985 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 71: /* CMDID: tTO  */
#line 344 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("to"); }
#line 2991 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 72: /* CMDID: tWHILE  */
#line 345 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("while"); }
#line 2997 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 73: /* CMDID: tWINDOW  */
#line 346 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("window"); }
#line 3003 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 74: /* CMDID: tWITH  */
#line 347 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("with"); }
#line 3009 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 75: /* CMDID: tWITHIN  */
#line 348 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("within"); }
#line 3015 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 76: /* CMDID: tWORD  */
#line 349 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("word"); }
#line 3021 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 77: /* CMDID: tWORDS  */
#line 350 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("words"); }
#line 3027 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 79: /* ID: tELSE  */
#line 354 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("else"); }
#line 3033 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 80: /* ID: tENDCLAUSE  */
#line 355 "engines/director/lingo/lingo-gr.y"
                        { (yyval.s) = new Common::String("end"); }
#line 3039 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 81: /* ID: tEXIT  */
#line 356 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("exit"); }
#line 3045 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 82: /* ID: tFACTORY  */
#line 357 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("factory"); }
#line 3051 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 83: /* ID: tGLOBAL  */
#line 358 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("global"); }
#line 3057 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 84: /* ID: tGO  */
#line 359 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("go"); }
#line 3063 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 85: /* ID: tIF  */
#line 360 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("if"); }
#line 3069 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 86: /* ID: tINSTANCE  */
#line 361 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("instance"); }
#line 3075 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 87: /* ID: tMACRO  */
#line 362 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("macro"); }
#line 3081 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 88: /* ID: tMETHOD  */
#line 363 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("method"); }
#line 3087 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 89: /* ID: tON  */
#line 364 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("on"); }
#line 3093 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 90: /* ID: tOPEN  */
#line 365 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("open"); }
#line 3099 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 91: /* ID: tPLAY  */
#line 366 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("play"); }
#line 3105 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 92: /* ID: tPROPERTY  */
#line 367 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("property"); }
#line 3111 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 93: /* ID: tPUT  */
#line 368 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("put"); }
#line 3117 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 94: /* ID: tSET  */
#line 369 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("set"); }
#line 3123 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 95: /* ID: tTELL  */
#line 370 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("tell"); }
#line 3129 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 96: /* ID: tTHEN  */
#line 371 "engines/director/lingo/lingo-gr.y"
                                { (yyval.s) = new Common::String("then"); }
#line 3135 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 97: /* idlist: %empty  */
#line 374 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.idlist) = new IDList; }
#line 3141 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 100: /* nonemptyidlist: ID  */
#line 379 "engines/director/lingo/lingo-gr.y"
                                                                {
		Common::Array<Common::String *> *list = new IDList;
		list->push_back((yyvsp[0].s));
		(yyval.idlist) = list; }
#line 3150 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 101: /* nonemptyidlist: nonemptyidlist ',' ID  */
#line 383 "engines/director/lingo/lingo-gr.y"
                                                        {
		(yyvsp[-2].idlist)->push_back((yyvsp[0].s));
		(yyval.idlist) = (yyvsp[-2].idlist); }
#line 3158 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 103: /* stmt: tENDIF '\n'  */
#line 394 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = nullptr; }
#line 3164 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 113: /* proc: CMDID cmdargs '\n'  */
#line 410 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new CmdNode((yyvsp[-2].s), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3170 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 114: /* proc: tPUT cmdargs '\n'  */
#line 411 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new CmdNode(new Common::String("put"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3176 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 115: /* proc: tGO cmdargs '\n'  */
#line 412 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new CmdNode(new Common::String("go"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3182 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 116: /* proc: tGO frameargs '\n'  */
#line 413 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new CmdNode(new Common::String("go"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3188 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 117: /* proc: tPLAY cmdargs '\n'  */
#line 414 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new CmdNode(new Common::String("play"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3194 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 118: /* proc: tPLAY frameargs '\n'  */
#line 415 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new CmdNode(new Common::String("play"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3200 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 119: /* proc: tOPEN cmdargs '\n'  */
#line 416 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new CmdNode(new Common::String("open"), (yyvsp[-1].nodelist), g_lingo->_compiler->_linenumber - 1); }
#line 3206 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 120: /* proc: tOPEN expr tWITH expr '\n'  */
#line 417 "engines/director/lingo/lingo-gr.y"
                                                 {
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-3].node));
		args->push_back((yyvsp[-1].node));
		(yyval.node) = new CmdNode(new Common::String("open"), args, g_lingo->_compiler->_linenumber - 1); }
#line 3216 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 121: /* proc: tNEXT tREPEAT '\n'  */
#line 422 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new NextRepeatNode(); }
#line 3222 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 122: /* proc: tEXIT tREPEAT '\n'  */
#line 423 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new ExitRepeatNode(); }
#line 3228 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 123: /* proc: tEXIT '\n'  */
#line 424 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new ExitNode(); }
#line 3234 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 124: /* proc: tDELETE chunk '\n'  */
#line 425 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new DeleteNode((yyvsp[-1].node)); }
#line 3240 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 125: /* proc: tHILITE chunk '\n'  */
#line 426 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new HiliteNode((yyvsp[-1].node)); }
#line 3246 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 126: /* proc: tASSERTERROR stmtoneliner  */
#line 427 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new AssertErrorNode((yyvsp[0].node)); }
#line 3252 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 127: /* cmdargs: %empty  */
#line 430 "engines/director/lingo/lingo-gr.y"
                                                                                        {
		// This matches `cmd`
		(yyval.nodelist) = new NodeList; }
#line 3260 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 128: /* cmdargs: expr trailingcomma  */
#line 433 "engines/director/lingo/lingo-gr.y"
                                                                                        {
		// This matches `cmd arg` and `cmd(arg)`
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-1].node));
		(yyval.nodelist) = args; }
#line 3270 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 129: /* cmdargs: expr ',' nonemptyexprlist trailingcomma  */
#line 438 "engines/director/lingo/lingo-gr.y"
                                                                {
		// This matches `cmd args, ...)
		(yyvsp[-1].nodelist)->insert_at(0, (yyvsp[-3].node));
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 3279 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 130: /* cmdargs: expr expr_nounarymath trailingcomma  */
#line 442 "engines/director/lingo/lingo-gr.y"
                                                                        {
		// This matches `cmd arg arg`
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-2].node));
		args->push_back((yyvsp[-1].node));
		(yyval.nodelist) = args; }
#line 3290 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 131: /* cmdargs: expr expr_nounarymath ',' nonemptyexprlist trailingcomma  */
#line 448 "engines/director/lingo/lingo-gr.y"
                                                                                {
		// This matches `cmd arg arg, ...`
		(yyvsp[-1].nodelist)->insert_at(0, (yyvsp[-3].node));
		(yyvsp[-1].nodelist)->insert_at(0, (yyvsp[-4].node));
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 3300 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 132: /* cmdargs: '(' ')'  */
#line 453 "engines/director/lingo/lingo-gr.y"
                                                                        {
		// This matches `cmd()`
		(yyval.nodelist) = new NodeList; }
#line 3308 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 133: /* cmdargs: '(' expr ',' ')'  */
#line 456 "engines/director/lingo/lingo-gr.y"
                           {
		// This matches `cmd(args,)`
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-2].node));
		(yyval.nodelist) = args; }
#line 3318 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 134: /* cmdargs: '(' expr ',' nonemptyexprlist trailingcomma ')'  */
#line 461 "engines/director/lingo/lingo-gr.y"
                                                                {
		// This matches `cmd(args, ...)`
		(yyvsp[-2].nodelist)->insert_at(0, (yyvsp[-4].node));
		(yyval.nodelist) = (yyvsp[-2].nodelist); }
#line 3327 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 137: /* frameargs: tFRAME expr  */
#line 473 "engines/director/lingo/lingo-gr.y"
                                                                        {
		// This matches `play frame arg`
		NodeList *args = new NodeList;
		args->push_back(new FrameNode((yyvsp[0].node)));
		(yyval.nodelist) = args; }
#line 3337 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 138: /* frameargs: tMOVIE expr  */
#line 478 "engines/director/lingo/lingo-gr.y"
                                                                                {
		// This matches `play movie arg`
		NodeList *args = new NodeList;
		args->push_back(new IntNode(1));
		args->push_back(new MovieNode((yyvsp[0].node)));
		(yyval.nodelist) = args; }
#line 3348 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 139: /* frameargs: tFRAME expr tOF tMOVIE expr  */
#line 484 "engines/director/lingo/lingo-gr.y"
                                                                {
		// This matches `play frame arg of movie arg`
		NodeList *args = new NodeList;
		args->push_back(new FrameNode((yyvsp[-3].node)));
		args->push_back(new MovieNode((yyvsp[0].node)));
		(yyval.nodelist) = args; }
#line 3359 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 140: /* frameargs: expr tOF tMOVIE expr  */
#line 490 "engines/director/lingo/lingo-gr.y"
                                                                {
		// This matches `play arg of movie arg` (weird but valid)
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-3].node));
		args->push_back(new MovieNode((yyvsp[0].node)));
		(yyval.nodelist) = args; }
#line 3370 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 141: /* frameargs: tFRAME expr expr_nounarymath  */
#line 496 "engines/director/lingo/lingo-gr.y"
                                                        {
		// This matches `play frame arg arg` (also weird but valid)
		NodeList *args = new NodeList;
		args->push_back(new FrameNode((yyvsp[-1].node)));
		args->push_back((yyvsp[0].node));
		(yyval.nodelist) = args; }
#line 3381 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 142: /* asgn: tPUT expr tINTO varorchunk '\n'  */
#line 504 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new PutIntoNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3387 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 143: /* asgn: tPUT expr tAFTER varorchunk '\n'  */
#line 505 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PutAfterNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3393 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 144: /* asgn: tPUT expr tBEFORE varorchunk '\n'  */
#line 506 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PutBeforeNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3399 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 145: /* asgn: tSET varorthe to expr '\n'  */
#line 507 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new SetNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3405 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 148: /* definevars: tGLOBAL idlist '\n'  */
#line 512 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new GlobalNode((yyvsp[-1].idlist)); }
#line 3411 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 149: /* definevars: tPROPERTY idlist '\n'  */
#line 513 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new PropertyNode((yyvsp[-1].idlist)); }
#line 3417 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 150: /* definevars: tINSTANCE idlist '\n'  */
#line 514 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new InstanceNode((yyvsp[-1].idlist)); }
#line 3423 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 151: /* ifstmt: tIF expr tTHEN stmt  */
#line 517 "engines/director/lingo/lingo-gr.y"
                            {
		NodeList *stmtlist = new NodeList;
		stmtlist->push_back((yyvsp[0].node));
		(yyval.node) = new IfStmtNode((yyvsp[-2].node), stmtlist); }
#line 3432 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 152: /* ifstmt: tIF expr tTHEN '\n' stmtlist_insideif endif  */
#line 521 "engines/director/lingo/lingo-gr.y"
                                                      {
		(yyval.node) = new IfStmtNode((yyvsp[-4].node), (yyvsp[-1].nodelist)); }
#line 3439 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 153: /* ifelsestmt: tIF expr tTHEN stmt tELSE stmt  */
#line 525 "engines/director/lingo/lingo-gr.y"
                                                         {
		NodeList *stmtlist1 = new NodeList;
		stmtlist1->push_back((yyvsp[-2].node));
		NodeList *stmtlist2 = new NodeList;
		stmtlist2->push_back((yyvsp[0].node));
		(yyval.node) = new IfElseStmtNode((yyvsp[-4].node), stmtlist1, stmtlist2); }
#line 3450 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 154: /* ifelsestmt: tIF expr tTHEN stmt tELSE '\n' stmtlist_insideif endif  */
#line 531 "engines/director/lingo/lingo-gr.y"
                                                                                   {
		NodeList *stmtlist1 = new NodeList;
		stmtlist1->push_back((yyvsp[-4].node));
		(yyval.node) = new IfElseStmtNode((yyvsp[-6].node), stmtlist1, (yyvsp[-1].nodelist)); }
#line 3459 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 155: /* ifelsestmt: tIF expr tTHEN '\n' stmtlist_insideif tELSE stmt  */
#line 535 "engines/director/lingo/lingo-gr.y"
                                                                             {
		NodeList *stmtlist2 = new NodeList;
		stmtlist2->push_back((yyvsp[0].node));
		(yyval.node) = new IfElseStmtNode((yyvsp[-5].node), (yyvsp[-2].nodelist), stmtlist2); }
#line 3468 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 156: /* ifelsestmt: tIF expr tTHEN '\n' stmtlist_insideif tELSE '\n' stmtlist_insideif endif  */
#line 539 "engines/director/lingo/lingo-gr.y"
                                                                                                         {
		(yyval.node) = new IfElseStmtNode((yyvsp[-7].node), (yyvsp[-4].nodelist), (yyvsp[-1].nodelist)); }
#line 3475 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 157: /* endif: %empty  */
#line 543 "engines/director/lingo/lingo-gr.y"
                        { warning("LingoCompiler::parse: no end if"); }
#line 3481 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 159: /* loop: tREPEAT tWHILE expr '\n' stmtlist tENDREPEAT '\n'  */
#line 546 "engines/director/lingo/lingo-gr.y"
                                                        {
		(yyval.node) = new RepeatWhileNode((yyvsp[-4].node), (yyvsp[-2].nodelist)); }
#line 3488 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 160: /* loop: tREPEAT tWITH ID tEQ expr tTO expr '\n' stmtlist tENDREPEAT '\n'  */
#line 548 "engines/director/lingo/lingo-gr.y"
                                                                                       {
		(yyval.node) = new RepeatWithToNode((yyvsp[-8].s), (yyvsp[-6].node), false, (yyvsp[-4].node), (yyvsp[-2].nodelist)); }
#line 3495 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 161: /* loop: tREPEAT tWITH ID tEQ expr tDOWN tTO expr '\n' stmtlist tENDREPEAT '\n'  */
#line 550 "engines/director/lingo/lingo-gr.y"
                                                                                             {
		(yyval.node) = new RepeatWithToNode((yyvsp[-9].s), (yyvsp[-7].node), true, (yyvsp[-4].node), (yyvsp[-2].nodelist)); }
#line 3502 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 162: /* loop: tREPEAT tWITH ID tIN expr '\n' stmtlist tENDREPEAT '\n'  */
#line 552 "engines/director/lingo/lingo-gr.y"
                                                                  {
		(yyval.node) = new RepeatWithInNode((yyvsp[-6].s), (yyvsp[-4].node), (yyvsp[-2].nodelist)); }
#line 3509 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 163: /* tell: tTELL expr tTO stmtoneliner  */
#line 556 "engines/director/lingo/lingo-gr.y"
                                                                {
		NodeList *stmtlist = new NodeList;
		stmtlist->push_back((yyvsp[0].node));
		(yyval.node) = new TellNode((yyvsp[-2].node), stmtlist); }
#line 3518 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 164: /* tell: tTELL expr '\n' stmtlist tENDTELL '\n'  */
#line 560 "engines/director/lingo/lingo-gr.y"
                                                        {
		(yyval.node) = new TellNode((yyvsp[-4].node), (yyvsp[-2].nodelist)); }
#line 3525 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 165: /* when: tWHEN  */
#line 564 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new WhenNode((yyvsp[0].w).eventName, (yyvsp[0].w).stmt); }
#line 3531 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 166: /* stmtlist: %empty  */
#line 566 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.nodelist) = new NodeList; }
#line 3537 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 168: /* nonemptystmtlist: stmtlistline  */
#line 571 "engines/director/lingo/lingo-gr.y"
                                                                {
		NodeList *list = new NodeList;
		if ((yyvsp[0].node)) {
			list->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = list; }
#line 3548 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 169: /* nonemptystmtlist: nonemptystmtlist stmtlistline  */
#line 577 "engines/director/lingo/lingo-gr.y"
                                                        {
		if ((yyvsp[0].node)) {
			(yyvsp[-1].nodelist)->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 3558 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 170: /* stmtlistline: '\n'  */
#line 584 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = nullptr; }
#line 3564 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 172: /* stmtlist_insideif: %empty  */
#line 588 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.nodelist) = new NodeList; }
#line 3570 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 174: /* nonemptystmtlist_insideif: stmtlistline_insideif  */
#line 593 "engines/director/lingo/lingo-gr.y"
                                                {
		NodeList *list = new NodeList;
		if ((yyvsp[0].node)) {
			list->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = list; }
#line 3581 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 175: /* nonemptystmtlist_insideif: nonemptystmtlist_insideif stmtlistline_insideif  */
#line 599 "engines/director/lingo/lingo-gr.y"
                                                                        {
		if ((yyvsp[0].node)) {
			(yyvsp[-1].nodelist)->push_back((yyvsp[0].node));
		}
		(yyval.nodelist) = (yyvsp[-1].nodelist); }
#line 3591 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 176: /* stmtlistline_insideif: '\n'  */
#line 606 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = nullptr; }
#line 3597 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 178: /* simpleexpr_nounarymath: tINT  */
#line 613 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new IntNode((yyvsp[0].i)); }
#line 3603 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 179: /* simpleexpr_nounarymath: tFLOAT  */
#line 614 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new FloatNode((yyvsp[0].f)); }
#line 3609 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 180: /* simpleexpr_nounarymath: tSYMBOL  */
#line 615 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new SymbolNode((yyvsp[0].s)); }
#line 3615 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 181: /* simpleexpr_nounarymath: tSTRING  */
#line 616 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new StringNode((yyvsp[0].s)); }
#line 3621 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 182: /* simpleexpr_nounarymath: tNOT simpleexpr  */
#line 617 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new UnaryOpNode(LC::c_not, (yyvsp[0].node)); }
#line 3627 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 183: /* simpleexpr_nounarymath: ID '(' ')'  */
#line 618 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new FuncNode((yyvsp[-2].s), new NodeList); }
#line 3633 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 184: /* simpleexpr_nounarymath: ID '(' nonemptyexprlist trailingcomma ')'  */
#line 619 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new FuncNode((yyvsp[-4].s), (yyvsp[-2].nodelist)); }
#line 3639 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 185: /* simpleexpr_nounarymath: '(' expr ')'  */
#line 620 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = (yyvsp[-1].node); }
#line 3645 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 191: /* var: ID  */
#line 628 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new VarNode((yyvsp[0].s)); }
#line 3651 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 196: /* chunk: tFIELD refargs  */
#line 638 "engines/director/lingo/lingo-gr.y"
                                { (yyval.node) = new FuncNode(new Common::String("field"), (yyvsp[0].nodelist)); }
#line 3657 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 197: /* chunk: tCAST refargs  */
#line 639 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new FuncNode(new Common::String("cast"), (yyvsp[0].nodelist)); }
#line 3663 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 198: /* chunk: tCHAR expr tOF simpleexpr  */
#line 640 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyval.node) = new ChunkExprNode(kChunkChar, (yyvsp[-2].node), nullptr, (yyvsp[0].node)); }
#line 3670 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 199: /* chunk: tCHAR expr tTO expr tOF simpleexpr  */
#line 642 "engines/director/lingo/lingo-gr.y"
                                                                {
		(yyval.node) = new ChunkExprNode(kChunkChar, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3677 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 200: /* chunk: tWORD expr tOF simpleexpr  */
#line 644 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyval.node) = new ChunkExprNode(kChunkWord, (yyvsp[-2].node), nullptr, (yyvsp[0].node)); }
#line 3684 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 201: /* chunk: tWORD expr tTO expr tOF simpleexpr  */
#line 646 "engines/director/lingo/lingo-gr.y"
                                                                {
		(yyval.node) = new ChunkExprNode(kChunkWord, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3691 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 202: /* chunk: tITEM expr tOF simpleexpr  */
#line 648 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyval.node) = new ChunkExprNode(kChunkItem, (yyvsp[-2].node), nullptr, (yyvsp[0].node)); }
#line 3698 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 203: /* chunk: tITEM expr tTO expr tOF simpleexpr  */
#line 650 "engines/director/lingo/lingo-gr.y"
                                                                {
		(yyval.node) = new ChunkExprNode(kChunkItem, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3705 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 204: /* chunk: tLINE expr tOF simpleexpr  */
#line 652 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyval.node) = new ChunkExprNode(kChunkLine, (yyvsp[-2].node), nullptr, (yyvsp[0].node)); }
#line 3712 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 205: /* chunk: tLINE expr tTO expr tOF simpleexpr  */
#line 654 "engines/director/lingo/lingo-gr.y"
                                                                {
		(yyval.node) = new ChunkExprNode(kChunkLine, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3719 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 206: /* chunk: tTHE tLAST chunktype inof simpleexpr  */
#line 656 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new TheLastNode((yyvsp[-2].chunktype), (yyvsp[0].node)); }
#line 3725 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 207: /* chunktype: tCHAR  */
#line 659 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.chunktype) = kChunkChar; }
#line 3731 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 208: /* chunktype: tWORD  */
#line 660 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.chunktype) = kChunkWord; }
#line 3737 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 209: /* chunktype: tITEM  */
#line 661 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.chunktype) = kChunkItem; }
#line 3743 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 210: /* chunktype: tLINE  */
#line 662 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.chunktype) = kChunkLine; }
#line 3749 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 211: /* object: tSCRIPT refargs  */
#line 665 "engines/director/lingo/lingo-gr.y"
                                { (yyval.node) = new FuncNode(new Common::String("script"), (yyvsp[0].nodelist)); }
#line 3755 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 212: /* object: tWINDOW refargs  */
#line 666 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new FuncNode(new Common::String("window"), (yyvsp[0].nodelist)); }
#line 3761 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 213: /* refargs: simpleexpr  */
#line 669 "engines/director/lingo/lingo-gr.y"
                                                                                {
		// This matches `ref arg` and `ref(arg)`
		NodeList *args = new NodeList;
		args->push_back((yyvsp[0].node));
		(yyval.nodelist) = args; }
#line 3771 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 214: /* refargs: '(' ')'  */
#line 674 "engines/director/lingo/lingo-gr.y"
                                                                                        {
		// This matches `ref()`
		(yyval.nodelist) = new NodeList; }
#line 3779 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 215: /* refargs: '(' expr ',' ')'  */
#line 677 "engines/director/lingo/lingo-gr.y"
                           {
		// This matches `ref(args,)`
		NodeList *args = new NodeList;
		args->push_back((yyvsp[-2].node));
		(yyval.nodelist) = args; }
#line 3789 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 216: /* refargs: '(' expr ',' nonemptyexprlist trailingcomma ')'  */
#line 682 "engines/director/lingo/lingo-gr.y"
                                                                {
		// This matches `ref(args, ...)`
		(yyvsp[-2].nodelist)->insert_at(0, (yyvsp[-4].node));
		(yyval.nodelist) = (yyvsp[-2].nodelist); }
#line 3798 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 217: /* the: tTHE ID  */
#line 688 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheNode((yyvsp[0].s)); }
#line 3804 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 218: /* the: tTHE ID tOF theobj  */
#line 689 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheOfNode((yyvsp[-2].s), (yyvsp[0].node)); }
#line 3810 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 219: /* the: tTHE tNUMBER tOF theobj  */
#line 690 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheOfNode(new Common::String("number"), (yyvsp[0].node)); }
#line 3816 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 224: /* theobj: tMENUITEM simpleexpr tOF tMENU simpleexpr  */
#line 697 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new MenuItemNode((yyvsp[-3].node), (yyvsp[0].node)); }
#line 3822 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 225: /* theobj: tSOUND simpleexpr  */
#line 698 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new SoundNode((yyvsp[0].node)); }
#line 3828 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 226: /* theobj: tSPRITE simpleexpr  */
#line 699 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new SpriteNode((yyvsp[0].node)); }
#line 3834 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 227: /* menu: tMENU simpleexpr  */
#line 702 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new MenuNode((yyvsp[0].node)); }
#line 3840 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 228: /* thedatetime: tTHE tABBREVIATED tDATE  */
#line 704 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheDate); }
#line 3846 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 229: /* thedatetime: tTHE tABBREVIATED tTIME  */
#line 705 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheTime); }
#line 3852 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 230: /* thedatetime: tTHE tABBREV tDATE  */
#line 706 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheDate); }
#line 3858 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 231: /* thedatetime: tTHE tABBREV tTIME  */
#line 707 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheTime); }
#line 3864 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 232: /* thedatetime: tTHE tABBR tDATE  */
#line 708 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheDate); }
#line 3870 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 233: /* thedatetime: tTHE tABBR tTIME  */
#line 709 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheAbbr, kTheTime); }
#line 3876 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 234: /* thedatetime: tTHE tLONG tDATE  */
#line 710 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheLong, kTheDate); }
#line 3882 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 235: /* thedatetime: tTHE tLONG tTIME  */
#line 711 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheLong, kTheTime); }
#line 3888 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 236: /* thedatetime: tTHE tSHORT tDATE  */
#line 712 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheShort, kTheDate); }
#line 3894 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 237: /* thedatetime: tTHE tSHORT tTIME  */
#line 713 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new TheDateTimeNode(kTheShort, kTheTime); }
#line 3900 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 238: /* thenumberof: tTHE tNUMBER tOF tCHARS inof simpleexpr  */
#line 717 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNumberOfNode(kNumberOfChars, (yyvsp[0].node)); }
#line 3906 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 239: /* thenumberof: tTHE tNUMBER tOF tWORDS inof simpleexpr  */
#line 718 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNumberOfNode(kNumberOfWords, (yyvsp[0].node)); }
#line 3912 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 240: /* thenumberof: tTHE tNUMBER tOF tITEMS inof simpleexpr  */
#line 719 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNumberOfNode(kNumberOfItems, (yyvsp[0].node)); }
#line 3918 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 241: /* thenumberof: tTHE tNUMBER tOF tLINES inof simpleexpr  */
#line 720 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNumberOfNode(kNumberOfLines, (yyvsp[0].node)); }
#line 3924 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 242: /* thenumberof: tTHE tNUMBER tOF tMENUITEMS inof menu  */
#line 721 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNumberOfNode(kNumberOfMenuItems, (yyvsp[0].node)); }
#line 3930 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 245: /* writablethe: tTHE ID  */
#line 726 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new TheNode((yyvsp[0].s)); }
#line 3936 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 246: /* writablethe: tTHE ID tOF writabletheobj  */
#line 727 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new TheOfNode((yyvsp[-2].s), (yyvsp[0].node)); }
#line 3942 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 248: /* writabletheobj: tMENU expr_noeq  */
#line 731 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new MenuNode((yyvsp[0].node)); }
#line 3948 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 249: /* writabletheobj: tMENUITEM expr_noeq tOF tMENU expr_noeq  */
#line 732 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new MenuItemNode((yyvsp[-3].node), (yyvsp[0].node)); }
#line 3954 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 250: /* writabletheobj: tSOUND expr_noeq  */
#line 733 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new SoundNode((yyvsp[0].node)); }
#line 3960 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 251: /* writabletheobj: tSPRITE expr_noeq  */
#line 734 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new SpriteNode((yyvsp[0].node)); }
#line 3966 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 252: /* list: '[' exprlist ']'  */
#line 737 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new ListNode((yyvsp[-1].nodelist)); }
#line 3972 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 253: /* list: '[' ':' ']'  */
#line 738 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PropListNode(new NodeList); }
#line 3978 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 254: /* list: '[' proplist ']'  */
#line 739 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PropListNode((yyvsp[-1].nodelist)); }
#line 3984 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 255: /* proplist: proppair  */
#line 742 "engines/director/lingo/lingo-gr.y"
                                                        {
		NodeList *list = new NodeList; 
		list->push_back((yyvsp[0].node));
		(yyval.nodelist) = list; }
#line 3993 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 256: /* proplist: proplist ',' proppair  */
#line 746 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyvsp[-2].nodelist)->push_back((yyvsp[0].node));
		(yyval.nodelist) = (yyvsp[-2].nodelist); }
#line 4001 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 257: /* proppair: tSYMBOL ':' expr  */
#line 751 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new PropPairNode(new SymbolNode((yyvsp[-2].s)), (yyvsp[0].node)); }
#line 4007 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 258: /* proppair: ID ':' expr  */
#line 752 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PropPairNode(new SymbolNode((yyvsp[-2].s)), (yyvsp[0].node)); }
#line 4013 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 259: /* proppair: tSTRING ':' expr  */
#line 753 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new PropPairNode(new StringNode((yyvsp[-2].s)), (yyvsp[0].node)); }
#line 4019 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 260: /* unarymath: '+' simpleexpr  */
#line 756 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 4025 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 261: /* unarymath: '-' simpleexpr  */
#line 757 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.node) = new UnaryOpNode(LC::c_negate, (yyvsp[0].node)); }
#line 4031 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 266: /* expr: expr '+' expr  */
#line 767 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4037 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 267: /* expr: expr '-' expr  */
#line 768 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4043 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 268: /* expr: expr '*' expr  */
#line 769 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4049 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 269: /* expr: expr '/' expr  */
#line 770 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4055 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 270: /* expr: expr tMOD expr  */
#line 771 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4061 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 271: /* expr: expr '>' expr  */
#line 772 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_gt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4067 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 272: /* expr: expr '<' expr  */
#line 773 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_lt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4073 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 273: /* expr: expr tEQ expr  */
#line 774 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_eq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4079 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 274: /* expr: expr tNEQ expr  */
#line 775 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_neq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4085 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 275: /* expr: expr tGE expr  */
#line 776 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_ge, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4091 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 276: /* expr: expr tLE expr  */
#line 777 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_le, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4097 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 277: /* expr: expr tAND expr  */
#line 778 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_and, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4103 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 278: /* expr: expr tOR expr  */
#line 779 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4109 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 279: /* expr: expr '&' expr  */
#line 780 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_ampersand, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4115 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 280: /* expr: expr tCONCAT expr  */
#line 781 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_concat, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4121 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 281: /* expr: expr tCONTAINS expr  */
#line 782 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_contains, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4127 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 282: /* expr: expr tSTARTS expr  */
#line 783 "engines/director/lingo/lingo-gr.y"
                                        { (yyval.node) = new BinaryOpNode(LC::c_starts, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4133 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 285: /* expr_nounarymath: expr_nounarymath '+' expr  */
#line 792 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4139 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 286: /* expr_nounarymath: expr_nounarymath '-' expr  */
#line 793 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4145 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 287: /* expr_nounarymath: expr_nounarymath '*' expr  */
#line 794 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4151 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 288: /* expr_nounarymath: expr_nounarymath '/' expr  */
#line 795 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4157 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 289: /* expr_nounarymath: expr_nounarymath tMOD expr  */
#line 796 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4163 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 290: /* expr_nounarymath: expr_nounarymath '>' expr  */
#line 797 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_gt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4169 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 291: /* expr_nounarymath: expr_nounarymath '<' expr  */
#line 798 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_lt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4175 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 292: /* expr_nounarymath: expr_nounarymath tEQ expr  */
#line 799 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_eq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4181 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 293: /* expr_nounarymath: expr_nounarymath tNEQ expr  */
#line 800 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_neq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4187 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 294: /* expr_nounarymath: expr_nounarymath tGE expr  */
#line 801 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_ge, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4193 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 295: /* expr_nounarymath: expr_nounarymath tLE expr  */
#line 802 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_le, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4199 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 296: /* expr_nounarymath: expr_nounarymath tAND expr  */
#line 803 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_and, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4205 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 297: /* expr_nounarymath: expr_nounarymath tOR expr  */
#line 804 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4211 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 298: /* expr_nounarymath: expr_nounarymath '&' expr  */
#line 805 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_ampersand, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4217 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 299: /* expr_nounarymath: expr_nounarymath tCONCAT expr  */
#line 806 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new BinaryOpNode(LC::c_concat, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4223 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 300: /* expr_nounarymath: expr_nounarymath tCONTAINS expr  */
#line 807 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new BinaryOpNode(LC::c_contains, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4229 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 301: /* expr_nounarymath: expr_nounarymath tSTARTS expr  */
#line 808 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new BinaryOpNode(LC::c_starts, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4235 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 304: /* expr_noeq: expr_noeq '+' expr_noeq  */
#line 813 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4241 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 305: /* expr_noeq: expr_noeq '-' expr_noeq  */
#line 814 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4247 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 306: /* expr_noeq: expr_noeq '*' expr_noeq  */
#line 815 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4253 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 307: /* expr_noeq: expr_noeq '/' expr_noeq  */
#line 816 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4259 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 308: /* expr_noeq: expr_noeq tMOD expr_noeq  */
#line 817 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4265 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 309: /* expr_noeq: expr_noeq '>' expr_noeq  */
#line 818 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_gt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4271 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 310: /* expr_noeq: expr_noeq '<' expr_noeq  */
#line 819 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_lt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4277 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 311: /* expr_noeq: expr_noeq tNEQ expr_noeq  */
#line 820 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_neq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4283 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 312: /* expr_noeq: expr_noeq tGE expr_noeq  */
#line 821 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_ge, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4289 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 313: /* expr_noeq: expr_noeq tLE expr_noeq  */
#line 822 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_le, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4295 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 314: /* expr_noeq: expr_noeq tAND expr_noeq  */
#line 823 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_and, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4301 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 315: /* expr_noeq: expr_noeq tOR expr_noeq  */
#line 824 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4307 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 316: /* expr_noeq: expr_noeq '&' expr_noeq  */
#line 825 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_ampersand, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4313 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 317: /* expr_noeq: expr_noeq tCONCAT expr_noeq  */
#line 826 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_concat, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4319 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 318: /* expr_noeq: expr_noeq tCONTAINS expr_noeq  */
#line 827 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new BinaryOpNode(LC::c_contains, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4325 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 319: /* expr_noeq: expr_noeq tSTARTS expr_noeq  */
#line 828 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new BinaryOpNode(LC::c_starts, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4331 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 320: /* sprite: tSPRITE expr tINTERSECTS simpleexpr  */
#line 831 "engines/director/lingo/lingo-gr.y"
                                                { (yyval.node) = new IntersectsNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 4337 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 321: /* sprite: tSPRITE expr tWITHIN simpleexpr  */
#line 832 "engines/director/lingo/lingo-gr.y"
                                                        { (yyval.node) = new WithinNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 4343 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 322: /* exprlist: %empty  */
#line 835 "engines/director/lingo/lingo-gr.y"
                                                                { (yyval.nodelist) = new NodeList; }
#line 4349 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 324: /* nonemptyexprlist: expr  */
#line 839 "engines/director/lingo/lingo-gr.y"
                                                        {
		NodeList *list = new NodeList; 
		list->push_back((yyvsp[0].node));
		(yyval.nodelist) = list; }
#line 4358 "engines/director/lingo/lingo-gr.cpp"
    break;

  case 325: /* nonemptyexprlist: nonemptyexprlist ',' expr  */
#line 843 "engines/director/lingo/lingo-gr.y"
                                                {
		(yyvsp[-2].nodelist)->push_back((yyvsp[0].node));
		(yyval.nodelist) = (yyvsp[-2].nodelist); }
#line 4366 "engines/director/lingo/lingo-gr.cpp"
    break;


#line 4370 "engines/director/lingo/lingo-gr.cpp"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        if (yyreport_syntax_error (&yyctx) == 2)
          goto yyexhaustedlab;
      }
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 848 "engines/director/lingo/lingo-gr.y"


int yyreport_syntax_error(const yypcontext_t *ctx) {
	int res = 0;

	Common::String msg = "syntax error, ";

	// Report the unexpected token.
	yysymbol_kind_t lookahead = yypcontext_token(ctx);
	if (lookahead != YYSYMBOL_YYEMPTY)
		msg += Common::String::format("unexpected %s", yysymbol_name(lookahead));

	// Report the tokens expected at this point.
	enum { TOKENMAX = 10 };
	yysymbol_kind_t expected[TOKENMAX];

	int n = yypcontext_expected_tokens(ctx, expected, TOKENMAX);
	if (n < 0)
		// Forward errors to yyparse.
		res = n;
	else
		for (int i = 0; i < n; ++i)
			msg += Common::String::format("%s %s", i == 0 ? ": expected" : " or", yysymbol_name(expected[i]));

	yyerror(msg.c_str());

	return res;
}
