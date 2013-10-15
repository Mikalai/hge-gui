#ifndef DIALOG_H
#define DIALOG_H

#include <map>
#include <string>
#include <vector>

struct Response
{
    int id;
    int next_phrase;
    std::string content;
};

struct Phrase
{
    int id;
    std::string content;
    std::map<int, Response*> m_responses;

    ~Phrase()
    {
        for (auto v : m_responses)
        {
            delete v.second;
        }
        m_responses.clear();
    }
};

class Dialog
{
public:
    Dialog();

    const std::string GetCurrentPhrase();
    const std::vector<std::string> GetCurrentResponses();

    void Start();
    void Terminate();

    //  returns true if dialog ends
    bool ChooseResponse(int index);

    void AddPhrase(int index, Phrase* value);
private:

    std::map<int, Phrase*> m_phrases;
    Phrase* m_current = nullptr;
};

#endif // DIALOG_H
