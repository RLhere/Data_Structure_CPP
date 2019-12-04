/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-12-04 15:27:48
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-12-04 16:24:25
 */
#include"./vector.h"
using namespace std;

typedef int Rank;//秩
#define DEFAULT_CAPACITY    3//默认的初始容量

template <typename T> class Vector {//向量模板类
    protected:
        Rank _size; int _capacity;  T* _elem;//规模、容量、数据区
        void copyFrom(T const* A, Rank lo, Rank hi)//复制数组区间A[lo, hi)
        {
            this->_elem = A;
            for(int i = lo; i < hi; i++)
            {
                *(_elem + i) = *(A + i);
            }
        }
        void expand();//空间不足时扩容
        void shrink();//装填因子过小时压缩
        bool bubble(Rank lo, Rank hi);//扫描交换
        void bubbleSort(Rank lo, Rank hi);//起泡排序算法
        Rank max(Rank lo, Rank hi)//选取最大元素
        {
            int maxrank = lo;
            int max = *(this->_elem + lo);
            for(int i = lo; i < hi; i++)
            {
                if(*(this->_elem + i) > max)
                {
                    max = *(this->_elem + i);
                    maxrank = i;
                }
            }
            return maxrank
        }
        void selectionSort(Rank lo, Rank hi);//选取排序算法
        void merge(Rank lo, Rank mi, Rank hi);//归并算法
        void mergeSort(Rank lo, Rank hi);//归并排序算法
        Rank partition(Rank lo, Rank hi);//轴点构造算法
        void quickSort(Rank lo, Rank hi);//快速排序算法
        void heapSort(Rank lo, Rank hi);//堆排序

    public:
    //构造函数
        Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为c、规模为s、所有元素初始为v
        {
            _elem = new T[_capacity = c];
            for(_size = 0; _size < s; _elem[_size++] = v);
        }// s <= c
        Vector(T const* A, Rank lo, Rank hi) {  copyFrom(A, lo, hi); }//数组区间复制
        Vector(T const* A, Rank n) {  copyFrom(A, 0, n); }//数组整体复制
        Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//向量区间复制
        Vector(Vector<T> const& V) {  copyFrom(V._elem, 0, V._size); }//向量整体复制
    //析构函数
        ~Vector() {  delete [] _elem; }//释放内部空间
    //只读访问接口
        Rank size() const { return _size; }//规模
        bool empty() const { return !_size; }//判空
        int disordered() const//判断向量是否已排序
        {
            int flag = 1;
            if(*(this->_elem) < *(this->_elem + 1))
            {
                for(int i = this->lo; i < this->hi - 1; i++)
                {
                    if(*(this->lo + i) > *(this->lo + i + 1))
                        flag = 0;
                }
                return flag;
            }
            if(*(this->_elem) > *(this->_elem + 1))
            {
                for(int i = this->lo; i < this->hi - 1; i++)
                {
                    if(*(this->lo + i) < *(this->lo + i + 1))
                        flag = 0;
                }
                return flag;
            }
        }
        Rank find(T const& e) const {  return find(e, 0, _size); }//无序向量整体查找
        Rank find(T const& e, Rank lo, Rank hi) const//无序向量区间查找
        {
            int i;
            for(i = lo; i < hi; i++)
            {
                if(e == *(this->_elem + i))
                {
                    return i;
                }
            }
            if(i == hi)
            {
                return -1;
            }
        }
        Rank search(T const& e) const//有序向量整体查找
        {  return (0 >= _size) ? -1 : search(e, 0, _size); }


        Rank search(T const& e, Rank lo, Rank hi) const//有序向量区间查找
        {
            int mid = (lo + hi) >> 1;
            
        }


    //可写访问接口
        T& operator[](Rank r) const;//重载下标操作符，可以类似于数组形式引用各元素
        Vector<T> & operator=(Vector<T> const&);//重载赋值操作符，以便直接克隆向量
        T remove(Rank r);//删除秩为r的元素
        int remove(Rank lo, Rank hi);//删除秩在区间[lo, hi)之内的元素
        Rank insert(Rank r, T const& e);//插入元素
        Rank insert(T const& e) {  return insert(_size, e);  }//默认作为末元素插入
        void sort(Rank lo, Rank hi);//对[lo, hi)排序
        void sort() {  sort(0, _size);  }//整体排序
        void unsort(Rank lo, Rank hi);//对[lo, hi)置乱
        void unsort() {  unsort(0, _size);  }//整体置乱
        int deduplicate();//无序去重
        int uniquify();//有序去重
    //遍历
        void traverse(void (*)(T&));//遍历(使用函数指针，只说或局部性修改)
        template <typename VST> void traverse(VST&);//遍历(使用函数对象，可全局性修改)

};//Vector