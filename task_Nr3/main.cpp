#include <QCoreApplication>
#include <iomanip>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <QDebug>
using namespace std;

QFile file("marks.txt");
QTextStream in(&file);
QString line;
QStringList obj;
const int marksPerStudent = 5;
const int numberOfStudents = 9;
int studentMark[numberOfStudents][marksPerStudent];
float averageMark[5];
string dates[5];
string studentNr[numberOfStudents];

void printStudentMarks();
void calculateAverage();
void printAverage();
void readFromTextFile();
void writeToTextFile();

int main()
{
    if (!file.exists()){
        cout << "Can't find file \"marks.txt\"";
        return -1;
    }
     if(!file.open(QFile::ReadWrite | QFile::Text))  {
         cout << "Can't read file \"marks.txt\"";
         return -1;
     }

     readFromTextFile();
     cout << "\t\t\t";
     for (int i=0; i<marksPerStudent; i++) cout << dates[i] << " ";
     printStudentMarks();
     calculateAverage();
     printAverage();
     writeToTextFile();

     return 0;
}

void readFromTextFile() {

    line = file.readLine();
    obj = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    for (int i=0; i<marksPerStudent; i++) {
        dates[i] = obj.at(i+1).toUtf8().constData();
    }

    for (int i=0; i<numberOfStudents; i++) {
        line = file.readLine();
        obj = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        studentNr[i] = obj.at(0).toUtf8().constData();
        for (int j=0; j<marksPerStudent; j++) {
            studentMark[i][j] = obj.at(j+1).toInt();
        }
    }
}

void printStudentMarks() {

    cout << endl;
    for (int i=0; i<numberOfStudents; i++) {
        cout << studentNr[i] << " student marks:  ";
        for (int j=0; j<marksPerStudent; j++) cout << studentMark[i][j] << "     ";
        cout << endl;
    }
}

void calculateAverage() {

    for (int i=0; i<marksPerStudent; i++) {
        for (int j=0; j<numberOfStudents; j++) averageMark[i] += studentMark[j][i];
        averageMark[i] /= numberOfStudents;
    }
    cout << "\t\t\t";
}

void printAverage() {
    cout << " ";
    for (int i=0; i<marksPerStudent; i++) {
        cout << fixed << setprecision(2) << averageMark[i] << "  ";
    }
    cout << "\n\n";
}

void writeToTextFile() {

    int numOfDates = sizeof(dates)/sizeof(*dates);
    in << "\r\n\r\n";
    for (int i=0; i<numOfDates; i++) {
        in << QString::fromStdString(dates[i]) << "  ";
    }
    in << "\r\n";
    for (int i=0; i<5; i++) {
        float f = floor(averageMark[i] * 100.0) / 100.0;
        in << " " << QString::number(f) << "  ";
    }

}



