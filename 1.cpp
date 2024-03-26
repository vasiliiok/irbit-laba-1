#include <iostream>
#include <fstream>
#include <cardmod.h>

class encoder {
private:
    static void swap(int i, int j, unsigned char *const &arr) {
        unsigned char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

private:
    unsigned char s_block_[256] = {0};
    unsigned char *key_ = nullptr;
    size_t key_size_ = 0;

    void allocateKeyMemory(size_t key_size) {
        key_size_ = key_size;
        key_ = new unsigned char[key_size_]{0};
    }

    void clearKeyMemory() {
        delete[] key_;
        key_ = nullptr;
        key_size_ = 0;
    }

    void copyKey(unsigned const char *key) {
        for (int i = 0; i < key_size_; ++i) {
            key_[i] = key[i];
        }
    }

    void init() {
        for (int i = 0; i < 256; ++i) {
            s_block_[i] = i;
        }

        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + s_block_[i] + key_[i % key_size_]) % 256;
            swap(i, j, s_block_);
        }
    }

    struct ByteGenerator {
        int x, y;
        unsigned char s_block[256] = {0};

        explicit ByteGenerator(unsigned char const *s_block_) {
            x = 0;
            y = 0;
            //s_block[256] = {0};

            for (int i = 0; i < 256; ++i) {
                s_block[i] = s_block_[i];
            }
        }

        unsigned char gen()
        {
            x = (x + 1) % 256;
            y = (y + s_block[x]) % 256;

            swap(x, y, s_block);

            return s_block[(s_block[x] + s_block[y]) % 256];
        }
    };

public:
    encoder(unsigned char const *key, int size) {
        allocateKeyMemory(size);
        copyKey(key);
        init();
    }

    void keyMutator(unsigned char const *key, int size) {
        if(key_size_ != size) {
            clearKeyMemory();
            allocateKeyMemory(size);
        }
        copyKey(key);
        init();
    }

    void encode(char const *input_path, char const *output_path) {
        std::ifstream input_file(input_path, std::ios_base::binary);
        std::ofstream output_file(output_path, std::ios_base::binary);
        ByteGenerator generator(s_block_);

        if (input_file.is_open() && output_file.is_open())
        {
            unsigned char ch;
            while (true) {
                ch = input_file.get();
                if (input_file.eof()) break;
                output_file.put(ch ^ generator.gen());
            }
        } else {
            std::cout << "Cannot open file!!";
        }
    }
};

int main() {
    encoder code(reinterpret_cast<const unsigned char *>("123456"), 6);
    code.encode("../test.cpp", "../test.cip");
    code.encode("../test.cip", "../t.cpp");

    //code.encode("../test.cpp", "../test2.cip");
    //code.encode("../test2.cip", "../t2.cpp");

    return 0;
}