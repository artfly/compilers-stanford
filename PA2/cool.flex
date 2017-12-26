/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
    if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
        YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
int str_curr_idx = 0; /* current char position in string buffer */
bool invalid_str = false; /* true if string contains any errors */

int comment_depth = 0; /* comment depth for managing nested comments */

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

%}

/* start condition for strings */
%x STRING
/* start condition for comments */
%x COMMENT
/* start condition for one line comments */
%x ONELINECOMMENT

%{

/**
 * Write char into string buffer if possible. On fail it sets error message.
 *
 * @param c character
 * @return result of write 
 */
bool write_char(char c) { 
    if (str_curr_idx >= (MAX_STR_CONST - 1)) {
        cool_yylval.error_msg = "String constant too long";
        return false;
    } else {
      string_buf[str_curr_idx] = c;
      str_curr_idx++;
      return true;
    }
}

/**
 * Restore initial state after string parsing. 
 * Sets error flag to false and moves current char pointer to start.
 */
void restore_initial_state() {
    invalid_str = false;
    str_curr_idx = 0;
}

%}

CLASS                  (?i:class)
ELSE                   (?i:else)
FI                     (?i:fi)
IF                     (?i:if)
IN                     (?i:in)
INHERITS               (?i:inherits)
LET                    (?i:let)
LOOP                   (?i:loop)
POOL                   (?i:pool)
THEN                   (?i:then)
WHILE                  (?i:while)
CASE                   (?i:case)
ESAC                   (?i:esac)
OF                     (?i:of)
NEW                    (?i:new)
ISVOID                 (?i:isvoid)
NOT                    (?i:not)
DARROW                 =>
LE                     <=
ASSIGN                 <-

QUOTATION              \"
NUL                    \0
BACKSPACE              \\b
TAB                    \\t
LINEFEED               \\n
FORMFEED               \\f
HORIZONTALTAB          \\t
ESCAPEDCHAR            \\[^btnf\0]

ONELINECOMMENTSTART    --
COMMENTSTART           "(*"
COMMENTEND             "*)"

INT_CONST              [0-9]+
BOOL_CONST             t(?i:rue)|f(?i:alse)

TYPEID                 [A-Z][A-Za-z0-9_]*
OBJECTID               [a-z][A-Za-z0-9_]*

NEWLINE                \n
WHITESPACE             [ \t\f\v\r]+

SINGLECHAR             [+/\-*=<.~,;:)(@}{]

ANY                    .

%%

<STRING>{

<<EOF>>            { cool_yylval.error_msg = "EOF in string constant"; BEGIN(INITIAL); return ERROR; }

{NUL}              { cool_yylval.error_msg = "String contains null character"; invalid_str = true; }

{BACKSPACE}        { if (!invalid_str) { invalid_str = !write_char('\b'); }  }

{HORIZONTALTAB}    { if (!invalid_str) { invalid_str = !write_char('\t'); }  }

{LINEFEED}         { if (!invalid_str) { invalid_str = !write_char('\n'); }  }

{FORMFEED}         { if (!invalid_str) { invalid_str = !write_char('\f'); }  }

{ESCAPEDCHAR}      { if (!invalid_str) { invalid_str = !write_char(*(yytext + 1)); } }

{QUOTATION}        { int token;
                     if (invalid_str) { 
                     token = ERROR;
                     } else {
                         string_buf[str_curr_idx] = '\0';
                         str_curr_idx++;
                         cool_yylval.symbol = new StringEntry(string_buf, str_curr_idx, STR_CONST);
                         token = STR_CONST;
                     }

                     restore_initial_state();
                     BEGIN(INITIAL);
                     return token;
                   }

{NEWLINE}          { if (!invalid_str) {
                         cool_yylval.error_msg = yytext;
                     }
                     restore_initial_state();
                     BEGIN(INITIAL);
                     return ERROR;
                   } 

{ANY}              { if (!invalid_str) { invalid_str = !write_char(*yytext); } }

}

<COMMENT>{

<<EOF>>           { cool_yylval.error_msg = "EOF in comment"; BEGIN(INITIAL); return ERROR; }

{COMMENTSTART}    { comment_depth++; }

{COMMENTEND}      { comment_depth--; if (comment_depth == 0) { BEGIN(INITIAL); } }

{ANY}             /** eat up comment **/

}

<ONELINECOMMENT>{

{NEWLINE}    { curr_lineno++; BEGIN(INITIAL); }

{ANY}        /* eat up comment */

}

 /*
  * Keywords.
  */
{CLASS}                 { return CLASS; }
{ELSE}                  { return ELSE; }
{FI}                    { return FI; }
{IF}                    { return IF; }
{IN}                    { return IN; }
{INHERITS}              { return INHERITS; }
{LET}                   { return LET; }
{LOOP}                  { return LOOP; }
{POOL}                  { return POOL; }
{THEN}                  { return THEN; }
{WHILE}                 { return WHILE; }
{CASE}                  { return CASE; }
{ESAC}                  { return ESAC; }
{OF}                    { return OF; }
{DARROW}                { return DARROW; }
{NEW}                   { return NEW; }
{ISVOID}                { return ISVOID; }
{ASSIGN}                { return ASSIGN; }
{NOT}                   { return NOT; }
{LE}                    { return LE; }

 /*
  * Constants.
  */
{INT_CONST}             { cool_yylval.symbol = new IntEntry(yytext, yyleng, INT_CONST); return INT_CONST; }
{BOOL_CONST}            { cool_yylval.boolean = *yytext == 't'; return BOOL_CONST; }

 /*
  * Identifiers.
  */
{TYPEID}                { cool_yylval.symbol = new IdEntry(yytext, yyleng, TYPEID); return TYPEID; }
{OBJECTID}              { cool_yylval.symbol = new IdEntry(yytext, yyleng, OBJECTID); return OBJECTID; }

 /*
  * Strings.
  */
{QUOTATION}              { BEGIN(STRING); }

 /*
  * Single char tokens.
  */
{SINGLECHAR}            { return *yytext; }

 /*
  * Comments.
  */
{ONELINECOMMENTSTART}   { BEGIN(ONELINECOMMENT); }
{COMMENTSTART}          { comment_depth = 1; BEGIN(COMMENT); }
{COMMENTEND}            { cool_yylval.error_msg = "Unmatched *)"; return ERROR; }

 /*
  * New lines and whitespaces.
  */
<*>{NEWLINE}            { curr_lineno++; }
{WHITESPACE}            /* ignore whitespaces */

 /*
  * Any unknown character.
  */
{ANY}                   { cool_yylval.error_msg = yytext; return ERROR; }

%%
