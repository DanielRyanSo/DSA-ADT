#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 32

typedef char String[30];

typedef struct{
    String songName;
    String singer;
    String genre;
} Song;

typedef struct{
    Song elem;
    int next;
} Heapspace;

typedef struct{
    Heapspace H[MAX];
    int avail;
} VirtualHeap;

String genreTable[16] = {
    "Ballad", "Pop Rock", "Pop", "R&B", "Rock", "Country Pop", "J-Pop", "K-Pop",
    "Classical", "Theater", "EDM", "OPM", "Reggae", "Dance", "Jazz", "Indie"
};

int hash(String genre){
    for(int i = 0; i < 16; i++){
        if(strcmp(genreTable[i], genre) == 0) return i;
    }
    return 0;
}

void initDict(VirtualHeap *VH){
    int i, Lim, Half;
    Lim = MAX - 1;
    Half = MAX / 2;
    for(i = 0; i < Half; i++){
        strcpy(VH->H[i].elem.genre, "Empty");
        VH->H[i].elem.songName[0] = '\0';
        VH->H[i].elem.singer[0] = '\0';
        VH->H[i].next = -1;
    }
    for(; i < Lim; i++){
        VH->H[i].next = i + 1;
    }
    VH->H[i].next = -1;
    VH->avail = MAX / 2;
}

int search(VirtualHeap VH, Song song){
    int idx = hash(song.genre);
    int trav = idx;
    if(strcmp(VH.H[trav].elem.genre, "Empty") == 0) return 0;
    while(trav != -1){
        if(strcmp(VH.H[trav].elem.songName, song.songName) == 0 &&
           strcmp(VH.H[trav].elem.singer, song.singer) == 0 &&
           strcmp(VH.H[trav].elem.genre, song.genre) == 0){
            return 1;
        }
        trav = VH.H[trav].next;
    }
    return 0;
}

void insert(VirtualHeap *VH, Song song){
    int idx = hash(song.genre);
    if(strcmp(VH->H[idx].elem.genre, "Empty") == 0){
        VH->H[idx].elem = song;
        VH->H[idx].next = -1;
        return;
    }
    int newIdx = VH->avail;
    if(newIdx == -1) return;
    VH->avail = VH->H[newIdx].next;
    VH->H[newIdx].elem = song;
    VH->H[newIdx].next = -1;

    int trav = idx;
    while(VH->H[trav].next != -1){
        trav = VH->H[trav].next;
    }
    VH->H[trav].next = newIdx;
}

void deleteMember(VirtualHeap *VH, Song song){
    int idx = hash(song.genre);
    int trav = idx;
    int prev = -1;

    if(strcmp(VH->H[trav].elem.genre, "Empty") == 0) return;

    while(trav != -1 &&
          (strcmp(VH->H[trav].elem.songName, song.songName) != 0 ||
           strcmp(VH->H[trav].elem.singer, song.singer) != 0 ||
           strcmp(VH->H[trav].elem.genre, song.genre) != 0)){
        prev = trav;
        trav = VH->H[trav].next;
    }

    if(trav == -1) return;

    if(prev == -1){
        if(VH->H[trav].next == -1){
            strcpy(VH->H[trav].elem.genre, "Empty");
            VH->H[trav].elem.songName[0] = '\0';
            VH->H[trav].elem.singer[0] = '\0';
        }else{
            int nxt = VH->H[trav].next;
            VH->H[trav].elem = VH->H[nxt].elem;
            VH->H[trav].next = VH->H[nxt].next;

            VH->H[nxt].next = VH->avail;
            VH->avail = nxt;
        }
    }else{
        VH->H[prev].next = VH->H[trav].next;
        VH->H[trav].next = VH->avail;
        VH->avail = trav;
    }
}

void displayDict(VirtualHeap VH){
    int trav, cntr, LIM;
    LIM = MAX / 2;

    printf("Playlist of Janie Sabado");
    printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    printf("\n  %3s   %30s   %-15s   %-13s","Ndx","Song Name","Singer","Genre");
    printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    for(trav = 0; trav < LIM; trav++){
        if(strcmp(VH.H[trav].elem.genre,"Empty") == 0){
            printf("\n  %3d.  %30s - %-15s | %-13s",trav+1,"---","---","---");
        }else{
            printf("\n  %3d.  %30s - %-15s | %-13s",
                   trav+1,VH.H[trav].elem.songName,VH.H[trav].elem.singer,VH.H[trav].elem.genre);
            cntr = VH.H[trav].next;
            while(cntr != -1){
                printf("\n        %30s - %-15s | %-13s",
                       VH.H[cntr].elem.songName, VH.H[cntr].elem.singer, VH.H[cntr].elem.genre);
                cntr = VH.H[cntr].next;
            }
        }
        printf("\n\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    }
}

int main(){
    Song songBook[20]={ {"Someone Like You","Adele","Ballad"},
                        {"Yellow Submarine","Beatles","Pop Rock"},
                        {"Training Season","Dua Lipa","Pop"},
                        {"Let's go back","Jungle","Dance"},
                        {"Sway","Michael Buble","Jazz"},
                        {"Love Story","Taylor Swift","Country Pop"},
                        {"Where is my Husband?","Raye","Jazz"},
                        {"Fly me to the moon","Frank Sinatra","Jazz"},
                        {"Thinking Out Loud","Ed Sheeran","Ballad"},
                        {"Back on 74","Jungle","Dance"},
                        {"Mr. Brightside","The Killers","Pop Rock"},
                        {"Kirari","Fuji Kaze","J-Pop"},
                        {"This is What You Came For","Calvin Harris","Pop"},
                        {"Rock with you","SEVENTEEN","K-Pop"},
                        {"Symphony no. 8","Beethoven","Classical"},
                        {"Defying Gravity","Wicked","Theater"},
                        {"Alone","Marshmello","EDM"},
                        {"Buwan","Juan Karlos","OPM"},
                        {"NO PROBLEMZ","Jungle","Dance"},
                        {"Doo Wop'","Lauryn Hill","R&B"}};

    int trav;
    Song temp={"Fly me to the moon","Frank Sinatra","Jazz"};
    Song check={"Everynight","Jungle","Dance"};
    Song delFirst={"Training Season","Dua Lipa","Pop"};
    VirtualHeap VH;

    initDict(&VH);

    for(trav=0;trav<20;trav++){
        insert(&VH,songBook[trav]);
    }

    displayDict(VH);
    printf("\n");

    printf("\nThe song \"%s\" %s in my playlist",check.songName,(search(VH,check))?"exists":"does not exist");
    printf("\nThe song \"%s\" %s in my playlist",temp.songName,(search(VH,temp))?"exists":"does not exist");

    printf("\n\nDeleting song %s",temp.songName);
    deleteMember(&VH,temp);
    printf("\nDeleting song %s",delFirst.songName);
    deleteMember(&VH,delFirst);
    printf("\n\nInserting song %s",check.songName);
    insert(&VH,check);

    printf("\n");
    displayDict(VH);

    return 0;
}
