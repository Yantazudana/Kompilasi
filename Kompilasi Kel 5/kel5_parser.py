from sly import Parser

import kel5_lexer

class BasicParser(Parser):
    #token diteruskan dari lexer ke parser
    tokens = kel5_lexer.BasicLexer.tokens
  
    precedence = (
        ('left', 'PLUS', 'MINUS'),
        ('left', 'TIMES', 'DIVIDE'),
        ('right', 'UMINUS'),
    )
  
    def __init__(self):
        self.env = { }
  
    @_('')
    def statement(self, p):
        pass

    @_('FOR var_assign TO expr THEN statement')
    def statement(self, p):
        return ('for_loop', ('for_loop_setup', p.var_assign, p.expr), p.statement)

    @_('IF condition THEN statement ELSE statement')
    def statement(seld, p):
        return ('if_stmt', p.condition, ('branch', p.statement0, p.statement1))

    @_('FUN NAME "(" ")" ARROW statement')
    def statement(self, p):
        return ('fun_def', p.NAME, p.statement)

    @_('NAME "(" ")"')
    def statement(self, p):
        return ('fun_call', p.NAME)

    @_('expr EQEQ expr')
    def condition(self, p):
        return ('condition_eqeq', p.expr0, p.expr1)

    @_('var_assign')
    def statement(self, p):
        return p.var_assign

    @_('NAME "=" expr')
    def var_assign(self, p):
        return ('var_assign', p.NAME, p.expr)

    @_('NAME "=" STRING')
    def var_assign(self, p):
        return ('var_assign', p.NAME, p.STRING)

    @_('expr')
    def statement(self, p):
        return (p.expr)

    @_('expr PLUS expr')
    def expr(self, p):
        return ('add', p.expr0, p.expr1)

    @_('expr MINUS expr')
    def expr(self, p):
        return ('sub', p.expr0, p.expr1)

    @_('expr TIMES expr')
    def expr(self, p):
        return ('mul', p.expr0, p.expr1)

    @_('expr DIVIDE expr')
    def expr(self, p):
        return ('div', p.expr0, p.expr1)

    @_('expr LE expr')
    def expr(self, p):
        return ('Less_than_or_equal_to', p.expr0, p.expr1)

    @_('expr GT expr')
    def expr(self, p):
        return ('Greater_than', p.expr0, p.expr1)

    @_('expr LT expr')
    def expr(self, p):
        return ('Less_than', p.expr0, p.expr1)

    @_('expr GE expr')
    def expr(self, p):
        return ('Greater_than_or_equal_to', p.expr0, p.expr1)

    @_('expr NE expr')
    def expr(self, p):
        return ('condition_not_equal', p.expr0, p.expr1)

    @_('"-" expr %prec UMINUS')
    def expr(self, p):
        return p.expr

    @_('NAME')
    def expr(self, p):
        return ('var', p.NAME)
    
    @_('NUMBER')
    def expr(self, p):
        return ('num', p.NUMBER)

    @_('PRINT expr')
    def expr(self, p):
        return ('print', p.expr)

    @_('PRINT STRING')
    def statement(self, p):
        return ('print', p.STRING)

if __name__ == '__main__':
    lexer = pm_lexer.BasicLexer()
    parser = BasicParser()
    env = {}
    while True:
        try:
            text = input('pm > ')
        except EOFError:
            break
        if text:
            tree = parser.parse(lexer.tokenize(text))
            print(tree)
