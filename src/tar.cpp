/*
* copy from https://github.com/lindenb/cclindenb/blob/master/src/core/lindenb/io/tarball.cpp
*/
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <ctime>
#include <fstream>
#include "TarClass.h"
namespace LOCALNS = LibTar;

#define TARHEADER static_cast<LOCALNS::PosixTarHeader*>(header)
#define THROW(x) std::cout << x


#pragma warning(disable : 4996)

void LOCALNS::Tar::_init(void* header)
{
    std::memset(header, 0, sizeof(PosixTarHeader));
    std::strcpy(TARHEADER->magic, "ustar");
    std::strcpy(TARHEADER->version, " ");
    std::sprintf(TARHEADER->mtime, "%011lo", static_cast<unsigned long>(time(NULL)));
    std::sprintf(TARHEADER->mode, "%07o", 0644);
    std::sprintf(TARHEADER->gname, "%s", "users");
}

void LOCALNS::Tar::_checksum(void* header)
{
    unsigned int sum = 0;
    char *p = (char *)header;
    char *q = p + sizeof(PosixTarHeader);
    while (p < TARHEADER->checksum) sum += *p++ & 0xff;
    for (int i = 0; i < 8; ++i) {
        sum += ' ';
        ++p;
    }
    while (p < q) sum += *p++ & 0xff;

    std::sprintf(TARHEADER->checksum, "%06o", sum);
}

void LOCALNS::Tar::_size(void* header, unsigned long fileSize)
{
    std::sprintf(TARHEADER->size, "%011llo", (long long unsigned int)fileSize);
}

void LOCALNS::Tar::_filename(void* header, const char* filename)
{
    if (filename == NULL || filename[0] == 0 || std::strlen(filename) >= 100)
    {
        THROW("invalid archive name \"" << filename << "\"");
    }
    std::snprintf(TARHEADER->name, 100, "%s", filename);
}

void LOCALNS::Tar::_endRecord(std::size_t len)
{
    char c = '\0';
    while ((len % sizeof(PosixTarHeader)) != 0)
    {
        out.write(&c, sizeof(char));
        ++len;
    }
}


LOCALNS::Tar::Tar(std::iostream& _out)
    : _finished(false)
    , out(_out)
{
    if (sizeof(PosixTarHeader) != 512)
    {
        THROW(sizeof(PosixTarHeader));
    }
}

LOCALNS::Tar::~Tar()
{
    if (!_finished)
    {
        std::cerr << "[warning]tar file was not finished." << std::endl;
    }
}

/** writes 2 empty blocks. Should be always called before closing the Tar file */
void LOCALNS::Tar::finish()
{
    _finished = true;
    //The end of the archive is indicated by two blocks filled with binary zeros
    PosixTarHeader header;
    std::memset((void*)&header, 0, sizeof(PosixTarHeader));
    out.write((const char*)&header, sizeof(PosixTarHeader));
    out.write((const char*)&header, sizeof(PosixTarHeader));
    out.flush();
}

void LOCALNS::Tar::put(const char* filename, const std::string& s)
{
    put(filename, s.c_str(), s.size());
}
void LOCALNS::Tar::put(const char* filename, const char* content)
{
    put(filename, content, std::strlen(content));
}

void LOCALNS::Tar::put(const char* filename, const char* content, std::size_t len)
{
    PosixTarHeader header;
    _init((void*)&header);
    _filename((void*)&header, filename);
    header.typeflag[0] = 0;
    _size((void*)&header, static_cast<unsigned long>(len));
    _checksum((void*)&header);
    out.write((const char*)&header, sizeof(PosixTarHeader));
    out.write(content, len);
    _endRecord(len);
}

void LOCALNS::Tar::putFile(const char* filename, const char* nameInArchive)
{
    char buff[BUFSIZ];
    std::FILE* in = std::fopen(filename, "rb");
    if (in == NULL)
    {
        THROW("Cannot open " << filename << " " << std::strerror(errno));
    }
    std::fseek(in, 0L, SEEK_END);
    long int len = std::ftell(in);
    std::fseek(in, 0L, SEEK_SET);

    PosixTarHeader header;
    _init((void*)&header);
    _filename((void*)&header, nameInArchive);
    header.typeflag[0] = 0;
    _size((void*)&header, len);
    _checksum((void*)&header);
    out.write((const char*)&header, sizeof(PosixTarHeader));


    std::size_t nRead = 0;
    while ((nRead = std::fread(buff, sizeof(char), BUFSIZ, in))>0)
    {
        out.write(buff, nRead);
    }
    std::fclose(in);

    _endRecord(len);
}

void LOCALNS::Tar::readToFile(const std::string& outputDir, std::istream& in)
{
    char zeroBlock[512];
    memset(zeroBlock, 0, 512);
    while (in)
    {
        // read tar header
        PosixTarHeader tarHeader;
        in.read((char *)(void *)&(tarHeader), sizeof(PosixTarHeader));
        //When a block with zeroes-only is found, the TAR archive ends here
        if (memcmp(&tarHeader, zeroBlock, 512) == 0)
        {
            THROW("Found TAR end\n");
            break;
        }
        //Normal file
        if (0 == *(tarHeader.typeflag) || '\0' == *(tarHeader.typeflag))
        {
            size_t fileSize = decodeTarOctal(tarHeader.size);
            char* fileData = new char[fileSize]; //+1: Place a terminal NUL to allow interpreting the file as cstring (you can remove this if unused)
            in.read(fileData, fileSize);
            // check file path size
            std::string filePath(outputDir);
            filePath.append("\\").append(tarHeader.name);
            std::fstream out(filePath.c_str(), std::ios::out | std::ios::binary);
            out.write(fileData, fileSize);
            delete[] fileData;
            //In the tar archive, entire 512-byte-blocks are used for each file
            //Therefore we now have to skip the padded bytes.
            size_t paddingBytes = (512 - (fileSize % 512)) % 512; //How long the padding to 512 bytes needs to be
                                                              //Simply ignore the padding
            in.ignore(paddingBytes);
        }
    }
}

static uint64_t LOCALNS::decodeTarOctal(char* data, size_t size)
{
#define ASCII_TO_NUMBER(num) ((num)-48) //Converts an ascii digit to the corresponding number (assuming it is an ASCII digit)
    unsigned char* currentPtr = (unsigned char*)data + size;
    uint64_t sum = 0;
    uint64_t currentMultiplier = 1;
    //Skip everything after the last NUL/space character
    //In some TAR archives the size field has non-trailing NULs/spaces, so this is neccessary
    unsigned char* checkPtr = currentPtr; //This is used to check where the last NUL/space char is
    for (; checkPtr >= (unsigned char*)data; checkPtr--) {
        if ((*checkPtr) == 0 || (*checkPtr) == ' ') {
            currentPtr = checkPtr - 1;
        }
    }
    for (; currentPtr >= (unsigned char*)data; currentPtr--) {
        sum += ASCII_TO_NUMBER(*currentPtr) * currentMultiplier;
        currentMultiplier *= 8;
    }
    return sum;
}
