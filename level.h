#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

class Level {
    public:
    static std::shared_ptr<Level> make_level(int choice);
    virtual ~Level();
    virtual char generateBlock(std::string, bool) = 0;
};


class level_0 final: public Level{
    int pos;
public:
    level_0();
    ~level_0();
    char generateBlock(std::string input, bool isRandom) override ;
};

class level_1 : public Level{
public:
    ~level_1();
    char generateBlock(std::string, bool isRandom) override ;
};

class level_2 final: public Level{
public:
    ~level_2();
    char generateBlock(std::string, bool) override ;
};

class level_3 final: public Level{
    int pos;
public:
    level_3();
    ~level_3();
    char generateBlock(std::string, bool isRandom) override;
};

class level_4 final: public Level{
    int pos;
public:
    level_4();
    ~level_4();
    char generateBlock(std::string, bool) override ;
};



#endif
