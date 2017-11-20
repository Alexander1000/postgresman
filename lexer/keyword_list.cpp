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

    bool exists(char *value)
    {
        bool isExists = false;
        char *pKeyword = NULL;
        int lexemeLength = strlen(value);

        for (int i = 0; i < lexemeLength; ++i) {
            if (value[i] >= 'A' && value[i] <= 'Z') {
                value[i] += 32;
            }
        }

        for (int i = 0; i < this->list.size(); ++i) {
            pKeyword = this->list.at(i);

            if (lexemeLength != strlen(pKeyword)) {
                continue;
            }

            if (strcmp(value, pKeyword) == 0) {
                isExists = true;
            }
        }

        return isExists;
    }

private:
    std::vector<char*> list;
};
