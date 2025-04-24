import random
import numpy as np

# from lab3.main import evaluateRandom, generateN, generate_range, distribute, distribute_values, elimination_method, possibility_func_linear
# import lab3.main

# def random_discrete_2d(probabilities: list[list[float]]) -> tuple[int, int]:
#     """
#     Generates a random discrete 2D point based on the given probabilities.
#     """
#     if not probabilities or not all(probabilities):
#         raise ValueError("Probabilities cannot be empty or None.")
    
#     border_probabilities: list[float] = [sum(row) for row in probabilities]
    
#     x = lab3.random_choice(list(enumerate(border_probabilities)))
    
#     y_probabilities: list[float] = [probabilities[x][i] * border_probabilities[x] for i in range(len(probabilities[x]))]

#     y = lab3.random_choice(list(enumerate(y_probabilities)))

#     return (x, y)


def evaluateRandom(numbers, N_counters, min_val, max_val):
    counters = np.zeros(N_counters)

    counters_thresholds = np.full(N_counters, min_val)

    step = (max_val - min_val) / N_counters

    for i in range(1, N_counters + 1):
        counters_thresholds[i - 1] += step * i

    for val in numbers:
        for counter_id in range(0, N_counters):
            if val <= counters_thresholds[counter_id]:
                counters[counter_id] += 1
                break

    return counters

def generateN(n, generatorFunc, **generateFuncArgs):
    print(f'arguments: {generateFuncArgs}')
    values = []

    for _ in range(0, n):
        values.append(generatorFunc(**generateFuncArgs))  

    return values

def generate_range(range_start, range_end):
    # random.random returns float from [0.0, 1.0] range
    return (range_start + random.random() * (range_end - range_start))

def distribute(distributor_table, value, min_value, max_value):
    # distributor table example:
    # [[0.1, 1], [0.3, 3], [0.2, 4], [0.4, 10]]

    normalized = (value - min_value) / (max_value - min_value)

    chance = 0.0

    for bucket in distributor_table:
        chance += bucket[0]
        if normalized < chance:
            return bucket[1]
    
    return bucket[-1]
            
def distribute_values(distributor_table, values, min_value, max_value):
    return_values = []
    
    for element in values:
        distr_val = distribute(distributor_table, element, min_value, max_value)
        return_values.append(distr_val)

    return return_values


# f (x=coś, y) -> przeskalować (znormalizować) przekrój
# |
# v
# f (Y /(pod warunkiem) X = coś) = (fy oraz X = x) / (fx (coś)) = to samo 


def main():
    distribute_values_X = [
        1, 2, 3, 4
    ]

    distribute_values_Y = [
        1, 2, 3, 4
    ]

    distribute_table_XY = [
        [0  , 0.1, 0  , 0.2],
        [0.1, 0  , 0  , 0  ],
        [0  , 0  , 0.3, 0.05],
        [0.2, 0  , 0.05,0  ]
    ]


    distribute_table_X = []
    # distribute_table_X = [
    #     0.3, 0.1, 0.35, 0.25
    # ]

    for row in distribute_table_XY:
        distribute_table_X.append(round(sum(row), 2))

    print(f'Distribute table X:\n{distribute_table_X}')

    distribute_table_Y = [
        # [0, 1/3, 0, 2/3] # X = 1
        # TODO: X = 2
        # TODO: X = 3
        # TODO: X = 4
    ]

    for row_id in range(0, len(distribute_table_XY)):
        Y_row = []
        for element_id in range(0, len(distribute_table_XY[row_id])):
            Y_row.append(round(distribute_table_XY[row_id][element_id] / distribute_table_X[row_id], 2))
        distribute_table_Y.append(Y_row)

    print(f'Distribute table Y:\n{distribute_table_Y}')

    # TODO: 100000 punkty, 16 liczników (dla każdej komórki)

    distributor_X = []

    for element_id in range(0, len(distribute_table_X)):
        distributor_X.append([distribute_table_X[element_id], distribute_values_X[element_id]])

    print(f'Distributor for X:\n{distributor_X}')

    distibutor_Y = []

    for row_id in range(0, len(distribute_table_Y)):
        Y_row = []
        for element_id in range(0, len(distribute_table_Y[row_id])):
            Y_row.append([distribute_table_Y[row_id][element_id], distribute_values_Y[element_id]])

        distibutor_Y.append(Y_row)    

    print(f'Distributor for Y:')

    for row in distibutor_Y:
        print(f'{row}')

    Ngenerated = 100000

    Xvals = generateN(Ngenerated, generate_range, range_start=0, range_end=100)

    Xvals = distribute_values(distributor_X, Xvals, 0, 100)

    Xeval = evaluateRandom(Xvals, 4, 1, 4)

    print(Xeval)

    Yvals = []

    for x in Xvals:
        y = generate_range(0, 100)
        y = distribute(distibutor_Y[x - 1], y, 0, 100) # błąd logiczny, bo X - 1 to niekoniecznie index
        Yvals.append(y)

    counters = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]

    for i in range(0, Ngenerated):
        counters[Xvals[i] - 1][Yvals[i] - 1] += 1

    print('\n\nFinal count:')
    for row in counters:
        print(row)



if __name__ == "__main__":
    main()