#include <expat.h>
#include <string.h>
#include "dialog.h"

int ContentCode = 1;
int ResponseCode = 2;

struct DialogBuilder
{
    int token_code;
    Phrase* m_phrase;
    Response* m_respose;

    DialogBuilder(Dialog* d)
        : m_d(d)
    {}

    Dialog* m_d = nullptr;
};

void start(void *data, const char *el, const char **attr)
{
    DialogBuilder* d = (DialogBuilder*)data;
    int i;

    if (!strcmp(el, "dialogs"))
    {
    }
    else if (!strcmp(el, "dialog"))
    {
    }
    else if (!strcmp(el, "phrases"))
    {
    }
    else if (!strcmp(el, "phrase"))
    {
        d->m_phrase = new Phrase;
        for (i = 0; attr[i]; i += 2)
        {
            if (!strcmp(attr[i], "id"))
            {
                d->m_phrase->id = atoi(attr[i+1]);
            }
        }
    }
    else if (!strcmp(el, "content"))
    {
        d->token_code = ContentCode;
    }
    else if (!strcmp(el, "responses"))
    {
    }
    else if (!strcmp(el, "response"))
    {
        d->m_respose = new Response;
        for (i = 0; attr[i]; i += 2)
        {
            if (!strcmp(attr[i], "id"))
            {
                d->m_respose->id = atoi(attr[i+1]);
            }
            else if (!strcmp(attr[i], "next"))
            {
                d->m_respose->next_phrase = atoi(attr[i+1]);
            }
        }

        d->token_code = ResponseCode;
    }
    else
    {
        d->token_code = 0;
    }
}  /* End of start handler */

void end(void *data, const char *el)
{
    DialogBuilder* b = (DialogBuilder*)data;
    if (!strcmp(el, "dialogs"))
    {
    }
    else if (!strcmp(el, "dialog"))
    {
    }
    else if (!strcmp(el, "phrases"))
    {
    }
    else if (!strcmp(el, "phrase"))
    {
        b->m_d->AddPhrase(b->m_phrase->id, b->m_phrase);
        b->m_phrase = nullptr;
    }
    else if (!strcmp(el, "content"))
    {
        b->token_code = 0;
    }
    else if (!strcmp(el, "responses"))
    {
    }
    else if (!strcmp(el, "response"))
    {
        b->m_phrase->m_responses[b->m_respose->id] = b->m_respose;
        b->m_respose = nullptr;
        b->token_code = 0;
    }
}

void text(void *userData, const XML_Char *s, int len)
{
    DialogBuilder* d = (DialogBuilder*)userData;
    if (d->token_code == ContentCode)
    {
        d->m_phrase->content.assign(s, s+len);
    }
    else if (d->token_code == ResponseCode)
    {
        d->m_respose->content.assign(s, s+len);
    }
}


Dialog::Dialog()
{
    XML_Parser p = XML_ParserCreate(NULL);
    if (! p) {
        fprintf(stderr, "Couldn't allocate memory for parser\n");
        exit(-1);
    }

    XML_SetElementHandler(p, start, end);
    XML_SetCharacterDataHandler(p, text);
    DialogBuilder b(this);
    XML_SetUserData(p, &b);

    FILE* f = fopen("../data.xml", "rb");
    if (f == 0)
        return;

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::vector<char> buffer;
    buffer.resize(size);
    fread(&buffer[0], sizeof(char), size, f);

    if (!XML_Parse(p, &buffer[0], buffer.size(), 1))
    {
        fprintf(stderr, "Parse error at line %d:\n%s\n",
                XML_GetCurrentLineNumber(p),
                XML_ErrorString(XML_GetErrorCode(p)));
        exit(-1);
    }
}

void Dialog::AddPhrase(int index, Phrase *value)
{
    m_phrases[index] = value;
}

void Dialog::Start()
{
    m_current = m_phrases[1];
}

void Dialog::Terminate()
{
    m_current = nullptr;
}

const std::string Dialog::GetCurrentPhrase()
{
    if (m_current)
        return m_current->content;
}

const std::vector<std::string> Dialog::GetCurrentResponses()
{
    std::vector<std::string> res;
    if (m_current)
    {
        for (auto e : m_current->m_responses)
        {
            res.push_back(e.second->content);
        }
    }
    return res;
}

bool Dialog::ChooseResponse(int index)
{
    if (index >= 0)
    {
        if (m_current)
        {
            auto it = m_current->m_responses.begin();
            std::advance(it, index);
            m_current = m_phrases[it->second->next_phrase];
            return m_current->m_responses.empty();
        }
    }
    return true;
}
