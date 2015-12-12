/*
** server.c -- a stream socket server demo
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <windows.h>
#include <signal.h>
#define PORT "3490" // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold
#define MAXDATASIZE 258

int sockfd, new_fd,numbytes; // listen on sock_fd, new connection on new_fd
char buf[MAXDATASIZE];
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr; // connector's address information
socklen_t sin_size;
struct sigaction sa;
int yes=1;
char s[INET6_ADDRSTRLEN];
int rv;


//>>>>>-----------------------遊戲---------------------------
//>>>>>-----------------------遊戲---------------------------
//>>>>>-----------------------遊戲---------------------------
//>>>>>-----------------------遊戲---------------------------
//>>>>>-----------------------遊戲---------------------------

    int table[17][17];
    char row=64;
    int column=0;
    int tableR,tableC;
    int	chess=1;
    int check;
    int change=0;
    int score1=2,score2=2;
    int I,J,Z,W;
    
    char sendTable[MAXDATASIZE];
    
    int size=6;

 
int mainGame() 
{
    for(W=0;W <=size*size-5 ;W++)
    {
        system("cls");
        
        
        printTable();

        score1=0;
        score2=0;
        check=0;

        canChess();

        Score();
        
        if(table[0][0]==1)
        {
            printf("你的對手認輸了\n");
            break;
        }

        if(chess==2)
        {
            if(score1-score2>=size*size/2-size)
            {
                printf("認輸嗎?	Y:1 N:0 \n");
                scanf(" %d",&check);
                if(check==1)
                {
                    table[0][0]=1;
                    tableTosendTable();
                    if (send(sockfd, sendTable, MAXDATASIZE, 0) == -1)
                            perror("send");
                    
                    sendTableToTable();
                    break;
                }
            }
        }
        else
        {
                if(score2-score1>=size*size/2-size)
            {
                printf("認輸嗎?	Y:1 N:0");
                scanf(" %d",&check);
                if(check==1)
                {
                    table[0][0]=1;
                    tableTosendTable();
                    if (send(sockfd, sendTable, MAXDATASIZE, 0) == -1)
                            perror("send");
                    
                    sendTableToTable();
                    break;
                }
            }
        }

        change==0;

        canChess();
        
        canChess();
        
        if(chess==2)
        {
            tableTosendTable();
            printf("你沒有地方可以下\n");
            if (send(sockfd, sendTable, MAXDATASIZE, 0) == -1)
                    perror("send");
            table[0][0]=2;
            sendTableToTable();
        }
        chess=1;

        if(table[0][0]!=2)
        {
            if(change!=1)
            {
                break;
            }
                printf("\n");
                printf("玩家1分數: %d\n",score1);
                printf("玩家2分數: %d\n\n",score2);
                printf("目前玩家:%d",chess); 
                if(chess==1)
                {
                    printf("  ◆\n");
                }
                else if(chess==2)
                {
                    printf("  ◇\n");
                }
            while(printf("輸入橫排%c~%c : 輸入直排1~%d :",(char)(row+1),(char)(row+size),size))
            {
                char inRow;
                int inColumn;
    //	        printf("輸入橫排%c~%c : 輸入直排1~%d :",(char)(row+1),(char)(row+size),size);
                scanf(" %c %d",&inRow,&inColumn);

                if((int)inRow <65 || (int)inRow>64+size || inColumn < 1 || inColumn>size)
                {
                    printf("輸入錯誤\n");
                }
                else
                {
                    check=1;
                    printf("輸入:%c%d 確認嗎? Y:1 N:0 ",inRow,inColumn);
                    scanf(" %d",&check);
                    if(check!=0)
                    { 
                        check=1;
                        change=0;
                        tableR=inRow-64;
                        tableC=inColumn;

                        if(table[tableR][tableC]!=0)
                        {
                            printf("此步無法下\n");
                        }
                        else
                        {
                            checkTable();
                            if(change!=1)
                            {
                               printf("此步無法下\n");
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

            tableTosendTable();
            printTable();
            if (send(new_fd, sendTable, MAXDATASIZE, 0) == -1)
                    perror("send");
            if ((numbytes = recv(new_fd, sendTable, MAXDATASIZE, 0)) == -1) {
                    perror("recv");
            }
            sendTableToTable();
        }
        table[0][0]=0;
    }
    
    return 0;
}


void sendTableToTable()
{
    table[0][0]=sendTable[0];
    for(I=1;I<=size;I++)
    {
        for(J=1 ;J<=size ;J++)
        {
            table[J][I]=sendTable[(I-1)*size+J];
        }
    }
}

void tableTosendTable()
{
    sendTable[0]=(char)table[0][0];
    for(I=1;I<=size;I++)
    {
        for(J=1 ;J<=size ;J++)
        {
            sendTable[(I-1)*size+J]=(char)table[J][I];
        }
    }
    
}

void printTable()
{
    printf("     ");
    
    for(I=1;I<=size;I++)
    {
        printf("%c  ",(char)(row+I));
    }
    
    printf("\n");
    
    for(I=1;I<=size;I++)
    {
        if(I<10)
        {
            printf("%d    ",column+I);
        }
        else
        {
            printf("%d   ",column+I);
        }
        for(J=1;J<=size;J++)
        {
            if(table[J][I]==1)
            {
                printf("◆  ");
            }
            else if(table[J][I]==2)
            {
                printf("◇  ");
            }
            else if(table[J][I]==0)
            {
                printf("◎  ");
            }
//            printf("%d   ",table[J][I]);
        }
        printf("\n");
    }
} 

void Score()
{
		
	for(I=1;I<=size;I++)
    {
        for(J=1;J<=size;J++)
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
	for(Z=0;Z<8;Z++)
	{
		switch(Z)
		{
			case 0: 
				if(table[tableR-1][tableC-1]==chess || table[tableR-1][tableC-1]==0)
				{
					break;
				}
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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
				for(I=2;I<=size;I++)
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

void changeTable(int A)
{
	switch(A)
	{
		case 0:
			for(I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC-I]==chess)
				{
					break;
				}
				table[tableR-I][tableC-I]=chess;
			}
			break;
		case 1:
			for(I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC]==chess)
				{
					break;
				}
				table[tableR-I][tableC]=chess;
			}
			break;
		case 2:
			for(I=1;I<=size;I++)
			{
				if(table[tableR-I][tableC+I]==chess)
				{
					break;
				}
				table[tableR-I][tableC+I]=chess;
			}
			break;
		case 3:
			for(I=1;I<=size;I++)
			{
				if(table[tableR][tableC+I]==chess)
				{
					break;
				}
				table[tableR][tableC+I]=chess;
			}
			break;
		case 4:
			for(I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC+I]==chess)
				{
					break;
				}
				table[tableR+I][tableC+I]=chess;
			}
			break;
		case 5:
			for(I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC]==chess)
				{
					break;
				}
				table[tableR+I][tableC]=chess;
			}
			break;
		case 6:
			for(I=1;I<=size;I++)
			{
				if(table[tableR+I][tableC-I]==chess)
				{
					break;
				}
				table[tableR+I][tableC-I]=chess;
			}
			break;
		case 7:
			for(I=1;I<=size;I++)
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



void PlayGame(){
    
    table[0][0]=0;
    for(I=1;I<=size;I++)
    {
        for(J=1;J<=size;J++)
        {
            table[I][J]=0;
        }
    }
    
    table[size/2][size/2]=1;
    table[size/2 + 1][size/2 + 1]=1;
    table[size/2 + 1][size/2]=2;
    table[size/2][size/2 + 1]=2;
    
    mainGame();
    
    Score();
    
    if(score1>score2)
    {
    	printf("\n");
    	printf("玩家1:%d    玩家2:%d\n",score1,score2); 
    	printf("玩家1獲勝\n"); 
    }
    else if(score1<score2)
    {
    	printf("\n");
    	printf("玩家1:%d    玩家2:%d\n",score1,score2); 
    	printf("玩家2獲勝\n"); 
    }
    else
    {
    	printf("\n");
    	printf("玩家1:%d    玩家2:%d\n",score1,score2); 
    	printf("和局\n");
    }
     

}//end of game




void sigchld_handler(int s)
{
while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
if (sa->sa_family == AF_INET) {
return &(((struct sockaddr_in*)sa)->sin_addr);
}
return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(void)
{
//    int sockfd, new_fd,numbytes; // listen on sock_fd, new connection on new_fd
//char buf[MAXDATASIZE];
//struct addrinfo hints, *servinfo, *p;
//struct sockaddr_storage their_addr; // connector's address information
//socklen_t sin_size;
//struct sigaction sa;
//int yes=1;
//char s[INET6_ADDRSTRLEN];
//int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
    }
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
        p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
        sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
            perror("server: bind");
            continue;
        }
    break;
    }
    
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }
    freeaddrinfo(servinfo); // all done with this structure
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }


    printf("server: waiting for connections...\n");
    while(1) { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s);
        printf("server: got connection from %s\n", s);
        
        if (!fork()) { // this is the child process
            
            PlayGame();
            
            
            close(sockfd); // child doesn't need the listener
          
            
            close(new_fd);
            exit(0);
            break;
        }
        close(new_fd); // parent doesn't need this
    }
    close(new_fd);
    return 0;
}
