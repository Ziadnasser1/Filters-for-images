// FCAI – Programming 1 – 2022 - Assignment 3
// Program Name: PhotoshopApp2.0.cpp
// Program Description: Lets the user apply filters on colored photos
// Last Modification Date: 4/17/2022
// Author1 and ID and Group: Alan Samir Hakkoun, 20210755, Group A S3 S4
// Author2 and ID and Group: Ziad Nasser Shaaban, 20210153, Group A S3 S4
// Author3 and ID and Group: Saif El-Din Hazem Mohammed, 20210165, Group A S3 S4
// Teaching Assistant: Nessma Mohamed
// Purpose: Editing colored photos

#include<iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE][RGB];
unsigned char image4[SIZE][SIZE][RGB];
unsigned char imageTemp [SIZE][SIZE][RGB];

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
void editOriginal();

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
        }
    }
    cout << "\nThank you for using our photoshop app \uF04A";
    return 0;
}


void blackWhite() {
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB ;k++){
                if(image[i][j][0]+image[i][j][1]+image[i][j][2] >381)
                    image[i][j][k]=255;
                else
                    image[i][j][k]=0;
            }
        }
    }
}

void invertFilter() {
}

void mergeFilter() {

    char imageFileName[100];
    cout << "\nPlease enter file name of the image to merge: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image1);             // Adds the photo to merge
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int h = 0; h < RGB; h++) {
                image[i][j][h] = image[i][j][h] / 2;             // Reduces the value of the pixel by half
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int h = 0; h < RGB; h++) {
                image1[i][j][h] = image1[i][j][h] / 2;             // Reduces the value of the pixel by half
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int h = 0; h < RGB; h++) {
                image[i][j][h] = image[i][j][h] + image1[i][j][h];             // Adds the values of both pixels together
            }
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
                         for(int k=0;k<RGB;k++){
                                //taking the data in each pixel and put it in temporary variable then changing each pixel's data
                                //with it's opposite pixel's data belong to the other half of the image
                                //and giving the opposite pixel the data of the temporary variable.
                                int temp= image[i][j][k];
                                image[i][j][k]=image[SIZE-1-i][j][k];
                                image[SIZE-1-i][j][k]=temp;
                            }

                        }
                    }
            break;
            }
        case 'v':
            {
                //in case of vertical flip loop till reach half of the columns length.
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE/2;j++){
                        for(int k=0;k<RGB;k++){
                            //taking the data in each pixel and put it in temporary variable then changing each pixel's data
                            //with it's opposite pixel's data belong to the other half of the image.
                            //and giving the opposite pixel the data of the temporary variable.
                            int temp= image[i][j][k];
                            image[i][j][k]=image[i][SIZE-1-j][k];
                            image[i][SIZE-1-j][k]=temp;
                            }
                        }
                    }
             break;
            }
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
                for (int j = 0; j < SIZE; j++) {
                    for (int h = 0; h < RGB; h++) {
                        image[i][j][h] = image[i][j][h] / 2;             // Reduces the value of the pixel by half
                    }
                }
            }
            break;
        } else if (degreeType == "l") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int h = 0; h < RGB; h++) {
                        lightAdder = 255 - image[i][j][h];
                        lightAdder /= 2;             // Get the value needed to reach 255 and divide by 2
                        image[i][j][h] += lightAdder;             // Adds the lightAdder value to the pixel to lighten it
                    }
                }
            }
            break;
        } else {
            cout << "Invalid input\n" << endl;
        }
    }
}

void rotateImage() {
}

void detectEdges() {
    unsigned char imagetmp0[SIZE][SIZE][RGB];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB ;k++){
                if(image[i][j][0]+image[i][j][1]+image[i][j][2] >381)
                    image[i][j][k]=255;
                else
                    image[i][j][k]=0;

            }
        }
    }

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                if(i==0 || i==255 || j==0 || j==255){ //leaving the data of the boundary pixel the same without changes.
                imagetmp0[i][j][k]=image[i][j][k];
            }
             else{
                 if((image[i-1][j][k]==image[i][j-1][k])&&(image[i+1][j][k]==image[i][j+1][k])&&(image[i-1][j][k]==image[i+1][j][k])&&(image[i][j-1][k]==image[i][j+1][k]))//check the different between the surrounding pixels color.
                    imagetmp0[i][j][k]=255;
                else
                    imagetmp0[i][j][k]=0;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                image[i][j][k] = imagetmp0[i][j][k];
            }
        }
    }
}

void enlargeImage() {
}

void shrinkImage() {
    string shrinkLevel;
    while (true) {
        cout << "Shrink to (1/2), (1/3) or (1/4)?\n"
                ">> ";
        cin >> shrinkLevel;
        if ((shrinkLevel == "1/2") || (shrinkLevel == "1/3") || (shrinkLevel == "1/4")) {
            int level = shrinkLevel[shrinkLevel.length() - 1] - '0';             // Gets the shrink level
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int h = 0; h < RGB; h++) {
                        imageTemp[i][j][h] = 255;             // Create a plain white image
                    }
                }
            }
            int k = 0;
            int l = 0;
            for (int h = 0; h < RGB; h++) {
                for (int i = 0; i < SIZE; i += level) {
                    for (int j = 0; j < SIZE; j += level) {
                        imageTemp[k][l][h] = image[i][j][h];             // Adds the photo after shrinking to the white one
                        l++;
                    }
                    l = 0;
                    k++;
                }
                l = 0;
                k = 0;
            }
            editOriginal();             // Adds the edited photo to the original one
            break;
        } else {
            cout << "Invalid shrinking level\n" << endl;
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
                        for(int k=0;k<RGB;k++){
                            //giving each pixel in the right side of the image the data of the opposite left side pixel.
                            image[i][j][k]=image[i][SIZE-1-j][k];
                            }
                        }
                    }
            break;
            }
        case 'r':
            {
                //in case of mirroring the right half of the required image loop from the left of the image till the vertical half.
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE/2;j++){
                        for(int k=0;k<RGB;k++){
                            //giving each pixel in the left side of the image the data of the opposite right side pixel.
                            image[i][j][k]=image[i][SIZE-1-j][k];
                            }
                        }
                    }
             break;
            }
            case 'u':
            {
                //in case of mirroring the upper half of the required image loop from the horizontal half of the image till its end.
                for(int i=SIZE/2;i<SIZE;i++){
                    for(int j=0;j<SIZE;j++){
                        for(int k=0;k<RGB;k++){
                             //giving each pixel in the upper side the data of the opposite pixel in the down side.
                            image[i][j][k]=image[SIZE-1-i][j][k];
                            }
                        }
                    }
             break;
            }
            case 'd':
            {
                //in case of mirroring the down half of the required image loop from the beginning of the image till its horizontal half.
                for(int i=0;i<SIZE/2;i++){
                    for(int j=0;j<SIZE;j++){
                        for(int k=0;k<SIZE;k++){
                            //giving each pixel in the down side the data of the opposite pixel in the upper side.
                            image[i][j][k]=image[SIZE-1-i][j][k];
                            }
                        }
                    }
             break;
            }
    }
}

void shuffleImage() {
}

void blurImage() {
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            for (int h = 0; h < RGB; h++) {
                if (i != 255) {
                    image[i][j][h] =
                            (image[i + 1][j - 1][h] + image[i - 1][j + 1][h] + image[i + 1][j][h] + image[i][j + 1][h] +
                             image[i + 1][j + 1][h] + image[i - 1][j - 1][h] + image[i - 1][j][h] +
                             image[i][j - 1][h]) / 8;             // Assigning the pixel with the average of the pixels around the pixel
                } else {
                    image[i][j][h] =
                            (image[i][j - 1][h] + image[i - 1][j + 1][h] + image[i][j][h] + image[i][j + 1][h] +
                             image[i][j + 1][h] + image[i - 1][j - 1][h] + image[i - 1][j][h] +
                             image[i][j - 1][h]) / 8;            // Assigning the pixel with the average of the pixels around the pixel
                }
            }
        }
    }
}

void saveImage() {
    char imageFileName[100];
    cout << "\nEnter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
    cout << "Your image has been saved.\n" << endl;
}

void loadImage () {
    while (true) {
        char imageFileName[100];
        cout << "\nPlease enter file name of the image to process: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
        if (readRGBBMP(imageFileName, image) != 1) {
            break;
        }
    }
}

void editOriginal() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int h = 0; h < RGB; h++) {
                image[i][j][h] = imageTemp[i][j][h];
            }
        }
    }
}
