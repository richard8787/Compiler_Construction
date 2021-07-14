/*	Definition section */
%{
    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
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
        }
        else
            printf("error:%d: %s redeclared in this block. previous declaration at line %d\n",yylineno,Name_insert,the_lineno);
    };

    static void lookup_symbol(char* input_string){
        int the_address = -1;
        for(int i=0 ;i <= scope_level;i++)
        {
            for(int j=0;j < Index_con[i];j++)
            {
                if(!strcmp(input_string,table_list[i][j].Name))
                {    
                    the_address = table_list[i][j].Address;
                }
            }
        }
        if(the_address != -1)
            printf("IDENT (name=%s, address=%d)\n",input_string, the_address);
        else
            printf("error:%d: undefined: %s\n",yylineno,input_string);
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
            return 'I';
        else if(!strcmp(temp_type,"float"))
            return 'F';
        else if(!strcmp(temp_type,"string"))
            return 'S';
        else if(!strcmp(temp_type,"bool"))
            return 'B';
        else
            return 'W';
    };

    static void dump_symbol(/* ... */){
        printf("> Dump symbol table (scope level: %d)\n",scope_level);
        printf("%-10s%-10s%-10s%-10s%-10s%s\n", "Index", "Name", "Type", "Address", "Lineno", "Element type");
        for(int i=0; i<Index_con[scope_level] ;i++)
            printf("%-10d%-10s%-10s%-10d%-10d%s\n",table_list[scope_level][i].Index, table_list[scope_level][i].Name, table_list[scope_level][i].TypeS, table_list[scope_level][i].Address, table_list[scope_level][i].Lineno, table_list[scope_level][i].Element);
        Index_con[scope_level]=0;
    };

%}

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */


%union {
    int i_val;
    float f_val;
    char *s_val;
    bool b_val;

    struct ctr{
        char* id_name;
        char id_type[20];
    }ctr;
}

/* Token without return */
%token INT FLOAT BOOL STRING
%token SEMICOLON 
%token INC DEC GEQ LEQ EQL NEQ ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN
%token QUO_ASSIGN REM_ASSIGN AND OR LPAREN RPAREN LBRACK RBRACK
%token LBRACE RBRACE COMMA QUOTA RETURN IF ELSE FOR WHILE
%token TRUE FALSE CONTINUE BREAK VOID PRINT IDENT

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT
%token <b_val> BOOL_LIT

/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type TypeName ExpressionExpr IncDecExpr IDENT Expression DeclarationStmt
%type <s_val> UnaryExpr unary_op mul_op add_op cmp_op AA BB CC DD EE AssignmetExpr assign_op
%type <s_val> PrimaryExpr Operand IndexExpr Literal ConversionExpr PrintStmt
/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : StatementList { dump_symbol();}
;

Type
    : TypeName { $$ = $1;}
;

TypeName
    : INT { $$ = "I";}
    | FLOAT{ $$ = "F";}
    | STRING{ $$ = "S";}
    | BOOL{ $$ = "B";}
;

Expression
    : Expression OR AA { printf("OR\n"); print_type = 0; $$ = "B";}
    | AA { $$ = $1;}
;

AA
    : AA AND BB { printf("AND\n");}
    | BB { $$ = $1;}
;

BB
    : BB cmp_op CC { printf("%s\n",$2);}
    | CC { $$ = $1;}
;

CC
    : CC add_op DD { printf("%s\n",$2);}
    | DD { $$ = $1;}
;

DD
    : DD mul_op EE { printf("%s\n",$2);}
    | EE { $$ = $1;}
;

EE
    : UnaryExpr { $$ = $1;}
;

UnaryExpr
    : PrimaryExpr { $$ = $1;}
    | unary_op UnaryExpr { printf("%s\n",$1);}
;

binary_op
    : OR { printf("OR\n");}
    | AND { printf("AND\n");}
    | cmp_op
    | add_op
    | mul_op
;

cmp_op
    : EQL{ $$ ="EQL";}
    | NEQ{ $$ ="NEQ";}
    | '<'{ $$ ="LSS";}
    | LEQ{ $$ ="LEQ";}
    | '>'{ $$ ="GTR";}
    | GEQ{ $$ ="GEQ";}
;

add_op
    : '+'{ $$ ="ADD";}
    | '-'{ $$ ="SUB";}
;

mul_op
    : '*'{ $$ ="MUL";}
    | '/'{ $$ ="QUO";}
    | '%'{ $$ ="REM";}
;

unary_op
    : '+' { $$ = "POS";}
    | '-' { $$ = "NEG";}
    | '!' { $$ = "NOT";}
;

PrimaryExpr
    : Operand { $$ = $1;}
    | IndexExpr
    | ConversionExpr
;

Operand
    : Literal { $$ = $1;}
    | IDENT {
        lookup_symbol(yylval.ctr.id_name);
        $$ = $1; 
        lookup_symbol_IDENTtype(yylval.ctr.id_name);
    }
    | LPAREN Expression RPAREN
;

Literal
    : INT_LIT {
        printf("INT_LIT %d\n", $<i_val>$);
        print_type = 1;
        $$ = "I";
    }
    | FLOAT_LIT {
        printf("FLOAT_LIT %f\n", $<f_val>$);
        print_type = 2;
        $$ = "F";
    }
    | STRING_LIT {
        printf("STRING_LIT %s\n", $<s_val>$);
        print_type = 3;
        $$ = "S";
    }
    | BOOL_LIT {
        if($<b_val>$)
            printf("TRUE\n");
        else
            printf("FALSE\n");
        print_type = 0;
        $$ = "B";
    }
;

IndexExpr
    : PrimaryExpr LBRACK Expression RBRACK { $$ = $1; lookup_symbol_arraytype($1);}
;

ConversionExpr
    : LPAREN Type RPAREN IDENT {
        lookup_symbol($4);
        printf("%c to %s\n", lookup_symbol_conversiontype($4), $2);
    }
    | LPAREN Type RPAREN Literal {
        printf("%s to %s\n", $4, $2);
    }
;

Statement
    : DeclarationStmt
    | AssignmetStmt
    | IncDecStmt
    | Block
    | IfStmt
    | WhileStmt
    | ForStmt
    | PrintStmt
    | ExpressionStmt
;

ExpressionExpr
    : IDENT '+' IDENT {
        lookup_symbol($1);
        lookup_symbol($3);
        printf("ADD\n");
    }
    | IDENT '-' IDENT {
        lookup_symbol($1);
        lookup_symbol($3);
        printf("SUB\n");
    }
    | IDENT '*' IDENT {
        lookup_symbol($1);
        lookup_symbol($3);
        printf("MUL\n");
    }
    | IDENT '/' IDENT {
        lookup_symbol($1);
        lookup_symbol($3);
        printf("QUO\n");
    }
    | IDENT '%' IDENT {
        lookup_symbol($1);
        lookup_symbol($3);
        printf("REM\n");
    }
;
ExpressionStmt
    : ExpressionExpr SEMICOLON
;

DeclarationStmt
    : Type IDENT {strcpy(tempstring,yylval.ctr.id_name);} '=' Expression SEMICOLON{
        insert_symbol(tempstring, yylval.ctr.id_type, "-");
    }
    | Type IDENT SEMICOLON{
        insert_symbol(yylval.ctr.id_name, yylval.ctr.id_type, "-");
    }
    | Type IDENT { strcpy(tempstring,yylval.ctr.id_name);} LBRACK Expression RBRACK SEMICOLON {
        insert_symbol(tempstring, "array" , yylval.ctr.id_type);
    }
;

AssignmetExpr
    : Expression assign_op Expression {
            char t = lookup_symbol_conversiontype($3);
            char tout[20];
            if(t == 'I')
                strcpy(tout,"int");
            if(t == 'F')
                strcpy(tout,"float");
            if(t == 'S')
                strcpy(tout,"string");
            if(t == 'B')
                strcpy(tout,"bool");
            if(t == 'W')
                strcpy(tout,"wrong");
            if(!strcmp($1,"I") || !strcmp($1,"F") ||!strcmp($1,"S") || !strcmp($1,"B"))
                printf("error:%d: cannot assign to %s\n",yylineno,tout);
            printf("%s\n",$2); 
        }
;

AssignmetStmt
    : AssignmetExpr SEMICOLON
;

assign_op
    : '=' { $$ = "ASSIGN";}
    | ADD_ASSIGN { $$ = "ADD_ASSIGN";}
    | SUB_ASSIGN { $$ = "SUB_ASSIGN";}
    | MUL_ASSIGN { $$ = "MUL_ASSIGN";}
    | QUO_ASSIGN { $$ = "QUO_ASSIGN";}
    | REM_ASSIGN { $$ = "REM_ASSIGN";}
;

IncDecExpr
    : Expression INC { printf("INC\n");}
    | Expression DEC { printf("DEC\n");}
;

IncDecStmt
    : IncDecExpr SEMICOLON
;

Block
    : LBRACE { scope_level++;} StatementList { dump_symbol(); scope_level--;} RBRACE
;

StatementList
    : Statement StatementList
    | Statement
;

IfStmt
    : IF Condition Block
    | IF Condition Block ELSE IfStmt
    | IF Condition Block ELSE Block
;

Condition
    : Expression
;

WhileStmt
    : WHILE LPAREN Condition RPAREN Block
;

ForStmt
    : FOR LPAREN ForClause RPAREN Block
;

ForClause
    : InitStmt SEMICOLON Condition SEMICOLON PostStmt
;

InitStmt
    : SimpleExpr
;

PostStmt
    : SimpleExpr
;

SimpleExpr
    : AssignmetExpr
    | Expression
    | IncDecExpr
;

PrintStmt
    : PRINT LPAREN Expression RPAREN SEMICOLON {
        if(print_type == 0 )
            printf("PRINT bool\n");
        if(print_type == 1 )
            printf("PRINT int\n");
        if(print_type == 2 )
            printf("PRINT float\n");
        if(print_type == 3 )
            printf("PRINT string\n");
        
        /*
        if(!strcmp($3 ,"B") )
            printf("PRINT bool\n");
        else if(!strcmp($3 ,"I") )
            printf("PRINT int\n");
        else if(!strcmp($3 ,"F") )
            printf("PRINT float\n");
        else if(!strcmp($3 ,"S") )
            printf("PRINT string\n");
        else{
            if(lookup_symbol_conversiontype($3) == 'B')
                printf("PRINT bool\n");
            else if(lookup_symbol_conversiontype($3) == 'I')
                printf("PRINT int\n");
            else if(lookup_symbol_conversiontype($3) == 'F')
                printf("PRINT float\n");
            else if(lookup_symbol_conversiontype($3) == 'S')
                printf("PRINT string\n");
            else
                lookup_symbol_arraytype_print($3);
        }
        */
    }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}