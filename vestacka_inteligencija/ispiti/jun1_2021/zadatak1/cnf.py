'''
dimacs format:
        (3)        (2)
p cnf num_of_vars num_of_cl

1 3 0     -> p1 | p3
-1 2 -3 0 -> ~p1 | p2 | ~p3
''' 

class CNF():
    def __init__(self):
        self.clauses = []
        self.var_name_to_number = {}
        self.number_to_var_name = {}

    def add_clause(self, clause):
        self.clauses.append(clause)

        for literal in clause:
            var_name = literal.strip("-")
            if var_name not in self.var_name_to_number:
                var_number = len(self.var_name_to_number) + 1
                self.var_name_to_number[var_name] = var_number
                self.number_to_var_name[var_number] = var_name

    def dimacs(self):
        result = f"p cnf {len(self.var_name_to_number)} {len(self.clauses)}\n"
        
        for clause in self.clauses:
            for literal in clause:
                var_name = literal.strip("-")
                
                if literal[0] == "-":
                    result += "-"
                
                result += f"{self.var_name_to_number[var_name]} "
        
            result += "0\n"

        return result