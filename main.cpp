#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iomanip>
// Курсова робота,  індивідуальне завдання № 22
// Виконав: Якубович Сргій, КБ-14-1
struct Subscrip //Дані про підписні видання
{
    char country[30]; //країна подорожі
    int days; //кількість днів
    char date[11]; //дата відправлення
    char modeTransport[20]; //вид транспорту
    double price; //ціна
} travel[1000];

void MenuMain();
void OpenList(char *);
void ReadOpenFile(char *);
void Create();
void CreateListFile();
void Enter(char *, char *);
void Sort_1(char *);
void Sort_2(char *);
void Sort_3(char *);
void Error(char *);

FILE *file;
char countryTemp[15], dateTemp[11], modeTransportTemp[20], priceTemp[10];

using namespace std;

int main()
{
    setlocale(LC_ALL, "Ukr");
    CreateListFile();
    MenuMain();
    system("PAUSE");
    return EXIT_SUCCESS;
}
void CreateListFile() //створення файлу зі списком імен файлів записів
{
    if ((file=fopen("ListSavedFiles.txt","rt"))==NULL)
        file=fopen("ListSavedFiles.txt","wt");
    fclose(file);
}
void MenuMain() //Початкове меню
{
     system("CLS");
     int opt;
     cout<<"\n\n\t\t\tIнформацiйно-пошукова система\n"<<endl;
     cout<<"\t1. Створити файл"<<endl;
     cout<<"\t2. Вiдкрити файл для додання нових даних"<<endl;
     cout<<"\t3. Вiдкрити файл для виводу усiх записiв"<<endl;
     cout<<"\t4. Вивести усi тури до певної країни заданого мiсяця року"<<endl;
     cout<<"\t5. Вивести перелiк турiв, не довших заданої кiлькостi днiв"<<endl;
     cout<<"\t6. Вивести перелiк турiв заданого часового дiапазону та цiнового\
 обмеже-\t   ння"<<endl;
     cout<<"\t7. Вихiд"<<endl;
     cout<<"\tВведiть номер пункту меню :"<<endl;
     cin>>opt;
     switch (opt)
     {
         case 1: Create(); break;
         case 2: OpenList("a"); break;
         case 3: OpenList("r"); break;
         case 4: OpenList("1"); break;
         case 5: OpenList("2"); break;
         case 6: OpenList("3"); break;
         case 7: exit(1);
         default: system("CLS"); MenuMain();
     }
}
void OpenList(char *regime) //відкити список збережених раніше файлів (п. 2, 3)
{
    system("CLS");
    int nunInList=1; char nameFile[40]; //номер файлу у списку; файл зі списку
    char nameFileTemp[40]; //тимчасове ім'я файлу
    char nameFileTemp2[40]; //тимчасове ім'я файлу 2
    int numTemp;//номер бажаного файлу
    file=fopen("ListSavedFiles.txt","rt");
    cout<<"\n\n\t\t\tСписок ранiше збережених файлiв :"<<endl;
    while (!feof(file))
    {
        fgets(nameFileTemp2, 40, file);
        cout<<"\t"<<nunInList++<<". "<<nameFileTemp2;
    }
    
    cout<<"\n\tВведiть номер файлу, який хочете вiдкрити :"<<endl;
    cin>>numTemp;
    
    nunInList=1;
    rewind(file); //вказівник зміщується на початок файлу
    while (!feof(file))
    {
        fgets(nameFileTemp, 40, file);
        if (numTemp==nunInList)
           for(int i=0;i<strlen(nameFileTemp);i++)
           {
               nameFile[i]=nameFileTemp[i];
               nameFile[i+1]='\0';
               if (nameFileTemp[i+1]=='\n') break;
           }
        nunInList++;
    }
    fclose(file);
    if (regime=="r") ReadOpenFile(nameFile);
    if (regime=="a") Enter(nameFile,regime);
    if (regime=="1") Sort_1(nameFile);
    if (regime=="2") Sort_2(nameFile);
    if (regime=="3") Sort_3(nameFile);
}
void ReadOpenFile(char *nameFile) //для зчитування відкритого файлу (п. 3)
{
    int daysTemp;
    Error(nameFile);
    cout<<"\n\t\t          <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t\t     <<<<< Усi записи у файлi >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    Країна     |   Днiв   |Дата вiдправлення|Транспорт |    Цiна    |";
    cout<<"\n|               |          |                 |          |            |"<<endl;
    while(!feof(file))
    {
        fscanf(file, "%s %u %s %s %s", countryTemp, &daysTemp, dateTemp,\
modeTransportTemp, priceTemp);

        for (int i=0;i<70;i++) cout<<"=";
        cout<<"\n| "<<setw(13)<<countryTemp<<" | "<<setw(8)<<daysTemp<<" | "\
<<setw(15)<<dateTemp<<" | "<<setw(8)<<modeTransportTemp<<" | "<<setw(10)<<priceTemp<<" |"<<endl;

    }
    for (int i=0;i<70;i++) cout<<"=";
    cout<<endl<<endl;
    fclose(file);
    system("PAUSE");
    MenuMain();
    return;
}
void Create() //створення нового файлу
{
    char nameFile[30]={"/0"}; //ім'я нового файлу
    char nameFileInList[30]; //імена файлів у списку
    char answ; //відповідь Y/N 
    system("CLS");
    cout<<"\n\t\t\tВведiть iм'я файлу :"<<endl;
    getchar();
    gets(nameFile);
    int n=strlen(nameFile); //довжина імені нового файла, а також ін.- тимчасове
    if ((nameFile[n-4]!='.') || (nameFile[n-3]!='t') || (nameFile[n-2]!='x')
|| (nameFile[n-1]!='t')) //Перевірка, чи закінчується ім'я файлу на '.txt'
        strcat(nameFile,".txt");//якщо ні, то файлу задається розширення .txt
    if ((file=fopen(nameFile,"rt"))==NULL) //перевірка чи файл існує
        file=fopen(nameFile,"wt"); //якщо ні, то він створюється
    else                           //Якщо існує, то є можливість замінити
    {                              //раніше збережений файл
        cout<<"Файл з таким iм'ям уже iснує. Замiнити? (Y/N)"<<endl;
        cin>>answ;
        if ((answ!='Y') && (answ!='y'))
        {
            MenuMain();
            return;
        }
    }
    fclose(file);
    file=fopen("ListSavedFiles.txt","a+t");
    n=0;
    while (!feof(file)) //перевірка чи є файл з таким ім'ям у списку раніше
    {                   //збережених файлів (так - n=1, ні -  n=0)
        fgets(nameFileInList, 30, file);
        int temp=strlen(nameFileInList); //позбавляє ім'я зі списку символу
        if (strcmp(nameFile,nameFileInList)!=0)// переходу на новий рядок
            nameFileInList[temp-1]=nameFileInList[temp];
        if (strcmp(nameFile,nameFileInList)==0)
            n=1;
    }
    if (n==0) //якщо файл немає в списку, то він додається
    {
        fputs("\n",file);
        fputs(nameFile, file);
    }
    fclose(file);
    Enter(nameFile,"w");
}
void Enter(char *nameFile, char *regime) //Введення даних до файлу
{
    system("CLS");
    file=fopen(nameFile, regime);
    int n;
    cout<<"\n\t<<Скiльки путiвок є у турагенствi?>>"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"\tВведiть "<<i+1<<"-у країну подорожi (бажано ISO-код країни):"<<endl;
        getchar();
        gets(travel[i].country);
        cout<<"\tКiлькiсть днiв:"<<endl;
        cin>>travel[i].days;
        cout<<"\tДата вiдправлення (у форматi дд.мм.рррр):"<<endl;
        getchar();
        gets(travel[i].date);
        cout<<"\tВид транспорту:"<<endl;
        gets(travel[i].modeTransport);
        cout<<"\tЦiна:"<<endl;
        cin>>travel[i].price;
        if (regime=="a") fputs("\n",file);
        fprintf(file, "%s %i %s %s %.2lf", travel[i].country, travel[i].days,
travel[i].date, travel[i].modeTransport, travel[i].price);
        if ((regime=="w") && (i!=n-1)) fputs("\n",file);
    }
    fclose(file);
    system("PAUSE");
    MenuMain();
    return;
}

void Sort_1(char *nameFile) //Вивести усi тури до певної країни заданого мiсяця року (п. 4)
{
    system("CLS");
    char country[30]; //країна, яку задає користувач
    char mounth[3]; //заданий користувачем місяць року
    char info[80];
    char mounthTemp[3];
    int daysTemp;
    cout<<"\tВведiть країну подорожi: "<<endl;
    getchar();
    gets(country);
    cout<<"\tВведiть порядковий номер потрiбного мiсяця: "<<endl;
    gets(mounth);
    if (strlen(mounth)==1)
    {
        mounth[1]=mounth[0];
        mounth[0]='0';
        mounth[2]='\0';
    }
    Error(nameFile);
    cout<<"\n\t\t             <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t\t<<<<< Усi тури до країни "<<country<<" у мiсяцi "<<mounth<<" >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    Країна     |   Днiв   |Дата вiдправлення|Транспорт |    Цiна    |";
    cout<<"\n|               |          |                 |          |            |"<<endl;
    while(!feof(file))
    {
        fscanf(file, "%s %u %s %s %s", countryTemp, &daysTemp, dateTemp,\
modeTransportTemp, priceTemp);
        
        mounthTemp[0]=dateTemp[3];
        mounthTemp[1]=dateTemp[4];
        mounthTemp[2]='\0';
        
        if ((strcmp(country,countryTemp)==0) && (strcmp(mounth,mounthTemp)==0))
        {
        for (int i=0;i<70;i++) cout<<"=";
        cout<<"\n| "<<setw(13)<<countryTemp<<" | "<<setw(8)<<daysTemp<<" | "\
<<setw(15)<<dateTemp<<" | "<<setw(8)<<modeTransportTemp<<" | "<<setw(10)<<priceTemp<<" |"<<endl;
        }
    }
    for (int i=0;i<70;i++) cout<<"=";
    cout<<endl<<endl;
    fclose(file);
    system("PAUSE");
    MenuMain();
    return;
}

void Sort_2(char *nameFile) //Вивести перелiк турiв, не довших заданої кiлькостi днiв (п. 5)
{
    system("CLS");
    int days; //кількість днів, яку задає користувач
    char info[80];
    int daysTemp;
    cout<<"\tВведiть кiлькiсть днiв: "<<endl;
    cin>>days;
    Error(nameFile);
    cout<<"\n\t\t          <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t <<<<< Перелiк турiв, тривалiсть яких менша "<<days;
    if (days==1) cout<<" дня >>>>>"<<endl;
    else cout<<" днiв >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    Країна     |   Днiв   |Дата вiдправлення|Транспорт |    Цiна    |";
    cout<<"\n|               |          |                 |          |            |"<<endl;
    while(!feof(file))
    {
        fscanf(file, "%s %u %s %s %s", countryTemp, &daysTemp, dateTemp,\
modeTransportTemp, priceTemp);
        
        if (daysTemp<days)
        {
        for (int i=0;i<70;i++) cout<<"=";
        cout<<"\n| "<<setw(13)<<countryTemp<<" | "<<setw(8)<<daysTemp<<" | "\
<<setw(15)<<dateTemp<<" | "<<setw(8)<<modeTransportTemp<<" | "<<setw(10)<<priceTemp<<" |"<<endl;
        }

    }
    for (int i=0;i<70;i++) cout<<"=";
    cout<<endl<<endl;
    fclose(file);
    system("PAUSE");
    MenuMain();
    return;
}
void Sort_3(char *nameFile) //Вивести перелiк турiв заданого часового дiапазону та цiнового обмеження (п. 6)
{
    system("CLS");
    double price; //ціна, яку задає користувач
    char dateFirst[11], dateLast[11]; //діапазон дат
    char dateDaysFirst[3], dateDaysLast[3], dateMounthFirst[3], dateMounthLast[3], dateYearFirst[5], dateYearLast[5];
    int dateFirstNum, dateLastNum, dateTempNum;
    int daysTemp;
    cout<<"\tВведiть цiну: "<<endl;
    cin>>price;
    cout<<"\tВведiть початок та кiнець дiапозону дат (у форматi дд.мм.рррр): "<<endl;
    getchar();
    gets(dateFirst);
    gets(dateLast);
    
    dateFirstNum=atoi(&dateFirst[6])*10000+atoi(&dateFirst[3])*100+atoi(dateFirst);
    dateLastNum=atoi(&dateLast[6])*10000+atoi(&dateLast[3])*100+atoi(dateLast);
    
    Error(nameFile);
    cout<<"\n\t                 <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n << Перелiк турiв з "<<dateFirst<<" по "<<dateLast<<" за цiною, не\
 бiльшою нiж "<<setiosflags(ios::fixed)<<setprecision(2)<<price<<" >>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    Країна     |   Днiв   |Дата вiдправлення|Транспорт |    Цiна    |";
    cout<<"\n|               |          |                 |          |            |"<<endl;
    while(!feof(file))
    {
        fscanf(file, "%s %u %s %s %s", countryTemp, &daysTemp, dateTemp,\
modeTransportTemp, priceTemp);
        dateTempNum=atoi(&dateTemp[6])*10000+atoi(&dateTemp[3])*100+atoi(dateTemp);
        if ((atof(priceTemp)<=price) && (dateTempNum>=dateFirstNum) && (dateTempNum<=dateLastNum))
        {
        for (int i=0;i<70;i++) cout<<"=";
        cout<<"\n| "<<setw(13)<<countryTemp<<" | "<<setw(8)<<daysTemp<<" | "\
<<setw(15)<<dateTemp<<" | "<<setw(8)<<modeTransportTemp<<" | "<<setw(10)<<priceTemp<<" |"<<endl;
        }

    }
    for (int i=0;i<70;i++) cout<<"=";
    cout<<endl<<endl;
    fclose(file);
    system("PAUSE");
    MenuMain();
    return;
}
void Error(char *nameFile) //перевірка на помилку відкриття файлу
{
    system("CLS");
    if((file=fopen(nameFile,"rt"))==NULL)
    {
        cout<<"Помилка вiдкриття файлу "<<nameFile<<endl;
        system("PAUSE");
        MenuMain();
        return;
    }
}
