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

    def copy(self):
        return copy.deepcopy(self)
    
    def get_all_variables(self):
        result = set()
        for component in self.components:
            result.update(component.get_all_variables())

        return result
    
    def is_valid(self): # tautology
        variables = list(self.get_all_variables)
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return False, valuation
        return True, None    
        
    def is_satisfiable(self):
        variables = list(self.get_all_variables)
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return True, valuation
        return False, None
    
    def is_contradictory(self):
        variables = list(self.get_all_variables)
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return False, valuation
        return True, None
    
    def is_falsifiable(self):
        variables = list(self.get_all_variables)
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return True, valuation
        return False, None
    
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
    return [Var(name.strip()) for name in names.split(",")]

def example1():
    pass

if __name__ == "__main__":
    pass
