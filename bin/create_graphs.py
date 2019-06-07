import math

import matplotlib
#matplotlib.use("Tkagg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import scipy.optimize as opt
from matplotlib.ticker import FormatStrFormatter

def get_data_from_file(filename):
    data = pd.read_csv(filename)
    print data

    if filename == "diameter.csv":
        n = data['n'].values
        diameters = data['diameter'].values

        draw_diameters(n, diameters)

    elif filename == "cluster.csv":
        n = data['n'].values
        coeffs = data['coeff'].values
        densities = data['density'].values

        draw_clustering_coefficients(n, coeffs, densities)

    elif filename == "degree.csv":
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
    ax.xaxis.set_major_formatter(FormatStrFormatter('%d'))
    ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
    ax.legend()
    ax.grid(alpha = .4, linestyle = '--')

def draw_log_line(ax):
    x = np.linspace(10, 100000, 10000)
    ax.plot(x, np.log(x), c = 'C3', label = '$diameter(n) = \\log{n}$')

def draw_step_line(ax):
    x = np.linspace(10, 100000, 10000)
    ax.plot(x, np.piecewise(x, [x < 80, x >= 80, x >= 5120], [3, 4, 5]), 
            alpha = 0.75,
            label = 'fitted piecewise function')

def draw_diameters(n, diameters):
    _, ax = plt.subplots(1, 1, figsize = (6, 6))
    ax.scatter(n, diameters)
    ax.set_xscale('log')
    draw_log_line(ax)
    draw_step_line(ax)
    set_up_plot(ax,
                "Lin-Log Graph of Average Diameters",
                "log of number of nodes",
                "average diameters")
    #plt.show()
    plt.savefig("diameter.png")

def func(x, a):
    return a * (np.log(x)) / x

def draw_curve(ax, x, y):
    xdata = np.linspace(10, 100000, 10000)
    popt, _ = opt.curve_fit(func, x, y)
    ax.plot(xdata, func(xdata, *popt), alpha = 0.75,
        label = "$CC(n) = \\frac{%.3f\\log {n}}{n}$" % tuple(popt))

def draw_clustering_coefficients(n, coeffs, densities):
    _, ax = plt.subplots(1, 1, figsize = (6, 6))
    ax.plot(n, densities, c = 'C3', label = 'average edge densities')
    ax.scatter(n, coeffs, label = 'average coefficients')
    draw_curve(ax, n, coeffs)
    ax.set_xscale('log')
    set_up_plot(ax,
                "Lin-Log Graph of Average Clustering Coefficients",
                "log of number of nodes",
                "average clustering coefficients")
    #plt.show()
    plt.savefig("cluster.png")

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
        ax[1].set_xscale('log')
        ax[1].set_yscale('log')
        set_up_plot(ax[1], 
                    "Same Data on Log-Log Scale",
                    "log of degree",
                    "log of frequency")

        #plt.show()
        plt.savefig("degree{}.png".format(N))

if __name__ == "__main__":
    #get_data_from_file("diameter.csv")
    get_data_from_file("cluster.csv")
    #get_data_from_file("degree.csv")
