// Mini-Project
// Created by Avcton & Mabdullahatif on 12/6/21.
// Description: This program performs various image processing operations
// on a PGM image format. It includes operations such as loading and saving
// images, creating a negative image, applying mean and median filters,
// flipping, rotating, resizing, and cropping the image.

// libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Function to sort a vector in ascending order
void AscSort(vector<int> &A, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 1 + i; j < size; j++) {
            if (A[i] < A[j]) {
                int T = A[i];
                A[i] = A[j];
                A[j] = T;
            }
        }
    }
}
// Structure to represent a PGM image
struct PGMImage{
    int H, W, MaxGray;
    float PI = 3.1416;
    string Comment;
    string MagicNo;
    vector<vector<int>> ImageData;
// Constructor
    PGMImage(){
        cout<<"HERE"<<endl;
        H = W = MaxGray = -1;
    }
// Function to create a 2D vector for image data
    void Create(vector<vector<int>> &Img, int H, int W){
        Img = vector<vector<int>>(H);
        for(int i = 0; i< H; i++)
            Img[i] = vector<int>(W);
        return;
    }

    bool ReserveMemory(){
// Code to create memory storage for the image
// This code assumes that H and W have been set earlier
// Function to allocate memory for the image
        cout<<W<<" "<<H<<endl;
        cout << Comment << endl;
        if(H < 0 || W < 0)
            return false;
        Create(ImageData, H, W);
        return true;
    }

    bool LoadImage(char FileName[]){
// Code to open File, Reserve Memory and load image data in memory
// Function to load an image from a file
        ifstream FIN(FileName);

        if(! FIN.is_open())
            return false;

        getline(FIN, MagicNo);
        getline(FIN, Comment);          // reading the comment. PROBLEM HERE THE COMMENT IS OPTIONAL
        FIN >> W >> H >> MaxGray;
        if( !ReserveMemory())
            return false;

        for(int r = 0; r < H; r++){
            for(int c = 0; c < W; c++){
                FIN >> ImageData[r][c];
            }
        }

        FIN.close();
        return true;
    }

    bool SaveImage(char FileName[]){
// Code to open File, Reserve Memory and load image data in memory
// Function to save an image to a file
        if(H < 0)
            return false;

        ofstream FOUT(FileName);

        if(!FOUT.is_open())
            return false;

        FOUT << "P2" <<endl
        << "# Created By Irfan View running under wine on OSX"<<endl
        << W <<" " <<H<<endl
        <<MaxGray<<endl;

        for(int r = 0; r < H; r++){
            for(int c = 0; c < W; c++){
                FOUT << ImageData[r][c]<<" ";
            }
            FOUT << endl;
        }
        FOUT.close();
        return true;
    }

    bool Create_Negative(){
// Function to create the negative of the image
        for(int r=0; r<H; r++)
            for(int c=0; c<W; c++)
                ImageData[r][c] = MaxGray - ImageData[r][c];

        return true;
    }

// Function to generate a dummy vector for resizing the image
    vector<vector<int>> DummyVectorGenerator(vector<vector<int>> Dummy, int increment, bool putZero){

        // A dummy vector
        Dummy = vector<vector<int>>(H);
        for(int i = 0; i< H; i++)           // Memory reservation
            Dummy[i] = vector<int>(W);

        for(int r=0; r<H; r++)
            for(int c=0; c<W; c++)
                Dummy[r][c] = ImageData[r][c];      // Copying all the elements

        for(int i=0; i<increment; i++){                  // declairing more rows
            Dummy.insert(Dummy.begin(), vector<int>(W));
            Dummy.push_back(vector<int>(W));
        }

        for(int i=0, c=1; i<increment; i++, c++){         // Initializing the incremented rows
            for(int j=0; j<W; j++){
                if(putZero == true){
                    Dummy[i][j] = 0;
                    Dummy[H+i][j] = 0;
                }
                else {
                    Dummy[i][j] = ImageData[increment-c][j];
                    Dummy[H+i][j] = ImageData[H-c][j];
                }
            }
        }

        for(int i=0, c=1; i<increment; i++, c++){               // Initializing the incremented coloumns
            for(int j=0; j< H+(2*increment); j++){
                if(putZero == true){
                    Dummy[j].push_back(0);
                    Dummy[j].insert(Dummy[j].begin(), 0);
                }
                else{
                    Dummy[j].push_back(ImageData[i][W-c]);
                    Dummy[j].insert(Dummy[j].begin(), ImageData[i][increment-c]);
                }
            }
        }

        return Dummy;
    }

// Function to apply a mean filter to the image
    bool Mean_Filter(int FilterSize=3){

        int increment = FilterSize / 2;
        bool putZero = true;

        vector<vector<int>> Dummy = DummyVectorGenerator(ImageData, increment, putZero);

        for(int r=increment; r<H+increment; r++)    // The main show
        {
            for(int c=increment; c<W+increment; c++)
            {
                int sum=0, avg;

                for(int i = r-FilterSize/2; i <= r+FilterSize/2; i++)       // The required matrix fetch
                    for(int j = c-FilterSize/2; j <= c+FilterSize/2; j++)
                        sum = sum + Dummy[i][j];

                avg = sum / (FilterSize * FilterSize);
                ImageData[r-increment][c-increment] = avg;  // Puting the calculated avg back into the original image

            }
        }

        return true;
    }

// Function to apply a median filter to the image
    bool Median_Filter(int FilterSize=3){

        int M;
        int increment = FilterSize / 2;
        bool putZero = false;
        vector<int> Median = vector<int>(FilterSize * FilterSize);
        vector<vector<int>> Dummy = DummyVectorGenerator(ImageData, increment, putZero);

        for(int r=increment; r<H+increment; r++)    // The main show
        {
            for(int c=increment; c<W+increment; c++)
            {
                int u=0;
                for(int i = r-FilterSize/2; i <= r+FilterSize/2; i++)            // The required matrix fetch
                    for(int j = c-FilterSize/2; j <= c+FilterSize/2; j++, u++)
                        Median[u] = Dummy[i][j];

                AscSort(Median, FilterSize*FilterSize);             // Sorting the generated array

                M = Median[(FilterSize*FilterSize)/2];              // Calculating the Median
                ImageData[r-increment][c-increment] = M;            // Storing it

            }
        }
        return true;
    }

    int max(int a, int b){
        if(a>b)
            return a;
        else
            return b;
    }
// Function to rotate the image by a specified angle
    bool Rotate(double angle){

        double rad = (PI * angle) / 180;
        int newr, newc;

        vector<vector<int>> dummy(max(H,W));

        for(int i=0; i<max(H,W); i++)
            dummy[i] = vector<int>(max(H,W));

//        int r0 = W/2 - cos(angle)*W/2 - sin(angle)*H/2;
//        int c0 = H/2 - cos(angle)*H/2 + sin(angle)*W/2;

        for(int r=0; r<H; r++){
            for(int c=0; c<W; c++){
                newr = r * cos(rad) + c * sin(rad);
                newc = r * -sin(rad) + c * cos(rad);

                if(newr < H && newc < W && newr >= 0 && newc >= 0)
                    dummy[r][c] = ImageData[newr][newc];
            }
        }

        H = max(H, W);
        W = max(H, W);

        ImageData = dummy;

        return true;
    }

// Function to rotate the image clockwise by 90 degrees
    bool RotateClockwise(){

        vector<vector<int>>V(H);
        for(int i=0; i<H; i++)
            V[i] = vector<int>(W);

        for(int r=0, cc = W-1; r<H; r++, cc--)
        {
            for(int c=0; c<W; c++)
                V[c][cc] = ImageData[r][c];
        }

        for(int r=0; r<H; r++)
        {
            for(int c=0; c<W; c++)
                ImageData[r][c] = V[r][c];
        }

        return true;
    }

// Function to rotate the image counter-clockwise by 90 degrees
    bool RotateCounterClockwise(){

        vector<vector<int>>V(H);
        for(int i=0; i<H; i++)
            V[i] = vector<int>(W);

        for(int r=0; r<H; r++)
        {
            for(int c=0, rr = H-1; c<W; c++, rr--)
                V[rr][r] = ImageData[r][c];
        }

        for(int r=0; r<H; r++)
        {
            for(int c=0; c<W; c++)
                ImageData[r][c] = V[r][c];
        }


        return true;
    }

// Function to flip the image horizontally
    bool FlipHorizontal(){

        int rows = H;

        for(int r=0; r<rows; r++)
        {
            for(int c=0; c<W; c++)
            {
                int T = ImageData[r][c];
                ImageData[r][c] = ImageData[rows-1][c];
                ImageData[rows-1][c] = T;
            }
                rows--;
        }

        return true;
    }

// Function to flip the image vertically
    bool FlipVertical(){

        for(int r=0; r<H; r++)
        {
            int Col = W;
            for(int c=0; c<Col; c++)
            {
                int T = ImageData[r][c];
                ImageData[r][c] = ImageData[r][Col-1];
                ImageData[r][Col-1] = T;
                Col--;
            }
        }

        return true;
    }

// Function to resize the image
    bool Resize(int NewH, int NewW){

        int inc = H - NewH;

        if(inc<0)
            inc = -inc;

        vector<vector<int>> Dummy(NewH);
        for(int i=0; i<NewH; i++)
            Dummy[i] = vector<int>(W);

        for(int r=0; r<H; r++){
            int RealRow = (NewW/NewH) * r;

            for(int c=0; c<W; c++){
                Dummy[RealRow][c] = ImageData[r][c];
            }
        }

        for(int i=0; i<inc; i++)
            ImageData.push_back(vector<int>(W));

        for(int i=0; i<NewH; i++){
            for(int c=0; c<W; c++){
                ImageData[i][c] = Dummy[i][c];
            }
        }

        H = NewH;

        return true;
    }

// Function to crop the image
    bool CropImage(int Left, int Top, int Right, int Bottom){


        for(int r=Top, row=0; r<H-Bottom; r++, row++)
        {
            for(int c=Left, col=0; c<W-Right; c++, col++)
            {
                ImageData[row][col] = ImageData[r][c];
            }
        }

        H = H - (Top + Bottom);
        W = W - (Left + Right);

        return true;
    }
};

// Function to display the menu and get the user's choice
int Menu(){
    int choice;
    do{
        cout<<endl<<"1. Load Image"<<endl
        <<"2. Save Image"<<endl
        <<"__________________________"<<endl << endl
        <<"3. Create Negative Image"<<endl
        <<"__________________________"<<endl << endl
        <<"4. Mean Filter"<<endl
        <<"5. Median Filter"<<endl
        <<"__________________________"<<endl << endl
        <<"6. Flip Horizontal"<<endl
        <<"7. Flip Vertical"<<endl
        <<"8. Rotate Clockwise by 90 Degree"<<endl
        <<"9. Rotate Counter Clockwise by 90 degree"<<endl
        <<"10. Rotate By arbitrary angle"<<endl
        <<"11. Resize Image"<<endl
        <<"12. Apply general Linear Transformation"<<endl
        <<"13. Crop Image"<<endl
        <<"__________________________"<<endl << endl
        <<"14. Exit"<<endl<<endl
        <<"Enter Your Choice: ";
        cin>> choice;
    } while(choice < 1 || choice > 14);

    return choice;
}

int main()
{
    PGMImage Image;

    char FileName[100];
    int Choice;

    do{
        Choice = Menu();
        if(Choice == 1){
            cout<<"Enter File Name ";
            cin>>FileName;
            if(Image.LoadImage(FileName) )
                cout<<"Image Loaded Successfully "<<endl;
            else
                cout<<"Image Not Loaded Successfully "<<endl;
        }
        else if(Choice == 2){
            cout<<"Enter File Name ";
            cin >> FileName;
            if(Image.SaveImage(FileName) )
                cout<<"Image Saved Successfully "<<endl;
            else
                cout<<"Image Not Saved Successfully "<<endl;

        }
        else if(Choice == 3){
            if(Image.H < 0)
                cout<<"No Image Loaded"<<endl;
            else
                Image.Create_Negative();
        }
        else if(Choice == 4){
            Image.Mean_Filter(5);
        }
        else if(Choice == 5){
            int S;
            cout<<"Filter Size ";
            cin>> S;
            Image.Median_Filter(S);
        }
        else if(Choice == 6){
            Image.FlipHorizontal();
        }
        else if(Choice == 7){
            Image.FlipVertical();
        }
        else if(Choice == 8){
            Image.RotateClockwise();
        }
        else if(Choice == 9){
            Image.RotateCounterClockwise();
        }
        else if(Choice == 10){
            int angle;
            cout << "Enter an angle: ";
            cin >> angle;

            Image.Rotate(angle);
        }
        else if(Choice == 11){
            int h, w;
            cout << "Enter the new Height: "; cin >> h;
            cout << "Enter the new Width: "; cin >> w;

            Image.Resize(h, w);
        }
        else if(Choice == 12){

        }
        else if(Choice == 13){
            int L, T, R, B;
            cout << "Enter the left length: "; cin >> L;
            cout << "Enter the top length: "; cin >> T;
            cout << "Enter the right length: "; cin >> R;
            cout << "Enter the bottom length: "; cin >> B;

            Image.CropImage(L, T, R, B);
        }

    }while(Choice != 14);

    return 0;
}
