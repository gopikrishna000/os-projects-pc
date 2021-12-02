// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <string.h>
#include <cerrno>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


#define PORT 8080


using namespace std;

int createFile(char *directoryName){
    fstream file;
    file.open(directoryName,ios::out);       
    if(!file){
        cout << "Error Creating File.\n";
        return -1;
    } 
    cout << "File Successfully Created.\n";
    file.close();
    return 1;
}

int createDirectory(char *directoryName)
{
    if (mkdir(directoryName, 0777) == -1)
    {
        cout << "Error Creating Directory.\n";
        return -1;
    }
    cout << "Directory Successfully Created.\n";
    return 1;
}
 
int getCountOfChar(char *str, char c)
{
    if (str == NULL)
    return 0;
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == c)
        {
        count++;
        }
    }
    return count;
}

void readDirectory(char *name)
{
    DIR *directory = opendir(name);
    struct dirent *dstream;
    while ((dstream = readdir(directory)) != NULL)
    {
        int n = getCountOfChar(name, '/');
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1 || i < 0)
            {
            cout << " |-";
            }
            else
            {
            cout << " ";
        }
        }
        cout << dstream->d_name << "(" << (dstream->d_type == DT_DIR ? "dir" : "file") << ")"
        << '\n';
        if (dstream->d_type == DT_DIR && strcmp(dstream->d_name, ".") != 0 &&
        strcmp(dstream->d_name, "..") != 0)
        {
            char temp[1024];
            char *rootPath = strcat(strcat(strcpy(temp, name), "/"), dstream->d_name);
            readDirectory(rootPath);
        }
    }
    closedir(directory);
}

int createNonDeleteableDirectory(char *directoryName)
{
    if (mkdir(directoryName, 0000) == -1)
    {
        cout << "Error Creating Directory.\n";
        return -1;
    }
    cout << "Directory Successfully Created.\n";
    return 1;
}

int deleteDirectory(char *directoryName)
{
    if (remove(directoryName) == -1)
    {
         cout << "Error Deleting Directory!:no such directory exist.\n";
        return -1;
    }
    cout << "Directory Successfully Deleted.\n";
    return 1;
}


/* Read characters from 'fd' until a newline is encountered. If a newline
  character is not encountered in the first (n - 1) bytes, then the excess
  characters are discarded. The returned string placed in 'buf' is
  null-terminated and includes the newline character if it was read in the
  first (n - 1) bytes. The function return value is the number of bytes
  placed in buffer (which includes the newline character if encountered,
  but excludes the terminating null byte). */

ssize_t readLine(int fd, void *buffer, size_t n);


int main()
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
//	char *hello = "Hello from server";
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
    else{
         printf("Created server: \n");
    }
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    else{
        printf("attached port: \n");
    }

	address.sin_family = AF_INET;
	address.sin_addr.s_addr =  inet_addr((new string("192.168.177.26"))->c_str());  //INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
    if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{ 
		perror("accept");
		exit(EXIT_FAILURE);
	}

    printf("Connected to a client\n");

dup2(new_socket,STDOUT_FILENO);

char option;
char buf[100];
    char *directoryName;
    while (true)
    {
        cout<<"Choosed option: ";
        cout.flush();
        //cin >> option;

        readLine(new_socket,buf,100);
        cout<<buf[0]<<"\n";
          cout.flush();
        option = buf[0];
        if (option == '0')  
        break;
        cout<<"Directory name: ";
        cout.flush();
        readLine(new_socket,buf,100);
   //     cin.ignore();
    //    cin.getline(directoryName,100);
directoryName = buf;
cout<<directoryName<<"\n";
cout.flush();
        switch (option)
        {
            case '1':      
                createFile(directoryName);
                break; 
            case '2':             
                createDirectory(directoryName);
                break;
            case '3':
                readDirectory(directoryName);
                break;
            case '4':
                createNonDeleteableDirectory(directoryName);
                break;
            case '5':
                deleteDirectory(directoryName);
                break;
            default:
                cout << "Invalid Choice !!!"<<option<<"is choosen\n";
                break;
        }
    }







/*

	valread = read( new_socket , buffer, 1024);
	printf("%s\n",buffer );
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;

    */

}


/*


#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

int createDirectory(char *directoryName)
{
    if (mkdir(directoryName, 0777) == -1)
    {
        cout << "Error Creating Directory.\n";
        return -1;
    }
    cout << "Directory Successfully Created.\n";
    return 1;
}
 
int getCountOfChar(char *str, char c)
{
    if (str == NULL)
    return 0;
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == c)
        {
        count++;
        }
    }
    return count;
}

void readDirectory(char *name)
{
    DIR *directory = opendir(name);
    struct dirent *dstream;
    while ((dstream = readdir(directory)) != NULL)
    {
        int n = getCountOfChar(name, '/');
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1 || i < 0)
            {
            cout << " |-";
            }
            else
            {
            cout << " ";
        }
        }
        cout << dstream->d_name << "(" << (dstream->d_type == DT_DIR ? "dir" : "file") << ")"
        << '\n';
        if (dstream->d_type == DT_DIR && strcmp(dstream->d_name, ".") != 0 &&
        strcmp(dstream->d_name, "..") != 0)
        {
            char temp[1024];
            char *rootPath = strcat(strcat(strcpy(temp, name), "/"), dstream->d_name);
            readDirectory(rootPath);
        }
    }
    closedir(directory);
}

int createNonDeleteableDirectory(char *directoryName)
{
    if (mkdir(directoryName, 0000) == -1)
    {
        cout << "Error Creating Directory.\n";
        return -1;
    }
    cout << "Directory Successfully Created.\n";
    return 1;
}

int deleteDirectory(char *directoryName)
{
    if (rmdir(directoryName) == -1)
    {
         cout << "Error Deleting Directory:no such directory exist.\n";
        return -1;
    }
    cout << "Directory Successfully Deleted.\n";
    return 1;
}


int main(){

    cout << "0 - Exit , 1 - Create Directory, 2 - Read Files and Subdirectories, 3 - Create Non-deletable Directory, 4 - Delete Empty Directory\n";
    int option;
    char *directoryName;
    while (true)
    {
        cout<<"Choose option: ";
        cin >> option;
        if (option == 0)
        break;
        cout<<"Directory name: ";
        cin.ignore();
        cin.getline(directoryName,100);
        switch (option)
         {
            case 1:             
                createDirectory(directoryName);
                break;
            case 2:
                readDirectory(directoryName);
                break;
            case 3:
                createNonDeleteableDirectory(directoryName);
                break;
            case 4:
                deleteDirectory(directoryName);
                break;
            default:
                cout << "Try Again !!!";
                break;
        }
    }
    return 0;
}

*/

ssize_t readLine(int fd, void *buffer, size_t n)
{
    ssize_t numRead;                    /* # of bytes fetched by last read() */
    size_t totRead;                     /* Total bytes read so far */
    bool start=1;
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = (char*)buffer;                       /* No pointer arithmetic on "void *" */

    totRead = 0;
    for (;;) {
        numRead = read(fd, &ch, 1);

        if (numRead == -1) {
            if (errno == EINTR)         /* Interrupted --> restart read() */
                continue;
            else
                return -1;              /* Some other error */

        } else if (numRead == 0) {      /* EOF */
            if (totRead == 0)           /* No bytes read; return 0 */
                return 0;
            else                        /* Some bytes read; add '\0' */
                break;

        } else {                        /* 'numRead' must be 1 if we get here */
            if (totRead < n - 1) {      /* Discard  (n - 1) bytes */
            
            if (ch == '\n'){
                if(start)
                continue;
                else
                break;

            }

                start = 0;
                totRead++;
                *buf++ = ch;
            }
            else
             break;


            
        }
    }

    *buf = '\0';
    return totRead;
}