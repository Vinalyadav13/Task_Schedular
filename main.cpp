// Task Scheduler in C++ 


#include <iostream> 
#include <fstream> 
#include <vector> 
#include <iomanip> 
#include <ctime> 
#include <sstream> 
using namespace std;

struct Task { 
    string title; 
    string category; // Daily, Weekly, Monthly 
    string dueDate; // Format: YYYY-MM-DD 
    string description; 
};

vector<Task> tasks; const string FILENAME = "tasks.txt";

void loadTasks() { ifstream fin(FILENAME); 
    Task t; 
    while (getline(fin, t.title)) { 
        getline(fin, t.category); 
        getline(fin, t.dueDate); 
        getline(fin, t.description); 
        tasks.push_back(t); 
    } 
    fin.close(); 
}

    bool verifyPassword() {
    const string correctPassword = "iamgreat";  
    string input;
    cout << "\033[1;36mEnter Password to access Task Scheduler: \033[0m";
    cin >> input;
    if (input == correctPassword) {
        cout << "\033[1;32mAccess Granted \033[0m\n";
        return true;
    } else {
        cout << "\033[1;31mAccess Denied \033[0m\n";
        return false;
    }
}


void saveTasks() { 
    ofstream fout(FILENAME); 
    for (auto& t : tasks) { 
        fout << t.title << endl << t.category << endl << t.dueDate << endl << t.description << endl; 
    } 
    fout.close(); 
}

void printHeader(const string& title) { 
    cout << "\033[1;36m\n==== " << title << " ====" << "\033[0m\n"; 
}

void addTask() { 
    Task t; 
    cin.ignore(); 
    printHeader("Add New Task"); 
    cout << "Enter Title: "; 
    getline(cin, t.title); 
    cout << "Enter Category (Daily/Weekly/Monthly): "; 
    getline(cin, t.category); 
    cout << "Enter Due Date (YYYY-MM-DD): "; 
    getline(cin, t.dueDate); 
    cout << "Enter Description: "; 
    getline(cin, t.description); 
    tasks.push_back(t); saveTasks(); 
    cout << "\033[1;32mTask added successfully!\033[0m\n"; 
}

void viewTasks() { 
    printHeader("Your Tasks"); 
    if (tasks.empty()) { 
        cout << "\033[1;31mNo tasks available.\033[0m\n"; 
        return; 
    } 
    int index = 1; 
    for (const auto& t : tasks) { 
        cout << "\033[1;33m[" << index++ << "]\033[0m " << t.title << " (" << t.category << ", Due: " << t.dueDate << ")\n"; 
        cout << "   Description: " << t.description << "\n"; 
    }
 }

void deleteTask() { 
    viewTasks(); 
    printHeader("Delete Task"); 
    int index; cout << "Enter task number to delete: "; 
    cin >> index; 
    if (index < 1 || index > tasks.size()) { 
        cout << "\033[1;31mInvalid task number.\033[0m\n"; 
        return; } tasks.erase(tasks.begin() + index - 1); 
        saveTasks(); 
        cout << "\033[1;32mTask deleted successfully!\033[0m\n"; 
    }

string getTodayDate() { 
    time_t now = time(0); 
    tm *ltm = localtime(&now); 
    stringstream ss; 
    ss << 1900 + ltm->tm_year << "-" << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" << setw(2) << setfill('0') << ltm->tm_mday; 
    return ss.str(); 
}

void showReminders() { 
    printHeader("Today's Reminders"); 
    string today = getTodayDate(); 
    bool found = false; 
    for (const auto& t : tasks) { 
        if (t.dueDate == today) { 
            found = true; 
            cout << "\033[1;35m- " << t.title << " (" << t.category << ")\033[0m\n"; 
            cout << "  Description: " << t.description << "\n"; 
        } 
    } 
    if (!found) { 
        cout << "\033[1;32mNo tasks due today.\033[0m\n"; 
    } 
}

void showMenu() { 
    printHeader("Task Scheduler Menu"); 
    cout << "\033[1;34m1. Add Task\n2. View Tasks\n3. Delete Task\n4. Show Today's Reminders\n5. Exit\033[0m\n"; 
    cout << "Choose an option: "; 
}

int main() {
    if (!verifyPassword()) {
        return 0;  // exit if wrong password
    }

    loadTasks();  // only load tasks if password is correct

    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: showReminders(); break;
            case 5: cout << "\033[1;35mExiting...\033[0m\n"; break;
            default: cout << "\033[1;31mInvalid choice.\033[0m\n";
        }
    } while (choice != 5);

    return 0;
}
