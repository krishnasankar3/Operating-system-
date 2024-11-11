#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_KEY 1234  
#define MSG_SIZE 256  

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

   
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

  
    message.msg_type = 1;

   
    printf("Enter the message to send: ");
    fgets(message.msg_text, MSG_SIZE, stdin);
    
   
    message.msg_text[strcspn(message.msg_text, "\n")] = '\0';

   
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the queue: %s\n", message.msg_text);

    return 0;
}

