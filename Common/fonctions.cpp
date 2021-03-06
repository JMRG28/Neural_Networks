#include "fonctions.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include<string>
#include <stdlib.h>
#include <time.h>
#include<cmath>
#include"../Neurone/Neurone.h"
#include"../Neurone/NeuroneB.h"
#include"../Layer/Layer.h"
#include"../Reseau/Reseau.h"
#include"../Common/fonctions.h"
#include"../Settings/Settings.h"

/**
* Affichage de vecteur DOUBLE
* @method printVec
* @param  vec      Vecteur à afficher
*/
void printVec (std::vector<double> vec){
  for (unsigned int i=0;i<vec.size();i++){
    std::cout<<vec[i]<<",";
  }
}
/**
* Affichage de vecteur INT
* @method printVec
* @param  vec      Vecteur à afficher
*/
void printVec (std::vector<int> vec){
  for (unsigned int i=0;i<vec.size();i++){
    std::cout<<vec[i]<<",";
  }
}
/**
* Affichage de vecteur de vecteur de DOUBLE
* @method printVec
* @param  vec       Vecteur à afficher
*/
void printVec (std::vector<std::vector<double> > vec){
  for (unsigned int i=0;i<vec.size();i++){
    for (unsigned int j=0;j<vec[i].size();j++){
      std::cout<<vec[i][j]<<",";
    }
    std::cout<<std::endl<<"----------"<<std::endl;
  }
}
/**
* Affichage de vecteur de vecteur de vecteur de DOUBLE
* @method printVec
* @param  vec       Vecteur à afficher
*/
void printVec (std::vector<std::vector<std::vector<double> > > vec){
  std::cout<<"<";
  for(unsigned int k =0; k < vec.size();k++){
    std::cout<<"<";
    for (unsigned int i=0;i<vec[k].size();i++){
      std::cout<<"<";
      for (unsigned int j=0;j<vec[k][i].size();j++){
        std::cout<<vec[k][i][j];
        if ( j != vec[k][i].size()-1){
          std::cout<<",";
        }
      }
      std::cout<<">";
      if ( i != vec[k].size()-1){
        std::cout<<",";
      }
    }
    std::cout<<">"<<(k!=vec.size() ? " ":">")<<std::endl;
  }
}

/**
* Recupération des données dans un fichier
* @method getInput
* @param  fileName Nom du fichier
*/
std::vector< std::vector <double> > getInput(char const * fileName){
  /**
  * Counter
  */
  std::ifstream in(fileName);
  std::string ligne;
  int nbLignes = 0;
  while(std::getline(in, ligne)){
    nbLignes++;
  }
  in.close();

  /**
  * Parser
  */
  std::ifstream fichier(fileName, std::ios::in);
  if(fichier){
    std::vector< std::vector <double> > stock(nbLignes); // Tableau de chaine de caractère qui va contenir tout le fichier ligne par ligne
    std::cout << "\033[1;36m file " << "\033[1;31m" << fileName << "\033[1;36m opened with success , nbLignes= " <<nbLignes<<"\033[0m"<< std::endl;
    std::string s;
    double temp = 1;
    std::string ligne;

    for (int j = 0; j < nbLignes; j++) {
      fichier>>ligne;
      std::stringstream ss(ligne);
      /** strinsplit à partir du caractère ',' */
      while (getline(ss, s, ',')) {
        temp = atof(s.c_str());
        stock[j].push_back(temp);
      }
    }
    swapVec(&stock);
    fichier.close();
    return stock;
  }
  else {
    std::cerr << "\033[0;31m ERROR [ "<< "Can't open file" << " IN FILE " << __FILE__ << " AT LINE " << __LINE__ << " ] \n \033[0m";
    std::vector< std::vector <double> > stock(nbLignes);
    return stock;
  }

}

/**
* Extraction de la derniére colonne d'un tableau bi-dimensionnel (vecteur de vecteur)
* @method extractResult
* @param  input         Vecteur de vecteur
*/
std::vector <double> extractResult(std::vector< std::vector <double> > * input){
  std::vector<double> res(input->size());
  unsigned int pos =((*input)[0].size())-1;
  for(unsigned int i=0;i<input->size();i++){
    res[i]=(*input)[i][pos];
    (*input)[i].pop_back();
  }
  return res;
}

/**
* Echange de vecteur aléatoire avec synchronisation
* @method swapVec
* @param  input   Vecteur de vecteur à échanger
* @param  result  Autre vecteur à synchroniser
*/
void swapVec (std::vector<std::vector<double> > * input, std::vector <double> * result){
  unsigned int r;
  for (unsigned int i=0;i<input->size();i++){
    do{
      r = rand()%input->size();
    }while(r == i);
    (*input)[i].swap((*input)[r]);
    iter_swap(result->begin() + i ,result->begin() + r);
  }
}

/**
* Echange de vecteur aléatoire
* @method swapVec
* @param  input   Vecteur de vecteur à échanger
*/
void swapVec (std::vector<std::vector<double> > * input){
  unsigned int r;
  for (unsigned int i=0;i<input->size();i++){
    do{
      r = rand()%input->size();
    }while(r == i);
    (*input)[i].swap((*input)[r]);
  }
}
unsigned int int_to_int(unsigned k) {
  if (k == 0) return 0;
  if (k == 1) return 1;                       /* schlagué */
  return (k % 2) + 10 * int_to_int(k / 2);
}

/**
* Génération d'entrées pour OU et ET
* @method generateInput
* @param  n             Nombre d'entrées
* @param  estet         True si génération de ET sinon False pour OU
*/
std::vector<std::vector<double> > generateInput(int n, bool estet){
  int nbtest = (int)pow(2,n);
  std::vector< std::vector < double > >  testtab(nbtest, std::vector<double>(n,0));
  for (int i =0; i < nbtest; i ++){
    int tmp = i;
    tmp = int_to_int(tmp);
    for (int j =0; j < n; j ++){
      testtab[i][j]= (tmp/(int)pow(10,n-1-j)==1?1 : 0) ;
      tmp = tmp- (testtab[i][j]==1? (int)pow(10,n-1-j): 0);
    }
    if ( !estet && i > 0){
      testtab[i].push_back(1);
    }
    else if ( !estet) {
      testtab[i].push_back(0);
    }
    std::cout << "Serie I :";
    for (int k =0; k < n; k ++){
      std::cout<<testtab[i][k];
    }
    if (estet && i == nbtest-1){
      testtab[i].push_back(1);
    }
    else if ( estet){
      testtab[i].push_back(0);
    }
    std::cout<<" o : "<<testtab[i][testtab[i].size()-1]<<std::endl;
  }
  return testtab;
}

/**
* @method findIndMax
* @param  vec        Vecteur
* @return            Indice du max
*/
unsigned int findIndMax(std::vector<double> vec){
  double max = vec[0];
  unsigned int indMax=0;
  for(unsigned int i=0;i<vec.size();i++){
    if(vec[i]>max){
      max=vec[i];
      indMax = i;
    }
  }
  return indMax;
}

/**
* Récupération d'entrée dans un fichier
* @method getInputUltime
* @param  fileName       Nom du fichier
* @param  pourcentage    Pourcentage à récuperer pour le training
*/
std::vector < std::vector <std::vector <double> > > getInputUltime(char const * fileName,float pourcentage){
  /**
  * Counter
  */
  std::ifstream in(fileName);
  std::string ligne;
  int nbLignes = 0;
  while(std::getline(in, ligne)){
    nbLignes++;
  }
  in.close();

  /**
  * Parser
  */
  std::ifstream fichier(fileName, std::ios::in);
  if(fichier){
    std::vector< std::vector <double> > stock(nbLignes); // Tableau de chaine de caractère qui va contenir tout le fichier ligne par ligne
    std::cout << "\033[1;36m file " << "\033[1;31m" << fileName << "\033[1;36m opened with success , nbLignes= " <<nbLignes<<"\033[0m"<< std::endl;
    std::string s;
    double temp = 1;
    std::string ligne;
    for (int j = 0; j < nbLignes; j++) {
      fichier>>ligne;
      std::stringstream ss(ligne);
      /** strinsplit à partir du caractère ',' */
      while (getline(ss, s, ',')) {
        temp = atof(s.c_str());
        stock[j].push_back(temp); // On stock chaque information dans une case
      }
    }
    swapVec(&stock);
    fichier.close();
    int tailleTraining = (int)((pourcentage/100) * nbLignes);
    int tailleTesting = nbLignes - tailleTraining;
    std::vector< std::vector <std::vector <double> > > result(2);
    for(int i=0;i<tailleTraining;i++){
      result[0].push_back(stock[i]);
    }
    for(int i=0;i<tailleTesting;i++){
      result[1].push_back(stock[i+tailleTraining]);
    }
    return result;
  }
  else {
    std::cerr << "\033[0;31m ERROR [ "<< "Can't open file" << " IN FILE " << __FILE__ << " AT LINE " << __LINE__ << " ] \n \033[0m";
    exit(2);
    std::vector< std::vector < std::vector <double> > > result(2);
    return result;
  }
}

/**
* Affichage de l'architecture (cf. PYTHON)
* @method displayArchi
* @param  info         Vecteur d'information sur l'architecture
*/
void displayArchi(std::vector<int> info){
  std::string endline = "network.draw()";
  std::string begin = "network = DrawNN( [";
  std::string dyNeuron= " ";
  for (unsigned int i = 0; i <= info.size()-2; i++){
    dyNeuron = std::to_string(info[i]) + ",";
    begin+=dyNeuron;
  }
  dyNeuron = std::to_string(info[info.size()-1]);
  begin += dyNeuron +"] )";
  system("sed -i '$ d' Archi.py");
  system("sed -i '$ d' Archi.py");
  std::ofstream fichier("Archi.py", std::ios::app);
  if(fichier)
  {
    fichier<< begin <<"\n";
    fichier<<endline;
    fichier.close();
  }
  else  {
    std::cerr << "\033[0;31m ERROR [ "<< "Can't open file" << " IN FILE " << __FILE__ << " AT LINE " << __LINE__ << " ] \n \033[0m";
  }
  system("python Archi.py");
}
void  startLauncher(std::string file, bool arch, int ep, double eta,unsigned int gradient,FonctionActivation::EnumFonctionActivation fct, float auto_off) {
  std::string newfile= "./TrainingSets/"+file;
  const char * fileName = newfile.c_str();
  Settings Settings(fileName);
  std::vector<int> archi = (*Settings.getArchi());
  std::cout << "Affichage de l'architecture du reseau, Fermez pour commencer" << std::endl;
  if(arch == true){
    displayArchi(archi);
  }
  system("clear");
  Reseau * rezo = new Reseau(archi.size(),archi,1.0,eta,fct);
  std::vector<std::vector <std::vector <double> > > trainingettesting = getInputUltime(fileName,80);
  std::vector<std::vector<double> > training = trainingettesting[0];
  std::vector<std::vector<double> > testing = trainingettesting[1];
  int epoch = ep;
  std::vector<double> res(Settings.getDifferentOutputs()->size());
  int temp;
  std::vector<std::vector<std::vector<double> > > testData(training.size());
  std::cout<< "\033[1;33m"<<std::endl;
  std::cout<<"--------------------------------"<<std::endl;
  for(unsigned int k=0;k<Settings.getDifferentOutputs()->size();k++){
    std::vector<double> mapVect(Settings.getDifferentOutputs()->size(),0);
    std::cout<<(*Settings.getDifferentOutputs())[k]<<" has been mapped to {" ;
    for(unsigned int z=0;z<mapVect.size();z++){
      if(z==k)std::cout<<"1," ;
      else std::cout<<"0," ;
    }
    std::cout<<"}"<<std::endl;

  }
  std::cout<<"--------------------------------"<<std::endl;
  std::cout<<"\033[0m"<<std::endl;
  for (unsigned int i = 0; i < training.size(); i++){
    temp=(int)training[i][training[i].size()-1];
    training[i].pop_back();
    for(unsigned int j=0;j<Settings.getDifferentOutputs()->size();j++){
      if(temp==(*Settings.getDifferentOutputs())[j]){
        res[j]=1;
      }
      else res[j]=0;
    }
    testData[i] = {training[i],res};
  }

  std::cout << "Learning Starting..."<<std::endl;
  double pourcentage;
  int deb = time(NULL);



  std::vector<std::vector<double> > expectedRes(testing.size());
  for (unsigned int i = 0; i < testing.size(); i++){
    temp=(int)testing[i][testing[i].size()-1];
    for(unsigned int j=0;j<Settings.getDifferentOutputs()->size();j++){
      if(temp==(*Settings.getDifferentOutputs())[j]){
        res[j]=1;
      }
      else res[j]=0;
    }
    expectedRes[i]=res;
  }
  std::vector<double> result (Settings.getDifferentOutputs()->size());
  int tmp = 0;
  int nberr = 0;
  int anciennenberr=0;

  for(int i=0;i<epoch;i++){
    pourcentage = (((double)i/(double)epoch)*100);
    swapVec(&testData[0]);
    rezo->learn(testData,gradient);
    int deltat = time(NULL) - deb;

    if (auto_off) {
      tmp = 0;
      nberr = 0;
      anciennenberr=0;
      for(unsigned int i=0;i<testing.size();i++){
        result= rezo->fire_all(testing[i]);
        std::vector<double> print (Settings.getDifferentOutputs()->size(),0);
        print[findIndMax(result)]=1;
        anciennenberr=nberr;
        bool err = false;
        for(unsigned int l =0;l<print.size();l++){
          if (print[l]!=expectedRes[i][l]) err=true;
        }
        nberr += err;
        tmp++;
      }

      std::cout<< "\033[1;32m >> " << (int)pourcentage << "% | " << i << " epoch | "<< deltat <<" secondes | Error "<< ((float)nberr/tmp)*100 <<"%                 \r"<< std::flush;
      if (((float)nberr/tmp)*100<auto_off) break;
    }
    else{
    std::cout<< "\033[1;32m >> " << (int)pourcentage << "% | " << i << " epoch | "<< deltat <<" secondes               \r"<< std::flush;
    }
  }
  int delta = time(NULL)-deb;
  std::cout << "\r\033[1;36m 100% \033[0m";
  std::cout << "<\033[1;33m DONE \033[0m>         "<< std::endl;
  std::cout << "\033[1;36m Learning Completed \033[0m" << std::endl;
  std::cout << "Displaying last recorded weights..." << std::endl;
  rezo->printWeight();
  tmp = 0;
  nberr = 0;
   anciennenberr=0;

  /** Nouveau test avec des valeurs inconnues pour le résaux neuronal */
  for(unsigned int i=0;i<testing.size();i++){
    std::cout<<"Test; input : ";
    printVec(testing[i]);
    std::cout<<" attendu : ";
    printVec(expectedRes[i]);
    std::cout<<" recu : ";
    result= rezo->fire_all(testing[i]);
    std::vector<double> print (Settings.getDifferentOutputs()->size(),0);
    print[findIndMax(result)]=1;
    anciennenberr=nberr;
    bool err = false;
    for(unsigned int l =0;l<print.size();l++){
      if (print[l]!=expectedRes[i][l]) err=true;
    }
    nberr += err;
    printVec(print);
    if ( nberr > anciennenberr){
      std::cout<< "\033[1;31m /!\\"<<"\033[0m";
    }
    std::cout<<std::endl;
    tmp++;
  }
  std::cout<<"\033[1;33mNombre d'erreur : \033[0m \033[1;32m"<<((float)nberr/tmp)*100<<"\% \033[0m --->("<<nberr<<" / "<<tmp<<")"<<std::endl;
  std::cout<<"\033[1;33mTemps d'apprentissage : \033[1;33m"<<delta<<" secondes \033[0m"<<std::endl;

}
