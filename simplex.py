#!/usr/bin/python

import sys
from fractions import Fraction

cellsize = 3  # for formatting output

# prints 2d 'array'
def pm(M):
	for row in M:
		for x in row:
			sz = len('{}'.format(x))
			print(' '*(cellsize - sz) + '{}'.format(x), end=', ')
		print('')
	print('')



# prints table
def pt(Mlist):
	for i in range(len(Mlist[0])):
		for t in Mlist:
			print(t[i], end='   ')
		print('')


# prints certificate
def pv(y):
	for i in range(len(y)):
		if i < len(y) - 1:
			print('{0:.7f}'.format(y[i].numerator/y[i].denominator).rstrip('0').rstrip('.'), end=' ')
		else:
			print('{0:.7f}'.format(y[i].numerator/y[i].denominator).rstrip('0').rstrip('.'))



# appends matrix Mb below Ma
def appd(Ma, Mb):
	if not Ma or not Mb:
		print('{} is invalid'.format(Ma if not Ma else Mb))
		return None
	if len(Ma[0]) != len(Mb[0]):
		print('number of columns don\'t match')
		pm(Ma)
		pm(Mb)
		return None
	r = Ma + Mb
	return r



# appends matrix Mb to the right of Ma, not inplace
def appr(Ma, Mb):
	if not Ma or not Mb:
		print('{} is invalid'.format(Ma if not Ma else Mb))
		return None
	if len(Ma) != len(Mb):
		print('number of rows don\'t match')
		pm(Ma)
		pm(Mb)
		return None
	r = []
	for i in range(len(Ma)):
		r.append(Ma[i] + Mb[i])
	return r



def bpositive(M):
	for row in range(len(M)):
		if M[row][-1] < 0:
			M[row] = [-x for x in M[row]]

	return ([x[:-1] for x in M], [[x[-1]] for x in M])

#all(xx >= 0 for xx in [x[-1] for x in A]


def swapBelow(M, row, col):

	below = [x[col] for x in M[row + 1:]]
	for i in range(len(below)):
		if below[i] != Fraction(0):
			M[row], M[row + i + 1] = M[row + i + 1], M[row]
			return M

	print('I f*ckd up')
	return False # this should never happen



# adds M[][c] to the base through element M[i][j]
def esc(M, r, c):

	for i in range(len(M)):

		if i == r: 	# will change the pivot row later
			continue

		row_mult = -M[i][c] / M[r][c]

		for j in range(len(M[0])):
			M[i][j] = M[i][j] + (row_mult * M[r][j])

	M[r] = [x/M[r][c] for x in M[r]]

	return M



def identity(rank):
	I = [[Fraction(0) for c in range(rank)] for r in range(rank)]
	for i in range(rank):
		I[i][i] = Fraction(1)
	return I



def primal(M, id_size, base):

	for idx, value in enumerate(base):
		if value != 0:
			M = esc(M, value, idx + id_size)

	unlimited = True
	for c in range(id_size, len(M[0])):
		for r in range(len(M)):
			if M[r][c] > 0:
				unlimited = False
	if unlimited:
		return (False, M, M[0][:id_size])

	# main simplex loop
	while not all(x >= 0 for x in M[0][id_size:-1]):

		pivot = (-1, -1, Fraction(sys.maxsize))
	
		col = id_size  # always start after certificate index
		while(M[0][col] >= 0 and col < len(M[0])):
			col += 1
	
		assert(col < len(M[0]))
	
		row = 1  # always start after c row index
		while(row < len(M)):
			if M[row][col] > 0 and M[row][-1] / M[row][col] < pivot[2]:
				pivot = (row, col, M[row][-1] / M[row][col])
			row += 1
	
		if pivot[2] == Fraction(sys.maxsize):
			return (False, M, M[0][:id_size])
			
	
		base[base.index(pivot[0])] = 0
		base[pivot[1] - id_size] = pivot[0]
	
		esc(M, pivot[0], pivot[1])
			

	solucao = [0 for x in base[:-id_size]]
	for idx, value in enumerate(base[:-id_size]):
		if value != 0:
			solucao[idx] = M[value][-1]

	return (True, M, M[0][:id_size], M[0][-1], solucao)



def auxPL(M, id_size):

	# making trivial base
	row  = 1
	base = [0 for x in M[0][id_size:-1]]
	for i in range(len(M[0]) - id_size - 1, len(M[0]) - 1):
		base[i - id_size] = row
		row += 1

	# changing M to canonical form
	row = 1
	col  = len(M[0]) - id_size - 1
	while row < len(M) and col < len(M[0]) - 1:
		M = esc(M, row, col)
		row += 1
		col += 1

	# main simplex loop
	while M[0][-1] != 0 and not all(x >= 0 for x in M[0][id_size:-1]):
		pivot = (-1, -1, Fraction(sys.maxsize))

		col = id_size  # always start after certificate index
		while(M[0][col] >= 0 and col < len(M[0])):
			col += 1

		assert(col < len(M[0]))

		row = 1  # always start after c row index
		while(row < len(M)):
			if M[row][col] > 0 and M[row][-1] / M[row][col] < pivot[2]:
				pivot = (row, col, M[row][-1] / M[row][col])
			row += 1

		assert(pivot[2] != Fraction(sys.maxsize))

		base[base.index(pivot[0])] = 0
		base[pivot[1] - id_size] = pivot[0]

		esc(M, pivot[0], pivot[1])

	if M[0][-1] < Fraction(0):
		return (False, M, M[0][:id_size])

	else:
		M = M[1:]
		vero = [x[:id_size] for x in M]

		M = [x[id_size:] for x in M]
		base = base[:-id_size]

		aux = [xx for xx in list(range(1, id_size + 1)) \
			   if xx not in [x for x in base if x != 0]]

		for r in aux:
			for cidx in range(len(M[r - 1]) - (id_size + 1)):
				if M[r - 1][cidx] != 0:
					M = esc(M, r - 1, cidx)
					base[cidx] = r
					break
		M = [x[:-(id_size + 1)] + x[-1:] for x in M]
		M = appr(vero, M)
		return (True, M, base)




if __name__ == '__main__':
	
	aux = input().split(' ')
	m = int(aux[0])
	n = int(aux[1])

	aux = input().split(' ')
	c = [-Fraction(x) for x in aux]

	A = []
	b = []
	for i in range(m):
		aux = input().split(' ')
		A.append([Fraction(x) for x in aux])
		b.append([A[-1][-1]])
		A[-1].pop()

	c += [Fraction(0) for x in range(len(A))] # slack variables in c
	c_ext = [[Fraction(0) for x in range(len(A))] + [x for x in c[:-len(A)]] \
			+[Fraction(0) for x in range(len(A))] + [Fraction(0)]]
	c_aux = [[Fraction(0) for x in range(len(A))] + [Fraction(0) for x in range(len(c))] \
			+[Fraction(1) for x in range(len(A))] + [Fraction(0)]]

	I = identity(len(A))
	M = appr(I, A)  # left idendity matrix to record operations
	M = appr(M, I)	# slack variables
	M = appr(M, b)
	M, posb = bpositive(M)  # make sure b is >= 0, return A split from b
	M = appr(M, I)  # auxiliary identity matrix to find valid base
	M = appr(M, posb)
	M = appd(c_aux, M)

	result  = auxPL(M, len(I))

	if (result[0]):
		# append the real c to M
		#M = appd(c_ext, result[1])
		M = appd(c_ext, result[1])
		result = primal(M, len(I), result[2])
		if(result[0]):
			print('otima')
			print(result[3])
			pv(result[4])
			pv(result[2])
		else:
			print('ilimitada')
			pv(result[2])

	else:
		print('inviavel')
		pv(result[2])