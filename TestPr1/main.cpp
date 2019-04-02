//
//  main.cpp
//  TestPr1
//
//  Created by Apotsang Yangzom on 2/6/19.
//  Copyright © 2019 Apotsang Yangzom. All rights reserved.
//

#include <iostream>
using namespace std;

class SparseRow{
public:
    int row; // row number.
    int col; // column number.
    int value; //Integer values.
public:
    SparseRow(); //default constructor
    SparseRow(int v, int c, int k);
    void display(); //print row number, column number and the integer values.
    //other methods that are necessary such as get and set.
    void setCol(int j);
    void setRow(int i);
    void setValue(int a);
    int getCol();
    int getRow();
    int getValue();
};

SparseRow::SparseRow(){
    row = -1;
    col = -1;
    value= -1;
}
SparseRow:: SparseRow(int r, int c, int k) {
    row = r;
    col = c;
    value = k;
    
}
void SparseRow:: display(){
    cout<<row<<", "<<col <<", "<<value<<", "<<endl;
}
void SparseRow::setCol(int j) {
    col = j;
}
void SparseRow:: setRow (int j) {
    row = j;
}
void SparseRow::setValue(int a) {
    value = a;
}

int SparseRow::getCol(){
    return col;
}
int SparseRow::getRow(){
    return row;
}
int SparseRow::getValue(){
    return value;
}

class SparseMatrix{
protected:
    int noRows; // Number of rows of the original matrix
    int noCols;// Number of cols of the original matrix
    int commonValue; // read from input
    int noNonSparseValues;
    SparseRow* myMatrix; // Array
public:
    SparseMatrix ();
    SparseMatrix (int n, int m, int cv, int noNSV);
    SparseMatrix* Transpose(); // Matrix Transpose
    SparseMatrix* Multiply(SparseMatrix& M);
    SparseMatrix* Add (SparseMatrix& M);
    void display();
    void displayMatrix();
    int getValueAt(int r, int c);
    void setCol(int j);
    void setRow(int i);
    void setValue(int a);
    SparseRow* getMyMatrix();
    void setMyMatrix(int r, int c, int value, int location);
};

SparseMatrix:: SparseMatrix() {
    // to be finished
}
SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV)
{
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
}
SparseRow* SparseMatrix:: getMyMatrix(){
    return myMatrix;
}
void SparseMatrix::setMyMatrix(int r, int c, int value, int location){
    myMatrix[location].setRow(r);
    myMatrix[location].setCol(c);
    myMatrix[location].setValue(value);
}
void SparseMatrix:: display() {
    for (int i=0; i< this->noNonSparseValues; i++) {
        myMatrix[i].display();
    }
}
void SparseMatrix:: displayMatrix()
{
    for (int i = 0; i < noRows; i++)
    {
        for (int j=0; j < noCols; j++)
        {
            cout << getValueAt(i,j)<< " ";
        }
        cout <<endl;
    }
}
int SparseMatrix::getValueAt(int r, int c)
{
    for (int i=0; i<noNonSparseValues; i++)
    {
        if (myMatrix[i].getRow()==r && myMatrix[i].getCol() == c) {
            return myMatrix[i].getValue();
        }
    }
        return commonValue;
}



// Transpose, multiply and add

SparseMatrix* SparseMatrix:: Transpose(){
    
    SparseMatrix* SM = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues);
    for (int i =0; i < noNonSparseValues; i++) {
        SM->myMatrix[i].setRow(myMatrix[i].getCol());
        SM->myMatrix[i].setCol(myMatrix[i].getRow());
        SM->myMatrix[i].setValue(myMatrix[i].getValue());
    }
    return SM;
}
SparseMatrix* SparseMatrix:: Add(SparseMatrix& M) {
    SparseMatrix* temp = new SparseMatrix (noRows, noCols, commonValue, noNonSparseValues+M.noNonSparseValues);
    SparseMatrix* sm;
    int count =0;
    int i = 0;
    int j;
    int valueToAdd;
    bool found;
    int location = 0;
    int r =0;
    int c =0;
    bool* myArray = new bool [M.noNonSparseValues];
    for (int k=0; k < M.noNonSparseValues; k++) {
        myArray[k]=false;
    }
    while(i < noNonSparseValues) {
        j=0;
        found = false;
        //(*temp).myMatrix[(*temp).noNonSparseValues].row = myMatrix[i].row;
        //(*temp).myMatrix[(*temp).noNonSparseValues].col = myMatrix[i].col;
        valueToAdd = commonValue;
        while((j < M.noNonSparseValues) && (!found)) {
            if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) && (myMatrix[i].getCol() == M.myMatrix[j].getCol())) {
                found = true;
                valueToAdd = M.myMatrix[j].getValue();
                myArray[j] = true;
                count++;
                r = M.myMatrix[j].getRow();
                c= M.myMatrix[j].getCol();
            }
            else {
                j++;
                
            }
        }
        if (!found) {
            r = myMatrix[j].getRow();
            c= myMatrix[j].getCol();
        }
        int addition = myMatrix[i].getValue()+valueToAdd;
        if (addition != commonValue) {
            (*temp).setMyMatrix(r,c, addition, location);
            location ++;
        }
        
        else {
            count++;
        }
        
        i++;
    }
    for (int k=0; k<M.noNonSparseValues; k++) {
        if (!myArray[k]) {
            (*temp).myMatrix[location].setRow(myMatrix[k].getRow());
            (*temp).myMatrix[location].setCol(myMatrix[k].getCol());
            (*temp).myMatrix[location].setValue(myMatrix[k].getValue());
            location ++;
        }
    }
    int size;
    size = noNonSparseValues + M.noNonSparseValues - count;
    int index=0; //
    sm = new SparseMatrix(noRows, noCols, commonValue, size);
    for (int i=0; i < size; i++) {
        sm->setMyMatrix(temp->myMatrix[i].getRow(), temp->myMatrix[i].getCol(),
                        temp->myMatrix[i].getValue(), index);
        index ++;
        
    }
    delete [] myArray;
    return sm;
}

SparseMatrix* SparseMatrix:: Multiply(SparseMatrix& M){
    int index_1= 0;
    int index_2;
    int location = 0;
    int counter = 0; //tracker
    int r;
    int c;
     //counter
    
    int size =0;
    SparseMatrix* mul;
    SparseMatrix* transpose = M.Transpose();
    SparseMatrix* OneMatrix = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues+M.noNonSparseValues);
    SparseMatrix* TwoMatrix = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues+M.noNonSparseValues);
   
    while (index_1 < noNonSparseValues) {
        index_2=0;
        while(index_2 < transpose->noNonSparseValues) {
            if (this->myMatrix[index_1].getCol()==transpose->myMatrix[index_2].getCol()) {
                r = myMatrix[index_1].getRow();
                c = transpose->myMatrix[index_2].getRow();
                OneMatrix->setMyMatrix(r, c, myMatrix[index_1].getValue()*transpose->myMatrix[index_2].getValue(), location);
                location ++;
                counter ++;
            }
            index_2++;
        }
        index_1++;
    }
    
    int valueToAdd;
    int before=0;
    int count =0;
     int location2 = 0;
    
    while(before < OneMatrix->noNonSparseValues) {
        int after = before +1;
        int r = OneMatrix->myMatrix[before].getRow();
        int c = OneMatrix->myMatrix[before].getCol();
        int v = OneMatrix->myMatrix[before].getValue();
        valueToAdd = v;
        
        while(after < counter) {
            if (OneMatrix->myMatrix[after].getRow()==r && OneMatrix->myMatrix[after].getCol() ==c) {
                valueToAdd += OneMatrix->myMatrix[after].getValue();
                counter ++;
                OneMatrix->myMatrix[after].setValue(commonValue);
                
            }
            after ++;
            
        }
        if (valueToAdd != commonValue) {
            (*TwoMatrix).setMyMatrix(r, c, valueToAdd, location);
            location ++;
            count ++;

        }
        before ++;
        
    }
    size = noNonSparseValues + M.noNonSparseValues - count;
    
   
    
    mul = new SparseMatrix(noRows, noCols, commonValue, size);
    
    for (int i=0; i<size ; i++) {
        int r = TwoMatrix->myMatrix[i].getRow();
        int c = TwoMatrix->myMatrix[i].getCol();
        int val = TwoMatrix->myMatrix[i].getValue();
        
        mul->setMyMatrix(r, c, val, location2);
        location2++;
    }
    
    return mul;
}

int main() {
    
    int r, c, cv, nsv;
    int val;
    SparseMatrix* temp = new SparseMatrix();
    
    cout <<"Enter the first matrix"<<endl;
    cin >> r >> c >> cv >>nsv;
    cout<< r <<" " <<c <<" " <<cv <<" "<<nsv<<endl;
    SparseMatrix* firstOne = new SparseMatrix(r,c,cv,nsv);
    int count=0;
    for (int i=0; i < r; i++)
    {
        SparseRow* obj = new SparseRow();
        for (int j=0; j < c; j++) {
            
            cin>>val;
            if (val != cv) {
                obj->setValue(val);
                obj->setCol(j);
                obj->setRow(i);
                
                firstOne->setMyMatrix(obj->getRow(), obj->getCol(), obj->getValue(), count);
                
                count ++;
            }
           
        }
    }
    
    
    cout <<"Enter the second matrix"<<endl;
    
    cin >> r >>c>>cv>> nsv;
    
    SparseMatrix* secondOne = new SparseMatrix (r, c, cv, nsv);
    
    cout<< r <<" " <<c <<" " <<cv <<" "<<nsv<<endl;
    int counter=0;
    for (int i=0; i < r; i++)
    {
        SparseRow* obj = new SparseRow();
        for (int j=0; j < c; j++) {
            
            cin>>val;
            if (val != cv) {
                obj->setValue(val);
                
                obj->setCol(j);
                obj->setRow(i);
                
                secondOne->setMyMatrix(obj->getRow(), obj->getCol(), obj->getValue(), counter);
                counter ++;
            }
            
        }
    }
    cout <<"Frist one in Sparse matrix format" << endl;
    (*firstOne).display();
    
    cout <<"Frist one in normal matrix format" <<endl;
    (*firstOne).displayMatrix();
    
    cout<<"Second one in sparse matrix format"<<endl;
    (*secondOne).display();
    
    cout<<"Second one in normal matrix format"<<endl;
    (*secondOne).displayMatrix();
    
   cout<<"After Transpose first one in normal format"<<endl;
     temp = (*firstOne).Transpose();
     (*temp).displayMatrix();
     
    cout<<"After Transpose second one in normal format"<<endl;
     temp = (*secondOne).Transpose();
     (*temp).displayMatrix();
     
     cout<<"Multiplication of matrices in sparse matrix form: "<<endl;
     temp = (*secondOne).Multiply(*firstOne);
     (*temp).display();
     
     cout <<"Addition of matrices in sparse matrix form: " <<endl;
     temp = (*secondOne).Add(*firstOne);
     (*temp).display();
     
    
    return 0;
    
}
