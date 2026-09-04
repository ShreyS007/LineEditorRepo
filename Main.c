#include <stdio.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LEN 256

// Global document state
char document[MAX_LINES][MAX_LEN];
int line_count = 0;

// --- HELP MENU ---
void print_help() {
    printf("\n--- Available Commands ---\n");
    printf("DISPLAY                  - Show the entire document\n");
    printf("INSERT <line_num> <text> - Add a new line (e.g., INSERT 1 Hello World)\n");
    printf("DELETE <line_num>        - Remove a specific line (e.g., DELETE 2)\n");
    printf("SAVE <filename>          - Save to a text file (e.g., SAVE doc.txt)\n");
    printf("LOAD <filename>          - Load from a text file (e.g., LOAD doc.txt)\n");
    printf("DELETE_FILE <filename>   - Delete an actual text file from the disk\n");
    printf("SEARCH <phrase>          - Find lines containing a word or phrase\n");
    printf("REPLACE <old> <new>      - Replace a word across the entire document\n");
    printf("STATS                    - Show total line and word counts\n");
    printf("HELP                     - Show this list of commands again\n");
    printf("EXIT                     - Quit the editor\n");
    printf("--------------------------\n\n");
}

// --- CORE FEATURES ---
void display_document() {
    if (line_count == 0) {
        printf("Document is empty.\n");
        return;
    }
    for (int i = 0; i < line_count; i++) {
        printf("%d: %s", i + 1, document[i]);
    }
}

void insert_line(int line_num, const char *text) {
    if (line_count >= MAX_LINES) {
        printf("Error: Document full.\n");
        return;
    }
    if (line_num < 1 || line_num > line_count + 1) {
        printf("Error: Invalid line number.\n");
        return;
    }

    int idx = line_num - 1;
    for (int i = line_count; i > idx; i--) {
        strcpy(document[i], document[i - 1]);
    }
    
    strncpy(document[idx], text, MAX_LEN - 1);
    document[idx][MAX_LEN - 1] = '\0';
    line_count++;
}

void delete_line(int line_num) {
    if (line_num < 1 || line_num > line_count) {
        printf("Error: Invalid line number.\n");
        return;
    }

    int idx = line_num - 1;
    for (int i = idx; i < line_count - 1; i++) {
        strcpy(document[i], document[i + 1]);
    }
    line_count--;
}

void save_document(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not save file.\n");
        return;
    }
    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s", document[i]);
    }
    fclose(file);
    printf("Document saved to %s\n", filename);
}

void load_document(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }
    line_count = 0; 
    while (fgets(document[line_count], MAX_LEN, file) != NULL) {
        line_count++;
        if (line_count >= MAX_LINES) break;
    }
    fclose(file);
    printf("Document loaded from %s\n", filename);
}

// --- BONUS FEATURES ---
void search_word(const char *phrase) {
    int found = 0;
    for (int i = 0; i < line_count; i++) {
        if (strstr(document[i], phrase) != NULL) {
            printf("Found on Line %d: %s", i + 1, document[i]);
            found = 1;
        }
    }
    if (found == 0) {
        printf("Phrase '%s' not found.\n", phrase);
    }
}

void find_and_replace(const char *target, const char *replacement) {
    int target_len = strlen(target);
    int replacements_made = 0;

    for (int i = 0; i < line_count; i++) {
        char buffer[MAX_LEN] = {0};
        char *current_pos = document[i];
        char *match;
        
        while ((match = strstr(current_pos, target)) != NULL) {
            strncat(buffer, current_pos, match - current_pos);
            strcat(buffer, replacement);
            current_pos = match + target_len;
            replacements_made++;
        }
        strcat(buffer, current_pos);
        strcpy(document[i], buffer);
    }
    printf("Replaced %d occurrence(s) of '%s' with '%s'.\n", replacements_made, target, replacement);
}

void document_stats() {
    int word_count = 0;
    for (int i = 0; i < line_count; i++) {
        int in_word = 0;
        for (int j = 0; document[i][j] != '\0'; j++) {
            char c = document[i][j];
            if (c == ' ' || c == '\n' || c == '\t') {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                word_count++;
            }
        }
    }
    printf("--- Document Statistics ---\n");
    printf("Total Lines: %d\n", line_count);
    printf("Total Words: %d\n", word_count);
    printf("---------------------------\n");
}

// --- MAIN LOOP ---
int main() {
    char input[MAX_LEN + 50]; 
    char command[20];

    printf("Line Editor Started. Type HELP for a list of commands or EXIT to quit.\n");
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        // Extract just the command word first
        if (sscanf(input, "%19s", command) != 1) continue;

        if (strcmp(command, "EXIT") == 0) {
            break;
        } 
        else if (strcmp(command, "HELP") == 0) {
            print_help();
        }
        else if (strcmp(command, "DISPLAY") == 0) {
            display_document();
        } 
        else if (strcmp(command, "INSERT") == 0) {
            int line_num;
            char text[MAX_LEN];
            if (sscanf(input, "%*s %d %[^\n]", &line_num, text) >= 2) {
                strcat(text, "\n"); 
                insert_line(line_num, text);
            } else {
                printf("Usage: INSERT <line_number> <text>\n");
            }
        } 
        else if (strcmp(command, "DELETE") == 0) {
            int line_num;
            if (sscanf(input, "%*s %d", &line_num) == 1) {
                delete_line(line_num);
            } else {
                printf("Usage: DELETE <line_number>\n");
            }
        } 
        else if (strcmp(command, "SAVE") == 0) {
            char filename[MAX_LEN];
            if (sscanf(input, "%*s %[^\n]", filename) == 1) save_document(filename);
            else printf("Usage: SAVE <filename>\n");
        } 
        else if (strcmp(command, "LOAD") == 0) {
            char filename[MAX_LEN];
            if (sscanf(input, "%*s %[^\n]", filename) == 1) load_document(filename);
            else printf("Usage: LOAD <filename>\n");
        }
        else if (strcmp(command, "DELETE_FILE") == 0) {
            char filename[MAX_LEN];
            if (sscanf(input, "%*s %[^\n]", filename) == 1) {
                if (remove(filename) == 0) {
                    printf("File '%s' deleted successfully.\n", filename);
                } else {
                    printf("Error: Could not delete file '%s'. It may not exist or is locked.\n", filename);
                }
            } else {
                printf("Usage: DELETE_FILE <filename>\n");
            }
        }
        else if (strcmp(command, "SEARCH") == 0) {
            char phrase[MAX_LEN];
            if (sscanf(input, "%*s %[^\n]", phrase) == 1) search_word(phrase);
            else printf("Usage: SEARCH <phrase>\n");
        }
        else if (strcmp(command, "REPLACE") == 0) {
            char old_word[MAX_LEN], new_word[MAX_LEN];
            if (sscanf(input, "%*s %s %[^\n]", old_word, new_word) >= 2) {
                find_and_replace(old_word, new_word);
            } else {
                printf("Usage: REPLACE <old_word> <new_word>\n");
            }
        }
        else if (strcmp(command, "STATS") == 0) {
            document_stats();
        }
        else {
            printf("Error: Unknown command. Type HELP for a list of available commands.\n");
        }
    }
    
    printf("Exiting editor.\n");
    return 0;
}