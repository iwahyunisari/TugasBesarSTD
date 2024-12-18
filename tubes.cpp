#include "tubes.h"
#include <iostream>
#include <cstring> // Untuk operasi string

using namespace std;

// Fungsi untuk menyalin string menggunakan loop manual
void copyString(char* dest, const char* src, int maxLength) {
    int i = 0;
    while (src[i] != '\0' && i < maxLength - 1) { // Sisakan 1 untuk null-terminator
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Tambahkan null-terminator
}

// Menyalin seluruh daftar pesan
adrMess copyList(adrMess head) {
    if (!head) return nullptr;

    // Buat node pertama
    Message* newHead = new Message;
    copyString(newHead->content, head->content, 10000);
    newHead->important = head->important;
    newHead->next = nullptr;

    // Salin node berikutnya
    Message* current = newHead;
    Message* original = head->next;

    while (original) {
        Message* newNode = new Message;
        copyString(newNode->content, original->content, 10000);
        newNode->important = original->important;
        newNode->next = nullptr;

        current->next = newNode;
        current = newNode;
        original = original->next;
    }

    return newHead;
}

// Menghapus seluruh daftar pesan
void deleteList(adrMess &head) {
    while (head) {
        Message* temp = head;
        head = head->next;
        temp = NIL;
    }
}

// Mendorong state ke stack
void pushStack(adrStack &stack, adrMess head) {
    adrStack newNode = new UndoRedoStack;
    newNode->state = copyList(head); // Salin daftar
    newNode->next = stack;
    stack = newNode;
}

// Menarik state dari stack
adrMess popStack(adrStack &stack) {
    if (!stack) return nullptr;

    adrStack temp = stack;
    adrMess state = stack->state;
    stack = stack->next;
    temp = nullptr;
    return state;
}

void undo(adrMess &head, adrStack &undoStack, adrStack &redoStack) {
    if (!undoStack) {
        cout << "Tidak ada aksi untuk di-undo." << endl;
        return;
    }
    pushStack(redoStack, head);
    deleteList(head);
    head = popStack(undoStack);
}

void redo(adrMess &head, adrStack &redoStack, adrStack &undoStack) {
    if (!redoStack) {
        cout << "Tidak ada aksi untuk di-redo." << endl;
        return;
    }
    pushStack(undoStack, head);
    deleteList(head);
    head = popStack(redoStack);
}

// Tambahkan pesan baru
void addMessage(adrMess &head, const char* message) {
    adrMess newMessage = new Message;
    copyString(newMessage->content, message, 10000);
    newMessage->important = false;
    newMessage->next = nullptr;

    if (!head) {
        head = newMessage;
    } else {
        adrMess temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newMessage;
    }
}

// Sisipkan pesan
void insertMessage(adrMess &head, int index, const char* message) {
    adrMess newMessage = new Message;
    copyString(newMessage->content, message, 10000);
    newMessage->important = false;

    if (index == 1) {
        newMessage->next = head;
        head = newMessage;
        return;
    }

    adrMess temp = head;
    for (int i = 1; i < index - 1 && temp; ++i) {
        temp = temp->next;
    }

    if (temp) {
        newMessage->next = temp->next;
        temp->next = newMessage;
    } else {
        newMessage = nullptr; // Jika index tidak valid
    }
}

// Hapus pesan
void deleteMessage(adrMess &head, int index) {
    if (!head) return;

    if (index == 1) {
        adrMess temp = head;
        head = head->next;
        temp = nullptr;
        return;
    }

    adrMess temp = head;
    for (int i = 1; i < index - 1 && temp; ++i) {
        temp = temp->next;
    }

    if (temp && temp->next) {
        adrMess toDelete = temp->next;
        temp->next = temp->next->next;
        toDelete = nullptr;
    }
}

void displayAllMessages(adrMess head) {
    adrMess temp = head;
    int index = 1;
    while (temp) {
        cout << "[" << index++ << "] " << temp->content << ". ";
        //if (temp->important) cout << " [PENTING]";
        temp = temp->next;
        //index++;
    }
}

void displayImportantMessages(adrMess head) {
    adrMess temp = head;
    bool found = false;
    while (temp) {
        if (temp->important) {
            cout << temp->content << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Tidak ada pesan penting." << endl;
}

// Tandai pesan sebagai penting
void markAsImportant(adrMess &head, int index) {
    adrMess temp = head;
    for (int i = 1; i < index && temp; ++i) {
        temp = temp->next;
    }
    if (temp) {
        temp->important = true;
    }
}

void deleteUndoRedoStack(adrStack &stack) {
    while (stack) {
        adrStack temp = stack;
        stack = stack->next;
        temp = NIL; // Hapus node stack
    }
}
