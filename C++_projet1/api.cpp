#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
   // verif si un argc passé en paramètre (nombre d'argument) 
   /*if (argc<= 1)
   {
      cout << "Fermeture du programme : Réexecutez en ajoutant votre nom de fichier en paramètre " << endl; 
      return -1;
   }
   string fichier (argv[1]);
    size_t index = fichier.find_last_of(".");
    string ext = fichier.substr(index);
    if (!(ext == ".fasta" || ext  == ".fa" || ext == ".FASTA"))
    {
      cout << "mauvaise extension, veuillez utilisé un format de fichier en viguer" << endl;
      return -2;
    }*/
  ifstream flux("seq.fasta");
  string ligne; //Une variable pour stocker les lignes lues
  string header;
  vector<string> sequence;
  string s("12");
  if (flux) 
   {//L'ouverture s'est bien passée, on peut donc lire
    int sum=0;
      while(getline(flux, ligne).good()) //Tant qu'on n'est pas à la fin, on lit tout le fichier et que la lecture est bonne
      {
         // prendre l'header
         if (!ligne.empty() && ligne[0] == '>' && ligne[0]+1 != '>') {
            header = ligne;
            sum+=1;
            cout << header << endl;
         }
         // prendre les sequences
          else if(!ligne.empty())
         {
            sequence.push_back(ligne);
         }
      }
      for (int i =0; i< sequence.size(); i++){
      cout << sequence[i] << endl;}
       cout << "nombre de sequences dans le fichier = " << sum << endl;
   }  
   else
   {
      cout << "ERREUR : Impossible d'ouvrir le fichier en lecture." << endl;
      return -3;
   }
  return 0;
}