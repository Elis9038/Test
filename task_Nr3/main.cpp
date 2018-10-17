#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
using namespace std;


QFile file("marks.txt");
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


int main()
{

    if (!file.exists()){
        cout << "Can't find file \"marks.txt\"";
        return -1;
    }

     if(!file.open(QFile::ReadOnly | QFile::Text))  {
         cout << "Can't read file \"marks.txt\"";
         return -1;
     }


     readFromTextFile();


     cout << "\t\t\t";
     for (int i=0; i<marksPerStudent; i++) cout << dates[i] << " ";

     printStudentMarks();

     calculateAverage();
     printAverage();

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

        for (int j=0; j<marksPerStudent; j++) averageMark[i] += studentMark[j][i];

        averageMark[i] /= marksPerStudent;

    }

    cout << "\t\t\t";

}


void printAverage() {

    for (int i=0; i<marksPerStudent; i++) {

        cout << " " << averageMark[i] << "  ";

    }
    cout << "\n\n";

}



