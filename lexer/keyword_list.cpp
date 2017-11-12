#include <vector>

class KeywordList
{
public:
    KeywordList()
    {
    }

    void addValue(char* value)
    {
        this->list.push_back(value);
    }

private:
    std::vector<char*> list;
};
