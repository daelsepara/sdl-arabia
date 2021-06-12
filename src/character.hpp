#ifndef __CHARACTER__HPP__
#define __CHARACTER__HPP__

#include <string>
#include <vector>

#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"

namespace Character
{
    enum class Type
    {
        CUSTOM = 0,
        WARRIOR,
        WIZARD,
        THIEF,
        RANGER,
        MERCHANT,
        NOMAD,
        BEGGAR
    };

    class Base
    {
    public:
        std::string Name = "";

        std::string Description = "";

        Character::Type Type = Character::Type::CUSTOM;

        int Life = 10;

        int Money = 12;

        int ITEM_LIMIT = 8;

        int MAX_LIFE_LIMIT = 10;

        int SKILLS_LIMIT = 4;

        std::vector<Skill::Base> Skills = std::vector<Skill::Base>();

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        std::vector<Item::Base> LostItems = std::vector<Item::Base>();

        std::vector<Skill::Base> LostSkills = std::vector<Skill::Base>();

        int LostMoney = 0;

        int StoryID = 0;

#if defined(_WIN32) || defined(__arm__)
        long long Epoch = 0;
#else
        long Epoch = 0;
#endif

        Base()
        {
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, int life, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Life = life;
            MAX_LIFE_LIMIT = life;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, std::vector<Codeword::Type> codewords, int life, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Codewords = codewords;
            Life = life;
            MAX_LIFE_LIMIT = life;
            Money = money;
        }
    };

    auto WARRIOR = Character::Base("The Warrior", Character::Type::WARRIOR, "You must live your life by the high ideals of the military code. You accept wounds to your body without flinching, but never a wound to your honour.", {Skill::ARCHERY, Skill::FOLKLORE, Skill::SWORDPLAY, Skill::WRESTLING}, {Item::BOW, Item::SWORD}, 12);
    auto WIZARD = Character::Base("The Wizard", Character::Type::WIZARD, "You are a student of sorcery and mystery. The stars of your birth guarantee you a charmed life.", {Skill::CUNNING, Skill::FOLKLORE, Skill::LUCK, Skill::MAGIC}, {Item::RING}, 12);
    auto THIEF = Character::Base("The Thief", Character::Type::THIEF, "Born and bred in the dark crannies of Baghdad's slums, you believe your knavish skills are equal to any challenge.", {Skill::AGILITY, Skill::CUNNING, Skill::ROGUERY, Skill::STREETWISE}, {}, 12);
    auto RANGER = Character::Base("The Ranger", Character::Type::RANGER, "You have no fear of any peril that nature can throw at you. The only true evil in this world resides in the hearts of selfish men.", {Skill::ARCHERY, Skill::SEAFARING, Skill::STREETWISE, Skill::WILDERNESS_LORE}, {Item::BOW}, 12);
    auto MERCHANT = Character::Base("The Merchant", Character::Type::MERCHANT, "In your youth you were fascinated by the strange journeys of Sinbad. Now you have the chance to outdo them.", {Skill::LUCK, Skill::ROGUERY, Skill::SEAFARING, Skill::SWORDPLAY}, {Item::SWORD}, 12);
    auto NOMAD = Character::Base("The Nomad", Character::Type::NOMAD, "Your true home is among the desert dunes. You know that city dwellers are not to be trusted.", {Skill::AGILITY, Skill::FOLKLORE, Skill::MAGIC, Skill::WILDERNESS_LORE}, {Item::RING}, 12);
    auto BEGGAR = Character::Base("The Beggar", Character::Type::BEGGAR, "All pious men should give generously to the poor, but in your experience many disregard this. No matter -- if you aren't offered charity, you'll simply take it.", {Skill::CUNNING, Skill::LUCK, Skill::STREETWISE, Skill::WRESTLING}, {}, 12);
    auto CUSTOM = Character::Base("Custom Character", Character::Type::CUSTOM, "This is a player generated character.", {}, {}, 12);

    std::vector<Character::Base> Classes = {Character::WARRIOR, Character::WIZARD, Character::THIEF, Character::RANGER, Character::MERCHANT, Character::NOMAD, Character::BEGGAR};

    int FIND_ITEM(Character::Base &player, Item::Type item)
    {
        auto found = -1;

        if (player.Items.size() > 0)
        {
            for (auto i = 0; i < player.Items.size(); i++)
            {
                if (player.Items[i].Type == item && player.Items[i].Charge != 0)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = -1;

        if (player.Skills.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found >= items.size();
    }

    int COUNT_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        auto found = 0;

        for (auto i = 0; i < items.size(); i++)
        {
            if (Character::FIND_ITEM(player, items[i].Type) >= 0)
            {
                found++;
            }
        }

        return found;
    }

    bool VERIFY_ITEMS_ANY(Character::Base &player, std::vector<Item::Base> items)
    {
        return Character::COUNT_ITEMS(player, items) > 0;
    }

    // Checks if player has the skill and the required item
    bool VERIFY_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    if (player.Skills[i].Requirement != Item::Type::NONE)
                    {
                        found = Character::VERIFY_ITEMS(player, {player.Skills[i].Requirement});
                    }
                    else
                    {
                        found = true;
                    }

                    break;
                }
            }
        }
        return found;
    }

    bool VERIFY_ANY_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ALL_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found++;
                }
            }
        }

        return found == skills.size();
    }

    bool HAS_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL_ITEMS(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE && items.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    for (auto j = 0; j < items.size(); j++)
                    {
                        if (Character::FIND_ITEM(player, items[j]) >= 0)
                        {
                            found++;
                        }
                    }
                }
            }
        }

        return found;
    }

    // verify that player has the skill and ANY of the items
    bool VERIFY_SKILL_ANY(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) > 0;
    }

    // verify that player has the skill and ALL of the items
    bool VERIFY_SKILL_ALL(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) == items.size();
    }

    bool VERIFY_SKILL_ITEM(Character::Base &player, Skill::Type skill, Item::Type item)
    {
        return Character::VERIFY_SKILL_ALL(player, skill, {item});
    }

    int FIND_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        auto found = -1;

        if (player.Codewords.size() > 0)
        {
            for (auto i = 0; i < player.Codewords.size(); i++)
            {
                if (player.Codewords[i] == codeword)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        auto found = 0;

        if (player.Codewords.size() > 0 && codewords.size() > 0)
        {
            for (auto i = 0; i < codewords.size(); i++)
            {
                auto result = Character::FIND_CODEWORD(player, codewords[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found;
    }

    bool VERIFY_CODEWORDS_ANY(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) > 0;
    }

    bool VERIFY_CODEWORDS_ALL(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) == codewords.size();
    }

    bool VERIFY_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::VERIFY_CODEWORDS_ALL(player, codewords);
    }

    bool VERIFY_LIFE(Character::Base &player, int threshold = 0)
    {
        return player.Life > threshold;
    }

    bool VERIFY_POSSESSIONS(Character::Base &player)
    {
        return player.Items.size() <= player.ITEM_LIMIT;
    }

    void GET_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        player.Items.insert(player.Items.end(), items.begin(), items.end());
    }

    void GET_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        for (auto i = 0; i < codewords.size(); i++)
        {
            if (!Character::VERIFY_CODEWORDS(player, {codewords[i]}))
            {
                player.Codewords.push_back(codewords[i]);
            }
        }
    }

    void REMOVE_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        if (Character::VERIFY_CODEWORDS(player, {codeword}))
        {
            auto result = FIND_CODEWORD(player, codeword);

            if (result >= 0)
            {
                player.Codewords.erase(player.Codewords.begin() + result);
            }
        }
    }

    void GET_UNIQUE_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        for (auto i = 0; i < items.size(); i++)
        {
            if (!Character::VERIFY_ITEMS(player, {items[i].Type}))
            {
                player.Items.push_back(items[i]);
            }
        }
    }

    void LOSE_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        if (player.Items.size() > 0 && items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    player.Items.erase(player.Items.begin() + result);
                }
            }
        }
    }

    void LOSE_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                auto result = Character::FIND_SKILL(player, skills[i]);

                if (result >= 0)
                {
                    player.LostSkills.push_back(player.Skills[result]);

                    player.Skills.erase(player.Skills.begin() + result);
                }
            }
        }
    }

    void GAIN_LIFE(Character::Base &player, int life)
    {
        player.Life += life;

        if (player.Life < 0)
        {
            player.Life = 0;
        }
        else if (player.Life > player.MAX_LIFE_LIMIT)
        {
            player.Life = player.MAX_LIFE_LIMIT;
        }
    }

    void GAIN_MONEY(Character::Base &player, int money)
    {
        player.Money += money;

        if (player.Money < 0)
        {
            player.Money = 0;
        }
    }

    void LOSE_POSSESSIONS(Character::Base &player)
    {
        player.LostItems = player.Items;

        player.Items.clear();
    }

    void LOSE_ALL(Character::Base &player)
    {
        player.LostMoney = player.LostMoney;
        player.Money = 0;

        Character::LOSE_POSSESSIONS(player);
    }

    void REFILL(Character::Base &player, Item::Type type)
    {
        for (auto i = 0; i < player.Items.size(); i++)
        {
            if (player.Items[i].Type == type)
            {
                player.Items[i].Charge = -1;
            }
        }
    }

    void EMPTY(Character::Base &player, Item::Type type)
    {
        for (auto i = 0; i < player.Items.size(); i++)
        {
            if (player.Items[i].Type == type && player.Items[i].Charge == -1)
            {
                player.Items[i].Charge = 0;

                break;
            }
        }
    }

} // namespace Character

#endif
