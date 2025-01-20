#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // For rename and remove
#include <cstdlib> // For system
#include <dirent.h> // For directory navigation

using namespace std;

void listFiles(const string& path) {
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            cout << entry->d_name << endl;
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
}

void viewFile(const string& fileName) {
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << fileName << endl;
    }
}

void createDirectory(const string& dirName) {
    if (system(("mkdir " + dirName).c_str()) == 0) {
        cout << "Directory created: " << dirName << endl;
    } else {
        perror("mkdir");
    }
}

void copyFile(const string& src, const string& dest) {
    ifstream srcFile(src.c_str(), ios::binary);
    ofstream destFile(dest.c_str(), ios::binary);
    if (srcFile.is_open() && destFile.is_open()) {
        destFile << srcFile.rdbuf();
        srcFile.close();
        destFile.close();
        cout << "File copied from " << src << " to " << dest << endl;
    } else {
        cout << "Unable to copy file: " << src << " to " << dest << endl;
    }
}

void moveFile(const string& src, const string& dest) {
    if (rename(src.c_str(), dest.c_str()) == 0) {
        cout << "File moved from " << src << " to " << dest << endl;
    } else {
        perror("rename");
    }
}

int main() {
    string command, path, fileName, src, dest;

    while (true) {
        cout << "Enter a command \n1-list \n2-view\n3-create \n4-copy \n5-move \n6-exit \n";
        cin >> command;

        if (command =="1") {
            cout << "Enter directory path: ";
            cin >> path;
            listFiles(path);
        } else if (command == "2") {
            cout << "Enter file name: ";
            cin >> fileName;
            viewFile(fileName);
        } else if (command == "3") {
            cout << "Enter directory name: ";
            cin >> path;
            createDirectory(path);
        } else if (command == "4") {
            cout << "Enter source file name: ";
            cin >> src;
            cout << "Enter destination file name: ";
            cin >> dest;
            copyFile(src, dest);
        } else if (command == "5") {
            cout << "Enter source file name: ";
            cin >> src;
            cout << "Enter destination file name: ";
            cin >> dest;
            moveFile(src, dest);
        } else if (command == "6") {
            break;
        } else {
            cout << "Invalid command. Try again." << endl;
        }
    }

    return 0;
}



