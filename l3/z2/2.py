import copy
from collections import defaultdict
import random
import time
from sys import stderr


class GeneticAlgorithm:
    def __init__(self, time_limit, init_solution, alphabet, alphabet_values):
        self.population_size = 15
        self.alphabet = alphabet
        with open('dict.txt') as f:
            self.dictionary = set((word for word in f.read().split()))
        self.alphabet_values = alphabet_values
        self.init_population = init_solution
        self.time_limit = time_limit
        self.best_solution = self.init_population[0]
        self.best_solution_fitness = self.get_fitness(self.best_solution)
        for solution in self.init_population:
            fitness = self.get_fitness(self.best_solution)
            if self.get_fitness(solution) > fitness:
                self.best_solution = solution
                self.best_solution_fitness = fitness

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
        child1 = list(child1)
        child2 = list(child2)
        for i in range(partition_left, partition_right):
            child1[i], child2[i] = self.__swap(child1[i], child2[i])
        child1 = "".join(child1)
        child2 = "".join(child2)
        return child1, child2

    def __swap(self, value1, value2):
        return value2, value1

    def mutation(self, solution):
        i = random.randint(0, len(solution) - 1)
        j = random.randint(0, len(solution) - 1)
        solution = list(solution)
        solution[i], solution[j] = self.__swap(solution[i], solution[j])
        operation = random.choices(["add", "remove"])
        if operation == "remove":
            i = random.randint(0, len(solution) - 1)
            solution.pop(solution[i])
        else:
            remaining = copy.deepcopy(self.alphabet)
            for letter in solution:
                remaining[letter] -= 1

            letters_remaining = []
            for letter in remaining:
                if remaining[letter] > 0:
                    letters_remaining.append(letter)

            if letters_remaining:
                letter = random.choices(letters_remaining)
                solution.append(letter[0])
        solution = "".join(solution)
        return solution

    def genetic_algorithm(self):
        population = self.init_population
        start = time.time()
        while time.time() - start < self.time_limit:
            population_fitness = []
            for solution in population:
                solution_fitness = self.get_fitness(solution)
                population_fitness.append(solution_fitness)
                if solution_fitness > self.best_solution_fitness:
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
        print(self.best_solution_fitness)
        print(self.best_solution, file=stderr)

    def get_fitness(self, solution):
        fitness = 0
        remaining = copy.deepcopy(self.alphabet)
        for letter in solution:
            fitness += self.alphabet_values[letter]
            remaining[letter] -= 1
            if remaining[letter] < 0:
                return -1
        if solution in self.dictionary:
            return fitness
        return -1


if __name__ == "__main__":
    time_limit, alphabet, initial = [int(param) for param in input().split()]
    alphabet_count = defaultdict(int)
    alphabet_value = defaultdict(int)
    for i in range(alphabet):
        char, value = input().split()
        alphabet_count[char] += 1
        alphabet_value[char] = int(value)
    initial_population = []
    for i in range(initial):
        initial_population.append(input().strip())

    genetic_algorithm = GeneticAlgorithm(time_limit, initial_population, alphabet_count, alphabet_value)
    genetic_algorithm.genetic_algorithm()
    genetic_algorithm.print_best_solution()
