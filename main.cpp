#include <iostream>
#include "tubes.h"

using namespace std;

int main()
{
    adrMess head = nullptr;
    adrStack undoStack = nullptr;
    adrStack redoStack = nullptr;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambahkan pesan baru\n";
        cout << "2. Tampilkan semua pesan\n";
        cout << "3. Tandai pesan sebagai penting\n";
        cout << "4. Sisipkan pesan\n";
        cout << "5. Hapus pesan\n";
        cout << "6. Undo/Redo\n";
        cout << "7. Tampilkan pesan penting\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore(); // Menghilangkan newline dari buffer

        switch (choice) {
            case 1: {
                char newMessage[10000];
                cout << "Masukkan pesan baru: ";
                cin.getline(newMessage, 10000);

                // Simpan state sebelum melakukan perubahan
                pushStack(undoStack, head);

                // Kosongkan redo stack karena ini aksi baru
                deleteUndoRedoStack(redoStack);

                // Tambahkan pesan baru
                addMessage(head, newMessage);
                break;
            }
            case 2: {
                cout << "\nSemua Pesan:\n";
                displayAllMessages(head);
                break;
            }
            case 3: {
                int index;
                cout << "Masukkan nomor pesan yang ingin ditandai sebagai penting: ";
                cin >> index;

                // Simpan state sebelum melakukan perubahan
                pushStack(undoStack, head);

                // Kosongkan redo stack karena ini aksi baru
                deleteUndoRedoStack(redoStack);

                // Tandai pesan sebagai penting
                markAsImportant(head, index);
                break;
            }
            case 4: {
                int index;
                char newMessage[10000];
                cout << "Masukkan posisi penyisipan: ";
                cin >> index;
                cin.ignore(); // Menghilangkan newline dari buffer
                cout << "Masukkan pesan baru: ";
                cin.getline(newMessage, 10000);

                // Simpan state sebelum melakukan perubahan
                pushStack(undoStack, head);

                // Kosongkan redo stack karena ini aksi baru
                deleteUndoRedoStack(redoStack);

                // Sisipkan pesan
                insertMessage(head, index, newMessage);
                break;
            }
            case 5: {
                int index;
                cout << "Masukkan nomor pesan yang ingin dihapus: ";
                cin >> index;

                // Simpan state sebelum melakukan perubahan
                pushStack(undoStack, head);

                // Kosongkan redo stack karena ini aksi baru
                deleteUndoRedoStack(redoStack);

                // Hapus pesan
                deleteMessage(head, index);
                break;
            }
            case 6: {
                int action;
                cout << "Pilih aksi (1 = Undo, 2 = Redo): ";
                cin >> action;

                if (action == 1) {
                    undo(head, undoStack, redoStack);
                } else if (action == 2) {
                    redo(head, redoStack, undoStack);
                } else {
                    cout << "Aksi tidak valid.\n";
                }
                break;
            }
            case 7: {
                cout << "\nPesan Penting:\n";
                displayImportantMessages(head);
                break;
            }
            case 8: {
                cout << "Keluar dari program.\n";
                break;
            }
            default: {
                cout << "Pilihan tidak valid.\n";
                break;
            }
        }
    } while (choice != 8);

    // Hapus semua data saat keluar dari program
    deleteList(head);
    deleteUndoRedoStack(undoStack);
    deleteUndoRedoStack(redoStack);

    return 0;
}
