import copy
from enum import Enum
import random
import time
from sys import stderr
import math

import numpy as np


class Board:
    def __init__(self, n, m):
        self.board = np.zeros((n, m))
        self.start = None
        self.size = n * m
        self.moves = {'U': Move.UP, 'D': Move.DOWN, 'R': Move.RIGHT, 'L': Move.LEFT}
        self.directions = {value: key for (key, value) in self.moves.items()}

    def add_field(self, i, j, type):
        self.board[i][j] = type
        if self.board[i][j] == 5:
            self.start = (j, i)

    def path_fitness(self, path):
        agent_x = self.start[0]
        agent_y = self.start[1]

        path_length = 0
        for direction in path:
            agent_x += direction.value[0]
            agent_y += direction.value[1]

            path_length += 1
            if path_length > self.size or self.board[agent_y][agent_x] == 1:
                return math.inf
            if self.board[agent_y][agent_x] == 8:
                return path_length
        return math.inf


class Move(Enum):
    UP = (0, -1)
    RIGHT = (1, 0)
    DOWN = (0, 1)
    LEFT = (-1, 0)


class GeneticAlgorithm:
    def __init__(self, board, init_population, time_limit):
        self.board = board
        self.init_population = init_population
        self.time_limit = time_limit
        self.best_path = self.init_population[0]
        self.best_path_fitness = self.board.path_fitness(self.best_path)
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
        i = random.randint(0, len(solution) - 1)
        j = random.randint(0, len(solution) - 1)
        solution[i], solution[j] = self.__swap(solution[i], solution[j])
        return solution

    def genetic_algorithm(self, population_size):
        population = self.init_population
        start = time.time()
        while time.time() - start < self.time_limit:
            population_fitness = []
            for path in population:
                path_fitness = self.board.path_fitness(path)
                population_fitness.append(path_fitness)
                if path_fitness < self.best_path_fitness:
                    self.best_path = path
                    self.best_path_fitness = path_fitness

            new_population = []
            for i in range(population_size // 2):
                child1, child2 = self.cross_over(
                    population[self.tournament_selection(population_fitness)]
                    , population[self.tournament_selection(population_fitness)])
                new_population += [self.mutation(child1), self.mutation(child2)]
            population = new_population

    def print_best_path(self):
        print(self.best_path_fitness)
        for move in self.best_path[:self.best_path_fitness]:
            print(board.directions[move], file=stderr, end="")


if __name__ == "__main__":
    time_limit, n, m, s, p = [int(param) for param in input().split()]
    board = Board(n, m)
    for i in range(n):
        field = input()[:m]
        for j in range(m):
            board.add_field(i, j, int(field[j]))

    solutions = [[board.moves[char] for char in input().strip()] for i in range(s)]
    genetic_algorithm = GeneticAlgorithm(board, solutions, time_limit)
    genetic_algorithm.genetic_algorithm(p)
    genetic_algorithm.print_best_path()
