#ifndef __CODEWORDS__HPP__
#define __CODEWORDS__HPP__

#include <map>

namespace Codeword
{
    enum class Type
    {
        NONE = -1,
        CONCH,
        FABRIC,
        GEMINI,
        HAJJI,
        HAREM,
        IRIS,
        KISMET,
        MORDANT,
        NOOSE,
        SESAME,
        TRUCE,
        ZEBRA
    };

    std::map<Codeword::Type, const char *> Descriptions = {
        {Codeword::Type::CONCH, "Conch"},
        {Codeword::Type::FABRIC, "Fabric"},
        {Codeword::Type::GEMINI, "Gemini"},
        {Codeword::Type::HAJJI, "Hajji"},
        {Codeword::Type::HAREM, "Harem"},
        {Codeword::Type::IRIS, "Iris"},
        {Codeword::Type::KISMET, "Kismet"},
        {Codeword::Type::MORDANT, "Mordant"},
        {Codeword::Type::NOOSE, "Noose"},
        {Codeword::Type::SESAME, "Sesame"},
        {Codeword::Type::TRUCE, "Truce"},
        {Codeword::Type::ZEBRA, "Zebra"}};

    std::vector<Codeword::Type> Invisible = {};

    bool IsInvisible(Codeword::Type codeword)
    {
        auto invisible = false;

        for (auto i = 0; i < Codeword::Invisible.size(); i++)
        {
            if (Codeword::Invisible[i] == codeword)
            {
                invisible = true;

                break;
            }
        }

        return invisible;
    }

} // namespace Codeword
#endif
