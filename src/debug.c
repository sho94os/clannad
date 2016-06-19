#include <stdarg.h>
#include <stdio.h>
#include "clannad.h"

void
indented_printf(int indent, const char *format, ...)
{
  for (int i = 0; i < indent; i++) printf("  ");
  va_list list;
  va_start(list, format);
  vprintf(format, list);
  va_end(list);
}

void
indented_puts(int indent, const char *str)
{
  indented_printf(indent, "%s\n", str);
}

void
indented_putc(int indent, const char c)
{
  indented_printf(indent, "%c\n", c);
}

char*
kind_label(enum NodeKind type)
{
  switch (type) {
    case NODE_ROOT:
      return "NODE_ROOT";
    case NODE_FUNC:
      return "NODE_FUNC";
    case NODE_FUNC_DECL:
      return "NODE_FUNC_DECL";
    case NODE_PARAM_DECL:
      return "NODE_PARAM_DECL";
    case NODE_VAR_DECL:
      return "NODE_VAR_DECL";
    case NODE_FUNCALL:
      return "NODE_FUNCALL";
    case NODE_TYPE:
      return "NODE_TYPE";
    case NODE_PTR:
      return "NODE_PTR";
    case NODE_SPEC:
      return "NODE_SPEC";
    case NODE_FUNC_SPEC:
      return "NODE_FUNC_SPEC";
    case NODE_COMPOUND_STMT:
      return "NODE_COMPOUND_STMT";
    case NODE_RETURN:
      return "NODE_RETURN";
    case NODE_IDENTIFIER:
      return "NODE_IDENTIFIER";
    case NODE_INTEGER:
      return "NODE_INTEGER";
    case NODE_STRING:
      return "NODE_STRING";
    case NODE_BINOP:
      return "NODE_BINOP";
    default:
      fprintf(stderr, "kind_label is not defined for %d\n", type);
      return "NODE_UNSUPPORTED";
  }
}

void dump_node(int indent, Node *node);

void
dump_vector(int indent, Vector *vec)
{
  for (int i = 0; i < vec->length; i++) {
    dump_node(indent, (Node *)vector_get(vec, i));
  }
}

void
dump_nodes(int indent, int argc, ...)
{
  va_list list;
  va_start(list, argc);
  for (int i = 0; i < argc; i++) dump_node(indent, va_arg(list, Node *));
  va_end(list);
}

void
dump_node(int indent, Node *node)
{
  switch (node->kind) {
    case NODE_ROOT:
    case NODE_COMPOUND_STMT:
      indented_puts(indent, kind_label(node->kind));
      dump_vector(indent + 1, node->children);
      break;
    case NODE_PTR:
    case NODE_RETURN:
      indented_puts(indent, kind_label(node->kind));
      if (node->param) dump_node(indent + 1, node->param);
      break;
    case NODE_FUNC:
      indented_puts(indent, kind_label(node->kind));
      dump_nodes(indent + 1, 3, node->type, node->decl, node->stmts);
      break;
    case NODE_FUNC_DECL:
    case NODE_PARAM_DECL:
    case NODE_VAR_DECL:
      indented_puts(indent, kind_label(node->kind));
      dump_nodes(indent + 1, 2, node->type, node->decl);
      break;
    case NODE_FUNCALL:
    case NODE_FUNC_SPEC:
      indented_puts(indent, kind_label(node->kind));
      dump_node(indent + 1, node->func);
      dump_vector(indent + 1, node->params);
      break;
    case NODE_IDENTIFIER:
    case NODE_SPEC:
    case NODE_TYPE:
    case NODE_STRING:
      indented_printf(indent, "%s id=%s\n", kind_label(node->kind), node->id);
      break;
    case NODE_INTEGER:
      indented_printf(indent, "%s ival=%d\n", kind_label(node->kind), node->ival);
      break;
    case NODE_BINOP:
      indented_printf(indent, "%s %c\n", kind_label(node->kind), node->op);
      dump_node(indent + 1, node->lhs);
      dump_node(indent + 1, node->rhs);
      break;
    default:
      indented_puts(indent, kind_label(node->kind));
      break;
  }
}

void
dump_ast(Node *ast)
{
  dump_node(0, ast);
}
