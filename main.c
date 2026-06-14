#include "ast.h"

int main(void) {

	AstNodeArguments *f_args = make_ast_node_arguments();
	push_ast_node_argument_float(f_args, 0.12);
	AstNodeFunctionCall *print1 = make_ast_node_function_call(f_args, "print");

	AstNodeArguments *i_args = make_ast_node_arguments();
	push_ast_node_argument_integer(i_args, 12);
	AstNodeFunctionCall *print2 = make_ast_node_function_call(i_args, "print");

	AstNodeArguments *s_args = make_ast_node_arguments();
	push_ast_node_argument_string(s_args, "Hello, World!");
	AstNodeFunctionCall *print3 = make_ast_node_function_call(s_args, "print");

	AstNode *ast = make_ast();
	push_ast_function_call(ast, print1);
	push_ast_function_call(ast, print2);
	push_ast_function_call(ast, print3);
	print_ast(ast);
	free_ast(ast);

	return 0;
}
