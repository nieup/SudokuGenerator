/**********************************************************
*
*	File : main.cpp
*	Author : Cédric HUMBERT
*
*	Description : Projet Sudoku Generation de Grille
*	Generation d'une grille de Sudoku
*        de niveau moyen ou difficille.
*
*	Date Création : 21 Avril 2015
*	Date Derniere Modification : 23 Avril 2015
*
*************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

    /// TO DO : ////// Envoyer sur le GitHub //////////////////
    /**
     * solveProb -> Ajouter une Gestion des erreurs
     *
     * --------------------------------------------
     *                     Pseudo
     * --------------------------------------------
     * Tant que (résolu)
     *      Remplir une casse
     *      Lancer la résolution
     *      Si(résolu)
     *          Arreter
     *
     */

    /// DONE :
    /**
     * Observations : Les test sont laissés en commentaire dans le code
     *
     * Generation Random
     *
     *      Fonctionnement : OK
     *
     */


int retRand(int borneSup){

    return rand()% (borneSup+1);
}


class Bloc{
    int datB[9];
public:

    Bloc(){for(int a = 0 ; a < 9 ; a++){datB[a] = 0;}}

    void setCase(int a, int val){datB[a] = val;}

    bool isInBloc(int val){
        for (int i = 0 ; i < 9 ; i++){
            if (datB[i]==val){return true;}
        }
        return false;
    }
};

class Grille{
    int dataG[9][9];
    bool isPoss[9][9];
    Bloc ligV[9];
    Bloc ligH[9];
    Bloc Carre[9];
public:

    /*      Initialisation :
     */

    Grille(){
        for (int i = 0 ; i < 9; i++){
            for (int j = 0 ; j < 9 ; j++){
                dataG[i][j] = 0;
                ligH[i].setCase(j, dataG[i][j]);
                ligV[j].setCase(i, dataG[i][j]);
                Carre[retCar(i, j)].setCase(retNumCar(i,j), dataG[i][j]);
                if (dataG[i][j] == 0){isPoss[i][j] = true;}
                else {isPoss[i][j]=false;}
            }
        }
    }

    /*      Fonctionnalités d'Affichage :
     *
     * De la Grille contenant les nombres
     * De la Grille contenant les possibilités
     * Des 2 à la suite
     */
    void afficheGrille(){
        cout << "Affichage Grille : " << endl;
        for (int i = 0; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                cout << dataG[i][j];
                if (j%3 == 2){cout <<".";}
                else {cout << "/";}
            }
            cout << endl;
            if (i%3 == 2){cout <<".................." << endl;}
        }
    }

    void afficheGrillePoss(){
        cout << "Affichage Grille Poss : " << endl;
        for (int i = 0; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){cout << "-" ;}
                else {cout << "X";}
                if (j%3 == 2){cout <<".";}
                else {cout << "/";}
            }
            cout << endl;
            if (i%3 == 2){cout <<".................." << endl;}
        }
    }

    void afficheTout(){
        afficheGrille();
        afficheGrillePoss();
    }

    /*      Gestion des Possibilités :     */

    void resetIsPoss(){
        //cout << "Poss Reset ! " << endl;
        for(int i = 0 ; i < 9 ; i++){
            for(int j = 0 ; j < 9 ; j++){
                if (dataG[i][j] == 0){isPoss[i][j] = true;}
                else {isPoss[i][j] = false;}
            }
        }
    }

    void reMapIsPoss(int val){
        //cout << "ReMap avec : " << val << endl;
        for(int i = 0 ; i < 9 ;  i++){
            for(int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){
                    if (ligH[i].isInBloc(val)){isPoss[i][j] = false;}
                    else if (ligV[j].isInBloc(val)){isPoss[i][j] = false;}
                    else if (Carre[retCar(i, j)].isInBloc(val)){isPoss[i][j] = false;}
                }
            }
        }
    }

    /*      Gestion des Variables Internes :    */
    static int retC(int carId){
        if(carId == 0 || carId == 3 || carId == 6){return 0;}
        else if(carId == 1 || carId == 4 || carId == 7){return 3;}
        else if(carId == 2 || carId == 5 || carId == 8){return 6;}
    }

    static int retL(int carId){
        if(carId == 0 || carId == 1 || carId == 2){return 0;}
        else if(carId >= 3 && carId <= 5 ){return 3;}
        else if(carId > 5){return 6;}
    }
    static int retNumCar(int L, int C){return (L%3)*3 + C%3;}

    static int retCar(int L, int C){
        if( L == 0 || L == 1 || L == 2){
            if(C == 0 || C == 1 || C == 2){
                return 0;
            }
            if(C == 3 || C == 4 || C == 5){
                return 1;
            }
            if(C == 6 || C == 7 || C == 8){
                return 2;
            }
        }
        else if( L == 3 || L == 4 || L == 5){
            if(C == 0 || C == 1 || C == 2){
                return 3;
            }
            if(C == 3 || C == 4 || C == 5){
                return 4;
            }
            if(C == 6 || C == 7 || C == 8){
                return 5;
            }
        }
        else if( L == 6 || L == 7 || L == 8){
            if(C == 0 || C == 1 || C == 2){
                return 6;
            }
            if(C == 3 || C == 4 || C == 5){
                return 7;
            }
            if(C == 6 || C == 7 || C == 8){
                return 8;
            }
        }
        else {return -1;}
    }



    /*      Fonctionalités de Travail     */
    bool filledGrille(){ // Retourne Vrai si la Grille est remplie
        bool fini = true;
        for(int i = 0 ; i < 9 ;  i++){
            for(int j = 0 ; j < 9 ; j++){
                if (dataG[i][j] == 0){fini = false;}
            }
        }
        if (fini){return true;}
        else{return false;}
    }

    void solveProp(){ // Solveur du Sudoku
        /* Tourne sur chaqu'un des nombres
         * metant à jour la grille des
         * possibilités
         */
        bool goOn = true;
        while (goOn){
            goOn = false;
            for(int a = 1 ; a < 10 ; a++){
                //cout << a << endl;
                resetIsPoss();
                reMapIsPoss(a);
                if (setNew(a)){goOn = true;}
                //affiche();
                //cin >> goOn;
            }
            if (filledGrille()){goOn = false; }
            //afficheGrille();
            //cin >> goOn;
        }
    }

    bool setNew(int val){ // Ajoute le nombre val partout ou c'est possible dans le tableau Retourne True si un nombre a été ajouté
        bool retVal = false;
        for(int i = 0 ; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){
                    if(isAlone(i, j)){
                        dataG[i][j] = val;
                        ligV[j].setCase(i, val);
                        ligH[i].setCase(j, val);
                        Carre[retCar(i,j)].setCase(retNumCar(i, j), val);
                        retVal = true;
                        //cout << "Entre : " << dataG[i][j] << " en (" << i << "," << j << ") test : " << (dataG[i][j] != 0) << endl;
                    }
                }
            }
        }
        if(retVal){return true;}
        else{return false;}
    }

    bool isAlone(int L, int C){
        int onlyOne = 0;
        // Sur la ligne Horizontale :
        for(int a = 0 ; a < 9 ; a++){if(isPoss[L][a]){onlyOne++;}}
        if(onlyOne == 1){return true;}

        // Sur la ligne Verticale  :
        onlyOne = 0;
        for(int a = 0 ; a < 9 ; a++){if(isPoss[a][C]){onlyOne++;}}
        if(onlyOne == 1){return true;}
        //*/

        //* Sur le Carre :
        onlyOne = 0;
        int carId = retCar(L,C);


        for (int i = 0 ; i < 9 ; i++){
            for(int j = 0 ; j < 9 ; j++){
                if (retCar(i,j) == carId){
                    if(isPoss[i][j]){onlyOne++;}
                }
            }
        }
        // cout << "Ligne " << L << " Colonne " << C << " Carre " << carId <<  endl; // " couple ("<<i<<","<<j<<")"<<
        if(onlyOne == 1){return true;}
        //*/
        return false;
    }


    /// Nouvelles Fonctions
    void addNb(){
        // Choisit la valeur
        int val = retRand(9);
        //cout << "Valeur a entrer :" << val << endl;
        int lenPoss;
        resetIsPoss();
        reMapIsPoss(val);
        lenPoss = sumIsPoss();
        lenPoss = retRand(lenPoss);
        if (lenPoss != 0){
            //cout << "Case a cocher : " << lenPoss << endl;
            for(int i = 0 ; i < 9 ; i++){
                for(int j = 0 ; j < 9 ; j++){
                    if(isPoss[i][j]){lenPoss--;}
                    if(lenPoss==0){
                        setVal(i, j, val);
                        //cout << "La valeur " << val << " a ete ajoutee en L = " << i << " C = " << j << endl;
                        i = 10;
                        j = 10;
                    }
                }
            }
        }
    }

    void setVal(int L, int C, int val){
        dataG[L][C] = val;
        ligV[C].setCase(L, val);
        ligH[L].setCase(C, val);
        Carre[retCar(L,C)].setCase(retNumCar(L, C), val);
        //cout << "Carre " << retNumCar(L,C) << " est dans le bloc ? "<< Carre[retNumCar(L,C)].isInBloc(val) << endl;
    }
    void resetGrille(){
        for (int i = 0 ; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                setVal(i, j, 0);
            }
        }

    }
    int sumIsPoss(){
        int sum = 0;
        for (int i = 0 ; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if(isPoss[i][j]){sum++;}
            }
        }
        return sum;
    }

    Grille operator=(Grille grB){
        for(int i = 0 ; i < 9 ; i++){
            for(int j = 0 ; j < 9 ; j++){
                setVal(i, j, grB.getDat(i,j));
            }
        }
    }
    int getDat(int L, int C){
        return dataG[L][C];
    }
};




int main()
{
    cout << "\t Hello the world! Main " << endl;
    Grille gr_buf, gr_base = Grille();

    int i = 0;
    srand(time(NULL));
    for (int j = 0 ; j < 150 ; j++){
        gr_base.resetGrille();
        gr_buf.resetGrille();
        i = 0;
        while(!gr_buf.filledGrille() && i <= 50){
            gr_base.addNb();
            gr_buf = gr_base;
            gr_buf.solveProp();
            i++;
        }
        if(gr_buf.filledGrille()){
            cout << "Voici une Grille et sa solution : " << endl;
            gr_base.afficheGrille();
            gr_buf.afficheGrille();
        }
    }

    return 0;

}

int main_test(){

    /*
    Grille gr, gr_base = Grille();
    gr = gr_base;
    cout << " \t Hello the world! Main Test " << endl;

    gr.solveProp();
    gr.afficheGrille();


    for (int i = 0 ; i < 20 ; i++){
        cout << retRand(4) << endl;
    }

    return 0;
    //*/
}



























