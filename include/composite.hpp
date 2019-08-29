#ifndef DESIGNPATTERNS_COMPOSITE_HPP
#define DESIGNPATTERNS_COMPOSITE_HPP

#include <string>
#include <vector>

enum ReadWriteError { Invalid = -1 };
enum FileType { Regular, Directory };

class File {
public:
    File(const std::string &name, const int permissions);
    virtual ~File();

    virtual int get_file_type() const = 0;

    virtual std::string get_name() const;
    virtual size_t get_size() const = 0;
    virtual int get_permissions() const;

    virtual void add(std::unique_ptr<File> file);
    virtual void remove(std::unique_ptr<File> file);

    virtual int read(std::string &buf, const size_t count) = 0;
    virtual int write(const std::string &data) = 0;

private:
    std::string _name;
    int _permissions;
};

class RegularFile : public File {
public:
    RegularFile(const std::string &name, int permissions);
    ~RegularFile();

    int get_file_type() const;

    std::string get_name() const;
    size_t get_size() const;
    int get_permissions() const;

    int read(std::string &buf, const size_t count);
    int write(const std::string &data);

private:
    std::string _content;
};

class DirectoryFile : public File {
public:
    DirectoryFile(const std::string &name, int permissions);
    ~DirectoryFile();

    int get_file_type() const;

    std::string get_name() const;
    size_t get_size() const;
    int get_permissions() const;

    void add(std::unique_ptr<File> file);
    void remove(std::unique_ptr<File> file);

    int read(std::string &buf, const size_t count);
    int write(const std::string &data);
private:
    std::vector<std::unique_ptr<File>> _files;
};

#endif //DESIGNPATTERNS_COMPOSITE_HPP
