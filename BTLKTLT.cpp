#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="matrix"> tên của ma trận là dữ liệu đầu vào</param>
/// <param name="row"> số dòng của ma trận</param>
/// <param name="col">số cột của ma trận</param>
/// Logic code: 
///     + khởi tạo 1 mảng có row*col phần tử kiểu bool để đánh dấu các vị trí mà robot đã đi qua
///     + khởi tạo 1 mảng có maximum phần tử = row*col kiểu int để chứa kết quả
///     + 1 cái mảng tạm chứa nhiều nhất là 4 giá trị của robot để tiến hành xét
///     + B1: Xác định vị trí bắt đầu của robot và tiến hành di chuyển
///     +       * Các trường hợp:
///                 * Nếu vị trí có dòng = 0 và cột = 0 thì chỉ tồn tại 2 giá trị là bên phải và dưới
///                 * Nếu vị trí có dòng = 0 và cột ! = 0 thì chỉ tồn tại 3 giá trị là bên phải,dưới,trái
///                 * Nếu vị trí có dòng != 0 và cột != 0 thì chỉ tồn tại 4 giá trị là 4 hướng 
///                 * Nếu vị trí có dòng = tổng số dòng và cột = 0 thì chỉ tồn tại 2 giá trị là bên phải và trên 
///                 * Nếu vị trí có dòng = tổng số dòng và cột != 0 thì chỉ tồn tại 3 giá trị là bên phải và trên và bên trái
///                 * Nếu vị trí có dòng = tổng số dòng và cột = tổng số cột thì chỉ tồn tại 2 giá trị là bên  trên và bên trái
///                 // Tương tự thế sẽ tự liệt kê thêm các trường hợp đặc biệt để xét
///     + Sau khi xác định được 4 giá trị là 4 hướng đi của robot thì bắt đầu tìm giá trị lớn nhất trong 4 giá trị đó. 
///     + Tiếp theo đó thì đi kiểm tra vị trí của phần tử max đó đã đi chưa. Nếu đi qua rồi thì tiến hành xóa pt khỏi mảng tạm và tìm lại giá trị max khác
///     + Cuối cùng là thu được giá trị hợp lệ. Và gọi đệ quy lại hàm đó tiếp tục đi tiếp. Điều kiện dừng là khi các hướng của robot đã đi qua hết rồi thì dừng
void ReadDataFromFile(fstream& f,int matrix[][100],int &row,int &col)
{
    // Hàm đọc dữ liệu từ file data.txt
    f.open("data.txt", ios::in);
    f >> row >>  col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            f >> matrix[i][j];
        }
    }
    f.close();
}
void WriteResultToFile(fstream& f, int a[],int length)
{
    // ghi kết quả ra file result.txt
    f.open("result.txt", ios::out);
    f << length << "\n";
    for (int i = 0; i < length; i++)
    {
        f << a[i] << " ";
    }
    f.close();    
    cout << "Ghi du lieu ra file thanh cong!\n";
}
void PrintMatrix(int matrix[][100], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << setw(5)<<left<< matrix[i][j];
        }
        cout << endl;
    }
}
void del(int a[], int index, int& n)
{
    for (int i = index; i < n; ++i)
    {
        a[i] = a[i + 1];
    }
    n--;
}
void output_array(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        
        cout << a[i] << " ";
    }
    cout << endl;
}
int FindItemByValue(int matrix[][100], int row, int col, int value)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == value)
                return i * col + j;
        }
    }
    return -1;
}
int MaxOfList(int list[], int length)
{
    int max = list[0];
    for (int i = 1; i < length; i++)
    {
        if (list[i] > max)
            max = list[i];
    }
    return max;
}
int FindItemByValue(int list[], int length, int item)
{
    for (int i = 0; i < length; i++)
    {
        if (list[i] == item)
            return i;
    }
    return -1;
}
void FindThePathOfRobot(int result[], int matrix[][100], int rowStart, int colStart, bool flag[], int row, int col, int& steps,bool isPrintStep)
{
    int values[4] = {0,0,0,0};
    int lengthValues = 4;// mảng chứa giá trị 4 phía. 0: trên; 1: dưới; 2:trái; 3: phải
    steps++;
    if (rowStart >= 1 && colStart >= 1 && rowStart < row - 1 && colStart < col - 1)
    {
        values[0] = matrix[rowStart - 1][colStart];
        values[1] = matrix[rowStart + 1][colStart];
        values[2] = matrix[rowStart][colStart - 1];
        values[3] = matrix[rowStart][colStart + 1];
    }
    else if(rowStart == 0 && colStart != 0 && rowStart < row && colStart < col)
    {
        values[1] = matrix[rowStart + 1][colStart];
        values[2] = matrix[rowStart][colStart - 1];
        values[3] = matrix[rowStart][colStart + 1];
    }
    else if (colStart == 0 && rowStart == 0 && rowStart < row && colStart < col)
    {
        values[1] = matrix[rowStart + 1][colStart];
        values[3] = matrix[rowStart][colStart + 1];
    }
    else if (rowStart != 0 && colStart == 0 && rowStart < row && colStart < col)
    {
        values[0] = matrix[rowStart - 1][colStart];
        values[1] = matrix[rowStart + 1][colStart];
        values[3] = matrix[rowStart][colStart + 1];
    }
    else if ((colStart) == col - 1 && rowStart < row-1)
    {
        values[0] = matrix[rowStart - 1][colStart];
        values[1] = matrix[rowStart + 1][colStart];
        values[2] = matrix[rowStart][colStart - 1];

    }
    else if (rowStart == row - 1  && colStart < col - 1)
    {
        values[0] = matrix[rowStart - 1][colStart];
        values[2] = matrix[rowStart][colStart - 1];
        values[3] = matrix[rowStart][colStart + 1];
    }
    else if(col - 1 == colStart && row-1== rowStart)
    {
        values[0] = matrix[rowStart - 1][colStart];
        values[2] = matrix[rowStart][colStart - 1];
    }
    for (int i = 0; i < 4; i++)
    {
        if (values[i] == -858993460) values[i] = 0;
    }
    if (isPrintStep)
    {
        cout << setw(25) << left << "" << "+ Buoc " << steps << ": Cac gia tri xet: ";
        for (int i = 0; i < 4; i++)
        {
            if (values[i] == 0) continue;
            cout << values[i] << " ";
        }
        cout << endl;
    }
    int valMax = MaxOfList(values, lengthValues);
    int idxVal = FindItemByValue(matrix, row, col, valMax);
    while (flag[idxVal] && lengthValues >= 0)
    {
        del(values, FindItemByValue(values,lengthValues,valMax), lengthValues);
        valMax = MaxOfList(values, lengthValues);
        idxVal = FindItemByValue(matrix, row, col, valMax);
    }
    if (lengthValues == -1)
    {
        return ;
    }
    result[steps] = valMax;
    flag[idxVal] = true;
    if (isPrintStep)
    {
        cout << setw(25) << left << "" << "=> Chon so " << valMax << endl;
    }
    FindThePathOfRobot(result, matrix, idxVal / col, idxVal % col, flag, row, col, steps, isPrintStep);
}
void PrintTheSamePositionsOf2Array(int matrix[][100],int row,int col,int arr1[],int length1,int arr2[],int length2)
{
    for (int i = 0; i < length1; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            if (arr1[i] == arr2[j])
            {
                int pos = FindItemByValue(matrix, row, col, arr1[i]);
                cout << "(" << pos / col << "," << pos % col << ") ";
            }
        }
    }
}
void PrintMenu()
{
    cout << endl << endl << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n";
    cout << setw(26) << right << "*" << setw(16) << left << "" << setw(51) << "Chuong trinh tim duong di cua robot" << "*" << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n";
    cout << setw(26) << right << "*" << setw(8) << left << "" << setw(59) << "1. Tim duong di cua 1 robot" << "*" << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n";
    cout << setw(26) << right << "*" << setw(8) << left << "" << setw(59) << "2. Tim duong di cua 2 robot co vi tri khac nhau" << "*" << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n";
    cout << setw(26) << right << "*" << setw(8) << left << "" << setw(59) << "3. Tim duong di cua 2 robot ma khong duoc di trung" << "*" << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n";
    cout << setw(26) << right << "*" << setw(8) << left << "" << setw(59) << "4. Hien thi Step by step duong di cua robot" << "*" << endl;
    cout << setw(25) << left << "" << "---------------------------------------------------------------------\n\n";
}
int main()
{
    fstream f;
    int col, row;
    int matrix[100][100];
    int option = 0;
    char checkContinue;
    ReadDataFromFile(f, matrix, row, col);
    const int length = row * col;
    bool *flag = new bool[length]{};
    int steps1 = 0;
    int steps2 = 0;
    int *result1 = new int[length] {};
    int *result2 = new int[length] {};
    bool* flag2 = new bool[length] {};
    int rowStart1 = 0, colStart1 = 0;
    int rowStart2 = 0, colStart2 = 0;
    int checkedItem = -1;
    do
    {
        system("CLS");
        PrintMenu();
        cout << endl;
        cout << setw(25) << left << "" << "Moi nhap lua chon cua ban: "; cin >> option; cin.ignore();
        switch (option)
        {
        case 1:
            cout << setw(25) << left << "" << "Nhap hang bat dau cua robot: "; cin >> rowStart1;
            cout << setw(25) << left << "" << "Nhap cot bat dau cua robot: "; cin >> colStart1;
            result1[0] = matrix[rowStart1][colStart1];
            flag[rowStart1 * col + colStart1] = true;
            FindThePathOfRobot(result1, matrix, rowStart1, colStart1, flag, row, col, steps1,false);
            cout << setw(25) << left << "" << "So buoc ma robot da di: " << steps1 << endl;
            cout << setw(25) << left << "" << "Cac gia tri robot di qua: "; output_array(result1, steps1);
            cout << endl;
            WriteResultToFile(f, result1, steps1);
            steps1 = 0;
            flag = new bool[length] {};
            result1 = new int[100]{};
            
            break;
            
        case 2:
            cout << setw(25) << left << "" << "Nhap hang bat dau cua robot thu 1: "; cin >> rowStart1;
            cout << setw(25) << left << "" << "Nhap cot bat dau cua robot thu 1: "; cin >> colStart1;
            cout << setw(25) << left << "" << "Nhap hang bat dau cua robot thu 2: "; cin >> rowStart2;
            cout << setw(25) << left << "" << "Nhap cot bat dau cua robot thu 2: "; cin >> colStart2;
            result1[0] = matrix[rowStart1][colStart1];
            flag[rowStart1 * col + colStart1] = true;
            result2[0] = matrix[rowStart2][colStart2];
            flag2[rowStart2 * col + colStart2] = true;
            FindThePathOfRobot(result1, matrix, rowStart1, colStart1, flag, row, col, steps1, false);
            FindThePathOfRobot(result2, matrix, rowStart2, colStart2, flag2, row, col, steps2, false);
            cout << setw(25) << left << "" << "Cac gia tri robot 1 di qua: "; output_array(result1, steps1);
            cout << endl;
            cout << setw(25) << left << "" << "Cac gia tri robot 2 di qua: "; output_array(result2, steps2);
            cout << endl;
            cout << setw(25) << left << "" << "Cac vi tri bi trung: "; PrintTheSamePositionsOf2Array(matrix, row, col, result1, steps1, result2, steps2);
            cout << endl;
            steps1 = 0;
            flag = new bool[length] {};
            result1 = new int[100] {};
            steps2 = 0;
            flag2 = new bool[length] {};
            result2 = new int[100] {};
            break;
        case 3:
            cout << setw(25) << left << "" << "Nhap hang bat dau cua robot thu 1: "; cin >> rowStart1;
            cout << setw(25) << left << "" << "Nhap cot bat dau cua robot thu 1: "; cin >> colStart1;
            result1[0] = matrix[rowStart1][colStart1];
            flag[rowStart1 * col + colStart1] = true;
            cout << setw(25) << left << "" << "So buoc ma robot 1 da di: " << steps1 << endl;
            FindThePathOfRobot(result1, matrix, rowStart1, colStart1, flag, row, col, steps1, false);
            cout << setw(25) << left << "" << "Cac gia tri robot 1 di qua: "; output_array(result1, steps1);
            cout << endl;   
            cout << setw(25) << left << "" << "Cac vi tri ma robot chua di qua: ";
            for (int i = 0; i < length; i++)
            {
                if(!flag[i])
                    cout << "(" << i / col << "," << i % col << ") ";
            }
            do
            {
                cout << setw(25) << left << "" <<  "Nhap hang bat dau cua robot thu 2: "; cin >> rowStart2;
                cout << setw(25) << left << "" <<  "Nhap cot bat dau cua robot thu 2: "; cin >> colStart2;
                checkedItem = FindItemByValue(result1, steps1, matrix[rowStart2][colStart2]);
                if ((colStart1 == colStart2 && rowStart1 == rowStart2) || checkedItem != -1)
                {
                    cout << setw(25) << left << "" << "Vi tri bi trung voi robot ban dau! Nhap lai.\n";
                }
            } while (colStart1 == colStart2 && rowStart1 == rowStart2 || checkedItem != -1);
            result2[0] = matrix[rowStart2][colStart2];
            flag[rowStart2 * col + colStart2] = true;
            FindThePathOfRobot(result1, matrix, rowStart2, colStart2, flag, row, col, steps2, false);
            cout << setw(25) << left << "" << "So buoc ma robot 2 da di: " << steps2 << endl;
            cout << setw(25) << left << "" << "Cac gia tri robot 2 di qua: "; output_array(result2, steps2);
            cout << endl;
            steps1 = 0;
            flag = new bool[length] {};
            result1 = new int[100] {};
            steps2 = 0;
            flag2 = new bool[length] {};
            result2 = new int[100] {};
            break;
        case 4:
            cout << setw(25) << left << "" << "Nhap hang bat dau cua robot: "; cin >> rowStart1;
            cout << setw(25) << left << "" << "Nhap cot bat dau cua robot: "; cin >> colStart1;
            result1[0] = matrix[rowStart1][colStart1];
            flag[rowStart1 * col + colStart1] = true;
            FindThePathOfRobot(result1, matrix, rowStart1, colStart1, flag, row, col, steps1, true);
            cout << setw(25) << left << "" << "So buoc ma robot da di: " << steps1 << endl;
            cout << setw(25) << left << "" << "Cac gia tri robot di qua: "; output_array(result1, steps1);
            cout << endl;
            steps1 = 0;
            flag = new bool[length] {};
            result1 = new int[100] {};
            break;
        default: exit(0);
            break;
        }
        cout << setw(25) << left << "" << "Ban muon tiep tuc? Y/N -------> "; cin >> checkContinue; cin.ignore();
        if (checkContinue != 'Y' && checkContinue != 'y')
        {
            cout << endl;
            cout << setw(20) << left << "" << "Ket thuc chuong trinh \n\n";
        }
    } while (checkContinue == 'Y' || checkContinue == 'y');

    return 0;
}

