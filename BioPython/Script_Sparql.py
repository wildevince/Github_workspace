#!/usr/bin/env python3
# -*- coding: utf-8 -*-

print("Démarrage...\n")
import pandas as pd
import rdflib
from rdflib import Namespace, Graph, URIRef, BNode, Literal
from rdflib.namespace import RDF
import re


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
ontologies = rdflib.Graph()
print("Voulez-vous : "+
    "\n\t1.\tcréé une nouvelle ontologie (par défaut)" +
    "\n\t2.\tmodifier l'ontologie actuelle (en travaux)" + 
    "\n\t3.\tchargé l'ontologie actuelle (très bientôt)")
ans = input(" 1 ou 'autre' : \t") 
if (ans == 3) : 
    ontologies = Graph()
    Rturn = ontologies.open("./bdLylie/storedOntologies.txt", create= False)
    if (Rturn == rdflib.store.NO_STORE) :
        print("\n\nPas de sauvegarde accissible! \nCréation d'une sauvegarde vide\n")
        ontologies.open("./bdLylie/storedOntologies.txt", create= True)
        ontologies.close()

if (ans == 2) :
    print("\n\nZone en travaux\n\n")
    ontologies = Graph()
    ontologies.parse("./bdLylie/storedOntologies.txt", format= 'n3') 
    print("Taille graph ontologie actuelle = \t ", len(ontologies))
    #exit(2)
else :    
    print("\n\nChargement de l'ontologie ... patientez...\n")
    ontologies = Graph()
    filePath = "./bdLylie/termes_ontology.txt"
    Prefix = {}
    thesaurus = {}
    OFile = open(filePath, 'r')
    check = True
    for line in OFile :
        #print(line)
        if (line[0] == ";") :
            result = re.search("^;([^,\s]+)[,\s](.+)$",line)
            #print(result)
            if (result) :
                Prefix[result.group(1)] = result.group(2)
                ontologies.bind(result.group(1),result.group(2))
            else : 
                print("prefix illisible")
                check = False
        if ((line[0] != ";") and (line[0] != "!")) :
            result = re.search("(^[^!;][^,\s]+)[,\s]+([^,\s]+)$",line)
            #print(result)
            if (result) :
                thesaurus[result.group(1)] = result.group(2)
            else : 
                print("terme ontologique illisible")
                check = False
    for line in OFile :
        if (line[0] == "!") :
            result = re.search("^!([^,\s]+)[,\s]([^,\s]+)$",line)
            #print(result)
            if (result) :
                ontologies.add( (URIRef(result.group(1)), RDF.subClassOf ,URIRef(result.group(2)) ) )
            else : 
                print("triplet illisible")
                check = False
    if  (check) :
        print("format correct")
    else : 
        print("erreur format\n\t(vérifier les espaces ^^)")
        exit(1)
    print("Sauvegarde graph ontologie\n\n")
    ontologies.serialize( destination= "./bdLylie/storedOntologies.txt", format= 'n3')
    OFile.close()
#
#print(Prefix)
#print(thesaurus)
#
print("Nous allons charger les triplets du graph .\n" )
custom_graph = rdflib.Graph()
print("Voulez-vous : "+
    "\n\t1.\tcréé un nouveau graph (par défaut)" +
    "\n\t2.\tchargé la sauvegarde (très bientôt)" )
ans = input(" 1 ou 2 : \t") 
if (ans == 2) : 
    custom_graph = Graph()
    Rturn = custom_graph.open("./bdLylie/storedGraph.txt", create= False)
    if (Rturn == rdflib.store.NO_STORE) :
        print("\n\nPas de sauvegarde accissible! \nCréation d'une sauvegarde vide\n")
        ontologies.open("./bdLylie/storedGraph.txt", create= True)
        ontologies.close()
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
    custom_graph = Graph()
    csv = pd.read_csv(filePath)
    for onto in ontologies : 
        custom_graph.add(onto)
    del csv["Plants/group"]
    #print(csv.head())
    BNodes = {}
    for Id in csv["Id"] :
        BNodes[Id] = BNode()
        #custom_graph.add(( BNodes[Id], RDF.type, URIRef(#######################################################################) ))
    #
    for col in csv :
        if (col == 'Id' ):
            continue
        #print(BNodes)
        #a = input()
        i = 0
        for instance in BNodes :
            #sujet = BNodes[Id]
            if (returnURIRef(col, thesaurus) == 1 ) :
                print("erreur format")
                continue
                #exit(2)
            sujet = BNodes[instance]
            prop = URIRef(returnURIRef(col, thesaurus))
            objet = Literal(csv[col][i])
            custom_graph.add(( sujet, prop, objet ))
            i += 1

    print("Sauvegarde...")

    custom_graph.serialize( destination= "./bdLylie/storedGraph.txt", format= 'n3')
    ontologies.serialize( destination= "./bdLylie/storedOntologies.txt", format= 'n3')
print("\n\nNous avons terminé !\nEn vous remerciant\n\n")
#fin
#csv
