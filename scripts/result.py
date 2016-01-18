#!/usr/bin/python

import sys

import subprocess

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

subprocess.call("./all.sh " + sys.argv[1] + " " + sys.argv[2], shell=True)

sum = 0
sub = 0
i = 0
for s in open('speedy/Speedy_' + sys.argv[1] + '_' + sys.argv[2] + '_result.txt'):
	sum += float(s.split()[2])
	i = i + 1
	sub += float(s.split()[10])
msg =  ("speedy" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(sub/i))
print msg
sys.stdout.flush()
sum = 0
sub = 0
i = 0
for s in open('w1_1/w1_1_' + sys.argv[1] + '_' + sys.argv[2] + '_result.txt'):
	sum += float(s.split()[2])
	i = i + 1
	sub += float(s.split()[10])
msg =  ("w1_1" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(sub/i))
print msg
sys.stdout.flush()
sum = 0
sub = 0
i = 0
for s in open('w4/w4_' + sys.argv[1] + '_' + sys.argv[2] + '_result.txt'):
	sum += float(s.split()[2])
	i = i + 1
	sub += float(s.split()[10])
msg =  ("w4" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(sub/i))
print msg
sys.stdout.flush()
sum = 0
sub = 0
i = 0
for s in open('w5/w5_' + sys.argv[1] + '_' + sys.argv[2] + '_result.txt'):
	sum += float(s.split()[2])
	i = i + 1
	sub += float(s.split()[10])
msg =  ("w5" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(sub/i))
print msg
sys.stdout.flush()
sum = 0
sub = 0
i = 0
for s in open('rabinastar/rabinastar_' + sys.argv[1] + '_' + sys.argv[2] + '_result.txt'):
	sum += float(s.split()[2])
	i = i + 1
	sub += float(s.split()[10])
if( i != 0 ):
	msg =  ("rabinastar" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(sub/i))
	print msg
	sys.stdout.flush()
else:
	msg =  ("rabinastar" + " " + sys.argv[1] + " " + sys.argv[2] + " " + "total_time" + " " + str(sum) + " " + "suboptimality" + " " + str(0))
	print msg
	sys.stdout.flush()