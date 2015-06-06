//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <bits/stdc++.h>

using namespace std;

//General Methods
void GetData();
int BinarySearch();

//Indexing Mode Methods
void IndexingModeMenu();
void Indexing();
void IndexingFileInsert();
void IndexingFileSearch();
char* IndexingFileRecordSearch();
void UnpackBufferAndPrint();
void IndexingFileDelete();
void DeleteIndexingListIndex();
void IndexingFileUpdate();
void PrintOneRecord();
void IndexingFilePrint();
void IndexingFileOpenOut();
void IndexingFileOpenIn();

//Fixed Length Mode Methods
void FixedLengthModeMenu();
void FixedLengthFileInsert();
void FixedLengthFileSearch();
void FixedLengthFileUpdate();
void FixedLengthFileDelete();
void FixedLengthFilePrint();

struct Student
{
	char id[15];
	char name[50];
	char address[50];
};	Student s;

struct indexEntry
{
	char id[15];
	int offset;
}indexingList[100];

//Global Variabels
int indexingIndex = 0;

fstream indexingFile;

int main()
{
	system("COLOR 0F");
	int choice;
	string con;
	system("CLS");
menu: {
	cout << "\n\t\t\tFile Orgnization System.\n\n"
		<< "Please select one of the following:\n"
		<< "1- Indexing Mode File.\n"
		<< "2- Fixed Length Mode File.\n"
		<< "3- Close the program.\n\n"
		<< "please enter your choice   [1 - 3] ===> ";
	cin >> choice;
}
	switch (choice) {
	case 1: {
		IndexingModeMenu();
		system("COLOR 0F");
		break;
	}
	case 2: {
		FixedLengthModeMenu();
		system("COLOR 0F");
		break;
	}
	case 3: {
		cout << "\nthank you for using my program :)\n";
		return 0;
	}
	default: {
		cout << "please enter a value between 1 and 3\n";
	}
	}
	cout << "\ndo you want to continue in the Program?   [yes - no] ===> ";
	cin >> con;
	if (con == "Yes" || con == "yes" || con == "Y" || con == "y") {
		system("CLS");
		goto menu;
	}
	else {
		cout << "\nthank you for using my program :)\n";
		system("pause");
		return 0;
	}
}

//Genral Methods
void GetData(){
	cin.ignore();
	cout << "\nStudnt ID:        ";
	cin.getline(s.id, 15);
	cout << "Student Name:     ";
	cin.getline(s.name, 50);
	cout << "Student Address:  ";
	cin.getline(s.address, 50);
}

int BinarySearch(char target[]){
	int low = 0;
	int high = indexingIndex - 1;
	while (low <= high)
	{
		int middel = (low + high) / 2;
		if (atoi(indexingList[middel].id) == atoi(target))
		{
			return middel;
		}
		else if (atoi(indexingList[middel].id) < atoi(target))
		{
			high = middel - 1;
		}
		else if (atoi(indexingList[middel].id) > atoi(target))
		{
			low = middel + 1;
		}
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
//                          Indexing File Mode                                     //
/////////////////////////////////////////////////////////////////////////////////////

//Indexing Mode Methods
void IndexingModeMenu(){
	system("COLOR 3B");
	system("cls");
	int choice = 0;
	string con = "yes";

menu: {
	cout << "\n\t\t\tIndexing Mode File Orgnization\n\n"
		<< "Please select one of the following:\n"
		<< "1- Print the File On Screen.\n"
		<< "2- Add New Record.\n"
		<< "3- Update Record.\n"
		<< "4- Delete Record.\n"
		<< "5- Search For Record.\n"
		<< "6- Close the program.\n\n"
		<< "please enter your choice   [1 - 6] ===> ";
	cin >> choice;
}
	switch (choice) {
	case 1: {
		IndexingFilePrint();
		break;
	}
	case 2: {
		IndexingFileInsert();
		break;
	}
	case 3: {
		IndexingFileUpdate();
		break;
	}
	case 4: {
		IndexingFileDelete();
		break;
	}
	case 5: {
		IndexingFileSearch();
		break;
	}
	case 6: {
		cout << "\nthank you for using Indexing Mode File Orgnization :)\n";
		return;
	}
	default: {
		cout << "please enter a value between 1 and 6\n";
	}
	}
	cout << "\ndo you want to continue in Indexing Mode?   [yes - no] ===> ";
	cin >> con;
	if (con == "Yes" || con == "yes" || con == "Y" || con == "y") {
		system("CLS");
		goto menu;
	}
	else {
		cout << "\nthank you for using Indexing Mode File Orgnization :)\n";
		return;
	}
}

void IndexingFileOpenIn(){
	indexingFile.open("IndexingFile.txt", ios::app | ios::binary | ios::in);
}

void IndexingFileOpenOut(){
	indexingFile.open("IndexingFile.txt", ios::app | ios::binary | ios::out);
}

//Insert Record to indexingList
void Indexing(char id[15], int offset){
	strcpy(indexingList[indexingIndex].id, id);
	indexingList[indexingIndex].offset = offset;
	indexingIndex++;
}

//Insert Record to The file
void IndexingFileInsert(){
	IndexingFileOpenOut();
	char buffer[200];
	GetData();
	strcpy(buffer, s.id);
	strcat(buffer, "|");
	strcat(buffer, s.name);
	strcat(buffer, "|");
	strcat(buffer, s.address);
	strcat(buffer, "#");
	int bufferLength = strlen(buffer);
	indexingFile.seekp(0, ios::end);
	int address = indexingFile.tellp();
	indexingFile.write((char*)&bufferLength, sizeof(bufferLength));
	indexingFile.write(buffer, bufferLength);
	//indexing Record
	Indexing(s.id, address);
	indexingFile.close();
}

//Search For The Record and return buffer
char* IndexingFileRecordSearch(){
	IndexingFileOpenIn();
	char buffer[200], target[15];
	cout << "\nEnter Target ID For Search: ===> ";
	cin >> target;
	int targetIndex = BinarySearch(target);
	int offset = indexingList[targetIndex].offset;
	indexingFile.seekg(offset + 2, ios::beg);
	indexingFile.getline(buffer, sizeof(buffer), '#');
	return buffer;
	indexingFile.close();
}

// ReDesign The Buffer and print it
void UnpackBufferAndPrint(char buffer[]){
	istrstream strstreem(buffer);
	strstreem.getline(s.id, 15, '|');
	strstreem.getline(s.name, 15, '|');
	strstreem.getline(s.address, 50, '#');
	cout << "\n\nStudent ID:       " << s.id;
	cout << "\nStudent Name:     " << s.name;
	cout << "\nStudent Address:  " << s.address;
}

void realunpack(char * buffer)
{
	cout << strtok(buffer, "|") << " , ";
	cout << strtok(NULL, "|") << " , ";
	cout << strtok(NULL, "#") << " , ";
}

//Excute Search Method and print method
void IndexingFileSearch(){
	char buffer[200];
	strcpy(buffer, IndexingFileRecordSearch());
	UnpackBufferAndPrint(buffer);
}

//Delete Index from indexingList
void DeleteIndexingListIndex(int targetIndex){

	for (int i = targetIndex; i <= indexingIndex; i++)
	{
		indexingList[i] = indexingList[i + 1];
	}
	strcpy(indexingList[indexingIndex].id, "-1");
	indexingList[indexingIndex].offset = -1;
	indexingIndex--;
}

//Delet Record from indexingFile
void DeleteRecordIndexingFile(int offset){
	IndexingFileOpenOut();
	int head = -1;
	indexingFile.seekp(offset + 2, ios::beg);
	if (head == -1)
	{
		head = offset;
		indexingFile << '*';
		indexingFile << '|';
		indexingFile << -1;
	}
	else
	{
		indexingFile << '*';
		indexingFile << '|';
		indexingFile << head;
		head = offset;
	}
	indexingFile.close();
}

//Delet From File AND Avail List also
void IndexingFileDelete(){
	char target[15];
	cout << "\nEnter Target ID to Delete: ===> ";
	cin >> target;
	int targetIndex = BinarySearch(target);
	int offset = indexingList[targetIndex].offset;
	//Delete Index
	DeleteIndexingListIndex(targetIndex);
	//Delete Record From File
	DeleteRecordIndexingFile(offset);
}

//Excute Search Method then Delete Record then Insert new Record
void IndexingFileUpdate(){
	IndexingFileSearch();
	IndexingFileDelete();
	cout << "\n\nEnter New Data\n\n";
	IndexingFileInsert();
}

void IndexingFilePrint(){
	fstream indexingFile;
	Student s;
	char temp[200];
	char delim = '|';
	unsigned char length;

	indexingFile.open("IndexingFile.txt", ios::in | ios::binary);

	if (indexingFile.fail()){
		cout << "Error opening file\n";
		system("PAUSE");
		exit(1);
	}

	while (!indexingFile.eof()){

		indexingFile.read((char *)&length, 1);
		if (indexingFile.eof()) break;

		indexingFile.getline(temp, length, delim);
		strcpy(s.id, temp);

		indexingFile.getline(temp, length, delim);
		strcpy(s.name, temp);

		indexingFile.getline(temp, length, '#');
		strcpy(s.address, temp);
		indexingFile.read(temp, 1);

		cout << s.id
			<< " " << s.name
			<< " " << s.address
			<< endl;
	}
	indexingFile.close();
}

/////////////////////////////////////////////////////////////////////////////////////
//                      Fixed Lingth File Mode                                     //
/////////////////////////////////////////////////////////////////////////////////////

void FixedLengthModeMenu(){
	system("COLOR 1F");
	system("CLS");
	int choice = 0;
	string con = "yes";

menu: {
	cout << "\n\t\t\tFixed Length Mode File Orgnization.\n\n"
		<< "Please select one of the following:\n"
		<< "1- Print the File On Screen.\n"
		<< "2- Add New Record.\n"
		<< "3- Update The File.\n"
		<< "4- Delete Record From The File.\n"
		<< "5- Search For Record.\n"
		<< "6- Close the program.\n\n"
		<< "please enter your choice   [1 - 6] ===> ";
	cin >> choice;
}
	switch (choice) {
	case 1: {
		FixedLengthFilePrint();
		break;
	}
	case 2: {
		FixedLengthFileInsert();
		break;
	}

	case 3: {
		FixedLengthFileUpdate();
		break;
	}
	case 4: {
		FixedLengthFileDelete();
		break;
	}
	case 5: {
		FixedLengthFileSearch();
		break;
	}
	case 6: {
		cout << "\nthank you for using my Fixed Length Mode File Orgnization :)\n";
		return;
	}
	default: {
		cout << "please enter a value between 1 and 6\n";
	}
	}
	cout << "do you want to continue in Fixed Length Mode?   [yes - no] ===> ";
	cin >> con;
	if (con == "Yes" || con == "yes" || con == "Y" || con == "y") {
		system("CLS");
		goto menu;
	}
	else {
		cout << "\nthank you for using my program :)\n";
		return;
	}
}

void FixedLengthFilePrint(){

	Student record;
	fstream fixedlengthFile("fixedlengthFile.txt", ios::in | ios::binary);
	fixedlengthFile.read((char *)&record, sizeof(record));
	while (!fixedlengthFile.eof())
	{
		cout << "\tStudent ID:       " << record.id << endl;
		cout << "\tStudent Name:     " << record.name << endl;
		cout << "\tStudent Address:  " << record.address << endl << endl;
		fixedlengthFile.read((char *)&record, sizeof(record));
	}
	fixedlengthFile.close();
}

void FixedLengthFileInsert(){
	fstream fixedlengthFile("fixedlengthFile.txt", ios::out | ios::app | ios::binary);
	Student record;
	cin.ignore();
	cout << "\n\nInsert Student ID:       ";
	cin.getline(record.id, 15);
	cout << "Insert Student name:     ";
	cin.getline(record.name, 50);
	cout << "Insert Student address:  ";
	cin.getline(record.address, 50);
	cout << endl;
	fixedlengthFile.write((char *)&record, sizeof(record));
	fixedlengthFile.close();
}

void FixedLengthFileUpdate(){
	int recNum;
	fstream fixedlengthFile("fixedlengthFile.txt", ios::in | ios::out | ios::binary);
	Student record;
	cout << "Enter Number of the Record you want to Update: ";
	cin >> recNum;
	fixedlengthFile.seekg((recNum-1) * sizeof(record), ios::beg);
	fixedlengthFile.read((char *)&record, sizeof(record));
	cout << "\n\n\tStudent ID:       " << record.id << endl;
	cout << "\tStudent Name:     " << record.name << endl;
	cout << "\tStudent Address:  " << record.address << endl << endl;
	cout << "Enter the new data:\n";
	cin.ignore();
	cout << "\n\tStudent ID:       ";
	cin.getline(record.id, 10);
	cout << "\tStudent Name:     ";
	cin.getline(record.name, 50);
	cout << "\tStudent Address:  ";
	cin.getline(record.address, 50);
	cout << endl;
	fixedlengthFile.seekp((recNum-1) * sizeof(record), ios::beg);
	fixedlengthFile.write((char *)&record, sizeof(record));
	fixedlengthFile.close();
}

void FixedLengthFileSearch(){
	int recNum;
	cout << "Enter The Number of the record to search for: ";
	cin >> recNum;
	fstream fixedlengthFile("fixedlengthFile.txt", ios::in | ios::out | ios::binary);
	Student record;
	fixedlengthFile.seekg((recNum-1) * sizeof(record), ios::beg);
	fixedlengthFile.read((char *)&record, sizeof(record));
	cout << "\n\n\tStudent ID:       " << record.id << endl;
	cout << "\tStudent Name:     " << record.name << endl;
	cout << "\tStudent Address:  " << record.address << endl << endl;
	fixedlengthFile.close();
}

void FixedLengthFileDelete(){
	int recNum;
	fstream fixedlengthFile("fixedlengthFile.txt", ios::in | ios::out | ios::binary);
	Student record;
	cout << "Enter Number of the Record you want to Delete: ";
	cin >> recNum;
	fixedlengthFile.seekg((recNum - 1) * sizeof(record), ios::beg);
	fixedlengthFile.read((char *)&record, sizeof(record));
	cout << "\n\n\tStudent ID:       " << record.id << endl;
	cout << "\tStudent Name:     " << record.name << endl;
	cout << "\tStudent Address:  " << record.address << endl << endl;
	cout << "Has Successfully Deleted\n";
	cin.ignore();
	strcpy(record.id, "*");
	strcpy(record.name, "Deleted");
	strcpy(record.address, "");
	cout << endl;
	fixedlengthFile.seekp((recNum - 1) * sizeof(record), ios::beg);
	fixedlengthFile.write((char *)&record, sizeof(record));
	fixedlengthFile.close();

}







/////////////////////////////////////////////////////////////////////////////////////
//                          END OF THE PROJECT                                     //
/////////////////////////////////////////////////////////////////////////////////////
