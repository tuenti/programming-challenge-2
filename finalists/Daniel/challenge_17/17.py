#!/usr/bin/python

import sys, multiprocessing
import math
from copy import copy
#import pygame
from time import sleep

#pygame.init()

# http://www.bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
def ccw(A,B,C):
	return (C[1]-A[1])*(B[0]-A[0]) > (B[1]-A[1])*(C[0]-A[0])
def intersect(A,B,C,D):
	return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D)

# http://www.ariel.com.au/a/python-point-int-poly.html
def point_inside_polygon(x,y,poly):
	n = len(poly)
	inside = False
	p1x,p1y = poly[0]
	for i in range(n+1):
		p2x,p2y = poly[i % n]
		if y > min(p1y,p2y):
			if y <= max(p1y,p2y):
				if x <= max(p1x,p2x):
					if p1y != p2y:
						xinters = (y-p1y)*(p2x-p1x)/(p2y-p1y)+p1x
					if p1x == p2x or x <= xinters:
						inside = not inside
		p1x,p1y = p2x,p2y
	return inside

# http://stackoverflow.com/questions/328107/how-can-you-determine-a-point-is-between-two-other-points-on-a-line-segment
def point_inside_line(a, b, c):
	"Return true iff point c intersects the line segment from a to b."
	# (or the degenerate case that all 3 points are coincident)
	return (collinear(a, b, c) 
		and (within(a[0], c[0], b[0]) if a[0] != b[0]
			else within(a[1], c[1], b[1])))
def collinear(a, b, c):
	"Return true iff a, b, and c all lie on the same line."
	return (b[0] - a[0]) * (c[1] - a[1]) == (c[0] - a[0]) * (b[1] - a[1])
def within(p, q, r):
	"Return true iff q is between p and r (inclusive)."
	return p <= q <= r or r <= q <= p


# The real algorithm starts here:
def main(d):
	center = d['center']
	radius = d['radius']
	ingredients = dict() # for storing the number of each ingredient
	
	"""
	pygame_scale = 250 / radius
	pygame_move_x = 250 - (pygame_scale * center[0])
	pygame_move_y = 250 - (pygame_scale * center[1])
	window = pygame.display.set_mode((500, 500))
	color_red = pygame.Color(255, 0, 0)
	color_white = pygame.Color(255, 255, 255)
	color_black = pygame.Color(0, 0, 0)
	window.fill(color_white)
	# draw the pizza
	center_coords = (int((center[0]*pygame_scale)+pygame_move_x), int((center[1]*pygame_scale)+pygame_move_y))
	pygame.draw.circle(window, color_black, center_coords, int(d['radius']*pygame_scale), 1)
	window.set_at(center_coords, color_red)
	"""
	
	for polygon in d['polygons']:
		if not polygon['name'] in ingredients:
			ingredients[polygon['name']] = 0
		polygon['vertices'] = [polygon['vertex']]
		edges = polygon['edges'] - 1
		
		"""
		# check if center is inside the pizza
		x = center[0] - polygon['center'][0]
		y = center[1] - polygon['center'][1]
		dist_to_center = math.hypot(x, y)
		polygon['inside_pizza'] = dist_to_center <= radius
		"""
		
		x = polygon['vertex'][0] - polygon['center'][0]
		y = polygon['vertex'][1] - polygon['center'][1]
		dist_to_center = math.hypot(x, y)
		angle = math.atan2(y, x) # -pi/2: up, 0: right, pi/2: down, pi: left
		step = math.pi * 2 / polygon['edges']
		while edges:
			new_angle = angle + edges*step
			if new_angle > math.pi:
				new_angle -= 2*math.pi
			v_x = math.cos(new_angle) * dist_to_center + polygon['center'][0]
			v_y = math.sin(new_angle) * dist_to_center + polygon['center'][1]
			polygon['vertices'].append((v_x, v_y))
			edges -= 1
	
	if d['polygons'] == []: # if pizza has no ingredients, that's easy
		return "TRUE"
	
	"""
	for polygon in d['polygons']:
		v = []
		for vertex in polygon['vertices']:
			v.append( (int((vertex[0]*pygame_scale)+pygame_move_x), int((vertex[1]*pygame_scale)+pygame_move_y)) )
		pygame.draw.polygon(window, color_black, v, 1)
		window.set_at( (int((polygon['center'][0]*pygame_scale)+pygame_move_x), int((polygon['center'][1]*pygame_scale)+pygame_move_y)), color_red)
		pygame.display.update()
		sleep(2)
	sleep(2)
	"""
	
	# First, check if an ingredient is covering the center of the pizza.
	# If it's true, it's impossible to cut the pizza without cutting the ingredient.
	count_ingredients = copy(ingredients)
	for polygon in d['polygons']:
		if point_inside_polygon(center[0], center[1], polygon['vertices']):
			return "FALSE"
		# also, check if the pizza has odd number of any ingredient
		count_ingredients[polygon['name']] += 1
	for i in count_ingredients.itervalues():
		if i % 2:
			return "FALSE"
	
	# The problem limits are fairly low, so the algorithm is as follows:
	# Iterate through all vertices of all ingredients. For each vertex,
	# draw a line that goes through that vertex and the center of the pizza.
	# Then, check if that line crosses with any ingredient edge.
	# If there is a line that can cut the pizza, check if both sides have
	# the same number of ingredients.
	#print
	#print "***************************"
	#print
	for polygon in d['polygons']:
		#print
		#print "-------------------------"
		#print polygon
		for vertex in polygon['vertices']:
			#print
			#print vertex
			# Line between vertex and pizza center: (A,B)
			angle = math.atan2(center[1]-vertex[1], center[0]-vertex[0])
			v_x = math.cos(angle) * radius
			v_y = math.sin(angle) * radius
			A = (v_x + center[0], v_y + center[1])
			v_x *= -1
			v_y *= -1
			B = (v_x + center[0], v_y + center[1])
			
			"""
			A_coords = (int((A[0]*pygame_scale)+pygame_move_x), int((A[1]*pygame_scale)+pygame_move_y))
			B_coords = (int((B[0]*pygame_scale)+pygame_move_x), int((B[1]*pygame_scale)+pygame_move_y))
			pygame.draw.line(window, color_red, A_coords, B_coords, 1)
			pygame.display.update()
			sleep(2)
			"""
			
			if angle < 0:
				angle += math.pi # between 0 and pi, for slope comparison
			# Iterate again through the ingredients, to check if the line cuts any of them.
			valid_line = True
			for poly2 in d['polygons']:
				#print poly2
				for v in xrange(poly2['edges']):
					# each edge is the line between the point and the previous point (index -1 does the trick in python)
					C = poly2['vertices'][v-1]
					D = poly2['vertices'][v]
					if C == vertex or D == vertex:
						continue # we know that the line will dodge this edge
					#print A, B, C, D
					angle2 = math.atan2(C[1]-D[1], C[0]+D[0])
					if angle2 < 0:
						angle2 += math.pi # between 0 and pi, for slope comparison
					if angle2 == angle:
						continue # parallel / coincident lines. This is valid
					if C in (A, B) or D in (A, B): # if vertex just touches the cut at the edge of the pizza, it's ok
						continue
					if point_inside_line(A, B, C): # point D will be handled in the next segment
						if intersect(A, B, poly2['vertices'][v-2], D): # It's cutting the ingredient
							valid_line = False
							break
						else: # It's just touching the vertex
							continue
					if intersect(A, B, C, D):
						valid_line = False
						break
				if not valid_line:
					break
			if valid_line:
				# Now check if both sides have the same number of each ingredient
				one_side = copy(ingredients)
				other_side = copy(ingredients)
				for poly3 in d['polygons']:
					if ccw(A, B, poly3['center']):
						one_side[poly3['name']] += 1
					else:
						other_side[poly3['name']] += 1
				if one_side == other_side:
					#print one_side, other_side
					return "TRUE"
	
	return "FALSE"

def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	line = sys.stdin.readline()
	input_dump.write(line)
	n = int(line)
	for _ in xrange(n):
		d = dict()
		
		line = sys.stdin.readline()
		input_dump.write(line)
		center_x, center_y, d['radius'] = map(float, line.split())
		d['center'] = (center_x, center_y)
		
		line = sys.stdin.readline()
		input_dump.write(line)
		n_ingredients = int(line)
		d['polygons'] = []
		
		for _ in xrange(n_ingredients):
			line = sys.stdin.readline()
			input_dump.write(line)
			name, n_edges, number = line.split()
			n_edges = int(n_edges)
			for _ in xrange(int(number)):
				line = sys.stdin.readline()
				input_dump.write(line)
				c_x, c_y, v_x, v_y = map(float, line.split())
				d['polygons'].append({'name':name, 'edges':n_edges, 'center':(c_x,c_y), 'vertex':(v_x,v_y)})

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	for n, result in enumerate(pool.map(main, data)):
	#for n, d in enumerate(data):
	#	result = main(d)
		print("Case #" + str(n+1) + ": " + str(result))
