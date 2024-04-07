#include <iostream>
#include <vector>
#include <cstring>

class BinaryHeap {
private:
    std::vector<char*> heap_;
    size_t virtual_size_ = 16;
    size_t physical_size_ = 0;

    void addPlace() {
        virtual_size_ *= 2;
        heap_.reserve(virtual_size_);
    }

    void copy(BinaryHeap const &obj) {
        for (auto elm : obj.heap_) {
            heap_.push_back(
                    new char[std::strlen(elm) + 1]);
            std::strcpy(heap_.back(), elm);
            ++physical_size_;
        }
    }

    void clearMemory() {
        for (auto elm : heap_) {
            delete [] elm;
        }
        physical_size_ = 0;
        heap_.clear();
    }

private:
    void sift_up(int index) {
        // While element smaller than his parent,
        // we swap their, and restart with parent
        while (index > 0 && std::strcmp(heap_[index / 2], heap_[index])) {
            std::swap(heap_[index], heap_[index / 2]);
            index /= 2;
        }
    }

    void sift_down(int index) {
        // While element bigger than his child,
        // we swap their, and restart with child
        while (2 * index < physical_size_) {
            int left = 2 * index + 1; // left son
            int right = 2 * index + 2; // right son

            int choice = left;
            // If right is existing and smaller - choice him
            if (right <= physical_size_ && std::strcmp(heap_[left], heap_[right])) {
                choice = right;
            }

            if (heap_[index] <= heap_[choice]) {
                //Condition is fulfilled - exit
                break;
            }

            std::swap(heap_[index], heap_[choice]);
            index = choice;
        }
    }

public:
    BinaryHeap() {
        heap_.reserve(virtual_size_);
    }

    // Copy constructor
    BinaryHeap(BinaryHeap const &obj) {
        virtual_size_ = obj.virtual_size_;
        heap_.reserve(virtual_size_);
        copy(obj);
    }

    // Assigned operator
    BinaryHeap &operator=(BinaryHeap const &obj) {
        clearMemory();
        virtual_size_ = obj.virtual_size_;
        heap_.reserve(virtual_size_);
        copy(obj);
        return *this;
    }

    ~BinaryHeap() {
        clearMemory();
    }

public:
    void getMin(char* pointer) {
        std::strcpy(pointer, heap_.front());
    }

    void takeMin(char* pointer) {
        std::strcpy(pointer, heap_.front());
        std::swap(heap_.front(), heap_.back());

        delete [] heap_.back();
        heap_.pop_back();
        --physical_size_;

        sift_down(0);
    }

    void add(char* string) {
        if (physical_size_ == virtual_size_) {
            addPlace();
        }

        heap_.push_back(
                new char[std::strlen(string) + 1]);
        ++physical_size_;
        std::strcpy(heap_.back(), string);

        sift_up(physical_size_ - 1);
    }

    void mergeQueues(BinaryHeap const &queue_1, BinaryHeap const &queue_2) {
        clearMemory();

        virtual_size_ = queue_1.virtual_size_ +
                        queue_2.virtual_size_;
        heap_.reserve(virtual_size_);

        copy(queue_1);
        copy(queue_2);

        for (int i = physical_size_ - 1; i >= 0; --i) {
            sift_down(i);
        }
    }
};

int main() {

}