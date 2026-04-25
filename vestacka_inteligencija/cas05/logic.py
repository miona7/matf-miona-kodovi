import copy 
from itertools import combinations

# x, y, z, w, ... -> O(2^n)
def all_valuations(variables):
    # l = 0, 1, 2, ..., len(variables) -> koliko ce promeljivih u datoj valuaciji biti istinito
    for l in range(len(variables) + 1):
                        # pravi kombinacije duzine l od zadatih promenljivih
        for true_variables in combinations(variables, l):
            result = {x: False for x in variables}
            result.update({x: True for x in true_variables})
            yield result

class Formula():
    def __init__(self):
        self.components = []
    
    def __str__(self):
        pass

    def copy(self):
        return copy.deepcopy(self)

    def __and__(self, other): # self & other -> self.__and__(other)
        return And(self.copy(), other.copy())

    def __or__(self, other): # self | other -> self.__or__(other)
        return Or(self.copy(), other.copy())

    def __rshift__(self, other): # self >> other -> self.__rshift__(other)
        return Impl(self.copy(), other.copy())

    def __eq__(self, other): # self == other -> self.__eq__(other)
        return Eq(self.copy(), other.copy())

    def __invert__(self): # ~self -> self.__invert__()
        return Not(self.copy())
    
    def interpret(self, valuation):
        pass
    
    def get_all_variables(self):
        result = set()
        for component in self.components:
            result.update(component.get_all_variables())

        return result
    
    def is_valid(self): # tautology
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return False, valuation
        return True, None    
        
    def is_satisfiable(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return True, valuation
        return False, None
    
    def is_contradictory(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return False, valuation
        return True, None
    
    def is_falsifiable(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return True, valuation
        return False, None
    
    def all_valuations_that_interpret_to_true(self):
        result = []
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                result.append(valuation)
        return result

class Var(Formula):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def __str__(self):
        return self.name

    def interpret(self, valuation):
        return valuation[self.name]
    
    def get_all_variables(self):
        return set([self.name])
    
class Const(Formula):
    def __init__(self, value):
        super().__init__()
        self.value = value

    def __str__(self):
        return "{}".format(1 if self.value else 0)

    def interpret(self, valuation):
        return self.value
    
class And(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    def __str__(self):
        return f"({self.components[0]}) & ({self.components[1]})"

    def interpret(self, valuation):
        return self.components[0].interpret(valuation) and self.components[1].interpret(valuation)

class Or(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    def __str__(self):
        return f"({self.components[0]}) | ({self.components[1]})"
    
    def interpret(self, valuation):
        return self.components[0].interpret(valuation) or self.components[1].interpret(valuation)

class Impl(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    def __str__(self):
        return f"({self.components[0]}) >> ({self.components[1]})"
    
    def interpret(self, valuation): # p => q <=> ~p or q
        return not self.components[0].interpret(valuation) or self.components[1].interpret(valuation)

class Eq(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    def __str__(self):
        return f"({self.components[0]}) == ({self.components[1]})"
    
    def interpret(self, valuation):
        return self.components[0].interpret(valuation) == self.components[1].interpret(valuation)

class Not(Formula):
    def __init__(self, op):
        super().__init__()
        self.components = [op]

    def __str__(self):
        return f"~({self.components[0]})"
    
    def interpret(self, valuation):
        return not self.components[0].interpret(valuation) 

def vars(names):
    return [Var(name.strip()) for name in names.split(", ")]

def evaluate_formula(formula):
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is contradictory: ", formula.is_contradictory())
    print("is falsifiable: ", formula.is_falsifiable())
    print("all true valuations: ")
    for valuation in formula.all_valuations_that_interpret_to_true():
        print(valuation)

def example1():
    x, y, z = vars("x, y, z")
    formula = (x & y) | (y >> z)
    # formula = Or(
    #     And(x, y),
    #     Impl(y, z)
    # )
    valuation = {
        "x": True,
        "y": False,
        "z": True
    }

    print(formula)
    print(formula.interpret(valuation))
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is contradictory: ", formula.is_contradictory())
    print("is falsifiable: ", formula.is_falsifiable())

def example2():
    ana_je_zubar = Var("ana_je_zubar")
    formula = ana_je_zubar | ~ana_je_zubar
    evaluate_formula(formula)

def example3():
    p, q = vars("p, q")
    formula = p >> q
    evaluate_formula(formula)

def example4():
    '''
    
    U igri mines dimenzija 2x3 dobijena je sledeca konfiguracija
    
    |1|A|C|
    |1|B|2|
    
    A, B, C su neotvorena polja, a brojevi oznacavaju broj mina u okolnim poljima.
    Zapisati u iskaznoj logici uslove koji moraju da vaze.
    
    '''
    A, B, C = vars("A, B, C")
    formula = (A | B) & ~(A & B) & ~(~A & ~B) & \
              (B | A) & ~(B & A) & ~(~B & ~A) & \
              ~(A & B & C) & ~(~A & ~B & ~C) & \
              (A | B) & (A | C) & (B | C)
    evaluate_formula(formula)

def example5():
    # Date su dve kutije A, B robot mora da stavi objekat u tacno jednu od njih
    
    A, B = vars("A, B")
    formula = (A | B) & ~(A & B) & ~(~A & ~B)
    evaluate_formula(formula)

def example6():
    ''' 
    
    |A|B|
    |C|D|
    
    Zapisati uslov da se u tabeli 2x2 sa poljima A, B, C, D moze postaviti tacno jedan zeton u svakom redu
    
    '''
    A, B, C, D = vars("A, B, C, D")
    formula = (A | B) & ~(A & B) & ~(~A & ~B) & \
              (C | D) & ~(C & D) & ~(~C & ~D)
    evaluate_formula(formula)

def example7():
    # U iskaznoj logici zapisati uslov da bitovi 3-bitnog polja moraju biti jednaki
    A, B, C = vars("A, B, C")
    formula = (A == B) & (B == C)
    evaluate_formula(formula)

def example8():
    '''

    Dva dvobitna broja se sabiraju i daju rezultat 3.
    1+2
    2+1
    3+0
    0+3
        A B
        C D
        ---
        1 1

    '''
    A, B, C, D = vars("A, B, C, D")
    formula = (B | D) & ~(B & D) & (A | C) & ~(A & C)
    evaluate_formula(formula)

def example9():
    # U iskoznoj logici zapisati da je 4 bitna reprezentacija broja palindrom ali da bitovi nisu jednaki
    A, B, C, D = vars("A, B, C, D")
    formula = (A == D) & (B == C) & ~((A == B) & (B == C) & (C == D))
    evaluate_formula(formula)

def example10():
    '''
    
    Tri polja se boje crvenom ili plavom. 
    Ukoliko je prvo crveno, druga dva moraju biti iste boje.
    Ukoliko je drugo crveno, trece mora biti plavo.
    
    '''
    A, B, C = vars("A, B, C")
    # A = True -> A je crveno
    formula = (A >> (B == C)) & (B >> ~C)
    evaluate_formula(formula)

def example11():
    '''

          A
         / \
        B - C
    
    Temana trougla A, B, C se boje sa dve boje, pri tome ni jedan par temena ne moze imati istu boju.
    
    '''
    A, B, C = vars("A, B, C")
    formula = ~(A == B) & ~(A == C) & ~(B == C)
    evaluate_formula(formula)

def example12():
    '''

    |A|B|
    |C|D|
    
    Tabela 2x2 se boji crvenom ili plavom bojom.
    Ako je polje A ofarbano crvenom onda barem jedno od ostalih polja mora biti plavo.
    Ako je polje D ofarabno plavom onda barem dva ostala moraju biti crvena.
    Ne smeju sva polja biti ofarabana istom bojom.
    
    '''
    A, B, C, D = vars("A, B, C, D")
    formula = (A >> (~B | ~C | ~D)) & (~D >> ((A & B) | (B & C) | (A & C))) & \
              ~((A == B) & (B == C) & (C == D))
    evaluate_formula(formula)

if __name__ == "__main__":
    # example1()
    # example2()
    # example3()
    # example4()
    # example5()
    # example6()
    # example7()
    # example8()
    # example9()
    # example10()
    # example11()
    example12()