import os
import csv
import matplotlib.pyplot as plt

# Get a list of all CSV files in the current directory
csv_files = [f for f in os.listdir('.') if f.endswith('.csv')]

# Loop through each CSV file
for csv_file in csv_files:
    # Read the CSV file and extract the data
    with open(csv_file, 'r') as f:
        reader = csv.reader(f)
        title = next(reader)[0]
        legend = next(reader)[1:]
        data = [row for row in reader]

    # Transpose the data and convert the values to floats
    arguments = [float(row[0]) for row in data]
    values = [[float(x) for x in row[1:]] for row in data]
    values_T = list(map(list, zip(*values)))

    # Create a line plot for each value series
    for i, col in enumerate(legend):
        plt.plot(arguments, values_T[i], label=col)

    # Set the title and axis labels
    plt.title(title)
    plt.xlabel('Argument')
    plt.ylabel('Value')
    plt.legend()

    # Show the plot
    plt.show()
