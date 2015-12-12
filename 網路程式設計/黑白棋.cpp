#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;


	int table[17][17];
    char row=64,inRow;
    int column=0,inColumn;
    int tableR,tableC;
    int	chess=1;
    int check;
    int change=0;
    int score1=2,score2=2;
    
    int size=6;

	void checkTable(void);
	void printTable(void);
	void changeTable(int Z);
	void canChess(void);
	void Score(void); 
 
int main() 
{
    
    for(int I=1;I<=size;I++)
    {
        for(int J=1;J<=size;J++)
        {
            table[I][J]=0;
        }
    }
    
    table[size/2][size/2]=1;
    table[size/2 + 1][size/2 + 1]=1;
    table[size/2 + 1][size/2]=2;
    table[size/2][size/2 + 1]=2;
    
    for(int W=0;W <=size*size-5 ;W++)
	{    
	    printTable();
	    
	    score1=0;
		score2=0;
		check=0;
		
	    canChess();
	    
	    Score();
	    
	    if(chess==2)
	    {
		    if(score1-score2>=size*size/2-size)
		    {
		    	cout<<"認輸嗎?	Y:1 N:0 "<<endl;
		    	cin>>check;
		    	if(check==1)
		    	{
		    		break;
		    	}
		    }
		}
		else
		{
			if(score2-score1>=size*size/2-size)
		    {
		    	cout<<"認輸嗎?	Y:1 N:0";
		    	cin>>check;
		    	if(check==1)
		    	{
		    		break;
		    	}
		    }
		}
		
		change==0;
		
		canChess();
		canChess();
		
		if(change!=1)
		{
			break;
		}
		
	    while(1)
	    {
	    	cout<<endl;
	    	cout<<setw(0)<<"玩家1分數: "<< score1<<endl;
	    	cout<<setw(0)<<"玩家2分數: "<< score2<<endl<<endl;
	    	cout<<"目前玩家:"<<chess<<endl; 
	        cout<<"輸入橫排"<<(char)(row+1)<<"~"<<(char)(row+size)<<" : "<< "輸入直排"<<"1~"<<size<<" : ";
	        cin>>inRow>>inColumn;
	        
	        if(inRow <65 || inRow>64+size || inColumn < 1 || inColumn>size)
	        {
	            cout<<"輸入錯誤"<<endl;
	        }
	        else
	        {
	            check=1;
	            cout<<"輸入:"<<inRow<<inColumn<<"確認嗎? Y:1 N:0"<<endl;
	            cin>>check;
	            if(check!=0)
	            { 
	            	 check=1;
	            	 change=0;
	                 tableR=inRow-64;
	                 tableC=inColumn;
	                 
	                 if(table[tableR][tableC]!=0)
	                 {
	                     cout<<"此步無法下"<<endl;
	                 }
	                 else
	                 {
	                     checkTable();
	                     if(change!=1)
	                     {
	                     	cout<<"此步無法下"<<endl;
	                     }
	                     else
	                     {
	                     	table[tableR][tableC]=chess;
	                     	break;
	                     }
	                 }
	            }
	        }
	    }
	    
	    if(chess==1)
	    {
		    chess=2;
		}
	    else
	    {
	    	chess=1;
	    }
	    system("cls");
	}
    
    Score();
    
    if(score1>score2)
    {
    	cout<<endl;
    	cout<<"玩家1:"<<score1<<"	玩家2:"<<score2 <<endl; 
    	cout<<"玩家1獲勝"<<endl; 
    }
    else if(score1<score2)
    {
    	cout<<endl;
    	cout<<"玩家1:"<<score1<<"	玩家2:"<<score2 <<endl; 
    	cout<<"玩家2獲勝"<<endl; 
    }
    else
    {
    	cout<<endl;
    	cout<<"玩家1:"<<score1<<"	玩家2:"<<score2 <<endl; 
    	cout<<"和局"<<endl;
    }
     
   
    return 0;
}

void printTable()
{
	cout<<"     ";
    
    for(int I=1;I<=size;I++)
    {
        cout<<(char)(row+I)<<"   ";
    }
    
    cout<<endl;
    
    for(int I=1;I<=size;I++)
    {
        if(I<10)
        {
            cout<<column+I<<"    ";
        }
        else
        {
            cout<<column+I<<"   ";
        }
        for(int J=1;J<=size;J++)
        {
            cout<<table[J][I]<<"   ";
        }
        cout<<endl;
    }
} 

void Score()
{
		
	for(int I=1;I<=size;I++)
    {
        for(int J=1;J<=size;J++)
        {
            if(table[I][J]==1)
            {
            	score1++;
            }
            else if(table[I][J]==2)
            {
            	score2++;
            }
        }
    }
}


void canChess()
{
	check=0;
	change=0;
    for(tableR=1;tableR <= size;tableR++)
    {
        for(tableC=1;tableC <= size;tableC++)
        {
        	if(table[tableR][tableC]==0)
        	{
            	checkTable();
        	}
        }
    }
	if(change!=1)
	{
		if(chess==1)
	    {
		    chess=2;
		}
	    else
	    {
	    	chess=1;
	    }
	}
	
	
}




void checkTable()
{
	for(int Z=0;Z<8;Z++)
	{
		switch(Z)
		{
			case 0: 
				if(table[tableR-1][tableC-1]==chess || table[tableR-1][tableC-1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR-I][tableC-I]==0 || table[tableR-I][tableC-I]== NULL )
					{
						break;
					}
					else if(table[tableR-I][tableC-I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
				
			case 1:
				if(table[tableR-1][tableC]==chess || table[tableR-1][tableC]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR-I][tableC]==0 || table[tableR-I][tableC]== NULL)
					{
						break;
					}
					else if(table[tableR-I][tableC]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 2:
				if(table[tableR-1][tableC+1]==chess || table[tableR-1][tableC+1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR-I][tableC+I]==0 || table[tableR-I][tableC+I]== NULL)
					{
						break;
					}
					else if(table[tableR-I][tableC+I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 3:
				if(table[tableR][tableC+1]==chess || table[tableR][tableC+1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR][tableC+I]==0 || table[tableR][tableC+I]== NULL)
					{
						break;
					}
					else if(table[tableR][tableC+I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 4:
				if(table[tableR+1][tableC+1]==chess || table[tableR+1][tableC+1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR+I][tableC+I]==0 || table[tableR+I][tableC+I]== NULL)
					{
						break;
					}
					else if(table[tableR+I][tableC+I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 5:
				if(table[tableR+1][tableC]==chess || table[tableR+1][tableC]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR+I][tableC]==0 || table[tableR+I][tableC]== NULL)
					{
						break;
					}
					else if(table[tableR+I][tableC]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 6:
				if(table[tableR+1][tableC-1]==chess || table[tableR+1][tableC-1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR+I][tableC-I]==0 || table[tableR+I][tableC-I]== NULL)
					{
						break;
					}
					else if(table[tableR+I][tableC-I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
			case 7:
				if(table[tableR][tableC-1]==chess || table[tableR][tableC-1]==0)
				{
					break;
				}
				for(int I=2;I<=size;I++)
				{
					if(table[tableR][tableC-I]==0 || table[tableR][tableC-I]== NULL)
					{
						break;
					}
					else if(table[tableR][tableC-I]==chess)
					{
						change=1;
						if(check==1)
						{
							changeTable(Z);
						}
						break;
					}
					
				}
				break;
		}
	}

}


void changeTable(int Z)
{
	switch(Z)
	{
		case 0:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC-I]==chess)
				{
					break;
				}
				table[tableR-I][tableC-I]=chess;
			}
			break;
		case 1:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC]==chess)
				{
					break;
				}
				table[tableR-I][tableC]=chess;
			}
			break;
		case 2:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC+I]==chess)
				{
					break;
				}
				table[tableR-I][tableC+I]=chess;
			}
			break;
		case 3:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR][tableC+I]==chess)
				{
					break;
				}
				table[tableR][tableC+I]=chess;
			}
			break;
		case 4:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC+I]==chess)
				{
					break;
				}
				table[tableR+I][tableC+I]=chess;
			}
			break;
		case 5:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC]==chess)
				{
					break;
				}
				table[tableR+I][tableC]=chess;
			}
			break;
		case 6:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC-I]==chess)
				{
					break;
				}
				table[tableR+I][tableC-I]=chess;
			}
			break;
		case 7:
			for(int I=1;I<=size;I++)
			{
				if(table[tableR][tableC-I]==chess)
				{
					break;
				}
				table[tableR][tableC-I]=chess;
			}
			break;
	}
}








