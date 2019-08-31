#ifndef DESIGNPATTERNS_DELEGATE_HPP
#define DESIGNPATTERNS_DELEGATE_HPP

#include <set>
#include <vector>
#include <string>

class SpellChecker;
class TextData {
private:
    std::string _data;
    std::unique_ptr<SpellChecker> _spell_checker;

public:
    TextData(const std::string &s,
            std::unique_ptr<SpellChecker> sc);
    TextData(const TextData &other);
    TextData& operator=(const TextData &other);
    ~TextData();

    std::string get_data();

    void set_spell_checker(std::unique_ptr<SpellChecker> sc);

    void spell_check();
};

class SpellChecker {
private:
    std::set<std::string> _dict;

public:
    SpellChecker();
    virtual ~SpellChecker();

    virtual std::vector<std::string> spell_check(const std::string &data);
};

class AdvancedSpellChecker : public SpellChecker {
    std::vector<std::string> spell_check(const std::string &data);
};

class StorageManager {
    virtual int save(const std::string &loc,
            const TextData &text_data) = 0;
};

class TextFileStorageManager : public StorageManager {
    int save(const std::string &loc,
             const TextData &text_data);
};

class PdfFileStorageManager : public StorageManager {
    int save(const std::string &loc,
             const TextData &text_data);
};

#endif //DESIGNPATTERNS_DELEGATE_HPP
