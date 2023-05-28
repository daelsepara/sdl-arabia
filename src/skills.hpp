#ifndef __SKILLS__HPP__
#define __SKILLS__HPP__

#include <vector>

#include "items.hpp"

namespace Skill
{
    enum class Type
    {
        NONE = -1,
        ARCHERY,
        AGILITY,
        CUNNING,
        FOLKLORE,
        LUCK,
        MAGIC,
        ROGUERY,
        SEAFARING,
        STREETWISE,
        SWORDPLAY,
        WILDERNESS_LORE,
        WRESTLING
    };

    class Base
    {
    public:
        const char *Name = NULL;
        const char *Description = NULL;
        Skill::Type Type;
        Item::Type Requirement = Item::Type::NONE;

        Base(const char *name, const char *description, Skill::Type type, Item::Type item)
        {
            Name = name;
            Type = type;
            Description = description;
            Requirement = item;
        }

        Base(const char *name, const char *description, Skill::Type type)
        {
            Name = name;
            Type = type;
            Description = description;
            Requirement = Item::Type::NONE;
        }
    };

    auto ARCHERY = Skill::Base("ARCHERY", "A long-range attack for both hunting and combat. You must possess a BOW to use this skill.", Skill::Type::ARCHERY, Item::Type::BOW);
    auto AGILITY = Skill::Base("AGILITY", "The ability to perform acrobatic feats, run, climb, balance and leap. A character with this skill is nimble and dexterous.", Skill::Type::AGILITY);
    auto CUNNING = Skill::Base("CUNNING", "The ability to think on your feet and devise clever ploys for getting out of trouble. Useful in countless situations.", Skill::Type::CUNNING);
    auto FOLKLORE = Skill::Base("FOLKLORE", "Knowledge of myth and legend. Such knowledge is power, and you know the best way of dealing with any supernatural menace.", Skill::Type::FOLKLORE);
    auto LUCK = Skill::Base("LUCK", "The general ability to 'fall on your feet'. Your natural good fortune will help you in all sorts of situations.", Skill::Type::LUCK);
    auto MAGIC = Skill::Base("MAGIC", "The ability to summon a jinni to do your bidding. You must possess a RING to use this skill.", Skill::Type::MAGIC, Item::Type::RING);
    auto ROGUERY = Skill::Base("ROGUERY", "The traditional repertoire of thief's tricks: picking pockets, opening locks, and skulking unseen in the shadows.", Skill::Type::ROGUERY);
    auto SEAFARING = Skill::Base("SEAFARING", "Knowing all about life at sea, including the ability to handle anything from a rowboat right up to a large sailing boat.", Skill::Type::SEAFARING);
    auto STREETWISE = Skill::Base("STREETWISE", "With this skill you are never at a loss in towns and cities. What others see as the squalor and menace of narrow alleys is home to you.", Skill::Type::STREETWISE);
    auto SWORDPLAY = Skill::Base("SWORDPLAY", "The best fighting skill, but to use it you must possess a SWORD.", Skill::Type::SWORDPLAY, Item::Type::SWORD);
    auto WILDERNESS_LORE = Skill::Base("WILDERNESS LORE", "A talent for survival in the wild -- whether forest, desert, swamp or mountain peak.", Skill::Type::WILDERNESS_LORE);
    auto WRESTLING = Skill::Base("WRESTLING", "You know how to handle yourself in a brawl, winning victory with armlocks, holds, leg sweeps and forearm jabs. You need no weapons -- your own body is the weapon.", Skill::Type::WRESTLING);

    std::vector<Skill::Base> ALL = {Skill::ARCHERY, Skill::AGILITY, Skill::CUNNING, Skill::FOLKLORE, Skill::LUCK, Skill::MAGIC, Skill::ROGUERY, Skill::SEAFARING, Skill::STREETWISE, Skill::SWORDPLAY, Skill::WRESTLING};

    int FIND(std::vector<Skill::Base> &skills, Skill::Type skill)
    {
        auto found = -1;

        if (skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (skills[i].Type == skill)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_LIST(std::vector<int> selection, int item)
    {
        auto found = -1;

        for (auto i = 0; i < selection.size(); i++)
        {
            if (selection[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    bool VERIFY(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        return FIND(skills, skill.Type) >= 0;
    }

    void ADD(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        if (!VERIFY(skills, skill))
        {
            skills.push_back(skill);
        }
    }

    void REMOVE(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        auto result = FIND(skills, skill.Type);

        if (result >= 0)
        {
            skills.erase(skills.begin() + result);
        }
    }

} // namespace Skill

#endif
