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

                     if(users[loggedInUserIndex].typeUser==0){
                        menuGestionDesEtudiants();
                        int choix=saisirInt(1,5,"Faites votre choix");
                        CLASS class[tMax];
                         switch (choix)
                            {
                            case 1:
                            int taille=loadClass(class); 
                            for (int i = 0; i < taille; i++)
                            {
                                printf("Id : %d\t\t",class[i].id);
                                printf("Nom : %s\n",class[i].nomC);
                            }
                                                   
                                break;
                            case 2:
                            USER users[tMax];
                            int taille2=loadUsers(users);
                            printf("Id \tNom \tprenom\t Mdp typeUser idClass NomClass\n");
                             for (int i = 0; i < taille2; i++)
                            {
                               printf( "%u \t%s \t%s \t%s \t%d \t%d \t%s\n", users[i].id,users[i].nom,users[i].prenom, users[i].mdp,users[i].typeUser,users->class.id,users->class.nomC);
                            }
                            break;
                            case 3:
                                USER user=saisirUser();
                                marquerPresence(user);
                                break;
                            
                            default:
                                menuGestionDesEtudiants();
                                break;
                            }
                        
                    }else{
                        //menu 
                    }
                   
                } else {
                    printf("Échec de la connexion. \n Nom d'utilisateur ou mot de passe incorrect.\n");
                }
   
    return 0;
}
