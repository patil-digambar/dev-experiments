// templates.cpp contains examples of function templates, class templates,
// template specialization, variadic templates, and perfect forwarding in C++20.

#include<iostream>
// Function template
template<typename T>
void display(const T& value)
{
    std::cout<<value<<std::endl;
}
// class template
template<typename T>
class container{
    T element;
    public:
    container(const T& elem):element(elem){}
    void show() const{
        std::cout<<element<<std::endl;
    }
};
// Full specialization for std::string
template<>
class container<std::string>{
    std::string element;
    public:
    container(const std::string& elem):element(elem){}
    void show() const{
        std::cout<<"String container: "<<element<<std::endl;
    }
};

//partial specialization can also be done for pointer types, arrays etc.
template<typename T>
class container<T*>{
   T* element;
   public:
   container(T* elem):element(elem){}
   void show() const{
       std::cout<<"Pointer container: "<<*element<<std::endl;
   }
};    

//variadic templates basic example
//accessing variadic template arguments using recursion
/*template<typename T, typename ...Args>
void printall(const T& first,const Args& ...args){
    std::cout<<first<<std::endl;
    if constexpr(sizeof...(args)>0) // C++17 feature
    {
        printall(args...);
    }
}

template<typename ...Arges>
void printall(const Arges&... args){
    (std::cout<< ... << args) << "\n"; // Fold expression (C++17)
}
*/
template<typename... Args>
void printall(const Args&... args){
    (std::cout<< ... << args) << "\n"; // Fold expression (C++17)
}
 
// perfect forwarding and type deduction
template<typename T>
void  func(T&& arg){
   
    if constexpr(std::is_lvalue_reference_v<T>){
        std::cout<<"lvalue reference"<<std::endl;
    }else{
        std::cout<<"rvalue reference"<<std::endl;
    }
    std::cout<<"Type of arg: "<<typeid(arg).name()<<std::endl;
    //return arg;
}

//perfecrt forwarding
template<typename T>
void wrapper(T&& arg){
    func(std::forward<T>(arg));
}

int main()
{
    std::cout<<"This is template file"<<std::endl;
    display(10); // int
    display(15.5); // double
    display("Hello, Templates!"); // const char*

    container<int> intContainer(42);
    intContainer.show();
    container<std::string> stringContainer("Hello, World!");
    stringContainer.show();

    container<int*> ptrContainer(new int(100));
    ptrContainer.show();
    printall(1,2.3,"Test",std::string("variadic"));

    int x = 20;
    wrapper(x); // lvalue, T deduced as int&
    wrapper(30.3); // rvalue, T deduced as int&&    

    return 0;
}