import math
import traceback

import numpy as np
import pandas as pd
import sys
import mykmeanssp as kmeans

DEFAULT_MAX_ITER = 300
np.random.seed(0)


def main(bonus_run=False, k=1, vectors=None):
    k, max_iter, eps, vectors = get_input_bonus_wrap(bonus_run, k, vectors)
    centroids = init_centroids(vectors, k)
    list_of_centroids = get_centroids_list(centroids)
    if bonus_run:
        return list_of_centroids
    print(list_of_centroids)


def get_input_bonus_wrap(bonus_run, k, vectors):
    if not bonus_run:
        k, max_iter, eps, vectors = get_input()
    else:
        max_iter, eps, vectors = 1000, 0.0, pd.DataFrame(vectors)
    return k, max_iter, eps, vectors

def get_input():
    if len(sys.argv) == 5:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], DEFAULT_MAX_ITER, sys.argv[2], sys.argv[3], sys.argv[4]
    else:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]
    try:
        k = int(k)
    except Exception as e:
        print("Invalid number of clusters!")
        sys.exit(1)
    try:
        max_iter = int(max_iter)
    except Exception as e:
        print("Invalid maximum iteration!")
        sys.exit(1)
    try:
        eps = float(eps)
    except Exception as e:
        print("Invalid eps!")
        sys.exit(1)
    assert 1 < max_iter < 1000, "Invalid maximum iteration!"
    vectors1 = pd.read_csv(file_path1)
    vectors2 = pd.read_csv(file_path2)
    num_columns1 = len(vectors1.columns)
    num_columns2 = len(vectors2.columns)
    column_names1 = [f'column{i + 1}' for i in range(num_columns1)]
    column_names2 = [f'column{i + 1}' for i in range(num_columns2)]
    vectors1.columns = column_names1
    vectors2.columns = column_names2
    vectors = pd.merge(vectors1, vectors2, on="column1", how="inner")
    assert 1 < k < len(vectors), "Invalid number of clusters!"
    sorted_vectors = vectors.sort_values('column1', ascending=True)
    sorted_vectors = sorted_vectors.set_index('column1')
    sorted_vectors.index = sorted_vectors.index.astype(int)
    return k, max_iter, eps, sorted_vectors


def get_python_list(vectors: pd.DataFrame):
    return vectors.values.tolist()


def init_centroids(vectors: pd.DataFrame, k) -> pd.DataFrame:
    try:
        rand_index = np.random.choice(vectors.index)
        centroids = pd.DataFrame(vectors.iloc[rand_index]).T
        for i in range(k - 1):
            centroids = pd.concat([centroids, pd.DataFrame(select_vector(vectors, centroids)).T])
    except Exception as e:
        print("An Error Has Occurred")
        traceback.print_exc()
        sys.exit(1)
    return centroids


def select_vector(vectors: pd.DataFrame, centroids: pd.DataFrame):
    dist_to_closest = [calc_dist_to_closest(vectors.loc[i], centroids) for i in vectors.index]
    sum_of_dist = sum(dist_to_closest)
    weights = [dist_to_closest[i] / sum_of_dist for i in range(len(vectors))] if sum_of_dist != 0 else [1 / len(vectors)] * len(vectors)
    selected_vector = np.random.choice(vectors.index, p=weights)
    return vectors.loc[selected_vector]


def calc_dist_to_closest(vector: pd.Series, centroids: pd.DataFrame):
    curr_min = math.inf
    for i in centroids.index:
        curr_min = min(curr_min, euclidean_dist(vector, centroids.loc[i]))
    return curr_min


def euclidean_dist(vector1: pd.Series, vector2: pd.Series):
    summer = 0
    for c1, c2 in zip(vector1.index, vector2.index):
        summer += (vector1.loc[c1] - vector2.loc[c2]) ** 2
    return summer ** .5


if __name__ == "__main__":
    main()
