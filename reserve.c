#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a song
typedef struct Song {
    char title[100];
    char artist[100];
    char genre[50];
    struct Song* next;
    struct Song* prev;
} Song;

// Define a structure for the playlist
typedef struct Playlist {
    Song* head;
    Song* tail;
    Song* current;
} Playlist;

// Function to create a new song
Song* createSong(const char* title, const char* artist, const char* genre) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->genre, genre);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

// Initialize the playlist
void initializePlaylist(Playlist* playlist) {
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
}

// Add a song to the playlist
void addSong(Playlist* playlist, const char* title, const char* artist, const char* genre) {
    Song* newSong = createSong(title, artist, genre);
    if (playlist->head == NULL) {
        playlist->head = newSong;
        playlist->tail = newSong;
        playlist->current = newSong;
    } else {
        playlist->tail->next = newSong;
        newSong->prev = playlist->tail;
        playlist->tail = newSong;
    }
    printf("Song '%s' added to the playlist.\n", title);
}

// Play the next song
void playNext(Playlist* playlist) {
    if (playlist->current == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    if (playlist->current->next != NULL) {
        playlist->current = playlist->current->next;
        printf("Now playing: %s by %s.\n", playlist->current->title, playlist->current->artist);
    } else {
        printf("This is the last song in the playlist.\n");
    }
}

// Play the previous song
void playPrevious(Playlist* playlist) {
    if (playlist->current == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    if (playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;
        printf("Now playing: %s by %s.\n", playlist->current->title, playlist->current->artist);
    } else {
        printf("This is the first song in the playlist.\n");
    }
}

// Display songs by genre
void displayByGenre(Playlist* playlist, const char* genre) {
    if (playlist->head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    Song* temp = playlist->head;
    int found = 0;
    printf("Songs in the genre '%s':\n", genre);
    while (temp != NULL) {
        if (strcmp(temp->genre, genre) == 0) {
            printf("- %s by %s\n", temp->title, temp->artist);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No songs found in this genre.\n");
    }
}

// Display the entire playlist
void displayPlaylist(Playlist* playlist) {
    if (playlist->head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    Song* temp = playlist->head;
    printf("Playlist:\n");
    while (temp != NULL) {
        printf("- %s by %s (%s)\n", temp->title, temp->artist, temp->genre);
        temp = temp->next;
    }
}

// Main function
int main() {
    Playlist playlist;
    initializePlaylist(&playlist);

    int choice;
    char title[100], artist[100], genre[50];

    do {
        printf("\n--- Music Playlist System ---\n");
        printf("1. Add Song\n");
        printf("2. Play Next Song\n");
        printf("3. Play Previous Song\n");
        printf("4. Display Songs by Genre\n");
        printf("5. Display Entire Playlist\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]s", title);
                printf("Enter artist name: ");
                scanf(" %[^\n]s", artist);
                printf("Enter genre: ");
                scanf(" %[^\n]s", genre);
                addSong(&playlist, title, artist, genre);
                break;
            case 2:
                playNext(&playlist);
                break;
            case 3:
                playPrevious(&playlist);
                break;
            case 4:
                printf("Enter genre: ");
                scanf(" %[^\n]s", genre);
                displayByGenre(&playlist, genre);
                break;
            case 5:
                displayPlaylist(&playlist);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
