import csv
import numpy as np

data = []
with open('data1700844515.csv', 'r') as file:
    csv_reader = csv.DictReader(file, delimiter=';')
    for row in csv_reader:
        data.append(row)

cpu_values = []
for row in data:
    cpu_value = int(row['CPU_0'])
    cpu_values.append(cpu_value)
    
print(np.mean(cpu_values))