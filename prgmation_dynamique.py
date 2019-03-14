#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#@author: vwilde
#"""


#import sys
#, os, random, re, datetime
"""
# sécuriser la saisi du parametre
if len(sys.argv) == 1 :
    print("\n\nVous devez donner un parametre au script")
    param = input("pas besoin ^^ :")
else :
    param = sys.argv[1]  
"""
class Matrix :
    ### bloc initialisation des cout
    c_match = 2
    c_mis = 1 #neg
    c_indel = 1 #lineaire + neg
    #matrice de similarité
    alphaB = ['A','C','G','T']
    #pos = [] 
    
    def __init__ (self, seq1, seq2) :
        self.S1 = seq1
        self.ls1 = len(self.S1)
        self.S2 = seq2
        self.ls2 = len(self.S2)
        self.content = CTab( self.S1, self.S2 )
        self.MS = CMS( Matrix.alphaB , Matrix.c_match, Matrix.c_mis)
    #

    ## absciss = S2
    # ordonner = s1

    def affiche(self) :
        print ("matrice de similarité :")
        for X in self.MS : 
            print (X)
        print("")
        print("Matrice de score :")
        i = 0
        while ( i <= self.ls2 ) :
            j = 0
            tab = []
            while ( j <= self.ls1 ) :
                tab.append( self.content[i][j][0] )
                j += 1
            print(tab)
            i += 1
        #
    # fin ___str___  
    
    #
    def insert(self,i,j) :
        return ( self.content[i-1][j][0] - Matrix.c_indel )
    
    def deletion(self,i,j) :
        return ( self.content[i][j-1][0] - Matrix.c_indel )
    
    def match_mist(self,i,j) :
        case1 = self.content[i-1][j-1][0] - Matrix.c_mis 
        case2 = self.content[i-1][j-1][0] + Matrix.c_match 
        return ( case2 if( self.S1[j-1] == self.S2[i-1] ) else case1)
    
    def madmax(self,i,j) :
        indel_max = max( self.deletion(i,j), self.insert(i,j) )
        return( max( indel_max, self.match_mist(i,j) ) )
    
    def findScore_throught_table(self, char1, char2) :
        iChar2 = 0
        while ( iChar2 < len(self.alphaB) ) :
            if ( char2 == self.alphaB[iChar2] )  : 
                if ( char1 == char2 ) : 
                    return ( self.MS[iChar2][iChar2]  )
                else :
                    iChar1 = 0
                    while (iChar1 < len(self.alphaB)) :
                        if (char1 == self.alphaB[iChar1]) :
                            return ( self.MS[iChar2][iChar1] )
                        iChar1 += 1
            iChar2 += 1
        #
                
        
    
    def initier_score(self) :
        k=1
        while ( k-1 < self.ls1 ) :
            self.content[0][k][0] = self.deletion(0,k)
            k +=1
        k = 1
        while ( k-1 < self.ls2 ) :
            self.content[k][0][0] = self.insert(k,0) 
            k +=1
        #
    
    """ Le but de mark est de marquer l'origine du calcule seulement dans les cases du milieu 
    (exemple :)  1 pour diagonal   2 pour verticale    0 pour horizotale
    
    - , - , - , - , - , - , -
    - , 1 , 0 , 0 , 0 , 0 , 0
    - , 2 , 1 , 0 , 0 , 0 , 0
    - , 2 , 2 , 1 , 0 , 0 , 1
    - , 2 , 2 , 1 , 1 , 0 , 0
    - , 2 , 2 , 2 , 2 , 1 , 1
    
    ou !!
    
    tu rempli une séquence bis qui garde mémoire de la trace
    
    """
    def mark(self,i,j):
        start = 0 + ( 0 if( (i-self.ls2/2)<0) else ( (i-self.ls2/2) if ((i-self.ls2/2)<self.ls1/2) else (self.ls1/2 -1) ))
        end = self.ls1/2 + ( (i+1) if((i+1)<self.ls1/2) else (self.ls1/2 -1) )
        return ( True if( (j >= start) and (j < end) ) else False )
    
    def remplir(self) :
        i = 1   #sequence S2
        while ( i-1 < self.ls2 ) :
            j = 1   #sequence S1
            while ( j-1 < self.ls1 ) :
                if ( self.deletion(i,j) >= max( self.insert(i,j) , self.match_mist(i,j) ) ):
                    self.content[i][j][0] = self.deletion(i,j)
                    #self.pos.append(j-1)
                    if (self.mark): self.content[i][j].append(0)
                elif ( self.insert(i,j) >= self.match_mist(i,j) ):
                    self.content[i][j][0] = self.insert(i,j)
                    #self.pos.append(j-1)
                    if (self.mark): self.content[i][j].append(2)
                else : 
                    self.content[i][j][0] = self.match_mist(i,j)
                    #if (self.S1[j-1] != self.)
                    if (self.mark): self.content[i][j].append(1)
                    #
                j += 1
            i += 1
        #
    #
    def backtrack(self) :
        print("")
        print("Résultat d'alignement :")
        #self.content[self.ls2-1][self.ls1-1]
        seq1 = "" #self.S1[self.ls1-1]      #aligned sequence 1
        seq2 = "" #self.S2[self.ls2-1]      #aligned sequence 2
        i = self.ls2
        j = self.ls1
        while (i > 0 and j > 0) :
            if (self.content[i][j][1] > 0) :    # soit match ou insertion
                if (self.content[i][j][1] < 2) :    # match
                    seq1 += self.S1[j-1]
                    seq2 += self.S2[i-1]
                    i -= 1
                    j -= 1
                else :                           # insertion
                    seq1 += "-"
                    seq2 += self.S2[i-1]
                    i -= 1
                #fin 2nd if 
            else :                              # deletion
                    seq1 += self.S1[j-1]
                    seq2 += "-"
                    j -= 1
        #fin while
        self.S1 = seq1[::-1]
        self.S2 = seq2[::-1]
        print(seq1[::-1])
        print(seq2[::-1])
        # fin
        
    def give_pos_mutation(self) :
        pos = []
        i_max = max(self.ls1, self.ls2)
        i = 0
        while (i < i_max) :
            if (self.S1[i] != self.S2[i] ) : 
                pos.append(i+1)
            i += 1
        aff = input("Afficher les positions ?   1 = oui    0 = no ")
        if (aff != 0) :
            print("Les positions des mutations sont : ")
            print(pos)
        #
    
    #
#fin class

def CTab(seq1, seq2) :
    Matt = []
    j = 0 
    while (j <= len(seq2) ) :
        Matt.append( [] )
        i = 0
        while (i  <= len(seq1) ) :
            Matt[j].append( [0] )
            i += 1
        j += 1
    return(Matt)

def CMS(alphaB, cout_Match, cout_Mis) :
    MS=[]
    ka = 0
    while ( ka < len(alphaB)) :
        MS.append( [] )
        kb = 0
        while (kb < len(alphaB)) :
            if (alphaB[ka] == alphaB[kb]) :
                MS[ka].append( cout_Match )
            else :
                cout_Mis = cout_Mis if (cout_Mis > 0) else -cout_Mis
                MS[ka].append( cout_Mis )
            kb += 1
        ka += 1
    return (MS)
    #



### ___ main ___ ## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___## ___ main ___###


# alignement 2 à 2 
# align global , matrice de similatirté
#    fixer cout des gap
#    fixer cout match/dismatch

## /\ use l'objet Seq .... moi  non ^^  : stings only

### bloc initialisation des séquences
S1 = "ACGGCT" 
S2 = "ACTGT"




Neo = Matrix(S1,S2)
Neo.initier_score()
Neo.remplir()

Neo.findScore_throught_table('A','A')

Neo.affiche()

Neo.backtrack()

Neo.give_pos_mutation()

#for line in Matt.content :
#    print (line)


"""
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
    """