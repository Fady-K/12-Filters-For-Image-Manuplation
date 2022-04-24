#include <iostream>
#include <string>
#include <algorithm>
#include "bmplib.cpp"
#include <limits>

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

//______________________________
void blacknwhite();
void Invert();
void Flip();
void RotateAll();
void merge();
void DarkenLighten();
void edgedetection();
void Enlarge();
void shrink();
void mirror();
void shuffleImage();
void blur();

using namespace std;

//___________________________________
void display(bool &first_time, int &choice)
{
    if (first_time)
    {
        cout << "!! Welcome !!" << endl;
        first_time = false;
    }

    cout << "1- Black and White Image\n2- Invert Image\n3- Merge Images\n4- Flip Image\n5- Rotate Image\n6- Darken and Lighten Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\n10- Mirror 1/2 Image\n11- Shuffle Image\n12- Blur Image\n0- Exit" << endl;

    cout << "What Do You Want To Do?: ";
    cin >> choice;
}

//_______________________________
int main()
{
    bool isFirstTime = true;
    bool isProgramRunning = true;
    int choice;
    display(isFirstTime, choice);
    while (isProgramRunning)
    {
        if (choice == 1)
        {
            blacknwhite();
        }
        else if (choice == 2)
        {
            Invert();
        }
        else if (choice == 3)
        {
            merge();
        }
        else if (choice == 4)
        {
            Flip();
        }
        else if (choice == 5)
        {
            RotateAll();
        }
        else if (choice == 6)
        {
            DarkenLighten();
        }
        else if (choice == 7)
        {

            edgedetection();
        }
        else if (choice == 8)
        {
            Enlarge();
        }
        else if (choice == 9)
        {
            shrink();
        }
        else if (choice == 10) 
        {
            mirror();
        }
        else if (choice == 11) 
        {
            shuffleImage();
        }
        else if (choice == 12) 
        {
            blur();
        }

        else if (choice == 0)
        {
            isProgramRunning = false;
            break;
        }

        else
        {
            cout << "#####################" << endl;
            cout << "!! Invalid !!" << endl;
            cout << "#####################" << endl;
        }
        display(isFirstTime, choice);
    }
}

//________________________
// Reading and Writing Functions
//________________________
// load image using readGSBMP >>>> this functions takes file name and the imagerix where to store the bits values
void load_image(bool SecondImage)
{
    // take the file name
    char ImageName[100];
    cout << "Enter The Image name: ";
    cin >> ws >> ImageName; // this tells the compiler to ignore buffers and to remove all white spaces before the content of the string

    // append .bmp to it
    strcat(ImageName, ".bmp");
    // fetch the file from the directory then fill the imagerix with it
    readGSBMP(ImageName, image);
    if (SecondImage)
    {
        // take the Seond file name
        char ImageName[100];
        cout << "Enter The Target name: ";
        cin >> ws >> ImageName; // this tells the compiler to ignore buffers and to remove all white spaces before the content of the string

        // append .bmp to it
        strcat(ImageName, ".bmp");
        // fetch the file from the directory then fill the imagerix with it
        readGSBMP(ImageName, image2);
    }
}

//__________________________________
void WriteImage(unsigned char image[SIZE][SIZE])
{
    // take the new image name
    char NewName[100];
    cout << "Enter The New Name: ";
    cin >> ws >> NewName; // this tell the compiller to ignore all the bufferst and to remove all white spaces before the content of the string

    // append .bmp to it

    strcat(NewName, ".bmp");

    // render the new image with newname
    writeGSBMP(NewName, image);
}

//__________________
// six filters
//__________________

// invert filter
void Invert()
{
    load_image(false);

    // loop over each bit of the imagerix
    for (int i = 0; i < 256; ++i) // loop over the rows of the image
    {
        // loop over the values inside each row (loop over the columns)
        for (int j = 0; j < 256; ++j)
        {
            // this will invert the pixel value
            image[i][j] = (abs(255 - image[i][j]));
        }
    }
    WriteImage(image);
}

//_______________________________________
// Rotating Filter (90, 180, 360)
//_______________________________________

void rotate90Clockwise()
{

    // Traverse each cycle
    for (int i = 0; i < 256 / 2; i++)
    {
        for (int j = i; j < 256 - i - 1; j++)
        {
            // Swap elements of each cycle
            // in clockwise direction
            int temp = image[i][j];
            image[i][j] = image[256 - 1 - j][i];
            image[256 - 1 - j][i] = image[256 - 1 - i][256 - 1 - j];
            image[256 - 1 - i][256 - 1 - j] = image[j][256 - 1 - i];
            image[j][256 - 1 - i] = temp;
        }
    }
}

//_________________________________________
void rotate90AntiClock()
{
    for (int i = 0; i < 256 / 2; i++)
    {
        for (int j = i; j < 256 - i - 1; j++)
        {
            // Swapping elements after each iteration in Anticlockwise direction
            int temp = image[i][j];
            image[i][j] = image[j][256 - i - 1];
            image[j][256 - i - 1] = image[256 - i - 1][256 - j - 1];
            image[256 - i - 1][256 - j - 1] = image[256 - j - 1][i];
            image[256 - j - 1][i] = temp;
        }
    }
}

//________________________________
void Rotate180Degrees()
{
    // rotate the imagerix by 180 degrees
    int N = 256;
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            swap(image[i][j], image[N - i - 1][N - j - 1]);
        }
    }

    // handle the case when the matrix has odd dimensions
    if (N & 1)
    {
        for (int j = 0; j < N / 2; j++)
        {
            swap(image[N / 2][j], image[N / 2][N - j - 1]);
        }
    }
}

//_________________________
void RotateAll()
{
    // take the angel from user
    cout << "Rotate (90), (180) or (360) degrees?: ";
    int angle;
    cin >> ws >> angle;

        // check the rotation angle
    if (angle == 90)
    {
        load_image(false);
        rotate90Clockwise();
        WriteImage(image);
    }
    else if (angle == 180)
    {
        load_image(false);
        Rotate180Degrees();
        WriteImage(image);
    }
    // 360 degrees >> 90 degree anti clock wise
    else if (angle == 360)
    {
        load_image(false);
        rotate90AntiClock();
        WriteImage(image);
    }
}

//_________________________________________
// Black And White Filter
//_________________________________________

void blacknwhite()
{
    // take image
    load_image(false);

    int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += i;
    }
    sum = sum / 255;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            if (image[i][j] > sum)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    // write the image
    WriteImage(image);
}

//_________________________
// Flip Filter (Vertically and Horizontally)
//_______________________

void verticalflip()
{
    for (int col = 0; col < SIZE; col++)
    {
        for (int row = 0; row < SIZE / 2; row++)
        {
            swap(image[row][col], image[SIZE - row][col]);
        }
    }
}

//_____________________________
void horizontalflip()
{
    int jy;
    for (int row = 0; row < SIZE; row++)
    {

        for (int col = 0; col < SIZE / 2; col++)
        {

            jy = image[row][col];
            image[row][col] = image[row][SIZE - 1 - col];
            image[row][SIZE - 1 - col] = jy;
        }
    }
}

//____________________________
void Flip()
{
    // load image
    load_image(false);
    // v or h

    char WayOfFliping;
    cout << "Flip (h)orizontally or (v)ertically?: ";
    cin >> ws >> WayOfFliping;
    if (WayOfFliping == 'v')
    {
        verticalflip();
    }
    else if (WayOfFliping == 'h')
    {
        horizontalflip();
    }
    // write the image
    WriteImage(image);
}

//_______________________
// Merging Filter
//_______________________

void merge()
{
    // take two images from the user
    load_image(true);
    // merge them
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
    // write the image
    WriteImage(image);
}

//_____________________
// Darken and Lighted filter
//_____________________

void Darken()
{

    for (int i = 0; i < SIZE; i++)

    {
        for (int j = 0; j < SIZE; j++)
        {

            image[i][j] = image[i][j] - (image[i][j] * 0.5);
        }
    }
}

//____________________________
void Lighten()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int new_value = (image[i][j] * 0.5) + image[i][j];
            image[i][j] = min(new_value, 255);
        }
    }
}

//___________________
void DarkenLighten()
{
    // take char from the user to determine  which filter apply

    char option;
    cout << "Do you want to (d)arken or (l)ighten?: ";
    cin >> ws >> option;
    // take image from the user
    load_image(false);
    // choose which filter to implement
    if (option == 'd')
    {
        Darken();
    }
    else if (option == 'l')
    {
        Lighten();
    }
    // write the image
    WriteImage(image);
}

//______________________________
// insert Funtion to insert based on the user desire
void Insert_To_Image_After_Modification(char Q, int &qrt_pos, unsigned char qrt_arr[SIZE / 2][SIZE / 2])
{
    if (qrt_pos == 1)
    {
        for (int i = 0, x = 0; i < SIZE / 2; ++i, ++x)
        {
            for (int j = 0, y = 0; j < SIZE / 2; ++j, ++y)
            {
                image[i][j] = qrt_arr[x][y];
            }
        }
    }
    else if (qrt_pos == 2)
    {
        for (int i = 0, x = 0; i < SIZE / 2; ++i, ++x)
        {
            for (int j = SIZE / 2, y = 0; j < SIZE; ++j, ++y)
            {
                image[i][j] = qrt_arr[x][y];
            }
        }
    }
    else if (qrt_pos == 3)
    {
        for (int i = SIZE / 2, x = 0; i < SIZE; ++i, ++x)
        {
            for (int j = 0, y = 0; j < SIZE / 2; ++j, ++y)
            {
                image[i][j] = qrt_arr[x][y];
            }
        }
    }
    else if (qrt_pos == 4)
    {
        for (int i = SIZE / 2, x = 0; i < SIZE; ++i, ++x)
        {
            for (int j = SIZE / 2, y = 0; j < SIZE; ++j, ++y)
            {

                image[i][j] = qrt_arr[x][y];
            }
        }
    }
}

// Shuffle Filter
void shuffleImage()
{
    // load the image
    load_image(false);

    // declare array to initialize with the image quarts
    unsigned char first_qrt[SIZE / 2][SIZE / 2];
    unsigned char second_qrt[SIZE / 2][SIZE / 2];
    unsigned char third_qrt[SIZE / 2][SIZE / 2];
    unsigned char fourth_qrt[SIZE / 2][SIZE / 2];

    // load each array with the corresponding quart from the image
    for (int i = 0; i < SIZE / 2; ++i)
    {

        for (int j = 0; j < SIZE / 2; ++j)
        {

            first_qrt[i][j] = image[i][j];
        }
    }

    for (int i = 0, x = 0; i < SIZE / 2; ++i, ++x)
    {
        for (int j = SIZE / 2, y = 0; j < SIZE; ++j, ++y)
        {
            second_qrt[x][y] = image[i][j];
        }
    }

    for (int i = SIZE / 2, x = 0; i < SIZE; ++i, ++x)
    {
        for (int j = 0, y = 0; j < SIZE / 2; ++j, ++y)
        {
            third_qrt[x][y] = image[i][j];
        }
    }

    for (int i = SIZE / 2, x = 0; i < SIZE; ++i, ++x)
    {
        for (int j = SIZE / 2, y = 0; j < SIZE; ++j, ++y)
        {
            fourth_qrt[x][y] = image[i][j];
        }
    }

    // take input from user
    int qrt1_pos, qrt2_pos, qrt3_pos, qrt4_pos;
    cout << "New order of quarters?: ";
    cin >> qrt1_pos >> qrt2_pos >> qrt3_pos >> qrt4_pos;

    // rearrange the image based on the user desire
    Insert_To_Image_After_Modification('1', qrt1_pos, first_qrt);
    Insert_To_Image_After_Modification('2', qrt2_pos, second_qrt);
    Insert_To_Image_After_Modification('3', qrt3_pos, third_qrt);
    Insert_To_Image_After_Modification('4', qrt4_pos, fourth_qrt);

    // writ the image
    WriteImage(image);
}
//______________________________
// Enlarge Filter
void EnlargeInput(int &Q)
{

    cout << "Which quarter to enlarge 1, 2, 3 or 4?: ";
    cin >> ws >> Q;
}

//__________________________
// Enlarge filter
void Enlarge()
{
    // load image from user
    load_image(false);

    // know which quart to enlarge from the user
    int quarter;
    EnlargeInput(quarter);

    // take quarter and enlarge it in new array image2
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (quarter == 1)
            {

                image2[i][j] = image[i / 2][j / 2];
            }

            else if (quarter == 2)
            {
                image2[i][j] = image[i / 2][128 + j / 2];
            }

            else if (quarter == 3)
            {
                image2[i][j] = image[128 + i / 2][j / 2];
            }

            else if (quarter == 4)
            {
                image2[i][j] = image[128 + i / 2][128 + j / 2];
            }
        }
    }
    // write the image
    WriteImage(image2);
}
//____________________
// shrink
//___________________
void shrinkHalf()
{

    for (int i = 0; i < (SIZE); i++)
    {

        for (int j = 0; j < (SIZE); j++)
        {
            image2[i][j] = 255;
        }
    }

    for (int i = 0; i < (SIZE); i++)
    {
        for (int j = 0; j < (SIZE); j++)
        {
            image2[i / 2][j / 2] = (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
        }
    }
}

void shrinkThird()
{
    for (int i = 0; i < (SIZE); i++)
    {
        for (int j = 0; j < (SIZE); j++)
        {
            image2[i][j] = 255;
        }
    }

    for (int i = 0; i < (SIZE); i++)
    {
        for (int j = 0; j < (SIZE); j++)
        {
            image2[i / 3][j / 3] = (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
        }
    }
}
void shrinkFourth()
{

    for (int i = 0; i < (SIZE); i++)
    {
        for (int j = 0; j < (SIZE); j++)
        {
            image2[i][j] = 255;
        }
    }

    for (int i = 0; i < (SIZE); i++)
    {
        for (int j = 0; j < (SIZE); j++)
        {
            image2[i / 4][j / 4] = (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
        }
    }
}

void shrink()
{
    load_image(false);
    string option;
    cout << "Shrink to (1/2), (1/3) or (1/4)?  ";
    cin >> option;
    if (option == "1/2")
    {

        shrinkHalf();
    }

    else if (option == "1/3")
    {

        shrinkThird();
    }
    else if (option == "1/4")
    {
        shrinkFourth();
    }
    WriteImage(image2);
}
//____________________
// blur Filter
//______________
void blur()
{
    load_image(false);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // get the average of the 25 pixels around every pixel
            image[i][j] = (image[i - 2][j - 2] + image[i - 2][j - 1] + image[i - 2][j] + image[i - 2][j + 1] + image[i - 2][j + 2] + image[i - 1][j - 2] + image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i - 1][j + 2] + image[i][j - 2] + image[i][j - 1] + image[i][j + 1] + image[i][j + 2] + image[i + 1][j - 2] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1] + image[i + 1][j + 2] + image[i + 2][j - 2] + image[i + 2][j - 1] + image[i + 2][j] + image[i + 2][j + 1] + image[i + 2][j + 2] + image[i][j]) / 25;
        }
    }

    WriteImage(image);
}

//_______________
// mirror filter
//______________
void Rmirror()
{
    for(int row = 0; row < SIZE  ; row++)
    {
        for (int col = 0; col < SIZE/2 ; col++)
        {
            image[row][(SIZE/2)-col] = image[row][(SIZE/2)+col];
        }   
    }
}




void Lmirror()
{
    for(int row = 0; row < SIZE  ; row++)
    {
        for (int col = 0; col < SIZE/2 ; col++)
        {
            image[row][(SIZE/2)+col] = image[row][(SIZE/2)-col];
        }
    }


}

void Umirror(){
for(int row = 0; row < SIZE/2  ; row++)
{
    for (int col = 0; col < SIZE ; col++)
    {
        image[(SIZE/2)+row][col] = image[(SIZE/2)-row][col];
    }
}


}
void LOmirror()
{
    for(int row = 0; row < SIZE/2  ; row++)
    {
        for (int col = 0; col < SIZE ; col++)
        {
            image[(SIZE/2)-row][col] = image[(SIZE/2)+row][col];
        }
    }


}

void mirror()
{
    load_image(false);
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?: ";
    char dir; 
    cin >> ws >> dir;
    if (dir == 'l')
    {

        Rmirror();


    }
    else if (dir == 'r')
    {
        Lmirror();


    }
    else if (dir == 'u')
    {
        Umirror();


    }
    else if (dir == 'd')
    {
        LOmirror();
    }
    
    WriteImage(image);
}

//______________________
// Edge Detection
//______________________
void edgedetection()
{
    // load image
    load_image(false);

    char num[256];
    for (int col = 1; col < SIZE; col++)
    {

        for (int row = 1; row < SIZE; row++)
        {

            if ((image[row - 1][col - 1]) - (image[row][col]) > 30)
            {

                num[col - 1] = image[row - 1][col - 1];
                image[row - 1][col - 1] = 0;
            }
        }
    }

    for (int col = 0; col < SIZE; col++)
    {
        for (int row = 0; row < SIZE; row++)
        {

            bool exists = find(begin(num), end(num), image[row][col]) != end(num);
            if (exists)
            {

                continue;
            }
            else
            {

                image[row][col] = 255;
            }
        }
    }
    // write image
    WriteImage(image);
}
