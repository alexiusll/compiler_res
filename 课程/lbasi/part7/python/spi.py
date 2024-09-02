'''
Author: linkenzone
Date: 2023-08-16 11:43:41
Descripttion: 
这一节重点看这个文件
SPI - Simple Pascal Interprete （简单的 Pascal 解释器）
'''

#*##############################################################################
#*                                                                             #
#*  LEXER  词法分析器（lexical analyzer）                                       #
#*                                                                             #
#*##############################################################################

#* Token types
#* EOF（文件结束）标记用于指示在词法分析中没有更多的输入可供处理。
#* 元组（tuple）赋值语法: 每个标记都是一个字符串常量，用于表示不同类型的词法单元。
INTEGER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, EOF = (
    'INTEGER', 'PLUS', 'MINUS', 'MUL', 'DIV', '(', ')', 'EOF'
)

class Token(object):
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def __str__(self):
        """
        类实例的字符串表示.
        Examples:
            Token(INTEGER, 3)
            Token(PLUS, '+')
            Token(MUL, '*')
        """
        return 'Token({type}, {value})'.format(
            type=self.type,
            value=repr(self.value)
        )

    def __repr__(self):
        return self.__str__()

class Lexer(object):
    def __init__(self, text):
        #* 客户端字符串输入, 例如. "4 + 2 * 3 - 6 / 2"
        self.text = text
        #* self.pos 是 self.text 的索引
        self.pos = 0
        self.current_char = self.text[self.pos] #* 指针

    def error(self):
        raise Exception('Invalid character')

    def advance(self):
        """推进 `pos` 指针并设置 `current_char` 变量。"""
        self.pos += 1
        if self.pos > len(self.text) - 1:
            self.current_char = None  # Indicates end of input
        else:
            self.current_char = self.text[self.pos]

    def skip_whitespace(self): #* 去掉空格
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def integer(self):
        """返回一个从输入中 的（多位）整数。"""
        result = ''
        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()
        return int(result)

    def get_next_token(self):
        """
        词法分析器（也称为扫描器或标记器）
        该方法负责将一句话拆分成标记，一次一个标记。
        """
        while self.current_char is not None:

            if self.current_char.isspace():
                self.skip_whitespace()
                continue

            if self.current_char.isdigit():
                return Token(INTEGER, self.integer())

            if self.current_char == '+':
                self.advance()
                return Token(PLUS, '+')

            if self.current_char == '-':
                self.advance()
                return Token(MINUS, '-')

            if self.current_char == '*':
                self.advance()
                return Token(MUL, '*')

            if self.current_char == '/':
                self.advance()
                return Token(DIV, '/')

            if self.current_char == '(':
                self.advance()
                return Token(LPAREN, '(')

            if self.current_char == ')':
                self.advance()
                return Token(RPAREN, ')')

            self.error()

        return Token(EOF, None)


#*##############################################################################
#*                                                                             #
#*  PARSER   解析器                                                             #
#*                                                                             #
#*##############################################################################

#* 编译器中的解析器（Parser）是编译器的一个关键组件，负责将源代码（通常是文本形式）转换为抽象语法树（Abstract Syntax Tree，AST）
#* 或其他类似的中间表示形式。解析器的主要任务是理解源代码的语法结构，检查其是否符合编程语言的语法规则，
#* 并将其转化为一种更容易处理的内部表示形式，以便进行进一步的编译或解释。

#* 首先，我们将创建一个名为 "AST" 的基本节点类，其他类将从这个类继承：
class AST(object):
    pass

#* 我们本可以创建一个单独的类来表示每个运算符，比如AddNode、SubNode、MulNode和DivNode，
#* 但实际上我们只会 创建一个BinOp类 来表示这四个二元运算符（二元运算符是对两个操作数进行操作的运算符）
class BinOp(AST):
    #* 构造函数的参数是 left、op 和 right，其中 left 和 right 分别指向左操作数和右操作数的节点。
    #* op 保存操作符本身的令牌：对于加法运算符是 Token(PLUS, '+')，对于减法运算符是 Token(MINUS, '-')，依此类推。
    def __init__(self, left, op, right):
        self.left = left
        self.token = self.op = op
        self.right = right

#* 为了在我们的AST中表示整数，我们将定义一个名为 "Num" 的类，它将保存一个整数令牌和令牌的值：
class Num(AST):
    def __init__(self, token):
        self.token = token
        self.value = token.value

#* 它在识别输入（一个算术表达式）后构建并返回一个AST：（通过递归的方式进行解析）
class Parser(object):
    def __init__(self, lexer):
        self.lexer = lexer  #* 设置词法分析器对象
        self.current_token = self.lexer.get_next_token() #* 将当前标记设为从输入中提取的第一个标记

    def error(self):
        raise Exception('Invalid syntax')

    def eat(self, token_type):
        #* 将当前的令牌类型与传递的令牌类型进行比较，如果它们匹配，然后 "消耗" 当前令牌
        #* 并将下一个令牌分配给 self.current_token，否则引发一个异常。
        if self.current_token.type == token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            self.error()

    def factor(self):
        #* 其中终结符LPAREN表示左括号 '（'，终结符RPAREN表示右括号 '）'，而括号内的非终结符expr指的是expr规则。
        """factor : INTEGER | LPAREN expr RPAREN"""
        token = self.current_token
        if token.type == INTEGER:
            self.eat(INTEGER)
            return Num(token)
        elif token.type == LPAREN:
            self.eat(LPAREN)
            node = self.expr()
            self.eat(RPAREN)
            return node

    def term(self):
        """term : factor ((MUL | DIV) factor)*"""
        node = self.factor()
        while self.current_token.type in (MUL, DIV):
            token = self.current_token
            if token.type == MUL:
                self.eat(MUL)
            elif token.type == DIV:
                self.eat(DIV)

            node = BinOp(left=node, op=token, right=self.factor())
        return node

    def expr(self):
        """
        expr   : term ((PLUS | MINUS) term)*
        term   : factor ((MUL | DIV) factor)*
        factor : INTEGER | LPAREN expr RPAREN
        """
        node = self.term()

        while self.current_token.type in (PLUS, MINUS):
            token = self.current_token
            if token.type == PLUS:
                self.eat(PLUS)
            elif token.type == MINUS:
                self.eat(MINUS)

            node = BinOp(left=node, op=token, right=self.term())

        return node

    def parse(self):
        return self.expr()


#*##############################################################################
#*                                                                             #
#*  INTERPRETER 解释器                                                         #
#*                                                                             #
#*##############################################################################

#* 以下是实现 访问者模式 的源代码
class NodeVisitor(object):
    def visit(self, node):
        method_name = 'visit_' + type(node).__name__
        visitor = getattr(self, method_name, self.generic_visit)
        return visitor(node)

    def generic_visit(self, node):
        raise Exception('No visit_{} method'.format(type(node).__name__))

#* 这是我们的 Interpreter 类的源代码，它继承自 NodeVisitor 类，
#* 并实现了具有 visit_NodeType 形式的不同方法，其中 NodeType 被替换为节点的类名，比如 BinOp、Num 等等：
class Interpreter(NodeVisitor):
    def __init__(self, parser):
        self.parser = parser

    def visit_BinOp(self, node):
        if node.op.type == PLUS:
            return self.visit(node.left) + self.visit(node.right)
        elif node.op.type == MINUS:
            return self.visit(node.left) - self.visit(node.right)
        elif node.op.type == MUL:
            return self.visit(node.left) * self.visit(node.right)
        elif node.op.type == DIV:
            return self.visit(node.left) // self.visit(node.right)

    def visit_Num(self, node):
        return node.value

    def interpret(self):
        tree = self.parser.parse()
        return self.visit(tree)


def main():
    while True:
        try:
            text = input('spi> ')
        except EOFError:
            break
        if not text:
            continue

        lexer = Lexer(text)
        parser = Parser(lexer)
        interpreter = Interpreter(parser)
        result = interpreter.interpret()
        print(result)


if __name__ == '__main__':
    main()
