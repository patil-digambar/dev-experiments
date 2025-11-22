#include <iostream>
#include <algorithm>

class buffer
{
private:
    int* ptr; // dynamic memory pointer
    int size;

public:
    // Default constructor
    buffer() : size(5), ptr(new int[5]) {}

    // Parameterized constructor
    buffer(int sz) : size(sz), ptr(new int[sz]) {}

    // Copy constructor (deep copy)
    buffer(const buffer& other) : size(other.size), ptr(new int[other.size])
    {
        std::copy(other.ptr, other.ptr + other.size, ptr); // copy elements
        // Deep copy avoids double delete
    }

    // Copy assignment operator (deep copy + self-assignment guard)
    buffer& operator=(const buffer& other) noexcept
    {
        if (this != &other) // self-assignment guard
        {
            delete[] ptr; // free current memory
            size = other.size;
            ptr = new int[size];
            std::copy(other.ptr, other.ptr + size, ptr);
        }
        // Note: copy-and-swap idiom could be used for strong exception safety
        return *this;
    }

    // Move constructor (transfer ownership)
    buffer(buffer&& other) noexcept : size(other.size), ptr(other.ptr)
    {
        other.ptr = nullptr; // nullify source to avoid double delete
        other.size = 0;
    }

    // Move assignment operator (transfer ownership + self-move guard)
    buffer& operator=(buffer&& other)
    {
        if (this != &other) // self-move guard
        {
            delete[] ptr;    // free current memory
            size = other.size;
            ptr = other.ptr; // take ownership
            other.ptr = nullptr; // nullify source
            other.size = 0;
        }
        return *this;
    }

    // Destructor
    ~buffer()
    {
        delete[] ptr; // free dynamic memory
    }
};

int main()
{
    buffer buf(10);            // parameterized constructor
    buffer buf1 = buf;         // copy constructor (deep copy)
    buffer buf2;               // default constructor
    buf2 = buf1;               // copy assignment (deep copy)

    buffer buf3 = std::move(buf2); // move constructor
    buf1 = std::move(buf);         // move assignment

    // Tricky / interview notes:
    // 1. Using a moved-from object is only safe to assign to or destroy.
    // 2. Shallow copy (copying ptr pointer only) would cause double delete.
    // 3. Move constructor and move assignment should be noexcept for STL containers.
    // 4. Self-copy / move assignment must be guarded with if(this != &other).
    // 5. STL vectors move elements if move constructor exists and is noexcept; else fallback to copy.
    // 6. Destructor safely handles moved-from object (delete nullptr is safe).
    // 7. Accessing moved-from ptr is unsafe (undefined behavior).
    // 8. Implicit copy/move generation can be dangerous for classes with dynamic memory.

    return 0;
}
