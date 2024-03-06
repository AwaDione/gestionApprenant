#include "header.h"

int main(int argc, char const *argv[])
{   
    int loggedInUserIndex =-1;
    USER users[tMax];
    int nbrUsers=loadUsers(users);
    char username[sMax],password[sMax];
   menuConnexion();

    printf("Nom  : ");
    scanf("%s", username);
    getchar();
    printf("Mot de passe : ");
    masquerMotDePasse(password, sizeof(password));
   
     loggedInUserIndex =authenticate(users,nbrUsers,username,password);
     if (loggedInUserIndex != -1) {
                    printf("Connexion réussie. Bienvenue, %s !\n", username);
                   
                } else {
                    printf("Échec de la connexion. \n Nom d'utilisateur ou mot de passe incorrect.\n");
                }
   
    return 0;
}