import subprocess

import matplotlib as matpl
from sklearn.datasets import load_iris
import subprocess as sp
import kmeans_pp


def main():
    iris = load_iris()
    results_of_kmeans_pp = []
    for k in range(1, 11):
        result_for_k = sp.run(['python', 'kmeans_pp.py', str(k), '333', '0', 'input_1_db_1', 'input_1_db_2'])
        results_of_kmeans_pp.append(result_for_k)



if __name__ == "__main__":
    main()
