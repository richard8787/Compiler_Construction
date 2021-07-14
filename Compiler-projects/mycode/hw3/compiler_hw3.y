/*	Definition section */
%{
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
    : INT { $$ = "i";}
    | FLOAT{ $$ = "f";}
    | STRING{ $$ = "s";}
    | BOOL{ $$ = "b";}
;

Expression
    : Expression OR AA { printf("OR\n"); codegen("ior\n"); print_type = 0; $$ = "B";}
    | AA { $$ = $1;}
;

AA
    : AA AND BB { printf("AND\n");codegen("iand\n");}
    | BB { $$ = $1;}
;

BB
    : BB cmp_op CC 
    { 
        printf("%s\n",$2);
        if(get_type()=='i')
        {
            if($2=="EQL")
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
            if($2 == "GTR")
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
            if($2 == "LEQ")
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
            if($2 == "GTR")
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
    | CC { $$ = $1;}
;

CC
    : CC add_op DD { printf("%s\n",$2);codegen("%c%s\n",get_type(),$2);}
    | DD { $$ = $1;}
;

DD
    : DD mul_op EE { printf("%s\n",$2);codegen("%c%s\n",get_type(),$2);}
    | EE { $$ = $1;}
;

EE
    : UnaryExpr { $$ = $1;}
;

UnaryExpr
    : PrimaryExpr { $$ = $1;}
    | unary_op UnaryExpr 
    { 
        printf("%s\n",$1);
        if($1 == "neg")
            codegen("%c%s\n",get_type(),$1);
        if($1 == "not")
            {
                codegen("iconst_1 ;load true for not\n");
                codegen("ixor\n");
            }
    }
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
    : '+'{ $$ ="add";}
    | '-'{ $$ ="sub";}
;

mul_op
    : '*'{ $$ ="mul";}
    | '/'{ $$ ="div";}
    | '%'{ $$ ="rem";}
;

unary_op
    : '+' { $$ = "pos";}
    | '-' { $$ = "neg";}
    | '!' { $$ = "not";}
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
        $$ = lookup_symbol_codegen_type(yylval.ctr.id_name);
        lookup_symbol_IDENTtype(yylval.ctr.id_name);
    }
    | LPAREN Expression RPAREN
;

Literal
    : INT_LIT {
        printf("INT_LIT %d\n", $<i_val>$);
        codegen("ldc %d\n",$<i_val>$);
        print_type = 1;
        pre_intlit = $<i_val>$;
        $$ = "i";
    }
    | FLOAT_LIT {
        printf("FLOAT_LIT %f\n", $<f_val>$);
        codegen("ldc %f\n",$<f_val>$);
        print_type = 2;
        $$ = "f";
    }
    | STRING_LIT {
        printf("STRING_LIT %s\n", $<s_val>$);
        codegen("ldc \"%s\"\n",$<s_val>$);
        print_type = 3;
        $$ = "s";
    }
    | BOOL_LIT {
        if($<b_val>$)
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
        $$ = "b";
    }
;

IndexExpr
    : PrimaryExpr LBRACK Expression RBRACK 
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
;

ConversionExpr
    : LPAREN Type RPAREN IDENT {
        lookup_symbol($4);
        printf("%c to %s\n", lookup_symbol_conversiontype($4), $2);
        codegen("%c2%s\n", lookup_symbol_conversiontype($4), $2);

        if(!strcmp($2,"i"))
        {
            print_type=1;
        }

        if(!strcmp($2,"f"))
        {
            print_type=2;
        }
        conver_flag = true;
    }
    | LPAREN Type RPAREN Literal {
        printf("%s to %s\n", $4, $2);
        codegen("%s2%s\n", $4,$2);
        if(!strcmp($2,"i"))
        {
            print_type=1;
        }

        if(!strcmp($2,"f"))
        {
            print_type=2;
        }
        conver_flag = true;
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
        if(yylval.ctr.id_type[0]=='b')
            codegen("istore %d\n",addno);
        else if(yylval.ctr.id_type[0]=='s')
            codegen("astore %d\n",addno);
        else
            codegen("%cstore %d\n",yylval.ctr.id_type[0],addno);
        
        insert_symbol(tempstring, yylval.ctr.id_type, "-");
    }

    | Type IDENT SEMICOLON{
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

    | Type IDENT { strcpy(tempstring,yylval.ctr.id_name);} LBRACK Expression RBRACK SEMICOLON {
        insert_symbol(tempstring, "array" , yylval.ctr.id_type);
    }
;

AssignmetExpr
    : Expression assign_op Expression {
            if($2 == "ASSIGN")
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
            if($2 == "ADD_ASSIGN")
            {
                codegen("%cadd\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
                
            }
            if($2 == "SUB_ASSIGN")
            {
                codegen("%csub\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if($2 == "MUL_ASSIGN")
            {
                codegen("%cmul\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if($2 == "QUO_ASSIGN")
            {
                codegen("%cdiv\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
            if($2 == "REM_ASSIGN")
            {
                codegen("%crem\n",get_type());
                codegen("%cstore %d\n",get_type(),preload_no);
            }
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
    : Expression INC 
    { 
        printf("INC\n");
        if($1 == 'i')
            codegen("ldc 1\n");
        else
            codegen("ldc 1.0\n");
        codegen("%cadd\n",get_type());
        codegen("%cstore %d\n",get_type(),preload_no);
        in_dec = 1;
    }
    | Expression DEC 
    { 
        printf("DEC\n");
        if($1 == 'i')
            codegen("ldc 1\n");
        else
            codegen("ldc 1.0\n");
        codegen("%csub\n",get_type());
        codegen("%cstore %d\n",get_type(),preload_no);
        in_dec = 0;
    }
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
    : WHILE LPAREN 
    {
        if(wh_flag)
            codegen("L_for_begin%d :\n",scope_level);
        else
            codegen("L_for_begin%d :\n",scope_level+10);
    } 
    Condition 
    {   
        if(wh_flag)
            codegen("ifeq L_for_exit%d\n",scope_level);
        else
            codegen("ifeq L_for_exit%d\n",scope_level+10);
    } 
    RPAREN Block
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
;

ForStmt
    : FOR LPAREN ForClause RPAREN
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
    Block
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
    {
        codegen("goto for_begin\n");
        codegen("for_exit :\n");
    }
;

ForClause
    : InitStmt SEMICOLON
    {
        codegen("for_begin :\n");
    } 
    Condition 
    {
        codegen("ifeq for_exit\n");
    }
    SEMICOLON PostStmt
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