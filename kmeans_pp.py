import numpy as np
import pandas as pd
import sys
DEFAULT_MAX_ITER = 300


def main():
    k, max_iter, eps, vectors = get_input()
    print()
    # centoirds = init_centroids(vectors, k)


# parse the input data into 3 variable
def get_input():
    if len(sys.argv) == 3:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], DEFAULT_MAX_ITER, sys.argv[2], sys.argv[3], sys.argv[4]
    else:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]
    try:
        k = int(k)
    except:
        print("Invalid number of clusters!")
    try:
        max_iter = int(max_iter)
    except:
        print("Invalid maximum iteration!")
    try:
        eps = float(eps)
    except:
        print("Invalid eps!")
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

def init_centroids(vectors, k):
    centroids = vectors[np.random.randint(0, len(vectors))]



if __name__ == "__main__":
    main()
