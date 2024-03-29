// #include <ctype.h>
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// bool consume(char *op);
// void expect(char *op);
// int expect_number();

// // トークンの種類
// typedef enum {
//   TK_RESERVED, // 記号
//   TK_NUM,      // 数字
//   TK_EOF,      // 入力の終わりを表すトークン
// } TokenKind;

// typedef struct Token Token;

// // トークン型
// struct Token {
//   TokenKind kind; // トークンの型
//   Token *next;    // 次の入力トークン
//   int val;        // kindがTK_NUMの場合、その数値
//   char *str;      // トークン文字列
//   int len;
// };

// // 現在着目しているトークン
// Token *token;

// typedef enum {
//   ND_ADD,      // 加算
//   ND_SUB,      // 減算
//   ND_MUL,      // 乗算
//   ND_DIV,      // 除算
//   ND_EQU,      // 等価
//   ND_NEQ,      // 不等価
//   ND_LT,       // 未満
//   ND_LE,       // 以下
//   ND_NUM,      // 整数トークン
// } NodeKind;

// typedef struct Node Node;

// struct Node {
//   NodeKind kind;
//   Node *lhs;
//   Node *rhs;
//   int val;
// };

// Node *new_node(NodeKind kind, Node *lhs, Node *rhs) {
//   Node *node = calloc(1, sizeof(Node));
//   node->kind = kind;
//   node->lhs = lhs;
//   node->rhs = rhs;
//   return node;
// }

// Node *new_node_num(int val) {
//   Node *node = calloc(1, sizeof(Node));
//   node->kind = ND_NUM;
//   node->val = val;
//   return node;
// }

// Node *expr();
// Node *equality();
// Node *relational();
// Node *add();
// Node *mul();
// Node *unary();
// Node *primary();

// Node *expr(){
//   Node *node = equality();
//   return node;
// }

// Node *equality(){
//   Node *node = relational();
//   for(;;){
//     if (consume("=="))
//       node = new_node(ND_EQU, node, relational());
//     else if (consume("!="))
//       node = new_node(ND_NEQ, node, relational());
//     else
//       return node;
//   }
// }

// Node *relational(){
//   Node *node = add();
//   for(;;){
//     if (consume("<"))
//       node = new_node(ND_LT, node, add());
//     else if (consume("<="))
//       node = new_node(ND_LE, node, add());
//     else if (consume(">"))
//       node = new_node(ND_LT, add(), node);
//     else if (consume(">="))
//       node = new_node(ND_LE, add(), node);
//     return node;
//   }
// }

// Node *add(){
//   Node *node = mul();
//   for(;;){
//     if (consume("+"))
//       node = new_node(ND_ADD, node, mul());
//     else if (consume("-"))
//       node = new_node(ND_SUB, node, mul());
//     else 
//       return node;
//   }
// }

// Node *mul(){
//   Node *node = unary();
//   for(;;){
//     if (consume("*"))
//       node = new_node(ND_MUL, node, unary());
//     else if (consume("/"))
//       node = new_node(ND_DIV, node, unary());
//     else
//       return node;
//   }
// }

// Node *unary(){
//     if (consume("+"))
//       return primary();
//     if (consume("-"))
//       return new_node(ND_SUB, new_node_num(0), primary());
//     return primary();
// }

// Node *primary(){
//   if(consume("(")){
//     Node *node = expr();
//     expect(")");
//     return node;
//   }
//   return new_node_num(expect_number());
// }

// // 入力プログラム
// char *user_input;

// // エラーを報告するための関数
// // printfと同じ引数を取る
// // エラー箇所を報告する
// void error_at(char *loc, char *fmt, ...) {
//   va_list ap;
//   va_start(ap, fmt);

//   int pos = loc - user_input;
//   fprintf(stderr, "%s\n", user_input);
//   fprintf(stderr, "%*s", pos, ""); // pos個の空白を出力
//   fprintf(stderr, "^ ");
//   vfprintf(stderr, fmt, ap);
//   fprintf(stderr, "\n");
//   exit(1);
// }

// // Reports an error and exit.
// void error(char *fmt, ...) {
//   va_list ap;
//   va_start(ap, fmt);
//   vfprintf(stderr, fmt, ap);
//   fprintf(stderr, "\n");
//   exit(1);
// }

// // 次のトークンが期待している記号のときには、トークンを1つ読み進めて
// // 真を返す。それ以外の場合には偽を返す。
// bool consume(char *op) {
//   if (token->kind != TK_RESERVED || token->len != strlen(op) || memcmp(token->str, op, token->len))
//     return false;
//   token = token->next;
//   return true;
// }

// // 次のトークンが期待している記号のときには、トークンを1つ読み進める。
// // それ以外の場合にはエラーを報告する。
// void expect(char *op) {
//   if (token->kind != TK_RESERVED || token->len != strlen(op) || memcmp(token->str, op, token->len))
//     error_at(token->str, "'%c'ではありません", op);
//   token = token->next;
// }

// // 次のトークンが数値の場合、トークンを1つ読み進めてその数値を返す。
// // それ以外の場合にはエラーを報告する。
// int expect_number() {
//   if (token->kind != TK_NUM)
//     error_at(token->str, "数ではありません");
//   int val = token->val;
//   token = token->next;
//   return val;
// }

// bool at_eof() {
//   return token->kind == TK_EOF;
// }

// // 新しいトークンを作成してcurに繋げる
// Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
//   Token *tok = calloc(1, sizeof(Token));
//   tok->kind = kind;
//   tok->str = str;
//   tok->len = len;
//   cur->next = tok;
//   return tok;
// }

// bool startswith(char *p, char *q){
//   return memcmp(p, q, strlen(q)) == 0;
// }

// // 入力文字列pをトークナイズしてそれを返す
// Token *tokenize(char *p) {
//   Token head;
//   head.next = NULL;
//   Token *cur = &head;

//   while (*p) {
//     // 空白文字をスキップ
//     if (isspace(*p)) {
//       p++;
//       continue;
//     }

//     if (startswith(p, "==") || startswith(p, "!=") ||
//         startswith(p, "<=") || startswith(p, ">=")){
//       cur = new_token(TK_RESERVED, cur, p++, 2);
//       p++;
//       continue;
//     }

//     if (strchr("+-*/()<>", *p)){
//       cur = new_token(TK_RESERVED, cur, p++, 1);
//       continue;
//     }

//     if (isdigit(*p)) {
//       cur = new_token(TK_NUM, cur, p, 0);
//       char *q = p;
//       cur->val = strtol(p, &p, 10);
//       cur->len = p - q;
//       continue;
//     }

//     error_at(cur->str, "トークナイズできません");
//   }

//   new_token(TK_EOF, cur, p, 0);
//   return head.next;
// }

// void gen(Node *node){
//   if (node->kind == ND_NUM){
//     printf("  push %d\n", node->val);
//     return;
//   }

//   gen(node->lhs);
//   gen(node->rhs);

//   printf("  pop rdi\n");
//   printf("  pop rax\n");

//   switch (node->kind) {
//     case ND_ADD:
//       printf("  add rax, rdi\n");
//       break;
//     case ND_SUB:
//       printf("  sub rax, rdi\n");
//       break;
//     case ND_MUL:
//       printf("  imul rax, rdi\n");
//       break;
//     case ND_DIV:
//       printf("  cqo\n");
//       printf("  idiv rdi\n");
//       break;
//     case ND_EQU:
//       printf("  cmp rax, rdi\n");
//       printf("  sete al\n");
//       printf("  movzb rax, al\n");
//       break;
//     case ND_NEQ:
//       printf("  cmp rax, rdi\n");
//       printf("  setne al\n");
//       printf("  movzb rax, al\n");
//       break;
//     case ND_LT:
//       printf("  cmp rax, rdi\n");
//       printf("  setl al\n");
//       printf("  movzb rax, al\n");
//       break;
//     case ND_LE:
//       printf("  cmp rax, rdi\n");
//       printf("  setle al\n");
//       printf("  movzb rax, al\n");
//       break;
//   }

//   printf("  push rax\n");
// }

// int main(int argc, char **argv) {
//   if (argc != 2) {
//     error("引数の個数が正しくありません");
//     return 1;
//   }

//   user_input = argv[1];
//   // トークナイズする
//   token = tokenize(user_input);
//   // トークンから構文木を作る
//   Node *node = expr();

//   // アセンブリの前半部分を出力
//   printf(".intel_syntax noprefix\n");
//   printf(".global main\n");
//   printf("main:\n");

//   // 抽象構文木を下りながらコード生成
//   gen(node);

//   //スタックトップに式全体の値が残っているはずなので
//   //それをRAXにロードして関数からの返り値とする
//   printf("  pop rax\n");
//   printf("  ret\n");
//   return 0;
// }