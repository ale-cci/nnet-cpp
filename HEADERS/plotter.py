import numpy as np
import matplotlib.pyplot as plt
import time


times = []
values = [[],[],[],[]]
learning_rate = None
momentum = None
pt_diff = None

graph_name = input("Graph Name: ").strip()
with open("plotdata.txt") as input:
	learning_rate = input.readline()
	momentum = input.readline()
	pt_diff = int(input.readline().strip())
	for t, v in enumerate(input):
		if t%4 == 0:
			times.append(t)
		values[t%4].append(v)

t = np.int_(times)

fig = plt.figure()
fig.suptitle('NNet Error')
ax = fig.add_subplot(111)

ax.set_xlabel('# Backpropagations')
ax.set_ylabel('Error')
for v in values:
	ax.plot(t, np.float32(v))
ax.set_xlim([0, t.size*pt_diff])
ax.set_ylim([0, 0.7])

ax.plot([0, t[-1]], [0.05, 0.05], 'r-')

ax.text(0.90, 0.88, ' λ={0} μ={1}'.format(learning_rate, momentum),
        verticalalignment='bottom', fontsize=8,
       transform=ax.transAxes)
if graph_name != "":
	plt.savefig('PLOTS/{0}.png'.format(graph_name))
plt.show()