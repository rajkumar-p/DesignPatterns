#include <experimental/filesystem>
#include <iostream>
#include <sys/stat.h>
#include "strategy.hpp"

DiskJanitor::DiskJanitor(std::unique_ptr<FilesPurger> purger)
    : _purger(std::move(purger))
{

}

void DiskJanitor::clean_files(const std::string &root, bool recursive)
{
    _purger->purge(root, recursive);
}

FilesPurger::~FilesPurger()
{

}

MTFilesPurger::MTFilesPurger(const time_t rel_time)
    : _rel_time(rel_time)
{

}

void MTFilesPurger::purge(const std::string &root, bool recursive)
{

}

ATFilesPurger::ATFilesPurger(const time_t rel_time)
    : _rel_time(rel_time)
{

}

void ATFilesPurger::purge(const std::string &root, bool recursive)
{

}

SZFilesPurger::SZFilesPurger(size_t limit)
    : _limit(limit)
{

}

void SZFilesPurger::purge(const std::string &root, bool recursive)
{
    namespace fs = std::experimental::filesystem;
    fs::path root_path(root);
    if (fs::exists(root_path) && fs::is_directory(root_path)) {
        for (const fs::directory_entry &entry : fs::recursive_directory_iterator(root_path)) {
            std::string path = entry.path();

            struct stat st;
            if (stat(path.c_str(), &st) != -1) {
                size_t sz = st.st_size;
                time_t at = st.st_atimespec.tv_sec;
                time_t mt = st.st_mtimespec.tv_sec;

                std::cout << path << "\t" << sz
                    << "\t" << at << "\t" << mt
                    << std::endl;
            }
        }
    }
}

