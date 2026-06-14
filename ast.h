#ifndef __AST_H__
#define __AST_H__

#include <stddef.h>

typedef enum AstNodeKind {
	AstNodeKindProgram = 1,
	AstNodeKindFunctionCall,
	AstNodeKindLiteralString,
	AstNodeKindLiteralInteger,
	AstNodeKindLiteralFloat,
} AstNodeKind;

typedef struct AstNodeLiteralFloat {
	AstNodeKind kind;
	double value;
} AstNodeLiteralFloat;

typedef struct AstNodeLiteralInteger {
	AstNodeKind kind;
	int value;
} AstNodeLiteralInteger;

typedef struct AstNodeLiteralString {
	AstNodeKind kind;
	char *value;
} AstNodeLiteralString;

typedef struct AstNodeArguments {
	size_t length;
	size_t capacity;
	struct {
		AstNodeKind kind;
		union {
			AstNodeLiteralString literal_string;
			AstNodeLiteralInteger literal_integer;
			AstNodeLiteralFloat literal_float;
		} value;
	} *values;
} AstNodeArguments;

typedef struct AstNodeFunctionCall {
	AstNodeKind kind;
	char *name;
	bool global;
	AstNodeArguments *arguments;
} AstNodeFunctionCall;

typedef struct AstNode {
	AstNodeKind kind;
	size_t length;
	size_t capacity;
	union {
		struct {
			AstNodeKind kind;
			union {
				AstNodeFunctionCall function_call;
			} item;
		} *body;
	};
} AstNode;

bool check_global_identifiers(const char *name);

AstNodeArguments *make_ast_node_arguments();
void *push_ast_node_argument_float(AstNodeArguments *args, double value);
void *push_ast_node_argument_integer(AstNodeArguments *args, int value);
void *push_ast_node_argument_string(AstNodeArguments *args, char *value);

AstNodeFunctionCall *make_ast_node_function_call(AstNodeArguments *args, char *name);
void print_ast_node_function_call(AstNodeFunctionCall *fc);

AstNodeLiteralFloat *make_ast_node_literal_float(double value);
AstNodeLiteralInteger *make_ast_node_literal_integer(int value);
AstNodeLiteralString *make_ast_node_literal_string(char *value);

AstNode *make_ast();
void *push_ast_function_call(AstNode *ast, AstNodeFunctionCall *fc);
void print_ast(AstNode *ast);
void free_ast(AstNode *ast);

#endif
