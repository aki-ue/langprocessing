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


int num_attr;
char string_attr[MAXSTRSIZE];


void end_scan(void);

struct KEY {
    char *keyword;
    int keytoken;
} key[KEYWORDSIZE];
FILE *mmpl;

void error(char *mes);

int init_scan(char *filename) {
    if ((mmpl = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "file open error");
        return -1;
    } else {
        return 0;
    }
}


char buff[1025];
int linenum;

int get_linenum(void) {
    return linenum;
}

char *tokens[NUMOFTOKEN + 1] = {
        "",
        "NAME", "program", "var", "array", "of", "begin", "end", "if", "then",
        "else", "procedure", "return", "call", "while", "do", "not", "or",
        "div", "and", "char", "integer", "boolean", "readln", "writeln", "true",
        "false", "NUMBER", "STRING", "+", "-", "*", "=", "<>", "<", "<=", ">",
        ">=", "(", ")", "[", "]", ":=", ".", ",", ":", ";", "read", "write", "break"
};

int isalphaordigit(int c) {
    return isalpha(c) || isdigit(c);
}

extern  int numtoken[NUMOFTOKEN+1];
void end_scan(void){
    int i;
    for(i=0;i<50;i++){
        if(numtoken[i]!=0){
            printf("%s    %d\n",tokens[i],numtoken[i]);
        }
    }
}


int scan(void) {
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
            int x;
            for(x=0; x<1024;x++){
                buff[x]='\0';
            }
            /*keywordsorname*/
            buff[i++] = c;
            while ((c = fgetc(mmpl)) != EOF) {
                if (isalphaordigit(c)) {
                    buff[i++] = c;
                    if(i>1025){
                        fprintf(stderr,"too long string");
                        return -1;
                    }
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
            num_attr = c;
            while ((c = fgetc(mmpl)) != EOF) {
                if (isdigit(c)) {
                    num_attr *= 10;
                    num_attr += c;
                    if(num_attr>32767){
                        fprintf(stderr,"too big");
                        return -1;
                    }
                } else if (isalpha(c)) {
                    fprintf(stderr, "error detected");
                    return -1;
                } else {
                    ungetc(c, mmpl);
                    return TNUMBER;
                }
            }
            if (c == EOF) {
                ungetc(c, mmpl);
                return TNUMBER;
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
        }else if(c=='\''){
            int f = 0;
            /*string*/
            int x;
            for(x=0; x<1024;x++){
                string_attr[x]='\0';
            }

            while ((c = fgetc(mmpl)) != EOF) {
                if (c=='\'') {
                    return TSTRING;
                }else if(c=='\n') {
                    fprintf(stderr," ' expected ");
                    return -1;
                }else{
                    string_attr[i++] = c;
                    if(i>1025){
                        fprintf(stderr,"too long string");
                        return -1;
                    }
                }
            }
            if (c == EOF) {
                ungetc(c, mmpl);
                return 1;
            }
        }
    }
    if(c == EOF){
        return -1;
    }
    int j = 0;
    for (j = 2; j < 50; j++) {
        if (strcmp(tokens[j], buff)==0) {
            return j;
        }
    }
    if(j==50){
        return TNAME;
    }
    return -1;
}
