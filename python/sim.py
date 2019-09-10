import random
import matplotlib.pyplot as plt
import numpy as np
import time
import math
from mpl_toolkits.mplot3d import Axes3D

obj = np.array([
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0],
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0],
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0],
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0],
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0],
    [random.randint(1,100), random.randint(1,100), random.randint(1,100), 0.0, 0.0, 0.0]
    ])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(0, 100)
ax.set_ylim(0, 100)
ax.set_zlim(0, 100)
scat = ax.scatter(obj[:,0], obj[:,1], obj[:,2])
fig.show()

for i in range(0, 1000):
    plt.pause(0.001)
    
    for o in obj:
        o[5] += 0.03
        o[2] = max(0,o[2]-o[5])
        
        if o[2] == 0:
            o[5] = -.5*(abs(o[5]))
    
    scat._offsets3d = (obj[:,0], obj[:,1], obj[:,2])
    plt.draw()