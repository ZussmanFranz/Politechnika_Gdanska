from itertools import compress
import random
import time
import matplotlib.pyplot as plt

from data import *
from queue import PriorityQueue

def initial_population(individual_size, population_size):
    return [[random.choice([True, False]) for _ in range(individual_size)] for _ in range(population_size)]

def fitness(items, knapsack_max_capacity, individual): # Po co jeszcze raz to deklarować?
    total_weight = sum(compress(items['Weight'], individual))
    if total_weight > knapsack_max_capacity:
        return 0
    return sum(compress(items['Value'], individual))

def population_best(items, knapsack_max_capacity, population):
    best_individual = None
    best_individual_fitness = -1
    for individual in population:
        individual_fitness = fitness(items, knapsack_max_capacity, individual)
        if individual_fitness > best_individual_fitness:
            best_individual = individual
            best_individual_fitness = individual_fitness
    return best_individual, best_individual_fitness

# My functions:

# Parents:

## Calculates sum of fitness values in population
def fitnesses(items, knapsack_max_capacity, population):
    fs = []
    max = -1

    for i in population:
        ft = fitness(items, knapsack_max_capacity, i)
        fs.append(ft)
        if ft > max:
            max = ft
    return max, fs

## Array of chances of the roulette wheel selection
def chance_distribution(fitnesses):
    # Each individual from the population contains the starting value of it's "chance zone" at it's index
    distribution = []
    start_pos = 0
    next = 0
    fitness_sum = sum(fitnesses)

    for i in fitnesses:
        chance = i / fitness_sum
        next = chance + start_pos
        distribution.append(next)
        start_pos = next

    return distribution

## Chooses an individual at the certain "chance zone" of a roulette
def choose_individual(chance, roulette):
    index = 0
    
    for i in roulette:
        if chance < i:
            return index
        index += 1

    return len(roulette) - 1   


# Children:

## Evenly divides "genome" with one point
def crossover(parents_genome):
    children = [[],[]]

    parent_size = len(parents_genome) // 2
    # point = parent_size // 2
    point = random.randrange(1, parent_size - 2)

    for i in range(0, parent_size):
        children[0].append(parents_genome[i + parent_size])
        children[1].append(parents_genome[i])
        if i == point: # It's time to change donor of genome
            temp = children[0]
            children[0] = children[1]
            children[1] = temp
            
    return children

## Generates indexes of pairs
def generate_pairs(parents_population):
    # Initialize the array with the desired pattern
    pairs_array = []
    size = len(parents_population)

    for i in range(0, size//2):
        pair = [parents_population[i],parents_population[i + size//2]]
        pairs_array.append(pair)
        

    return pairs_array


## Generates children for all the parents from set
def generate_children(parents_population):
    children_population = []

    # Array of sets for every index. Each set contains possible pairs
    pairs = generate_pairs(parents_population)

    # generate children for pairs
    for p in pairs:
        pair_result = crossover(p[0] + p[1])
        
        # Some hardcoded values
        children_population.append(pair_result[0])
        children_population.append(pair_result[1])

    return children_population

## Seeks for top n elites to keep in the population (returns the array of indexes)
def get_elites(items, knapsack_max_capacity, population, best_fitness, n_elites):
    elites = []
    size = len(population)

    best = PriorityQueue()

    for index in range(0, size):
        normalized_priority = fitness(items, knapsack_max_capacity, population[index]) * 100 / best_fitness
        best.put((-normalized_priority, index))

    for _ in range(0, n_elites):
        _, elite_index = best.get()
        elites.append(elite_index)

    return elites


# Mutation:

## Changes random bit in a choosen solution
def mutate(individual, bit_mutation_rate):
    chance = 0
    for bit_index in range(0, len(individual)):
        chance = random.randrange(0, 100)
        if chance/100 <= bit_mutation_rate:
            individual[bit_index] = not individual[bit_index]

    return individual 

def mutate_population(population, bit_mutation_rate):
    for i in population:
        i = mutate(i, bit_mutation_rate)
        
    return population
    

items, knapsack_max_capacity = get_big()
print(items)

population_size = 100
generations = 200
n_selection = population_size
n_elite = 1
bit_mutation_rate = 1 / len(items) 

start_time = time.time()
best_solution = None
best_fitness = 0
population_history = []
best_history = []
population = initial_population(len(items), population_size)


for generation_number in range(generations):
    population_history.append(population)

    # TODO: implement genetic algorithm

    # TODO: wybór rodziców
    max_fit, fsum = fitnesses(items, knapsack_max_capacity, population)
    roulette = chance_distribution(fsum) 
    # example of roulette: [0.0, 0.0, 0.04, 0.24, 0.45, 0.69, 0.81, 0.81, 0.82, 0.99, 1.0]

    selected_indexes = [] # set of unique indexes

    for i in range(0, n_selection):
        index = choose_individual(random.randrange(0, 100) / 100, roulette) # index of chosen individual
        selected_indexes.append(index)

    # TODO: tworzenie dzieci
    parents_population = []

    for parent_index in selected_indexes:
        parents_population.append(population[parent_index])

    new_population = generate_children(parents_population)

    # TODO: mutacja 
    new_population = mutate_population(new_population, bit_mutation_rate)

    # TODO: aktualizacja populacji
    elites_indexes = get_elites(items, knapsack_max_capacity, population, max_fit, n_elite)


    for ind in elites_indexes:
        # Elites replace children in the new generation (if len(new_population) == len(population))
        new_population[random.randrange(0, len(new_population))] = population[ind]

    population = new_population

    best_individual, best_individual_fitness = population_best(items, knapsack_max_capacity, population)
    if best_individual_fitness > best_fitness:
        best_solution = best_individual
        best_fitness = best_individual_fitness
    best_history.append(best_fitness)

end_time = time.time()
total_time = end_time - start_time
print('Best solution:', list(compress(items['Name'], best_solution)))
print('Best solution value:', best_fitness)
print('Time: ', total_time)

# plot generations
x = []
y = []
top_best = 10
for i, population in enumerate(population_history):
    plotted_individuals = min(len(population), top_best)
    x.extend([i] * plotted_individuals)
    population_fitnesses = [fitness(items, knapsack_max_capacity, individual) for individual in population]
    population_fitnesses.sort(reverse=True)
    y.extend(population_fitnesses[:plotted_individuals])
plt.scatter(x, y, marker='.')
plt.plot(best_history, 'r')
plt.xlabel('Generation')
plt.ylabel('Fitness')
plt.show()


