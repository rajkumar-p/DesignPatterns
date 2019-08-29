#include <iostream>
#include "composite.hpp"

/*
 * File Methods
 */
File::File(const std::string &name, const int permissions)
    : _name(name), _permissions(permissions)
{

}

File::~File()
{

}

std::string File::get_name() const
{
    return _name;
}

int File::get_permissions() const
{
    return _permissions;
}

void File::add(std::unique_ptr<File> file)
{
    std::cout << "Error: Not Implemented." << std::endl;
}

void File::remove(std::unique_ptr<File> file)
{
    std::cout << "Error: Not Implemented." << std::endl;
}

/*
 * RegularFile Methods
 */
RegularFile::RegularFile(const std::string &name, int permissions)
    : File(name, permissions), _content("")
{

}

RegularFile::~RegularFile()
{

}

int RegularFile::get_file_type() const
{
    return FileType::Regular;
}

std::string RegularFile::get_name() const
{
    return File::get_name();
}

size_t RegularFile::get_size() const
{
    return _content.size();
}

int RegularFile::get_permissions() const
{
    return File::get_permissions();
}

int RegularFile::read(std::string &buf, const size_t count)
{
    count < this->get_size() ? buf = _content.substr(count) : buf = _content;
    return buf.size();
}

int RegularFile::write(const std::string &data)
{
    _content += data;
    return data.size();
}

/*
 * DirectoryFile Methods
 */
DirectoryFile::DirectoryFile(const std::string &name, int permissions)
    : File(name, permissions)
{

}

DirectoryFile::~DirectoryFile()
{

}

int DirectoryFile::get_file_type() const
{
    return FileType::Directory;
}

std::string DirectoryFile::get_name() const
{
    return File::get_name();
}

size_t DirectoryFile::get_size() const
{
    size_t total = 0;
    for (size_t i = 0; i < _files.size(); ++i) {
        total += _files[i]->get_size();
    }

    return total;
}

int DirectoryFile::get_permissions() const
{
    return File::get_permissions();
}

void DirectoryFile::add(std::unique_ptr<File> file)
{
    _files.push_back(std::move(file));
}

void DirectoryFile::remove(std::unique_ptr<File> file)
{
    for (size_t i = 0; i < _files.size(); ++i) {
        if (file->get_name() == _files[i]->get_name()) {
            _files.erase(_files.begin() + i);
            return;
        }
    }
}

int DirectoryFile::read(std::string &buf, const size_t count)
{
    return ReadWriteError::Invalid;
}

int DirectoryFile::write(const std::string &data)
{
    return ReadWriteError::Invalid;
}
