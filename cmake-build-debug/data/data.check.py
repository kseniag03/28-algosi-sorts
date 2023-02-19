# build graphs

import os
import csv
import matplotlib.pyplot as plt

# List of directories with data

data_dir_list = [
    "D:\\Contest_check\\algosi\\chw01\\data-check",
    "D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\time-50",
    "D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\count-50",
    "D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\time-100",
    "D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\count-100"
    ]

# Get a list of all CSV files in the "data" directory

for data_dir in data_dir_list:
    csv_files = [f for f in os.listdir(data_dir) if f.endswith('.csv')]

    print(len(csv_files))
    cnt = 1;

    # Loop through each CSV file
    for csv_file in csv_files:
        plt.figure(figsize=(25, 25))

        print(csv_file)
        
        # Read the CSV file and extract the data
        csv_path = os.path.join(data_dir, csv_file)
        with open(csv_path, 'r') as f:
            reader = csv.reader(f, delimiter=';')
            title = next(reader)[0]
            legend = next(reader)[1:]
            data = [row for row in reader]

        #print(data)    

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

        # Save the plot to a file
        plt.savefig(f"{csv_path[:-4]}.png")

        # Clear current plot
        plt.clf()

        # Show the plot
        #plt.show()



#data_dir = "D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\count-100"
    
# D:\Contest_check\algosi\chw01\\data-check
# D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\time-50
# D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\count-50
# D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\time-100
# D:\\Contest_check\\algosi\\chw01\\data-check\\sorts-graphs\\count-100
