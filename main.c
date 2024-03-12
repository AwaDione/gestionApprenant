#include "header.h"

int main(int argc, char const *argv[])
{   char code[sMax];
    do{  
        int loggedInUserIndex =-1;
        USER users[tMax];
        int nbrUsers=loadUsers(users);
        char username[sMax],password[sMax];


    // system("clear");
        //int loggedInUserIndex =-1;
       // USER users[tMax];
        USER usersPres[tMax];//les utilisateurs qui sont présents
        // int nbrUsers=loadUsers(users);
        // char username[sMax],password[sMax];

   // system("clear");
    menuConnexion();

    printf("Nom d'utilisateur  : ");
    scanf("%s", username);
    getchar();
    printf("Mot de passe : ");
    masquerMotDePasse(password, sizeof(password));
   
     loggedInUserIndex =authenticatePass(users,nbrUsers,username,password);
     if (loggedInUserIndex != -1) {

        if(users[loggedInUserIndex].typeUser==0){
                       //menu Admin
                    do{    
                        int nbrUsersPres=loadUsersPres(usersPres);//les utilisateurs qui sont présents
                        
                         system("clear");
                        menuAdmin();
                        int choixMenuAdmin=saisirInt(1,4,"Faites votre choix");
                    switch ((choixMenuAdmin))
                    {
                       case 1:
                        printf("Bonjour");
                        break;
                       case 2:
                           int valide;
                            menuGenererFichier();
                           int choixmenuGF=saisirInt(1,2,"Faites votre choix");
                           switch (choixmenuGF)
                           {
                           case 1:
                            genererFichierPresences(usersPres,nbrUsersPres);
                            break;
                           case 2:
                           char ch[sMax],date[20],separateur;
                           char date1[30];
                               while (getchar() != '\n');
                                int isValid = 0;
                                do {
                                    printf("\033[0m");
                                    printf("\nVeuillez saisir une date au format(jj-mm-aaaa) : ");
                                    fgets(date, sizeof(date), stdin);

                                    // Supprimer le caractère de nouvelle ligne s'il est présent
                                    date[strcspn(date, "\n")] = '\0';
                                    if(strlen(date) == 10){
                                        isValid = validerDate(date);
                                    }else{
                                        printf("\033[0;31m");
                                        printf("\nFormat de date incorrect. Veuillez saisir la date au format jj-mm-aaaa.\n");
                                        printf("\033[0m");
                                        continue;
                                    }

                                    // Vider le tampon d'entrée
                                    //int c;
                                   // while ((c = getchar()) != '\n' && c != EOF);
                                }while (!isValid);

                               
                                  genererFichierPresencesDate(usersPres,nbrUsersPres, date,sMax);
                                             
                            break;
                            } 
                           
                          
                            
                        break;
                       case 3:
                            while (1)
                            { 
                                system("clear");
                                menuConnexionAdmin();
                                
                                scanf("%s",code);
                                loggedInUserIndex= authenticateCode(users,nbrUsers,code);
                                if (loggedInUserIndex==-1 && code[0]!='q'){ 
                                    printf("X Code invalide\n");
                                    sleep(1);
                                }
                                if(code[0]=='q' || code[0]=='Q' ){
                                    // system("clear");
                                    printf("Entrer votre mot de passe\n");
                                    masquerMotDePasse(password, sizeof(password));
                                    int Vpass= authenticatePass(users,nbrUsers,username,password);
                                    if(users[Vpass].typeUser==0 ){
                                        break;
                                    }else{
                                        printf("\n Le mot de passe Admin est requis\n");
                                        sleep(1);
                                        system("clear");
                                    }
                                }
                                if(users[loggedInUserIndex].id==atoi(code)){
                                    int nbrUsersPres=loadUsersPres(usersPres);//les utilisateurs qui sont présents
                                    char date[20];
                                    char heure[20];
                                    time_t now;
                                    time(&now);
                                    struct tm *currentTime = localtime(&now);
                                    strftime(date, sizeof(date), "%d-%m-%Y", currentTime);
                                    strftime(heure, sizeof(date), "%H:%M:%S", currentTime);
                                    int trouve = 1;
                                    for (int i = 0; i < nbrUsersPres; i++)
                                    {
                                        if (users[loggedInUserIndex].id==usersPres[i].id && strcmp(usersPres[i].date,date)==0)
                                        {
                                            printf("L'utilisateur est déja marqué présent\n");
                                            sleep(1);
                                            trouve=1;
                                            break;
                                        } else
                                        {
                                            trouve=0;
                                        }
                                    } 
                                    if (trouve==0)
                                    {
                                        marquerPresence(users[loggedInUserIndex]);
                                        printf("code valide, presence à:%s\n",heure);
                                        sleep(2);
                                       

                                    }
                                }
                             }
                       
                       default:
                        break;
                           
                       
                    }  
                    }while( code[0]!='q' && code[0]!='Q' );
                    
                       
        }else{
        //menu Etudiant
            menuApprenant();
            int choixMenuApprenant=saisirInt(1,4,"Entrez votre choix");
            switch (choixMenuApprenant)
            {
            case 1:
              //case 1
                while (1)
                            { 
                                system("clear");
                                menuConnexionAdmin();
                                char code[sMax];
                                scanf("%s",code);
                                loggedInUserIndex= authenticateCode(users,nbrUsers,code);
                                if (loggedInUserIndex==-1 && code[0]!='q'){ 
                                    printf("X Code invalide\n");
                                    sleep(1);
                                }
                                if(code[0]=='q' || code[0]=='Q' ){
                                    // system("clear");
                                    printf("Entrer votre mot de passe\n");
                                    masquerMotDePasse(password, sizeof(password));
                                    int Vpass= authenticatePass(users,nbrUsers,username,password);
                                    if(users[Vpass].typeUser==0 ){
                                        break;
                                    }else{
                                        printf("\n Le mot de passe Admin est requis\n");
                                        sleep(1);
                                        system("clear");
                                    }
                                }
                                if(users[loggedInUserIndex].id==atoi(code)){
                                    int nbrUsersPres=loadUsersPres(usersPres);//les utilisateurs qui sont présents
                                    char date[20];
                                    char heure[20];
                                    time_t now;
                                    time(&now);
                                    struct tm *currentTime = localtime(&now);
                                    strftime(date, sizeof(date), "%Y-%m-%d", currentTime);
                                    strftime(heure, sizeof(date), "%H:%M:%S", currentTime);
                                    int trouve = 1;
                                    for (int i = 0; i < nbrUsersPres; i++)
                                    {
                                        if (users[loggedInUserIndex].id==usersPres[i].id && strcmp(usersPres[i].date,date)==0)
                                        {
                                            printf("Vous  etes déja marqué présent\n");
                                            sleep(1);
                                            trouve=1;
                                            break;
                                        } else
                                        {
                                            trouve=0;
                                        }
                                    } 
                                    if (trouve==0)
                                    {
                                        marquerPresence(users[loggedInUserIndex]);
                                        printf("code valide, presence à:%s\n",heure);
                                        break;
                                    }
                                }
                             }
              //case1
                break;
            
            default:
                break;
            }
        }
    
    } else {
        printf("Échec de la connexion. \n Nom d'utilisateur ou mot de passe incorrect.\n");
    }
   }while (choixmenuAdmin);
    return 0;
}
