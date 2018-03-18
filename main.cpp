#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct metadata{
    string some_information;
};

struct node{
    int inode_number;
    struct metadata information;
};
map<string,struct node> store;

int root_inode = 0;
int next_available_inode = 1;
unsigned long length = 0;

void generate_tokens(string path, vector<string> &tokens, string delimiter){
    size_t pos = 0;
    string token;
    while ((pos = path.find(delimiter)) != std::string::npos) {
        token = path.substr(0, pos);
        tokens.push_back(token);
        path.erase(0, pos + 1);
    }
    tokens.push_back(path);
}
void listing(string path){
    string original_path = path;
    vector<string> tokens;
    int i, current_inode = root_inode;
    string key;
    generate_tokens(path,tokens,"/");
    if (original_path != "/") {
        for (i = 1; i < tokens.size(); i++) {
            key = to_string(current_inode) + "-" + tokens[i];
            if (store.find(key) == store.end()) {
                cout << "Invalid Path" << endl;
                return;
            }
            current_inode = store[key].inode_number;
        }
        key = to_string(current_inode) + "-";
    }
    else
        key = "0-";
    length = key.length();

    map<string, struct node>::iterator it = store.lower_bound(key);
    while(it!=store.end()){
        if( ((it->first).length() >= length)  && (((it->first).substr(0,length)).compare(key) == 0)){
            cout<<(it->first).substr(length)<<endl;
        }
        ++it;
    }
}

void add_directory(string path){
    vector<string> tokens;
    string key;
    int i, current_inode = root_inode;
    generate_tokens(path,tokens,"/");
    for(i=1; i<tokens.size()-1;i++){
        key = to_string(current_inode) + "-" + tokens[i];
        if(store.find(key) == store.end()){
            cout<<"Invalid Path"<<endl;
            return;
        }
        current_inode = store[key].inode_number;
    }

    if(tokens.size() > 1) {
        key = to_string(current_inode) + "-" + tokens[tokens.size() - 1];
        if (store.find(key) !=store.end()){
            cout<<"Directory already exists"<<endl;
            return;
        }
        struct node meta_node;
        meta_node.inode_number = next_available_inode;
        meta_node.information.some_information = "I am a directory";
        store[key] = meta_node;
        next_available_inode++;
    }

}

void rename_directory(string input){
    if (input == "/"){
        return;
    }
    vector<string>tokens;
    generate_tokens(input,tokens," ");
    string path, new_directory_name;
    path = tokens[1];
    new_directory_name = tokens[2];
    tokens.clear();
    generate_tokens(path, tokens,"/");
    string key,modified_key;
    int i, current_inode = root_inode;

    for (i = 1; i < tokens.size(); i++) {
        key = to_string(current_inode) + "-" + tokens[i];
        modified_key = to_string(current_inode) + "-";
        if (store.find(key) == store.end()) {
            cout << "Invalid Path" << endl;
        }
        current_inode = store[key].inode_number;
    }
    if (store.find(modified_key + new_directory_name) !=store.end()){
        cout<<"New directory name already exists"<<endl;
        return;
    }
    store[modified_key + new_directory_name] = store[key];
    store.erase(key);
}

int main() {
    cout<<"Listing: ls aboslute_path"<<endl;
    cout<<"Add: mkdir absolute path"<<endl;
    cout<<"Rename: rename absolute_path new_directory_name"<<endl;
    cout<<"Exit: exit"<<endl;
    string input;
    while(true){
        getline(cin,input);

        if (input == "exit")
            return 0;
        if (input.length() >=5  && input.substr(0,5).compare("mkdir") == 0){
            add_directory(input.substr(6));
        }
        else if (input.length() >=2  && input.substr(0,2).compare("ls")== 0){
            listing(input.substr(3));
        }
        else if (input.length() >=6  && input.substr(0,6).compare("rename")== 0){
            rename_directory(input);
        }
    }
}