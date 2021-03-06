#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/stat.h>

#define MONITFILE       "/tmp/monit.mp4"
#define MONITMAIL       "/tmp/mail.txt"

#define MONITPERIOD     600

unsigned long fsize(char* file)
{
    unsigned long len = 0;
    FILE * f = fopen(file, "r");
    if(f){
        fseek(f, 0, SEEK_END);
        len = (unsigned long)ftell(f);
        fclose(f);
    }
    return len;
}

void send_alert()
{
    char buf[1024];
    char buf2[1024];
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf (buf, "RTSP stream stop at %s", asctime(timeinfo));
    sprintf(buf2, "sendemail -f kaija.chang.co@gmail.com -t kaija.chang@gmail.com -u RTSP_ALERT -m \"%s\"", buf);
    //printf("%s", buf2);
    system(buf2);
}


int main(int argc, char **argv)
{
    char buf[1024];
    while(1)
    {
        remove(MONITFILE);
        printf("check RTSP server health\n");
        sprintf(buf, "ffmpeg  -rtsp_transport tcp  -i rtsp://182.92.76.200:80/v1/live?device_id=600018008 -map 0:v -vcodec copy -an -t 10 -y %s", MONITFILE);
        system(buf);
        unsigned long size = fsize(MONITFILE);
        printf("file size is %lu\n", size);
        if(size == 100000){
            printf("error stream stop\n");
            send_alert();
        }else{
            printf("stream is runing....\n");
        }
        sleep(MONITPERIOD);
    }
}
