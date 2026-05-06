#include <iostream>
#include <string>
#include <algorithm>

class smartBuffer {
    private:
    int* data;
    size_t bufferSize;
    std::string tag;

    public:
    smartBuffer(size_t size,std::string name)
    : bufferSize(size),tag(std::move(name)) {

        data = new int[bufferSize];
        for(size_t i = 0;i<bufferSize;i++) {
            data[i] = 0;
        }
        
        std::cout << "[Constructor] '" << tag << "' created. " 
                  << bufferSize * sizeof(int) << " bytes allocated.\n";
    }

    ~smartBuffer() {
        if(data!=nullptr) {
            delete[] data;
            data = nullptr;
        }
         std::cout << "[Destructor] '" << tag << "' destroyed. Memory released.\n";
    }

    
    void setValue(int index, int value);
    void displayStatus() const;
};

void smartBuffer::setValue(int index,int value) {
    if(!(index<bufferSize)) {
        std::cerr << "[Error] Invalid Index: " << index << " (Boundary check failed)" << std::endl;
        return;
    }
    data[index] = value;
}

void smartBuffer::displayStatus() const {
     std::cout << "Buffer Tag: " << tag << " | Size: " << bufferSize << " elements.\n";
}


int main() {
    std::cout << "--- Program Started ---\n" << std::endl;

    {
        
        smartBuffer myLocalBuffer(3, "Local_Stack_Buffer");
        myLocalBuffer.setValue(0, 100);
        myLocalBuffer.setValue(1, 200);
        myLocalBuffer.setValue(5, 999);
        myLocalBuffer.displayStatus();
        
        
    } 

    std::cout << "\n--- Program Ended ---\n" << std::endl;
    return 0;
}