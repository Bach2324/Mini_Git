#include <iostream>
#include "miniGit.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

miniGit::miniGit()
{
    
}
miniGit::~miniGit()
{
    
}
doublyNode *miniGit::init()
{
    doublyNode *Dnode = new doublyNode;
    Dnode->commitNumber = 0;
    Dnode->head = nullptr;
    Dnode->previous = nullptr;
    Dnode->next = nullptr;
    fs::remove_all(".miniGit");
    fs::create_directory(".miniGit");
    head = Dnode;
    return Dnode;
}
bool miniGit::checkFile(string file)
{
    doublyNode *dcrawler = head;
    singlyNode *crawler = dcrawler->head;
   
    while (crawler != nullptr)
    {
        if (crawler->fileName == file)
        {
            return true;
        }
        crawler = crawler->next;
    }
    return false;
}
void miniGit::addFile(doublyNode *Dnode, string fileName)
{ 
    singlyNode *insert = new singlyNode;
    insert->fileName = fileName;
    insert->fileVersion = "00";
    insert->next = nullptr;
    if (Dnode->head == nullptr)
    {
        Dnode->head = insert;
    }
    else
    {
        singlyNode *crawler = Dnode->head;
        while (crawler->next != nullptr)
        {    
            crawler = crawler->next;
        }
        crawler->next = insert;
    }
    return;
}
void miniGit::removeFile(string file)
{
    doublyNode *main = head;
    singlyNode *curr = main->head, *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->fileName == file)
        {
            if (prev == nullptr)
            {
                main->head = curr->next;
                delete curr;
            }
            else
            {
                prev->next = curr->next;
                delete curr;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}
void miniGit::printDS()
{
    doublyNode *DLL = head;
    do{
        singlyNode *slltmp = DLL->head;
        cout <<"Commit number: "<<DLL->commitNumber<<endl;
        cout <<"Files: ";
        while(slltmp != nullptr)
        {
            cout << slltmp->fileName << "." << slltmp->fileVersion <<", ";
            slltmp = slltmp->next;
        }
    cout<<endl;
    DLL = DLL->next;
    }while(DLL != nullptr);
}

void miniGit::commit(){
//go to current commit DLL node
//Run through and for each file if it already exists (if it doesn't exist just add to .minigit) then check if changes have been made
//If changes have been made increment the version number THEN copy the file into the .minigit directory
//if it is unchanged do nothing
//Once you have done this for each file then:
//create a new DLL Node with incremented commit number and port the SLL from the previous node to this one.
doublyNode *DLL = head;
while(DLL->next != nullptr){
    DLL = DLL->next;
}
singlyNode *SLL = DLL->head;
while(SLL != nullptr){
//logic to check if file already exists
//logic to check if files are the exact same
string tmp = ".minigit/" + SLL->fileName + SLL->fileVersion;
fstream file;
file.open(tmp.c_str());
if(file.fail()){ //if file doesn't already exist in .minigit directory adds the file.
string copyLine = "cp " + SLL->fileName +" .minigit/" + SLL->fileName + SLL->fileVersion;
system(copyLine.c_str());
}
else{//if file does exist:
    file.close();
    file.open(tmp.c_str());
    
}

SLL = SLL->next; 
}
}