#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#define NIL NULL

typedef struct Message *adrMess;
struct Message {
    char content[100];
    bool important;
    adrMess next;
};

// Operasi pada pesan
void addMessage(adrMess &head, const char* message);
void insertMessage(adrMess &head, int index, const char* message);
void deleteMessage(adrMess &head, int index);
void displayAllMessages(adrMess head);
void displayImportantMessages(adrMess head);
void markAsImportant(adrMess &head, int index);

// Undo/Redo
typedef struct UndoRedoStack *adrStack;
struct UndoRedoStack {
    adrMess state;
    adrStack next;
};

void pushStack(adrStack &stack, adrMess head);
adrMess popStack(adrStack &stack);
void undo(adrMess &head, adrStack &undoStack, adrStack &redoStack);
void redo(adrMess &head, adrStack &redoStack, adrStack &undoStack);
void deleteUndoRedoStack(adrStack &stack);

// Utilitas
adrMess copyList(adrMess head);
void deleteList(adrMess &head);

#endif // TUBES_H_INCLUDED
