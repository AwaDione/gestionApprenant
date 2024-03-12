
#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#define tMax 50//taille max des tableaux
#define sMax 10 //taille max des chaines de caractere
#define fileP "presence.txt" //fichier pour marquer les présents
#define fileAllUsers "allUsers.txt" //fichier qui contient tous les users
#define ListClass "listClass.txt" //fichier qui contient toutes les classes

//structure classe
typedef struct 
{
    int id;
    char nomC[sMax];

   
}CLASS;
//structure user
typedef struct 
{
    int id;
    char nom[sMax],prenom[sMax], mdp[sMax];
    enum type {
        admin,
        apprenant
    }typeUser;
    CLASS class;
    char date[tMax];
    char heure[tMax];

}USER;


// Prototypes des fonctions
void masquerMotDePasse(char *mdp, int longueurMax);
void saveUser(USER);//Fonction qui ajoute un user dans le fichier des users
int authenticatePass(USER users[], int nbrUsers, char username[], char password[]) ;// Fonction pour vérifier les informations de connexion
void marquerPresence(USER);// fonction marquer présence
int loadUsers(USER users[]);
int loadClass(CLASS class[]);
void menuConnexion();
void menuAdmin();
void choixmenuAdmin();
void menuGestionDesEtudiants();
int saisirInt(int min, int max, char msg[]);
USER saisirUser();
char testChar() ;
int authenticateCode(USER users[], int num_users, char code[]);
void dateActu(char date[]);
int loadUsersPres(USER users[]);
void menuConnexionAdmin();
void menuApprenant();
void menuGenererFichier();
void genererFichierPresences(USER user[],int taille);
void genererFichierPresencesDate(USER user[],int taille,char dat[],int);
int validerDate(char *date);
void inverserChaine(char* str, int len, int i, int temp);
void verifieDateSaisi(char *date);

#endif