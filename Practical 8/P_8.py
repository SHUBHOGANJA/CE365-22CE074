def compute_first_sets(grammar, terminals, non_terminals):
    first = {nt: set() for nt in non_terminals}
    for t in terminals:
        first[t] = {t}
    changed = True
    while changed:
        changed = False
        for head, body in grammar:
            if body == "ε":
                if "ε" not in first[head]:
                    first[head].add("ε")
                    changed = True
                continue
            can_derive_epsilon = True
            for idx, symbol in enumerate(body):
                if symbol in terminals:
                    if idx == 0 and symbol not in first[head]:
                        first[head].add(symbol)
                        changed = True
                    can_derive_epsilon = False
                    break
                if symbol in non_terminals:
                    for s in first[symbol] - {"ε"}:
                        if s not in first[head]:
                            first[head].add(s)
                            changed = True
                    if "ε" not in first[symbol]:
                        can_derive_epsilon = False
                        break
            if can_derive_epsilon and "ε" not in first[head]:
                first[head].add("ε")
                changed = True
    return first

def compute_follow_sets(grammar, terminals, non_terminals, first_sets):
    follow = {nt: set() for nt in non_terminals}
    follow["S"].add("$")
    changed = True
    while changed:
        changed = False
        for head, body in grammar:
            if body == "ε":
                continue
            for idx, symbol in enumerate(body):
                if symbol in non_terminals:
                    remainder = body[idx+1:] if idx+1 < len(body) else ""
                    if not remainder:
                        for s in follow[head]:
                            if s not in follow[symbol]:
                                follow[symbol].add(s)
                                changed = True
                        continue
                    first_of_remainder = set()
                    can_derive_epsilon = True
                    for rem_symbol in remainder:
                        for s in first_sets[rem_symbol] - {"ε"}:
                            first_of_remainder.add(s)
                        if "ε" not in first_sets[rem_symbol]:
                            can_derive_epsilon = False
                            break
                    for s in first_of_remainder:
                        if s not in follow[symbol]:
                            follow[symbol].add(s)
                            changed = True
                    if can_derive_epsilon:
                        for s in follow[head]:
                            if s not in follow[symbol]:
                                follow[symbol].add(s)
                                changed = True
    return follow

def construct_parsing_table(grammar, terminals, non_terminals, first_sets, follow_sets):
    parsing_table = {nt: {t: None for t in terminals | {'$'}} for nt in non_terminals}
    for head, body in grammar:
        first_body = set()
        can_derive_epsilon = True
        for symbol in body:
            first_body |= first_sets[symbol] - {'ε'}
            if 'ε' not in first_sets[symbol]:
                can_derive_epsilon = False
                break
        for terminal in first_body:
            parsing_table[head][terminal] = body
        if can_derive_epsilon:
            for terminal in follow_sets[head]:
                parsing_table[head][terminal] = body
    return parsing_table

def print_parsing_table(parsing_table):
    headers = sorted(parsing_table[next(iter(parsing_table))].keys())
    print(" ", " | ".join(headers))
    print("-" * (10 * len(headers)))
    for nt, row in parsing_table.items():
        row_entries = [row[t] if row[t] else "" for t in headers]
        print(nt, " | ".join(row_entries))

def parse_string(parsing_table, start_symbol, input_string):
    stack = ['$', start_symbol]
    input_string += '$'
    i = 0
    while stack:
        top = stack.pop()
        if top == '$' and input_string[i] == '$':
            print("String is valid.")
            return True
        elif top == input_string[i]:
            i += 1
        elif top in parsing_table:
            production = parsing_table[top].get(input_string[i])
            if production:
                if production != 'ε':
                    stack.extend(reversed(production))
            else:
                print("String is invalid.")
                return False
        else:
            print("String is invalid.")
            return False
    print("String is invalid.")
    return False

def main():
    grammar = [
        ("S", "ABC"), ("S", "D"), ("A", "a"), ("A", "ε"),
        ("B", "b"), ("B", "ε"), ("C", "(S)"), ("C", "c"), ("D", "AC")
    ]
    terminals = {"a", "b", "(", ")", "c", "ε"}
    non_terminals = {"S", "A", "B", "C", "D"}
    first_sets = compute_first_sets(grammar, terminals, non_terminals)
    follow_sets = compute_follow_sets(grammar, terminals, non_terminals, first_sets)
    parsing_table = construct_parsing_table(grammar, terminals, non_terminals, first_sets, follow_sets)
    print_parsing_table(parsing_table)
    input_string = input("Enter a string to parse: ")
    parse_string(parsing_table, "S", input_string)

if _name_ == "_main_":
    main()