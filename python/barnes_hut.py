import random
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

THETA = 0
G = 1
K = 1
DT = 1/5

class Node:
	def __init__(self):
		self.x = float(random.randint(1,99))
		self.y = float(random.randint(1,99))
		self.z = 50 #float(random.randint(41,59))
		self.dx = 0.0
		self.dy = 0.0
		self.dz = 0.0
		self.mass = 1.0

	def __repr__(self):
		return "Node<{:.2f}{:+.2f} {:.2f}{:+.2f} {:.2f}{:+.2f}>".format(self.x,self.dx,self.y,self.dy,self.z,self.dz)
	
	def distance(self, node):
		return np.sqrt((node.x - self.x)**2 + (node.y - self.y)**2 + (node.z - self.z)**2)
	
	def computeForce(self, node):
		dist = self.distance(node)
		dir = np.array([(node.x - self.x)/dist, (node.y - self.y)/dist, (node.z - self.z)/dist])
		f = list(dir * (G*(self.mass*node.mass*K)/dist))
		#if f[0] < 0 or f[1] < 0 or f[2] < 0:
			#print(f)
		return f


class TreeNode:
	def __init__(self, rangex, rangey, rangez):
		self.obj = None
		self.children = None
		self.rx = rangex
		self.ry = rangey
		self.rz = rangez
		self.xsz = (self.rx[1] - self.rx[0])/2
		self.ysz = (self.ry[1] - self.ry[0])/2
		self.zsz = (self.rz[1] - self.rz[0])/2
		self.alive = False
		self.com = None
		self.comNode = None
		self.mass = None
	
	def __repr__(self):
		return "TreeNode<x={:.2f}:{:.2f} y={:.2f}:{:.2f} z={:.2f}:{:.2f}>".format(self.rx[0],self.rx[1],self.ry[0],self.ry[1],self.rz[0],self.rz[1])

	def setupChildren(self):
		self.children = [
			TreeNode((self.rx[0],self.rx[0]+self.xsz),(self.ry[0],self.ry[0]+self.ysz),(self.rz[0],self.rz[0]+self.zsz)),
			TreeNode((self.rx[0],self.rx[0]+self.xsz),(self.ry[0],self.ry[0]+self.ysz),(self.rz[0]+self.zsz,self.rz[1])),
			TreeNode((self.rx[0],self.rx[0]+self.xsz),(self.ry[0]+self.ysz,self.ry[1]),(self.rz[0],self.rz[0]+self.zsz)),
			TreeNode((self.rx[0],self.rx[0]+self.xsz),(self.ry[0]+self.ysz,self.ry[1]),(self.rz[0]+self.zsz,self.rz[1])),
			TreeNode((self.rx[0]+self.xsz,self.rx[1]),(self.ry[0],self.ry[0]+self.ysz),(self.rz[0],self.rz[0]+self.zsz)),
			TreeNode((self.rx[0]+self.xsz,self.rx[1]),(self.ry[0],self.ry[0]+self.ysz),(self.rz[0]+self.zsz,self.rz[1])),
			TreeNode((self.rx[0]+self.xsz,self.rx[1]),(self.ry[0]+self.ysz,self.ry[1]),(self.rz[0],self.rz[0]+self.zsz)),
			TreeNode((self.rx[0]+self.xsz,self.rx[1]),(self.ry[0]+self.ysz,self.ry[1]),(self.rz[0]+self.zsz,self.rz[1]))
		]

	def nodeQuadrant(self, node):
		c = 0
		c += 4*int(node.x > self.rx[0]+(self.xsz))
		c += 2*int(node.y > self.ry[0]+(self.ysz))
		c += 1*int(node.z > self.rz[0]+(self.zsz))
		return c

	def addNode(self, node):
		if self.alive == False:
			self.obj = node
		elif self.children == None:
			self.setupChildren()
			self.children[self.nodeQuadrant(self.obj)].addNode(self.obj)
			self.children[self.nodeQuadrant(node)].addNode(node)
			self.obj = None
		else:
			self.children[self.nodeQuadrant(node)].addNode(node)
		self.alive = True
	
	def rRepr(self):
		out = [str(self)]
		if self.children != None:
			for child in self.children:
				if (child.alive):
					for line in child.rRepr():
						out.append(" " + line)
		elif self.obj != None:
			out.append(" " + str(self.obj))
		return out
	
	def computeMass(self):
		if self.com == None and self.mass == None:
			if self.obj != None:
				self.com = (self.obj.x, self.obj.y, self.obj.z)
				self.mass = self.obj.mass
			elif self.children == None:
				self.mass = 0.0
			else:
				cx = 0.0; cy = 0.0; cz = 0.0; m = 0.0
				for c in self.children:
					ccom, cmass = c.computeMass()
					if cmass > 0.0:
						cx += cmass*ccom[0]
						cy += cmass*ccom[1]
						cz += cmass*ccom[2]
						m += cmass
				self.mass = m
				self.com = (cx/m, cy/m, cz/m)
		
		if self.mass > 0:
			self.comNode = Node()
			self.comNode.x = self.com[0]
			self.comNode.y = self.com[1]
			self.comNode.z = self.com[2]
			self.comNode.mass = self.mass
		
		return self.com, self.mass
	
	def computeForce(self, node):
		if self.obj != None:
			if self.obj == node:
				return [0,0,0]
			else:
				return node.computeForce(self.obj)
		elif self.children != None:
			if self.xsz*2/node.distance(self.comNode) > THETA:
				f = [0,0,0]
				for c in self.children:
					if c.alive:
						fc = c.computeForce(node)
						f[0] += fc[0]
						f[1] += fc[1]
						f[2] += fc[2]
				return f
			else:
				if (self.comNode == None):
					return [0,0,0]
				else: 
					return self.comNode.computeForce(node)

def newUniverse(n):
	nodes = []
	for i in range(0,n):
		nodes.append(Node())
	return nodes

def newSpinningUniverse(n, speed):
	nodes = newUniverse(n)
	for n in nodes:
		n.dy = -(50-n.x)/50*speed
		n.dx = (50-n.y)/50*speed
	return nodes

#nodeA = Node()
#nodeA.mass = 5
#nodeA.x = 50; nodeA.y = 50; nodeA.z = 50;
#heavyNode = nodeA

#nodeB = Node()
#nodeB.mass = 5
#nodeB.x = 120; nodeB.y = 50; nodeB.z = 50;
#nodeB.dy = 10

#objs = newUniverse()
objs = newSpinningUniverse(100, 5)
heavyStar = Node()
heavyStar.x = 50; heavyStar.y = 50; heavyStar.z = 50;
heavyStar.mass = 10
objs.append(heavyStar)

##a = Node(); a.x = 40; a.y = 40; a.z = 40; a.dx = 1;
#b = Node(); b.x = 80; b.y = 80; b.z = 80; b.dx = -1;
#objs = [a,b]

tree = TreeNode((0.0,100.0),(0.0,100.0),(0.0,100.0))	
for o in objs:
	tree.addNode(o)
tree.computeMass()
for o in objs:
	f = tree.computeForce(o)



''' Plottery '''

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
#ax.set_xlim(tree.comNode.x-50, tree.comNode.x+50)
#ax.set_ylim(tree.comNode.y-50, tree.comNode.y+50)
#ax.set_zlim(tree.comNode.z-50, tree.comNode.z+50)
ax.set_xlim(heavyStar.x-50, heavyStar.x+50)
ax.set_ylim(heavyStar.y-50, heavyStar.y+50)
ax.set_zlim(heavyStar.z-50, heavyStar.z+50)

scat1 = ax.scatter(list(map(lambda n: n.x, objs)), list(map(lambda n: n.y, objs)), list(map(lambda n: n.z, objs)), color = 'y')

plt.ion()
plt.show()

ax = plt.gca()
ax.set_facecolor('xkcd:black')

for i in range(0, 10000):
	plt.pause(1e-10)
	if (i%100 == 0):
		print(i)
	
	tree = TreeNode(
		(
		np.min(list(map(lambda n: n.x, objs)))-1,
		np.max(list(map(lambda n: n.x, objs)))+1
		),
		(
		np.min(list(map(lambda n: n.y, objs)))-1,
		np.max(list(map(lambda n: n.y, objs)))+1
		),
		(
		np.min(list(map(lambda n: n.z, objs)))-1,
		np.max(list(map(lambda n: n.z, objs)))+1
		)
		)
	for o in objs:
		tree.addNode(o)
	tree.computeMass()
	for o in objs:
		f = tree.computeForce(o)
		#ax.quiver(o.x, o.y, o.z, f[0]*10, f[1]*10, f[2]*10)
		#ax.quiver([],[],[],[],[],[])
		o.dx += f[0]/o.mass * DT
		o.dy += f[1]/o.mass * DT
		o.dz += f[2]/o.mass * DT
		o.x += o.dx * DT
		o.y += o.dy * DT
		o.z += o.dz * DT
		
	#ax.set_xlim(tree.comNode.x-50, tree.comNode.x+50)
	#ax.set_ylim(tree.comNode.y-50, tree.comNode.y+50)
	#ax.set_zlim(tree.comNode.z-50, tree.comNode.z+50)
	ax.set_xlim(heavyStar.x-50, heavyStar.x+50)
	ax.set_ylim(heavyStar.y-50, heavyStar.y+50)
	ax.set_zlim(heavyStar.z-50, heavyStar.z+50)
	
	scat1._offsets3d = (list(map(lambda n: n.x, objs)), list(map(lambda n: n.y, objs)), list(map(lambda n: n.z, objs)))
