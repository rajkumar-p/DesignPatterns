#include <experimental/filesystem>
#include <sys/stat.h>
#include "strategy.hpp"

DiskJanitor::DiskJanitor(std::unique_ptr<FilesPurger> purger)
    : _purger(std::move(purger))
{

}

void DiskJanitor::clean_files(const std::string &root)
{
    _purger->purge(root);
}

FilesPurger::~FilesPurger()
{

}

MTFilesPurger::MTFilesPurger(const time_t rel_time)
    : _rel_time(rel_time)
{

}

void MTFilesPurger::purge(const std::string &root)
{
    namespace fs = std::experimental::filesystem;
    fs::path root_path(root);
    if (fs::exists(root_path) && fs::is_directory(root_path)) {
        for (const fs::directory_entry &entry :
                fs::recursive_directory_iterator(root_path)) {
            if (entry.is_directory()) {
                continue;
            }

            std::string path = entry.path();
            struct stat st;
            if (stat(path.c_str(), &st) != -1) {
                time_t at = st.st_mtimespec.tv_sec;
                double diff = difftime(at, _rel_time);
                if (diff < 0) {
                    fs::remove(path);
                }
            }
        }
    }
}

ATFilesPurger::ATFilesPurger(const time_t rel_time)
    : _rel_time(rel_time)
{

}

void ATFilesPurger::purge(const std::string &root)
{
    namespace fs = std::experimental::filesystem;
    fs::path root_path(root);
    if (fs::exists(root_path) && fs::is_directory(root_path)) {
        for (const fs::directory_entry &entry :
                fs::recursive_directory_iterator(root_path)) {
            if (entry.is_directory()) {
                continue;
            }

            std::string path = entry.path();
            struct stat st;
            if (stat(path.c_str(), &st) != -1) {
                time_t at = st.st_atimespec.tv_sec;
                double diff = difftime(at, _rel_time);
                if (diff < 0) {
                    fs::remove(path);
                }
            }
        }
    }
}

SZFilesPurger::SZFilesPurger(size_t limit)
    : _limit(limit)
{

}

void SZFilesPurger::purge(const std::string &root)
{
    namespace fs = std::experimental::filesystem;
    fs::path root_path(root);
    if (fs::exists(root_path) && fs::is_directory(root_path)) {
        for (const fs::directory_entry &entry :
                fs::recursive_directory_iterator(root_path)) {
            if (entry.is_directory()) {
                continue;
            }

            std::string path = entry.path();
            struct stat st;
            if (stat(path.c_str(), &st) != -1) {
                size_t sz = st.st_size;
                if (sz > _limit) {
                    fs::remove(path);
                }
            }
        }
    }
}

