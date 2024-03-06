#include "header.h"
int idUser=0;

void masquerMotDePasse(char *mdp, int longueurMax) {
    struct termios ancien, nouveau;
    int i = 0;

    // Obtenir les paramètres actuels du terminal
    tcgetattr(fileno(stdin), &ancien);
    nouveau = ancien;

    // Désactiver l'écho des caractères saisis
    nouveau.c_lflag &= ~ECHO;

    // Appliquer les nouveaux paramètres du terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &nouveau) != 0) {
        perror("Erreur lors de la désactivation de l'écho");
        return;
    }

    // Lire la saisie caractère par caractère
    while (i < longueurMax - 1) {
        char caractere = getchar();

        // Si l'utilisateur appuie sur la touche Entrée, terminer la saisie
        if (caractere == '\n' || caractere == EOF) {
            break;
        }

        // Stocker le caractère saisi dans le mot de passe
        mdp[i] = caractere;

        // Afficher un astérisque à l'écran
        printf("*");

        i++;
    }

    // Ajouter le caractère de fin de chaîne
    mdp[i] = '\0';

    // Réactiver l'écho des caractères
    if (tcsetattr(fileno(stdin), TCSANOW, &ancien) != 0) {
        perror("Erreur lors de la réactivation de l'écho");
        return;
    }

    printf("\n");
}

//fonction qui saisi un utilisateur
int saisirInt(int min, int max, char msg[])
{
    int x;
    do
    {
        puts(msg);
        scanf("%d", &x);
    } while (x<min || x>max);

    return x;
}


int authenticate(USER users[], int num_users, char username[], char password[]) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].nom, username) == 0 && strcmp(users[i].mdp, password) == 0) {
            return i; // L'utilisateur est trouvé, retourne son index
        }
    }
    return -1; // Aucun utilisateur correspondant
}
void marquerPresence(USER user) {
    FILE *file = fopen(fileP, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    time_t now;
    time(&now);
    struct tm *currentTime = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", currentTime);
    
    fprintf(file, "%d %s %s %s\n",user.id, user.nom,user.prenom, date);
    fclose(file);
}
// Fonction pour charger les utilisateurs à partir du fichier
int loadUsers(USER users[]) {
    FILE *file = fopen(fileAllUsers, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int id = 0;
    while (fscanf(file, "%u %s %s %s %u %u %s", &users[id].id,users[id].nom,users[id].prenom, users[id].mdp,&users[id].typeUser,&users->class.id,users->class.nomC) == 7) {
        id++;
    }

    fclose(file);
    return id;
}
int loadClass(CLASS class[]) {
    FILE *file = fopen(ListClass, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int id = 0;
    while (fscanf(file, "%d %s ", &class[id].id, class[id].nomC) == 2) {
        id++;
    }

    fclose(file);
    return id;
}
void menuConnexion(){
    puts("\t\tBienvenue");
    puts("\t-Entrer votre username :------------");
    puts("\t-Entrer votre mot de passe : *********");
}
void menuAdmin(){
    puts("1………..GESTION DES ÉTUDIANTS");
    puts("2………..GÉNÉRATION DE FICHIERS");
    puts("3………..MARQUER LES PRÉSENCES");
    puts("5………..ENVOYER UN MESSAGE");
    puts("4………..QUITTER");
  
}
void menuGestionDesEtudiants(){
    puts("1………..Liste des classes");
    puts("2………..Liste des etudiants");
    puts("3………..Marquer présence");
    puts("5………..Deconnexion");
    
}
USER saisirUser() {
    USER user;
    
    printf("Entrez votre mot de passe : ");
    masquerMotDePasse(user.mdp, sizeof(user.mdp));
    fflush(stdin); // Vidage du tampon d'entrée

    printf("Entrez le nom de l'utilisateur : ");
    scanf("%s", user.nom);
    fflush(stdin);

    printf("Entrez le prénom de l'utilisateur : ");
    scanf("%s", user.prenom);
    fflush(stdin);

    // Utilisation de la fonction pour cacher le mot de passe

    printf("Entrez le type de l'user (0 pour admin, 1 pour apprenant) : ");
    int type=saisirInt(0,1,"Entrez 0 pour Admin ou 1 pour Apprenant");
    
    user.typeUser = (type == 0) ? admin : apprenant;

    return user;
}