#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

///DATALIST CLASS IMPLEMENTATION
template <typename T>
dataList<T>::dataList() : fstPoint(nullptr), lastPoint(nullptr), pNext(nullptr), size(0){}

template <typename T>
void dataList<T>::push_back(T value) {
    dataList<T> *newData = new dataList<T>;
    newData->data = value;
    newData->pNext = nullptr;
    if (!fstPoint)
        fstPoint = newData;
    if (lastPoint)
        lastPoint->pNext = newData;
    lastPoint = newData;
    size++;
}

template<typename T>
void dataList<T>::push_front(T value) {
    dataList<T> *newData = new dataList<T>;
    newData->data = value;
    newData->pNext = fstPoint;
    fstPoint = newData;
    size++;
}

template <typename T>
void dataList<T>::insert(int index, T value) {
    if (index < 0 || index > size)
        return;
    dataList<T> **insertNode = &fstPoint;
    while (index){
        insertNode = &(*insertNode)->pNext;
        index--;
    }
    dataList<T> *newData = new dataList<T>;
    newData->data = value;
    newData->pNext = *insertNode;
    *insertNode = newData;
    size++;
}

template <typename T>
void dataList<T>::remove(int index) {
    if (index < 0 || index >= size)
        return;
    dataList<T> **del = &fstPoint;
    while (index){
        del = &(*del)->pNext;
        index--;
    }
    dataList<T> *delNode = *del;
    *del = delNode->pNext;
    delete delNode;
}

template<typename T>
T &dataList<T>::get(int index) const {
    if (index < 0 || index >= size)
        throw out_of_range("get(): Out of range");
    dataList<T> *Node = fstPoint;
    while (index){
        Node = Node->pNext;
        index--;
    }
    return Node->data;
}

template <typename T>
int dataList<T>::length() const {   return size;}

template <typename T>
void dataList<T>::clear() {
    lastPoint = nullptr;
    while (size){
        dataList<T> *del = fstPoint;
        fstPoint = fstPoint->pNext;
        delete del;
        size--;
    }
}

template <typename T>
void dataList<T>::print() const{
    dataList<T> *p = fstPoint;
    while (p){
        cout << p->data;
        if (p->pNext)
            cout << " ";
        p = p->pNext;
    }
}

template <typename T>
void dataList<T>::print(int col) const{
    if (!fstPoint)
        return;
    dataList<T>*p = fstPoint;
    while (col){
        cout << p->data;
        if (col != 1)
            cout << " ";
        col--;
        p = p->pNext;
    }
}

template <typename T>
void dataList<T>::reverse() {
    if (size <= 1)
        return;
    dataList<T> *p = fstPoint;
    while (p->pNext){
        push_front(p->pNext->data);
        dataList<T> *del = p->pNext;
        p->pNext = del->pNext;
        delete del;
    }
}

template <typename T>
dataList<T>& dataList<T>::operator=(const dataList<T> &other){
    if (!other.fstPoint)
        throw length_error("dataList is empty");
    dataList<T> *clone = new dataList<T>;
    for (int i = 0; i < other.length(); i++){
        clone->push_back(other.get(i));
    }
    return *clone;
}

template <typename T>
dataList<T>::~dataList(){
    if (fstPoint)
        clear();
}

///DATASET CLASS IMPLEMENTATION
Dataset::Dataset() {}

Dataset::~Dataset(){
//    for (int i = 0; i < data->length(); i++){
//        delete data->get(i);
//    }
//    delete []data;
}

int Dataset::getAtIndex(int row, int col) const{
    if (row >= data->length() || col >= data->get(0)->length() || row < 0 || col < 0){
        return -1;
    }
    return data->get(row)->get(col);
}

bool Dataset::loadFromCSV(const char *fileName) {
    string lineData;
    stringstream ss;
    ifstream file(fileName);
    if (file.is_open()) {
        int rNum = 0;
        while (getline(file,lineData))
            rNum++;
        data = new dataList<List<int> *>[rNum];
        file.clear();
        file.seekg(0, ios::beg);
        getline(file, lineData);
        ss << lineData;
        while (getline(ss, lineData, ',')) {
            label.push_back(lineData);
        }
        while (getline(file, lineData)) {
            dataList<int> *newLine = new dataList<int>;
            stringstream s;
            s << lineData;
            while (getline(s, lineData, ','))
                newLine->push_back(stoi(lineData));
            data->push_back(newLine);
        }
        file.close();
        return true;
    }
    return false;
}

Dataset::Dataset(const Dataset &other) {
    data = other.data;
    label = other.label;
//    cout << "Label: " << label.length() << endl;
//    cout << "Other label: " << other.label.length() << endl;
}

Dataset::Dataset(const dataList<int> *inputData) {
    data = new dataList<List<int>*> [inputData->length()];
    for (int i = 0; i < inputData->length(); i++){
        dataList<int> *newData = new dataList<int>;
        newData->push_back(inputData->get(0));
        data->push_back(newData);
    }
}

Dataset& Dataset::operator=(const Dataset& other){
    data = new dataList<List<int> *>[other.data->length()];
    for (int i = 0; i < other.data->length(); i++){
        data->push_back(other.data->get(i));
    }
    for (int i = 0; i < other.label.length(); i++){
        label.push_back(other.label.get(i));
    }
    return *this;
}

void Dataset::printHead(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0)
        return;
    label.print(nCols);
    cout << endl;
    nRows = (nRows > data->length())? data->length() : nRows;
    for (int i = 0; i < nRows; i++){
        ((dataList<int> *)data->get(i))->print(nCols);
        cout << endl;
    }
}

void Dataset::printTail(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0)
        return;
    nRows = (nRows > data->length())? data->length() : nRows;
    nCols = (nCols > data->get(0)->length())? data->get(0)->length() : nCols;
    label.print(nCols);
    cout << endl;
    for (int i = data->length() - nRows; i < data->length(); i++){
        ((dataList<int> *)data->get(i))->print(nCols);
        cout << endl;
    }
}

void Dataset::getShape(int &nRows, int &nCols) const {
    nRows = data->length();
    nCols = data->get(0)->length();
}

void Dataset::columns() const {
    label.print();
}

bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis != 0 && axis != 1)
        return false;
    if (axis){
        int idx = -1;
        for (int i = 0; i < label.length(); i++){
            if (label.get(i) == columns){//Duyệt qua mảng label để
                idx = i;
                break;
            }
        }
        if (idx == -1)
            return false;
        label.remove(idx);
        for (int i = 0; i < data->length(); i++)
            data->get(i)->remove(idx);
    } else{
        if (index < 0 || index >=  data->length())
            return false;
        data->remove(index);
    }
    return true;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    endRow = (endRow == -1)? data->length() - 1 : endRow;//BUG HERE lưu ý, X_train và y_train tạo không thành công nên data k có length
    endCol = (endCol == -1)? data->get(0)->length() - 1 : endCol;
    Dataset extractDataset;
    extractDataset.data = new dataList<List<int> *>[endRow - startRow + 1];
    for (int i = startRow; i <= endRow; i++){
        dataList<int> *newLine = new dataList<int>;
        for (int j = startCol; j <= endCol; j++){
            newLine->push_back(data->get(i)->get(j));
        }
        extractDataset.data->push_back(newLine);
    }
    return extractDataset;
}

kNN::kNN(int k) : k(k){}

void kNN::fit(const Dataset &X_train, const Dataset &y_train) {
    int row,col;
    X_train.getShape(row,col);
    data = X_train.extract(0,-1,0,-1);
    label = y_train.extract(0,-1,0,-1);
}

Dataset kNN::predict(const Dataset &X_test) {
    int row, col, dataRow, dataCol;
    dataList<int> *result = new dataList<int>;
    X_test.getShape(row,col);
    data.getShape(dataRow,dataCol);
    for (int i = 0; i < row; i++){
        dataList<dataList<double> *> *distanceList = new dataList<dataList<double> *>[dataRow];//Mảng để lưu khoảng cách các hình ảnh so vs hình ảnh đối chứng
        for (int r = 0; r < dataRow; r++) {
            double sum = 0;
            dataList<double> *newNode = new dataList<double>;
            for (int c = 0; c < dataCol; c++) {
                sum += pow(X_test.getAtIndex(i,c) - data.getAtIndex(r,c) , 2);
            }
            //cout << "distance hàng i: " << r + 2 << " với hàng: " << i + 42 << " bằng: " << sqrt(sum) << endl;
            newNode->push_back(sqrt(sum));
            newNode->push_back(label.getAtIndex(r,0));
            distanceList->push_back(newNode);
        }
        insertionSort(distanceList);
        dataList<double> num, fre;
        num.push_back(distanceList->get(0)->get(1));
        fre.push_back(1);
        for (int i = 1; i < k; i++){
            for (int j = 0; j < num.length(); j++){
                if (distanceList->get(i)->get(1) == num.get(j)){
                    fre.get(j)++;
                    break;
                }
                if (j == num.length() - 1){
                    num.push_back(distanceList->get(i)->get(1));
                    fre.push_back(1);
                    break;
                }
            }
        }
        int maxLabel = num.get(0), max = fre.get(0), maxidx = 0;
        for (int i = 1; i < num.length(); i++){
            if (fre.get(i) > max){
                maxLabel = num.get(i);
                max = fre.get(i);
                maxidx = i;
            }
        }
        for (int i = 0; i < distanceList->length(); i++){
            delete distanceList->get(i);
        }
        delete []distanceList;
        result->push_back(maxLabel);
    }
    return Dataset(result);
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred) {
    double count = 0.0;
    int row, col;
    y_test.getShape(row,col);
    for (int i = 0; i < row; i++){
        if (y_test.getAtIndex(i,0) == y_pred.getAtIndex(i,0))
            count++;
    }
    return count/row;
}

void train_test_split(Dataset& X, Dataset& y, double test_size,
                      Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test){
    int nRow = 0, nCol = 0;
    X.getShape(nRow,nCol);
    nRow *= test_size;
    X_train = X.extract(0,nRow,0,-1);
    X_test = X.extract(nRow + 1,-1,0,-1);
    y_train = y.extract(0,nRow,0,-1);
    y_test = y.extract(nRow + 1,-1,0,-1);
}

void insertionSort(dataList<dataList<double> *> *l){
    for (int idx = 1; idx < l->length(); idx++){
        if (l->get(idx)->get(0) < l->get(idx-1)->get(0)){//tại mảng vị trí đầu lưu distance, vị trí 2 lưu label
            int i = idx;
            while (l->get(i)->get(0) < l->get(i-1)->get(0)) {
                double temp = l->get(i - 1)->get(0);
                l->get(i - 1)->get(0) = l->get(i)->get(0);
                l->get(i)->get(0) = temp;
                temp = l->get(i - 1)->get(1);
                l->get(i - 1)->get(1) = l->get(i)->get(1);
                l->get(i)->get(1) = temp;
                i--;
                if (!i)
                    break;
            }
        }
    }
}