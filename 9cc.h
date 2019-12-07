#include <stdbool.h>

int main(int argc, char **argv);
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);


// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 数字
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;
typedef struct Token Token;
// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;
};
// 現在着目しているトークン
extern Token *token;

typedef enum {
  ND_ADD,      // 加算
  ND_SUB,      // 減算
  ND_MUL,      // 乗算
  ND_DIV,      // 除算
  ND_EQU,      // 等価
  ND_NEQ,      // 不等価
  ND_LT,       // 未満
  ND_LE,       // 以下
  ND_NUM,      // 整数トークン
} NodeKind;
typedef struct Node Node;
struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool consume(char *op);
void expect(char *op);
int expect_number();

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

// 入力プログラム
extern char *user_input;

Token *tokenize(char *p);
bool startswith(char *p, char *q);

void gen(Node *node);
