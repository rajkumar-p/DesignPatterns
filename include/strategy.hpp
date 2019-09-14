#ifndef DESIGNPATTERNS_STRATEGY_HPP
#define DESIGNPATTERNS_STRATEGY_HPP

#include <memory>
#include <string>

class FilesPurger;

class DiskJanitor {
private:
    std::unique_ptr<FilesPurger> _purger;
public:
    DiskJanitor(std::unique_ptr<FilesPurger> purger);

    void clean_files(const std::string &root);
};

class FilesPurger {
public:
    virtual ~FilesPurger();
    virtual void purge(const std::string &root) = 0;
};

class MTFilesPurger : public FilesPurger {
private:
    time_t _rel_time;

public:
    MTFilesPurger(const time_t rel_time);

    void purge(const std::string &root) override;
};

class ATFilesPurger : public FilesPurger {
private:
    time_t _rel_time;

public:
    ATFilesPurger(const time_t rel_time);

    void purge(const std::string &root) override;
};

class SZFilesPurger : public FilesPurger {
private:
    size_t _limit;

public:
    SZFilesPurger(size_t limit);

    void purge(const std::string &root) override;
};

#endif //DESIGNPATTERNS_STRATEGY_HPP
