#include <iostream>
#include <string.h>
using namespace std;
#define MAX 10

struct hash {
    char name[20];
    long int tele;
    int chain;
}rec[MAX];

class hashTable {
public:
    hashTable() {
        for(int i=0;i<MAX;i++) {
            strcpy(rec[i].name,"-");
            rec[i].tele = 0;
            rec[i].chain = -1;
        }
    }

    int hashing(long int tel) {
        return (tel%MAX);
    }
    void WithReplacement(struct hash h);
    void WithoutReplacement(struct hash h);
    void disp();

};

void hashTable::WithoutReplacement(struct hash h) {

		int k = hashing(h.tele);
	    int p = k;
	    int i;

	    if(rec[k].tele == 0) {
	        rec[k].tele = h.tele;
	        strcpy(rec[k].name, h.name);
	    }
	    else {
	       i = k+1;              // i points to next record
	       if(i >= MAX)          // to move to first record if i is greater than 9
	    	   i = i%MAX;
	       do
	       {

	            if(rec[i].tele == 0)
	            {
	                rec[i].tele = h.tele;
	                strcpy(rec[i].name, h.name);
	                int j=k;
										do
										{
											if(hashing(rec[j].tele) == k && rec[j].chain == -1)
											{
												rec[j].chain = i;
												break;
											}
											j++;
											if(j >= MAX)
												j = j%MAX;
										}while(j%MAX != k);
	                break;
	            }

	            i++;

	        }while(i%MAX!=k);

	       if(i == k)
	       {
	            cout<<"\nSorry, could'nt insert new record. Hash Table is full... ";
	        }

	    }
}

void hashTable::disp() {
    cout<<"\n\n";
    cout<<"\n\tINDEX\tNAME\tTELEPHONE\tCHAIN";
    for(int i=0; i<MAX; i++) {
        if(rec[i].tele == 0) {
            cout<<"\n\t  "<<i<<"\t"<<rec[i].name<<"\t"<<rec[i].tele<<"\t"<<rec[i].chain;
        } else {
        cout<<"\n\t  "<<i<<"\t"<<rec[i].name<<"\t"<<rec[i].tele<<"\t"<<rec[i].chain;
        }
    }
}

void hashTable::WithReplacement(struct hash h)
{
    int k = hashing(h.tele);
    int p = k;
    int i, change_pos;
    if(rec[k].tele == 0)
    {
        rec[k].tele = h.tele;
        strcpy(rec[k].name, h.name);
    }
    else if(hashing(rec[k].tele) == hashing(h.tele))
    {
       i = k+1;
       if(i >= MAX)
    	   i = i%MAX;
       do
       {
            if(hashing(rec[i].tele) == k)
            {
                p = k;
            }
            if(rec[i].tele == 0)
            {
                rec[i].tele = h.tele;
                strcpy(rec[i].name, h.name);
                int j=k;
                do
                {
					if(hashing(rec[j].tele) == k && rec[j].chain == -1)
					{
						rec[j].chain = i;
						break;
					}
					j++;
					if(j >= MAX)
						j = j%MAX;
                }while(j%MAX != k);

                break;
            }
            i++;
        }while(i%MAX!=k);
        if(i == k)
        {
            cout<<"\nSorry, could'nt insert new record. Hash Table is full... ";
        }
    }//else part is different
    else
    {
        hash temp;
        temp.tele = rec[k].tele;
        strcpy(temp.name,rec[k].name);
        temp.chain = rec[k].chain;
        rec[k].tele = h.tele;
        rec[k].chain = -1;
        strcpy(rec[k].name, h.name);

        i = k + 1;
        if(i >= MAX)
        	i = i%MAX;
        do
        {
            if(rec[i].tele == 0)
            {
                rec[i].tele = temp.tele;
                strcpy(rec[i].name, temp.name);

                rec[i].chain = temp.chain;
                change_pos = i;
                break;
            }
            i++;
        } while(i%MAX != k);

        for(i=0;i<MAX;i++)
        {
            if(rec[i].chain == k)
            {
            	if(change_pos >= MAX)
            		change_pos = change_pos-MAX;
                rec[i].chain = change_pos;
                break;
            }
        }
    }
}

int main()
{
    int ch, c=1;
    hashTable ht;
    hash h;

    do
    {
        cout<<"\n\n1. without replacement \n2.with replacement " ;
        cin>>ch;

        switch(ch)
        {

            case 1:
                cout<<"\nEnter name :\t";
                cin>>h.name;
                cout<<"\nEnter telephone number :\t";
                cin>>h.tele;
                ht.WithoutReplacement(h);
                ht.disp();
                break;

            case 2:
                cout<<"\nEnter name :\t";
                cin>>h.name;
                cout<<"\nEnter telephone number :\t";
                cin>>h.tele;
                ht.WithReplacement(h);
                ht.disp();
                break;
        }
    }while(c==1);

    return 0;
}
