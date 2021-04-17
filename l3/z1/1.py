import copy
from enum import Enum
import random
import time
from sys import stderr
import math

import numpy as np


class GeneticAlgorithm:
    def __init__(self, time_limit, init_solution, epsilon):
        self.population_size = 15
        self.init_population = self.get_init_population(init_solution)
        self.time_limit = time_limit
        self.epsilon = epsilon
        self.best_solution = self.init_population[0]
        self.best_solution_fitness = self.function_value(self.best_solution)
        self.tournaments_count = 5

    def tournament_selection(self, population_fitness):
        solution1 = random.randrange(len(population_fitness))
        for i in range(1, self.tournaments_count):
            solution2 = random.randint(0, len(population_fitness) - 1)
            if population_fitness[solution2] < population_fitness[solution1]:
                solution1 = solution2
        return solution1

    def cross_over(self, parent1, parent2):
        child1 = copy.deepcopy(parent1)
        child2 = copy.deepcopy(parent2)
        min_length = min(len(child1), len(child2))
        partition_left = random.randint(0, min_length - 1)
        partition_right = random.randint(0, min_length - 1)
        if partition_left > partition_right:
            partition_left, partition_right = self.__swap(partition_left, partition_right)
        for i in range(partition_left, partition_right):
            child1[i], child2[i] = self.__swap(child1[i], child2[i])
        return child1, child2

    def __swap(self, value1, value2):
        return value2, value1

    def mutation(self, solution):
        mutated = []
        for i, v in enumerate(solution):
            mutated.append(v * random.gauss(1, 0.1))
        return mutated

    def genetic_algorithm(self):
        population = self.init_population
        start = time.time()
        while time.time() - start < self.time_limit:
            population_fitness = []
            for solution in population:
                solution_fitness = self.function_value(solution)
                population_fitness.append(solution_fitness)
                if solution_fitness < self.best_solution_fitness:
                    self.best_solution = solution
                    self.best_solution_fitness = solution_fitness

            new_population = []
            for i in range(self.population_size // 2):
                child1, child2 = self.cross_over(
                    population[self.tournament_selection(population_fitness)]
                    , population[self.tournament_selection(population_fitness)])
                new_population += [self.mutation(child1), self.mutation(child2)]
            population = new_population

    def print_best_solution(self):
        for x in self.best_solution:
            print(x, end=" ")
        print(self.best_solution_fitness)

    def function_value(self, solution):
        f_x = 0
        for i in range(5):
            f_x += self.epsilon[i] * abs(solution[i]) ** (i + 1)
        return f_x

    def get_init_population(self, init_solution):
        population = []
        for i in range(self.population_size):
            population.append(self.mutation(init_solution))
        return population


if __name__ == "__main__":
    params = input().split()
    time_limit = int(params[0])
    x = list(map(float, params[1:6]))
    epsilon = list(map(float, params[6:11]))

    genetic_algorithm = GeneticAlgorithm(time_limit, x, epsilon)
    genetic_algorithm.genetic_algorithm()
    genetic_algorithm.print_best_solution()
