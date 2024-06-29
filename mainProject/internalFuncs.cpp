#include "internalFuncs.hpp"
#include <cctype>
#include <vector>

std::ostream& myFuncs::outError(std::ostream& out, const std::string& errText)
{
    out << errText << '\n';
    return out;
}

storage_t myFuncs::readStorage(std::istream& in)
{
    storage_t resStorage;
    std::string word = "";
    while (!in.eof())
    {
        if (in >> word)
        {
            cleanUpWord(word);
            if (checkLiter(word))
            {
                std::string spType = getSpType(word);
                auto scanFor = resStorage.find(spType);
                if (scanFor == resStorage.end())
                {
                    std::vector< std::string > words;
                    words.push_back(word);
                    resStorage.emplace(spType, words);
                }
                else
                {
                    (resStorage.at(spType)).push_back(word);
                }
            }
        }
    }
    return resStorage;
}

void myFuncs::cleanUpWord(std::string& word)
{
    std::string puncts = ".,:;?!";
    for (char p : puncts)
    {
        if (word.back() == p)
        {
            word.pop_back();
        }
    }

    std::string extras = "(){}[]<>'";
    for (char ex : extras)
    {
        if (word.back() == ex)
        {
            word.pop_back();
        }
        if (word.front() == ex)
        {
            word.erase(word.begin());
        }
    }
}

bool myFuncs::checkLiter(const std::string& word)
{
    for (char c : word)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

std::string myFuncs::getSpType(std::string& word)
{
    std::string resType = "";

    storage_t rusEnds;

    rusEnds["noun"] = { "�", "��", "��", "��", "����", "���", "���", "��", "��", "�", "���" };
    std::vector< std::string > nSec = { "��", "��", "��", "�", "�", "��", "���", "��" };
    std::vector< std::string > nThi = { "�", "��", "���", "���", "������", "��", "��" };
    std::vector< std::string > nFou = { "��", "�", "���", "�", "��", "��", "��", "���" };
    std::vector< std::string > nFif = { "�", "�", "��", "��", "��", "���", "���", "��", "��" };
    rusEnds["noun"].insert(rusEnds["noun"].end(), nSec.begin(), nSec.end());
    rusEnds["noun"].insert(rusEnds["noun"].end(), nThi.begin(), nThi.end());
    rusEnds["noun"].insert(rusEnds["noun"].end(), nFou.begin(), nFou.end());
    rusEnds["noun"].insert(rusEnds["noun"].end(), nFif.begin(), nFif.end());

    rusEnds["verb"] = { "���", "���", "���", "����", "����", "���", "���", "���", "��", "��" };
    std::vector< std::string > vSec = { "���", "��", "���", "���", "��", "��", "���", "���" };
    std::vector< std::string > vThi = { "��", "���", "���", "��", "�", "�", "��", "�", "��" };
    std::vector< std::string > vFou = { "��", "��", "��", "���", "���", "��", "���", "���", "��" };
    std::vector< std::string > vFif = { "���", "���", "��", "��", "��", "�", "��", "��", "��" };
    rusEnds["verb"].insert(rusEnds["verb"].end(), vSec.begin(), vSec.end());
    rusEnds["verb"].insert(rusEnds["verb"].end(), vThi.begin(), vThi.end());
    rusEnds["verb"].insert(rusEnds["verb"].end(), vFou.begin(), vFou.end());
    rusEnds["verb"].insert(rusEnds["verb"].end(), vFif.begin(), vFif.end());

    rusEnds["adjective"] = { "��", "��", "��", "��", "���", "���", "��", "��", "��", "��" };
    std::vector< std::string > aSec = { "���", "���", "���", "���", "��", "��", "��", "��" };
    std::vector< std::string > aThi = { "��", "��", "��", "��", "��", "��", "��", "��" };
    rusEnds["adjective"].insert(rusEnds["adjective"].end(), aSec.begin(), aSec.end());
    rusEnds["adjective"].insert(rusEnds["adjective"].end(), aThi.begin(), aThi.end());

    rusEnds["adverb"] = { "���", "���", "���", "���", "���", "���", "���", "���", "���" };
    std::vector< std::string > dSec = { "���", "���", "��", "��", "��", "����" };
    rusEnds["adjective"].insert(rusEnds["adjective"].end(), dSec.begin(), dSec.end());


    rusEnds["numeric"] = { "�����", "���", "���", "���", "���", "���", "����", "���", "���" };
    std::vector< std::string > uSec = { "�����", "���", "���", "���", "������", "������" };
    std::vector< std::string > uThi = { "���", "���", "�����", "���", "���", "��", "���" };
    std::vector< std::string > uFou = { "���", "����", "���", "���", "���", "���" };
    rusEnds["numeric"].insert(rusEnds["numeric"].end(), uSec.begin(), uSec.end());
    rusEnds["numeric"].insert(rusEnds["numeric"].end(), uThi.begin(), uThi.end());
    rusEnds["numeric"].insert(rusEnds["numeric"].end(), uFou.begin(), uFou.end());

    rusEnds["conjuct"] = { "�����", "�����", "�����", "������", "�����", "������", "����" };
    std::vector< std::string > cSec = { "����", "���", "���", "�����", "���", "����", "����" };
    std::vector< std::string > cThi = { "�", "��", "����", "����", "�����", "���", "�����" };
    std::vector< std::string > cFou = { "������", "�����", "����", "���", "���", "����" };
    rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cSec.begin(), cSec.end());
    rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cThi.begin(), cThi.end());
    rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cFou.begin(), cFou.end());

    rusEnds["prepos"] = { "�", "��", "slovo", "��", "��", "�", "��", "�", "��", "�", "�����" };
    std::vector< std::string > pSec = { "��-���", "���", "���", "��", "�", "������", "���" };
    std::vector< std::string > pThi = { "�����", "��-��", "���", "�����", "���", "�����" };
    rusEnds["prepos"].insert(rusEnds["prepos"].end(), pSec.begin(), pSec.end());
    rusEnds["prepos"].insert(rusEnds["prepos"].end(), pThi.begin(), pThi.end());

    for (auto iter = rusEnds["prepos"].begin(); iter != rusEnds["prepos"].end(); ++iter)
    {
        if (word == *iter)
        {
            return "Prepos";
        }
    }
    for (auto iter = rusEnds["conjuct"].begin(); iter != rusEnds["conjuct"].end(); ++iter)
    {
        if (word == *iter)
        {
            return "Conjuct";
        }
    }
    for (auto iter = rusEnds["numeric"].begin(); iter != rusEnds["numeric"].end(); ++iter)
    {
        if (word == *iter)
        {
            return "Numeric";
        }
    }

    std::vector< std::string > spTypes = { "noun", "verb", "adjective", "adverb", "numeric" };
    for (auto iter = spTypes.begin(); iter != spTypes.end(); ++iter)
    {
        for (size_t i = 0; i <= 6; i++)
        {
            if (checkType(word, i, rusEnds[*iter]))
            {
                return *iter;
            }
        }
    }

    return resType;
}

bool myFuncs::checkType(std::string& word, size_t& endSize, std::vector< std::string >& ends)
{
    std::string endL = word.substr(word.length() - endSize);
    for (auto iter = ends.begin(); iter != ends.end(); ++iter)
    {
        if (endL == *iter)
        {
            return true;
        }
    }
    return false;
}

void myFuncs::outDepot(std::string dest, std::ofstream& out, std::map< std::string, storage_t >& depot)
{
    for (auto storage : depot)
    {
        out.open(dest + "\\" + storage.first + ".txt");
        if (out.is_open())
        {
            for (auto iter : storage.second)
            {
                size_t len = (iter.second).size();
                for (size_t i = 0; i < len; i++)
                {
                    out << iter.second[i] << " ";
                }
            }
        }
        out.close();
    }
}

int myFuncs::letToSound(int let, bool& softFact)
{
    const std::string softMakers = "���������";
    const std::string notSoftMakers = "������������������������";

    std::map< int, int > softSounds = { { -11887, -12098 }, { -12103, -12103 }, { -11889, -12112 }, { -11897, -11897 },
    { -12104, -12104 }, { -11895, -11895 }, { -11890, -11901 } };

    for (int l : softMakers)
    {
        if (l == let)
        {
            softFact = true;
            return (*(softSounds.find(l))).second;
        }
    }

    std::map< int, int > nSoftSounds = { { -11898, -11898 }, { -11901, -11901 }, { -12102, -12102 }, { -12099, -12099 },
    { -12109, -12102 }, { -11896, -11896 }, { -12105, -11903 }, { -11899, -11899 }, { -11900, -11900 },
    { -11893, -11893 }, { -12110, -12110 }, { -12112, -12112 }, { -12097, -12097 }, { -11904, -11904 },
    { -12098, -12098 }, { -12101, -12101 }, { -12108, -11902 }, { -12106, -11896 }, { -11891, -11891 },
    { -11903, -11903 }, { -12100, -12100 }, { -11902, -11902 }, { -12111, -12097 } };

    for (int l : notSoftMakers)
    {
        if (l == let)
        {
            softFact = false;
            return (*(nSoftSounds.find(l))).second;
        }
    }
    return ' ';
}

bool myFuncs::printSound(std::ostream& out, int sound, bool softFact)
{
    std::string vowel = "������";
    for (int l : vowel)
    {
        if (l == sound)
        {
            out << "[ " << sound << " ] - �������";
            if (l == -12098 && softFact)
            {
                out << " ,�������";
            }
            out << '\n';
            return true;
        }
    }

    std::string deafNPair = "����";
    std::string deafPair = "������";
    std::string voicedNPair = "�����";
    std::string voicedPair = "�����";
    for (int l : deafNPair)
    {
        if (l == sound)
        {
            out << "[ " << sound << " ] - ���������, ������ ��������";
            if ((softFact && l == -11899) || (l != -11899))
            {
                out << " ,������";
                if (l == -11899)
                {
                    out << " ������";
                }
                else
                {
                    out << " ��������";
                }
            }
            else if (!softFact && l == -11899)
            {
                out << " ,������� ������";
            }
            out << '\n';
            return false;
        }
    }

    for (int l : deafPair)
    {
        if (l == sound)
        {
            out << "[ " << sound << " ] - ���������, ������ ������";
            if (softFact && l != -11896)
            {
                out << " ,������";
                if (l == -11896)
                {
                    out << " ��������";
                }
                else
                {
                    out << " ������";
                }
            }
            else
            {
                if (l == -11896)
                {
                    out << " ,������� ��������";
                }
                else
                {
                    out << " ,������� ������";
                }
            }
            out << '\n';
            return false;
        }
    }

    for (int l : voicedNPair)
    {
        if (l == sound)
        {
            out << "[ " << sound << " ] - ���������, ������� ��������";
            if (l == -12103)
            {
                out << " ,������ ��������";
            }
            else if (softFact)
            {
                out << " ,������ ������";
            }
            else
            {
                out << " ,������� ������";
            }
            out << '\n';
            return false;
        }
    }

    for (int l : voicedPair)
    {
        if (l == sound)
        {
            out << "[ " << sound << " ] - ���������, ������� ������";
            if (softFact)
            {
                out << " ,������ ������";
            }
            else
            {
                out << " ,������� ������";
            }
            out << '\n';
            return false;
        }
    }

    return false;
}
