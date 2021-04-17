import time

import numdifftools.nd_algopy as nd
import numpy as np


class HappyCat:
    def get_formula(self):
        return lambda y: ((np.linalg.norm(y) ** 2 - 4) ** 2) ** 0.125 + 0.25 * (
                0.5 * (np.linalg.norm(y) ** 2) + np.sum(y)) + 0.5

    """
      interval for get_random_value
      alpha
      epsilon
      """

    def get_initial_data(self):
        return [-8.0, 8.0], 0.01, 0.0000000005


class Griewank:
    def __product(self, y):
        prod = np.cos(y[0] / np.sqrt(1))
        for i in range(3):
            prod *= np.cos(y[i + 1] / np.sqrt(i + 2))
        return prod

    def get_formula(self):
        return lambda y: 1 + sum([(z ** 2) / 4000 for z in y]) - self.__product(y)

    """
    interval for get_random_value
    alpha
    epsilon
    """

    def get_initial_data(self):
        return [-8.0, 8.0], 0.01, 0.0000000001


class LocalSearch:
    def __init__(self, flag, time):
        self.x_best = []
        self.x_local_best = []
        self.tabuList = []
        self.n = 1000
        self.tabuLength = 3 * self.n
        self.time = time
        if flag == 0:
            self.function = HappyCat()
        elif flag == 1:
            self.function = Griewank()

    def __get_random_value(self, interval):
        return np.random.uniform(interval[0], interval[1], 4)

    """
    Tabu search, który znajduje minimum funkcji. Do tabu trafiają potencjalne minima lokalne.
    """
    def find_min(self):
        start_time = time.time()

        (interval, alpha, epsilon) = self.function.get_initial_data()
        x = self.__get_random_value(interval)
        self.x_best = x
        self.x_local_best = x
        gradient = nd.Gradient(self.function.get_formula())
        hessian = nd.Hessian(self.function.get_formula())
        hessian_inverse = np.linalg.inv(hessian(x))
        gradient_value = gradient(x)

        while time.time() - start_time < self.time:  # dopóki czas się nie skończy
            i = 0
            if len(self.tabuList) > self.tabuLength:
                self.tabuList.pop(0)
            while time.time() - start_time < self.time and np.linalg.norm(
                    gradient_value) >= epsilon and i < self.n:
                x = x - alpha * hessian_inverse.dot(gradient_value)
                gradient_value = gradient(x)
                hessian_inverse = np.linalg.inv(hessian(x))
                if self.function.get_formula()(x) < self.function.get_formula()(self.x_local_best):
                    self.x_local_best = x
                i += 1

            if self.function.get_formula()(self.x_local_best) < self.function.get_formula()(self.x_best):
                self.x_best = x
                self.tabuList.append([round(x_i, 3) for x_i in x]) #do tabu trafiają zaokrąglone x
            x = self.__get_random_value(interval)
            while [round(x_i, 3) for x_i in x] in self.tabuList: #czy wylosowany x jest w tabu
                x = self.__get_random_value(interval)
            gradient_value = gradient(x)

    """
    Funkcja porównuje x_local_best z x_best
    Gdyby czas został przerwany zanim ostatnie localBest zostało porównane z best
    """
    def __get_best_solution(self):
        f_local_best = self.function.get_formula()(self.x_local_best)
        f_x_best = self.function.get_formula()(self.x_best)
        if f_local_best < f_x_best:
            return self.x_local_best, f_local_best
        return self.x_best, f_x_best

    def print_result(self):
        (x, f_x) = self.__get_best_solution()
        for element in x:
            print(element, end=" ")
        print(f_x)


if __name__ == "__main__":
    try:
        t, b = map(int, input().split())
        if b != 0 and b != 1:
            raise Exception
        local_search = LocalSearch(b, t)
        local_search.find_min()
        local_search.print_result()
    except Exception:
        "Podaj poprawne parametry."
