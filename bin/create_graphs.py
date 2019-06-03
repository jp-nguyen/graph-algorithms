import matplotlib
#matplotlib.use("Tkagg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math
import scipy.optimize as opt

def get_data_from_file(filename):
    data = pd.read_csv(filename)
    print data

    if filename == "degree.csv":
        n = data['n'].values
        degrees = data['degree'].values
        counts = data['count'].values

        draw_degree_distribution(n, degrees, counts)

def set_up_plot(ax, title, xlabel, ylabel):
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_xticklabels(ax.get_xticks(), fontsize = 10)
    ax.set_yticklabels(ax.get_yticks(), fontsize = 10)
    ax.grid(alpha = .4, linestyle = '--')

def draw_degree_distribution(n, degrees, counts):
    for N in np.unique(n):
        mask = np.where(n == N)[0]
        
        _, ax = plt.subplots(1, 2, figsize = (12, 6), tight_layout = True)
        ax[0].bar(degrees[mask], counts[mask])
        set_up_plot(ax[0], 
                    "Lin-Lin Degree Distribution of {} Nodes".format(N),
                    "degree",
                    "frequency of degree")
        ax[1].scatter(np.log(degrees[mask]), np.log(counts[mask]), 
                    s = 80, facecolors = 'none', edgecolors = 'C3')
        set_up_plot(ax[1], 
                    "Same Data on Log-Log Scale",
                    "log of degree",
                    "log of frequency")

        #plt.show()
        plt.savefig("degree{}.png".format(N))

if __name__ == "__main__":
    get_data_from_file("cluster.csv")
    get_data_from_file("degree.csv")
    #get_data_from_file("diameter.csv")