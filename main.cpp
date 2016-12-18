#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iomanip>
// ������� ������,  ������������ �������� � 22
// �������: �������� ����, ��-14-1
struct Subscrip //��� ��� ������ �������
{
    char country[30]; //����� �������
    int days; //������� ���
    char date[11]; //���� �����������
    char modeTransport[20]; //��� ����������
    double price; //����
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
void CreateListFile() //��������� ����� � ������� ���� ����� ������
{
    if ((file=fopen("ListSavedFiles.txt","rt"))==NULL)
        file=fopen("ListSavedFiles.txt","wt");
    fclose(file);
}
void MenuMain() //��������� ����
{
     system("CLS");
     int opt;
     cout<<"\n\n\t\t\tI�������i���-�������� �������\n"<<endl;
     cout<<"\t1. �������� ����"<<endl;
     cout<<"\t2. �i������ ���� ��� ������� ����� �����"<<endl;
     cout<<"\t3. �i������ ���� ��� ������ ��i� �����i�"<<endl;
     cout<<"\t4. ������� ��i ���� �� ����� ����� �������� �i���� ����"<<endl;
     cout<<"\t5. ������� �����i� ���i�, �� ������ ������ �i������i ��i�"<<endl;
     cout<<"\t6. ������� �����i� ���i� �������� �������� �i������� �� �i������\
 ������-\t   ���"<<endl;
     cout<<"\t7. ���i�"<<endl;
     cout<<"\t����i�� ����� ������ ���� :"<<endl;
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
void OpenList(char *regime) //������ ������ ���������� ����� ����� (�. 2, 3)
{
    system("CLS");
    int nunInList=1; char nameFile[40]; //����� ����� � ������; ���� � ������
    char nameFileTemp[40]; //��������� ��'� �����
    char nameFileTemp2[40]; //��������� ��'� ����� 2
    int numTemp;//����� �������� �����
    file=fopen("ListSavedFiles.txt","rt");
    cout<<"\n\n\t\t\t������ ���i�� ���������� ����i� :"<<endl;
    while (!feof(file))
    {
        fgets(nameFileTemp2, 40, file);
        cout<<"\t"<<nunInList++<<". "<<nameFileTemp2;
    }
    
    cout<<"\n\t����i�� ����� �����, ���� ������ �i������ :"<<endl;
    cin>>numTemp;
    
    nunInList=1;
    rewind(file); //�������� �������� �� ������� �����
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
void ReadOpenFile(char *nameFile) //��� ���������� ��������� ����� (�. 3)
{
    int daysTemp;
    Error(nameFile);
    cout<<"\n\t\t          <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t\t     <<<<< ��i ������ � ����i >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    �����     |   ��i�   |���� �i����������|��������� |    �i��    |";
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
void Create() //��������� ������ �����
{
    char nameFile[30]={"/0"}; //��'� ������ �����
    char nameFileInList[30]; //����� ����� � ������
    char answ; //������� Y/N 
    system("CLS");
    cout<<"\n\t\t\t����i�� i�'� ����� :"<<endl;
    getchar();
    gets(nameFile);
    int n=strlen(nameFile); //������� ���� ������ �����, � ����� ��.- ���������
    if ((nameFile[n-4]!='.') || (nameFile[n-3]!='t') || (nameFile[n-2]!='x')
|| (nameFile[n-1]!='t')) //��������, �� ���������� ��'� ����� �� '.txt'
        strcat(nameFile,".txt");//���� �, �� ����� �������� ���������� .txt
    if ((file=fopen(nameFile,"rt"))==NULL) //�������� �� ���� ����
        file=fopen(nameFile,"wt"); //���� �, �� �� �����������
    else                           //���� ����, �� � ��������� �������
    {                              //����� ���������� ����
        cout<<"���� � ����� i�'�� ��� i���. ���i����? (Y/N)"<<endl;
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
    while (!feof(file)) //�������� �� � ���� � ����� ��'�� � ������ �����
    {                   //���������� ����� (��� - n=1, � -  n=0)
        fgets(nameFileInList, 30, file);
        int temp=strlen(nameFileInList); //��������� ��'� � ������ �������
        if (strcmp(nameFile,nameFileInList)!=0)// �������� �� ����� �����
            nameFileInList[temp-1]=nameFileInList[temp];
        if (strcmp(nameFile,nameFileInList)==0)
            n=1;
    }
    if (n==0) //���� ���� ���� � ������, �� �� ��������
    {
        fputs("\n",file);
        fputs(nameFile, file);
    }
    fclose(file);
    Enter(nameFile,"w");
}
void Enter(char *nameFile, char *regime) //�������� ����� �� �����
{
    system("CLS");
    file=fopen(nameFile, regime);
    int n;
    cout<<"\n\t<<��i���� ���i��� � � ����������i?>>"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"\t����i�� "<<i+1<<"-� ����� �������i (������ ISO-��� �����):"<<endl;
        getchar();
        gets(travel[i].country);
        cout<<"\t�i���i��� ��i�:"<<endl;
        cin>>travel[i].days;
        cout<<"\t���� �i���������� (� ������i ��.��.����):"<<endl;
        getchar();
        gets(travel[i].date);
        cout<<"\t��� ����������:"<<endl;
        gets(travel[i].modeTransport);
        cout<<"\t�i��:"<<endl;
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

void Sort_1(char *nameFile) //������� ��i ���� �� ����� ����� �������� �i���� ���� (�. 4)
{
    system("CLS");
    char country[30]; //�����, ��� ���� ����������
    char mounth[3]; //������� ������������ ����� ����
    char info[80];
    char mounthTemp[3];
    int daysTemp;
    cout<<"\t����i�� ����� �������i: "<<endl;
    getchar();
    gets(country);
    cout<<"\t����i�� ���������� ����� ����i����� �i����: "<<endl;
    gets(mounth);
    if (strlen(mounth)==1)
    {
        mounth[1]=mounth[0];
        mounth[0]='0';
        mounth[2]='\0';
    }
    Error(nameFile);
    cout<<"\n\t\t             <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t\t<<<<< ��i ���� �� ����� "<<country<<" � �i���i "<<mounth<<" >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    �����     |   ��i�   |���� �i����������|��������� |    �i��    |";
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

void Sort_2(char *nameFile) //������� �����i� ���i�, �� ������ ������ �i������i ��i� (�. 5)
{
    system("CLS");
    int days; //������� ���, ��� ���� ����������
    char info[80];
    int daysTemp;
    cout<<"\t����i�� �i���i��� ��i�: "<<endl;
    cin>>days;
    Error(nameFile);
    cout<<"\n\t\t          <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n\t <<<<< �����i� ���i�, ������i��� ���� ����� "<<days;
    if (days==1) cout<<" ��� >>>>>"<<endl;
    else cout<<" ��i� >>>>>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    �����     |   ��i�   |���� �i����������|��������� |    �i��    |";
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
void Sort_3(char *nameFile) //������� �����i� ���i� �������� �������� �i������� �� �i������ ��������� (�. 6)
{
    system("CLS");
    double price; //����, ��� ���� ����������
    char dateFirst[11], dateLast[11]; //������� ���
    char dateDaysFirst[3], dateDaysLast[3], dateMounthFirst[3], dateMounthLast[3], dateYearFirst[5], dateYearLast[5];
    int dateFirstNum, dateLastNum, dateTempNum;
    int daysTemp;
    cout<<"\t����i�� �i��: "<<endl;
    cin>>price;
    cout<<"\t����i�� ������� �� �i���� �i������� ��� (� ������i ��.��.����): "<<endl;
    getchar();
    gets(dateFirst);
    gets(dateLast);
    
    dateFirstNum=atoi(&dateFirst[6])*10000+atoi(&dateFirst[3])*100+atoi(dateFirst);
    dateLastNum=atoi(&dateLast[6])*10000+atoi(&dateLast[3])*100+atoi(dateLast);
    
    Error(nameFile);
    cout<<"\n\t                 <<<<< "<<nameFile<<" >>>>>";
    cout<<"\n << �����i� ���i� � "<<dateFirst<<" �� "<<dateLast<<" �� �i���, ��\
 �i����� �i� "<<setiosflags(ios::fixed)<<setprecision(2)<<price<<" >>"<<endl;
    for (int i=0;i<70;i++) cout<<"=";
    cout<<"\n|               |          |                 |          |            |";
    cout<<"\n|    �����     |   ��i�   |���� �i����������|��������� |    �i��    |";
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
void Error(char *nameFile) //�������� �� ������� �������� �����
{
    system("CLS");
    if((file=fopen(nameFile,"rt"))==NULL)
    {
        cout<<"������� �i������� ����� "<<nameFile<<endl;
        system("PAUSE");
        MenuMain();
        return;
    }
}
