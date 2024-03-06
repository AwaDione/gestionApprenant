
#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
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

}USER;


// Prototypes des fonctions
void masquerMotDePasse(char *mdp, int longueurMax);
void saveUser(USER);//Fonction qui ajoute un user dans le fichier des users
int authenticate(USER users[], int nbrUsers, char username[], char password[]) ;// Fonction pour vérifier les informations de connexion
void marquerPresence(USER);// fonction marquer présence
int loadUsers(USER users[]);
int loadClass(CLASS class[]);
void menuConnexion();
void menuAdmin();
void choixmenuAdmin();
void menuGestionDesEtudiants();
int saisirInt(int min, int max, char msg[]);
USER saisirUser();

#endif