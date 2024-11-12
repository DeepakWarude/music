#include <iostream>
#include <mutex>

int mutex = 1;
int full = 0;
int empty = 3;
int producedItem = 0;  // Variable to store the produced item

int wait(int s) {
    return s - 1;  
}

int signal(int s) {
    return s + 1;  
}

void producer() {
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    
    producedItem++;  // Increment the produced item
    std::cout << "\nProducer produces the item: " << producedItem;
    
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    
    std::cout << "\nConsumer consumes the item: " << producedItem;
    producedItem--;  // Decrement the produced item
    
    mutex = signal(mutex);
}

int main() {
    int n;

    std::cout << "1. Producer\n2. Consumer\n";
    while (true) {
        std::cout << "\nEnter your choice: ";
        std::cin >> n;
        
        switch (n) {
            case 1: 
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    std::cout << "Buffer is full\n";
                }
                break;

            case 2: 
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    std::cout << "Buffer is empty\n";
                }
                break;

            default:
                std::cout << "Invalid choice\n";
                break;
        }
        
        // Display the current status
        std::cout << "\nCurrent produced item count: " << producedItem;
    }
    
    return 0;
}
