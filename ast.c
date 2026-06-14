#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_global_identifiers(const char *name) {
	// NOTE: Assuming we have other reserved/global functions/keywords.
	const char *global[] = {"print"};

	for (size_t i = 0; i < sizeof(global) / sizeof(global[0]); ++i) {
		if (strcmp(name, global[i]) == 0) {
			return true;
		}
	}

	return false;
}

AstNodeArguments *make_ast_node_arguments() {
	AstNodeArguments *args = malloc(sizeof(AstNodeArguments));

	if (!args) {
		return NULL;
	}

	args->length = 0;
	args->capacity = 1;
	args->values = malloc(sizeof(*args->values) * args->capacity);

	if (!args->values) {
		free(args);
		return NULL;
	}

	return args;
}

void *push_ast_node_argument_float(AstNodeArguments *args, double value) {
	if (args->length >= args->capacity) {
		args->capacity *= 2;
		args->values = realloc(args->values, sizeof(*args->values) * args->capacity);
		if (!args->values) {
			free(args);
			return NULL;
		}
	}

	args->values[args->length].kind = AstNodeKindLiteralFloat;
	args->values[args->length].value.literal_float = *make_ast_node_literal_float(value);
	args->length++;

	return NULL;
}

void *push_ast_node_argument_integer(AstNodeArguments *args, int value) {
	if (args->length >= args->capacity) {
		args->capacity *= 2;
		args->values = realloc(args->values, sizeof(*args->values) * args->capacity);
		if (!args->values) {
			free(args);
			return NULL;
		}
	}

	args->values[args->length].kind = AstNodeKindLiteralInteger;
	args->values[args->length].value.literal_integer = *make_ast_node_literal_integer(value);
	args->length++;

	return NULL;
}

void *push_ast_node_argument_string(AstNodeArguments *args, char *value) {
	if (args->length >= args->capacity) {
		args->capacity *= 2;
		args->values = realloc(args->values, sizeof(*args->values) * args->capacity);
		if (!args->values) {
			free(args);
			return NULL;
		}
	}

	args->values[args->length].kind = AstNodeKindLiteralString;
	args->values[args->length].value.literal_string = *make_ast_node_literal_string(value);
	args->length++;

	return NULL;
}

AstNodeFunctionCall *make_ast_node_function_call(AstNodeArguments *args, char *name) {
	AstNodeFunctionCall *function_call = malloc(sizeof(AstNodeFunctionCall));
	if (!function_call) {
		return NULL;
	}

	function_call->kind = AstNodeKindFunctionCall;
	function_call->global = check_global_identifiers(name);
	function_call->name = name;
	function_call->arguments = args;

	return function_call;
}

void print_ast_node_function_call(AstNodeFunctionCall *fc) {
	puts("- FunctionCall: {kind, name, arguments}");
	printf("\tkind: %d\n", fc->kind);
	printf("\tname: %s\n", fc->name);
	printf("\tglobal: %d\n", fc->global);

	if (fc->arguments->length >= 1) {
		printf("\targuments: [%ld elements]\n", fc->arguments->length);

		for (size_t i = 0; i < fc->arguments->length; ++i) {
			AstNodeKind kind = fc->arguments->values[i].kind;
			printf("\t- kind: %d\n", kind);

			switch (kind) {
				case AstNodeKindLiteralFloat:
					printf("\t- value: %f\n", fc->arguments->values[i].value.literal_float.value);
					break;
				case AstNodeKindLiteralInteger:
					printf("\t- value: %d\n", fc->arguments->values[i].value.literal_integer.value);
					break;
				case AstNodeKindLiteralString:
					printf("\t- value: %s\n", fc->arguments->values[i].value.literal_string.value);
					break;
			}
		}
	}
}

AstNodeLiteralFloat *make_ast_node_literal_float(double value) {
	AstNodeLiteralFloat *literal_float = malloc(sizeof(AstNodeLiteralFloat));
	literal_float->kind = AstNodeKindLiteralFloat;
	literal_float->value = value;
	return literal_float;
}

AstNodeLiteralInteger *make_ast_node_literal_integer(int value) {
	AstNodeLiteralInteger *literal_integer = malloc(sizeof(AstNodeLiteralInteger));
	literal_integer->kind = AstNodeKindLiteralInteger;
	literal_integer->value = value;
	return literal_integer;
}

AstNodeLiteralString *make_ast_node_literal_string(char *value) {
	AstNodeLiteralString *literal_string = malloc(sizeof(AstNodeLiteralString));
	literal_string->kind = AstNodeKindLiteralString;
	literal_string->value = value;
	return literal_string;
}

AstNode *make_ast() {
	AstNode *ast = malloc(sizeof(AstNode));
	if (!ast) {
		return NULL;
	}

	ast->kind = AstNodeKindProgram;
	ast->length = 0;
	ast->capacity = 1;
	ast->body = malloc(sizeof(*ast->body) * ast->capacity);

	if (!ast->body) {
		free(ast);
		return NULL;
	}

	return ast;
}

void *push_ast_function_call(AstNode *ast, AstNodeFunctionCall *fc) {
	if (ast->length >= ast->capacity) {
		ast->capacity *= 2;
		ast->body = realloc(ast->body, sizeof(*ast->body) * ast->capacity);
		if (!ast->body) {
			free(ast);
			return NULL;
		}
	}

	ast->body[ast->length].kind = fc->kind;
	ast->body[ast->length].item.function_call = *fc;
	ast->length++;

	return NULL;
}

void print_ast(AstNode *ast) {
	printf("Program: {kind, body}\n");
	printf("kind: %d\n", ast->kind);

	if (ast->length >= 1) {
		printf("body: [%ld elements]\n", ast->length);

		for (size_t i = 0; i < ast->length; ++i) {
			AstNodeKind kind = ast->body[i].kind;
			switch (kind) {
				case AstNodeKindFunctionCall:
					print_ast_node_function_call(&ast->body[i].item.function_call);
					break;
			}
		}
	}
}

void free_ast(AstNode *ast) {
	free(ast->body);
	free(ast);
}
