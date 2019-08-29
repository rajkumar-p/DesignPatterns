#include "delegate.hpp"
#include <iostream>

TextData::TextData(const std::string &s, std::unique_ptr<SpellChecker> sc)
    : _data(s), _spell_checker(std::move(sc))
{
    std::cout <<"TextData::TextData()"<<std::endl;
}

TextData::TextData(const TextData &other)
    : _data(other._data),
    _spell_checker(new SpellChecker(*other._spell_checker))
{

}

TextData& TextData::operator=(const TextData &other)
{
    if (this != &other) {
        this->_data.clear();
        this->_data = other._data;

        this->_spell_checker.release();
        this->_spell_checker =
                std::make_unique<SpellChecker>(*other._spell_checker);
    }

    return *this;
}

TextData::~TextData()
{
    std::cout <<"TextData::~TextData()"<<std::endl;
}

std::string TextData::get_data()
{
    std::cout <<"TextData::get_data()"<<std::endl;
    return _data;
}

void TextData::set_spell_checker(std::unique_ptr<SpellChecker> sc)
{
    std::cout <<"Changing Spell Checker."<<std::endl;
    this->_spell_checker = std::move(sc);
}

void TextData::spell_check()
{
    std::cout <<"TextData::spell_check()"<<std::endl;
    std::cout <<"Spell checking text data."<<std::endl;
    _spell_checker->spell_check(this->get_data());
}

SpellChecker::SpellChecker()
{

}

SpellChecker::~SpellChecker()
{

}

std::vector<std::string> SpellChecker::spell_check(const std::string &data)
{
    std::cout <<"SpellChecker::spell_check()"<<std::endl;
    std::cout <<"SpellChecking : "<<data<<std::endl;
    return {};
}

std::vector<std::string> AdvancedSpellChecker::spell_check(const std::string &data)
{
    std::cout <<"AdvancedSpellChecker::spell_check()"<<std::endl;
    std::cout <<"Advanced SpellChecking : "<<data<<std::endl;
    return {};
}

