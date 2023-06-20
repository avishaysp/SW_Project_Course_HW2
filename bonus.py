import math
import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Ellipse
from sklearn.datasets import load_iris
import kmeans_pp
iris = load_iris()


def euclidian_dist(vec1, vec2):
    assert len(vec1) == len(vec1)
    return sum(((vec1[i] - vec2[i]) ** 2 for i in range(len(vec1)))) ** .5


def dist_to_closest(vector, centroids):
    return min((euclidian_dist(vector, centroids[i]) for i in range(len(centroids))))


def inertia(centroids):
    data = iris.data.tolist()
    return sum((dist_to_closest(vec, centroids)) ** 2 for vec in data)


def main():
    all_centroids = [None]  # avoid index 0
    for k in range(1, 11):
        centroids_for_k = kmeans_pp.main(bonus_run=True, k=k, vectors=iris.data)
        all_centroids.append(centroids_for_k)
    inertia_val = [None] + [inertia(all_centroids[k]) for k in range(1, 11)]  # avoid index 0
    first_diff = [None] + [inertia_val[i + 1] - inertia_val[i] for i in range(1, len(inertia_val) - 1)]
    second_diff = [None] + [first_diff[i + 1] - first_diff[i] for i in range(1, len(first_diff) - 1)]
    elbow_index = second_diff.index(max(second_diff[1:]))
    plt.plot(inertia_val[1:])
    elbow_coords = (float(elbow_index), float(inertia_val[elbow_index + 1]))
    ax = plt.gca()

    # Compute aspect ratio of the x and y scales
    x0, x1 = ax.get_xlim()
    y0, y1 = ax.get_ylim()
    dx = x1 - x0
    dy = y1 - y0
    circle_radius = max((x1 - x0), (y1 - y0)) / 10  # adjust as needed

    # Add a circle
    circle = Ellipse(elbow_coords, circle_radius * 2 * dx / dy, circle_radius * 2, color='gray', fill=False, linestyle="--")
    plt.gca().add_patch(circle)
    plt.savefig('elbow.png')


if __name__ == "__main__":
    main()
