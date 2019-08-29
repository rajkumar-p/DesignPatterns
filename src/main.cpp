#include <iostream>
#include "composite.hpp"
#include "delegate.hpp"

void delegate()
{
    TextData text_data("Some data.",
                       std::unique_ptr<SpellChecker>(new SpellChecker()));
    text_data.spell_check();
    text_data.set_spell_checker(
            std::unique_ptr<SpellChecker>(new AdvancedSpellChecker()));
    text_data.spell_check();
}

void composite()
{
    std::unique_ptr<File> home(
            std::make_unique<DirectoryFile>("/users/raj", 700)
    );

    std::unique_ptr<File> f1(
            std::make_unique<RegularFile>("file1", 644)
    );
    std::unique_ptr<File> f2(
            std::make_unique<RegularFile>("file2", 644)
    );
    f1->write("Hello");
    f2->write("World!!!");

    home->add(std::move(f1));
    home->add(std::move(f2));

    std::cout << home->get_name() << "|" << home->get_permissions() << "|" <<
              home->get_size() << std::endl;

    std::unique_ptr<File> tmp(
            std::make_unique<DirectoryFile>("/users/raj/tmp", 700)
    );

    std::unique_ptr<File> f3(
            std::make_unique<RegularFile>("file3", 644)
    );
    std::unique_ptr<File> f4(
            std::make_unique<RegularFile>("file4", 644)
    );
    f3->write("Good");
    f4->write("Day");

    tmp->add(std::move(f3));
    tmp->add(std::move(f4));

    std::cout << tmp->get_name() << "|" << tmp->get_permissions() << "|" <<
              tmp->get_size() << std::endl;

    home->add(std::move(tmp));

    std::cout << home->get_name() << "|" << home->get_permissions() << "|" <<
              home->get_size() << std::endl;
}

int main(int argc, char* argv[]) {
    delegate();
    composite();
    return 0;
}