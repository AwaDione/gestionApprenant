#include "header.h"
int idUser=0;



char testChar() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void masquerMotDePasse(char *mdp, int longueurMax) {
    int i = 0;
    char c;
    while (1) {
        c = testChar();
        if (c == '\n') {
            mdp[i] = '\0';
            break;
        } else if (c == 127) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Efface le caractère précédent
            }
        } else {
            mdp[i++] = c;
            printf("*"); // Affiche un astérisque
        }     
    }
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


int authenticatePass(USER users[], int num_users, char username[], char password[]) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].mdp, password) == 0) {
            return i; // L'utilisateur est trouvé, retourne son index
        }
    }
    return -1; // Aucun utilisateur correspondant
}
int authenticateCode(USER users[], int num_users, char code[]) {
  
     for (int i = 0; i < num_users; i++) {
        if (users[i].id==atoi(code)) {
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
    char heure[20];
   // strftime(date, sizeof(date), "%Y-%m-%d ", currentTime);
    strftime(date, sizeof(date), "%d-%m-%Y", currentTime);
    strftime(heure, sizeof(heure), "%H:%M:%S", currentTime);
    strcpy(user.date,date); strcpy(user.heure,heure);
    fprintf(file, "%d %s %s %s %s \n",user.id, user.nom,user.prenom, user.date,user.heure);
    fclose(file);
}
void genererFichierPresences(USER user[],int taille) {
    char comp[tMax];
    FILE *fil = fopen("allPresence", "w");
    if (fil == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fprintf(fil,"La liste des Présences du %s\n\n",user[0].date);
    fprintf(fil,"Mat\t Nom\t Prénom \t Date \t    Heure\n");

    strcpy(comp,user[0].date);
   for (int i = 0; i < taille; i++)
   {
        if (strcmp(user[i].date,comp)!=0)
        {
            if (i==taille) break;
            
            fprintf(fil,"\nLa liste des Présences du %s\n",user[i].date);
            fprintf(fil,"Mat\t Nom\t Prénom \t Date \t    Heure\n");
            
        }
        fprintf(fil, "%d\t %s \t %s \t %s \t %s \n",user[i].id, user[i].nom,user[i].prenom, user[i].date,user[i].heure);
    strcpy(comp,user[i].date);

        
   }
   
    fclose(fil);
}
void genererFichierPresencesDate(USER user[],int taille,char date[],int t) {
    //strcpy(date,"2024-03-06");
   char nom[tMax]="presenceDate"; 
   strcat(nom,date);
   strcat(nom,".txt");
   //strcpy(nom,date);
    FILE *filP = fopen(nom, "w");
    if (filP == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fprintf(filP,"La liste des Présences du %s\n\n",date);
   for (int i = 0; i < taille; i++)
   {//inverserChaine(date,10,0,0);
        if (strcmp(user[i].date,date)==0)
        {
            fprintf(filP, "%d %s %s %s %s \n",user[i].id, user[i].nom,user[i].prenom, user[i].date,user[i].heure);
        }
        
   }
   
    fclose(filP);
}
int validateDate(char *date){
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    // Vérifier le format de la date
    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-') {
        printf("\033[0;31m");
        printf("\nFormat de date incorrect. Veuillez saisir la date au format jj-mm-aaaa.\n");
        return 0;
    }

    // Extraire le jour, le mois et l'année de la date saisie
    int day, month, year;
    sscanf(date, "%d-%d-%d", &day, &month, &year);

    // Vérifier la validité du jour
    if (day < 1 || day > 31) {
        printf("\033[0;31m");
        printf("\nNombre de jours invalide.\n");
        return 0;
    }

    // Vérifier la validité du mois
    if (month < 1 || month > 12) {
        printf("\033[0;31m");
        printf("\nNombre de mois invalide.\n");
        return 0;
    }

    if(year > currentYear){
        printf("\033[0;31m");
        printf("\nL'année saisie ne doit pas être supérieure à l'année courante.\n");
        return 0;
    }

    // Si l'année est égale à l'année actuelle
    if(year == currentYear && month > currentMonth){
        printf("\033[0;31m");
        printf("\nMois invalide pour l'année en cours.\n");
        return 0;
    }

    if(year == currentYear && month == currentMonth && day > currentDay){
        printf("\033[0;31m");
        printf("\nJour invalide pour le mois de l'année en cours.\n");
        return 0;
    }
    
    int daysInMonth;
    if(month == 2){
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            daysInMonth = 29;
        }else {
            daysInMonth = 28;
        }
    }else if(month == 4 || month == 6 || month == 9 || month == 11){
        daysInMonth = 30;
    }else{
        daysInMonth = 31;
    }

    if(day > daysInMonth){
        printf("\033[0;31m");
        printf("\nNombre de jours invalide pour le mois %d.\n", month);
        return 0;
    }
    return 1;
    }
int validerDate(char *date){
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    // Vérifier le format de la date
    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-') {
        printf("\033[0;31m");
        printf("\nFormat de date incorrect. Veuillez saisir la date au format jj-mm-aaaa.\n");
        return 0;
    }

    // Extraire le jour, le mois et l'année de la date saisie
    int day, month, year;
    sscanf(date, "%d-%d-%d", &day, &month, &year);

    // Vérifier la validité du jour
    if (day < 1 || day > 31) {
        printf("\033[0;31m");
        printf("\nNombre de jours invalide.\n");
        return 0;
    }

    // Vérifier la validité du mois
    if (month < 1 || month > 12) {
        printf("\033[0;31m");
        printf("\nNombre de mois invalide.\n");
        return 0;
    }

    if(year > currentYear){
        printf("\033[0;31m");
        printf("\nL'année saisie ne doit pas être supérieure à l'année courante.\n");
        return 0;
    }

    // Si l'année est égale à l'année actuelle
    if(year == currentYear && month > currentMonth){
        printf("\033[0;31m");
        printf("\nMois invalide pour l'année en cours.\n");
        return 0;
    }

    if(year == currentYear && month == currentMonth && day > currentDay){
        printf("\033[0;31m");
        printf("\nJour invalide pour le mois de l'année en cours.\n");
        return 0;
    }
    
    int daysInMonth;
    if(month == 2){
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            daysInMonth = 29;
        }else {
            daysInMonth = 28;
        }
    }else if(month == 4 || month == 6 || month == 9 || month == 11){
        daysInMonth = 30;
    }else{
        daysInMonth = 31;
    }

    if(day > daysInMonth){
        printf("\033[0;31m");
        printf("\nNombre de jours invalide pour le mois %d.\n", month);
        return 0;
    }
    return 1;
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
int loadUsersPres(USER users[]) {
    FILE *file = fopen(fileP, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int id = 0;
    while (fscanf(file, "%u %s %s %s %s,", &users[id].id,users[id].nom,users[id].prenom, users[id].date,users[id].heure) == 5) {
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
void menuConnexionAdmin(){
    puts("-----------------------------------------------------");
    puts("--------------> Marquer les presences <--------------");
    puts("-----------------------------------------------------");
    printf("Entrer votre code [Q pour quitter]:");
}
void menuApprenant(){
    puts("\n1………..MARQUER MA PRÉSENCE");
    puts("2………..NOMBRE DE MINUTES D’ABSENCE");
    puts("3………..MES MESSAGES (0)");
    puts("4………..QUITTER");
}
void menuGenererFichier(){
     puts("\n1………..Toutes les présences");
    puts("2………..Générer par date");
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

// void dateActu(char *date){
//      time_t now;
//     time(&now);
//     struct tm *currentTime = localtime(&now);
//     strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", currentTime);
// }

void inverserChaine(char* str, int len, int i, int temp)
{
    // if current index is less than the remaining length of
    // string
    if (i < len) {
        temp = str[i];
        str[i] = str[len - 1];
        str[len - 1] = temp;
        i++;
        len--;
        inverserChaine(str, len, i, temp);
    }
}




void verifieDateSaisi(char *date){
    while (getchar() != '\n');
    int isValid = 0;
    do {
        printf("\033[0m");
        printf("\nVeuillez saisir une date au format(jj-mm-aaaa) : ");
        fgets(date, sizeof(date), stdin);
        // Supprimer le caractère de nouvelle ligne s'il est présent
        //date[strcspn(date, "\n")] = '\0';
            printf("la date saisi est : %s",date);

        if(strlen(date) == 10){
            printf("j'entre ici\n");
            isValid = validerDate(date);
        }else{
            printf("\033[0;31m");
            printf("\nFormat de date incorrect. Veuillez saisir la date au format jj-mm-aaaa.\n");
            printf("\033[0m");
            continue;
        }

        // Vider le tampon d'entrée
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }while (!isValid);

}