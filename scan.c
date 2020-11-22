/*bug included !! */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRSIZE 1024

/* Token */
#define    TNAME        1    /* Name : Alphabet { Alphabet | Digit } */
#define    TPROGRAM    2    /* program : Keyword */
#define    TVAR        3    /* var : Keyword */
#define    TARRAY        4    /* array : Keyword */
#define    TOF        5    /* of : Keyword */
#define    TBEGIN        6    /* begin : Keyword */
#define    TEND        7    /* end : Keyword */
#define    TIF        8    /* if : Keyword */
#define    TTHEN        9    /* then : Keyword */
#define    TELSE        10    /* else : Keyword */
#define    TPROCEDURE    11    /* procedure : Keyword */
#define    TRETURN        12    /* return : Keyword */
#define    TCALL        13    /* call : Keyword */
#define    TWHILE        14    /* while : Keyword */
#define    TDO        15    /* do : Keyword */
#define    TNOT        16    /* not : Keyword */
#define    TOR        17    /* or : Keyword */
#define    TDIV        18    /* div : Keyword */
#define    TAND        19    /* and : Keyword */
#define    TCHAR        20    /* char : Keyword */
#define    TINTEGER    21    /* integer : Keyword */
#define    TBOOLEAN    22    /* boolean : Keyword */
#define    TREADLN        23    /* readln : Keyword */
#define    TWRITELN    24    /* writeln : Keyword */
#define    TTRUE        25    /* true : Keyword */
#define    TFALSE        26    /* false : Keyword */
#define    TNUMBER        27    /* unsigned integer */
#define    TSTRING        28    /* String */
#define    TPLUS        29    /* + : symbol -*/
#define    TMINUS        30    /* - : symbol -*/
#define    TSTAR        31    /* * : symbol -*/
#define    TEQUAL        32    /* = : symbol -*/
#define    TNOTEQ        33    /* <> : symbol -*/
#define    TLE        34    /* < : symbol -*/
#define    TLEEQ        35    /* <= : symbol -*/
#define    TGR        36    /* > : symbol -*/
#define    TGREQ        37    /* >= : symbol -*/
#define    TLPAREN        38    /* ( : symbol -*/
#define    TRPAREN        39    /* ) : symbol -*/
#define    TLSQPAREN    40    /* [ : symbol -*/
#define    TRSQPAREN    41    /* ] : symbol -*/
#define    TASSIGN        42    /* := : symbol -*/
#define    TDOT        43    /* . : symbol -*/
#define    TCOMMA        44    /* , : symbol -*/
#define    TCOLON        45    /* : : symbol -*/
#define    TSEMI        46    /* ; : symbol -*/
#define    TREAD        47    /* read : Keyword */
#define    TWRITE        48    /* write : Keyword */
#define    TBREAK        49    /* break : Keyword */

#define NUMOFTOKEN    49

/* token-list.c */

#define KEYWORDSIZE    28


extern int num_attr;
extern char string_attr[MAXSTRSIZE];

extern int get_linenum(void);

extern void end_scan(void);

extern struct KEY {
    char *keyword;
    int keytoken;
} key[KEYWORDSIZE];
extern FILE *mmpl;
extern void error(char *mes);
extern int init_scan(char *filename) {
    if ((mmpl = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "e");
        return -1;
    } else {
        return 0;
    }
}


extern char buff[30];
extern int linenum;
char *tokens[NUMOFTOKEN + 1] = {
        "",
        "NAME", "program", "var", "array", "of", "begin", "end", "if", "then",
        "else", "procedure", "return", "call", "while", "do", "not", "or",
        "div", "and", "char", "integer", "boolean", "readln", "writeln", "true",
        "false", "NUMBER", "STRING", "+", "-", "*", "=", "<>", "<", "<=", ">",
        ">=", "(", ")", "[", "]", ":=", ".", ",", ":", ";", "read", "write", "break"
};

extern int isalphaordigit(int c) {
    return isalpha(c) || isdigit(c);
}

extern int scan(void) {
    char c;

    int i = 0;
    while ((c = fgetc(mmpl)) != EOF) {
        if (c == '\n') {
            linenum += 1;
            return 0;
        } else if (isspace(c)) {
            return 0;
        } else if (c == '<') {
            c = fgetc(mmpl);
            if (c == '>') {
                return TNOTEQ;
            } else if (c == '=') {
                return TLEEQ;
            } else {
                ungetc(c, mmpl);
                return TLE;
            }
        } else if (c == '>') {
            if ((c = fgetc(mmpl)) != EOF) {
                if (c == '=') {
                    return TGREQ;
                } else {
                    ungetc(c, mmpl);
                    return TGR;
                }
            } else {
                ungetc(c, mmpl);
                return 0;
            }
        } else if (c == ':') {
            c = fgetc(mmpl);
            if (c == '=') {
                return TASSIGN;
            } else {
                ungetc(c, mmpl);
                return TCOLON;
            }
        } else if (c == '=') {
            return TEQUAL;
        } else if (c == ';') {
            return TSEMI;
        } else if (c == ',') {
            return TCOMMA;
        } else if (c == '.') {
            return TDOT;
        } else if (c == '(') {
            return TLPAREN;
        } else if (c == ')') {
            return TRPAREN;
        } else if (c == '[') {
            return TLSQPAREN;
        } else if (c == ']') {
            return TRSQPAREN;
        } else if (c == '+') {
            return TPLUS;
        } else if (c == '-') {
            return TMINUS;
        } else if (c == '*') {
            return TSTAR;
        } else if (isalpha(c)) {
            int f = 0;
            /*alphabet*/
            buff[i++] = c;
            while ((c = fgetc(mmpl)) != EOF) {
                if (isalphaordigit(c)) {
                    buff[i++] = c;
                } else {
                    ungetc(c, mmpl);
                    f = 1;
                    break;
                }
            }
            if (c == EOF) {
                ungetc(c, mmpl);
            }
            if (f == 1) {
                break;
            }
        } else if (isdigit(c)) {
            /*digit*/
            buff[i++] = c;
            while ((c = fgetc(mmpl)) != EOF) {
                if (isdigit(c)) {
                    buff[i++] = c;
                } else if (isalpha(c)) {
                    fprintf(stderr, "error detected");
                    return -1;
                } else {
                    ungetc(c, mmpl);
                    return 1;
                }
            }
            if (c == EOF) {
                ungetc(c, mmpl);
                return 1;
            }
        } else if (c == '{') {
            /*comment case{}  */
            while ((c = fgetc(mmpl)) != EOF) {
                if (c == '}') {
                    return 0;
                } else {
                    continue;
                }
            }
            if (c == EOF) {
                fprintf(stderr, "error: comment not ended");
                return -1;
            }

        } else if (c == '/') {
            if ((c = fgetc(mmpl)) != EOF) {
                if (c == '*') {
                    while ((c = fgetc(mmpl)) != EOF) {
                        if (c != '*') {
                            if ((c = fgetc(mmpl)) != EOF) {
                                if (c == '/') {
                                    return 0;
                                } else {
                                    continue;
                                }
                            } else {
                                fprintf(stderr, "Error: comment not ended");
                                return -1;
                            }
                        } else {
                            continue;
                        }
                    }
                    if (c == EOF) {
                        fprintf(stderr, "Error: comment not ended");
                        return -1;
                    }
                } else {
                    fprintf(stderr, "Error:unknown token /");
                    return -1;
                }
            }
        }
    }
    int j=0;
    for(j=2;j<50;j++){
        if(strcmp(tokens[j],buff)){
            return j;
        }
    }
}
