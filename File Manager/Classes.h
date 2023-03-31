#pragma once




// Item Class --> abstract class

class Item
{
	string _name = "";
	int _attributes = 0;
	int _size = 0;
public:
	virtual void Create(string newName) = 0;
	virtual void Print() = 0 {
		cout << "Name: " << _name << endl;
		cout << "Attributes: " << _attributes << endl;
		cout << "Size: " << _size << endl;
	};
	virtual void Rename(string newName) = 0;
	virtual void Delete() = 0;
	virtual void CalculateSize() = 0;
	int getAttributes() const { return _attributes; }
	int getSize() const { return _size; }
	string getName() const { return _name; }
	void setAttributes(int newAtrribute) { this->_attributes = newAtrribute; }
	void setName(string name) { this->_name = name; }
	void setSize(int newSize) { this->_size = newSize; }
	virtual ~Item() = 0 {};
};

// Predicats

bool sizeS(const Item* it1, const Item* it2) {
	return it1->getSize() < it2->getSize();
}
bool sizeN(const Item* it1, const Item* it2) {
	return it1->getName().substr(it1->getName().rfind("\\") + 1)[0] < it2->getName().substr(it2->getName().rfind("\\") + 1)[0];
}



class File:public Item
{
public:

	void Create(string newName) override{
		ofstream file(newName.c_str(),ios::app);
		if (!file) throw BadDirCreate();
		if (!file.is_open()) throw BadDirOpen();
		this->setName(newName);
		this->setAttributes(newName.size());
		this->CalculateSize();
		file.close();
	}
	void Print() override {
		 Item::Print();
		 cout << "Type: File" << endl;
	};
	void Rename(string newName) override {
		if (rename(getName().c_str(),newName.c_str()) != -1) {
			this->setAttributes(newName.size());
			this->setName(newName);
			return;
		}
		throw BadDirRename();
	};
	void Delete() override {
		if (remove(getName().c_str()) != -1) {
			setName("");
			setSize(0);
			setAttributes(0);
			return;
		}
		throw BadDirRemove();
	}
	void CalculateSize() override  {
		ifstream file(getName().c_str(), ios::binary);
		if (!file) throw BadDirCreate();
		if (!file.is_open()) throw BadDirOpen();
		file.seekg(0, ios::end);
		setSize(file.tellg());
		file.close();
	}
	void writetoFile(string text)  {
		 ofstream file(getName().c_str(), ios::out);
		 if (!file) throw BadDirCreate();
		 if (!file.is_open()) throw BadDirOpen();
		 file << text<<endl;
		 file.close();
		 CalculateSize();
	}
	void appendtoFile(string text) {
		 ofstream file(getName().c_str(), ios::app);
		 if (!file) throw BadDirCreate();
		 if (!file.is_open()) throw BadDirOpen();
		 file << text;
		 file.close();
		 CalculateSize();
	}
	void Read() {
		ifstream file(getName().c_str(), ios::in);
		if (!file) throw BadDirCreate();
		if (!file.is_open()) throw BadDirOpen();
		string data;
		while (!file.eof()) {
			getline(file, data);
			cout << data << endl;
		}
		file.close();
	}
};




class Folder:public Item
{
public:
	vector<Item*>folderItems;

	void Create(string newName) override {
		if (_mkdir(newName.c_str()) != -1) {
			this->setName(newName);
			this->setAttributes(newName.size());
			return;
		}
		throw BadDirCreate();
	}
	void Rename(string newName) override  {
		if (rename(getName().c_str(), newName.c_str()) != -1) {
			this->setName(newName);
			this->setAttributes(newName.size());
			return;
		}
		throw BadDirRename();
	}
	void Print() override  {
		Item::Print();
		cout << "Type: Folder" << endl;
		for (auto& i : folderItems)
		{
			cout << endl;
			i->Print();
		}
	}
	void Delete() override {
		if (_rmdir(getName().c_str()) != -1) {
			setName("");
			setAttributes(0);
			folderItems.clear();
			return;
		}
		throw BadDirRemove();
	}
	void CalculateSize() override {
		int total = 0;
		for (auto& i : folderItems)
		{
			total += i->getSize();
		}
		setSize(total);
	}
	int setItems(string location,bool isSubfolder=false) {
		_finddata_t file_info;
		intptr_t handle = _findfirst((location + "/*").c_str(), &file_info);

		if (handle == -1) {
			return handle;
		}

		this->folderItems.clear();
		
		do {
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0) {
				continue;
			}

			Item* i1;

			if (file_info.attrib & _A_SUBDIR) {
				i1 = new Folder();
			}
			else {
				i1 = new File();
			}

			string dataName = location + "\\" + string(file_info.name);
			i1->setName(dataName);
			i1->setAttributes(dataName.size());
			i1->CalculateSize();
			if (file_info.attrib & _A_SUBDIR) {
				dynamic_cast<Folder*>(i1)->setItems(dataName,true);
			}

			this->folderItems.push_back(i1);

		} while (_findnext(handle, &file_info) == 0);
		this->CalculateSize();
		if (isSubfolder) this->folderItems.clear();
		this->setName(location);
		this->setAttributes(location.size());
		_findclose(handle);
		return 0;
	}
	void sort_(bool isSize=true) {
		if(isSize) sort(folderItems.begin(), folderItems.end(), sizeS);
		else sort(folderItems.begin(), folderItems.end(), sizeN);
	}
	

	~Folder()
	{
		for (auto& i : folderItems){delete i;}
	}

};







class FileManager
{
	string currentRoot;
	Folder* currentFolder;
public:
	Folder* getCurrentFolder() { return currentFolder; }
	string getCurrentRoot() { return currentRoot; }
	FileManager() : currentFolder(new Folder()),currentRoot("C:\\Users\\Public\\Documents") {
		currentFolder->setItems(currentRoot);
	}
	void mkdir(string newName) {
		Folder* f = new Folder();
		try {
			f->Create(currentRoot + "\\" + newName);
		}
		catch (const exception& ex) { 
			cout << ex.what() << endl;
			return;
		}
		currentFolder->folderItems.push_back(f);
		currentFolder->setItems(currentRoot);
		delete f;

	}
	void rmdir(string deleteName) {
		deleteName = currentRoot + "\\" + deleteName;
		for (auto& i : currentFolder->folderItems)
		{
			if (i->getName() == deleteName) {
				try {
					i->Delete();
				}
				catch (const exception& ex) {
					cout << ex.what() << endl;
					return;
				}
				currentFolder->setItems(currentRoot);
				return;
			}
		}
		try { throw BadDirRemove(); }
		catch (const exception& ex) { cout << ex.what() << endl; }
	}
	void type_nul(string newName) {
		File* f = new File();
		try {
			f->Create(currentRoot + "\\" + newName);
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
			return;
		}
		currentFolder->folderItems.push_back(f);
		currentFolder->setItems(currentRoot);
		delete f;
	}
	void rename(string oldName,string newName) {
		newName = currentRoot + "\\" + newName;
		for (auto& i : currentFolder->folderItems)
		{
			if (i->getName() == currentRoot + "\\" + oldName) {
				try {
					i->Rename(newName);
				}
				catch (const exception& ex) {
					cout << ex.what() << endl;
					return;
				}
				currentFolder->setItems(currentRoot);
				return;
			}
		}
		try { throw BadDirRename(); }
		catch (const exception& ex) { cout << ex.what() << endl; }
	}
	void cd(string newCurrent) {
		try {
			if (currentFolder->setItems(currentRoot + "\\" + newCurrent) == 0) {
				currentRoot = currentRoot + "\\" + newCurrent;
			}
			else {
				cout << "Dir doesn't exist" << endl;
			}
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
		}
	}
	void dir_s() {
		currentFolder->Print();
	}
	void cd_backwards() {
		string tempCurrent = currentRoot.substr(0, currentRoot.rfind("\\"));
		try {
			if(currentFolder->setItems(tempCurrent)==0) currentRoot = tempCurrent;
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
		}
	}
	void move(string standerName, string moverName) {
		bool check1 = false;
		for (auto& i : currentFolder->folderItems) {if (i->getName() == currentRoot + "\\" + standerName) check1 = true;}
		if (!check1) {
			try { throw BadDirMove(); }
			catch (const exception& ex) { 
				cout << ex.what() << endl; 
				return;
			}
		};
		rename(moverName, standerName + "\\" + moverName);
	}
	void open(string file) {
		file = currentRoot + "\\" + file;
		ShellExecuteA(0, 0, file.c_str(), 0, 0, SW_SHOW);
	}
	void type(string fileName) {
		for (auto& i : currentFolder->folderItems)
		{
			if (i->getName() == currentRoot + "\\"+ fileName) {
				try {(dynamic_cast<File*>(i))->Read();}
				catch (const exception& ex) { cout << ex.what() << endl; }
			}
		}
		try { throw BadDirOpen(); }
		catch (const exception& ex) { cout << ex.what() << endl;}
	}
	void compare(string name1, string name2) {
		for (auto& i :currentFolder->folderItems)
		{
			if (i->getName() == currentRoot + "\\" + name1) {
				for (auto& j : currentFolder->folderItems)
				{
					if (j->getName() == currentRoot + "\\" + name2) {
						if (i->getSize() > j->getSize()) cout << name1 << " is larger in size" << endl;
						else if (i->getSize() < j->getSize()) cout << name2 << " is larger in size" << endl;
						else cout << "This files have the same size" << endl;
						return;
					}
				}
			}
		}
		try { throw BadDirOpen(); }
		catch (const exception& ex) { cout << ex.what() << endl; }
	}
	void write(string fileName) {
		for (auto& i : currentFolder->folderItems)
		{
			if (i->getName() == currentRoot + "\\" + fileName) {
				string text;
				cout << "Enter text:\n";
				getline(cin, text);
				try { (dynamic_cast<File*>(i))->writetoFile(text); }
				catch (const exception& ex) { cout << ex.what() << endl; }
			}
		}
		try { throw BadDirOpen(); }
		catch (const exception& ex) { cout << ex.what() << endl; }
	}
	void append(string fileName) {
		for (auto& i : currentFolder->folderItems)
		{
			if (i->getName() == currentRoot + "\\" + fileName) {
				cout << "Enter text:\n";
				string text;
				getline(cin, text);
				try { (dynamic_cast<File*>(i))->appendtoFile(text); }
				catch (const exception& ex) { cout << ex.what() << endl; }
			}
		}
		try { throw BadDirOpen(); }
		catch (const exception& ex) { cout << ex.what() << endl; }
	}
	void sortF(bool isSize=true) {
		currentFolder->sort_(isSize);
	}
	void help() {
		cout << "mkdir --> Creates a new folder" << endl;
		cout << "rmdir --> Deletes selected folder" << endl;
		cout << "cd --> Changes the current directory" << endl;
		cout << "cd.. --> Changes the current directory backwards" << endl;
		cout << "cd/ --> Changes the current directory to C:\\" << endl;
		cout << "dir --> Displays all content of directories" << endl;
		cout << "open --> Opens selected directory" << endl;
		cout << "type_nul --> Creates a new file" << endl;
		cout << "del/f --> Deletes selected file" << endl;
		cout << "move --> Moves selected directory" << endl;
		cout << "rename --> Renames selected directory" << endl;
		cout << "datetime --> Displays current date and time" << endl;
		cout << "type --> Displays the content of selected file" << endl;
		cout << "shutdown --> Allows proper local or remote shutdown of machine" << endl;
		cout << "compare --> Compares two directories by their size" << endl;
		cout << "write --> Writes text to the selected file" << endl;
		cout << "append --> Appends text to the selected file" << endl;
		cout << "cls --> Clears the terminal screen" << endl;
		cout << "color --> Changes the color of terminal" << endl;
		cout << "exit --> Closes the terminal" << endl;
	}

	~FileManager() {delete currentFolder;}

};













//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//class FileManager
//{
//	string current="C:\\Users\\Public\\Documents";
//	vector<string>folders; // all subfolders in current folder
//	vector<string>files; // all files in current folder
//public:
//
//	vector<string> getFolder() { return folders; }
//	vector<string> getFiles() { return files; }
//
//	// Show Methods
//
//	void showAllSubfolders()const {
//		for (auto& i : folders)
//		{
//			cout << i << endl;
//		}
//	}
//	
//	void showAllFiles()const {
//		for (auto& i : files)
//		{
//			cout << i << endl;
//		}
//	}
//
//	void dir_s()const {
//		cout << "Current Directory: " << current << endl;
//		cout << "\nSubfolders:\n" << endl;
//		showAllSubfolders();
//		cout << "\nFiles:\n" << endl;
//		showAllFiles();
//	}
//
//	// Create Methods
//
//
//	bool createFolder(string folderName) {
//		folderName = current + "\\" + folderName;
//		if (_mkdir(folderName.c_str()) != -1) {
//			folders.push_back(folderName);
//			cout << "Folder Created Succesfully" << endl;
//			return true;
//		}
//		return false;
//	}
//
//	bool createFile(string fileName, string extension) {
//		fileName = current + "\\" + fileName + "." + extension;
//		ofstream file(fileName.c_str(), ios::out);
//		if (!file) throw exception("File couldn't be created");
//		if (!file.is_open()) throw exception("File couldn't be opened");
//
//		files.push_back(fileName);
//
//		file.close();
//		return true;
//	}
//
//	// Delete Methods
//
//	bool deleteFolder(string folderName) {
//		folderName = current + "\\" + folderName;
//		if (_rmdir(folderName.c_str()) != -1) {
//			
//			if (removefromVector(folderName) != -1) {
//				cout << "File Deleted Succesfully" << endl;
//				return true;
//			}
//		}
//		else {
//			cout << "The system cannot find the file specified." << endl;
//			return false;
//		}
//	}
//
//	bool deleteFile(string fileName, string extension) {
//		fileName = current + "\\" + fileName + "." + extension;
//		if (remove(fileName.c_str()) == 0) {
//			if (removefromVector(fileName.c_str(), false) != -1) {
//				cout << "File Deleted Succesfully" << endl;
//				return true;
//			}
//			return false;
//		}
//		cout << "The system cannot find the file specified." << endl;
//		return false;
//	}
//
//
//
//
//	// Rename Methods
//
//	bool renameFolder(string oldFolderName,string newFolderName,bool isFolder=true) {
//		newFolderName = current + "\\" + newFolderName;
//		oldFolderName = current + "\\" + oldFolderName;
//		if (rename(oldFolderName.c_str(), newFolderName.c_str()) == 0) {
//			if (isFolder) {
//				for (auto i = folders.begin(); i != folders.end(); i++) {
//					if (oldFolderName == *i) {
//						*i = newFolderName;
//						cout << "Folder Renamed Succesfully" << endl;
//						return true;
//					};
//					saveSubfolders();
//				}
//			}
//			else {
//				for (auto i = files.begin(); i != files.end(); i++) {
//					if (oldFolderName == *i) {
//						*i = newFolderName;
//						cout << "File Renamed Succesfully" << endl;
//						return true;
//					};
//					saveFiles();
//				}
//			}
//			
//		}
//		cout << "The system cannot find the file specified." << endl;
//		return false;
//		
//	}
//
//	// Move Methods
//
//	bool moveFolder(string stander, string mover) {
//		if (renameFolder(mover, stander + "\\" + mover)) {
//			cout << "Folder Moved Succesfully" << endl;
//			return true;
//		}return false;
//	}
//	
//	bool moveFolder(string stander, string mover,string moverextension) {
//		if (renameFolder(mover + "." + moverextension, stander + "\\" + mover + "."+moverextension,false)) {
//			cout << "File Moved Succesfully" << endl;
//			return true;
//		}return false;
//	}
//
//
//
//	int removefromVector(string folderName,bool isFolder=true) {
//		if (isFolder) {
//			for (auto i = folders.begin(); i != folders.end(); i++) {
//				if (*i == folderName) {
//					folders.erase(i);
//					saveSubfolders();
//					return 1;
//				}
//			}
//		}
//		else {
//			for (auto i = files.begin(); i != files.end(); i++) {
//				if (*i == folderName) {
//					files.erase(i);
//					saveFiles();
//					return 1;
//				}
//			}
//		}
//		return -1;
//	}
//	
//
//	//
//
//
//	inline void openFolder(string folder) {
//		current = current + "\\" + folder;
//	}
//
//
//	
//
//	
//
//
//	// savers
//
//	void saveSubfolders() {
//		ofstream database("SubFolders.txt", ios::out);
//		for (auto& i : folders)
//		{
//			database << i << endl;
//		}
//		database.close();
//	}
//	
//	void saveFiles() {
//		ofstream database("Files.txt", ios::out);
//		for (auto& i : files)
//		{
//			database << i << endl;
//		}
//		database.close();
//	}
//
//
//
//
//
//	// open
//
//	void OpenDefaultAppFolder(string file) {
//		file = current + "\\" + file;
//		ShellExecuteA(0, 0, file.c_str(), 0, 0, SW_SHOW);
//	}
//	void OpenDefaultAppFile(string file,string extension) {
//		file = current + "\\" + file +"."+extension;
//		ShellExecuteA(0, 0, file.c_str(), 0, 0, SW_SHOW);
//	}
//
//
//
//
//
//
//	void show_folder() {
//		_finddata_t file_info;
//		intptr_t handle = _findfirst((current + "/*").c_str(), &file_info);
//
//		if (handle == -1) {
//			cerr << "Could not open folder: " << current << endl;
//			return;
//		}
//
//		do {
//			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0) {
//				continue;
//			}
//
//			cout << "Name: "<<file_info.name<<endl;
//			cout << "Attribute: "<<file_info.attrib<<endl;
//			cout << "Size: "<<file_info.size << endl;
//
//			if (file_info.attrib & _A_SUBDIR) {
//				cout << "Type : Subfolder";
//			}
//			else cout << "Type: File";
//
//			cout << "\n-------------------------------------------\n";
//		} while (_findnext(handle, &file_info) == 0);
//
//		_findclose(handle);
//	}
//
//
//
//
//
//
//};

/*void setItems(string newCurrent) {
		_finddata_t file_info;
		intptr_t handle = _findfirst((newCurrent + "/*").c_str(), &file_info);

		if (handle == -1) {
			cerr << "Could not open folder: " << newCurrent << endl;
			return;
		}
		currentFolder->folderItems.clear();
		currentRoot = newCurrent;
		currentFolder->setName(currentRoot);
		currentFolder->setAttributes(currentRoot.size());
		do {
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0) {
				continue;
			}

			Item* i1;
			if (file_info.attrib & _A_SUBDIR) {
				i1 = new Folder();
			}
			else {
				i1 = new File();
			}
			string dataName = currentRoot + "\\" + string(file_info.name);
			i1->setName(dataName);
			i1->setAttributes(dataName.size());
			i1->CalculateSize();
			if (file_info.attrib & _A_SUBDIR) {
				setItems(currentRoot+"\\");
			}
			currentFolder->folderItems.push_back(i1);

		} while (_findnext(handle, &file_info) == 0);
		currentFolder->CalculateSize();
		_findclose(handle);
	}*/

