#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;


//implement to avoid empty lines and spaces and tab


//ask for the name of this cpp
// ask if "addmid"'s index was larger than count
//ask if delete 2 to 2 work
//ask what's supposed to happen when you add before//after out of range index
//ask about the argument manager file name (command or sort)
//ask about argument manager command line

struct people
{
    //0=id; 1=firstname; 2=lastname; 3=DOB; 4=years worked; 5=salary; 6=position
    string data[7];
    people *next;
    people *prev;
};

class linkedlist
{
private:
    people *head;
    people *tail;
    people *original;
    people *newtail;
public:
    linkedlist();
    void addend(string arr[7]);
    void deletebeg();
    void addmid(string arr[7], int);
    void addbeg(string arr[7]);
    void deleteend();
    void addend2(string arr[7]);
    void print(string name);
    void deleteid(string);
    void copiedhead();
    void deleteind(int, int);
    int count();
    void toarray(people arr[]);
    void mergesort(people arr[], int l, int r, int ind);
    void merge(people arr[], int l, int m, int r, int ind);
    void tolink(people arr[]);
    int sortcommand(string line);
    void outputori(string name);
    void deletecommand(string line);
    void input(string line, string data[9], string finaldata[7]);
    
};



int main(int argc, char * argv[])
{
    if (argc < 2) {
        cout << "Usage: sort \"input=<file>;output=<file>;sort=<file>\"" << endl;
        return -1;
    }
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outputfilename= am.get("output");
    string commandfilename = am.get("command");
    cout << "File name for input: " << infilename << endl <<"File name for output: "<< outputfilename << endl<< "File name for command: " << commandfilename << endl;
    
    
    ifstream inputfile;
    inputfile.open(infilename);
    string line;
    string data[9];
    string finaldata[7];
    linkedlist hey;
    ofstream writingfile;
    writingfile.open(outputfilename, std::ios::out | std::ios::trunc);
    writingfile.close();
    while (getline(inputfile, line))
    {
        if (line=="" || line=="\n")
            continue;
        hey.input(line, data, finaldata);
        hey.addend(finaldata);
        hey.addend2(finaldata);
    }
    inputfile.close();
    //hey.copiedhead();
    inputfile.open(commandfilename);
    while (getline(inputfile, line))
    {
        if (line=="" || line=="\n")
            continue;
        if (line.at(0)=='s')
        {
            int ind;
            ind=hey.sortcommand(line);
            people array[hey.count()];
            hey.toarray(array);
            hey.mergesort(array, 0, hey.count()-1, ind);
            hey.tolink(array);
            hey.print(outputfilename);
        }
        if (line.at(0)=='o')
        {
            hey.outputori(outputfilename);
        }
        if (line.at(0)=='d')
        {
            hey.deletecommand(line);
            hey.print(outputfilename);
        }
        
        if (line.at(0)=='a')
        {
            string dat[9];
            string finaldat[7];
            line=line.erase(0,4);
            if (line.at(1)=='t')
            {
                line.erase(0,3);
                string line1;
                if (line.at(0)=='b')
                {
                    int indnum=0;
                    while(inputfile.peek()=='1' || inputfile.peek()=='2' ||inputfile.peek()=='3' ||inputfile.peek()=='4' ||inputfile.peek()=='5' ||inputfile.peek()=='6' ||inputfile.peek()=='7' ||inputfile.peek()=='8' ||inputfile.peek()=='9' ||inputfile.peek()=='0')
                    {
                        getline(inputfile, line1);
                        hey.input(line1, dat, finaldat);
                        hey.addmid(finaldat, indnum);
                        indnum++;
                    }
                }
                else if (line.at(0)=='e')
                {
                    string line1;
                    while(inputfile.peek()=='1' || inputfile.peek()=='2' ||inputfile.peek()=='3' ||inputfile.peek()=='4' ||inputfile.peek()=='5' ||inputfile.peek()=='6' ||inputfile.peek()=='7' ||inputfile.peek()=='8' ||inputfile.peek()=='9' ||inputfile.peek()=='0')
                    {
                        getline(inputfile, line1);
                        hey.input(line1, dat, finaldat);
                        hey.addend(finaldat);
                    }
                    
                }
            }
            if (line.at(2)=='f')
            {
                line=line.erase(0,7);
                int index=0;
                stringstream geek(line);
                geek>>index;
                string line1;
                while(inputfile.peek()=='1' || inputfile.peek()=='2' ||inputfile.peek()=='3' ||inputfile.peek()=='4' ||inputfile.peek()=='5' ||inputfile.peek()=='6' ||inputfile.peek()=='7' ||inputfile.peek()=='8' ||inputfile.peek()=='9' ||inputfile.peek()=='0')
                {
                    getline(inputfile, line1);
                    hey.input(line1, dat, finaldat);
                    hey.addmid(finaldat, index);
                    index++;
                }
                
            }
            else if (line.at(0)=='a')
            {
                line=line.erase(0,6);
                int index=0;
                stringstream geek(line);
                geek>>index;
                index++;
                string line1;
                while(inputfile.peek()=='1' || inputfile.peek()=='2' ||inputfile.peek()=='3' ||inputfile.peek()=='4' ||inputfile.peek()=='5' ||inputfile.peek()=='6' ||inputfile.peek()=='7' ||inputfile.peek()=='8' ||inputfile.peek()=='9' ||inputfile.peek()=='0')
                {
                    getline(inputfile, line1);
                    hey.input(line1, dat, finaldat);
                    hey.addmid(finaldat, index);
                    index++;
                }
                
            }

            hey.print(outputfilename);
        }
        
        
        if (inputfile.peek()!=-1)
        {
            ofstream file;
            file.open(outputfilename, ios::out | ios::app);
            file<<endl<<endl;
        }
    }
    
   
    return 0;
}


void linkedlist :: input(string line,string data[9],string finaldata[7] )
{
    string token;
    istringstream ss(line);
    int count=0;
    while (getline(ss, token,' '))
    {
        data[count]=token;
        count++;
    }
    string dob;
    dob.append(data[5]);
    dob.append(data[3]);
    dob.append(data[4]);
    int j=0;
    for (int i=0;i<9;i++)
    {
        if (i==3)
        {
            finaldata[j]=dob;
            i+=2;
            j++;
            continue;
        }
        
        if (i==8)
        {
            cout<<data[i]<<"-"<<endl;
        }
        
        finaldata[j]=data[i];
        j++;
    }
}

void linkedlist :: deletecommand(string line)
{
    line=line.erase(0, 7);
    if (line.at(0)=='a')
    {
        line.erase(0,3);
        if (line.at(0)=='b')
        {
            deletebeg();
        }
        else
        {
            deleteend();
        }
        return;
    }
    string check="id";
    for (int i=0;i<line.length();i++)
    {
        if (line.at(i)=='t')
        {
            check="index";
        }
    }
    if (check=="id")
    {
        deleteid(line);
        return;
    }
    if (check=="index")
    {
        int counter=0;
        for (int i=0;i<line.length();i++)
        {
            if (line.at(i)==' ')
            {
                break;
            }
            counter++;
        }
        string tempind1=line.substr(0, counter);
        line=line.erase(0, counter+4);
        int ind1=0, ind2=0;
        stringstream geek(tempind1);
        geek>>ind1;
        stringstream geek1(line);
        geek1>>ind2;
        deleteind(ind1, ind2);
        return;
    }
    
    
}

void linkedlist :: outputori(string name)
{
    if (original==0)
        return;
    ofstream file;
    file.open(name, ios::out | ios::app);
    people *cu=original;
    while (cu->next!=NULL)
    {
        string year=cu->data[3].substr(0,4);
        string month=cu->data[3].substr(4,2);
        string day=cu->data[3].substr(6,2);
        file<<cu->data[0]<<" "<<cu->data[1]<<" "<<cu->data[2]<<" "<<month<<" "<<day<<" "<<year<<" "<<cu->data[4]<<" "<<cu->data[5]<<" "<<cu->data[6];
        cu=cu->next;
        file<<endl;
    }
    string year=cu->data[3].substr(0,4);
    string month=cu->data[3].substr(4,2);
    string day=cu->data[3].substr(6,2);
    file<<cu->data[0]<<" "<<cu->data[1]<<" "<<cu->data[2]<<" "<<month<<" "<<day<<" "<<year<<" "<<cu->data[4]<<" "<<cu->data[5]<<" "<<cu->data[6];
}


int linkedlist :: sortcommand(string line)
{
    line=line.erase(0,5);
    int sortind=0;
    if (line.at(0)=='i')
    {
        sortind=0;
    }
    if (line.at(0)=='f')
    {
        sortind=1;
    }
    if (line.at(0)=='l')
    {
        sortind=2;
    }
    if (line.at(0)=='D')
    {
        sortind=3;
    }
    if (line.at(0)=='y')
    {
        sortind=4;
    }
    if (line.at(0)=='s')
    {
        sortind=5;
    }
    if (line.at(0)=='p')
    {
        sortind=6;
    }
    return sortind;
}

void linkedlist:: tolink(people arr[])
{
    people *temp=new people;
    temp->next=0; temp->prev=0;
    int counter=count();
    head=0;
    for (int i=0;i<counter;i++)
    {
        addend(arr[i].data);
    }
}

void linkedlist :: merge(people arr[], int l, int m, int r, int ind)
{
    if (ind==4 || ind ==5)
    {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 =  r - m;
        people L[n1], R[n2];
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1+ j];
        i = 0;
        j = 0;
        k = l;
    
        while (i < n1 && j < n2)
        {
            stringstream geek(L[i].data[ind]);
            int x, y;
            geek>>x;
            stringstream geeks(R[j].data[ind]);
            geeks>>y;
            if (x<=y)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
        return;
    }
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    people L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if ((L[i].data[ind]).compare(R[j].data[ind])<=0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void linkedlist :: mergesort(people arr[], int l, int r, int ind)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergesort(arr, l, m, ind);
        mergesort(arr, m+1, r, ind);
        merge(arr, l, m, r, ind);
    }
}

void linkedlist :: toarray(people arr[])
{
    people *cu=head;
    int i=0;
    while (cu!=0)
    {
        arr[i].data[0]=cu->data[0];
        arr[i].data[1]=cu->data[1];
        arr[i].data[2]=cu->data[2];
        arr[i].data[3]=cu->data[3];
        arr[i].data[4]=cu->data[4];
        arr[i].data[5]=cu->data[5];
        arr[i].data[6]=cu->data[6];
        cu=cu->next;
        i++;
    }
}

void linkedlist :: deleteid(string a)
{
    if (head==0)
        return;
    people *cu=head;
    int counter=1;
    while (cu!=0)
    {
        if (cu->data[0]==a && counter==1)
        {
            deletebeg(); return;
        }
        if (cu->data[0]==a && counter==count())
        {
            deleteend(); return;
        }
        if (cu->data[0]==a)
        {
            cu->prev->next=cu->next;
            cu->next->prev=cu->prev;
            return;
        }
        counter++;
        cu=cu->next;
    }
}

void linkedlist :: deleteind(int ind1, int ind2)
{
    if (head==0 || ind1<0 || ind2< 0 || ind2>count()-1 || ind1>count()-1 || ind1>ind2)
        return;
    people *cu1=head;
    people *cu2=head;
    for (int i=0;i<ind1;i++)
    {
        cu1=cu1->next;
    }
    for (int i=0;i<ind2;i++)
    {
        cu2=cu2->next;
    }
    if (ind1==0 && ind2==count()-1)
    {
        head=0;
        tail=0;
        return;
    }
    if (ind1==0)
    {
        head=cu2->next;
        head->prev=0;
        return;
    }
    if (ind2==count()-1)
    {
        tail=cu1->prev;
        tail->next=0;
        return;
    }
 
    cu1->prev->next=cu2->next;
    cu2->next->prev=cu1->prev;
    delete cu1;
    delete cu2;
}

void linkedlist :: deleteend()
{
    
    if (head==0 || count()==1)
    {
        deletebeg();
        return;
    }
    tail=tail->prev;
    tail->next=0;
}

void linkedlist :: deletebeg()
{
    if (head==0)
        return;
    if (count()==1)
    {
        head=0;
        tail=0;
        return;
    }
    head=head->next;
    head->prev=0;
}

void linkedlist :: addmid(string arr[7], int ind)
{
    people *cu1=head;
    while (cu1!=0)
    {
        if (cu1->data[0]==arr[0])
        {
            return;
        }
        cu1=cu1->next;
    }
    people *temp=new people;
    temp->next=0; temp->prev=0;
    if (ind<0 || ind>count())
        return;
    for (int i=0;i<7;i++)
    {
        temp->data[i]=arr[i];
    }
    
    if (head==0 || ind==0)
    {
        addbeg(arr); return;
    }
    if (ind==count())
    {
        addend(arr); return;
    }
    people *cu=head;
    for (int i=0;i<ind;i++)
    {
        cu=cu->next;
    }
    cu->prev->next=temp;
    temp->prev=cu->prev;
    temp->next=cu;
    cu->prev=temp;
    
}

int linkedlist :: count()
{
    if (head==0)
        return 0;
    int counter=1;
    people *cu=head;
    while (cu->next!=0)
    {
        cu=cu->next;
        counter++;
    }
    return counter;
}

void linkedlist :: copiedhead()
{
    people *cu=head;
    original=head;
}

void linkedlist :: print(string name)
{
    if (head==0)
        return;
    ofstream file;
    file.open(name, ios::out | ios::app);
    people *cu=head;
    
    while (cu->next!=0)
    {

        string year=cu->data[3].substr(0,4);
        string month=cu->data[3].substr(4,2);
        string day=cu->data[3].substr(6,2);
        file<<cu->data[0]<<" "<<cu->data[1]<<" "<<cu->data[2]<<" "<<month<<" "<<day<<" "<<year<<" "<<cu->data[4]<<" "<<cu->data[5]<<" "<<cu->data[6];
        file<<endl;
        
        cu=cu->next;
        
    }
    
    
    string year=cu->data[3].substr(0,4);
    string month=cu->data[3].substr(4,2);
    string day=cu->data[3].substr(6,2);
    
    file<<cu->data[0]<<" "<<cu->data[1]<<" "<<cu->data[2]<<" "<<month<<" "<<day<<" "<<year<<" "<<cu->data[4]<<" "<<cu->data[5]<<" "<<cu->data[6];
    
}

linkedlist:: linkedlist()
{
    head=0;
    tail=0;
    original=0;
    newtail=0;
}

void linkedlist:: addend2(string arr[7])
{
    people *temp=new people;
    temp->next=0; temp->prev=0;
    for (int i=0;i<7;i++)
    {
        temp->data[i]=arr[i];
    }
    if (original==0)
    {
        original=temp;
        newtail=temp;
        return;
    }
    newtail->next=temp;
    temp->prev=newtail;
    newtail=temp;
}

void linkedlist:: addend(string arr[7])
{
    people *cu1=head;
    while (cu1!=0)
    {
        if (cu1->data[0]==arr[0])
        {
            return;
        }
        cu1=cu1->next;
    }
    people *temp=new people;
    temp->next=0; temp->prev=0;
    for (int i=0;i<7;i++)
    {
        temp->data[i]=arr[i];
    }
    if (head==0)
    {
        head=temp;
        tail=temp;
        return;
    }
    tail->next=temp;
    temp->prev=tail;
    tail=temp;
}

void linkedlist ::addbeg(string arr[7])
{
    people *temp=new people;
    temp->next=0; temp->prev=0;
    for (int i=0;i<7;i++)
    {
        temp->data[i]=arr[i];
    }
    if (head==0)
    {
        addend(arr); return;
    }
    temp->next=head;
    head->prev=temp;
    head=temp;
}
