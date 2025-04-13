#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Task {
    std::string description;
    bool completed;

    Task(std::string desc, bool done = false) : description(desc), completed(done) {}
};

std::vector<Task> tasks;

void loadTasks(const std::string& filename) {
    std::ifstream inFile(filename);
    std::string line;
    while (getline(inFile, line)) {
        bool done = (line[0] == '1');
        tasks.emplace_back(line.substr(2), done);
    }
}

void saveTasks(const std::string& filename) {
    std::ofstream outFile(filename);
    for (const auto& task : tasks) {
        outFile << (task.completed ? "1" : "0") << " " << task.description << "\n";
    }
}

void showTasks() {
    std::cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". [" << (tasks[i].completed ? 'x' : ' ') << "] "
                  << tasks[i].description << "\n";
    }
}

void addTask() {
    std::string desc;
    std::cout << "Enter task description: ";
    std::getline(std::cin, desc);
    tasks.emplace_back(desc);
    std::cout << "Task added!\n";
}

void markTaskDone() {
    int idx;
    std::cout << "Enter task number to mark as done: ";
    std::cin >> idx;
    std::cin.ignore();
    if (idx >= 1 && idx <= tasks.size()) {
        tasks[idx - 1].completed = true;
        std::cout << "Task marked as done.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

void deleteTask() {
    int idx;
    std::cout << "Enter task number to delete: ";
    std::cin >> idx;
    std::cin.ignore();
    if (idx >= 1 && idx <= tasks.size()) {
        tasks.erase(tasks.begin() + idx - 1);
        std::cout << "Task deleted.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

int main() {
    const std::string filename = "tasks.txt";
    loadTasks(filename);

    while (true) {
        std::cout << "\n1. View tasks\n2. Add task\n3. Mark task done\n4. Delete task\n5. Save and exit\n";
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();  // clear newline

        switch (choice) {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: markTaskDone(); break;
            case 4: deleteTask(); break;
            case 5: 
                saveTasks(filename);
                std::cout << "Tasks saved. Goodbye!\n";
                return 0;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
}
