import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_excel('data.xlsx')

# Scatter
plt.figure(figsize = (8, 6))
plt.scatter(data['身高/cm'], data['体重/kg'], s = 30, marker = 'x')
#plt.title('Weight-Height Scatter', size = 16)
plt.xlabel('Height / cm', size = 14)
plt.ylabel('Weight / kg', size = 14)
plt.xticks(range(157, 187, 2), size = 12)
plt.yticks(range(40, 95, 5), size = 12)
plt.savefig("scatter0.png", dpi = 300)
plt.show()

# Colored scatter
grouped = data.groupby("性别")
girls = grouped.get_group('女')
boys = grouped.get_group('男')

plt.figure(figsize = (8, 6))
plt.scatter(girls['身高/cm'], girls['体重/kg'], s = 30, marker = 'o', label = 'Female')
plt.scatter(boys['身高/cm'], boys['体重/kg'], s = 30, marker = 'x', label = 'Male')
plt.legend(loc = 6)
#plt.title('Weight-Height Scatter', size = 16)
plt.xlabel('Height / cm', size = 14)
plt.ylabel('Weight / kg', size = 14)
plt.xticks(range(157, 187, 2), size = 12)
plt.yticks(range(40, 95, 5), size = 12)
plt.savefig("scatter1.png", dpi = 300)
plt.show()