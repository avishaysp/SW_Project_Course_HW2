import math
import numpy as np
import pandas as pd
import sys
import mykmeanssp as kmeans

DEFAULT_MAX_ITER = 300


def main():
    K, max_iter, eps, vectors = get_input()
    centroids = init_centroids(vectors, K)
    list_of_vectors = get_python_list(vectors)
    list_of_centroids = get_python_list(centroids)
    x = kmeans.fit(K, max_iter, len(list_of_vectors), len(list_of_vectors[0]), eps, list_of_vectors, list_of_centroids)
    print(x)
    
# parse the input data into 3 variable
def get_input():
    print(len(sys.argv))
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
    sorted_vectors_wo_key = sorted_vectors.drop('column1', axis=1)
    return k, max_iter, eps, sorted_vectors_wo_key


def get_python_list(vectors: pd.DataFrame):
    return vectors.values.tolist()


def init_centroids(vectors: pd.DataFrame, k) -> pd.DataFrame:
    rand_index = np.random.choice(vectors.index)
    centroids = pd.DataFrame(vectors.iloc[rand_index]).T
    for i in range(k - 1):
        centroids = pd.concat([centroids, pd.DataFrame(select_vector(vectors, centroids)).T])
    return centroids


def select_vector(vectors: pd.DataFrame, centroids: pd.DataFrame):
    dist_to_closest = [calc_dist_to_closest(vectors.iloc[i], centroids) for i in vectors.index]
    sum_of_dist = sum(dist_to_closest)
    weights = [dist_to_closest[i] / sum_of_dist for i in range(len(vectors))] if sum_of_dist else [1] * len(vectors)
    return vectors.sample(weights=weights, n=1).iloc[0]


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
