#!/usr/bin/env python3
# -*- coding: utf-8 -*-

print("Démarrage...\n")
import pandas as pd
import rdflib
from rdflib import Namespace, Graph, URIRef, BNode, Literal
from rdflib.namespace import RDF, FOAF
import re

ontology_graph_filePATH = "./bdLylie/storedOntologies.txt"
custom_graph_filePATH = "./bdLylie/storedGraph.txt"

def returnURIRef(value, dico) :
    found = False
    for key, uri in dico.items() :
        if ( key == value ) : 
            return (uri)
    if (not found) : 
        print("erreur format")
        return (1)

#import pprint
print("\n\nBonjour, je m'appelle Lylie. Comment puis-je vous aider ? \n" +
    "Nous allons créé une base de donnée pour le tp HNSN204.\n" )
print("Nous allons charger une ontologie personnalisée adaptée à l'énoncer.\n" )
custom_graph = rdflib.Graph()
print("Voulez-vous : "+
    "\n\t1.\tcréé une nouvelle ontologie (par défaut)" +
    "\n\t2.\tmodifier l'ontologie actuelle (en travaux)" + 
    "\n\t3.\tchargé l'ontologie actuelle (très bientôt)")
ans = input(" 1 ou 'autre' : \t") 
if ((ans[0] == '3') or (int(ans) == 3))  : 
    custom_graph = Graph()
    Rturn = custom_graph.open("./bdLylie/storedGraph.txt", create= False)
    if (Rturn == rdflib.store.NO_STORE) :
        print("\n\nPas de sauvegarde accissible! \nCréation d'une sauvegarde vide\n")
        custom_graph.open("./bdLylie/storedGraph.txt", create= True)
        #custom_graph.close()

if ((ans[0] == '2') or (int(ans) == 2)) :
    print("\n\nZone en travaux\n\n")
    custom_graph = Graph()
    custom_graph.parse("./bdLylie/storedGraph.txt", format= 'n3') 
    print("Taille graph ontologie actuelle = \t ", len(custom_graph))
    #exit(2)
else :    
    print("\n\nChargement de l'ontologie ... patientez...\n")
    custom_graph = Graph()
    filePath = "./bdLylie/RDF_Ontology.txt"
    Prefix = {}
    thesaurus = {}
    OFile = open(filePath, 'r')
    check = True
    for line in OFile :
        #print(line)
        if ((line[0] == "#") or (len(line) == 0) or (line[0] == "!") or (line[0] == "=") or (line[0] == "\n")) :
            continue
        if (line[0] == ";") :
            result = re.search("^;([^,\s]+)[,\s](.+)$",line)
            #print(result)
            if (result) :
                Prefix[result.group(1)] = Namespace(result.group(2))
                custom_graph.bind(result.group(1),result.group(2))
            else : 
                print("prefix illisible\t:\t", line)
                check = False
        else : 
            if ((line[0] != "#") and (line[0] != "!") and (line[0] != "=") and (len(line) != 0)):
                result = re.search("(^[^!;=#][^,\s]+)[,\s]+([^,\s]+)[,\s]+([^,\s]+)$",line)
                if (result) :
                    #thesaurus[result.group(1)] = result.group(2)    #origial
                    thesaurus[result.group(1)] = [result.group(2),result.group(3)]
                    custom_graph.add( (Prefix[result.group(2)][result.group(3)], FOAF.name, Literal(result.group(1)) ))
                    #custom_graph.predicates(subject=result.group(1), object=result.group(2))
                else : 
                    print("terme ontologique illisible\t:\t", line)
                    check = False
    for line in OFile :
        if (line[0] == "!") :
            result = re.search("^[!]([^,\s]+)[,\s]+([^,\s]+)[,\s]+([^,\s]+)[,\s]+([^,\s]+)$",line)
            #print(result)
            if (result) :
                custom_graph.add( ( Prefix[result.group(1)][result.group(2)], RDF.subClassOf ,Prefix[result.group(3)][result.group(4)] ) )
            else : 
                print("triplet illisible\t:\t", line)
                check = False
        else :
            if (line[0] == "=") :
                result = re.search("^[=]([^,\s]+)[,\s]+([^,\s]+)[,\s]+([^,\s]+)[,\s]+([^,\s]+)$",line)
                #print(result)
                if (result) :
                    custom_graph.add( ( Prefix[result.group(1)][result.group(2)], RDF.subClassOf ,Prefix[result.group(3)][result.group(4)] ) )
                else : 
                    print("triplet illisible\t:\t", line)
                    check = False
    if  (check) :
        print("format correct")
    else : 
        print("erreur format\n\t(vérifier les espaces ^^)")
        exit(1)
    print("Sauvegarde graph ontologie\n\n")
    custom_graph.serialize( destination= "./bdLylie/storedGraph.txt", format= 'n3')
    OFile.close()
#
#print(Prefix)
#print(thesaurus)
#
print("Nous allons charger les triplets du graph .\n" )
#custom_graph = rdflib.Graph()
print("Voulez-vous : "+
    "\n\t1.\tcréé un nouveau graph (par défaut)" +
    "\n\t2.\tchargé la sauvegarde (très bientôt)" )
ans = input(" 1 ou 2 : \t") 
if ((ans[0] == '2') or (int(ans) == 2)) : 
    #custom_graph = Graph()
    Rturn = custom_graph.open("./bdLylie/storedGraph.txt", create= False)
    if (Rturn == rdflib.store.NO_STORE) :
        print("\n\nPas de sauvegarde accissible! \nCréation d'une sauvegarde vide\n")
        custom_graph.open("./bdLylie/storedGraph.txt", create= True)
        custom_graph.close()
else :    
    print("Voulez-vous charger les data de l'énoncer ? \n")
    ans = input ("yes(par défaut) / no \t:\t")
    if (ans == "no") :
        print("###\t\t\tzone en travaux\t\t\t###")
        #exit(1) 
        filePath = input(" ok \n" + "Veuillez renseigner le chemin du fichier csv, s'il-vous-plaît ?\n")
    else :
        filePath = "./Data_Projet_Entete_modify.csv"

    print("\nChargement des données ... patientez... \n")
    #custom_graph = Graph()
    #result = custom_graph.parse(data="./bdLylie/storedGraph.txt", format="n3")
    #if (not result) : 
    #    print("parse invalide")
    #    exit(1)
    #custom_graph += custom_graph
    csv = pd.read_csv(filePath)
    del csv["Plants/group"]
    #print(csv.head())
    Nodes = {}
    for Id in csv["Id"] :
        Nodes[Id] = Literal(Id)
        custom_graph.add(( Nodes[Id], RDF.type, Prefix["NCBITaxon"]["NCBITaxon_3702"]) )
    #
    for col in csv :
        if (col == 'Id' ):
            continue
        #print(Nodes)
        #a = input()
        i = 0
        for instance in Nodes :
            #sujet = Nodes[Id]
            if (returnURIRef(col, thesaurus) == 1 ) :
                print("erreur format")
                continue
                #exit(2)
            sujet = Nodes[instance]
            #prop = URIRef(returnURIRef(col, thesaurus))    #origin
            prop = Prefix[thesaurus[col][0]][thesaurus[col][1]]
            objet = Literal(csv[col][i])
            custom_graph.add(( sujet, prop, objet ))
            i += 1

    print("Sauvegarde...")

    custom_graph.serialize( destination= "./bdLylie/storedGraph.txt", format= 'n3')
    #custom_graph.serialize( destination= "./bdLylie/storedGraph.txt", format= 'n3')
print("\n\nNous avons terminé !\nEn vous remerciant\n\n")
#fin
#csv
