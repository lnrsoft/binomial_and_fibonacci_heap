#!/usr/bin/python
import sys

if (len(sys.argv) == 2):
    f = open(sys.argv[1], "r")
    for linea in f:
        if linea[-1] == "\n":
            linea = linea[:-1]
        (info,connections) = linea.split("--")
        (this,value,rang) = info[1:-1].split(",")
        this = this.split(":")[1]
        value = value.split(":")[1]
        rang = rang.split(":")[1]
        print this, value, rang
        (father,broforward,brobackward,sons) = connections[1:-1].split(",")
        father = father.split(":")[1]
        broforward = broforward.split(":")[1]
        brobackward = brobackward.split(":")[1]
        sons = sons.split(":")[1]
        print father, brobackward, broforward, sons
else:
#Error, invalid number of parameters
    print "Error, invalid number of parameters"
