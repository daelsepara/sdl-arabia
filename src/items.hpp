#ifndef __ITEMS__HPP__
#define __ITEMS__HPP__

#include <vector>

namespace Item
{
    enum class Type
    {
        NONE = -1,
        BOW,
        RING,
        SWORD,
        CLOAK,
        JEWELLED_SWORD,
        BLACK_JEWEL,
        HAWK,
        GOLDEN_APPLE,
        WATER_BOTTLE,
        MAGIC_SLIPPERS,
        JASMINE_FLOWER,
        INDIAN_ROPE,
        CHART,
        HUBBLE_BUBBLE_PIPE,
        LONG_TAILED_CAT,
        LAMP_OF_ANTAR,
        DIAMOND,
        PRAYER_MAT,
        First = BOW,
        Last = PRAYER_MAT
    };

    class Base
    {
    public:
        std::string Name;
        std::string Description;

        Item::Type Type = Item::Type::NONE;

        int Charge = -1;

        Base()
        {
        }

        Base(const char *name, const char *description, Item::Type type)
        {
            Name = name;
            Description = description;
            Type = type;
        }

        Base(const char *name, const char *description, Item::Type type, int charge)
        {
            Name = name;
            Description = description;
            Type = type;
            Charge = charge;
        }
    };

    // Item defaults
    auto BOW = Item::Base("BOW", "BOW", Item::Type::BOW);
    auto RING = Item::Base("RING", "RING", Item::Type::RING);
    auto SWORD = Item::Base("SWORD", "SWORD", Item::Type::SWORD);
    auto CLOAK = Item::Base("CLOAK", "CLOAK", Item::Type::CLOAK);
    auto JEWELLED_SWORD = Item::Base("JEWELLED SWORD", "JEWELLED SWORD", Item::Type::JEWELLED_SWORD);
    auto BLACK_JEWEL = Item::Base("BLACK JEWEL", "BLACK JEWEL", Item::Type::BLACK_JEWEL);
    auto HAWK = Item::Base("HAWK", "HAWK", Item::Type::HAWK);
    auto GOLDEN_APPLE = Item::Base("GOLDEN APPLE", "GOLDEN APPLE", Item::Type::GOLDEN_APPLE);
    auto WATER_BOTTLE = Item::Base("WATER BOTTLE", "WATER BOTTLE", Item::Type::WATER_BOTTLE);
    auto MAGIC_SLIPPERS = Item::Base("MAGIC SLIPPERS", "MAGIC SLIPPERS", Item::Type::MAGIC_SLIPPERS);
    auto JASMINE_FLOWER = Item::Base("JASMINE FLOWER", "JASMINE FLOWER", Item::Type::JASMINE_FLOWER);
    auto INDIAN_ROPE = Item::Base("INDIAN ROPE", "INDIAN ROPE", Item::Type::INDIAN_ROPE);
    auto CHART = Item::Base("CHART", "CHART", Item::Type::CHART);
    auto HUBBLE_BUBBLE_PIPE = Item::Base("HUBBLE BUBBLE PIPE", "HUBBLE BUBBLE PIPE", Item::Type::HUBBLE_BUBBLE_PIPE);
    auto LONG_TAILED_CAT = Item::Base("LONG TAILED CAT", "LONG TAILED CAT", Item::Type::LONG_TAILED_CAT);
    auto LAMP_OF_ANTAR = Item::Base("LAMP of Antar", "LAMP of Antar", Item::Type::LAMP_OF_ANTAR);
    auto DIAMOND = Item::Base("DIAMOND", "DIAMOND", Item::Type::DIAMOND);
    auto PRAYER_MAT = Item::Base("PRAYER-MAT", "PRAYER-MAT", Item::Type::PRAYER_MAT);

    std::vector<Item::Type> UniqueItems = {Item::Type::LONG_TAILED_CAT, Item::Type::LAMP_OF_ANTAR};

    bool IsUnique(Item::Type item)
    {
        auto unique = false;

        for (auto i = 0; i < Item::UniqueItems.size(); i++)
        {
            if (Item::UniqueItems[i] == item)
            {
                unique = true;

                break;
            }
        }

        return unique;
    }

    void REMOVE(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    items.erase(items.begin() + i);

                    break;
                }
            }
        }
    }

    void ADD(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            auto found = 0;

            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    found++;
                }
            }

            if (found == 0)
            {
                items.push_back(item);
            }
        }
        else
        {
            items.push_back(item);
        }
    }

    bool VERIFY(std::vector<Item::Base> &items, Item::Base item)
    {
        auto has = false;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    has = true;

                    break;
                }
            }
        }

        return has;
    }

    int FIND(std::vector<int> list, int item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int FIND_TYPE(std::vector<Item::Base> list, Item::Type item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int COUNT_TYPES(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = 0;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found++;
            }
        }

        return found;
    }

    int FIND_LEAST(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = -1;

        auto min = 255;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                if (list[i].Charge < min)
                {
                    found = i;

                    min = list[i].Charge;
                }
            }
        }

        return found;
    }

} // namespace Item
#endif
