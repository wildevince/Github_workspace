#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#@author: vwilde
#"""


import sys, os, random, re, datetime

# sécuriser la saisi du parametre
if len(sys.argv) == 1 :
    print("\n\nVous devez donner un parametre au script")
    param = input("pas besoin ^^ :")
else :
    param = sys.argv[1]  

class Matrix :
    ### bloc initialisation des cout
    c_match = 2
    c_mis = 1 #neg
    c_indel = 1 #lineaire + neg
    def __init__ (self, seq1, seq2) :
        self.S1 = seq1
        self.S2 = seq2
        self.content = CTab(self.S1, self.S2)
    #

## absciss = S2
# ordonner = s1

    def __str__ (self) :
        i = 0
        while (i <= len(self.content) ) :    #### 
            tabseq =[]
            if (i == 0) :
                tabseq.append(" ")
                tabseq.append("-")
                k = 0
                while ( k < len(self.S1) ) :
                    tabseq.append( S1[k] )
                    k += 1
            else : 
                newchar = "-" if (i == 1) else S2[i] 
                tabseq.append( newchar )
                j = 0
                while ( j < len(self.content[0]) ) :
                    tabseq.append( (self.content[j][i-1] ) )
                    j +=  1
                #
            print(tabseq )
            i += 1
    # fin ___str___  


        #


def CTab(seq1, seq2) :
    Matt = []
    j = 0 
    while (j <= len(seq2) ) :
        Matt.append( [] )
        i = 0
        while (i  <= len(seq1) ) :
            Matt[j].append(0)
            i += 1
        j += 1
        
    return(Matt)





### ___ main ___ ## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___###


# alignement 2 à 2 
# align global , matrice de similatirté
#    fixer cout des gap
#    fixer cout match/dismatch

## /\ use l'objet Seq .... moi  non ^^  : stings only

### bloc initialisation des séquences
S1 = "ACGGCT" 
S2 = "ACTGT"

Matt = Matrix(S1,S2)

print(Matt)

# print(len(S1)) == 6  

