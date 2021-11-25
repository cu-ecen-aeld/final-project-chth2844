/******************************************************************************
 * File: fps.c
 *****************************************************************************/

//References
//https://github.com/cu-ecen-aeld/final-project-adityavarshney100/blob/master/Test_code/FP_test_code/fp_test.c
//https://github.com/sparkfun/Fingerprint_Scanner-TTL

// Include files

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <unistd.h> 
//#include <string.h> 
//#include <fcntl.h>

#include <netinet/in.h> 

#include <arpa/inet.h>

#define MAX 80
#define PORT 9000
#define SA struct sockaddr


// Constants
#define MAX_FRAME_SIZE          12
#define UARTIO_OK              0
#define ERR_OPEN               -1
#define ERR_CLOSE              -2
#define ERR_READ               -3
#define ERR_WRITE              -4
#define ERR_DATA_MISMATCH      -5
#define MAX 			12
#define PORT 			9000
#define SA struct sockaddr


unsigned char OPEN[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01};
unsigned char CLOSE[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x01};	
unsigned char LED_ON[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x13, 0x01};
unsigned char LED_OFF[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x12, 0x01};
unsigned char ISPRESSFINGER2[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x26, 0x00, 0x27, 0x01};

unsigned char ISPRESSFINGER[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x26, 0x01};
unsigned char GETENROLLCOUNT[MAX_FRAME_SIZE]	= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x01};
unsigned char CAPTURE[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0x01};
unsigned char CAPTURE_BEST[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x61, 0x01};
unsigned char IDENTIFY_N[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x51, 0x01};

unsigned char CHECKENROLL[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x21, 0x01};
unsigned char ENROLLSTART[MAX_FRAME_SIZE] 	= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x22, 0x01};
unsigned char ENROLL1[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x23, 0x01};
unsigned char ENROLL2[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x24, 0x01};
unsigned char ENROLL3[MAX_FRAME_SIZE] 		= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x25, 0x01};

  unsigned char cResponse[MAX_FRAME_SIZE];
  char sDevice[] = "/dev/serial0";
  unsigned char bytes_read=0;
  unsigned char bytes_write=0;
  int hDevice=0;
char buff[MAX];
	

int error(char *sFormat, ...) {
  va_list args;

  // not in quiet mode?
  // output error
  printf("ERROR: ");

  va_start(args, sFormat);
  vprintf(sFormat, args);
  va_end(args);

  printf("\n");
  return -1;
}

// io_open
// Call to open device

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int io_open(char *sDevice,int nOpen) {
	// can open it?
	int hDevice=open(sDevice,nOpen);

	if(hDevice<0) {
		error("io failed to open %s",sDevice);
		return -1;
	}
	return hDevice;
}

// io_close
// Call to close device

int io_close(int hDevice) {
	// can close it?
	if(close(hDevice)<0) {
		error("io failed to close device");
		return -1;
	}
	return 0;
}

void usage() {
	printf("\nUsage:\n\n");
	printf("\nExample:\n");
	printf("uart-loopback /dev/ttyO2\n");
	printf("\n");
}


void CRC_value(unsigned char *data)
{
	uint16_t sum =0;
		
	for(int i=0;i<10;i++)
		sum+= data[i];

	data[10] = (sum & 0x00ff);
	data[11] = (sum & 0xff00)>>8;
}


int led_open()
{
	if ((bytes_write=write(hDevice,OPEN,sizeof(OPEN)))!=(sizeof(OPEN))) 
	{
    		io_close(hDevice);
    		error("io failed to write at %s. Bytes Written:%d",sDevice,bytes_write);
  	}
  	// read response
  	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);
  	if (bytes_read<MAX_FRAME_SIZE) 
	{
    		io_close(hDevice);
    		error("io failed to read from %s, bytes read: %d",sDevice, bytes_read);
  	}
}

int led_on_fingerprint()
{
	for (int i=0; i<MAX_FRAME_SIZE; i++) 
    		cResponse[i] = 0;

	bytes_write=write(hDevice,LED_ON,sizeof(LED_ON));
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);
	if(cResponse[8] == 0x30)
		return 0;
	else
		return -1;
}

int led_off_fingerprint()
{
	for (int i=0; i<MAX_FRAME_SIZE; i++) 
    		cResponse[i] = 0;

	bytes_write=write(hDevice,LED_OFF,sizeof(LED_OFF));
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);
	if(cResponse[8] == 0x30)
		return 0;
	else
		return -1;
}

int identify_fingerprint()
{
	for (int i=0; i<MAX_FRAME_SIZE; i++) 
    		cResponse[i] = 0;	

	//Capture fingerprint
	bytes_write=write(hDevice,CAPTURE,sizeof(CAPTURE));
	while(1)
	{
		bytes_read=read(hDevice, cResponse, 1);
		if(cResponse[0] == 0x55)
			break;
	}
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);

	//Identify fingerprint
	for (int i=0; i<MAX_FRAME_SIZE; i++)
    		cResponse[i] = 0;
	bytes_write=write(hDevice,IDENTIFY_N,sizeof(IDENTIFY_N));
	while(1)
	{
		bytes_read=read(hDevice, cResponse, 1);
		if(cResponse[0] == 0x55)
			break;
	}
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);

	if(cResponse[7] == 0x30)
	{
		if(cResponse[3] == 1)
                {
                   printf("Fingerprint ID: Chirayu\n");
                } 
		buff[0] = (char) cResponse[3];
		while(led_off_fingerprint() == -1);
		return 1;
	}
	buff[0] = (char) 0;
	while(led_off_fingerprint() == -1);
	return 0;
}

int is_Finger_pressed()
{
	for (int i=0; i<MAX_FRAME_SIZE; i++) 
    		cResponse[i] = 0;

        int pval=0;
	bytes_write=write(hDevice,ISPRESSFINGER,sizeof(ISPRESSFINGER));
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);
	//if(cResponse[8] == 0x30 && cResponse[7] == 0x00 && cResponse[6] == 0x00 && cResponse[5] == 0x00 && cResponse[4] == 0x00)
	//{	
		//return 1;
	//}
        pval+=cResponse[4];
        pval+=cResponse[5];
        pval+=cResponse[6];
        pval+=cResponse[7];
        if(pval==0) 
           return 1;
	return 0;
}

int get_fingerprint_count()
{
	uint32_t count = 0;
	for (int i=0; i<MAX_FRAME_SIZE; i++) 
    		cResponse[i] = 0;

	bytes_write=write(hDevice,GETENROLLCOUNT,sizeof(GETENROLLCOUNT));
	bytes_read=read(hDevice, cResponse, MAX_FRAME_SIZE);

	if(cResponse[8] == 0x30)
	{
		count += cResponse[4];
		count += (cResponse[5]>>8)&0x0000ff00;
		count += (cResponse[6]>>16)&0x00ff0000;
		count += (cResponse[7]>>24)&0xff000000;
		return count;
	}
	return 0;
}

void fingerprint()
{
	int function=0;
	printf("\n\n************** Fingerprint Sensor User Space Test Code ************************\n");
	printf("1. Press 1 to ID a fingerprint\n");
	printf("Enter number: ");
	scanf("%d", &function);
	printf("%d\n\n",function);


	if(function == 1)
	{
		led_on_fingerprint();
		printf("Press finger\n");
		while(1)
		{
			if(is_Finger_pressed())
			{
				printf("Finger is pressed\n");
				if(identify_fingerprint())
				{
					buff[1] =(char) 1;
					printf("Fingerprint Authorized\n");
				}
				else
				{
					buff[1] =(char) 0;
					printf("Fingerprint NOT Authorized\n");
				}
				break;
			}					
		}
	}
	else if(function == 2)//Enrollment count
	{
		led_on_fingerprint();
		printf("Number of Enrolled Fingerprints = %d \n",get_fingerprint_count());
		led_off_fingerprint();
	}
	else if(function == 3) //Blink test
	{
		for(int i =0;i<10;i++)
		{
			led_on_fingerprint();
			delay(10);
			led_off_fingerprint();
			delay(10);
		}
	}
	else
	{
		printf("Invalid Number\n");
	}
}

void func(int sockfd)
{

	for (int n=0;n<3;n++) 
	{
		write(sockfd,buff, sizeof(buff));
	}
}


void socket_conn()
{
	int sockfd;
	struct sockaddr_in servaddr;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	char ip_addr[20];
	printf("Enter IP address of the server:");
	scanf("%s",ip_addr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip_addr);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}

void IR_sensor()
{
	
}

int main(int argc, char **argv) 
{
  	hDevice=io_open(sDevice,O_RDWR | O_NOCTTY);
	if(hDevice<0) 
	{
    		return ERR_OPEN;
  	}
  
  // Set attributes
  	struct termios options;
	tcgetattr(hDevice, &options);
	options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	options.c_cflag &= ~(CSIZE | PARENB);
	options.c_cflag |= B9600 | CS8 | CREAD | CLOCAL;
	options.c_cc[VTIME] = 1;
	options.c_cc[VMIN] = 0;
	tcflush(hDevice, TCIOFLUSH);
	tcsetattr(hDevice, TCSANOW, &options);
  
	bzero(buff, sizeof(buff));
	led_open();
  	while(1)
  	{
		fingerprint();
		
	}
// close device
  io_close(hDevice);
  
	return 0;
}
