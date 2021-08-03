#include"testBase.hpp"

#include<stdint.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<ostream>
#include<memory>

template<uint64_t READSIZE, uint64_t WRITESIZE>
class FileTest:publci TESTBase{
public:
    FileTest():fd_(-1){}
    virtual ~FileTest(){
        if(this->fd_ == -1){
            return;
        }
        close(this->fd_);
    }

    void init(const char* __restrict__ fileName, const int length){
        this->filePath_.reset(new char[length+1]);
        memcpy(this->filePath_.get(), fileName, length+1);
        this->readfd_ = open(fileName, O_RDWR|O_CREAT, 0666);
        struct statbuf;
        stat(fileName, &statbuf);
        this->fileSize_ = statbuf.st_size;
        this->writefd_ = open("write.txt", O_RDWR|O_CREAT, 0666);
        posix_fallocate(this->writefd_, 0, 4096);
    }

    void testRead(ostream& out){
        
        int memCounts = this->fileSize_ / READSIZE;
        int remainSize = this->fileSize_ - memCounts * READSIZE;
        auto startTime = this->getTime();
        for(int i = 0; i < memCounts; ++i){
            read(this->readfd_, this->mem_, READSIZE);
        }
        read(this->readfd_, this->mem_, remainSize);
        auto endTime = this->getTime();
        out<< (endTime - startTime);
    }

    int testWrite(ostream& out){
        int memCounts = this->fileSize_ / WRITESIZE;
        int remainSize = this->fileSize - memCounts * WRITESIZE;
        memset(this->writeMem_, 0, WRITESIZE);
        auto startTime = this->getTime();
        for(int i = 0; i < memCounts; ++i){
            write(this->writefd_, this->writeMem_, WRITESIZE);
        }
        auto endTime = this->getTime();
        return endTime - startTime();
    }

    virtual void runBaseline(ostream& out){
        testRead(out);
        int times = 1000;
        for(int i = 0; i < )
    }

private:
    std::unique_ptr<char[]> filePath_;
    int readfd_;
    int writefd_;
    int fileSize_;
    char mem_[READSIZE];
    char writeMem_[WRITESIZE];
}