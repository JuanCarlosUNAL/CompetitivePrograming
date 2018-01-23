'''
1
7C 8C 5S 8D AC JC 3S AD 2H 6S AS 7S 9D 5H 8S JS 2C 2S 3H KS QC QS JD 6C KD AH 2D 7H JH 9C TD 6D 6H KH 9H 4D QH 7D TC KC 3D QD 9S TS 8H 3C TH 4S 5D 5C 4H 4C 
'''
import sys

cases = int(sys.stdin.readline())
case = 1
while cases > 0:
	cartas = sys.stdin.readline().strip().split(" ")

	i = 0
	pos = 27
	y = 0
	while i < 3:
		if cartas[pos-1][0].isdigit(): 
			val = int(cartas[pos-1][0]) 
		else:
			val = 10
		y += val
		init = (10 - val) +1
		del cartas[pos-init:pos]
		pos -= init
		i += 1

	print ( "Case", str(case)+":", cartas[y-1] )

	case += 1
	cases -= 1
