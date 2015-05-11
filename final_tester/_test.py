# -*- coding: UTF-8 -*-
import time
import os
import timeit
import threading

problems = {'A' : "Goddess-Hunter",\
           'B' : "No-Title",\
           'C' : "Rank-of-Sum",\
           'D' : "String-Counter",\
           'E' : "String-Game",\
           'F' : "Villa-Builder",\
           'G' : "Oyk-Cut-Paper-Again",\
           'H' : "Matrix",\
           'I' : "Nightmare",\
           'J' : "The-xor-longest-Path"\
           }


timelimit = {'A' : "Goddess-Hunter 2s",\
           'B' : "No-Title 1s",\
           'C' : "Rank-of-Sum 2s",\
           'D' : "String-Counter 2s",\
           'E' : "String-Game 3s",\
           'F' : "Villa-Builder 2s",\
           'G' : "Oyk-Cut-Paper-Again 1s",\
           'H' : "Matrix 1s",\
           'I' : "Nightmare 2s",\
           'J' : "The-xor-longest-Path 2s"\
           }

parameter = {'g++' : 'g++ -O2 -std=c++11 -lm -o main main.cpp',\
             'gcc' : 'gcc -O2 -std=gnu99 -lm -o main main.c',\
             'java' : 'javac Main.java'}

def count():
    time.sleep(10)
    print u"本程序已运行10s以上，若程序未运行完，可关闭程序并判TLE"
    os.system("pause")
    exit()

def run():
    if id[1] == 'java':
        s = 'java ' + id[2] + '<data\\' + name + '.in >test.out'
    else:
        s = 'main <data\\' + name + '.in >test.out'
    t = timeit.timeit('os.system("' + s + '")', setup = 'import os', number = 1)
    print u"运行用时：%.3fs" % t

os.system("del *.out")
os.system("del *.exe")
os.system("del *.class")
print
print
print 
print u"————————————————正文分割线———————————————————"

for p in sorted(problems.items()):
    print p
print

for p in parameter.items():
    print p
print

print u"请输入题目编号和编译器，并将代码保存于main.cpp/main.c/?.java中"
print u"Sample: A g++ / A gcc / A java Main(java需要文件名)"

id = raw_input().split()
name = problems[id[0].upper()]
args = parameter[id[1]]

time1 = time.time()
if id[1] == 'java':
    os.system('javac ' + id[2] +'.java')
else:
    os.system(args)
time2 = time.time()
print u"编译用时：%.3fs" % (time2 - time1)

for t in [threading.Thread(target = count)]:
    t.setDaemon(True)
    t.start()

print u"第一次运行"
run()
print u"第二次运行"
run()
print u"时限：" + timelimit[id[0].upper()]

os.system("fc data\\" + name + ".out test.out")

os.system("pause")
