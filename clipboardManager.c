#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

#define MAX_CLIPBOARD_SIZE 10

typedef struct {
    char *text;
} ClipboardItem;

typedef struct {
    int size;
    int current;
    ClipboardItem *head;
    ClipboardItem *items[MAX_CLIPBOARD_SIZE];
} ClipboardHistory;

void initClipboardHistory(ClipboardHistory *history) {
    history->size = 0;
    history->current = -1;
    history->head= NULL;
}

void clearClipboardHistory(ClipboardHistory *history) {
    for (int i = 0; i < history->size; i++) {
        free(history->items[i]->text);
        free(history->items[i]);
        history->items[i] = NULL;
    }
    history->size = 0;
}
void addToClipboardHistory(ClipboardHistory *history, const char *text) {
    if (history->size >= MAX_CLIPBOARD_SIZE) {
        // Clear the oldest clipboard item to make space for the new item
        free(history->items[MAX_CLIPBOARD_SIZE-1 ]->text);
        free(history->items[MAX_CLIPBOARD_SIZE-1 ]);
        for (int i = history->size-1 ; i > 0; i--) {
            history->items[i] = history->items[i];
        }
        history->size--;
    }

    ClipboardItem *newItem = (ClipboardItem *)malloc(sizeof(ClipboardItem));
    newItem->text = strdup(text);

    // Shift the existing items to the right to make space for the new item
    for (int i = history->size; i > 0; i--) {
        history->items[i] = history->items[i - 1];
    }

    // Add the new item to the beginning of the clipboard history
    history->items[0] = newItem;
    history->size++;
}

void printClipboardHistory(ClipboardHistory *history) {
    printf("__________________________________________________\n");
    printf("\t  ----------------------\n");
    printf("\t!!  Clipboard History:   !!\n");
    printf("\t  ----------------------\n");
    for (int i = 0; i < history->size; i++) {
        printf(">> %d: %s\n", i + 1, history->items[i]->text);
    }
    printf("__________________________________________________\n");
}
void saveClipboardHistoryToFile(ClipboardHistory *history) {
    char *filename="save.txt";
    FILE *file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < history->size; i++) {
            fprintf(file, "%s\n", history->items[i]->text);
        }
        fclose(file);
        printf("\nClipboard history saved to file.\n");
    } else {
        printf("Failed to save clipboard history to file.\n");
    }
}

void loadClipboardHistoryFromFile(ClipboardHistory *history) {
    FILE *file = fopen("save.txt", "r");
    if (file) {
        // Clear existing clipboard history before loading from file
        clearClipboardHistory(history);

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
            addToClipboardHistory(history, buffer);
        }
        fclose(file);
//        printf("Clipboard history loaded from file.\n");
    } else {
        printf("Clipboard history file not found. Starting with an empty clipboard history.\n");
    }
}
ClipboardItem* getClipboardItem(ClipboardHistory *history, int index) {
    if (index >= 1 && index <= history->size) {
        return history->items[index - 1];
    }
    return NULL; // Invalid index or history is empty
}

int getIntegerInput() {
    int option;
    while (1) {
        printf("\tEnter option: ");
        if (scanf("%d", &option) == 1) {
            // Input is a valid integer
            while (getchar() != '\n'); // Clear the input buffer
            return option;
        } else {
            // Input is not an integer, clear the input buffer and ask again
            while (getchar() != '\n');
            printf("\n>>> Invalid input. Please enter a valid integer.<<<\n\n");
        }
    }
}
void clearConsole() {
    #ifdef _WIN32
        system("cls"); // Windows command to clear console
    #else
        system("clear"); // Linux command to clear console
    #endif
}

void copyClipboardItem(ClipboardHistory *history,int index) {
    ClipboardItem *item = getClipboardItem(history, index);
    const char* selectedText = item->text; // Replace this with the actual selected text

   #ifdef _WIN32
        // Code to copy text to Windows clipboard
        if (OpenClipboard(NULL)) {
            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(selectedText) + 1);
            if (hMem) {
                char *clipboardData = (char*)GlobalLock(hMem);
                strcpy(clipboardData, selectedText);
                GlobalUnlock(hMem);
                EmptyClipboard();
                SetClipboardData(CF_TEXT, hMem);
                CloseClipboard();
                printf("Text copied to system clipboard.\n");
            } else {
                printf("Failed to allocate memory for clipboard data.\n");
            }
        } else {
            printf("Failed to open the clipboard.\n");
        }
    #else
        // Code to copy text to Linux clipboard
        FILE *clipboard = popen("xclip -i -selection clipboard", "w");
        if (clipboard) {
            fprintf(clipboard, "%s", selectedText);
            fclose(clipboard);
            printf("Text copied to system clipboard.\n");
        } else {
            printf("Failed to access clipboard on Linux.\n");
        }
    #endif

}


int main() {
    ClipboardHistory history;
    initClipboardHistory(&history);
    loadClipboardHistoryFromFile(&history);
    int option;
    char answer;
    char buffer[1024];
    do {printf("\n___________________________________________________\n");
        printf("||\t                                           |\n");
        printf("||\t!!! Options: !!!                           |\n");
        printf("||\t  ------------                             |\n");
        printf("||\t                                           |\n");
        printf("||\t1. Add item to clipboard history.          |\n");
        printf("||\t2. Get clipboard history.                  |\n");
        printf("||\t3. Clear clipboard history.                |\n");
        printf("||\t4. Quit.                                   |\n");
        printf("||\t                                           |\n");
        printf("||_________________________________________________|\n\n");
        option=getIntegerInput();
        printf("\n");
        switch (option)
        {
        case 1:
            clearConsole();
            printf("\t** Enter clipboard items (Enter 'q' to exist adding): **\n\n");
            printf("\tEnter text to add to clipboard history:\n");
            while (1)
            {
                printf("> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character

                if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
                {
                    saveClipboardHistoryToFile(&history);
                    break; // Stop adding items if the user enters 'q' or 'Q'
                }

                addToClipboardHistory(&history, buffer);
            }
            break;
        case 2:
            clearConsole();
            printClipboardHistory(&history);
            if (history.size > 0)
            {
                printf("\nIf you want to retrieve the item enter 'y' else enter the any value : ");
                scanf("%c",&answer);
                if(answer=='y' || answer=='Y')
                {
                    printf("\nEnter the index of the clipboard item you want to retrieve (1 to %d): \n\n", history.size);
                    int index = getIntegerInput();
                    ClipboardItem *item = getClipboardItem(&history, index);
                    if (item)
                    {
                        printf("\nClipboard item %d: >>  %s\n\n", index, item->text);
                        copyClipboardItem(&history, index);
                    }
                    else
                    {
                        printf("\nInvalid index or clipboard history is empty.\n");
                    }
                }
            }
            break;
        case 3:
            clearConsole();
            clearClipboardHistory(&history);
            printf("Clipboard history cleared.\n");
            break;
        case 4:
            break;
        default:
            clearConsole();
            printf(">>  Invalid option. Please try again. <<\n");
            break;
        }
    } while (option != 4);

    clearClipboardHistory(&history);

    return 0;
}
