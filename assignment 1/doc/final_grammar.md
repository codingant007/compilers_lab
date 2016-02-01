#GRAMMAR

```
stmt -> id ASSIGN expr
		| if expr then stmt
		| while expr do stmt
		| begin opt_stmts end

opt_stmts -> stmt_list | EPS
stmt_list -> stmt_list | EPS
expr -> sub_expr expr'
expr' -> EQ sub_expr | LT sub_expr | GT sub_expr
sub_expr -> term pm_expr
pm_expr -> MINUS sub_expr | plus_expr | EPS
plus_expr -> PLUS sub_expr
term -> factor mul_term
mul_term -> MUL term | div_term | EPS
div_term -> DIV term
factor -> NUM | ID | LP expr RP
```

//Note: In case of expressions of the form 5>(6==7), paranthesis are required to create a valid expression