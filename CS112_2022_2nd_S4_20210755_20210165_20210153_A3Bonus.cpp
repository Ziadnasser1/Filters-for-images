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
