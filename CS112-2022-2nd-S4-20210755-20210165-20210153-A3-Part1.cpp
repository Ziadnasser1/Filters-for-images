// FCAI – Programming 1 – 2022 - Assignment 3
// Program Name: CS112-2022-2nd-S4-20210755-20210165-20210153-A3-Part1.cpp
// Program Description: Lets the user apply filters on gray scale and colored bmp images
// Last Modification Date: 04/18/2022
// Author1 and ID and Group: Alan Samir Hakkoun, 20210755, Group A S3 S4
// Author2 and ID and Group: Saif El-Din Hazem, 20210165, Group A S3 S4
// Author3 and ID and Group: Ziad Nasser Shaaban, 20210153, Group A S3 S4
// Teaching Assistant: Nessma Mohamed
// Purpose: Editing photos

#include<iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char mergedImg[SIZE][SIZE];



void loadImage();
void blackWhite();
void invertFilter();
void mergeFilter();
void flipImage();
void darkenLighten();
void rotateImage();
void detectEdges();
void enlargeImage();
void shrinkImage();
void mirrorHalf();
void shuffleImage();
void blurImage();
void saveImage();

int main() {
    char filter;
    string stateDecide;
    bool progRun = true;
    cout << "Ahlan ya user ya habibi \uF04A\n";
    loadImage();
    while (true) {
        if (!progRun) {
            break;
        }
        cout << "\nPLease select a filter to apply or 0 to exit:\n"
                "1-Black & White Filter\n"
                "2-Invert Filter\n"
                "3-Merge Filter\n"
                "4-Flip Image\n"
                "5-Darken and Lighten Image\n"
                "6-Rotate Image\n"
                "7-Detect Image Edges\n"
                "8-Enlarge Image\n"
                "9-Shrink Image\n"
                "a-Mirror 1/2 Image\n"
                "b-Shuffle Image\n"
                "c-Blur Image\n"
                "s-Save image to a file\n"
                "0-Exit\n"
                ">> ";
        cin >> filter;
        switch (filter) {
            case '1':
                blackWhite();
                break;
            case '2':
                invertFilter();
                break;
            case '3':
                mergeFilter();
                break;
            case '4':
                flipImage();
                break;
            case '5':
                darkenLighten();
                break;
            case '6':
                rotateImage();
                break;
            case '7':
                detectEdges();
                break;
            case '8':
                enlargeImage();
                break;
            case '9':
                shrinkImage();
                break;
            case 'a':
                mirrorHalf();
                break;
            case 'b':
                shuffleImage();
                break;
            case 'c':
                blurImage();
                break;
            case 's':
                saveImage();
                cout << "Enter 1 to continue or any to exit: ";
                cin >> stateDecide;
                if (stateDecide == "1") {
                    loadImage();
                    break;
                } else {
                    progRun = false;
                    break;
                }
            case '0':
                progRun = false;
                break;
            default:
                cout << "Enter a valid filter or 0 to exit\n";
                break;
        }
    }
    cout << "\nThank you for using our image editing app \uF04A";
    return 0;
}


void blackWhite() {
}

void invertFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = abs(image[i][j]-255);
        }
    }
}

void mergeFilter() {
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            mergedImg[i][j] = image[i][j];
        }
    }
    cout <<"Please enter name of image file to merge with: \n >> ";
    loadImage();
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            image[i][j] = (mergedImg[i][j]+image[i][j])/2;
        }
    }

}

void flipImage() {
    char option;
    cout<<"flip (h)orizontally or (v)ertically?"<<endl;
    cout<<">>";
    cin>>option;
    //cases of vertical or horizontal flip filter for the required image.
    switch(option){
        case 'h':
            {
                //in case of horizontal flip loop till reach half of the rows length.
                for(int i=0;i<SIZE/2;i++){
                    for(int j=0;j<SIZE;j++){
                        //taking the data in each pixel and put it in temporary variable then changing each pixel's data
                        //with it's opposite pixel's data belong to the other half of the image
                        //and giving the opposite pixel the data of the temporary variable.
                        int temp= image[i][j];
                        image[i][j]=image[SIZE-1-i][j];
                        image[SIZE-1-i][j]=temp;
                        }
                    }
            break;
            }
        case 'v':
            {
                //in case of vertical flip loop till reach half of the columns length.
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE/2;j++){
                        //taking the data in each pixel and put it in temporary variable then changing each pixel's data
                        //with it's opposite pixel's data belong to the other half of the image.
                        //and giving the opposite pixel the data of the temporary variable.
                        int temp= image[i][j];
                        image[i][j]=image[i][SIZE-1-j];
                        image[i][SIZE-1-j]=temp;
                        }
                    }
             break;
            }
}

void darkenLighten() {
    string degreeType;
    while (true) {
        long lightAdder;
        cout << "Do you want to (d)arken or (l)ighten?\n"
                ">> ";
        cin >> degreeType;
        if (degreeType == "d") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    image[i][j] = image[i][j]/2;
                }
            }
            break;
        } else if (degreeType == "l") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    lightAdder = 255 - image[i][j];
                    lightAdder /= 2;
                    image[i][j] += lightAdder;
                }
            }
            break;
        } else {
            cout << "Invalid input\n" << endl;
        }
    }
}

void rotateImage() {
     int choice;
    for (int i = 0; i < (SIZE); i++){
        for (int j =i+1; j< (SIZE); j++) {
            swap(image[i][j],image[j][i]);
        }
    }

    cout<<"Rotate (90), (180) or (270) degrees ? /n >> ";
    cin>>choice;

    if(choice==90){
        for (int i = 0; i < SIZE; i++ ){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[j][i], image[SIZE-j-1][i]);
            }
        }
    }

    else if(choice==180){
        for (int i = 0; i < (SIZE); i++){
            for (int j =0; j< (SIZE-i); j++){
                swap(image[i][j],image[SIZE-j-1][SIZE-i-1]);
            }
        }
    }

    else if(choice==270){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[i][j], image[i][SIZE-j-1]);
            }
        }
    }

    else cout<<"Wrong Choice, Please Try Again !";
}

void detectEdges() {
}

void enlargeImage() {
}

void shrinkImage(){
    int choice;
    cout<<"1- Shrink to (1/2)\n 2- Shrink to (1/3) \n 3- Shrink to (1/4)?\n >> ";
    cin>>choice;
    if (choice==1){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/2][j/2]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/2 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/2; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }

}

        else if (choice==2){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/3][j/3]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/3 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/3; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
    else if (choice==3){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/4][j/4]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/4 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/4; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
    }

void mirrorHalf() {
     char choice;
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?"<<endl;
    cout<<">>";
    cin>>choice;

    //cases of the different types of mirroring the image.
    switch(choice){
        case 'l':
            {
                //in case of mirroring the left half of the required image loop from vertical half till the end.
                for(int i=0;i<SIZE;i++){
                    for(int j=SIZE/2;j<SIZE;j++){
                        //giving each pixel in the right side of the image the data of the opposite left side pixel.
                        image[i][j]=image[i][SIZE-1-j];
                        }
                    }
            break;
            }
        case 'r':
            {
                //in case of mirroring the right half of the required image loop from the left of the image till the vertical half.
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE/2;j++){
                        //giving each pixel in the left side of the image the data of the opposite right side pixel.
                        image[i][j]=image[i][SIZE-1-j];
                        }
                    }
             break;
            }
            case 'u':
            {
                //in case of mirroring the upper half of the required image loop from the horizontal half of the image till its end.
                for(int i=SIZE/2;i<SIZE;i++){
                    for(int j=0;j<SIZE;j++){
                        //giving each pixel in the upper side the data of the opposite pixel in the down side.
                        image[i][j]=image[SIZE-1-i][j];
                        }
                    }
             break;
            }
            case 'd':
            {
                //in case of mirroring the down half of the required image loop from the beginning of the image till its horizontal half.
                for(int i=0;i<SIZE/2;i++){
                    for(int j=0;j<SIZE;j++){
                        //giving each pixel in the down side the data of the opposite pixel in the upper side.
                        image[i][j]=image[SIZE-1-i][j];
                        }
                    }
             break;
            }
    }
}

void shuffleImage() {
}

void blurImage() {
}

void saveImage() {
    char imageFileName[100];
    cout << "\nEnter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
    cout << "Your image has been saved.\n" << endl;
}

void loadImage () {
    while (true) {
        char imageFileName[100];
        cout << "\nPlease enter file name of the image to process: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
        if (readGSBMP(imageFileName, image) != 1) {
            break;
        }
    }
}
