
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void speedtest();

int main(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("Running speedtest...\n");
	speedtest();
	FILE *temp;
	FILE *log;

	//printf("Locating log and temp files...\n");
	temp = fopen("temp.txt", "r");
	log = fopen("log.txt", "r");
	if(log == NULL){
		//printf("file does not exist, creating file...\n");
		log = fopen("log.txt", "a");
		fprintf(log, "ping download upload date\n");
	}
	else{
		//printf("file exists.\n");
		fclose(log);
		log = fopen("log.txt", "a");
	}
	
	if(temp == NULL){
		printf("speed test failed.\n");
		return -1;
	}

	//printf("Copying temp to log...\n");
	float ping, down, up;
	char date[100];
	//fgets(buf, sizeof buf, temp);
	//sscanf(buf, "%*s %f", &ping);
	fscanf(temp, "%*s %f %*s", &ping);
	fscanf(temp, "%*s %f %*s", &down);
	fscanf(temp, "%*s %f %*s", &up);
	sprintf(date, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	fprintf(log, "%.2f %.2f %.2f %s\n", ping, down, up, date);

	printf("Result: ");
	printf("%.2f %.2f %.2f %s\n", ping, down, up, date);
	fclose(temp);
	fclose(log);
	return 0;
}

void speedtest(){
	system("speedtest-cli --simple > temp.txt");
}


